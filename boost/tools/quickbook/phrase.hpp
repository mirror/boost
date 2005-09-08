/*=============================================================================
    Copyright (c) 2002 2004 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_PHRASE_HPP)
#define BOOST_SPIRIT_PHRASE_HPP

#include "detail/utils.hpp"
#include <boost/spirit/core.hpp>
#include <boost/spirit/utility/confix.hpp>
#include <boost/spirit/utility/chset.hpp>
#include <boost/spirit/actor/assign_actor.hpp>
#include <boost/spirit/dynamic/if.hpp>

namespace quickbook
{
    using namespace boost::spirit;

    template <typename Actions>
    struct phrase_grammar : grammar<phrase_grammar<Actions> >
    {
        phrase_grammar(Actions& actions, bool& is_not_preformatted)
        : actions(actions), is_not_preformatted(is_not_preformatted) {}

        template <typename Scanner>
        struct definition
        {
            definition(phrase_grammar const& self)
            {
                using detail::var;

                space =
                    *(space_p | comment)
                    ;

                blank =
                    *(blank_p | comment)
                    ;

                eol = blank >> eol_p
                    ;

                close_bracket =
                    ']' |
                    if_p(var(self.is_not_preformatted))
                    [
                        eol_p >> eol_p                  // Make sure that we don't go
                    ]                                   // past a single block, except
                    ;                                   // when preformatted.

                hard_space =
                    (eps_p - (alnum_p | '_')) >> space  // must not be followed by
                    ;                                   // alpha-numeric or underscore

                comment =
                    "[/" >> *(anychar_p - ']') >> ']'
                    ;

                common =
                        self.actions.macro              [self.actions.do_macro]
                    |   phrase_markup
                    |   inline_code
                    |   simple_format
                    |   escape
                    |   comment
                    ;

                inline_code =
                    '`' >>
                    (
                       *(anychar_p -
                            (   '`'
                            |   (eol >> eol)            // Make sure that we don't go
                            )                           // past a single block
                        ) >> eps_p('`')
                    )                                   [self.actions.inline_code]
                    >>  '`'
                    ;

                simple_format =
                        simple_bold
                    |   simple_italic
                    |   simple_underline
                    |   simple_teletype
                    |   simple_strikethrough
                    ;

                simple_bold =
                    '*' >>
                    (
                        (   graph_p >>                  // graph_p must follow '*'
                            *(anychar_p -
                                (   eol                 // Make sure that we don't go
                                |   (graph_p >> '*')    // past a single line
                                )
                            ) >> graph_p                // graph_p must precede '*'
                            >> eps_p('*'
                                >> (space_p | punct_p)) // space_p or punct_p must
                        )                               // follow '*'
                    |   (
                            graph_p                     // A single char. e.g. *c*
                            >> eps_p('*'
                                >> (space_p | punct_p))
                        )
                    )                                   [self.actions.simple_bold]
                    >> '*'
                    ;

                simple_italic =
                    '/' >>
                    (
                        (   graph_p >>                  // graph_p must follow '/'
                            *(anychar_p -
                                (   eol                 // Make sure that we don't go
                                |   (graph_p >> '/')    // past a single line
                                )
                            ) >> graph_p                // graph_p must precede '/'
                            >> eps_p('/'
                                >> (space_p | punct_p)) // space_p or punct_p must
                        )                               // follow '/'
                    |   (
                            graph_p                     // A single char. e.g. /c/
                            >> eps_p('/'
                                >> (space_p | punct_p))
                        )
                    )                                   [self.actions.simple_italic]
                    >> '/'
                    ;

                simple_underline =
                    '_' >>
                    (
                        (   graph_p >>                  // graph_p must follow '_'
                            *(anychar_p -
                                (   eol                 // Make sure that we don't go
                                |   (graph_p >> '_')    // past a single line
                                )
                            ) >> graph_p                // graph_p must precede '_'
                            >> eps_p('_'
                                >> (space_p | punct_p)) // space_p or punct_p must
                        )                               // follow '_'
                    |   (
                            graph_p                     // A single char. e.g. _c_
                            >> eps_p('_'
                                >> (space_p | punct_p))
                        )
                    )                                   [self.actions.simple_underline]
                    >> '_'
                    ;

                simple_teletype =
                    '=' >>
                    (
                        (   graph_p >>                  // graph_p must follow '='
                            *(anychar_p -
                                (   eol                 // Make sure that we don't go
                                |   (graph_p >> '=')    // past a single line
                                )
                            ) >> graph_p                // graph_p must precede '='
                            >> eps_p('='
                                >> (space_p | punct_p)) // space_p or punct_p must
                        )                               // follow '='
                    |   (
                            graph_p                     // A single char. e.g. =c=
                            >> eps_p('='
                                >> (space_p | punct_p))
                        )
                    )                                   [self.actions.simple_teletype]
                    >> '='
                    ;

                simple_strikethrough =
                    '-' >>
                    (
                        (   graph_p >>                  // graph_p must follow '-'
                            *(anychar_p -
                                (   eol                 // Make sure that we don't go
                                |   (graph_p >> '-')    // past a single line
                                )
                            ) >> graph_p                // graph_p must precede '-'
                            >> eps_p('-'
                                >> (space_p | punct_p)) // space_p or punct_p must
                        )                               // follow '-'
                    |   (
                            graph_p                     // A single char. e.g. =c=
                            >> eps_p('-'
                                >> (space_p | punct_p))
                        )
                    )                                   [self.actions.simple_strikethrough]
                    >> '-'
                    ;

                phrase =
                   *(   common
                    |   comment
                    |   (anychar_p -
                            close_bracket)              [self.actions.plain_char]
                    )
                    ;

                phrase_markup =
                        '['
                    >>  (   image
                        |   url
                        |   link
                        |   anchor
                        |   source_mode    
                        |   funcref
                        |   classref
                        |   memberref
                        |   enumref
                        |   headerref
                        |   bold
                        |   italic
                        |   underline
                        |   teletype
                        |   strikethrough
                        |   str_p("br")                 [self.actions.break_]
                        )
                    >>  ']'
                    ;

                escape =
                        str_p("\\n")                    [self.actions.break_]
                    |   '\\' >> punct_p                 [self.actions.raw_char]
                    |   (
                            "'''" >> !eol
                        >>  *(anychar_p - "'''")        [self.actions.raw_char]
                        >>  "'''"
                        )
                    ;

                image =
                        '$' >> blank
                    >> (*(anychar_p -
                            close_bracket))             [self.actions.image]
                    ;

                url =
                        '@'
                    >>  (*(anychar_p -
                            (']' | hard_space)))        [self.actions.url_pre]
                    >>  (   eps_p(']')
                        |   (hard_space >> phrase)
                        )                               [self.actions.url_post]
                    ;

                link =
                        "link" >> hard_space
                    >>  (*(anychar_p -
                            (']' | hard_space)))        [self.actions.link_pre]
                    >>  (   eps_p(']')
                        |   (hard_space >> phrase)
                        )                               [self.actions.link_post]
                    ;

                anchor =
                        '#'
                    >>  blank
                    >>  (   *(anychar_p -
                                close_bracket)
                        )                               [self.actions.anchor]
                    ;

                funcref =
                    "funcref" >> hard_space
                    >>  (*(anychar_p -
                            (']' | hard_space)))        [self.actions.funcref_pre]
                    >>  (   eps_p(']')
                        |   (hard_space >> phrase)
                        )                               [self.actions.funcref_post]
                    ;

                classref =
                    "classref" >> hard_space
                    >>  (*(anychar_p -
                            (']' | hard_space)))        [self.actions.classref_pre]
                    >>  (   eps_p(']')
                        |   (hard_space >> phrase)
                        )                               [self.actions.classref_post]
                    ;

                memberref =
                    "memberref" >> hard_space
                    >>  (*(anychar_p -
                            (']' | hard_space)))        [self.actions.memberref_pre]
                    >>  (   eps_p(']')
                        |   (hard_space >> phrase)
                        )                               [self.actions.memberref_post]
                    ;

                enumref =
                    "enumref" >> hard_space
                    >>  (*(anychar_p -
                            (']' | hard_space)))        [self.actions.enumref_pre]
                    >>  (   eps_p(']')
                        |   (hard_space >> phrase)
                        )                               [self.actions.enumref_post]
                    ;

                headerref =
                    "headerref" >> hard_space
                    >>  (*(anychar_p -
                            (']' | hard_space)))        [self.actions.headerref_pre]
                    >>  (   eps_p(']')
                        |   (hard_space >> phrase)
                        )                               [self.actions.headerref_post]
                    ;

                bold =
                        ch_p('*')                       [self.actions.bold_pre]
                    >>  blank >> phrase                 [self.actions.bold_post]
                    ;

                italic =
                        ch_p('\'')                      [self.actions.italic_pre]
                    >>  blank >> phrase                 [self.actions.italic_post]
                    ;

                underline =
                        ch_p('_')                       [self.actions.underline_pre]
                    >>  blank >> phrase                 [self.actions.underline_post]
                    ;

                teletype =
                        ch_p('^')                       [self.actions.teletype_pre]
                    >>  blank >> phrase                 [self.actions.teletype_post]
                    ;

                strikethrough =
                        ch_p('-')                       [self.actions.strikethrough_pre]
                    >>  blank >> phrase                 [self.actions.strikethrough_post]
                    ;

                source_mode =
                    (
                        str_p("c++")
                    |   "python"
                    )                                   [assign_a(self.actions.source_mode)]
                    ;
            }
            
            rule<Scanner>   space, blank, comment, phrase, phrase_markup, image, 
                            close_bracket, bold, italic, underline, teletype, 
                            strikethrough, escape, url, common, funcref, 
                            classref, memberref, enumref, headerref, anchor, 
                            link, hard_space, eol, inline_code, simple_format, 
                            simple_bold, simple_italic, simple_underline, 
                            simple_teletype, simple_strikethrough, source_mode;

            rule<Scanner> const&
            start() const { return common; }
        };

        bool& is_not_preformatted;
        Actions& actions;
    };
}

#endif // BOOST_SPIRIT_PHRASE_HPP

