/*=============================================================================
    Copyright (c) 2005 Joel de Guzman
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#include "./post_process.hpp"
#include <boost/spirit/core.hpp>
#include <boost/bind.hpp>
#include <set>
#include <stack>
#include <cctype>

namespace quickbook
{
    using namespace boost::spirit;
    using boost::bind;
    typedef std::string::const_iterator iter_type;
    
    struct printer
    {
        printer(std::ostream& out, int& indent, int linewidth)
            : out(out), indent_(indent), linewidth(linewidth)
            , column(0), prev(0), in_string(false) {}
                
        void indent()
        {
            assert(indent_ > 0); // this should not happen
            for (int i = 0; i < indent_; ++i)
                out << ' ';
            column = indent_;
        }
        
        void cr()
        {
            out << '\n';
            indent();
        }
        
        void align_indent()
        {
            // make sure we are at the proper indent position
            if (column != indent_)
                cr();
        }

        void print(char ch)
        {
            if (ch == '"' && prev != '\\')
                in_string = !in_string; // don't cut strings! $$$ Fix Me. Do the right thing! $$$

            if (!in_string && std::isspace(ch))
            {
                if (!std::isspace(prev))
                {
                    if (column > linewidth)
                    {
                        cr();
                    }
                    else
                    {
                        ++column;
                        out << ' ';
                    }
                }
            }
            else
            {
                if (ch == '<' && column > linewidth)
                    cr();
                else if (prev == '>' && column > linewidth)
                    cr();
                out << ch;
                ++column;
            }
            
            prev = ch;
        }

        void         
        print(iter_type f, iter_type l)
        {
            for (iter_type i = f; i != l; ++i)
                print(*i);
        }
        
        char prev;
        std::ostream& out;
        int& indent_;
        int column;
        bool in_string;
        int linewidth;
    };    
    
    struct tidy_compiler
    {
        tidy_compiler(std::ostream& out, int linewidth)
            : out(out), indent(0), printer_(out, indent, linewidth)
        {
            flow_tags.insert("anchor");
            flow_tags.insert("phrase");
            flow_tags.insert("literal");
            flow_tags.insert("bridgehead");
            flow_tags.insert("entry");
            flow_tags.insert("emphasis");
            flow_tags.insert("ulink");
            flow_tags.insert("link");
            flow_tags.insert("varlistentry");
            flow_tags.insert("term");
            flow_tags.insert("functionname");
            flow_tags.insert("classname");
            flow_tags.insert("methodname");
            flow_tags.insert("enumname");
            flow_tags.insert("headername");
            flow_tags.insert("inlinemediaobject");
            flow_tags.insert("imageobject");
            flow_tags.insert("imagedata");
            flow_tags.insert("title");
            flow_tags.insert("xi");
            flow_tags.insert("firstname");
            flow_tags.insert("surname");
            flow_tags.insert("year");
            flow_tags.insert("holder");
            flow_tags.insert("sbr");
        }
        
        bool is_flow_tag(std::string const& tag)
        {
            return flow_tags.find(tag) != flow_tags.end();
        }

        std::set<std::string> flow_tags;
        std::stack<std::string> tags;
        std::ostream& out;
        int indent;
        printer printer_;
        std::string current_tag;
    };    
    
    struct tidy_grammar : grammar<tidy_grammar>
    {
        tidy_grammar(tidy_compiler& state, int tab)
            : state(state), tab(tab) {}

        template <typename Scanner>
        struct definition
        {
            definition(tidy_grammar const& self)
            {
                tag = (lexeme_d[+alnum_p])  [bind(&tidy_grammar::do_tag, &self, _1, _2)];

                code =
                        "<programlisting>"
                    >>  *(anychar_p - "</programlisting>")
                    >>  "</programlisting>"
                    ;

                start_tag = '<' >> tag >> *(anychar_p - '>') >> '>';
                start_end_tag = 
                        '<' >> tag >> *(anychar_p - ('/' | ch_p('>'))) >> "/>"
                    |   "<?" >> tag >> *(anychar_p - '?') >> "?>"
                    |   "<!" >> tag >> *(anychar_p - '>') >> '>'
                    ;
                content = lexeme_d[ +(anychar_p - '<') ];
                end_tag = "</" >> +(anychar_p - '>') >> '>';

                markup = 
                        code            [bind(&tidy_grammar::do_code, &self, _1, _2)]
                    |   start_end_tag   [bind(&tidy_grammar::do_start_end_tag, &self, _1, _2)]
                    |   start_tag       [bind(&tidy_grammar::do_start_tag, &self, _1, _2)]
                    |   end_tag         [bind(&tidy_grammar::do_end_tag, &self, _1, _2)]
                    |   content         [bind(&tidy_grammar::do_content, &self, _1, _2)]
                    ;

                tidy = +markup;
            }

            rule<Scanner> const&
            start() { return tidy; }

            rule<Scanner>   tidy, tag, start_tag, start_end_tag,
                            content, end_tag, markup, code;
        };

        void do_code(iter_type f, iter_type l) const
        {
            state.out << '\n';
            state.out << std::string(f, l);
            state.out << '\n';
            state.printer_.indent();
        }

        void do_tag(iter_type f, iter_type l) const
        {
            state.current_tag = std::string(f, l);
        }

        void do_start_end_tag(iter_type f, iter_type l) const
        {
            bool is_flow_tag = state.is_flow_tag(state.current_tag);
            if (!is_flow_tag)
                state.printer_.align_indent();
            state.printer_.print(f, l);
            if (!is_flow_tag)
                state.printer_.cr();
        }

        void do_start_tag(iter_type f, iter_type l) const
        {
            state.tags.push(state.current_tag);                     
            bool is_flow_tag = state.is_flow_tag(state.current_tag);
            if (!is_flow_tag)
                state.printer_.align_indent();
            state.printer_.print(f, l);
            if (!is_flow_tag)
            {
                state.indent += tab;
                state.printer_.cr();
            }
        }

        void do_content(iter_type f, iter_type l) const
        {
            state.printer_.print(f, l);
        }

        void do_end_tag(iter_type f, iter_type l) const
        {
            bool is_flow_tag = state.is_flow_tag(state.tags.top());
            if (!is_flow_tag)
            {
                state.indent -= tab;
                state.printer_.cr();
            }
            state.printer_.print(f, l);
            state.tags.pop();                     
        }
        
        tidy_compiler& state;
        int tab;
    };

    void post_process(
        std::string const& in
      , std::ostream& out
      , int indent
      , int linewidth)
    {
        if (indent == -1)
            indent = 2;         // set default to 2
        if (linewidth == -1)
            linewidth = 80;     // set default to 80

        tidy_compiler state(out, linewidth);
        tidy_grammar g(state, indent);
        parse(in.begin(), in.end(), g, space_p);
    }
}

