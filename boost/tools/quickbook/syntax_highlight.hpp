/*=============================================================================
    Copyright (c) 2002 2004 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_QUICKBOOK_SYNTAX_HIGHLIGHT_HPP)
#define BOOST_SPIRIT_QUICKBOOK_SYNTAX_HIGHLIGHT_HPP

#include <boost/spirit/core.hpp>
#include <boost/spirit/utility/confix.hpp>
#include <boost/spirit/utility/chset.hpp>
#include <boost/spirit/symbols/symbols.hpp>
#include <boost/spirit/utility/escape_char.hpp>
#include "./phrase.hpp"

namespace quickbook
{
    using namespace boost::spirit;

    // Grammar for C++ highlighting
    template <
        typename Process
      , typename Space
      , typename Macro
      , typename DoMacro
      , typename PreEscape
      , typename PostEscape
      , typename EscapeActions
      , typename Unexpected
      , typename Out>
    struct cpp_highlight
    : public grammar<cpp_highlight<Process, Space, Macro, DoMacro, PreEscape, PostEscape, EscapeActions, Unexpected, Out> >
    {
        cpp_highlight(Out& out, Macro const& macro, DoMacro do_macro, EscapeActions& escape_actions)
        : out(out), macro(macro), do_macro(do_macro), escape_actions(escape_actions) {}

        template <typename Scanner>
        struct definition
        {
            definition(cpp_highlight const& self)
                : common(self.escape_actions, unused)
                , unused(false)
            {
                program
                    =
                    *(  (+space_p)      [Space(self.out)]
                    |   self.macro      [self.do_macro]
                    |   escape
                    |   preprocessor    [Process("preprocessor", self.out)]
                    |   comment         [Process("comment", self.out)]
                    |   keyword         [Process("keyword", self.out)]
                    |   identifier      [Process("identifier", self.out)]
                    |   special         [Process("special", self.out)]
                    |   string_         [Process("string", self.out)]
                    |   char_           [Process("char", self.out)]
                    |   number          [Process("number", self.out)]
                    |   anychar_p       [Unexpected(self.out)]
                    )
                    ;

                qbk_phrase =
                   *(   common
                    |   (anychar_p - str_p("``"))   [self.escape_actions.plain_char]
                    )
                    ;

                escape
                    = str_p("``")           [PreEscape(self.escape_actions, save)]
                    >>  (
                            (+(anychar_p - "``") >> eps_p("``"))
                            & qbk_phrase
                        )
                    >> str_p("``")          [PostEscape(self.out, self.escape_actions, save)]
                    ;

                preprocessor
                    =   '#' >> ((alpha_p | '_') >> *(alnum_p | '_'))
                    ;

                comment
                    =   comment_p("//") | comment_p("/*", "*/")
                    ;

                keyword
                    =   keyword_ >> (eps_p - (alnum_p | '_'))
                    ;   // make sure we recognize whole words only

                keyword_
                    =   "and_eq", "and", "asm", "auto", "bitand", "bitor",
                        "bool", "break", "case", "catch", "char", "class",
                        "compl", "const_cast", "const", "continue", "default",
                        "delete", "do", "double", "dynamic_cast",  "else",
                        "enum", "explicit", "export", "extern", "false",
                        "float", "for", "friend", "goto", "if", "inline",
                        "int", "long", "mutable", "namespace", "new", "not_eq",
                        "not", "operator", "or_eq", "or", "private",
                        "protected", "public", "register", "reinterpret_cast",
                        "return", "short", "signed", "sizeof", "static",
                        "static_cast", "struct", "switch", "template", "this",
                        "throw", "true", "try", "typedef", "typeid",
                        "typename", "union", "unsigned", "using", "virtual",
                        "void", "volatile", "wchar_t", "while", "xor_eq", "xor"
                    ;

                special
                    =   +chset_p("~!%^&*()+={[}]:;,<.>?/|\\-")
                    ;

                string_
                    =   !as_lower_d['l'] >> confix_p('"', *c_escape_ch_p, '"')
                    ;

                char_
                    =   !as_lower_d['l'] >> confix_p('\'', *c_escape_ch_p, '\'')
                    ;

                number
                    =   (
                            as_lower_d["0x"] >> hex_p
                        |   '0' >> oct_p
                        |   real_p
                        )
                        >>  *as_lower_d[chset_p("ldfu")]
                    ;

                identifier
                    =   (alpha_p | '_') >> *(alnum_p | '_')
                    ;
            }

            rule<Scanner>   program, macro, preprocessor, comment, special, string_, 
                            char_, number, identifier, keyword, qbk_phrase, escape;

            symbols<> keyword_;
            phrase_grammar<EscapeActions> common;
            std::string save;
            bool unused;

            rule<Scanner> const&
            start() const { return program; }
        };

        Out& out;
        Macro const& macro;
        DoMacro do_macro;
        EscapeActions& escape_actions;
    };

    // Grammar for Python highlighting
    // See also: The Python Reference Manual
    // http://docs.python.org/ref/ref.html
    template <
        typename Process
      , typename Space
      , typename Macro
      , typename DoMacro
      , typename PreEscape
      , typename PostEscape
      , typename EscapeActions
      , typename Unexpected
      , typename Out>
    struct python_highlight
    : public grammar<python_highlight<Process, Space, Macro, DoMacro, PreEscape, PostEscape, EscapeActions, Unexpected, Out> >
    {
        python_highlight(Out& out, Macro const& macro, DoMacro do_macro, EscapeActions& escape_actions)
        : out(out), macro(macro), do_macro(do_macro), escape_actions(escape_actions) {}

        template <typename Scanner>
        struct definition
        {
            definition(python_highlight const& self)
                : common(self.escape_actions, unused)
                , unused(false)
            {
                program
                    =
                    *(  (+space_p)      [Space(self.out)]
                    |   self.macro      [self.do_macro]
                    |   escape          
                    |   comment         [Process("comment", self.out)]
                    |   keyword         [Process("keyword", self.out)]
                    |   identifier      [Process("identifier", self.out)]
                    |   special         [Process("special", self.out)]
                    |   string_         [Process("string", self.out)]
                    |   number          [Process("number", self.out)]
                    |   anychar_p       [Unexpected(self.out)]
                    )
                    ;

                qbk_phrase =
                   *(   common
                    |   (anychar_p - str_p("``"))   [self.escape_actions.plain_char]
                    )
                    ;

                escape
                    = str_p("``")           [PreEscape(self.escape_actions, save)]
                    >>  (
                            (+(anychar_p - "``") >> eps_p("``"))
                            & qbk_phrase
                        )
                    >> str_p("``")          [PostEscape(self.out, self.escape_actions, save)]
                    ;

                comment
                    =   comment_p("#")
                    ;

                keyword
                    =   keyword_ >> (eps_p - (alnum_p | '_'))
                    ;   // make sure we recognize whole words only

                keyword_
                    =
                    "and",       "del",       "for",       "is",        "raise",    
                    "assert",    "elif",      "from",      "lambda",    "return",   
                    "break",     "else",      "global",    "not",       "try",  
                    "class",     "except",    "if",        "or",        "while",    
                    "continue",  "exec",      "import",    "pass",      "yield",   
                    "def",       "finally",   "in",        "print",

                    // Technically "as" and "None" are not yet keywords (at Python
                    // 2.4). They are destined to become keywords, and we treat them 
                    // as such for syntax highlighting purposes.
                    
                    "as", "None"
                    ;

                special
                    =   +chset_p("~!%^&*()+={[}]:;,<.>/|\\-")
                    ;

                string_prefix
                    =    as_lower_d[str_p("u") >> ! str_p("r")]
                    ;
                
                string_
                    =   ! string_prefix >> (long_string | short_string)
                    ;

                short_string
                    =   confix_p('\'', * c_escape_ch_p, '\'') |
                        confix_p('"', * c_escape_ch_p, '"')    
                    ;
            
                long_string
                    // Note: the "str_p" on the next two lines work around
                    // an INTERNAL COMPILER ERROR when using VC7.1
                    =   confix_p(str_p("'''"), * lex_escape_ch_p, "'''") |
                        confix_p(str_p("\"\"\""), * lex_escape_ch_p, "\"\"\"")
                    ;
                
                number
                    =   (
                            as_lower_d["0x"] >> hex_p
                        |   '0' >> oct_p
                        |   real_p
                        )
                        >>  *as_lower_d[chset_p("lj")]
                    ;

                identifier
                    =   (alpha_p | '_') >> *(alnum_p | '_')
                    ;
            }

            rule<Scanner>   program, macro, comment, special, string_, string_prefix, 
                            short_string, long_string, number, identifier, keyword, 
                            qbk_phrase, escape;

            symbols<> keyword_;
            phrase_grammar<EscapeActions> common;
            std::string save;
            bool unused;

            rule<Scanner> const&
            start() const { return program; }
        };

        Out& out;
        Macro const& macro;
        DoMacro do_macro;
        EscapeActions& escape_actions;
    };
}

#endif // BOOST_SPIRIT_QUICKBOOK_SYNTAX_HIGHLIGHT_HPP
