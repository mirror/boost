/*=============================================================================
    Copyright (c) 2002 2004 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_QUICKBOOK_PHRASE_HPP)
#define BOOST_SPIRIT_QUICKBOOK_PHRASE_HPP

#include "detail/utils.hpp"
#include <boost/spirit/core.hpp>
#include <boost/spirit/utility/confix.hpp>
#include <boost/spirit/utility/chset.hpp>
#include <boost/spirit/actor/assign_actor.hpp>
#include <boost/spirit/dynamic/if.hpp>

namespace quickbook
{
    using namespace boost::spirit;

    template <typename Rule, typename Action>
    inline void
    simple_markup(Rule& simple, char mark, Action const& action, Rule const& eol)
    {
        simple =
            mark >>
            (
                (
                    graph_p                     // A single char. e.g. *c*
                    >> eps_p(mark
                        >> (space_p | punct_p))
                )
            |   (   graph_p >>                  // graph_p must follow mark
                    *(anychar_p -
                        (   eol                 // Make sure that we don't go
                        |   (graph_p >> mark)   // past a single line
                        )
                    ) >> graph_p                // graph_p must precede mark
                    >> eps_p(mark
                        >> (space_p | punct_p)) // space_p or punct_p must
                )                               // follow mark
            )                                   [action]
            >> mark
            ;
    }
    
    template <typename Actions>
    struct phrase_grammar : grammar<phrase_grammar<Actions> >
    {
        phrase_grammar(Actions& actions, bool& is_not_preformatted)
            : is_not_preformatted(is_not_preformatted), actions(actions) {}

        template <typename Scanner>
        struct definition
        {
            definition(phrase_grammar const& self)
            {
                using detail::var;
                Actions& actions = self.actions;

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
                        actions.macro                   [actions.do_macro]
                    |   phrase_markup
                    |   code_block
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
                    )                                   [actions.inline_code]
                    >>  '`'
                    ;

                code_block =
                    "``" >>
                    (
                       *(anychar_p - "``")
                            >> eps_p("``")
                    )                                   [actions.code_block]
                    >>  "``"
                    ;

                simple_format =
                        simple_bold
                    |   simple_italic
                    |   simple_underline
                    |   simple_teletype
                    ;

                simple_markup(simple_bold, 
                    '*', actions.simple_bold, eol);
                simple_markup(simple_italic, 
                    '/', actions.simple_italic, eol);
                simple_markup(simple_underline, 
                    '_', actions.simple_underline, eol);
                simple_markup(simple_teletype, 
                    '=', actions.simple_teletype, eol);

                phrase =
                   *(   common
                    |   comment
                    |   (anychar_p -
                            close_bracket)              [actions.plain_char]
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
                        |   quote
                        |   replaceable
                        |   footnote
                        |   str_p("br")                 [actions.break_]
                        )
                    >>  ']'
                    ;

                escape =
                        str_p("\\n")                    [actions.break_]
                    |   '\\' >> punct_p                 [actions.raw_char]
                    |   (
                            ("'''" >> !eol)             [actions.escape_pre]
                        >>  *(anychar_p - "'''")        [actions.raw_char]
                        >>  str_p("'''")                [actions.escape_post]
                        )
                    ;

                image =
                        '$' >> blank
                    >> (*(anychar_p -
                            close_bracket))             [actions.image]
                    ;

                url =
                        '@'
                    >>  (*(anychar_p -
                            (']' | hard_space)))        [actions.url_pre]
                    >>  (   eps_p(']')
                        |   (hard_space >> phrase)
                        )                               [actions.url_post]
                    ;

                link =
                        "link" >> hard_space
                    >>  (*(anychar_p -
                            (']' | hard_space)))        [actions.link_pre]
                    >>  (   eps_p(']')
                        |   (hard_space >> phrase)
                        )                               [actions.link_post]
                    ;

                anchor =
                        '#'
                    >>  blank
                    >>  (   *(anychar_p -
                                close_bracket)
                        )                               [actions.anchor]
                    ;

                funcref =
                    "funcref" >> hard_space
                    >>  (*(anychar_p -
                            (']' | hard_space)))        [actions.funcref_pre]
                    >>  (   eps_p(']')
                        |   (hard_space >> phrase)
                        )                               [actions.funcref_post]
                    ;

                classref =
                    "classref" >> hard_space
                    >>  (*(anychar_p -
                            (']' | hard_space)))        [actions.classref_pre]
                    >>  (   eps_p(']')
                        |   (hard_space >> phrase)
                        )                               [actions.classref_post]
                    ;

                memberref =
                    "memberref" >> hard_space
                    >>  (*(anychar_p -
                            (']' | hard_space)))        [actions.memberref_pre]
                    >>  (   eps_p(']')
                        |   (hard_space >> phrase)
                        )                               [actions.memberref_post]
                    ;

                enumref =
                    "enumref" >> hard_space
                    >>  (*(anychar_p -
                            (']' | hard_space)))        [actions.enumref_pre]
                    >>  (   eps_p(']')
                        |   (hard_space >> phrase)
                        )                               [actions.enumref_post]
                    ;

                headerref =
                    "headerref" >> hard_space
                    >>  (*(anychar_p -
                            (']' | hard_space)))        [actions.headerref_pre]
                    >>  (   eps_p(']')
                        |   (hard_space >> phrase)
                        )                               [actions.headerref_post]
                    ;

                bold =
                        ch_p('*')                       [actions.bold_pre]
                    >>  blank >> phrase                 [actions.bold_post]
                    ;

                italic =
                        ch_p('\'')                      [actions.italic_pre]
                    >>  blank >> phrase                 [actions.italic_post]
                    ;

                underline =
                        ch_p('_')                       [actions.underline_pre]
                    >>  blank >> phrase                 [actions.underline_post]
                    ;

                teletype =
                        ch_p('^')                       [actions.teletype_pre]
                    >>  blank >> phrase                 [actions.teletype_post]
                    ;

                strikethrough =
                        ch_p('-')                       [actions.strikethrough_pre]
                    >>  blank >> phrase                 [actions.strikethrough_post]
                    ;
                
                quote =
                        ch_p('"')                       [actions.quote_pre]
                    >>  blank >> phrase                 [actions.quote_post]
                    ;

                replaceable =
                        ch_p('~')                       [actions.replaceable_pre]
                    >>  blank >> phrase                 [actions.replaceable_post]
                    ;

                source_mode =
                    (
                        str_p("c++")
                    |   "python"
                    )                                   [assign_a(actions.source_mode)]
                    ;

                footnote =
                        str_p("footnote")               [actions.footnote_pre]
                    >>  blank >> phrase                 [actions.footnote_post]
                    ;
            }
            
            rule<Scanner>   space, blank, comment, phrase, phrase_markup, image, 
                            close_bracket, bold, italic, underline, teletype, 
                            strikethrough, escape, url, common, funcref, 
                            classref, memberref, enumref, headerref, anchor, 
                            link, hard_space, eol, inline_code, simple_format, 
                            simple_bold, simple_italic, simple_underline, 
                            simple_teletype, source_mode, 
                            quote, code_block, footnote, replaceable;

            rule<Scanner> const&
            start() const { return common; }
        };

        bool& is_not_preformatted;
        Actions& actions;
    };
}

#endif // BOOST_SPIRIT_QUICKBOOK_PHRASE_HPP

