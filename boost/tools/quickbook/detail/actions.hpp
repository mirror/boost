/*=============================================================================
    Copyright (c) 2002 2004 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_QUICKBOOK_ACTIONS_HPP)
#define BOOST_SPIRIT_QUICKBOOK_ACTIONS_HPP

#include <time.h>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <sstream>
#include <boost/spirit/iterator/position_iterator.hpp>
#include "../syntax_highlight.hpp"
#include "utils.hpp"

namespace quickbook
{
    struct error_action
    {
        // Prints an error message to std::cerr

        template <typename Iterator>
        void operator()(Iterator const& first, Iterator const& /*last*/) const
        {
            boost::spirit::file_position const pos = first.get_position();
            std::cerr
                << "Syntax Error at \"" << pos.file
                << "\" line " << pos.line
                << ", column " << pos.column << ".\n";
        }
    };

    struct phrase_action
    {
        //  Handles paragraph, h1, h2, h3, h4, h5, h6,
        //  blurb, blockquote, preformatted, list_item,
        //  unordered_list, ordered_list

        phrase_action(
            std::ostream&       out,
            std::stringstream&  phrase,
            std::string&        section_id,
            std::string const&  pre,
            std::string const&  post,
            bool                anchor = false)
        : out(out)
        , phrase(phrase)
        , section_id(section_id)
        , pre(pre)
        , post(post)
        , anchor(anchor) {}

        template <typename Iterator>
        void operator()(Iterator const& first, Iterator const& last) const
        {
            if (out)
            {
                std::string  str = phrase.str();
                if (anchor)
                    out << "<anchor id=\""
                        << section_id << '.'
                        << detail::make_identifier(str.begin(), str.end())
                        << "\" />";
                phrase.str(std::string());
                out << pre << str << post;
            }
        }

        std::ostream&       out;
        std::stringstream&  phrase;
        std::string&        section_id;
        std::string         pre;
        std::string         post;
        bool                anchor;
    };

    struct simple_phrase_action
    {
        //  Handles simple text formats

        simple_phrase_action(
            std::ostream&       out,
            std::string const&  pre,
            std::string const&  post)
        : out(out)
        , pre(pre)
        , post(post) {}

        template <typename Iterator>
        void operator()(Iterator first, Iterator const& last) const
        {
            if (out)
            {
                out << pre;
                while (first != last)
                    detail::print_char(*first++, out);
                out << post;
            }
        }

        std::ostream&   out;
        std::string     pre;
        std::string     post;
    };

    struct list_action
    {
        //  Handles lists

        typedef std::pair<char, int> mark_type;
        list_action(
            std::ostream& out
          , std::stringstream& list_buffer
          , int& indent
          , std::stack<mark_type>& list_marks)
        : out(out)
        , list_buffer(list_buffer)
        , indent(indent)
        , list_marks(list_marks) {}

        template <typename Iterator>
        void operator()(Iterator const& first, Iterator const& last) const
        {
            assert(!list_marks.empty()); // there must be at least one item in the stack
            std::string  str = list_buffer.str();
            list_buffer.str(std::string());
            out << str;

            while (!list_marks.empty())
            {
                char mark = list_marks.top().first;
                list_marks.pop();
                out << std::string((mark == '#') ? "\n</orderedlist>" : "\n</itemizedlist>");
                if (list_marks.size() >= 1)
                    out << std::string("\n</listitem>");
            }

            indent = -1; // reset
        }

        std::ostream& out;
        std::stringstream& list_buffer;
        int& indent;
        std::stack<mark_type>& list_marks;
    };

    struct list_format_action
    {
        //  Handles list formatting and hierarchy

        typedef std::pair<char, int> mark_type;
        list_format_action(
            std::stringstream& out
          , int& indent
          , std::stack<mark_type>& list_marks)
        : out(out)
        , indent(indent)
        , list_marks(list_marks) {}

        template <typename Iterator>
        void operator()(Iterator first, Iterator const& last) const
        {
            int new_indent = 0;
            while (first != last && (*first == ' ' || *first == '\t'))
            {
                char mark = *first++;
                if (mark == ' ')
                {
                    ++new_indent;
                }
                else // must be a tab
                {
                    assert(mark == '\t');
                    // hardcoded tab to 4 for now
                    new_indent = ((new_indent + 4) / 4) * 4;
                }
            }

            char mark = *first;
            assert(mark == '#' || mark == '*'); // expecting a mark

            if (indent == -1) // the very start
            {
                assert(new_indent == 0);
            }

            if (new_indent > indent)
            {
                //~ char parent_mark = 0;
                //~ if (list_marks.size() >= 1)
                    //~ parent_mark = list_marks.top().first;
                indent = new_indent;
                list_marks.push(mark_type(mark, indent));
                if (list_marks.size() > 1)
                {
                    // Make this new list a child of the previous list.
                    // The previous listelem has already ended so we erase
                    // </listitem> to accomodate this sub-list. We'll close
                    // the listelem later.

                    std::string str = out.str();
                    std::string::size_type pos = str.rfind("\n</listitem>");
                    assert(pos <= str.size());
                    str.erase(str.begin()+pos, str.end());
                    out.str(std::string());
                    out << str;
                    //~ out << std::string((parent_mark == '#') ? "<orderedlist>\n" : "<itemizedlist>\n");
                }
                //~ else
                //~ {
                    out << std::string((mark == '#') ? "<orderedlist>\n" : "<itemizedlist>\n");
                //~ }
            }

            else if (new_indent < indent)
            {
                assert(!list_marks.empty());
                indent = new_indent;
                //~ list_marks.pop();
                //~ out << std::string((mark == '#') ? "\n</orderedlist>" : "\n</itemizedlist>");
                //~ if (list_marks.size() >= 1)
                    //~ out << std::string("\n</listitem>");

                while (!list_marks.empty() && (indent < list_marks.top().second))
                {
                    char mark = list_marks.top().first;
                    list_marks.pop();
                    out << std::string((mark == '#') ? "\n</orderedlist>" : "\n</itemizedlist>");
                    if (list_marks.size() >= 1)
                        out << std::string("\n</listitem>");
                }
            }

            if (mark != list_marks.top().first) // new_indent == indent
            {
                boost::spirit::file_position const pos = first.get_position();
                std::cerr
                    << "Illegal change of list style at \"" << pos.file
                    << "\" line " << pos.line
                    << ", column " << pos.column << ".\n";
                std::cerr << "Ignoring change of list style" << std::endl;
            }
        }

        std::stringstream& out;
        int& indent;
        std::stack<mark_type>& list_marks;
    };

    struct span
    {
        // Decorates c++ code fragments

        span(char const* name, std::ostream& out)
        : name(name), out(out) {}

        template <typename Iterator>
        void operator()(Iterator first, Iterator last) const
        {
            if (out)
            {
                out << "<phrase role=\"" << name << "\">";
                while (first != last)
                    detail::print_char(*first++, out);
                out << "</phrase>";
            }
        }

        char const* name;
        std::ostream& out;
    };

    struct unexpected_char
    {
        // Handles unexpected chars in c++ syntax

        unexpected_char(std::ostream& out)
        : out(out) {}

        template <typename Char>
        void operator()(Char) const
        {
            if (out)
                out << '#'; // print out an unexpected character
        }

        std::ostream& out;
    };

    struct anchor_action
    {
        // Handles anchors

        anchor_action(std::ostream& out)
            : out(out) {}

        template <typename Iterator>
        void operator()(Iterator first, Iterator last) const
        {
            if (out)
            {
                out << "<anchor id=\"";
                while (first != last)
                    detail::print_char(*first++, out);
                out << "\" />\n";
            }
        }

        std::ostream& out;
    };

    char const* quickbook_get_date = "__quickbook_get_date__";
    char const* quickbook_get_time = "__quickbook_get_time__";

    struct do_macro_action
    {
        // Handles macro substitutions

        do_macro_action(std::ostream& phrase)
        : phrase(phrase) {}

        void operator()(std::string const& str) const
        {
            if (str == quickbook_get_date)
            {
                char strdate[ 64 ];
                time_t t = time(0);
                strftime( strdate, sizeof(strdate), "%Y-%b-%d", localtime(&t) );
                phrase << strdate;
            }
            else if (str == quickbook_get_time)
            {
                char strdate[ 64 ];
                time_t t = time(0);
                strftime( strdate, sizeof(strdate), "%I:%M:%S %p", localtime(&t) );
                phrase << strdate;
            }
            else
            {
                phrase << str;
            }
        }

        std::ostream& phrase;
    };

    struct space
    {
        // Prints a space

        space(std::ostream& out)
        : out(out) {}

        template <typename Iterator>
        void operator()(Iterator first, Iterator last) const
        {
            if (out)
            {
                while (first != last)
                    detail::print_space(*first++, out);
            }
        }

        template <typename Char>
        void operator()(Char ch) const
        {
            if (out)
            {
                detail::print_space(ch, out);
            }
        }

        std::ostream& out;
    };

    struct code_action
    {
        // Does the actual syntax highlighing of code

        code_action(std::ostream& out,
                    std::string const & source_mode,
                    symbols<std::string> const& macro)
        : out(out)
        , source_mode(source_mode)
        , cpp_p(out, macro, do_macro_action(out))
        , python_p(out, macro, do_macro_action(out))
        {
        }

        template <typename Iterator>
        void operator()(Iterator first, Iterator last) const
        {
            if (out)
            {
                // preprocess the code section to remove the initial indentation
                std::string program(first, last);
                detail::unindent(program);
                
                out << "<programlisting>\n"
                    << "<literal>\n";

                // print the code with syntax coloring
                if (source_mode == "c++")
                {
                    parse(program.begin(), program.end(), cpp_p);
                }
                else if (source_mode == "python")
                {
                    parse(program.begin(), program.end(), python_p);
                }
                
                out << "</literal>\n"
                    << "</programlisting>\n";
            }
        }

        std::ostream& out;
        std::string const& source_mode;
        
        cpp_highlight<
            span
          , space
          , symbols<std::string>
          , do_macro_action
          , unexpected_char
          , std::ostream>
        cpp_p;
        
        python_highlight<
            span
          , space
          , symbols<std::string>
          , do_macro_action
          , unexpected_char
          , std::ostream>
        python_p;
    };

    struct inline_code_action
    {
        // Does the actual syntax highlighing of code inlined in text

        inline_code_action(std::ostream& out,
                           std::string const& source_mode,
                           symbols<std::string> const& macro)
        : out(out)
        , source_mode(source_mode)
        , cpp_p(out, macro, do_macro_action(out))
        , python_p(out, macro, do_macro_action(out))
        {}

        template <typename Iterator>
        void operator()(Iterator first, Iterator last) const
        {
            if (out)
            {
                out << "<code>";

                // print the code with syntax coloring
                if (source_mode == "c++")
                {
                    parse(first, last, cpp_p);
                }
                else if (source_mode == "python")
                {
                    parse(first, last, python_p);
                }
                
                out << "</code>";
            }
        }

        std::ostream& out;
        std::string const& source_mode;
        
        cpp_highlight<
            span
          , space
          , symbols<std::string>
          , do_macro_action
          , unexpected_char
          , std::ostream>
        cpp_p;
        
        python_highlight<
            span
          , space
          , symbols<std::string>
          , do_macro_action
          , unexpected_char
          , std::ostream>
        python_p;
    };

    namespace
    {
        // Some markups

        const char* paragraph_pre   = "<para>\n";
        const char* paragraph_post  = "</para>\n";
        const char* h1_pre          = "<bridgehead renderas=\"sect1\">";
        const char* h1_post         = "</bridgehead>";
        const char* h2_pre          = "<bridgehead renderas=\"sect2\">";
        const char* h2_post         = "</bridgehead>";
        const char* h3_pre          = "<bridgehead renderas=\"sect3\">";
        const char* h3_post         = "</bridgehead>";
        const char* h4_pre          = "<bridgehead renderas=\"sect4\">";
        const char* h4_post         = "</bridgehead>";
        const char* h5_pre          = "<bridgehead renderas=\"sect5\">";
        const char* h5_post         = "</bridgehead>";
        const char* h6_pre          = "<bridgehead renderas=\"sect6\">";
        const char* h6_post         = "</bridgehead>";
        const char* hr_             = "<para/>";

        const char* blurb_pre =
            "<informaltable frame=\"all\">\n"
            "<?dbhtml table-width=\"74%\" ?>\n"
            "<tgroup cols=\"1\">\n"
            "<tbody>\n"
            "<row>\n"
            "<entry role=\"blurb\">\n"
            ;

        const char* blurb_post =
            "</entry>\n"
            "</row>\n"
            "</tbody>\n"
            "</tgroup>\n"
            "</informaltable>\n"
            ;

        const char* blockquote_pre      = "<blockquote><para>";
        const char* blockquote_post     = "</para></blockquote>";
        const char* preformatted_pre    = "<programlisting><literal>";
        const char* preformatted_post   = "</literal></programlisting>";
        const char* list_item_pre       = "<listitem>\n";
        const char* list_item_post      = "\n</listitem>";
        const char* bold_pre_           = "<emphasis role=\"bold\">";
        const char* bold_post_          = "</emphasis>";
        const char* italic_pre_         = "<emphasis>";
        const char* italic_post_        = "</emphasis>";
        const char* underline_pre_      = "<emphasis role=\"underline\">";
        const char* underline_post_     = "</emphasis>";
        const char* teletype_pre_       = "<literal>";
        const char* teletype_post_      = "</literal>";
        const char* break_mark          = "<sbr/>\n";
        const char* url_pre_            = "<ulink url=\"";
        const char* url_post_           = "</ulink>";
        const char* link_pre_           = "<link linkend=\"";
        const char* link_post_          = "</link>";
        const char* start_varlistentry_ = "<varlistentry>";
        const char* end_varlistentry_   = "</varlistentry>\n";
        const char* start_varlistterm_  = "<term>";
        const char* end_varlistterm_    = "</term>";
        const char* start_varlistitem_  = "<listitem>";
        const char* end_varlistitem_    = "</listitem>";
        const char* start_header_       = "<thead>";
        const char* end_header_         = "</thead>\n";
        const char* start_row_          = "<row>";
        const char* end_row_            = "</row>\n";
        const char* start_cell_         = "<entry>";
        const char* end_cell_           = "</entry>";
        const char* funcref_pre_        = "<functionname alt=\"";
        const char* funcref_post_       = "</functionname>";
        const char* classref_pre_       = "<classname alt=\"";
        const char* classref_post_      = "</classname>";
        const char* memberref_pre_      = "<methodname alt=\"";
        const char* memberref_post_     = "</methodname>";
        const char* enumref_pre_        = "<enumname alt=\"";
        const char* enumref_post_       = "</enumname>";
        const char* headerref_pre_      = "<headername alt=\"";
        const char* headerref_post_     = "</headername>";
    }

    struct raw_char_action
    {
        // Prints a single raw (unprocessed) char.
        // Allows '<', '>'... etc.

        raw_char_action(std::ostream& phrase)
        : phrase(phrase) {}

        template <typename Char>
        void operator()(Char const& ch) const
        {
            phrase << ch;
        }

        template <typename Iterator>
        void operator()(Iterator const& first, Iterator const& /*last*/) const
        {
            phrase << *first;
        }

        std::ostream& phrase;
    };

    struct plain_char_action
    {
        // Prints a single plain char.
        // Converts '<' to "&lt;"... etc See utils.hpp

        plain_char_action(std::ostream& phrase)
        : phrase(phrase) {}

        template <typename Char>
        void operator()(Char const& ch) const
        {
            detail::print_char(ch, phrase);
        }

        template <typename Iterator>
        void operator()(Iterator const& first, Iterator const& /*last*/) const
        {
            detail::print_char(*first, phrase);
        }

        std::ostream& phrase;
    };

    struct image_action
    {
        // Handles inline images

        image_action(std::ostream& phrase)
        : phrase(phrase) {}

        template <typename Iterator>
        void operator()(Iterator first, Iterator last) const
        {
            phrase << "<inlinemediaobject><imageobject><imagedata fileref=\"";
            while (first != last)
                detail::print_char(*first++, phrase);
            phrase << "\"></imagedata></imageobject></inlinemediaobject>";
        }

        std::ostream& phrase;
    };

    struct markup_action
    {
        // A generic markup action

        markup_action(std::ostream& phrase, std::string const& str)
        : phrase(phrase), str(str) {}

        template <typename T>
        void operator()(T const&) const
        {
            phrase << str;
        }

        template <typename T>
        void operator()(T const&, T const&) const
        {
            phrase << str;
        }

        std::ostream& phrase;
        std::string str;
    };

    template <typename Actions>
    struct indentifier_action
    {
        // Handles macro identifiers

        indentifier_action(Actions& actions)
        : actions(actions) {}

        template <typename Iterator>
        void operator()(Iterator const& first, Iterator const& last) const
        {
            actions.macro_id.assign(first, last);
            actions.phrase_save = actions.phrase.str();
            actions.phrase.str(std::string());
        }

        Actions& actions;
    };

    template <typename Actions>
    struct macro_def_action
    {
        // Handles macro definitions

        macro_def_action(Actions& actions)
        : actions(actions) {}

        template <typename Iterator>
        void operator()(Iterator const& first, Iterator const& last) const
        {
            actions.macro.add(
                actions.macro_id.begin()
              , actions.macro_id.end()
              , actions.phrase.str());
            actions.phrase.str(actions.phrase_save);
        }

        Actions& actions;
    };

    struct link_action
    {
        // Handles links (URL, XML refentry, function, class, member)

        link_action(std::ostream& phrase, char const* tag)
        : phrase(phrase), tag(tag) {}

        template <typename Iterator>
        void operator()(Iterator first, Iterator last) const
        {
            Iterator save = first;
            phrase << tag;
            while (first != last)
                detail::print_char(*first++, phrase);
            phrase << "\">";

            // Yes, it is safe to dereference last here. When we
            // reach here, *last is certainly valid. We test if
            // *last == ']'. In which case, the url is the text.
            // Example: [@http://spirit.sourceforge.net/]

            if (*last == ']')
            {
                first = save;
                while (first != last)
                    detail::print_char(*first++, phrase);
            }
        }

        std::ostream& phrase;
        char const* tag;
    };

    template <typename Actions>
    struct variablelist_action
    {
        // Handles variable lists

        variablelist_action(Actions& actions)
        : actions(actions) {}

        template <typename Iterator>
        void operator()(Iterator, Iterator) const
        {
            if (!!actions.out)
            {
                actions.out << "<variablelist>\n";

                actions.out << "<title>";
                std::string::iterator first = actions.table_title.begin();
                std::string::iterator last = actions.table_title.end();
                while (first != last)
                    detail::print_char(*first++, actions.out);
                actions.out << "</title>\n";

                std::string str = actions.phrase.str();
                actions.phrase.str(std::string());
                actions.out << str;

                actions.out << "</variablelist>\n";
                actions.table_span = 0;
                actions.table_header.clear();
                actions.table_title.clear();
            }
        }

        Actions& actions;
    };

    template <typename Actions>
    struct table_action
    {
        // Handles tables

        table_action(Actions& actions)
        : actions(actions) {}

        template <typename Iterator>
        void operator()(Iterator, Iterator) const
        {
            if (!!actions.out)
            {
                actions.out << "<informaltable frame=\"all\">\n"
                             << "<bridgehead renderas=\"sect4\">";

                actions.out << "<phrase role=\"table-title\">";
                std::string::iterator first = actions.table_title.begin();
                std::string::iterator last = actions.table_title.end();
                while (first != last)
                    detail::print_char(*first++, actions.out);
                actions.out << "</phrase>";

                actions.out << "</bridgehead>\n"
                             << "<tgroup cols=\"" << actions.table_span << "\">\n";

                if(!actions.table_header.empty())
                {
                    actions.out << "<thead>" << actions.table_header << "</thead>\n";
                }

                actions.out << "<tbody>\n";

                std::string str = actions.phrase.str();
                actions.phrase.str(std::string());
                actions.out << str;

                actions.out << "</tbody>\n"
                             << "</tgroup>\n"
                             << "</informaltable>\n";
                actions.table_span = 0;
                actions.table_header.clear();
                actions.table_title.clear();
            }
        }

        Actions& actions;
    };

    struct start_row_action
    {
        // Handles table rows

        start_row_action(std::stringstream& phrase, unsigned& span, std::string& header)
            : phrase(phrase), span(span), header(header) {}

        template <typename T>
        void operator()(T const&) const
        {
            // the first row is the header
            if(header.empty() && !phrase.str().empty())
            {
                header = phrase.str();
                phrase.str(std::string());
            }

            phrase << start_row_;
            span = 0;
        }

        template <typename T>
        void operator()(T const& t,T const&) const
        {
            (*this)(t);
        }

        std::stringstream& phrase;
        unsigned& span;
        std::string& header;
    };

    struct start_col_action
    {
        // Handles table columns

        start_col_action(std::ostream& phrase, unsigned& span)
        : phrase(phrase), span(span) {}

        template <typename T>
        void operator()(T const&) const
        {
            phrase << start_cell_; ++span;
        }

        std::ostream& phrase;
        unsigned& span;
    };

    struct begin_section_action
    {
        // Handles begin page

        begin_section_action(
            std::ostream& phrase
          , std::string& library_id
          , std::string& section_id)
        : phrase(phrase)
        , library_id(library_id)
        , section_id(section_id) {}

        template <typename Iterator>
        void operator()(Iterator first, Iterator last) const
        {
            if (section_id.empty())
                section_id = detail::make_identifier(first, last);
            phrase << "\n<section id=\"" << library_id << "." << section_id << "\">\n";
            phrase << "<title>";
            while (first != last)
                detail::print_char(*first++, phrase);
            phrase << "</title>\n";
        }

        std::ostream& phrase;
        std::string& library_id;
        std::string& section_id;
    };

    struct xinclude_action
    {
        // Handles XML includes

        xinclude_action(std::ostream& out_)
            : out(out_) {}

        template <typename Iterator>
        void operator()(Iterator first, Iterator last) const
        {
            out << "\n<xi:include href=\"";
            while (first != last)
                detail::print_char(*first++, out);
            out << "\" />\n";
        }

        std::ostream& out;
    };

    struct xml_author
    {
        // Handles xml author

        xml_author(std::ostream& out)
        : out(out) {}

        void operator()(std::pair<std::string, std::string> const& author) const
        {
            out << "    <author>\n"
                << "      <firstname>" << author.first << "</firstname>\n"
                << "      <surname>" << author.second << "</surname>\n"
                << "    </author>\n";
        }

        std::ostream& out;
    };

    struct xml_year
    {
        // Handles xml year

        xml_year(std::ostream& out)
            : out(out) {}

        void operator()(std::string const &year) const
        {
            out << "      <year>" << year << "</year>\n";
        }

        std::ostream& out;
    };

    template <typename Actions>
    void pre(std::ostream& out, Actions& actions)
    {
        // The quickbook file has been parsed. Now, it's time to
        // generate the output. Here's what we'll do *before* anything else.

        if (actions.doc_id.empty())
            actions.doc_id = detail::make_identifier(
                actions.doc_title.begin(),actions.doc_title.end());

        if (actions.doc_dirname.empty())
            actions.doc_dirname = actions.doc_id;

        if (actions.doc_last_revision.empty())
        {
            // default value for last-revision is now

            char strdate[ 30 ];
            time_t t = time(0);
            strftime(
                strdate, sizeof(strdate),
                "$" /* prevent CVS substitution */ "Date: %Y/%m/%d %H:%M:%S $",
                gmtime(&t)
            );

            actions.doc_last_revision = strdate;
        }

        out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            << "<!DOCTYPE library PUBLIC \"-//Boost//DTD BoostBook XML V1.0//EN\"\n"
            << "     \"http://www.boost.org/tools/boostbook/dtd/boostbook.dtd\">\n"
            << '<' << actions.doc_type << "\n"
            << "    id=\"" << actions.doc_id << "\"\n"
            << "    name=\"" << actions.doc_title << "\"\n"
            << "    dirname=\"" << actions.doc_dirname << "\"\n"
            << "    last-revision=\"" << actions.doc_last_revision << "\" \n"
            << "    xmlns:xi=\"http://www.w3.org/2001/XInclude\">\n"
            << "  <" << actions.doc_type << "info>\n";

        for_each(
            actions.doc_authors.begin()
          , actions.doc_authors.end()
          , xml_author(out));

        if (!actions.doc_copyright_holder.empty())
        {
            out << "\n" << "    <copyright>\n";

            for_each(
                actions.doc_copyright_years.begin()
              , actions.doc_copyright_years.end()
              , xml_year(out));

            out << "      <holder>" << actions.doc_copyright_holder << "</holder>\n"
                << "    </copyright>\n"
                << "\n"
            ;
        }

        if (!actions.doc_license.empty())
        {
            out << "    <legalnotice>\n"
                << "      <para>\n"
                << "        " << actions.doc_license << "\n"
                << "      </para>\n"
                << "    </legalnotice>\n"
                << "\n"
            ;
        }

        if (!actions.doc_purpose.empty())
        {
            out << "    <" << actions.doc_type << "purpose>\n"
                << "      " << actions.doc_purpose
                << "    </" << actions.doc_type << "purpose>\n"
                << "\n"
            ;
        }

        if (!actions.doc_purpose.empty())
        {
            out << "    <" << actions.doc_type << "category name=\"category:"
                << actions.doc_category
                << "\"></" << actions.doc_type << "category>\n"
                << "\n"
            ;
        }

        out << "  </" << actions.doc_type << "info>\n"
            << "\n"
        ;

        if (!actions.doc_title.empty())
        {
            out << "  <title>" << actions.doc_title;
            if (!actions.doc_version.empty())
                out << ' ' << actions.doc_version;
            out << "</title>\n\n\n";
        }
    }

    template <typename Actions>
    void post(std::ostream& out, Actions& actions)
    {
        // We've finished generating our output. Here's what we'll do
        // *after* everything else.
        out << "\n</" << actions.doc_type << ">\n\n";
    }
}

#endif // BOOST_SPIRIT_QUICKBOOK_UTILS_HPP

