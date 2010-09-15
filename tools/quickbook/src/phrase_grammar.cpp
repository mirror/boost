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
                |   (cl::anychar_p - ']')       [actions.plain_char]
                )
                ;

            comment =
                "[/" >> *(dummy_block | (cl::anychar_p - ']')) >> ']'
                ;

            dummy_block =
                '[' >> *(dummy_block | (cl::anychar_p - ']')) >> ']'
                ;
        }

        bool unused;
        cl::rule<Scanner> phrase, comment, dummy_block;
        phrase_grammar common;

        cl::rule<Scanner> const&
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
                    *cl::space_p
                >>  macro_identifier            [actions.macro_identifier]
                >>  *cl::space_p
                >>  (   '='
                    >>  *cl::space_p
                    >>  phrase                  [actions.macro_definition]
                    >>  *cl::space_p
                    )
                |   cl::eps_p                   [actions.macro_definition]
                ;

            macro_identifier =
                +(cl::anychar_p - (cl::space_p | ']' | '='))
                ;

            phrase =
               *(   common
                |   (cl::anychar_p - ']')       [actions.plain_char]
                )
                ;
        }

        bool unused;
        cl::rule<Scanner> macro, macro_identifier, phrase;
        phrase_grammar common;

        cl::rule<Scanner> const&
        start() const { return macro; }
    };

    cl::parse_info<iterator> call_parse(
        iterator& first, iterator last, phrase_grammar& g)
    {
        return boost::spirit::classic::parse(first, last, g);
    }

    cl::parse_info<iterator> call_parse(
        iterator& first, iterator last, simple_phrase_grammar& g)
    {
        return boost::spirit::classic::parse(first, last, g);
    }

    cl::parse_info<iterator> call_parse(
        iterator& first, iterator last, command_line_grammar& g)
    {
        return boost::spirit::classic::parse(first, last, g);
    }
}
