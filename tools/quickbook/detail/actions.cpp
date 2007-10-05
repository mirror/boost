/*=============================================================================
    Copyright (c) 2002 2004 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    Copyright (c) 2005 Thomas Guest
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#include <numeric>
#include <functional>
#include <boost/bind.hpp>
#include <boost/filesystem/convenience.hpp>
#include "./actions.hpp"
#include "./utils.hpp"

#if (defined(BOOST_MSVC) && (BOOST_MSVC <= 1310))
#pragma warning(disable:4355)
#endif

namespace quickbook
{
    void error_action::operator()(iterator const& first, iterator const& /*last*/) const
    {
        boost::spirit::file_position const pos = first.get_position();
        detail::outerr(pos.file,pos.line)
            << "Syntax Error near column " << pos.column << ".\n";
    }

    void phrase_action::operator()(iterator const& first, iterator const& last) const
    {
        if (out)
        {
            std::string str = phrase.str();
            detail::convert_nbsp(str);
            phrase.str(std::string());
            out << pre << str << post;
        }
    }

    void anchored_phrase_action::operator()(iterator const& first, iterator const& last) const
    {
        if (out)
        {
            std::string str = phrase.str();
            detail::convert_nbsp(str);
            if (qbk_version_n < 103) // version 1.2 and below
            {
                out << "<anchor id=\""
                    << section_id << '.'
                    << detail::make_identifier(str.begin(), str.end())
                    << "\" />";
            }
            else // version 1.3 and above
            {
                out << "<anchor id=\""
                    << library_id << '.' << qualified_section_id << '.'
                    << detail::make_identifier(str.begin(), str.end())
                    << "\" />";
            }
            phrase.str(std::string());
            out << pre << str << post;
        }
    }

    void simple_phrase_action::operator()(iterator first, iterator const& last) const
    {
        if (out)
        {
            out << pre;
            while (first != last)
                detail::print_char(*first++, out);
            out << post;
        }
    }

    void list_action::operator()(iterator const& first, iterator const& last) const
    {
        BOOST_ASSERT(!list_marks.empty()); // there must be at least one item in the stack
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

    void list_format_action::operator()(iterator first, iterator const& last) const
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
                BOOST_ASSERT(mark == '\t');
                // hardcoded tab to 4 for now
                new_indent = ((new_indent + 4) / 4) * 4;
            }
        }

        char mark = *first;
        BOOST_ASSERT(mark == '#' || mark == '*'); // expecting a mark

        if (indent == -1) // the very start
        {
            BOOST_ASSERT(new_indent == 0);
        }

        if (new_indent > indent)
        {
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
                BOOST_ASSERT(pos <= str.size());
                str.erase(str.begin()+pos, str.end());
                out.str(std::string());
                out << str;
            }
            out << std::string((mark == '#') ? "<orderedlist>\n" : "<itemizedlist>\n");
        }

        else if (new_indent < indent)
        {
            BOOST_ASSERT(!list_marks.empty());
            indent = new_indent;

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
            detail::outerr(pos.file,pos.line)
                << "Illegal change of list style near column " << pos.column << ".\n";
            detail::outwarn(pos.file,pos.line)
                << "Ignoring change of list style" << std::endl;
        }
    }

    void span::operator()(iterator first, iterator const& last) const
    {
        if (out)
        {
            out << "<phrase role=\"" << name << "\">";
            while (first != last)
                detail::print_char(*first++, out);
            out << "</phrase>";
        }
    }

    void unexpected_char::operator()(char) const
    {
        if (out)
            out << '#'; // print out an unexpected character
    }

    void anchor_action::operator()(iterator first, iterator const& last) const
    {
        if (out)
        {
            out << "<anchor id=\"";
            while (first != last)
                detail::print_char(*first++, out);
            out << "\" />\n";
        }
    }

    void do_macro_action::operator()(std::string const& str) const
    {
        if (str == quickbook_get_date)
        {
            char strdate[64];
            strftime(strdate, sizeof(strdate), "%Y-%b-%d", current_time);
            phrase << strdate;
        }
        else if (str == quickbook_get_time)
        {
            char strdate[64];
            strftime(strdate, sizeof(strdate), "%I:%M:%S %p", current_time);
            phrase << strdate;
        }
        else
        {
            phrase << str;
        }
    }

    void space::operator()(char ch) const
    {
        if (out)
        {
            detail::print_space(ch, out);
        }
    }

    void space::operator()(iterator first, iterator const& last) const
    {
        if (out)
        {
            while (first != last)
                detail::print_space(*first++, out);
        }
    }

    void pre_escape_back::operator()(iterator const& first, iterator const& last) const
    {
        save = escape_actions.phrase.str(); // save the stream
    }

    void post_escape_back::operator()(iterator const& first, iterator const& last) const
    {
        std::string str = escape_actions.phrase.str();
        escape_actions.phrase.str(save); // restore the stream
        out << str;
    }

    void code_action::operator()(iterator const& first, iterator const& last) const
    {
        if (out)
        {
            std::string save = phrase.str();
            phrase.str(std::string());

            // preprocess the code section to remove the initial indentation
            std::string program_(first, last);
            detail::unindent(program_);

            // $$$ fix me $$$ this is wasteful. we have to convert
            // back to a vector<char> so we can use the same iterator type 
            // used by the rest of the system, otherwise, it is wasteful 
            // of function template instantiations

            std::vector<char> program(program_.begin(), program_.end());
            iterator first_(program.begin(), program.end());
            iterator last_(program.end(), program.end());
            first_.set_position(first.get_position());

            // print the code with syntax coloring
            if (source_mode == "c++")
            {
                parse(first_, last_, cpp_p);
            }
            else if (source_mode == "python")
            {
                parse(first_, last_, python_p);
            }
            
            std::string str = temp.str();
            temp.str(std::string());
            phrase.str(std::string());
            phrase << save;

            out << "<programlisting>\n";
            out << str;
            out << "</programlisting>\n";
        }
    }

    void inline_code_action::operator()(iterator const& first, iterator const& last) const
    {
        std::string save = out.str();
        out.str(std::string());
 
        // print the code with syntax coloring
        if (source_mode == "c++")
        {
            parse(first, last, cpp_p);
        }
        else if (source_mode == "python")
        {
            parse(first, last, python_p);
        }
        std::string str = temp.str();
        temp.str(std::string());
        out.str(std::string());

        out << save;
        out << "<code>";
        out << str;
        out << "</code>";
    }

    void raw_char_action::operator()(char ch) const
    {
        phrase << ch;
    }

    void raw_char_action::operator()(iterator const& first, iterator const& /*last*/) const
    {
        phrase << *first;
    }

    void plain_char_action::operator()(char ch) const
    {
        detail::print_char(ch, phrase);
    }

    void plain_char_action::operator()(iterator const& first, iterator const& /*last*/) const
    {
        detail::print_char(*first, phrase);
    }

    void image_action::operator()(iterator first, iterator const& last) const
    {
        fs::path const img_path(std::string(first, last));

        phrase << "<inlinemediaobject>";

        phrase << "<imageobject><imagedata fileref=\"";
        while (first != last)
            detail::print_char(*first++, phrase);
        phrase << "\"></imagedata></imageobject>";

        // Also add a textobject -- use the basename of the image file.
        // This will mean we get "alt" attributes of the HTML img.
        phrase << "<textobject><phrase>";
        detail::print_string(fs::basename(img_path), phrase);
        phrase << "</phrase></textobject>";

        phrase << "</inlinemediaobject>";
    }

    void indentifier_action::operator()(iterator const& first, iterator const& last) const
    {
        actions.macro_id.assign(first, last);
        actions.phrase_save = actions.phrase.str();
        actions.phrase.str(std::string());
    }

    void macro_def_action::operator()(iterator const& first, iterator const& last) const
    {
        actions.macro.add(
            actions.macro_id.begin()
          , actions.macro_id.end()
          , actions.phrase.str());
        actions.phrase.str(actions.phrase_save);
    }

    void link_action::operator()(iterator first, iterator const& last) const
    {
        iterator save = first;
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

    void variablelist_action::operator()(iterator, iterator) const
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

    void table_action::operator()(iterator, iterator) const
    {
        if (!!actions.out)
        {
            actions.out << "<informaltable frame=\"all\">\n"
                         << "<bridgehead renderas=\"sect4\">";

            std::string::iterator first = actions.table_title.begin();
            std::string::iterator last = actions.table_title.end();
            if (first != last) // allow no title
            {
                actions.out << "<phrase role=\"table-title\">";
                while (first != last)
                    detail::print_char(*first++, actions.out);
                actions.out << "</phrase>";
            }
            actions.out << "</bridgehead>\n"
                         << "<tgroup cols=\"" << actions.table_span << "\">\n";

            if (!actions.table_header.empty())
            {
                actions.out << "<thead>" << actions.table_header << "</thead>\n";
            }

            actions.out << "<tbody>\n";

            std::string str = actions.phrase.str();
            detail::convert_nbsp(str);
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

    void start_row_action::operator()(char) const
    {
        // the first row is the header
        if (header.empty() && !phrase.str().empty())
        {
            header = phrase.str();
            phrase.str(std::string());
        }

        phrase << start_row_;
        span = 0;
    }

    void start_row_action::operator()(iterator f, iterator) const
    {
        (*this)(*f);
    }

    void start_col_action::operator()(char) const
    {
        phrase << start_cell_; 
        ++span;
    }

    void begin_section_action::operator()(iterator first, iterator const& last) const
    {
        if (section_id.empty())
            section_id = detail::make_identifier(first, last);

        if (level != 0)
            qualified_section_id += '.';
        else
            BOOST_ASSERT(qualified_section_id.empty());
        qualified_section_id += section_id;
        ++level;

        if (qbk_version_n < 103) // version 1.2 and below
        {
            out << "\n<section id=\"" 
                << library_id << "." << section_id << "\">\n";
        }
        else // version 1.3 and above
        {
            out << "\n<section id=\"" << library_id 
                << "." << qualified_section_id << "\">\n";
        }
        std::string str;
        str = phrase.str();
        phrase.str(std::string());
        out << "<title>" << str << "</title>\n";
    }

    void end_section_action::operator()(iterator const& first, iterator const& last) const
    {
        out << "</section>";

        --level;
        if (level < 0)
        {
            boost::spirit::file_position const pos = first.get_position();
            detail::outerr(pos.file,pos.line)
                << "Mismatched [endsect] near column " << pos.column << ".\n";
        }
        if (level == 0)
        {
            qualified_section_id.clear();
        }
        else
        {
            std::string::size_type const n = 
                qualified_section_id.find_last_of('.');
            BOOST_ASSERT(std::string::npos != n);
            qualified_section_id.erase(n, std::string::npos);
        }
    }

    fs::path path_difference(fs::path const& outdir, fs::path const& xmlfile)
    {
        fs::path outtmp, xmltmp;
        fs::path::iterator out = outdir.begin(), xml = xmlfile.begin();
        for(; out != outdir.end() && xml != xmlfile.end(); ++out, ++xml)
        {
            if(!fs::equivalent(outtmp /= *out, xmltmp /= *xml))
                break;
        }
        std::divides<fs::path> concat;
        out = (out == outdir.begin()) ? outdir.end() : out;
        xmltmp = std::accumulate(out, outdir.end(), fs::path(), boost::bind(concat, _1, ".."));
        return std::accumulate(xml, xmlfile.end(), xmltmp, concat);
    }

    void xinclude_action::operator()(iterator const& first, iterator const& last) const
    {
        // Given an xml file to include and the current filename, calculate the
        // path to the XML file relative to the output directory.
        fs::path xmlfile(std::string(first, last));
        if (!xmlfile.is_complete())
        {
            fs::path infile = fs::complete(actions.filename).normalize();
            xmlfile = (infile.branch_path() / xmlfile).normalize();
            fs::path outdir = fs::complete(actions.outdir).normalize();
            xmlfile = path_difference(outdir, xmlfile);
        }
        out << "\n<xi:include href=\"";
        detail::print_string(detail::escape_uri(xmlfile.string()), out);
        out << "\" />\n";
    }

    void include_action::operator()(iterator const& first, iterator const& last) const
    {
        fs::path filein(std::string(first, last), fs::native);
        std::string doc_type, doc_id, doc_dirname, doc_last_revision;

        // check to see if the path is complete and if not, make it relative to the current path
        if (!filein.is_complete())
        {
            filein = actions.filename.branch_path() / filein;
            filein.normalize();
        }

        // swap the filenames
        std::swap(actions.filename, filein);

        // save the doc info strings
        actions.doc_type.swap(doc_type);
        actions.doc_id.swap(doc_id);
        actions.doc_dirname.swap(doc_dirname);
        actions.doc_last_revision.swap(doc_last_revision);

        // scope the macros
        macros_type macro = actions.macro;

        // if an id is specified in this include (in in [include:id foo.qbk]
        // then use it as the doc_id.
        if (!actions.include_doc_id.empty())
        {
            actions.doc_id = actions.include_doc_id;
            actions.include_doc_id.clear();
        }

        // update the __FILENAME__ macro
        *boost::spirit::find(actions.macro, "__FILENAME__") = actions.filename.native_file_string();

        // parse the file
        quickbook::parse(actions.filename.native_file_string().c_str(), actions, true);

        // restore the values
        std::swap(actions.filename, filein);

        actions.doc_type.swap(doc_type);
        actions.doc_id.swap(doc_id);
        actions.doc_dirname.swap(doc_dirname);
        actions.doc_last_revision.swap(doc_last_revision);

        actions.macro = macro;
    }

    void xml_author::operator()(std::pair<std::string, std::string> const& author) const
    {
        out << "    <author>\n"
            << "      <firstname>" << author.first << "</firstname>\n"
            << "      <surname>" << author.second << "</surname>\n"
            << "    </author>\n";
    }

    void xml_year::operator()(std::string const &year) const
    {
        out << "      <year>" << year << "</year>\n";
    }

    void pre(std::ostream& out, quickbook::actions& actions, bool ignore_docinfo)
    {
        // The doc_info in the file has been parsed. Here's what we'll do 
        // *before* anything else.

        if (actions.doc_id.empty())
            actions.doc_id = detail::make_identifier(
                actions.doc_title.begin(),actions.doc_title.end());

        if (actions.doc_dirname.empty())
            actions.doc_dirname = actions.doc_id;

        if (actions.doc_last_revision.empty())
        {
            // default value for last-revision is now

            char strdate[64];
            strftime(
                strdate, sizeof(strdate),
                (debug_mode ? 
                    "DEBUG MODE Date: %Y/%m/%d %H:%M:%S $" :
                    "$" /* prevent CVS substitution */ "Date: %Y/%m/%d %H:%M:%S $"),
                current_gm_time
            );
            actions.doc_last_revision = strdate;
        }

        // if we're ignoring the document info, we're done.
        if (ignore_docinfo)
        {
            return;
        }

        if (qbk_major_version == 0)
        {
            // hard code quickbook version to v1.1
            qbk_major_version = 1;
            qbk_minor_version = 1;
            qbk_version_n = 101;
            detail::outwarn(actions.filename.native_file_string(),1)
                << "Warning: Quickbook version undefined. "
                "Version 1.1 is assumed" << std::endl;
        }
        else
        {
            qbk_version_n = (qbk_major_version * 100) + qbk_minor_version; 
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

        if (qbk_version_n < 103)
        {
            // version < 1.3 compatibility
            actions.doc_license = actions.doc_license_1_1;
            actions.doc_purpose = actions.doc_purpose_1_1;
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

        if (!actions.doc_category.empty())
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

    void post(std::ostream& out, quickbook::actions& actions, bool ignore_docinfo)
    {
        // if we're ignoring the document info, do nothing.
        if (ignore_docinfo)
        {
            return;
        }

        // We've finished generating our output. Here's what we'll do
        // *after* everything else.
        out << "\n</" << actions.doc_type << ">\n\n";
    }

    void phrase_to_string_action::operator()(iterator const& first, iterator const& last) const
    {
        out = phrase.str();
        phrase.str(std::string());
    }

    actions::actions(char const* filein_, fs::path const& outdir_, std::ostream &out_)
        : filename(fs::complete(fs::path(filein_, fs::native)))
        , outdir(outdir_)
        , out(out_)
        , extract_doc_license(doc_license, phrase)
        , extract_doc_purpose(doc_purpose, phrase)
        , table_span(0)
        , table_header()
        , source_mode("c++")
        , code(out, phrase, temp, source_mode, macro, *this)
        , code_block(phrase, phrase, temp, source_mode, macro, *this)
        , inline_code(phrase, temp, source_mode, macro, *this)
        , paragraph(out, phrase, paragraph_pre, paragraph_post)
        , h1(out, phrase, doc_id, section_id, qualified_section_id, h1_pre, h1_post)
        , h2(out, phrase, doc_id, section_id, qualified_section_id, h2_pre, h2_post)
        , h3(out, phrase, doc_id, section_id, qualified_section_id, h3_pre, h3_post)
        , h4(out, phrase, doc_id, section_id, qualified_section_id, h4_pre, h4_post)
        , h5(out, phrase, doc_id, section_id, qualified_section_id, h5_pre, h5_post)
        , h6(out, phrase, doc_id, section_id, qualified_section_id, h6_pre, h6_post)
        , hr(out, hr_)
        , blurb(out, phrase, blurb_pre, blurb_post)
        , blockquote(out, phrase, blockquote_pre, blockquote_post)
        , preformatted(out, phrase, preformatted_pre, preformatted_post)
        , warning(out, phrase, warning_pre, warning_post)
        , caution(out, phrase, caution_pre, caution_post)
        , important(out, phrase, important_pre, important_post)
        , note(out, phrase, note_pre, note_post)
        , tip(out, phrase, tip_pre, tip_post)
        , plain_char(phrase)
        , raw_char(phrase)
        , image(phrase)
        , list_buffer()
        , list_marks()
        , indent(-1)
        , list(out, list_buffer, indent, list_marks)
        , list_format(list_buffer, indent, list_marks)
        , list_item(list_buffer, phrase, list_item_pre, list_item_post)
        , funcref_pre(phrase, funcref_pre_)
        , funcref_post(phrase, funcref_post_)
        , classref_pre(phrase, classref_pre_)
        , classref_post(phrase, classref_post_)
        , memberref_pre(phrase, memberref_pre_)
        , memberref_post(phrase, memberref_post_)
        , enumref_pre(phrase, enumref_pre_)
        , enumref_post(phrase, enumref_post_)
        , headerref_pre(phrase, headerref_pre_)
        , headerref_post(phrase, headerref_post_)
        , bold_pre(phrase, bold_pre_)
        , bold_post(phrase, bold_post_)
        , italic_pre(phrase, italic_pre_)
        , italic_post(phrase, italic_post_)
        , underline_pre(phrase, underline_pre_)
        , underline_post(phrase, underline_post_)
        , teletype_pre(phrase, teletype_pre_)
        , teletype_post(phrase, teletype_post_)
        , strikethrough_pre(phrase, strikethrough_pre_)
        , strikethrough_post(phrase, strikethrough_post_)
        , quote_pre(phrase, quote_pre_)
        , quote_post(phrase, quote_post_)
        , replaceable_pre(phrase, replaceable_pre_)
        , replaceable_post(phrase, replaceable_post_)
        , footnote_pre(phrase, footnote_pre_)
        , footnote_post(phrase, footnote_post_)
        , simple_bold(phrase, bold_pre_, bold_post_)
        , simple_italic(phrase, italic_pre_, italic_post_)
        , simple_underline(phrase, underline_pre_, underline_post_)
        , simple_teletype(phrase, teletype_pre_, teletype_post_)
        , simple_strikethrough(phrase, strikethrough_pre_, strikethrough_post_)
        , variablelist(*this)
        , start_varlistentry(phrase, start_varlistentry_)
        , end_varlistentry(phrase, end_varlistentry_)
        , start_varlistterm(phrase, start_varlistterm_)
        , end_varlistterm(phrase, end_varlistterm_)
        , start_varlistitem(phrase, start_varlistitem_)
        , end_varlistitem(phrase, end_varlistitem_)
        , break_(phrase, break_mark)
        , identifier(*this)
        , macro_def(*this)
        , do_macro(phrase)
        , url_pre(phrase, url_pre_)
        , url_post(phrase, url_post_)
        , link_pre(phrase, link_pre_)
        , link_post(phrase, link_post_)
        , table(*this)
        , start_row(phrase, table_span, table_header)
        , end_row(phrase, end_row_)
        , start_cell(phrase, table_span)
        , end_cell(phrase, end_cell_)
        , anchor(out)
        , begin_section(out, phrase, doc_id, section_id, level, qualified_section_id)
        , end_section(out, level, qualified_section_id)
        , xinclude(out, *this)
        , include(*this)
        , level(0)
        , escape_pre(phrase, escape_pre_)
        , escape_post(phrase, escape_post_)
    {
        // turn off __FILENAME__ macro on debug mode = true
        std::string filename_str = debug_mode ? 
            std::string("NO_FILENAME_MACRO_GENERATED_IN_DEBUG_MODE") : 
            filename.native_file_string();

        // add the predefined macros
        macro.add
            ("__DATE__", std::string(quickbook_get_date))
            ("__TIME__", std::string(quickbook_get_time))
            ("__FILENAME__", filename_str)
        ;
    }
}
