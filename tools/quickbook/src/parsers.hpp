/*=============================================================================
    Copyright (c) 2010-2011 Daniel James
    Copyright (c) 2003 Martin Wille
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/

// Some custom parsers for use in quickbook.
 
#ifndef BOOST_QUICKBOOK_PARSERS_HPP
#define BOOST_QUICKBOOK_PARSERS_HPP

#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_nil.hpp>

namespace quickbook {
    namespace cl = boost::spirit::classic;
    
    // Used to store variables/state while parsing 

    template <typename ScopeT, typename DataT, typename ParserT>
    struct scoped_parser_impl
        : public cl::unary< ParserT, cl::parser< scoped_parser_impl<ScopeT, DataT, ParserT> > >
    {
        typedef scoped_parser_impl<ScopeT, DataT, ParserT> self_t;
        typedef cl::unary< ParserT, cl::parser< scoped_parser_impl<ScopeT, DataT, ParserT> > > base_t;

        template <typename ScannerT>
        struct result { typedef cl::match<> type; };

        scoped_parser_impl(DataT& actions, ParserT const &p)
            : base_t(p)
            , actions(actions)
        {}

        template <typename ScannerT>
        typename result<ScannerT>::type parse(ScannerT const &scan) const
        {
            typedef typename ScannerT::iterator_t iterator_t;
            iterator_t save = scan.first;

            ScopeT scope(actions);
            typename cl::parser_result<ParserT, ScannerT>::type result
                = this->subject().parse(scan);

            if (result) {
                scope.success(result);
                return scan.create_match(result.length(), cl::nil_t(), save, scan.first);
            }
            else {
                scope.failure();
                return scan.no_match();
            }
        }
        
        DataT& actions;
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    // scoped_parser
    //
    //      generator for scoped_parser_impl objects
    //      operator[] returns scoped_parser_impl according to its argument
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename ScopeT>
    struct scoped_parser
    {
        typedef typename ScopeT::data_type data_type;
    
        explicit scoped_parser(data_type& actions)
            : actions(actions) {}

        template<typename ParserT>
        scoped_parser_impl
        <
            ScopeT,
            data_type,
            typename cl::as_parser<ParserT>::type
        >
        operator[](ParserT const &p) const
        {
            typedef cl::as_parser<ParserT> as_parser_t;
            typedef typename as_parser_t::type parser_t;

            return scoped_parser_impl<ScopeT, data_type, parser_t>
                (actions, as_parser_t::convert(p));
        }
        
        data_type& actions;
    };
    
    // Lookback parser
    //
    // Requires that iterator has typedef 'lookback_range' and function
    // 'lookback' returning a 'lookback_range'.

    template <typename ParserT>
    struct lookback_parser
        : public cl::unary< ParserT, cl::parser< lookback_parser<ParserT> > >
    {
        typedef lookback_parser<ParserT> self_t;
        typedef cl::unary< ParserT, cl::parser< lookback_parser<ParserT> > > base_t;

        template <typename ScannerT>
        struct result
        {
            typedef typename cl::parser_result<ParserT, ScannerT>::type type;
        };

        lookback_parser(ParserT const& p)
            : base_t(p)
        {}

        template <typename ScannerT>
        typename result<ScannerT>::type parse(ScannerT const &scan) const
        {
            typedef typename ScannerT::iterator_t::lookback_range::iterator iterator_t;
            typedef cl::scanner<iterator_t, typename ScannerT::policies_t> scanner_t;

            iterator_t begin = scan.first.lookback().begin();
            scanner_t lookback_scan(begin, scan.first.lookback().end(), scan);
            
            if (this->subject().parse(lookback_scan))
                return scan.empty_match();
            else
                return scan.no_match();
        }
    };
    
    struct lookback_gen
    {
        template <typename ParserT>
        lookback_parser<ParserT> operator[](ParserT const& p) const
        {
            return lookback_parser<ParserT>(p);
        }
    };
    
    lookback_gen const lookback = lookback_gen();
}
#endif // BOOST_QUICKBOOK_SCOPED_BLOCK_HPP
