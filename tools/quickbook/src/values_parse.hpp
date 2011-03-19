/*=============================================================================
    Copyright (c) 2010-2011 Daniel James

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#if !defined(BOOST_SPIRIT_QUICKBOOK_VALUES_PARSE_HPP)
#define BOOST_SPIRIT_QUICKBOOK_VALUES_PARSE_HPP

#include "values.hpp"
#include <boost/spirit/include/classic_core.hpp>

namespace quickbook {
    namespace cl = boost::spirit::classic;

    struct value_builder_save
    {
        value_builder_save(value_builder& a) : a(a) { a.save(); }
        ~value_builder_save() { a.restore(); }
        value_builder& a;
    };

    template <typename ParserT>
    struct value_save_parser
        : public cl::unary< ParserT, cl::parser< value_save_parser<ParserT> > >
    {
        typedef value_save_parser<ParserT> self_t;
        typedef cl::unary< ParserT, cl::parser< value_save_parser<ParserT> > > base_t;

        template <typename ScannerT>
        struct result
        {
            typedef typename cl::parser_result<ParserT, ScannerT>::type type;
        };

        value_save_parser(value_builder& a, ParserT const &p)
            : base_t(p)
            , builder_(a)
        {}

        template <typename ScannerT>
        typename result<ScannerT>::type parse(ScannerT const &scan) const
        {
            typedef typename ScannerT::iterator_t iterator_t;
            iterator_t save = scan.first;

            value_builder_save saver(builder_);

            typename cl::parser_result<ParserT, ScannerT>::type result
                = this->subject().parse(scan);

            if (result) {
                return scan.create_match(result.length(), cl::nil_t(), save, scan.first);
            }
            else {
                return scan.no_match();
            }
        }
        
        value_builder& builder_;
    };

    struct value_save_gen
    {
        explicit value_save_gen(value_builder& b)
            : builder_(b) {}

        template<typename ParserT>
        value_save_parser<typename cl::as_parser<ParserT>::type>
        operator[](ParserT const& p) const
        {
            typedef typename cl::as_parser<ParserT> as_parser_t;
            typedef typename as_parser_t::type parser_t;
            
            return value_save_parser<parser_t>
                (builder_, as_parser_t::convert(p));
        }
        
        value_builder& builder_;
    };

    struct value_builder_list
    {
        value_builder_list(value_builder& a, value::tag_type t)
            : a(a), finished(false) { a.start_list(t); }
        void finish() { a.finish_list(); finished = true; }
        ~value_builder_list() { if(!finished) a.clear_list(); }
        value_builder& a;
        bool finished;
    };

    template <typename ParserT>
    struct value_scoped_list_parser
        : public cl::unary< ParserT, cl::parser< value_scoped_list_parser<ParserT> > >
    {
        typedef value_scoped_list_parser<ParserT> self_t;
        typedef cl::unary< ParserT, cl::parser< value_scoped_list_parser<ParserT> > > base_t;

        template <typename ScannerT>
        struct result
        {
            typedef typename cl::parser_result<ParserT, ScannerT>::type type;
        };

        value_scoped_list_parser(value_builder& a, value::tag_type k, ParserT const &p)
            : base_t(p)
            , builder_(a)
            , tag_(k)
        {}

        template <typename ScannerT>
        typename result<ScannerT>::type parse(ScannerT const &scan) const
        {
            typedef typename ScannerT::iterator_t iterator_t;
            iterator_t save = scan.first;

            value_builder_list list(builder_, tag_);
            typename cl::parser_result<ParserT, ScannerT>::type result
                = this->subject().parse(scan);

            if (result) {
                list.finish();
                return scan.create_match(result.length(), cl::nil_t(), save, scan.first);
            }
            else {
                return scan.no_match();
            }
        }
        
        value_builder& builder_;
        value::tag_type tag_;
    };
    
    struct value_scoped_list_gen
    {
        explicit value_scoped_list_gen(value_builder& b, value::tag_type t = value::no_tag)
            : b(b), tag_(t) {}

        template<typename ParserT>
        value_scoped_list_parser<typename cl::as_parser<ParserT>::type>
        operator[](ParserT const& p) const
        {
            typedef typename cl::as_parser<ParserT> as_parser_t;
            typedef typename as_parser_t::type parser_t;
            
            return value_scoped_list_parser<parser_t>
                (b, tag_, as_parser_t::convert(p));
        }
        
        value_scoped_list_gen operator()(value::tag_type const& tag) const
        {
            return value_scoped_list_gen(b, tag);
        }
        
        value_builder& b;
        value::tag_type tag_;
    };

    /* value_scoped_list_gen
     */

    struct value_string_entry {
        value_string_entry(value_builder& b, std::string const& v, value::tag_type t = value::no_tag)
            : b(b), v(v), tag_(t) {}

        template <typename Iterator>
        void operator()(Iterator, Iterator) const {
            b.insert(bbk_value(v, tag_));
        }

        value_builder& b;
        std::string v;
        value::tag_type tag_;
    };

    struct value_entry
    {
        value_entry(value_builder& b, value::tag_type t = value::no_tag)
            : b(b), tag_(t) {}

        template <typename Iterator>
        void operator()(Iterator begin, Iterator end) const {
            b.insert(qbk_value(begin, end, tag_));
        }
        
        value_string_entry operator()(std::string const& value) {
            return value_string_entry(b, value, tag_);
        }

        value_string_entry operator()(value::tag_type tag, std::string const& value) {
            return value_string_entry(b, value, tag);
        }

        value_entry operator()(value::tag_type const& value) {
            return value_entry(b, value);
        }

        value_builder& b;
        value::tag_type tag_;
    };

    struct value_fixed_tag {
        value_fixed_tag(value_builder& b, value::tag_type v)
            : b(b), v(v) {}

        template <typename Iterator>
        void operator()(Iterator, Iterator) const {
            b.set_tag(v);
        }

        value_builder& b;
        value::tag_type v;
    };

    struct value_tag
    {
        value_tag(value_builder& b)
            : b(b) {}

        void operator()(value::tag_type value) const {
            b.set_tag(value);
        }

        value_fixed_tag operator()(value::tag_type value) {
            return value_fixed_tag(b, value);
        }

        value_builder& b;
    };

    struct value_reset
    {
        value_reset(value_builder& b)
            : b(b) {}

        template <typename Iterator>
        void operator()(Iterator, Iterator) const {
            b.reset();
        }

        value_builder& b;
    };
    
    struct value_sort
    {
        value_sort(value_builder& b)
            : b(b) {}

        template <typename Iterator>
        void operator()(Iterator, Iterator) const {
            b.sort_list();
        }

        value_builder& b;
    };

    struct value_parser
    {
        value_parser()
            : builder()
            , save(builder)
            , reset(builder)
            , scoped(builder)
            , tag(builder)
            , entry(builder)
            , sort(builder)
            {}
    
        value get() { return builder.get(); }

        value_builder builder;
        value_save_gen save;
        value_reset reset;
        value_scoped_list_gen scoped;
        value_tag tag;
        value_entry entry;
        value_sort sort;
    };
}

#endif
