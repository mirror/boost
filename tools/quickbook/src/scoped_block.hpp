/*=============================================================================
    Copyright (c) 2010 Daniel James
    Copyright (c) 2003 Martin Wille
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 =============================================================================*/
 
// Used to parse an inner block, saves the streams and restores them if the
// parse fails. On success the action is passed the resulting block.
//
// Might be a good idea to do something more generic in the future.
//
// This is based on `boost::spirit::classic::scoped_lock` by Martin Wille

#ifndef BOOST_QUICKBOOK_SCOPED_BLOCK_HPP
#define BOOST_QUICKBOOK_SCOPED_BLOCK_HPP

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/composite/composite.hpp>
#include "actions_class.hpp"

namespace quickbook {

    namespace cl = boost::spirit::classic;
    
    struct scoped_block_push
    {
        typedef std::string attribute;

        scoped_block_push(quickbook::actions& actions)
            : actions(actions)
        {
            actions.out.push();
            actions.phrase.push();
        }
        
        ~scoped_block_push()
        {
            actions.phrase.pop();
            actions.out.pop();
        }
        
        std::string const& finish() 
        {
            actions.inside_paragraph();
            return actions.out.str();
        }

        quickbook::actions& actions;
    };

    template <typename ParserT>
    struct scoped_block_parser
        : public cl::unary< ParserT, cl::parser< scoped_block_parser<ParserT> > >
    {
        typedef scoped_block_parser<ParserT> self_t;
        typedef cl::unary< ParserT, cl::parser< scoped_block_parser<ParserT> > > base_t;

        template <typename ScannerT>
        struct result
        {
            typedef cl::match<std::string> type;
        };

        scoped_block_parser(quickbook::actions& a, ParserT const &p)
            : base_t(p)
            , actions(a)
        {}

        template <typename ScannerT>
        cl::match<std::string> parse(ScannerT const &scan) const
        {
            typedef typename ScannerT::iterator_t iterator_t;
            iterator_t save = scan.first;

            scoped_block_push push(actions);
            typename cl::parser_result<ParserT, ScannerT>::type result
                = this->subject().parse(scan);

            if (result)
                return scan.create_match(result.length(), push.finish(), save, scan.first);
            else
                return scan.no_match();
        }
        
        quickbook::actions& actions;
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    // scoped_block_parser_gen
    //
    //      generator for scoped_block_parser objects
    //      operator[] returns scoped_block_parser according to its argument
    //
    ///////////////////////////////////////////////////////////////////////////
    struct scoped_block_parser_gen
    {
        explicit scoped_block_parser_gen(quickbook::actions& actions)
            : actions(actions) {}

        template<typename ParserT>
        scoped_block_parser
        <
            typename cl::as_parser<ParserT>::type
        >
        operator[](ParserT const &p) const
        {
            typedef cl::as_parser<ParserT> as_parser_t;
            typedef typename as_parser_t::type parser_t;

            return scoped_block_parser<parser_t>
                (actions, as_parser_t::convert(p));
        }
        
        quickbook::actions& actions;
    };


    ///////////////////////////////////////////////////////////////////////////
    //
    // scoped_block_d parser directive
    //
    //      constructs a scoped_block_parser generator from its argument
    //
    ///////////////////////////////////////////////////////////////////////////
    inline scoped_block_parser_gen scoped_block(quickbook::actions& actions) {
        return scoped_block_parser_gen(actions);
    }

}
#endif // BOOST_QUICKBOOK_SCOPED_BLOCK_HPP
