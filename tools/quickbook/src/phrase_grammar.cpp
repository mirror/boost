/*=============================================================================
    Copyright (c) 2002 2004 2006 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include "phrase_grammar.hpp"
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

        phrase_markup
            =   '['
            >>  (   phrase_keyword_rules        [detail::assign_rule(phrase_keyword_rule)]
                >>  (cl::eps_p - (cl::alnum_p | '_'))
                >>  phrase_keyword_rule
                |   phrase_symbol_rules         [detail::assign_rule(phrase_keyword_rule)]
                >>  phrase_keyword_rule
                |   template_                   [actions.do_template]
                |   cl::str_p("br")             [actions.break_]
                )
            >>  ']'
            ;

        escape =
                cl::str_p("\\n")                [actions.break_]
            |   cl::str_p("\\ ")                // ignore an escaped space
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

        phrase_symbol_rules.add
            ("?", &cond_phrase)
            ;

        cond_phrase =
                blank
            >>  macro_identifier                [actions.cond_phrase_pre]
            >>  (!phrase)                       [actions.cond_phrase_post]
            ;

        phrase_symbol_rules.add
            ("$", &image)
            ;

        image =
                blank                           [cl::clear_a(actions.attributes)]
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
            
        phrase_symbol_rules.add
            ("@", &url)
            ;

        url =
                (*(cl::anychar_p -
                    (']' | hard_space)))        [actions.url_pre]
            >>  hard_space
            >>  phrase                          [actions.url_post]
            ;

        phrase_keyword_rules.add
            ("link", &link)
            ;

        link =
                space
            >>  (*(cl::anychar_p -
                    (']' | hard_space)))        [actions.link_pre]
            >>  hard_space
            >>  phrase                          [actions.link_post]
            ;

        phrase_symbol_rules.add
            ("#", &anchor)
            ;

        anchor =
                blank
            >>  (*(cl::anychar_p - phrase_end)) [actions.anchor]
            ;

        phrase_keyword_rules.add
            ("funcref", &funcref)
            ("classref", &classref)
            ("memberref", &memberref)
            ("enumref", &enumref)
            ("macroref", &macroref)
            ("headerref", &headerref)
            ("conceptref", &conceptref)
            ("globalref", &globalref)
            ;

        funcref =
                space
            >>  (*(cl::anychar_p -
                    (']' | hard_space)))        [actions.funcref_pre]
            >>  hard_space
            >>  phrase                          [actions.funcref_post]
            ;

        classref =
                space
            >>  (*(cl::anychar_p -
                    (']' | hard_space)))        [actions.classref_pre]
            >>  hard_space
            >>  phrase                          [actions.classref_post]
            ;

        memberref =
                space
            >>  (*(cl::anychar_p -
                    (']' | hard_space)))        [actions.memberref_pre]
            >>  hard_space
            >>  phrase                          [actions.memberref_post]
            ;

        enumref =
                space
            >>  (*(cl::anychar_p -
                    (']' | hard_space)))        [actions.enumref_pre]
            >>  hard_space
            >>  phrase                          [actions.enumref_post]
            ;

        macroref =
                space
            >>  (*(cl::anychar_p -
                    (']' | hard_space)))        [actions.macroref_pre]
            >>  hard_space
            >>  phrase                          [actions.macroref_post]
            ;

        headerref =
                space
            >>  (*(cl::anychar_p -
                    (']' | hard_space)))        [actions.headerref_pre]
            >>  hard_space
            >>  phrase                          [actions.headerref_post]
            ;

        conceptref =
                space
            >>  (*(cl::anychar_p -
                    (']' | hard_space)))        [actions.conceptref_pre]
            >>  hard_space
            >>  phrase                          [actions.conceptref_post]
            ;

        globalref =
                space
            >>  (*(cl::anychar_p -
                    (']' | hard_space)))        [actions.globalref_pre]
            >>  hard_space
            >>  phrase                          [actions.globalref_post]
            ;

        phrase_symbol_rules.add
            ("*", &bold)
            ("'", &italic)
            ("_", &underline)
            ("^", &teletype)
            ("-", &strikethrough)
            ("\"", &quote)
            ("~", &replaceable)
            ;

        bold =
                blank                           [actions.bold_pre]
            >>  phrase                          [actions.bold_post]
            ;

        italic =
                blank                           [actions.italic_pre]
            >>  phrase                          [actions.italic_post]
            ;

        underline =
                blank                           [actions.underline_pre]
            >>  phrase                          [actions.underline_post]
            ;

        teletype =
                blank                           [actions.teletype_pre]
            >>  phrase                          [actions.teletype_post]
            ;

        strikethrough =
                blank                           [actions.strikethrough_pre]
            >>  phrase                          [actions.strikethrough_post]
            ;

        quote =
                blank                           [actions.quote_pre]
            >>  phrase                          [actions.quote_post]
            ;

        replaceable =
                blank                           [actions.replaceable_pre]
            >>  phrase                          [actions.replaceable_post]
            ;

        phrase_keyword_rules.add
            ("c++", &source_mode_cpp)
            ("python", &source_mode_python)
            ("teletype", &source_mode_teletype)
            ;
        
        source_mode_cpp = cl::eps_p [cl::assign_a(actions.source_mode, "c++")];
        source_mode_python = cl::eps_p [cl::assign_a(actions.source_mode, "python")];
        source_mode_teletype = cl::eps_p [cl::assign_a(actions.source_mode, "teletype")];

        phrase_keyword_rules.add
            ("footnote", &footnote)
            ;

        footnote =
                blank                           [actions.footnote_pre]
            >>  phrase                          [actions.footnote_post]
            ;
    }

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

    // Explicitly instantiate phrase_grammar definition so that it can be
    // used in other grammars.
    template phrase_grammar::definition<scanner>::definition(
        phrase_grammar const& self);
}
