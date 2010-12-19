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
#include <boost/spirit/include/classic_assign_actor.hpp>
#include <boost/spirit/include/classic_if.hpp>
#include <boost/spirit/include/classic_clear_actor.hpp>

namespace quickbook
{
    namespace cl = boost::spirit::classic;

    struct block_markup_grammar_local
    {
        cl::rule<scanner>
                        h, h1, h2, h3, h4, h5, h6, blurb, blockquote,
                        warning, caution, important, note, tip,
                        inner_phrase, def_macro,
                        table, table_row, variablelist,
                        varlistentry, varlistterm, varlistitem, table_cell,
                        preformatted, begin_section, end_section,
                        xinclude, include,
                        template_, template_id, template_formal_arg,
                        template_body, identifier, import,
                        element_id, element_id_1_5, element_id_1_6;
    };

    void quickbook_grammar::impl::init_block_markup()
    {
        using detail::var;

        block_markup_grammar_local& local = store_.create();

        local.element_id =
                ':'
            >>
                (
                    cl::if_p(qbk_since(105u)) [space]
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
                space
            >>  local.element_id
            >>  space
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

        local.h  = space >> local.element_id_1_6 >> space >> local.inner_phrase [actions.h];
        local.h1 = space >> local.element_id_1_6 >> space >> local.inner_phrase [actions.h1];
        local.h2 = space >> local.element_id_1_6 >> space >> local.inner_phrase [actions.h2];
        local.h3 = space >> local.element_id_1_6 >> space >> local.inner_phrase [actions.h3];
        local.h4 = space >> local.element_id_1_6 >> space >> local.inner_phrase [actions.h4];
        local.h5 = space >> local.element_id_1_6 >> space >> local.inner_phrase [actions.h5];
        local.h6 = space >> local.element_id_1_6 >> space >> local.inner_phrase [actions.h6];
        
        static const bool true_ = true;
        static const bool false_ = false;

        block_keyword_rules.add("blurb", &local.blurb);

        local.blurb =
            scoped_block(actions)[inside_paragraph]
                                                [actions.blurb]
            ;

        block_symbol_rules.add
            (":", &local.blockquote)
            ;

        local.blockquote =
            blank >> scoped_block(actions)[inside_paragraph]
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
            scoped_block(actions)[inside_paragraph]
                                                [actions.warning]
            ;

        local.caution =
            scoped_block(actions)[inside_paragraph]
                                                [actions.caution]
            ;

        local.important =
            scoped_block(actions)[inside_paragraph]
                                                [actions.important]
            ;

        local.note =
            scoped_block(actions)[inside_paragraph]
                                                [actions.note]
            ;

        local.tip =
            scoped_block(actions)[inside_paragraph]
                                                [actions.tip]
            ;

        block_keyword_rules.add
            ("pre", &local.preformatted)
            ;

        local.preformatted =
            space                               [cl::assign_a(no_eols, false_)]
            >> !eol >> phrase                   [actions.preformatted]
            >> cl::eps_p                        [cl::assign_a(no_eols, true_)]
            ;

        block_keyword_rules.add
            ("def", &local.def_macro)
            ;

        local.def_macro =
               space
            >> macro_identifier                 [actions.macro_identifier]
            >> blank >> phrase                  [actions.macro_definition]
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
               space
            >> local.template_id                [cl::assign_a(actions.template_identifier)]
                                                [cl::clear_a(actions.template_info)]
            >>
            !(
                space >> '['
                >> *(
                        space
                    >>  local.template_id       [cl::push_back_a(actions.template_info)]
                    )
                >> space >> ']'
            )
            >>  (   cl::eps_p(*cl::blank_p >> cl::eol_p)
                                                [cl::assign_a(actions.template_block, true_)]
                |   cl::eps_p                   [cl::assign_a(actions.template_block, false_)]
                )
            >>  local.template_body             [actions.template_body]
            ;

        local.template_body =
           *(('[' >> local.template_body >> ']') | (cl::anychar_p - ']'))
            >> cl::eps_p(space >> ']')
            >> space
            ;

        block_keyword_rules.add
            ("variablelist", &local.variablelist)
            ;

        local.variablelist =
                (cl::eps_p(*cl::blank_p >> cl::eol_p) | space)
            >>  (*(cl::anychar_p - eol))        [cl::assign_a(actions.table_title)]
            >>  (+eol)                          [actions.output_pre]
            >>  *local.varlistentry
            >>  cl::eps_p                       [actions.variablelist]
            ;

        local.varlistentry =
            space
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
                    >>  space
                )
                | cl::eps_p                     [actions.error]
            )
            ;

        local.varlistterm =
            space
            >>  cl::ch_p('[')                   [actions.start_varlistterm]
            >>
            (
                (
                    phrase
                    >>  cl::ch_p(']')           [actions.end_varlistterm]
                    >>  space
                )
                | cl::eps_p                     [actions.error]
            )
            ;

        local.varlistitem =
            space
            >>  cl::ch_p('[')
            >>
            (
                (
                    inside_paragraph
                    >>  cl::ch_p(']')
                    >>  space
                )
                | cl::eps_p                     [actions.error]
            )
            ;

        block_keyword_rules.add
            ("table", &local.table)
            ;

        local.table =
                (cl::eps_p(*cl::blank_p >> cl::eol_p) | space)
            >>  local.element_id_1_5
            >>  (cl::eps_p(*cl::blank_p >> cl::eol_p) | space)
            >>  (*(cl::anychar_p - eol))        [cl::assign_a(actions.table_title)]
            >>  (+eol)                          [actions.output_pre]
            >>  *local.table_row
            >>  cl::eps_p                       [actions.table]
            ;

        local.table_row =
            space
            >>  cl::ch_p('[')                   [actions.start_row]
            >>
            (
                (
                    *local.table_cell
                    >>  cl::ch_p(']')           [actions.end_row]
                    >>  space
                )
                | cl::eps_p                     [actions.error]
            )
            ;

        local.table_cell =
                space
            >>  cl::ch_p('[')
            >>  (   scoped_block(actions) [
                        inside_paragraph
                    >>  cl::ch_p(']')
                    >>  space
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
               space
            >> (*(cl::anychar_p - phrase_end))
                                                [actions.xinclude]
            ;

        local.import =
               space
            >> (*(cl::anychar_p - phrase_end))
                                                [actions.import]
            ;

        local.include =
               space
            >>
           !(
                ':'
                >> (*((cl::alnum_p | '_') - cl::space_p))
                                                [cl::assign_a(actions.include_doc_id)]
                >> space
            )
            >> (*(cl::anychar_p - phrase_end))
                                                [actions.include]
            ;

        local.inner_phrase =
                cl::eps_p                       [actions.inner_phrase_pre]
            >>  phrase
            >>  cl::eps_p                       [actions.inner_phrase_post]
            ;
    }
}
