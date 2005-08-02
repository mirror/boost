/*=============================================================================
    Copyright (c) 2002 2004 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_QUICKBOOK_HPP)
#define BOOST_SPIRIT_QUICKBOOK_HPP

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
    struct quickbook_grammar
    : public grammar<quickbook_grammar<Actions> >
    {
        quickbook_grammar(Actions& actions_)
        : actions(actions_) {}

        template <typename Scanner>
        struct definition
        {
            definition(quickbook_grammar const& self)
                : is_not_preformatted(true)
            {
                using detail::var;

                library =
                    *(space_p | comment) >> blocks >> blank
                    ;

                blocks =
                   +(   block_markup
                    |   code
                    |   list                            [self.actions.list]
                    |   hr                              [self.actions.hr]
                    |   comment >> *eol
                    |   paragraph                       [self.actions.paragraph]
                    |   eol
                    )
                    ;

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
                    if_p(var(is_not_preformatted))
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

                hr =
                    str_p("----")
                    >> *(anychar_p - eol)
                    >> +eol
                    ;

                block_markup =
                        '['
                    >>  (   begin_section
                        |   end_section
                        |   headings
                        |   blurb
                        |   blockquote
                        |   preformatted
                        |   def_macro
                        |   table
                        |   variablelist
                        |   xinclude
                        |   include
                        )
                    >>  (   (']' >> +eol)
                        |   eps_p                       [self.actions.error]
                        )
                    ;

                begin_section =
                       "section"
                    >> hard_space
                    >>  (':' >> (*(alnum_p | '_'))      [assign_a(self.actions.section_id)]
                        | eps_p                         [assign_a(self.actions.section_id)]
                        )
                    >> (*(anychar_p -
                            close_bracket))             [self.actions.begin_section]
                    ;

                end_section =
                    str_p("endsect")                    [self.actions.end_section]
                    ;

                headings =
                    h1 | h2 | h3 | h4 | h5 | h6
                    ;

                h1 = "h1" >> hard_space >> phrase       [self.actions.h1];
                h2 = "h2" >> hard_space >> phrase       [self.actions.h2];
                h3 = "h3" >> hard_space >> phrase       [self.actions.h3];
                h4 = "h4" >> hard_space >> phrase       [self.actions.h4];
                h5 = "h5" >> hard_space >> phrase       [self.actions.h5];
                h6 = "h6" >> hard_space >> phrase       [self.actions.h6];

                blurb =
                    "blurb" >> hard_space
                    >> phrase                           [self.actions.blurb]
                    ;

                blockquote =
                    ':' >> blank >>
                    phrase                              [self.actions.blockquote]
                    ;

                preformatted =
                    "pre" >> hard_space                 [assign_a(is_not_preformatted, false)]
                    >> !eol >> phrase                   [self.actions.preformatted]
                    >> eps_p                            [assign_a(is_not_preformatted, true)]
                    ;

                def_macro =
                    "def" >> hard_space
                    >> identifier                       [self.actions.identifier]
                    >> blank >> phrase                  [self.actions.macro_def]
                    ;

                variablelist =
                    "variablelist" >> hard_space
                    >>  (*(anychar_p - eol))            [assign_a(self.actions.table_title)]
                    >>  +eol
                    >>  *varlistentry
                    >>  eps_p                           [self.actions.variablelist]
                    ;

                varlistentry =
                    space
                    >>  ch_p('[')                       [self.actions.start_varlistentry]
                    >>
                    (
                        (
                            varlistterm
                            >> +varlistitem
                            >>  ch_p(']')               [self.actions.end_varlistentry]
                            >>  space
                        )
                        | eps_p                         [self.actions.error]
                    )
                    ;

                varlistterm =
                    space
                    >>  ch_p('[')                       [self.actions.start_varlistterm]
                    >>
                    (
                        (
                            phrase
                            >>  ch_p(']')               [self.actions.end_varlistterm]
                            >>  space
                        )
                        | eps_p                         [self.actions.error]
                    )
                    ;

                varlistitem =
                    space
                    >>  ch_p('[')                       [self.actions.start_varlistitem]
                    >>
                    (
                        (
                            phrase                      [self.actions.end_varlistitem]
                            >>  ch_p(']')
                            >>  space
                        )
                        | eps_p                         [self.actions.error]
                    )
                    ;

                table =
                    "table" >> hard_space
                    >>  (*(anychar_p - eol))            [assign_a(self.actions.table_title)]
                    >>  +eol
                    >>  *table_row
                    >>  eps_p                           [self.actions.table]
                    ;

                table_row =
                    space
                    >>  ch_p('[')                       [self.actions.start_row]
                    >>
                    (
                        (
                            *table_cell
                            >>  ch_p(']')               [self.actions.end_row]
                            >>  space
                        )
                        | eps_p                         [self.actions.error]
                    )
                    ;

                table_cell =
                    space
                    >>  ch_p('[')                       [self.actions.start_cell]
                    >>
                    (
                        (
                            phrase
                            >>  ch_p(']')               [self.actions.end_cell]
                            >>  space
                        )
                        | eps_p                         [self.actions.error]
                    )
                    ;

                xinclude =
                       "xinclude"
                    >> hard_space
                    >> (*(anychar_p -
                            close_bracket))             [self.actions.xinclude]
                    ;

                include =
                       "include"
                    >> hard_space
                    >> 
                   !(
                        ':'
                        >> (*((alnum_p | '_') - space_p))[assign_a(self.actions.include_doc_id)]
                        >> space
                    )
                    >> (*(anychar_p -
                            close_bracket))             [self.actions.include]
                    ;

                identifier =
                    +(anychar_p - (space_p | ']'))
                    ;

                source_mode =
                    (
                        str_p("c++")
                    |   "python"
                    )                                   [assign_a(self.actions.source_mode)]
                    ;
                
                code =
                    (
                        code_line
                        >> *(*eol >> code_line)
                    )                                   [self.actions.code]
                    >> +eol
                    ;

                code_line =
                    ((ch_p(' ') | '\t'))
                    >> *(anychar_p - eol) >> eol
                    ;

                list =
                    eps_p(ch_p('*') | '#') >>
                   +(
                        (*blank_p
                        >> (ch_p('*') | '#'))           [self.actions.list_format]
                        >> *blank_p
                        >> list_item
                    )                                   [self.actions.list_item]
                    ;

                list_item =
                   *(   common
                    |   (anychar_p -
                            (   eol_p >> *blank_p >> eps_p(ch_p('*') | '#')
                            |   (eol >> eol)
                            )
                        )                               [self.actions.plain_char]
                    )
                    >> +eol
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

                paragraph =
                   *(   common
                    |   (anychar_p -                    // Make sure we don't go past
                            (eol >> eol)                // a single block.
                        )                               [self.actions.plain_char]
                    )
                    >> +eol
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
            }

            bool is_not_preformatted;
            
            rule<Scanner>   library, blocks, lib_info, block_markup, source_mode, code,
                            code_line, paragraph, space, blank, comment, headings,
                            h1, h2, h3, h4, h5, h6, hr, blurb, blockquote,
                            phrase, phrase_markup, image, list, close_bracket,
                            ordered_list, bold, italic, underline, teletype, strikethrough,
                            escape, def_macro, identifier, url, table, table_row,
                            variablelist, varlistentry, varlistterm, varlistitem,
                            table_cell, preformatted, list_item, common,
                            funcref, classref, memberref, enumref, headerref, anchor, link,
                            begin_section, end_section, xinclude, include, hard_space, eol,
                            inline_code, simple_format, simple_bold, simple_italic,
                            simple_underline, simple_teletype, simple_strikethrough;

            rule<Scanner> const&
            start() const { return library; }
        };

        Actions&   actions;
    };
}

#endif // BOOST_SPIRIT_QUICKBOOK_HPP

