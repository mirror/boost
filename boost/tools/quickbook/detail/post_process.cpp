/*=============================================================================
    Copyright (c) 2005 Joel de Guzman
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#include "./post_process.hpp"
#include "./utils.hpp"
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
        printer(std::string& out, int& current_indent, int linewidth)
            : prev(0), out(out), current_indent(current_indent) , column(0)
            , in_string(false), linewidth(linewidth) {}
                
        void indent()
        {
            BOOST_ASSERT(current_indent >= 0); // this should not happen!
            for (int i = 0; i < current_indent; ++i)
                out += ' ';
            column = current_indent;
        }

        void break_line()
        {
            out.erase(out.find_last_not_of(' ')+1); // trim trailing spaces
            out += '\n';
            indent();
        }
        
        bool line_is_empty() const
        {
            for (iter_type i = out.end()-(column-current_indent); i != out.end(); ++i)
            {
                if (*i != ' ')
                    return false;
            }
            return true;
        }
        
        void align_indent()
        {
            // make sure we are at the proper indent position
            if (column != current_indent)
            {
                if (column > current_indent)
                {
                    if (line_is_empty())
                    {
                        // trim just enough trailing spaces down to current_indent position
                        out.erase(out.end()-(column-current_indent), out.end());
                        column = current_indent;
                    }
                    else
                    {
                        // nope, line is not empty. do a hard CR
                        break_line();
                    }
                }
                else
                {
                    // will this happen? (i.e. column <= current_indent)
                    while (column != current_indent) 
                    {
                        out += ' ';
                        ++column;
                    }
                }
            }
        }

        void print(char ch)
        {
            // Print a char. Attempt to break the line if we are exceeding
            // the target linewidth. The linewidth is not an absolute limit.
            // There are many cases where a line will exceed the linewidth 
            // and there is no way to properly break the line. Preformatted
            // code that exceeds the linewidth are examples. We cannot break
            // preformatted code. We shall not attempt to be very strict with
            // line breaking. What's more important is to have a reproducable
            // output (i.e. processing two logically equivalent xml files 
            // results in two lexically equivalent xml files). *** pretty 
            // formatting is a secondary goal ***

            // Strings will occur only in tag attributes. Normal content
            // will have &quot; instead. We shall deal only with tag 
            // attributes here.
            if (ch == '"')
                in_string = !in_string; // don't break strings!

            if (!in_string && std::isspace(static_cast<unsigned char>(ch)))
            {
                // we can break spaces if they are not inside strings
                if (!std::isspace(static_cast<unsigned char>(prev)))
                {
                    if (column >= linewidth)
                    {
                        break_line();
                        if (column == 0 && ch == ' ')
                        {
                            ++column;
                            out += ' ';
                        }
                    }
                    else
                    {
                        ++column;
                        out += ' ';
                    }
                }
            }
            else
            {
                // we can break tag boundaries and stuff after 
                // delimiters if they are not inside strings
                // and *only-if* the preceding char is a space
                if (!in_string 
                    && column >= linewidth 
                    && (ch == '<' && std::isspace(static_cast<unsigned char>(prev))))
                    break_line();
                out += ch;
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

        void         
        print_tag(iter_type f, iter_type l, bool is_flow_tag)
        {
            if (is_flow_tag)
            {
                print(f, l);
            }
            else
            {
                // This is not a flow tag, so, we're going to do a 
                // carriage return anyway. Let us remove extra right
                // spaces.
                std::string str(f, l);
                BOOST_ASSERT(f != l); // this should not happen
                iter_type i = str.end();
                while (i != str.begin() && std::isspace(static_cast<unsigned char>(*(i-1))))
                    --i;
                print(str.begin(), i);
            }            
        }

        char prev;
        std::string& out;
        int& current_indent;
        int column;
        bool in_string;
        int linewidth;
    };    
    
    struct tidy_compiler
    {
        tidy_compiler(std::string& out, int linewidth)
            : out(out), current_indent(0), printer_(out, current_indent, linewidth)
        {
            flow_tags.insert("anchor");
            flow_tags.insert("phrase");
            flow_tags.insert("literal");
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
            flow_tags.insert("quote");
            flow_tags.insert("code");
            flow_tags.insert("type");
            flow_tags.insert("paramtype");

        }
        
        bool is_flow_tag(std::string const& tag)
        {
            return flow_tags.find(tag) != flow_tags.end();
        }

        std::set<std::string> flow_tags;
        std::stack<std::string> tags;
        std::string& out;
        int current_indent;
        printer printer_;
        std::string current_tag;
    };    
    
    struct tidy_grammar : grammar<tidy_grammar>
    {
        tidy_grammar(tidy_compiler& state, int indent)
            : state(state), indent(indent) {}

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

                // What's the business of lexeme_d['>' >> *space_p]; ?
                // It is there to preserve the space after the tag that is
                // otherwise consumed by the space_p skipper.
                
                escape = str_p("<!--quickbook-escape-prefix-->") >> 
                    *(anychar_p - str_p("<!--quickbook-escape-postfix-->"))
                     >> str_p("<!--quickbook-escape-postfix-->")
                    ;
                
                start_tag = '<' >> tag >> *(anychar_p - '>') >> lexeme_d['>' >> *space_p];
                start_end_tag = 
                        '<' >> tag >> *(anychar_p - ('/' | ch_p('>'))) >> lexeme_d["/>" >> *space_p]
                    |   "<?" >> tag >> *(anychar_p - '?') >> lexeme_d["?>" >> *space_p]
                    |   "<!--" >> tag >> *(anychar_p - "-->") >> lexeme_d["-->" >> *space_p]
                    |   "<!" >> tag >> *(anychar_p - '>') >> lexeme_d['>' >> *space_p]
                    ;
                content = lexeme_d[ +(anychar_p - '<') ];
                end_tag = "</" >> +(anychar_p - '>') >> lexeme_d['>' >> *space_p];

                markup = 
                        escape          [bind(&tidy_grammar::do_escape, &self, _1, _2)]
                    |   code            [bind(&tidy_grammar::do_code, &self, _1, _2)]
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
                            content, end_tag, markup, code, escape;
        };

        void do_escape(iter_type f, iter_type l) const
        {
            state.out += '\n';
            while (f != l && std::isspace(*f))
                ++f;
            for (iter_type i = f; i != l; ++i)
                state.out += *i;
            state.out += '\n';
            state.printer_.indent();
        }

        void do_code(iter_type f, iter_type l) const
        {
            state.out += '\n';
            // print the string taking care of line 
            // ending CR/LF platform issues
            for (iter_type i = f; i != l; ++i)
            {
                if (*i == '\n')
                {
                    state.out += '\n';
                    ++i;
                    if (i != l && *i != '\r')
                        state.out += *i;
                }
                else if (*i == '\r')
                {
                    state.out += '\n';
                    ++i;
                    if (i != l && *i != '\n')
                        state.out += *i;
                }
                else
                {
                    state.out += *i;
                }
            }
            state.out += '\n';
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
            state.printer_.print_tag(f, l, is_flow_tag);
            if (!is_flow_tag)
                state.printer_.break_line();
        }

        void do_start_tag(iter_type f, iter_type l) const
        {
            state.tags.push(state.current_tag);                     
            bool is_flow_tag = state.is_flow_tag(state.current_tag);
            if (!is_flow_tag)
                state.printer_.align_indent();
            state.printer_.print_tag(f, l, is_flow_tag);
            if (!is_flow_tag)
            {
                state.current_indent += indent;
                state.printer_.break_line();
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
                state.current_indent -= indent;
                state.printer_.align_indent();
            }
            state.printer_.print_tag(f, l, is_flow_tag);
            if (!is_flow_tag)
                state.printer_.break_line();
            state.tags.pop();                     
        }
        
        tidy_compiler& state;
        int indent;
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

        try
        {
            std::string tidy;
            tidy_compiler state(tidy, linewidth);
            tidy_grammar g(state, indent);
            parse_info<iter_type> r = parse(in.begin(), in.end(), g, space_p);
            BOOST_ASSERT(r.full); // this should not happen!
            out << tidy;
        }
        
        catch(...)
        {
            ::quickbook::detail::outerr("",0)
            <<  "Error Post Processing Failed. " 
            << std::endl;
            out << in;
        }
    }
}

