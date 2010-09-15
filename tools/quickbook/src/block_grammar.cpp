/*=============================================================================
    Copyright (c) 2002 2004  2006Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include "phrase_grammar.hpp"
#include "utils.hpp"
#include "actions_class.hpp"
#include "scoped_block.hpp"
#include <boost/spirit/include/classic_confix.hpp>
#include <boost/spirit/include/classic_chset.hpp>
#include <boost/spirit/include/classic_assign_actor.hpp>
#include <boost/spirit/include/classic_if.hpp>
#include <boost/spirit/include/classic_symbols.hpp>
#include <boost/spirit/include/classic_clear_actor.hpp>

namespace quickbook
{
    namespace cl = boost::spirit::classic;

    template <typename Scanner>
    struct block_grammar::definition
    {
        definition(block_grammar const&);

        bool no_eols;

        cl::rule<Scanner>
                        start_, blocks, block_markup, code, code_line, blank_line,
                        paragraph, space, blank, comment, headings, h, h1, h2,
                        h3, h4, h5, h6, hr, blurb, blockquote, admonition,
                        phrase, list, phrase_end, ordered_list, def_macro,
                        macro_identifier, table, table_row, variablelist,
                        varlistentry, varlistterm, varlistitem, table_cell,
                        preformatted, list_item, begin_section, end_section,
                        xinclude, include, hard_space, eol, paragraph_end,
                        template_, template_id, template_formal_arg,
                        template_body, identifier, dummy_block, import,
                        inside_paragraph,
                        element_id, element_id_1_5, element_id_1_6;

        cl::symbols<>   paragraph_end_markups;

        phrase_grammar common;

        cl::rule<Scanner> const&
        start() const { return start_; }
    };

    template <typename Scanner>
    block_grammar::definition<Scanner>::definition(block_grammar const& self)
        : no_eols(true)
        , common(self.actions, no_eols)
    {
        using detail::var;
        quickbook::actions& actions = self.actions;

        if (self.skip_initial_spaces)
        {
            start_ =
                *(cl::blank_p | comment) >> blocks >> blank
                ;
        }
        else
        {
            start_ =
                blocks >> blank
                ;
        }

        blocks =
           *(   block_markup
            |   code
            |   list                            [actions.list]
            |   hr                              [actions.hr]
            |   +eol
            |   paragraph                       [actions.inside_paragraph]
            )
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
            cl::if_p(var(no_eols))
            [
                eol >> *cl::blank_p >> cl::eol_p
                                                // Make sure that we don't go
            ]                                   // past a single block, except
            ;                                   // when preformatted.

        // Follows after an alphanumeric identifier - ensures that it doesn't
        // match an empty space in the middle of the identifier.
        hard_space =
            (cl::eps_p - (cl::alnum_p | '_')) >> space  // must not be preceded by
            ;                                   // alpha-numeric or underscore

        comment =
            "[/" >> *(dummy_block | (cl::anychar_p - ']')) >> ']'
            ;

        dummy_block =
            '[' >> *(dummy_block | (cl::anychar_p - ']')) >> ']'
            ;

        hr =
            cl::str_p("----")
            >> *(cl::anychar_p - eol)
            >> +eol
            ;

        block_markup =
                '[' >> space
            >>  (   begin_section
                |   end_section
                |   headings
                |   blurb
                |   blockquote
                |   admonition
                |   preformatted
                |   def_macro
                |   table
                |   variablelist
                |   xinclude
                |   include
                |   import
                |   template_
                )
            >>  (   (space >> ']' >> +eol)
                |   cl::eps_p                   [actions.error]
                )
            ;
        
        element_id =
                ':'
            >>
                (
                    cl::if_p(qbk_since(105u))   [space]
                >>  (+(cl::alnum_p | '_'))      [cl::assign_a(actions.element_id)]
                |   cl::eps_p                   [actions.element_id_warning]
                                                [cl::assign_a(actions.element_id)]
                )
            | cl::eps_p                         [cl::assign_a(actions.element_id)]
            ;
        
        element_id_1_5 =
                cl::if_p(qbk_since(105u)) [
                    element_id
                ]
                .else_p [
                    cl::eps_p                   [cl::assign_a(actions.element_id)]
                ]
                ;

        element_id_1_6 =
                cl::if_p(qbk_since(106u)) [
                    element_id
                ]
                .else_p [
                    cl::eps_p                   [cl::assign_a(actions.element_id)]
                ]
                ;

        begin_section =
               "section"
            >> hard_space
            >> element_id
            >> space
            >> phrase                           [actions.begin_section]
            ;

        end_section =
            cl::str_p("endsect")                [actions.end_section]
            ;

        headings =
            h1 | h2 | h3 | h4 | h5 | h6 | h
            ;

        h = "heading" >> hard_space >> element_id_1_6 >> space >> phrase   [actions.h];
        h1 = "h1" >> hard_space >> element_id_1_6 >> space >> phrase       [actions.h1];
        h2 = "h2" >> hard_space >> element_id_1_6 >> space >> phrase       [actions.h2];
        h3 = "h3" >> hard_space >> element_id_1_6 >> space >> phrase       [actions.h3];
        h4 = "h4" >> hard_space >> element_id_1_6 >> space >> phrase       [actions.h4];
        h5 = "h5" >> hard_space >> element_id_1_6 >> space >> phrase       [actions.h5];
        h6 = "h6" >> hard_space >> element_id_1_6 >> space >> phrase       [actions.h6];

        static const bool true_ = true;
        static const bool false_ = false;

        inside_paragraph =
            phrase                              [actions.inside_paragraph]
            >> *(
                +eol >> phrase                  [actions.inside_paragraph]
            )
            ;

        blurb =
            "blurb" >> hard_space
            >> scoped_block(actions)[inside_paragraph]
                                                [actions.blurb]
            ;

        blockquote =
            ':' >> blank >>
            scoped_block(actions)[inside_paragraph]
                                                [actions.blockquote]
            ;

        admonition =
            "warning" >> hard_space >>
            scoped_block(actions)[inside_paragraph]
                                                [actions.warning]
            |
            "caution" >> hard_space >>
            scoped_block(actions)[inside_paragraph]
                                                [actions.caution]
            |
            "important" >> hard_space >>
            scoped_block(actions)[inside_paragraph]
                                                [actions.important]
            |
            "note" >> hard_space >>
            scoped_block(actions)[inside_paragraph]
                                                [actions.note]
            |
            "tip" >> hard_space >>
            scoped_block(actions)[inside_paragraph]
                                                [actions.tip]
            ;

        preformatted =
            "pre" >> hard_space                 [cl::assign_a(no_eols, false_)]
            >> !eol >> phrase                   [actions.preformatted]
            >> cl::eps_p                        [cl::assign_a(no_eols, true_)]
            ;

        macro_identifier =
            +(cl::anychar_p - (cl::space_p | ']'))
            ;

        def_macro =
            "def" >> hard_space
            >> macro_identifier                 [actions.macro_identifier]
            >> blank >> phrase                  [actions.macro_definition]
            ;

        identifier =
            (cl::alpha_p | '_') >> *(cl::alnum_p | '_')
            ;

        template_id =
            identifier | (cl::punct_p - (cl::ch_p('[') | ']'))
            ;

        template_ =
            "template"
            >> hard_space
            >> template_id                      [cl::assign_a(actions.template_identifier)]
                                                [cl::clear_a(actions.template_info)]
            >>
            !(
                space >> '['
                >> *(
                        space >> template_id    [cl::push_back_a(actions.template_info)]
                    )
                >> space >> ']'
            )
            >>  (   cl::eps_p(*cl::blank_p >> cl::eol_p)
                                                [cl::assign_a(actions.template_block, true_)]
                |   cl::eps_p                   [cl::assign_a(actions.template_block, false_)]
                )
            >>  template_body                   [actions.template_body]
            ;

        template_body =
           *(('[' >> template_body >> ']') | (cl::anychar_p - ']'))
            >> cl::eps_p(space >> ']')
            >> space
            ;

        variablelist =
            "variablelist"
            >>  (cl::eps_p(*cl::blank_p >> cl::eol_p) | hard_space)
            >>  (*(cl::anychar_p - eol))        [cl::assign_a(actions.table_title)]
            >>  +eol
            >>  *varlistentry
            >>  cl::eps_p                       [actions.variablelist]
            ;

        varlistentry =
            space
            >>  cl::ch_p('[')                   [actions.start_varlistentry]
            >>
            (
                (
                    varlistterm
                    >>  (   scoped_block(actions) [+varlistitem]
                                                [actions.varlistitem]
                        |   cl::eps_p           [actions.error]
                        )
                    >>  cl::ch_p(']')           [actions.end_varlistentry]
                    >>  space
                )
                | cl::eps_p                     [actions.error]
            )
            ;

        varlistterm =
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

        varlistitem =
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

        table =
            "table"
            >>  (cl::eps_p(*cl::blank_p >> cl::eol_p) | hard_space)
            >> element_id_1_5
            >>  (cl::eps_p(*cl::blank_p >> cl::eol_p) | space)
            >>  (*(cl::anychar_p - eol))        [cl::assign_a(actions.table_title)]
            >>  +eol
            >>  *table_row
            >>  cl::eps_p                       [actions.table]
            ;

        table_row =
            space
            >>  cl::ch_p('[')                   [actions.start_row]
            >>
            (
                (
                    *table_cell
                    >>  cl::ch_p(']')           [actions.end_row]
                    >>  space
                )
                | cl::eps_p                     [actions.error]
            )
            ;

        table_cell =
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

        xinclude =
               "xinclude"
            >> hard_space
            >> (*(cl::anychar_p -
                    phrase_end))                [actions.xinclude]
            ;

        import =
               "import"
            >> hard_space
            >> (*(cl::anychar_p -
                    phrase_end))                [actions.import]
            ;

        include =
               "include"
            >> hard_space
            >>
           !(
                ':'
                >> (*((cl::alnum_p | '_') - cl::space_p))
                                                [cl::assign_a(actions.include_doc_id)]
                >> space
            )
            >> (*(cl::anychar_p -
                    phrase_end))                [actions.include]
            ;

        code =
            (
                code_line
                >> *(*blank_line >> code_line)
            )                                   [actions.code]
            >> *eol
            ;

        code_line =
            cl::blank_p >> *(cl::anychar_p - cl::eol_p) >> cl::eol_p
            ;

        blank_line =
            *cl::blank_p >> cl::eol_p
            ;

        list =
            cl::eps_p(cl::ch_p('*') | '#') >>
           +(
                (*cl::blank_p
                >> (cl::ch_p('*') | '#'))       [actions.list_format]
                >> *cl::blank_p
                >> list_item
            )                                   [actions.list_item]
            ;

        list_item =
           *(   common
            |   (cl::anychar_p -
                    (   cl::eol_p >> *cl::blank_p >> cl::eps_p(cl::ch_p('*') | '#')
                    |   (eol >> eol)
                    )
                )                               [actions.plain_char]
            )
            >> +eol
            ;

        paragraph_end_markups =
            "section", "endsect", "h1", "h2", "h3", "h4", "h5", "h6",
            "blurb", ":", "pre", "def", "table", "include", "xinclude",
            "variablelist", "import", "template", "warning", "caution",
            "important", "note", "tip", ":"
            ;

        paragraph_end =
            '[' >> space >> paragraph_end_markups >> hard_space | eol >> *cl::blank_p >> cl::eol_p
            ;

        paragraph =
           +(   common
            |   (cl::anychar_p -                // Make sure we don't go past
                    paragraph_end               // a single block.
                )                               [actions.plain_char]
            )
            >> (cl::eps_p('[') | +eol)
            ;

        phrase =
           *(   common
            |   comment
            |   (cl::anychar_p -
                    phrase_end)                 [actions.plain_char]
            )
            ;
    }

    cl::parse_info<iterator> call_parse(
        iterator& first, iterator last, block_grammar& g)
    {
        return boost::spirit::classic::parse(first, last, g);
    }
}
