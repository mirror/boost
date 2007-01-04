///////////////////////////////////////////////////////////////////////////////
// toy_spirit2.cpp
//
//  Copyright 2006 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <cctype>
#include <string>
#include <iomanip>
#include <iostream>
#include <boost/assert.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/xpressive/proto/proto.hpp>
#include <boost/xpressive/proto/transform/arg.hpp>
#include <boost/xpressive/proto/transform/construct.hpp>
#include <boost/xpressive/proto/transform/fold_to_list.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/algorithm/iteration/fold.hpp>
#include <boost/fusion/algorithm/query/any.hpp>
#include <boost/test/unit_test.hpp>

namespace boost
{
    // global tags
    struct char_tag {};
    struct ichar_tag {};
    struct istring_tag {};
    struct ichar_range_tag {};
    struct never_tag {};
    struct always_tag {};
    struct space_tag {};

    inline std::ostream & operator<<(std::ostream &sout, char_tag)
    { return sout; }

    // global primitives
    proto::meta::terminal<char_tag>::type const char_ = {{}};
    proto::meta::terminal<space_tag>::type const space = {{}};

    template<typename T>
    struct literal
      : proto::extends<typename proto::meta::terminal<T>::type, literal<T> >
    {
        typedef typename proto::meta::terminal<T>::type terminal_type;

        template<typename U>
        literal(U const &u)
          : proto::extends<terminal_type, literal<T> >(terminal_type::make(u))
        {}

        template<typename U>
        literal(literal<U> const &u)
          : proto::extends<terminal_type, literal<T> >(terminal_type::make(proto::arg(u)))
        {}

        using proto::extends<terminal_type, literal<T> >::operator =;
    };

    template<typename T>
    literal<T const &> lit(T const &t)
    {
        return literal<T const &>(t);
    }
}

namespace boost { namespace spirit2
{

    // Spirit2-specific tags ...
    struct parser_tag {};
    struct no_case_tag {};
    struct skipper_tag {};

    // handy typedefs
    typedef proto::meta::terminal<char_tag>::type anychar_p;
    typedef proto::meta::terminal<ichar_tag>::type ianychar_p;
    typedef proto::meta::terminal<char>::type chlit_p;
    typedef proto::meta::terminal<std::string>::type str_p;
    typedef proto::meta::terminal<char const *>::type szlit_p;
    typedef proto::meta::terminal<istring_tag>::type ianystr_p;
    typedef proto::meta::terminal<ichar_range_tag>::type ianychar_range_p;
    typedef proto::meta::terminal<never_tag>::type never_p;
    typedef proto::meta::terminal<space_tag>::type space_p;

    struct CharLiteral
      : proto::meta::terminal<char>
    {};

    struct NTBSLiteral
      : proto::meta::terminal<char const *>
    {};

    struct StdStringLiteral
      : proto::meta::terminal<std::string const &> // the const & is to work around a GCC bug
    {};

    struct CharParser
      : proto::meta::function<anychar_p, CharLiteral>
    {};

    struct ICharParser
      : proto::meta::function<ianychar_p, CharLiteral, CharLiteral>
    {};

    struct CharRangeParser
      : proto::meta::function<anychar_p, CharLiteral, CharLiteral>
    {};

    struct IStrParser
      : proto::meta::function<ianystr_p, StdStringLiteral>
    {};

    struct ICharRangeParser
      : proto::meta::function<ianychar_range_p, CharLiteral, CharLiteral>
    {};

    ianychar_p const ichar_ = {{}};
    ianystr_p const istr_ = {{}};
    ianychar_range_p const ichar_range_ = {{}};

    namespace utility
    {
        inline bool char_icmp(char ch, char lo, char hi)
        {
            return ch == lo || ch == hi;
        }

        template<typename FwdIter>
        inline bool string_cmp(char const *sz, FwdIter &begin, FwdIter end)
        {
            FwdIter tmp = begin;
            for(; *sz; ++tmp, ++sz)
                if(tmp == end || *tmp != *sz)
                    return false;
            begin = tmp;
            return true;
        }

