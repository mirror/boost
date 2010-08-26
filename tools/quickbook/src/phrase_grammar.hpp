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

#include "./grammar.hpp"

namespace quickbook
{
    using namespace boost::spirit::classic;

        template <typename Scanner>
        struct phrase_grammar::definition
        {
            definition(phrase_grammar const& self);

            rule<Scanner>   space, blank, comment, phrase, phrase_markup, image,
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

            rule<Scanner> const&
            start() const { return common; }
        };
}

#endif // BOOST_SPIRIT_QUICKBOOK_PHRASE_HPP

