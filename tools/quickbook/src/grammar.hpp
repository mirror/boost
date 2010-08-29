/*=============================================================================
    Copyright (c) 2002 2004  2006Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_QUICKBOOK_GRAMMARS_HPP)
#define BOOST_SPIRIT_QUICKBOOK_GRAMMARS_HPP

#include <boost/spirit/include/classic_core.hpp>
#include "actions.hpp"

namespace quickbook
{
    namespace cl = boost::spirit::classic;

    struct doc_info_grammar
    : public cl::grammar<doc_info_grammar>
    {
        doc_info_grammar(quickbook::actions& actions)
            : actions(actions) {}

        template <typename Scanner>
        struct definition;

        quickbook::actions& actions;
    };

    struct block_grammar : cl::grammar<block_grammar>
    {
        block_grammar(quickbook::actions& actions_, bool skip_initial_spaces = false)
            : actions(actions_), skip_initial_spaces(skip_initial_spaces) { }

        template <typename Scanner>
        struct definition;

        quickbook::actions& actions;
        bool const skip_initial_spaces;
    };

    struct phrase_grammar
        : cl::grammar<phrase_grammar>
    {
        phrase_grammar(quickbook::actions& actions, bool& no_eols)
            : no_eols(no_eols), actions(actions) {}

        template <typename Scanner>
        struct definition;

        bool& no_eols;
        quickbook::actions& actions;
    };

    struct simple_phrase_grammar
        : public cl::grammar<simple_phrase_grammar >
    {
        simple_phrase_grammar(quickbook::actions& actions)
            : actions(actions) {}

        template <typename Scanner>
        struct definition;

        quickbook::actions& actions;
    };

    struct command_line_grammar
        : public cl::grammar<command_line_grammar>
    {
        command_line_grammar(quickbook::actions& actions)
            : actions(actions) {}

        template <typename Scanner>
        struct definition;

        quickbook::actions& actions;
    };

    cl::parse_info<iterator> call_parse(
        iterator&, iterator, doc_info_grammar&);
    cl::parse_info<iterator> call_parse(
        iterator&, iterator, block_grammar&);
    cl::parse_info<iterator> call_parse(
        iterator&, iterator, phrase_grammar&);
    cl::parse_info<iterator> call_parse(
        iterator&, iterator, simple_phrase_grammar&);
    cl::parse_info<iterator> call_parse(
        iterator&, iterator, command_line_grammar&);
}

#endif
