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
        rule_store store_;

        // Main Grammar
        cl::rule<scanner> block_start;
        cl::rule<scanner> block_skip_initial_spaces;
        cl::rule<scanner> common;
        cl::rule<scanner> simple_phrase;
        cl::rule<scanner> phrase;
        cl::rule<scanner> extended_phrase;
        cl::rule<scanner> inside_paragraph;
        cl::rule<scanner> command_line;

        // Miscellaneous stuff
        cl::rule<scanner> hard_space;
        cl::rule<scanner> space;
        cl::rule<scanner> blank;
        cl::rule<scanner> eol;
        cl::rule<scanner> phrase_end;
        cl::rule<scanner> comment;
        cl::rule<scanner> macro_identifier;

        // Markup Symbols
        cl::symbols<cl::rule<scanner>*> phrase_keyword_rules;
        cl::symbols<cl::rule<scanner>*> phrase_symbol_rules;

        cl::symbols<cl::rule<scanner>*> block_keyword_rules;
        cl::symbols<cl::rule<scanner>*> block_symbol_rules;
        
        cl::symbols<cl::rule<scanner>*> extended_phrase_keyword_rules;
        
        // Doc Info
        cl::rule<scanner> doc_info_details;
        
        impl(quickbook::actions&);

    private:

        void init_main();
        void init_block_elements();
        void init_phrase_elements();
        void init_doc_info();
    };
}

#endif // BOOST_SPIRIT_QUICKBOOK_GRAMMARS_HPP
