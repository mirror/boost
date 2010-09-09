/*=============================================================================
    Copyright (c) 2002 2004 2006 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_QUICKBOOK_PHRASE_HPP)
#define BOOST_SPIRIT_QUICKBOOK_PHRASE_HPP

#include "grammar.hpp"
#include "actions_class.hpp"
#include "utils.hpp"
#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_confix.hpp>
#include <boost/spirit/include/classic_chset.hpp>
#include <boost/spirit/include/classic_assign_actor.hpp>
#include <boost/spirit/include/classic_clear_actor.hpp>
#include <boost/spirit/include/classic_if.hpp>
#include <boost/spirit/include/classic_loops.hpp>

namespace quickbook
{
    namespace cl = boost::spirit::classic;

    template <typename Rule, typename Action>
    inline void
    simple_markup(
        Rule& simple
      , char mark
      , Action const& action
      , Rule const& close
    )
    {
        simple =
            mark >>
            (
                (
                    cl::graph_p                 // A single char. e.g. *c*
                    >> cl::eps_p(mark
                        >> (cl::space_p | cl::punct_p | cl::end_p))
                                                // space_p, punct_p or end_p
                )                               // must follow mark
            |
                (   cl::graph_p >>              // graph_p must follow mark
                    *(cl::anychar_p -
                        (   (cl::graph_p >> mark) // Make sure that we don't go
                        |   close                 // past a single block
                        )
                    ) >> cl::graph_p            // graph_p must precede mark
                    >> cl::eps_p(mark
                        >> (cl::space_p | cl::punct_p | cl::end_p))
                                                // space_p, punct_p or end_p
                )                               // must follow mark
            )                                   [action]
            >> mark
            ;
    }

    template <typename Scanner>
    struct phrase_grammar::definition
    {
        definition(phrase_grammar const& self);

        cl::rule<Scanner>
                        space, blank, comment, phrase, phrase_markup, image,
                        simple_phrase_end, phrase_end, bold, italic, underline, teletype,
                        strikethrough, escape, url, common, funcref, classref,
                        memberref, enumref, macroref, headerref, conceptref, globalref,
                        anchor, link, hard_space, eol, inline_code, simple_format,
                        simple_bold, simple_italic, simple_underline,
                        simple_teletype, source_mode, template_,
                        quote, code_block, footnote, replaceable, macro,
                        dummy_block, cond_phrase, macro_identifier, template_args,
                        template_args_1_4, template_arg_1_4,
                        template_inner_arg_1_4, brackets_1_4,
                        template_args_1_5, template_arg_1_5,
                        template_inner_arg_1_5, brackets_1_5
                        ;

        cl::rule<Scanner> const&
        start() const { return common; }
    };

    template <typename Scanner>
    phrase_grammar::definition<Scanner>::definition(phrase_grammar const& self)
    {
        using detail::var;
        quickbook::actions& actions = self.actions;

        space =
            *(cl::space_p | comment)
            ;

        blank =
            *(cl::blank_p | comment)
            ;

        eol = blank >> cl::eol_p
            ;

        phrase_end =
            ']' |
            cl::if_p(var(self.no_eols))
            [
                eol >> eol                      // Make sure that we don't go
            ]                                   // past a single block, except
            ;                                   // when preformatted.

        // Follows an alphanumeric identifier - ensures that it doesn't
        // match an empty space in the middle of the identifier.
        hard_space =
            (cl::eps_p - (cl::alnum_p | '_')) >> space
            ;

        comment =
            "[/" >> *(dummy_block | (cl::anychar_p - ']')) >> ']'
            ;

        dummy_block =
            '[' >> *(dummy_block | (cl::anychar_p - ']')) >> ']'
            ;

        common =
                macro
            |   phrase_markup
            |   code_block
            |   inline_code
            |   simple_format
            |   escape
            |   comment
            ;

        macro =
            // must not be followed by alpha or underscore
            cl::eps_p(actions.macro
                >> (cl::eps_p - (cl::alpha_p | '_')))
            >> actions.macro                    [actions.do_macro]
            ;

        static const bool true_ = true;
        static const bool false_ = false;

        template_ =
            (
                cl::ch_p('`')                   [cl::assign_a(actions.template_escape,true_)]
                |
                cl::eps_p                       [cl::assign_a(actions.template_escape,false_)]
            )
            >>
            ( (
                (cl::eps_p(cl::punct_p)
                    >> actions.templates.scope
                )                               [cl::assign_a(actions.template_identifier)]
                                                [cl::clear_a(actions.template_args)]
                >> !template_args
            ) | (
                (actions.templates.scope
                    >> cl::eps_p(hard_space)
                )                               [cl::assign_a(actions.template_identifier)]
                                                [cl::clear_a(actions.template_args)]
                >> space
                >> !template_args
            ) )
            >> cl::eps_p(']')
            ;

        template_args =
            cl::if_p(qbk_since(105u)) [
                template_args_1_5
            ].else_p [
                template_args_1_4
            ]
            ;

        template_args_1_4 = template_arg_1_4 >> *(".." >> template_arg_1_4);

        template_arg_1_4 =
                (   cl::eps_p(*cl::blank_p >> cl::eol_p)
                                                [cl::assign_a(actions.template_block, true_)]
                |   cl::eps_p                   [cl::assign_a(actions.template_block, false_)]
                )
            >>  template_inner_arg_1_4          [actions.template_arg]
            ;

        template_inner_arg_1_4 =
            +(brackets_1_4 | (cl::anychar_p - (cl::str_p("..") | ']')))
            ;

        brackets_1_4 =
            '[' >> template_inner_arg_1_4 >> ']'
            ;

        template_args_1_5 = template_arg_1_5 >> *(".." >> template_arg_1_5);

        template_arg_1_5 =
                (   cl::eps_p(*cl::blank_p >> cl::eol_p)
                                                [cl::assign_a(actions.template_block, true_)]
                |   cl::eps_p                   [cl::assign_a(actions.template_block, false_)]
                )
            >>  (+(brackets_1_5 | ('\\' >> cl::anychar_p) | (cl::anychar_p - (cl::str_p("..") | '[' | ']'))))
                                                [actions.template_arg]
            ;

        template_inner_arg_1_5 =
            +(brackets_1_5 | ('\\' >> cl::anychar_p) | (cl::anychar_p - (cl::str_p('[') | ']')))
            ;

        brackets_1_5 =
            '[' >> template_inner_arg_1_5 >> ']'
            ;

        inline_code =
            '`' >>
            (
               *(cl::anychar_p -
                    (   '`'
                    |   (eol >> eol)            // Make sure that we don't go
                    )                           // past a single block
                ) >> cl::eps_p('`')
            )                                   [actions.inline_code]
            >>  '`'
            ;

        code_block =
                (
                    "```" >>
                    (
                       *(cl::anychar_p - "```")
                            >> cl::eps_p("```")
                    )                           [actions.code_block]
                    >>  "```"
                )
            |   (
                    "``" >>
                    (
                       *(cl::anychar_p - "``")
                            >> cl::eps_p("``")
                    )                           [actions.code_block]
                    >>  "``"
                )
            ;

        simple_format =
                simple_bold
            |   simple_italic
            |   simple_underline
            |   simple_teletype
            ;

        simple_phrase_end = '[' | phrase_end;

        simple_markup(simple_bold,
            '*', actions.simple_bold, simple_phrase_end);
        simple_markup(simple_italic,
            '/', actions.simple_italic, simple_phrase_end);
        simple_markup(simple_underline,
            '_', actions.simple_underline, simple_phrase_end);
        simple_markup(simple_teletype,
            '=', actions.simple_teletype, simple_phrase_end);

        phrase =
           *(   common
            |   comment
            |   (cl::anychar_p - phrase_end)    [actions.plain_char]
            )
            ;

        phrase_markup =
                '['
            >>  (   cond_phrase
                |   image
                |   url
                |   link
                |   anchor
                |   source_mode
                |   funcref
                |   classref
                |   memberref
                |   enumref
                |   macroref
                |   headerref
                |   conceptref
                |   globalref
                |   bold
                |   italic
                |   underline
                |   teletype
                |   strikethrough
                |   quote
                |   replaceable
                |   footnote
                |   template_                   [actions.do_template]
                |   cl::str_p("br")             [actions.break_]
                )
            >>  ']'
            ;

        escape =
                cl::str_p("\\ ")                // ignore an escaped space
            |   '\\' >> cl::punct_p             [actions.raw_char]
            |   "\\u" >> cl::repeat_p(4) [cl::chset<>("0-9a-fA-F")]
                                                [actions.escape_unicode]
            |   "\\U" >> cl::repeat_p(8) [cl::chset<>("0-9a-fA-F")]
                                                [actions.escape_unicode]
            |   (
                    ("'''" >> !eol)             [actions.escape_pre]
                >>  *(cl::anychar_p - "'''")    [actions.raw_char]
                >>  cl::str_p("'''")            [actions.escape_post]
                )
            ;

        macro_identifier =
            +(cl::anychar_p - (cl::space_p | ']'))
            ;

        cond_phrase =
                '?' >> blank
            >>  macro_identifier                [actions.cond_phrase_pre]
            >>  (!phrase)                       [actions.cond_phrase_post]
            ;

        image =
                '$' >> blank                    [cl::clear_a(actions.attributes)]
            >>  cl::if_p(qbk_since(105u)) [
                        (+(
                            *cl::space_p
                        >>  +(cl::anychar_p - (cl::space_p | phrase_end | '['))
                        ))                       [cl::assign_a(actions.image_fileref)]
                    >>  hard_space
                    >>  *(
                            '['
                        >>  (*(cl::alnum_p | '_'))  [cl::assign_a(actions.attribute_name)]
                        >>  space
                        >>  (*(cl::anychar_p - (phrase_end | '[')))
                                                [actions.attribute]
                        >>  ']'
                        >>  space
                        )
                ].else_p [
                        (*(cl::anychar_p - phrase_end))
                                                [cl::assign_a(actions.image_fileref)]
                ]
            >>  cl::eps_p(']')                  [actions.image]
            ;
            
        url =
                '@'
            >>  (*(cl::anychar_p -
                    (']' | hard_space)))        [actions.url_pre]
            >>  (   cl::eps_p(']')
                |   (hard_space >> phrase)
                )                               [actions.url_post]
            ;

        link =
                "link" >> hard_space
            >>  (*(cl::anychar_p -
                    (']' | hard_space)))        [actions.link_pre]
            >>  (   cl::eps_p(']')
                |   (hard_space >> phrase)
                )                               [actions.link_post]
            ;

        anchor =
                '#'
            >>  blank
            >>  (   *(cl::anychar_p - phrase_end)
                )                               [actions.anchor]
            ;

        funcref =
            "funcref" >> hard_space
            >>  (*(cl::anychar_p -
                    (']' | hard_space)))        [actions.funcref_pre]
            >>  (   cl::eps_p(']')
                |   (hard_space >> phrase)
                )                               [actions.funcref_post]
            ;

        classref =
            "classref" >> hard_space
            >>  (*(cl::anychar_p -
                    (']' | hard_space)))        [actions.classref_pre]
            >>  (   cl::eps_p(']')
                |   (hard_space >> phrase)
                )                               [actions.classref_post]
            ;

        memberref =
            "memberref" >> hard_space
            >>  (*(cl::anychar_p -
                    (']' | hard_space)))        [actions.memberref_pre]
            >>  (   cl::eps_p(']')
                |   (hard_space >> phrase)
                )                               [actions.memberref_post]
            ;

        enumref =
            "enumref" >> hard_space
            >>  (*(cl::anychar_p -
                    (']' | hard_space)))        [actions.enumref_pre]
            >>  (   cl::eps_p(']')
                |   (hard_space >> phrase)
                )                               [actions.enumref_post]
            ;

        macroref =
            "macroref" >> hard_space
            >>  (*(cl::anychar_p -
                    (']' | hard_space)))        [actions.macroref_pre]
            >>  (   cl::eps_p(']')
                |   (hard_space >> phrase)
                )                               [actions.macroref_post]
            ;

        headerref =
            "headerref" >> hard_space
            >>  (*(cl::anychar_p -
                    (']' | hard_space)))        [actions.headerref_pre]
            >>  (   cl::eps_p(']')
                |   (hard_space >> phrase)
                )                               [actions.headerref_post]
            ;

        conceptref =
            "conceptref" >> hard_space
            >>  (*(cl::anychar_p -
                    (']' | hard_space)))        [actions.conceptref_pre]
            >>  (   cl::eps_p(']')
                |   (hard_space >> phrase)
                )                               [actions.conceptref_post]
            ;

        globalref =
            "globalref" >> hard_space
            >>  (*(cl::anychar_p -
                    (']' | hard_space)))        [actions.globalref_pre]
            >>  (   cl::eps_p(']')
                |   (hard_space >> phrase)
                )                               [actions.globalref_post]
            ;

        bold =
                cl::ch_p('*')                   [actions.bold_pre]
            >>  blank >> phrase                 [actions.bold_post]
            ;

        italic =
                cl::ch_p('\'')                  [actions.italic_pre]
            >>  blank >> phrase                 [actions.italic_post]
            ;

        underline =
                cl::ch_p('_')                   [actions.underline_pre]
            >>  blank >> phrase                 [actions.underline_post]
            ;

        teletype =
                cl::ch_p('^')                   [actions.teletype_pre]
            >>  blank >> phrase                 [actions.teletype_post]
            ;

        strikethrough =
                cl::ch_p('-')                   [actions.strikethrough_pre]
            >>  blank >> phrase                 [actions.strikethrough_post]
            ;

        quote =
                cl::ch_p('"')                   [actions.quote_pre]
            >>  blank >> phrase                 [actions.quote_post]
            ;

        replaceable =
                cl::ch_p('~')                   [actions.replaceable_pre]
            >>  blank >> phrase                 [actions.replaceable_post]
            ;

        source_mode =
            (
                cl::str_p("c++")
            |   "python"
            |   "teletype"
            )                                   [cl::assign_a(actions.source_mode)]
            ;

        footnote =
                cl::str_p("footnote")           [actions.footnote_pre]
            >>  blank >> phrase                 [actions.footnote_post]
            ;
    }
}

#endif // BOOST_SPIRIT_QUICKBOOK_PHRASE_HPP

