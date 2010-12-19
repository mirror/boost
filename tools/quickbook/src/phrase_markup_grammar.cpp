/*=============================================================================
    Copyright (c) 2002 2004 2006 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include "grammar_impl.hpp"
#include "actions_class.hpp"
#include "utils.hpp"
#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_assign_actor.hpp>
#include <boost/spirit/include/classic_clear_actor.hpp>
#include <boost/spirit/include/classic_if.hpp>

namespace quickbook
{
    namespace cl = boost::spirit::classic;

    struct phrase_markup_grammar_local
    {
        cl::rule<scanner>
                        space, blank, comment, image,
                        phrase_end, bold, italic, underline, teletype,
                        strikethrough, url, funcref, classref,
                        memberref, enumref, macroref, headerref, conceptref, globalref,
                        anchor, link, hard_space, eol,
                        source_mode_cpp, source_mode_python, source_mode_teletype,
                        quote, footnote, replaceable,
                        dummy_block, cond_phrase, macro_identifier
                        ;
    };

    void quickbook_grammar::impl::init_phrase_markup()
    {
        using detail::var;

        phrase_markup_grammar_local& local = store_.create();

        local.space =
            *(cl::space_p | local.comment)
            ;

        local.blank =
            *(cl::blank_p | local.comment)
            ;

        local.eol = local.blank >> cl::eol_p
            ;

        local.phrase_end =
            ']' |
            cl::if_p(var(no_eols))
            [
                cl::eol_p >> *cl::blank_p >> cl::eol_p
                                                // Make sure that we don't go
            ]                                   // past a single block, except
            ;                                   // when preformatted.

        // Follows an alphanumeric identifier - ensures that it doesn't
        // match an empty space in the middle of the identifier.
        local.hard_space =
            (cl::eps_p - (cl::alnum_p | '_')) >> local.space
            ;

        local.comment =
            "[/" >> *(local.dummy_block | (cl::anychar_p - ']')) >> ']'
            ;

        local.dummy_block =
            '[' >> *(local.dummy_block | (cl::anychar_p - ']')) >> ']'
            ;

        local.macro_identifier =
            +(cl::anychar_p - (cl::space_p | ']'))
            ;

        phrase_symbol_rules.add
            ("?", &local.cond_phrase)
            ;

        local.cond_phrase =
                local.blank
            >>  local.macro_identifier          [actions.cond_phrase_pre]
            >>  (!phrase)                       [actions.cond_phrase_post]
            ;

        phrase_symbol_rules.add
            ("$", &local.image)
            ;

        local.image =
                local.blank                     [cl::clear_a(actions.attributes)]
            >>  cl::if_p(qbk_since(105u)) [
                        (+(
                            *cl::space_p
                        >>  +(cl::anychar_p - (cl::space_p | local.phrase_end | '['))
                        ))                       [cl::assign_a(actions.image_fileref)]
                    >>  local.hard_space
                    >>  *(
                            '['
                        >>  (*(cl::alnum_p | '_'))  [cl::assign_a(actions.attribute_name)]
                        >>  local.space
                        >>  (*(cl::anychar_p - (local.phrase_end | '[')))
                                                [actions.attribute]
                        >>  ']'
                        >>  local.space
                        )
                ].else_p [
                        (*(cl::anychar_p - local.phrase_end))
                                                [cl::assign_a(actions.image_fileref)]
                ]
            >>  cl::eps_p(']')                  [actions.image]
            ;
            
        phrase_symbol_rules.add
            ("@", &local.url)
            ;

        local.url =
                (*(cl::anychar_p -
                    (']' | local.hard_space)))  [actions.url_pre]
            >>  local.hard_space
            >>  phrase                          [actions.url_post]
            ;

        phrase_keyword_rules.add
            ("link", &local.link)
            ;

        local.link =
                local.space
            >>  (*(cl::anychar_p - (']' | local.hard_space)))
                                                [actions.link_pre]
            >>  local.hard_space
            >>  phrase                          [actions.link_post]
            ;

        phrase_symbol_rules.add
            ("#", &local.anchor)
            ;

        local.anchor =
                local.blank
            >>  (*(cl::anychar_p - local.phrase_end)) [actions.anchor]
            ;

        phrase_keyword_rules.add
            ("funcref", &local.funcref)
            ("classref", &local.classref)
            ("memberref", &local.memberref)
            ("enumref", &local.enumref)
            ("macroref", &local.macroref)
            ("headerref", &local.headerref)
            ("conceptref", &local.conceptref)
            ("globalref", &local.globalref)
            ;

        local.funcref =
                local.space
            >>  (*(cl::anychar_p -
                    (']' | local.hard_space)))  [actions.funcref_pre]
            >>  local.hard_space
            >>  phrase                          [actions.funcref_post]
            ;

        local.classref =
                local.space
            >>  (*(cl::anychar_p -
                    (']' | local.hard_space)))  [actions.classref_pre]
            >>  local.hard_space
            >>  phrase                          [actions.classref_post]
            ;

        local.memberref =
                local.space
            >>  (*(cl::anychar_p -
                    (']' | local.hard_space)))  [actions.memberref_pre]
            >>  local.hard_space
            >>  phrase                          [actions.memberref_post]
            ;

        local.enumref =
                local.space
            >>  (*(cl::anychar_p -
                    (']' | local.hard_space)))  [actions.enumref_pre]
            >>  local.hard_space
            >>  phrase                          [actions.enumref_post]
            ;

        local.macroref =
                local.space
            >>  (*(cl::anychar_p -
                    (']' | local.hard_space)))  [actions.macroref_pre]
            >>  local.hard_space
            >>  phrase                          [actions.macroref_post]
            ;

        local.headerref =
                local.space
            >>  (*(cl::anychar_p -
                    (']' | local.hard_space)))  [actions.headerref_pre]
            >>  local.hard_space
            >>  phrase                          [actions.headerref_post]
            ;

        local.conceptref =
                local.space
            >>  (*(cl::anychar_p -
                    (']' | local.hard_space)))  [actions.conceptref_pre]
            >>  local.hard_space
            >>  phrase                          [actions.conceptref_post]
            ;

        local.globalref =
                local.space
            >>  (*(cl::anychar_p -
                    (']' | local.hard_space)))  [actions.globalref_pre]
            >>  local.hard_space
            >>  phrase                          [actions.globalref_post]
            ;

        phrase_symbol_rules.add
            ("*", &local.bold)
            ("'", &local.italic)
            ("_", &local.underline)
            ("^", &local.teletype)
            ("-", &local.strikethrough)
            ("\"", &local.quote)
            ("~", &local.replaceable)
            ;

        local.bold =
                local.blank                     [actions.bold_pre]
            >>  phrase                          [actions.bold_post]
            ;

        local.italic =
                local.blank                     [actions.italic_pre]
            >>  phrase                          [actions.italic_post]
            ;

        local.underline =
                local.blank                     [actions.underline_pre]
            >>  phrase                          [actions.underline_post]
            ;

        local.teletype =
                local.blank                     [actions.teletype_pre]
            >>  phrase                          [actions.teletype_post]
            ;

        local.strikethrough =
                local.blank                     [actions.strikethrough_pre]
            >>  phrase                          [actions.strikethrough_post]
            ;

        local.quote =
                local.blank                     [actions.quote_pre]
            >>  phrase                          [actions.quote_post]
            ;

        local.replaceable =
                local.blank                     [actions.replaceable_pre]
            >>  phrase                          [actions.replaceable_post]
            ;

        phrase_keyword_rules.add
            ("c++", &local.source_mode_cpp)
            ("python", &local.source_mode_python)
            ("teletype", &local.source_mode_teletype)
            ;
        
        local.source_mode_cpp = cl::eps_p [cl::assign_a(actions.source_mode, "c++")];
        local.source_mode_python = cl::eps_p [cl::assign_a(actions.source_mode, "python")];
        local.source_mode_teletype = cl::eps_p [cl::assign_a(actions.source_mode, "teletype")];

        phrase_keyword_rules.add
            ("footnote", &local.footnote)
            ;

        local.footnote =
                local.blank                     [actions.footnote_pre]
            >>  phrase                          [actions.footnote_post]
            ;
    }
}
