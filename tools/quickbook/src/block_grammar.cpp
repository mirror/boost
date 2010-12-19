/*=============================================================================
    Copyright (c) 2002 2004  2006Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include "scoped_block.hpp"
#include "utils.hpp"
#include "actions_class.hpp"
#include "grammar_impl.hpp"
#include <boost/spirit/include/classic_confix.hpp>
#include <boost/spirit/include/classic_chset.hpp>
#include <boost/spirit/include/classic_assign_actor.hpp>
#include <boost/spirit/include/classic_if.hpp>
#include <boost/spirit/include/classic_symbols.hpp>
#include <boost/spirit/include/classic_clear_actor.hpp>

namespace quickbook
{
    namespace cl = boost::spirit::classic;

    struct block_grammar_local
    {
        cl::rule<scanner>
                        blocks, block_markup, block_markup_start,
                        code, code_line, blank_line,
                        paragraph, space, blank, comment, h, h1, h2,
                        h3, h4, h5, h6, hr, blurb, blockquote,
                        warning, caution, important, note, tip,
                        inner_phrase, phrase, list, phrase_end, ordered_list, def_macro,
                        macro_identifier, table, table_row, variablelist,
                        varlistentry, varlistterm, varlistitem, table_cell,
                        preformatted, list_item, begin_section, end_section,
                        xinclude, include, hard_space, eol, paragraph_end,
                        template_, template_id, template_formal_arg,
                        template_body, identifier, dummy_block, import,
                        inside_paragraph,
                        element_id, element_id_1_5, element_id_1_6;

        cl::rule<scanner> block_keyword_rule;
    };

    void quickbook_grammar::impl::init_block(bool skip_initial_spaces)
    {
        using detail::var;

        block_grammar_local& local = store_.create();

        if (skip_initial_spaces)
        {
            block_start =
                *(cl::blank_p | local.comment) >> local.blocks >> local.blank
                ;
        }
        else
        {
            block_start =
                local.blocks >> local.blank
                ;
        }

        local.blocks =
           *(   local.block_markup
            |   local.code
            |   local.list                      [actions.list]
            |   local.hr                        [actions.hr]
            |   +local.eol
            |   local.paragraph                 [actions.inside_paragraph]
            )
            ;

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
                local.eol >> *cl::blank_p >> cl::eol_p
                                                // Make sure that we don't go
            ]                                   // past a single block, except
            ;                                   // when preformatted.

        // Follows after an alphanumeric identifier - ensures that it doesn't
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

        local.hr =
            cl::str_p("----")
            >> *(cl::anychar_p - local.eol)
            >> +local.eol
            ;

        local.block_markup
            =   local.block_markup_start
            >>  local.block_keyword_rule
            >>  (   (local.space >> ']' >> +local.eol)
                |   cl::eps_p                   [actions.error]
                )
            ;

        // If you update this, make sure local.paragraph_end matches it,
        // without the actions.
        local.block_markup_start
            =   '[' >> local.space
            >>  (   block_keyword_rules         [detail::assign_rule(local.block_keyword_rule)]
                >>  (cl::eps_p - (cl::alnum_p | '_'))
                |   block_symbol_rules          [detail::assign_rule(local.block_keyword_rule)]
                )
            ;

        local.element_id =
                ':'
            >>
                (
                    cl::if_p(qbk_since(105u))
                        [local.space]
                >>  (+(cl::alnum_p | '_'))      [cl::assign_a(actions.element_id)]
                |   cl::eps_p                   [actions.element_id_warning]
                                                [cl::assign_a(actions.element_id)]
                )
            | cl::eps_p                         [cl::assign_a(actions.element_id)]
            ;
        
        local.element_id_1_5 =
                cl::if_p(qbk_since(105u)) [
                    local.element_id
                ]
                .else_p [
                    cl::eps_p                   [cl::assign_a(actions.element_id)]
                ]
                ;

        local.element_id_1_6 =
                cl::if_p(qbk_since(106u)) [
                    local.element_id
                ]
                .else_p [
                    cl::eps_p                   [cl::assign_a(actions.element_id)]
                ]
                ;

        block_keyword_rules.add
            ("section", &local.begin_section)
            ("endsect", &local.end_section)
            ;

        local.begin_section =
                local.space
            >>  local.element_id
            >>  local.space
            >>  local.inner_phrase              [actions.begin_section]
            ;

        local.end_section =
                cl::eps_p                       [actions.end_section]
            ;

        block_keyword_rules.add
            ("heading", &local.h)
            ("h1", &local.h1)
            ("h2", &local.h2)
            ("h3", &local.h3)
            ("h4", &local.h4)
            ("h5", &local.h5)
            ("h6", &local.h6)
            ;

        local.h  = local.space >> local.element_id_1_6 >> local.space >> local.inner_phrase [actions.h];
        local.h1 = local.space >> local.element_id_1_6 >> local.space >> local.inner_phrase [actions.h1];
        local.h2 = local.space >> local.element_id_1_6 >> local.space >> local.inner_phrase [actions.h2];
        local.h3 = local.space >> local.element_id_1_6 >> local.space >> local.inner_phrase [actions.h3];
        local.h4 = local.space >> local.element_id_1_6 >> local.space >> local.inner_phrase [actions.h4];
        local.h5 = local.space >> local.element_id_1_6 >> local.space >> local.inner_phrase [actions.h5];
        local.h6 = local.space >> local.element_id_1_6 >> local.space >> local.inner_phrase [actions.h6];
        
        static const bool true_ = true;
        static const bool false_ = false;

        local.inside_paragraph =
            local.phrase                        [actions.inside_paragraph]
            >> *(
                +local.eol >> local.phrase      [actions.inside_paragraph]
            )
            ;

        block_keyword_rules.add("blurb", &local.blurb);

        local.blurb =
            scoped_block(actions)[local.inside_paragraph]
                                                [actions.blurb]
            ;

        block_symbol_rules.add
            (":", &local.blockquote)
            ;

        local.blockquote =
            local.blank >> scoped_block(actions)[local.inside_paragraph]
                                                [actions.blockquote]
            ;

        block_keyword_rules.add
            ("warning", &local.warning)
            ("caution", &local.caution)
            ("important", &local.important)
            ("note", &local.note)
            ("tip", &local.tip)
            ;

        local.warning =
            scoped_block(actions)[local.inside_paragraph]
                                                [actions.warning]
            ;

        local.caution =
            scoped_block(actions)[local.inside_paragraph]
                                                [actions.caution]
            ;

        local.important =
            scoped_block(actions)[local.inside_paragraph]
                                                [actions.important]
            ;

        local.note =
            scoped_block(actions)[local.inside_paragraph]
                                                [actions.note]
            ;

        local.tip =
            scoped_block(actions)[local.inside_paragraph]
                                                [actions.tip]
            ;

        block_keyword_rules.add
            ("pre", &local.preformatted)
            ;

        local.preformatted =
            local.space                         [cl::assign_a(no_eols, false_)]
            >> !local.eol >> local.phrase       [actions.preformatted]
            >> cl::eps_p                        [cl::assign_a(no_eols, true_)]
            ;

        local.macro_identifier =
            +(cl::anychar_p - (cl::space_p | ']'))
            ;

        block_keyword_rules.add
            ("def", &local.def_macro)
            ;

        local.def_macro =
               local.space
            >> local.macro_identifier           [actions.macro_identifier]
            >> local.blank >> local.phrase      [actions.macro_definition]
            ;

        local.identifier =
            (cl::alpha_p | '_') >> *(cl::alnum_p | '_')
            ;

        local.template_id =
            local.identifier | (cl::punct_p - (cl::ch_p('[') | ']'))
            ;

        block_keyword_rules.add
            ("template", &local.template_)
            ;

        local.template_ =
               local.space
            >> local.template_id                [cl::assign_a(actions.template_identifier)]
                                                [cl::clear_a(actions.template_info)]
            >>
            !(
                local.space >> '['
                >> *(
                        local.space
                    >>  local.template_id       [cl::push_back_a(actions.template_info)]
                    )
                >> local.space >> ']'
            )
            >>  (   cl::eps_p(*cl::blank_p >> cl::eol_p)
                                                [cl::assign_a(actions.template_block, true_)]
                |   cl::eps_p                   [cl::assign_a(actions.template_block, false_)]
                )
            >>  local.template_body             [actions.template_body]
            ;

        local.template_body =
           *(('[' >> local.template_body >> ']') | (cl::anychar_p - ']'))
            >> cl::eps_p(local.space >> ']')
            >> local.space
            ;

        block_keyword_rules.add
            ("variablelist", &local.variablelist)
            ;

        local.variablelist =
                (cl::eps_p(*cl::blank_p >> cl::eol_p) | local.space)
            >>  (*(cl::anychar_p - local.eol))  [cl::assign_a(actions.table_title)]
            >>  (+local.eol)                    [actions.output_pre]
            >>  *local.varlistentry
            >>  cl::eps_p                       [actions.variablelist]
            ;

        local.varlistentry =
            local.space
            >>  cl::ch_p('[')                   [actions.start_varlistentry]
            >>
            (
                (
                    local.varlistterm
                    >>  (   scoped_block(actions) [+local.varlistitem]
                                                [actions.varlistitem]
                        |   cl::eps_p           [actions.error]
                        )
                    >>  cl::ch_p(']')           [actions.end_varlistentry]
                    >>  local.space
                )
                | cl::eps_p                     [actions.error]
            )
            ;

        local.varlistterm =
            local.space
            >>  cl::ch_p('[')                   [actions.start_varlistterm]
            >>
            (
                (
                    local.phrase
                    >>  cl::ch_p(']')           [actions.end_varlistterm]
                    >>  local.space
                )
                | cl::eps_p                     [actions.error]
            )
            ;

        local.varlistitem =
            local.space
            >>  cl::ch_p('[')
            >>
            (
                (
                    local.inside_paragraph
                    >>  cl::ch_p(']')
                    >>  local.space
                )
                | cl::eps_p                     [actions.error]
            )
            ;

        block_keyword_rules.add
            ("table", &local.table)
            ;

        local.table =
                (cl::eps_p(*cl::blank_p >> cl::eol_p) | local.space)
            >>  local.element_id_1_5
            >>  (cl::eps_p(*cl::blank_p >> cl::eol_p) | local.space)
            >>  (*(cl::anychar_p - local.eol))  [cl::assign_a(actions.table_title)]
            >>  (+local.eol)                    [actions.output_pre]
            >>  *local.table_row
            >>  cl::eps_p                       [actions.table]
            ;

        local.table_row =
            local.space
            >>  cl::ch_p('[')                   [actions.start_row]
            >>
            (
                (
                    *local.table_cell
                    >>  cl::ch_p(']')           [actions.end_row]
                    >>  local.space
                )
                | cl::eps_p                     [actions.error]
            )
            ;

        local.table_cell =
                local.space
            >>  cl::ch_p('[')
            >>  (   scoped_block(actions) [
                        local.inside_paragraph
                    >>  cl::ch_p(']')
                    >>  local.space
                    ]                           [actions.cell]
                | cl::eps_p                     [actions.error]
                )
            ;

        block_keyword_rules.add
            ("xinclude", &local.xinclude)
            ("import", &local.import)
            ("include", &local.include)
            ;

        local.xinclude =
               local.space
            >> (*(cl::anychar_p - local.phrase_end))
                                                [actions.xinclude]
            ;

        local.import =
               local.space
            >> (*(cl::anychar_p - local.phrase_end))
                                                [actions.import]
            ;

        local.include =
               local.space
            >>
           !(
                ':'
                >> (*((cl::alnum_p | '_') - cl::space_p))
                                                [cl::assign_a(actions.include_doc_id)]
                >> local.space
            )
            >> (*(cl::anychar_p - local.phrase_end))
                                                [actions.include]
            ;

        local.code =
            (
                local.code_line
                >> *(*local.blank_line >> local.code_line)
            )                                   [actions.code]
            >> *local.eol
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
                    (   cl::eol_p >> *cl::blank_p >> cl::eps_p(cl::ch_p('*') | '#')
                    |   (local.eol >> local.eol)
                    )
                )                               [actions.plain_char]
            )
            >> +local.eol
            ;

        // Note: Not using local.block_markup_start here as it would change
        // block_keyword_rule.
        local.paragraph_end
            =   '[' >> local.space
            >>  (   block_keyword_rules >> (cl::eps_p - (cl::alnum_p | '_'))
                |   block_symbol_rules
                )
            |   local.eol >> *cl::blank_p >> cl::eol_p
            ;

        local.paragraph =
           +(   common
            |   (cl::eps_p -                    // Make sure we don't go past
                    local.paragraph_end)        // a single block.
            >>  (   cl::space_p                 [actions.space_char]
                |   cl::anychar_p               [actions.plain_char]
                )
            )
            >> (cl::eps_p('[') | +local.eol)
            ;

        local.inner_phrase =
                cl::eps_p                       [actions.inner_phrase_pre]
            >>  local.phrase
            >>  cl::eps_p                       [actions.inner_phrase_post]
            ;

        local.phrase =
           *(   common
            |   local.comment
            |   (cl::anychar_p - local.phrase_end)
                                                [actions.plain_char]
            )
            ;
    }
}