        template<typename FwdIter>
        inline bool string_icmp(std::string const &str, FwdIter &begin, FwdIter end)
        {
            BOOST_ASSERT(0 == str.size() % 2);
            FwdIter tmp = begin;
            std::string::const_iterator istr = str.begin(), estr = str.end();
            for(; istr != estr; ++tmp, istr += 2)
                if(tmp == end || *tmp != *istr && *tmp != *(istr+1))
                    return false;
            begin = tmp;
            return true;
        }

        inline bool in_range(char ch, char lo, char hi)
        {
            return ch >= lo && ch <= hi;
        }

        inline bool in_irange(char ch, char lo, char hi)
        {
            return in_range(ch, lo, hi)
                || in_range(std::tolower(ch), lo, hi)
                || in_range(std::toupper(ch), lo, hi);
        }

        struct any_convertible
        {
            template<typename T>
            any_convertible(T const &);
        };

        inline std::string to_istr(char const *sz)
        {
            std::string res;
            res.reserve(std::strlen(sz) * 2);
            for(; *sz; ++sz)
            {
                res.push_back(std::tolower(*sz));
                res.push_back(std::toupper(*sz));
            }
            return res;
        }
    } // namespace utility

    // composite tags
    inline char const *tag_name(proto::tag::bitwise_or) { return "alternate"; }
    inline char const *tag_name(proto::tag::right_shift) { return "sequence"; }

    // Composite parser that contains a Fusion cons-list of other parsers
    // OR
    // A compiler that compiles an expression and wraps the result in 
    // a composite<> wrapper
    template<typename Tag, typename ListOrGrammar>
    struct composite
      : ListOrGrammar, Tag
    {
        composite();

        explicit composite(ListOrGrammar const &list)
          : ListOrGrammar(list)
        {}

        ListOrGrammar const &elems() const { return *this; }

        // The apply<> struct and the call() member are to satisfy the
        // proto compiler/transform protocol
        template<typename Expr, typename State, typename Visitor>
        struct apply
        {
            typedef composite<
                Tag
              , typename ListOrGrammar::template apply<Expr, State, Visitor>::type
            > type;
        };

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &state, Visitor &visitor)
        {
            return typename apply<Expr, State, Visitor>::type
                (ListOrGrammar::call(expr, state, visitor));
        }
    };

    struct char_range
      : std::pair<char, char>
    {
        char_range(char from, char to)
          : std::pair<char, char>(from, to)
        {}
    };

    struct ichar
    {
        ichar(char ch)
          : lo_(std::tolower(ch))
          , hi_(std::toupper(ch))
        {}

        char lo_, hi_;
    };

    struct istr
    {
        istr(char const *sz)
          : str_(utility::to_istr(sz))
        {}

        std::string str_;
    };

    struct ichar_range
      : std::pair<char, char>
    {
        ichar_range(char_range const &rng)
          : std::pair<char, char>(rng)
        {}
    };

    // The no-case directive
    namespace tag
    {
        struct no_case {};
    }

    struct no_case_directive
    {
        template<typename T>
        typename proto::meta::unary_expr<
            tag::no_case
          , typename proto::meta::as_expr_ref<T>::type
        >::type
        operator[](T const &t) const
        {
            typedef typename proto::meta::unary_expr<
                tag::no_case
              , typename proto::meta::as_expr_ref<T>::type
            >::type type;
            type that = {proto::as_expr_ref(t)};
            return that;
        }
    };

    no_case_directive const no_case = {};

