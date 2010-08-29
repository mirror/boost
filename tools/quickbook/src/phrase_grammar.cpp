/*=============================================================================
    Copyright (c) 2002 2004 2006 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include "phrase_grammar.hpp"

namespace quickbook
{
    template <typename Scanner>
    struct simple_phrase_grammar::definition
    {
        definition(simple_phrase_grammar const& self)
            : unused(false), common(self.actions, unused)
        {
            quickbook::actions& actions = self.actions;

            phrase =
               *(   common
                |   comment
                |   (anychar_p - ']')           [actions.plain_char]
                )
                ;

            comment =
                "[/" >> *(dummy_block | (anychar_p - ']')) >> ']'
                ;

            dummy_block =
                '[' >> *(dummy_block | (anychar_p - ']')) >> ']'
                ;
        }

        bool unused;
        rule<Scanner> phrase, comment, dummy_block;
        phrase_grammar common;

        rule<Scanner> const&
        start() const { return phrase; }
    };

    template <typename Scanner>
    struct command_line_grammar::definition
    {
        definition(command_line_grammar const& self)
            : unused(false), common(self.actions, unused)
        {
            quickbook::actions& actions = self.actions;

            macro =
                    *space_p
                >>  macro_identifier            [actions.macro_identifier]
                >>  *space_p
                >>  (   '='
                    >>  *space_p
                    >>  phrase                  [actions.macro_definition]
                    >>  *space_p
                    )
                |   eps_p                       [actions.macro_definition]
                ;

            macro_identifier =
                +(anychar_p - (space_p | ']' | '='))
                ;

            phrase =
               *(   common
                |   (anychar_p - ']')           [actions.plain_char]
                )
                ;
        }

        bool unused;
        rule<Scanner> macro, macro_identifier, phrase;
        phrase_grammar common;

        rule<Scanner> const&
        start() const { return macro; }
    };

    parse_info<iterator> call_parse(
        iterator& first, iterator last, phrase_grammar& g)
    {
        return boost::spirit::classic::parse(first, last, g);
    }

    parse_info<iterator> call_parse(
        iterator& first, iterator last, simple_phrase_grammar& g)
    {
        return boost::spirit::classic::parse(first, last, g);
    }

    parse_info<iterator> call_parse(
        iterator& first, iterator last, command_line_grammar& g)
    {
        return boost::spirit::classic::parse(first, last, g);
    }
}
