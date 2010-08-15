/*=============================================================================
    Copyright (c) 2006 Joel de Guzman
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_QUICKBOOK_CODE_SNIPPET_HPP)
#define BOOST_SPIRIT_QUICKBOOK_CODE_SNIPPET_HPP

#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_actor.hpp>
#include <boost/bind.hpp>
#include "./detail/template_stack.hpp"
#include "./detail/actions.hpp"

namespace quickbook
{
    struct code_snippet_actions
    {
        code_snippet_actions(std::vector<template_symbol>& storage,
                                 std::string const& doc_id,
                                 char const* source_type)
            : storage(storage)
            , doc_id(doc_id)
            , source_type(source_type)
        {}

        void pass_thru(iterator first, iterator last);
        void escaped_comment(iterator first, iterator last);
        void compile(iterator first, iterator last);
        void callout(iterator first, iterator last);

        std::string code;
        std::string snippet;
        std::string id;
        std::vector<template_body> callouts;
        std::vector<template_symbol>& storage;
        std::string const doc_id;
        char const* const source_type;
    };

    struct python_code_snippet_grammar
        : grammar<python_code_snippet_grammar>
    {
        typedef code_snippet_actions actions_type;
  
        python_code_snippet_grammar(actions_type & actions)
            : actions(actions)
        {}

        template <typename Scanner>
        struct definition
        {
            typedef code_snippet_actions actions_type;
            
            definition(python_code_snippet_grammar const& self)
            {
                actions_type& actions = self.actions;
            
                start_ =
                    +(
                            snippet                 [boost::bind(&actions_type::compile, &actions, _1, _2)]
                        |   anychar_p
                    )
                    ;

                identifier =
                    (alpha_p | '_') >> *(alnum_p | '_')
                    ;

                snippet =
                    "#[" >> *space_p
                    >> identifier                   [assign_a(actions.id)]
                    >> (*(code_elements - "#]"))
                    >> "#]"
                    ;

                code_elements =
                        escaped_comment
                    |   ignore
                    |   (anychar_p - "#]")         [boost::bind(&actions_type::pass_thru, &actions, _1, _2)]
                    ;

                ignore =
                        *blank_p >> "#<-"
                        >> (*(anychar_p - "#->"))
                        >> "#->" >> *blank_p >> eol_p
                    |   "\"\"\"<-\"\"\""
                        >> (*(anychar_p - "\"\"\"->\"\"\""))
                        >> "\"\"\"->\"\"\""
                    |   "\"\"\"<-"
                        >> (*(anychar_p - "->\"\"\""))
                        >> "->\"\"\""
                    ;

                escaped_comment =
                        *space_p >> "#`"
                        >> ((*(anychar_p - eol_p))
                            >> eol_p)               [boost::bind(&actions_type::escaped_comment, &actions, _1, _2)]
                    |   *space_p >> "\"\"\"`"
                        >> (*(anychar_p - "\"\"\""))    [boost::bind(&actions_type::escaped_comment, &actions, _1, _2)]
                        >> "\"\"\""
                    ;
            }

            rule<Scanner>
                start_, snippet, identifier, code_elements, escaped_comment,
                ignore;

            rule<Scanner> const&
            start() const { return start_; }
        };

        actions_type& actions;
    };  

    struct cpp_code_snippet_grammar
        : grammar<cpp_code_snippet_grammar>
    {
        typedef code_snippet_actions actions_type;
  
        cpp_code_snippet_grammar(actions_type & actions)
            : actions(actions)
        {}

        template <typename Scanner>
        struct definition
        {
            definition(cpp_code_snippet_grammar const& self)
            {
                actions_type& actions = self.actions;
            
                start_ =
                    +(
                            snippet                 [boost::bind(&actions_type::compile, &actions, _1, _2)]
                        |   anychar_p
                    )
                    ;

                identifier =
                    (alpha_p | '_') >> *(alnum_p | '_')
                    ;

                snippet =
                        "//[" >> *space_p
                        >> identifier                   [assign_a(actions.id)]
                        >> (*(code_elements - "//]"))
                        >> "//]"
                    |
                        "/*[" >> *space_p
                        >> identifier                   [assign_a(actions.id)]
                        >> *space_p >> "*/"
                        >> (*(code_elements - "/*]*"))
                        >> "/*]*/"
                    ;

                code_elements =
                        escaped_comment
                    |   ignore
                    |   line_callout
                    |   inline_callout
                    |   (anychar_p - "//]" - "/*]*/")    [boost::bind(&actions_type::pass_thru, &actions, _1, _2)]
                    ;

                inline_callout =
                    "/*<"
                    >> *space_p
                    >> (*(anychar_p - ">*/"))       [boost::bind(&actions_type::callout, &actions, _1, _2)]
                    >> ">*/"
                    ;

                line_callout =
                    "/*<<"
                    >> *space_p
                    >> (*(anychar_p - ">>*/"))      [boost::bind(&actions_type::callout, &actions, _1, _2)]
                    >> ">>*/"
                    >> *space_p
                    ;

                ignore =
                        *blank_p >> "//<-"
                        >> (*(anychar_p - "//->"))
                        >> "//->" >> *blank_p >> eol_p
                    |   "/*<-*/"
                        >> (*(anychar_p - "/*->*/"))
                        >> "/*->*/"
                    |   "/*<-"
                        >> (*(anychar_p - "->*/"))
                        >> "->*/"
                    ;

                escaped_comment =
                        *space_p >> "//`"
                        >> ((*(anychar_p - eol_p))
                            >> eol_p)               [boost::bind(&actions_type::escaped_comment, &actions, _1, _2)]
                    |   *space_p >> "/*`"
                        >> (*(anychar_p - "*/"))    [boost::bind(&actions_type::escaped_comment, &actions, _1, _2)]
                        >> "*/"
                    ;
            }

            rule<Scanner>
                start_, snippet, identifier, code_elements, escaped_comment,
                inline_callout, line_callout, ignore;

            rule<Scanner> const&
            start() const { return start_; }
        };

        actions_type& actions;
    };
}

#endif // BOOST_SPIRIT_QUICKBOOK_CODE_SNIPPET_HPP

