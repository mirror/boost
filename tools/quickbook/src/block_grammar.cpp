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

namespace quickbook
{
    namespace cl = boost::spirit::classic;

    struct block_grammar_local
    {
        cl::rule<scanner>
                        top_level, blocks, paragraph_separator,
                        block_markup, block_markup_start,
                        code, code_line, blank_line,
                        space, blank, comment, dummy_block, hr,
                        list, ordered_list, list_item, hard_space, eol;

        cl::rule<scanner> block_keyword_rule;
    };

    void quickbook_grammar::impl::init_block(bool skip_initial_spaces)
    {
        using detail::var;

        block_grammar_local& local = store_.create();

        if (skip_initial_spaces)
        {
            block_start =
                *(cl::blank_p | local.comment) >> local.top_level >> local.blank
                ;
        }
        else
        {
            block_start =
                local.top_level >> local.blank
                ;
        }

        local.top_level
            =   local.blocks
            >>  *(
                    local.block_markup >> local.blocks
                |   local.paragraph_separator >> local.blocks
                |   common
                |   cl::space_p                 [actions.space_char]
                |   cl::anychar_p               [actions.plain_char]
                );

        local.blocks =
           *(   local.code
            |   local.list                      [actions.list]
            |   local.hr                        [actions.hr]
            |   +local.eol
            )
            ;

        local.paragraph_separator
            =   cl::eol_p
            >> *cl::blank_p
            >>  cl::eol_p                       [actions.inside_paragraph]
            ;

        local.space =
            *(cl::space_p | local.comment)
            ;

        local.blank =
            *(cl::blank_p | local.comment)
            ;

        local.eol = local.blank >> cl::eol_p
            ;

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
            =   local.block_markup_start        [actions.inside_paragraph]
            >>  (   local.block_keyword_rule
                >>  (   (local.space >> ']' >> +local.eol)
                    |   cl::eps_p               [actions.error]
                    )
                |   cl::eps_p                   [actions.error]
                )
            ;

        local.block_markup_start
            =   '[' >> local.space
            >>  (   block_keyword_rules         [detail::assign_rule(local.block_keyword_rule)]
                >>  (cl::eps_p - (cl::alnum_p | '_'))
                |   block_symbol_rules          [detail::assign_rule(local.block_keyword_rule)]
                )
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
                    (   cl::eol_p >> *cl::blank_p
                    >>  (cl::ch_p('*') | '#' | cl::eol_p)
                    )
                )                               [actions.plain_char]
            )
            >> +local.eol
            ;
    }
}
