/*=============================================================================
    Copyright (c) 2002 2004 2006 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    Copyright (c) 2010 Daniel James
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_QUICKBOOK_GRAMMARS_IMPL_HPP)
#define BOOST_SPIRIT_QUICKBOOK_GRAMMARS_IMPL_HPP

#include "grammar.hpp"
#include "rule_store.hpp"
#include <boost/spirit/include/classic_symbols.hpp>

namespace quickbook
{
    namespace cl = boost::spirit::classic;

    struct quickbook_grammar::impl
    {
        quickbook::actions& actions;
        bool no_eols;
        rule_store store_;

        // phrase
        cl::rule<scanner> common;
        cl::rule<scanner> simple_phrase;
        cl::rule<scanner> phrase;
        cl::rule<scanner> command_line;
        cl::symbols<cl::rule<scanner>*> phrase_keyword_rules;
        cl::symbols<cl::rule<scanner>*> phrase_symbol_rules;

        // block
        cl::rule<scanner> block_start;
        cl::rule<scanner> block_skip_initial_spaces;
        cl::symbols<cl::rule<scanner>*> block_keyword_rules;
        cl::symbols<cl::rule<scanner>*> block_symbol_rules;
        
        // doc_info
        cl::rule<scanner> doc_info_details;
        
        impl(quickbook::actions&);

    private:

        void init_main();
        void init_block_markup();
        void init_phrase_markup();
        void init_doc_info();
    };
}

#endif // BOOST_SPIRIT_QUICKBOOK_GRAMMARS_HPP