    // The no-case transform, applies the tree-transform with
    // mpl::true_ as the visitor.
    template<typename Grammar>
    struct no_case_transform
      : Grammar
    {
        no_case_transform();

        template<typename Expr, typename State, typename>
        struct apply
          : Grammar::template apply<Expr, State, mpl::true_>
        {};

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &state, Visitor &)
        {
            mpl::true_ case_sensitive;
            return Grammar::call(expr, state, case_sensitive);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    /// Begin ToySpiritGrammar here
    ///////////////////////////////////////////////////////////////////////////////

    template<typename T, bool CaseSensitive>
    struct remove_case
    {
        typedef T type;
        static T const &call(T const &t)
        {
            return t;
        }
    };

    template<>
    struct remove_case<char, true>
    {
        typedef ichar type;
        static ichar call(char ch)
        {
            return ichar(ch);
        }
    };

    template<>
    struct remove_case<char const *, true>
    {
        typedef istr type;
        static istr call(char const *sz)
        {
            return istr(sz);
        }
    };

    template<typename T, std::size_t N>
    struct remove_case<T(&)[N], true>
      : remove_case<char const *, true>
    {};

    template<>
    struct remove_case<char_range, true>
    {
        typedef ichar_range type;
        static ichar_range call(char_range const &rng)
        {
            return ichar_range(rng);
        }
    };

    template<typename Grammar>
    struct case_sensitive
      : Grammar
    {
        case_sensitive();

        template<typename Expr, typename State, typename Visitor>
        struct apply
          : remove_case<
                typename Grammar::template apply<Expr, State, Visitor>::type
              , Visitor::value
            >
        {};

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &state, Visitor &visitor)       
        {
            return apply<Expr, State, Visitor>::call(Grammar::call(expr, state, visitor));
        }
    };

    struct ToySpiritGrammar;

    // Extract the arg from terminals
    struct ToySpiritTerminal
      : proto::or_<
            proto::trans::arg< proto::meta::terminal<char_tag> >
          , case_sensitive< proto::trans::arg< CharLiteral > >
          , case_sensitive< proto::trans::arg< NTBSLiteral > >
          , case_sensitive< 
                proto::trans::arg< proto::trans::arg_c< CharParser, 1 > >   // char_('a')
            >
          , case_sensitive<
                proto::trans::construct<                                    // char_('a','z')
                    char_range
                  , proto::trans::arg< proto::trans::arg_c< CharRangeParser, 1 > >
                  , proto::trans::arg< proto::trans::arg_c< CharRangeParser, 2 > >
                >
            >
        >
    {};

    // sequence rule folds all >>'s together into a list
    // and wraps the result in a composite<> wrapper
    struct ToySpiritSequence
      : composite<
            proto::tag::right_shift
          , proto::trans::reverse_fold_to_list<
                proto::meta::right_shift<ToySpiritGrammar, ToySpiritGrammar>
            >
        >
    {};

    // alternate rule folds all |'s together into a list
    // and wraps the result in a composite<> wrapper
    struct ToySpiritAlternate
      : composite<
            proto::tag::bitwise_or
          , proto::trans::reverse_fold_to_list<
                proto::meta::bitwise_or<ToySpiritGrammar, ToySpiritGrammar>
            >
        >
    {};

    // Directives such as no_case are handled here
    struct ToySpiritDirective
      : no_case_transform< 
            proto::trans::arg<
                proto::meta::unary_expr< tag::no_case, ToySpiritGrammar >
            >
        >
    {};

    // A ToySpiritGrammar is an alternate, a sequence, a directive or a terminal
    struct ToySpiritGrammar
      : proto::or_<
            ToySpiritSequence
          , ToySpiritAlternate
          , ToySpiritDirective
          , ToySpiritTerminal
        >
    {};

    ///////////////////////////////////////////////////////////////////////////////
    /// End ToySpiritGrammar
    ///////////////////////////////////////////////////////////////////////////////

    template<typename Iterator>
    struct parser
    {
        parser(Iterator begin, Iterator end)
          : first(begin), second(end)
        {}

        struct with_reset
        {
            with_reset(parser const &that, Iterator where)
              : that_(that), where_(where)
            {}

            template<typename T>
            bool operator()(T const &t) const
            {
                this->that_.first = this->where_;
                return this->that_(t);
            }
        private:
            parser const &that_;
            Iterator where_;
        };

