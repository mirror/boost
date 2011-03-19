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
#include "template_tags.hpp"
#include "parsers.hpp"
#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_confix.hpp>
#include <boost/spirit/include/classic_chset.hpp>
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
                mark
            >>  lookback
                [   cl::anychar_p
                >>  ~cl::eps_p(mark)            // first mark not be preceeded by
                                                // the same character.
                >>  (cl::space_p | cl::punct_p | cl::end_p)
                                                // first mark must be preceeded
                                                // by space or punctuation or the
                                                // mark character or a the start.
                ]
            >>  (   cl::graph_p                 // graph_p must follow first mark
                >>  *(  cl::anychar_p -
                        (   lookback[cl::graph_p]
                                                // final mark must be preceeded by
                                                // graph_p
                        >>  mark
                        >>  ~cl::eps_p(mark)    // final mark not be followed by
                                                // the same character.
                        >>  (cl::space_p | cl::punct_p | cl::end_p)
                                                // final mark must be followed by
                                                // space or punctuation
                        |   close               // Make sure that we don't go
                                                // past a single block
                        )
                    )
                >>  cl::eps_p(mark)
                )                               [action]
            >> mark
            ;
    }

    struct main_grammar_local
    {
        cl::rule<scanner>
                        top_level, blocks, paragraph_separator,
                        block_element,
                        code, code_line, blank_line, hr,
                        list, ordered_list, list_item,
                        phrase_element, extended_phrase_element, element,
                        simple_phrase_end,
                        escape,
                        inline_code, simple_format,
                        simple_bold, simple_italic, simple_underline,
                        simple_teletype, template_,
                        code_block, macro,
                        template_args,
                        template_args_1_4, template_arg_1_4,
                        template_inner_arg_1_4, brackets_1_4,
                        template_args_1_5, template_arg_1_5, template_arg_1_5_content,
                        template_inner_arg_1_5, brackets_1_5,
                        command_line_macro_identifier, command_line_phrase,
                        dummy_block
                        ;

        struct assign_element_type {
            assign_element_type(main_grammar_local& l) : l(l) {}

            void operator()(element_info& t) const {
                l.element_type = t.type;
                l.element_rule = *t.rule;
            }
            
            main_grammar_local& l;
        };

        struct check_element_type {
            check_element_type(main_grammar_local const& l, element_info::context t)
                : l(l), t(t) {}

            bool operator()() const {
                return l.element_type & t;
            }

            main_grammar_local const& l;
            element_info::context t;
        };

        element_info::type_enum element_type;
        cl::rule<scanner> element_rule;
        assign_element_type assign_element;

        main_grammar_local()
            : assign_element(*this) {}
        
        check_element_type check_element(element_info::context t) const {
            return check_element_type(*this, t);
        }
    };

    void quickbook_grammar::impl::init_main()
    {
        using detail::var;

        main_grammar_local& local = store_.create();

        block_skip_initial_spaces =
            *(cl::blank_p | comment) >> block_start
            ;

        block_start =
            local.top_level >> blank
            ;

        local.top_level
            =   local.blocks
            >>  *(
                    local.block_element >> !(+eol >> local.blocks)
                |   local.paragraph_separator >> local.blocks
                |   common
                |   cl::space_p                 [actions.space_char]
                |   cl::anychar_p               [actions.plain_char]
                );

        local.blocks =
           *(   local.code
            |   local.list                      [actions.list]
            |   local.hr                        [actions.hr]
            |   +eol
            )
            ;

        local.paragraph_separator
            =   cl::eol_p
            >> *cl::blank_p
            >>  cl::eol_p                       [actions.inside_paragraph]
            ;

        local.hr =
            cl::str_p("----")
            >> *(cl::anychar_p - eol)
            >> +eol
            ;

        local.block_element
            =   '[' >> space
            >>  local.element
            >>  cl::eps_p(local.check_element(element_info::in_block))
                                                [actions.inside_paragraph]
                                                [actions.values.reset]
            >>  (   local.element_rule
                >>  (   (space >> ']')
                    |   cl::eps_p               [actions.error]
                    )
                |   cl::eps_p                   [actions.error]
                )
            ;
        
        local.code =
            (
                local.code_line
                >> *(*local.blank_line >> local.code_line)
            )                                   [actions.code]
            >> *eol
            ;

        local.code_line =
            cl::blank_p >> *(cl::anychar_p - cl::eol_p) >> cl::eol_p
            ;

        local.blank_line =
            *cl::blank_p >> cl::eol_p
            ;

        local.list =
            cl::eps_p(cl::ch_p('*') | '#') >>
           +(
                (*cl::blank_p
                >> (cl::ch_p('*') | '#'))       [actions.list_format]
                >> *cl::blank_p
                >> local.list_item
            )                                   [actions.list_item]
            ;

        local.list_item =
           *(   common
            |   (cl::anychar_p -
                    (   cl::eol_p >> *cl::blank_p
                    >>  (cl::ch_p('*') | '#' | cl::eol_p)
                    )
                )                               [actions.plain_char]
            )
            >> +eol
            ;

        common =
                local.macro
            |   local.phrase_element
            |   local.code_block
            |   local.inline_code
            |   local.simple_format
            |   local.escape
            |   comment
            ;

        local.macro =
            // must not be followed by alpha or underscore
            cl::eps_p(actions.macro
                >> (cl::eps_p - (cl::alpha_p | '_')))
            >> actions.macro                    [actions.do_macro]
            ;

        local.template_ =
                cl::eps_p                       [actions.values.reset]
            >>  !cl::str_p("`")                 [actions.values.entry(template_tags::escape)]
            >>
            ( (
                (cl::eps_p(cl::punct_p)
                    >> actions.templates.scope
                )                               [actions.values.entry(template_tags::identifier)]
                >> !local.template_args
            ) | (
                (actions.templates.scope
                    >> cl::eps_p(hard_space)
                )                               [actions.values.entry(template_tags::identifier)]
                >> space
                >> !local.template_args
            ) )
            >> cl::eps_p(']')
            >> cl::eps_p                        [actions.do_template]
            ;

        local.template_args =
            cl::if_p(qbk_since(105u)) [
                local.template_args_1_5
            ].else_p [
                local.template_args_1_4
            ]
            ;

        local.template_args_1_4 = local.template_arg_1_4 >> *(".." >> local.template_arg_1_4);

        local.template_arg_1_4 =
            (   cl::eps_p(*cl::blank_p >> cl::eol_p)
            >>  local.template_inner_arg_1_4    [actions.values.entry(template_tags::block)]
            |   local.template_inner_arg_1_4    [actions.values.entry(template_tags::phrase)]
            )                               
            ;

        local.template_inner_arg_1_4 =
            +(local.brackets_1_4 | (cl::anychar_p - (cl::str_p("..") | ']')))
            ;

        local.brackets_1_4 =
            '[' >> local.template_inner_arg_1_4 >> ']'
            ;

        local.template_args_1_5 = local.template_arg_1_5 >> *(".." >> local.template_arg_1_5);

        local.template_arg_1_5 =
            (   cl::eps_p(*cl::blank_p >> cl::eol_p)
            >>  local.template_arg_1_5_content  [actions.values.entry(template_tags::block)]
            |   local.template_arg_1_5_content  [actions.values.entry(template_tags::phrase)]
            )
            ;

        local.template_arg_1_5_content =
            +(local.brackets_1_5 | ('\\' >> cl::anychar_p) | (cl::anychar_p - (cl::str_p("..") | '[' | ']')))
            ;

        local.template_inner_arg_1_5 =
            +(local.brackets_1_5 | ('\\' >> cl::anychar_p) | (cl::anychar_p - (cl::str_p('[') | ']')))
            ;

        local.brackets_1_5 =
            '[' >> local.template_inner_arg_1_5 >> ']'
            ;

        local.inline_code =
            '`' >>
            (
               *(cl::anychar_p -
                    (   '`'
                    |   (cl::eol_p >> *cl::blank_p >> cl::eol_p)
                                                // Make sure that we don't go
                    )                           // past a single block
                ) >> cl::eps_p('`')
            )                                   [actions.inline_code]
            >>  '`'
            ;

        local.code_block =
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

        local.simple_format =
                local.simple_bold
            |   local.simple_italic
            |   local.simple_underline
            |   local.simple_teletype
            ;

        local.simple_phrase_end = '[' | phrase_end;

        simple_markup(local.simple_bold,
            '*', actions.simple_bold, local.simple_phrase_end);
        simple_markup(local.simple_italic,
            '/', actions.simple_italic, local.simple_phrase_end);
        simple_markup(local.simple_underline,
            '_', actions.simple_underline, local.simple_phrase_end);
        simple_markup(local.simple_teletype,
            '=', actions.simple_teletype, local.simple_phrase_end);

        phrase =
           *(   common
            |   (cl::anychar_p - phrase_end)    [actions.plain_char]
            )
            ;

        extended_phrase =
           *(   local.extended_phrase_element
            |   common
            |   (cl::anychar_p - phrase_end)    [actions.plain_char]
            )
            ;

        inside_paragraph =
            actions.scoped_block[
            actions.values.save[
            (*( common
            |   (cl::anychar_p - phrase_end)    [actions.plain_char]
            |   (+eol)                          [actions.inside_paragraph]
            ))                                  [actions.inside_paragraph]
            ]
            ]
            ;

        local.phrase_element
            =   '['
            >>  space
            >>  (   local.element
                >>  cl::eps_p(local.check_element(element_info::in_phrase))
                >>  local.element_rule
                |   local.template_
                |   cl::str_p("br")             [actions.break_]
                )
            >>  ']'
            ;

        local.extended_phrase_element
            =   '[' >> space
            >>  local.element
            >>  cl::eps_p(local.check_element(element_info::in_conditional))
                                                [actions.inside_paragraph]
            >>  (   local.element_rule
                >>  (   (space >> ']')
                    |   cl::eps_p               [actions.error]
                    )
                |   cl::eps_p                   [actions.error]
                )
            ;


        local.element
            =   cl::eps_p(cl::punct_p)
            >>  elements                    [local.assign_element]
            |   elements                    [local.assign_element]
            >>  (cl::eps_p - (cl::alnum_p | '_'))
            ;

        local.escape =
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

        //
        // Simple phrase grammar
        //

        simple_phrase =
           *(   common
            |   (cl::anychar_p - ']')       [actions.plain_char]
            )
            ;

        //
        // Command line
        //

        command_line =
                *cl::space_p
            >>  local.command_line_macro_identifier
                                            [actions.macro_identifier]
            >>  *cl::space_p
            >>  (   '='
                >>  *cl::space_p
                >>  local.command_line_phrase
                                            [actions.macro_definition]
                >>  *cl::space_p
                )
            |   cl::eps_p                   [actions.macro_definition]
            ;

        local.command_line_macro_identifier =
            +(cl::anychar_p - (cl::space_p | ']' | '='))
            ;


        local.command_line_phrase =
           *(   common
            |   (cl::anychar_p - ']')       [actions.plain_char]
            )
            ;

        // Miscellaneous stuff

        // Follows an alphanumeric identifier - ensures that it doesn't
        // match an empty space in the middle of the identifier.
        hard_space =
            (cl::eps_p - (cl::alnum_p | '_')) >> space
            ;

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
            cl::if_p(var(actions.no_eols))
            [
                cl::eol_p >> *cl::blank_p >> cl::eol_p
                                                // Make sure that we don't go
            ]                                   // past a single block, except
            ;                                   // when preformatted.

        comment =
            "[/" >> *(local.dummy_block | (cl::anychar_p - ']')) >> ']'
            ;

        local.dummy_block =
            '[' >> *(local.dummy_block | (cl::anychar_p - ']')) >> ']'
            ;

        macro_identifier =
            +(cl::anychar_p - (cl::space_p | ']'))
            ;

    }
}