        template<typename, typename>
        struct result
        {
            typedef bool type;
        };

        template<typename T>
        bool operator()(T const &t, bool success) const
        {
            return success && (*this)(t);
        }

        template<typename List>
        bool operator()(composite<proto::tag::bitwise_or, List> const &alternates) const
        {
            return fusion::any(alternates.elems(), with_reset(*this, this->first));
        }

        template<typename List>
        bool operator()(composite<proto::tag::right_shift, List> const &sequence) const
        {
            return fusion::fold(sequence.elems(), true, *this);
        }

        bool operator()(char_tag ch) const
        {
            if(this->done())
                return false;
            ++this->first;
            return true;
        }

        bool operator()(char ch) const
        {
            if(this->done() || ch != *this->first)
                return false;
            ++this->first;
            return true;
        }

        bool operator()(ichar ich) const
        {
            if(this->done() || !utility::char_icmp(*this->first, ich.lo_, ich.hi_))
                return false;
            ++this->first;
            return true;
        }

        bool operator()(char const *sz) const
        {
            return utility::string_cmp(sz, this->first, this->second);
        }

        bool operator()(istr const &s) const
        {
            return utility::string_icmp(s.str_, this->first, this->second);
        }

        bool operator()(char_range rng) const
        {
            if(this->done() || !utility::in_range(*this->first, rng.first, rng.second))
                return false;
            ++this->first;
            return true;
        }

        bool operator()(ichar_range rng) const
        {
            if(this->done() || !utility::in_irange(*this->first, rng.first, rng.second))
                return false;
            ++this->first;
            return true;
        }

    private:
        bool done() const
        {
            return this->first == this->second;
        }

        mutable Iterator first;
        Iterator second;
    };

    template<typename Rule, typename Iterator>
    typename proto::if_matches< Rule, ToySpiritGrammar, bool >::type
    parse_impl(Rule const &rule, Iterator begin, Iterator end)
    {
        mpl::false_ is_case_sensitive;
        parser<Iterator> parse_fun(begin, end);
        return parse_fun(ToySpiritGrammar::call(rule, 0, is_case_sensitive));
    }

    // 2nd overload provides a short error message for invalid rules
    template<typename Rule, typename Iterator>
    typename proto::if_not_matches< Rule, ToySpiritGrammar, bool >::type
    parse_impl(Rule const &rule, Iterator begin, Iterator end)
    {
        BOOST_MPL_ASSERT((proto::matches<Rule, ToySpiritGrammar>));
        return false;
    }

    // parse() converts rule literals to proto expressions if necessary
    // and dispatches to parse_impl
    template<typename Rule, typename Iterator>
    bool parse(Rule const &rule, Iterator begin, Iterator end)
    {
        return parse_impl(proto::as_expr(rule), begin, end);
    }

}}

using namespace boost;

void test_toy_spirit2()
{
    using spirit2::no_case;
    std::string hello("abcd");

    BOOST_CHECK(
        spirit2::parse(
            "abcd"
          , hello.begin()
          , hello.end()
        )
    );

    BOOST_CHECK(
        spirit2::parse(
            char_ >> char_('b') >> 'c' >> char_
          , hello.begin()
          , hello.end()
        )
    );

    BOOST_CHECK(
       !spirit2::parse(
            char_ >> char_('b') >> 'c' >> 'D'
          , hello.begin()
          , hello.end()
        )
    );

    BOOST_CHECK(
        spirit2::parse(
            char_ >> char_('b') >> 'c' >> 'e'
          | char_ >> no_case[char_('B') >> "C" >> char_('D','Z')]
          , hello.begin()
          , hello.end()
        )
    );
}

using namespace boost::unit_test;
///////////////////////////////////////////////////////////////////////////////
// init_unit_test_suite
//
test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    test_suite *test = BOOST_TEST_SUITE("test proto, grammars and tree transforms");

    test->add(BOOST_TEST_CASE(&test_toy_spirit2));

    return test;
}
