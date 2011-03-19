/*=============================================================================
    Copyright (c) 2002 2004 2006 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    Copyright (c) 2005 Thomas Guest
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#include <numeric>
#include <functional>
#include <algorithm>
#include <boost/filesystem/v3/convenience.hpp>
#include <boost/filesystem/v3/fstream.hpp>
#include <boost/range/algorithm/replace.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/range/distance.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/next_prior.hpp>
#include "quickbook.hpp"
#include "actions.hpp"
#include "utils.hpp"
#include "markups.hpp"
#include "actions_class.hpp"
#include "grammar.hpp"
#include "input_path.hpp"
#include "template_tags.hpp"
#include "block_tags.hpp"
#include "phrase_tags.hpp"

namespace quickbook
{
    char const* quickbook_get_date = "__quickbook_get_date__";
    char const* quickbook_get_time = "__quickbook_get_time__";

    unsigned qbk_version_n = 0; // qbk_major_version * 100 + qbk_minor_version

    namespace {
        std::string fully_qualified_id(std::string const& library_id,
            std::string const& qualified_section_id,
            std::string const& section_id)
        {
            std::string id = library_id;
            if(!id.empty() && !qualified_section_id.empty()) id += '.';
            id += qualified_section_id;
            if(!id.empty() && !section_id.empty()) id += '.';
            id += section_id;
            return id;
        }
    }

    void list_action(quickbook::actions&, value);
    void header_action(quickbook::actions&, value);
    void begin_section_action(quickbook::actions&, value);
    void end_section_action(quickbook::actions&, value, file_position);
    void block_action(quickbook::actions&, value);
    void macro_definition_action(quickbook::actions&, value);
    void template_body_action(quickbook::actions&, value);
    void variable_list_action(quickbook::actions&, value);
    void table_action(quickbook::actions&, value);
    void xinclude_action(quickbook::actions&, value);
    void import_action(quickbook::actions&, value);
    void include_action(quickbook::actions&, value);
    void image_action(quickbook::actions&, value);
    void anchor_action(quickbook::actions&, value);
    void link_action(quickbook::actions&, value);
    void phrase_action_(quickbook::actions&, value);
    void source_mode_action(quickbook::actions&, value);

    void element_action::operator()(iterator first, iterator) const
    {
        value_consumer values = actions.values.get();
        if(!values.check()) return;
        value v = values.consume();
        if(values.check()) return;
        
        switch(v.get_tag())
        {
        case block_tags::list:
            return list_action(actions, v);
        case block_tags::generic_heading:
        case block_tags::heading1:
        case block_tags::heading2:
        case block_tags::heading3:
        case block_tags::heading4:
        case block_tags::heading5:
        case block_tags::heading6:
            return header_action(actions, v);
        case block_tags::begin_section:
            return begin_section_action(actions, v);
        case block_tags::end_section:
            return end_section_action(actions, v, first.get_position());
        case block_tags::blurb:
        case block_tags::preformatted:
        case block_tags::blockquote:
        case block_tags::warning:
        case block_tags::caution:
        case block_tags::important:
        case block_tags::note:
        case block_tags::tip:
            return block_action(actions,v);
        case block_tags::macro_definition:
            return macro_definition_action(actions,v);
        case block_tags::template_definition:
            return template_body_action(actions,v);
        case block_tags::variable_list:
            return variable_list_action(actions, v);
        case block_tags::table:
            return table_action(actions, v);
        case block_tags::xinclude:
            return xinclude_action(actions, v);
        case block_tags::import:
            return import_action(actions, v);
        case block_tags::include:
            return include_action(actions, v);
        case phrase_tags::image:
            return image_action(actions, v);
        case phrase_tags::anchor:
            return anchor_action(actions, v);
        case phrase_tags::url:
        case phrase_tags::link:
        case phrase_tags::funcref:
        case phrase_tags::classref:
        case phrase_tags::memberref:
        case phrase_tags::enumref:
        case phrase_tags::macroref:
        case phrase_tags::headerref:
        case phrase_tags::conceptref:
        case phrase_tags::globalref:
            return link_action(actions, v);
        case phrase_tags::bold:
        case phrase_tags::italic:
        case phrase_tags::underline:
        case phrase_tags::teletype:
        case phrase_tags::strikethrough:
        case phrase_tags::quote:
        case phrase_tags::replaceable:
        case phrase_tags::footnote:
            return phrase_action_(actions, v);
        case source_mode_tags::cpp:
        case source_mode_tags::python:
        case source_mode_tags::teletype:
            return source_mode_action(actions, v);
        default:
            break;
        }
    }

    // Handles line-breaks (DEPRECATED!!!)
    void break_action::operator()(iterator first, iterator) const
    {
        if(!actions.output_pre(phrase)) return;

        file_position const pos = first.get_position();
        if(*first == '\\')
        {
            detail::outwarn(actions.filename, pos.line)
                << "in column:" << pos.column << ", "
                << "'\\n' is deprecated, pleases use '[br]' instead" << ".\n";
        }

        if(!actions.warned_about_breaks)
        {
            detail::outwarn(actions.filename, pos.line)
                << "line breaks generate invalid boostbook"
                << "    (will only note first occurrence)."
                << "\n";

            actions.warned_about_breaks = true;
        }
            
        phrase << break_mark;
    }

    void error_message_action::operator()(iterator first, iterator last) const
    {
        file_position const pos = first.get_position();

        std::string value(first, last);
        std::string formatted_message = message;
        boost::replace_all(formatted_message, "%s", value);
        boost::replace_all(formatted_message, "%c",
            boost::lexical_cast<std::string>(pos.column));

        detail::outerr(actions.filename, pos.line)
            << detail::utf8(formatted_message) << std::endl;
        ++actions.error_count;
    }

    void error_action::operator()(iterator first, iterator /*last*/) const
    {
        file_position const pos = first.get_position();
        detail::outerr(actions.filename, pos.line)
            << "Syntax Error near column " << pos.column << ".\n";
        ++actions.error_count;
    }

    void block_action(quickbook::actions& actions, value block)
    {
        if(!actions.output_pre(actions.out)) return;
        detail::markup markup = detail::markups[block.get_tag()];

        value_consumer values = block;
        actions.out << markup.pre << values.consume().get_boostbook() << markup.post;
        values.finish();
    }

    void phrase_action_(quickbook::actions& actions, value phrase)
    {
        if(!actions.output_pre(actions.phrase)) return;
        detail::markup markup = detail::markups[phrase.get_tag()];

        value_consumer values = phrase;
        actions.phrase << markup.pre << values.consume().get_boostbook() << markup.post;
        values.finish();
    }

    void paragraph_action::operator()() const
    {
        if(actions.suppress) return;
    
        std::string str;
        actions.phrase.swap(str);

        std::string::const_iterator
            pos = str.begin(),
            end = str.end();

        while(pos != end && cl::space_p.test(*pos)) ++pos;

        if(pos != end) {
            detail::markup markup = detail::markups[block_tags::paragraph];
            actions.out << markup.pre << str;
            actions.output_pre(actions.out);
            actions.out << markup.post;
        }
    }
    
    namespace {
        void write_bridgehead(collector& out, int level,
            std::string const& str, std::string const& id, std::string const& linkend)
        {
            out << "<bridgehead renderas=\"sect" << level << "\"";
            if(!id.empty()) out << " id=\"" << id << "\"";
            out << ">";
            if(!linkend.empty()) out << "<link linkend=\"" << linkend << "\">";
            out << str;
            if(!linkend.empty()) out << "</link>";
            out << "</bridgehead>";
        }
    }

    void header_action(quickbook::actions& actions, value heading_list)
    {
        if(actions.suppress) return;

        value_consumer values = heading_list;

        bool generic = heading_list.get_tag() == block_tags::generic_heading;
        value element_id = values.optional_consume(general_tags::element_id);
        value content = values.consume();
        values.finish();

        int level;

        if (generic)
        {
            level = actions.section_level + 2;
                                            // section_level is zero-based. We need to use a
                                            // one-based heading which is one greater
                                            // than the current. Thus: section_level + 2.
            if (level > 6 )                 // The max is h6, clip it if it goes
                level =  6;                 // further than that
        }
        else
        {
            level = heading_list.get_tag() - block_tags::heading1 + 1;
        }

        std::string anchor;
        std::string linkend;

        if (!generic && qbk_version_n < 103) // version 1.2 and below
        {
            anchor = actions.section_id + '.' +
                detail::make_identifier(content.get_boostbook());
        }
        else
        {
            std::string id =
                !element_id.empty() ?
                    element_id.get_quickbook() :
                    detail::make_identifier(
                        qbk_version_n >= 106 ?
                            content.get_quickbook() :
                            content.get_boostbook()
                    );

            linkend = anchor =
                fully_qualified_id(actions.doc_id, actions.qualified_section_id, id);
        }

        actions.anchors.push_back(anchor);
        actions.output_pre(actions.out);
        
        write_bridgehead(actions.out, level,
            content.get_boostbook(), anchor + "-heading", linkend);
    }

    void simple_phrase_action::operator()(char mark) const
    {
        if(!actions.output_pre(out)) return;

        int tag =
            mark == '*' ? phrase_tags::bold :
            mark == '/' ? phrase_tags::italic :
            mark == '_' ? phrase_tags::underline :
            mark == '=' ? phrase_tags::teletype :
            0;
        
        assert(tag != 0);
        detail::markup markup = detail::markups[tag];

        value_consumer values = actions.values.get();
        value content = values.consume();
        values.finish();

        out << markup.pre;
        if (std::string const* ptr = find(macro, content.get_quickbook().c_str()))
        {
            out << *ptr;
        }
        else
        {
            out << content.get_boostbook();
        }
        out << markup.post;
    }

    bool cond_phrase_push::start()
    {
        saved_suppress = actions.suppress;
    
        value_consumer values = actions.values.get();
        bool condition = find(actions.macro,
            values.consume().get_quickbook().c_str());
    
        actions.suppress = actions.suppress || !condition;

        return true;
    }
    
    void cond_phrase_push::cleanup()
    {
        actions.suppress = saved_suppress;
    }

    namespace {
        int indent_length(std::string const& indent)
        {
            int length = 0;
            for(std::string::const_iterator
                first = indent.begin(), end = indent.end(); first != end; ++first)
            {
                switch(*first) {
                    case ' ': ++length; break;
                    // hardcoded tab to 4 for now
                    case '\t': length = ((length + 4) / 4) * 4; break;
                    default: BOOST_ASSERT(false);
                }
            }
            
            return length;
        }
    }

    void list_action(quickbook::actions& actions, value list)
    {
        if(actions.suppress) return;

        typedef std::pair<char, int> mark_type;
        std::stack<mark_type> list_marks;
        int list_indent = -1;

        BOOST_FOREACH(value_consumer values, list)
        {
            int new_indent = indent_length(
                    values.consume(general_tags::list_indent).get_quickbook());
            value mark_value = values.consume(general_tags::list_mark);
            std::string content = values.consume().get_boostbook();
            values.finish();

            char mark = mark_value.get_quickbook()[0];
            assert(mark == '*' || mark == '#');

            if(list_indent == -1) {
                assert(new_indent == 0);
            }

            if(new_indent > list_indent)
            {
                list_indent = new_indent;
                list_marks.push(mark_type(mark, list_indent));

                actions.out << ((mark == '#') ? "<orderedlist>\n" : "<itemizedlist>\n");
            }
            else if (new_indent < list_indent)
            {
                BOOST_ASSERT(!list_marks.empty());
                list_indent = new_indent;

                while (!list_marks.empty() && (list_indent < list_marks.top().second))
                {
                    char mark = list_marks.top().first;
                    list_marks.pop();
                    actions.out << "</simpara></listitem>";
                    actions.out << ((mark == '#') ? "\n</orderedlist>" : "\n</itemizedlist>");
                }
                actions.out << "</simpara></listitem>";
            }
            else
            {
                actions.out << "</simpara></listitem>";
            }

            if (mark != list_marks.top().first) // new_indent == list_indent
            {
                file_position const pos = mark_value.get_position();
                detail::outerr(actions.filename, pos.line)
                    << "Illegal change of list style near column " << pos.column << ".\n";
                detail::outwarn(actions.filename, pos.line)
                    << "Ignoring change of list style" << std::endl;
                ++actions.error_count;
            }
            
            actions.out << "<listitem><simpara>";
            actions.out << content;
        }

        assert(!list_marks.empty());
        while (!list_marks.empty())
        {
            char mark = list_marks.top().first;
            list_marks.pop();
            actions.out << "</simpara></listitem>";
            actions.out << ((mark == '#') ? "\n</orderedlist>" : "\n</itemizedlist>");
        }
    }

    // TODO: No need to check suppress since this is only used in the syntax
    //       highlighter. I should moved this or something.
    void span::operator()(iterator first, iterator last) const
    {
        out << "<phrase role=\"" << name << "\">";
        while (first != last)
            detail::print_char(*first++, out.get());
        out << "</phrase>";
    }

    void unexpected_char::operator()(iterator first, iterator last) const
    {
        file_position const pos = first.get_position();

        detail::outwarn(actions.filename, pos.line)
            << "in column:" << pos.column
            << ", unexpected character: " << detail::utf8(first, last)
            << "\n";

        // print out an unexpected character
        out << "<phrase role=\"error\">";
        while (first != last)
            detail::print_char(*first++, out.get());
        out << "</phrase>";
    }

    void anchor_action(quickbook::actions& actions, value anchor)
    {
        if(actions.suppress) return;
        
        value_consumer values = anchor;
        actions.anchors.push_back(values.consume().get_quickbook());
        values.finish();
    }

    void do_macro_action::operator()(std::string const& str) const
    {
        if(!actions.output_pre(phrase)) return;

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
        detail::print_space(ch, out.get());
    }

    void space::operator()(iterator first, iterator last) const
    {
        while (first != last)
            detail::print_space(*first++, out.get());
    }

    void pre_escape_back::operator()(iterator first, iterator last) const
    {
        escape_actions.phrase.push(); // save the stream
    }

    void post_escape_back::operator()(iterator first, iterator last) const
    {
        escape_actions.output_pre(escape_actions.phrase);
        out << escape_actions.phrase.str();
        escape_actions.phrase.pop(); // restore the stream
    }

    void source_mode_action(quickbook::actions& actions, value source_mode)
    {
        actions.source_mode = source_mode_tags::name(source_mode.get_tag());
    }

    void code_action::operator()(iterator first, iterator last) const
    {
        if(!actions.output_pre(out)) return;

        // preprocess the code section to remove the initial indentation
        std::string program(first, last);
        detail::unindent(program);
        if (program.size() == 0)
            return; // Nothing left to do here. The program is empty.

        iterator first_(program.begin(), first.get_position());
        iterator last_(program.end());

        // TODO: Shouldn't phrase be empty here? Why would it be output
        // after the code block?
        std::string save;
        phrase.swap(save);

        // print the code with syntax coloring
        std::string str = syntax_highlight(first_, last_, actions, actions.source_mode);

        phrase.swap(save);

        //
        // We must not place a \n after the <programlisting> tag
        // otherwise PDF output starts code blocks with a blank line:
        //
        out << "<programlisting>";
        out << str;
        out << "</programlisting>\n";
    }

    void inline_code_action::operator()(iterator first, iterator last) const
    {
        if(!actions.output_pre(out)) return;

        std::string save;
        out.swap(save);

        // print the code with syntax coloring
        std::string str = syntax_highlight(first, last, actions, actions.source_mode);

        out.swap(save);

        out << "<code>";
        out << str;
        out << "</code>";
    }

    void raw_char_action::operator()(char ch) const
    {
        if(!actions.output_pre(phrase)) return;
        phrase << ch;
    }

    void raw_char_action::operator()(iterator first, iterator /*last*/) const
    {
        if(!actions.output_pre(phrase)) return;
        phrase << *first;
    }

    void plain_char_action::operator()(char ch) const
    {
        if(!actions.output_pre(phrase)) return;
        detail::print_char(ch, phrase.get());
    }

    void plain_char_action::operator()(iterator first, iterator /*last*/) const
    {
        if(!actions.output_pre(phrase)) return;
        detail::print_char(*first, phrase.get());
    }

    void escape_unicode_action::operator()(iterator first, iterator last) const
    {
        if(!actions.output_pre(phrase)) return;

        while(first != last && *first == '0') ++first;

        // Just ignore \u0000
        // Maybe I should issue a warning?
        if(first == last) return;
        
        std::string hex_digits(first, last);
        
        if(hex_digits.size() == 2 && *first > '0' && *first <= '7') {
            using namespace std;
            detail::print_char(strtol(hex_digits.c_str(), 0, 16), phrase.get());
        }
        else {
            phrase << "&#x" << hex_digits << ";";
        }
    }

    void image_action(quickbook::actions& actions, value image)
    {
        if(!actions.output_pre(actions.phrase)) return;

        typedef std::map<std::string, value> attribute_map;
        attribute_map attributes;

        value_consumer values = image;
        attributes["fileref"] = values.consume();

        BOOST_FOREACH(value pair_, values)
        {
            value_consumer pair = pair_;
            value name = pair.consume();
            value value = pair.consume();
            pair.finish();
            if(!attributes.insert(std::make_pair(name.get_quickbook(), value)).second)
            {
                detail::outwarn(actions.filename, name.get_position().line)
                    << "Duplicate image attribute: "
                    << detail::utf8(name.get_quickbook())
                    << std::endl;
            }
        }
        
        values.finish();

        // Find the file basename and extension.
        //
        // Not using Boost.Filesystem because I want to stay in UTF-8.
        // Need to think about uri encoding.
        
        std::string fileref = attributes["fileref"].get_quickbook();

        // Check for windows paths, then convert.
        // A bit crude, but there you go.

        if(fileref.find('\\') != std::string::npos)
        {
            detail::outwarn(actions.filename, attributes["fileref"].get_position().line)
                << "Image path isn't portable: '"
                << detail::utf8(fileref)
                << "'"
                << std::endl;
        }

        boost::replace(fileref, '\\', '/');

        // Find the file basename and extension.
        //
        // Not using Boost.Filesystem because I want to stay in UTF-8.
        // Need to think about uri encoding.

        std::string::size_type pos;
        std::string stem,extension;

        pos = fileref.rfind('/');
        stem = pos == std::string::npos ?
            fileref :
            fileref.substr(pos + 1);

        pos = stem.rfind('.');
        if (pos != std::string::npos)
        {
            extension = stem.substr(pos + 1);
            stem = stem.substr(0, pos);
        }

        // Extract the alt tag, to use as a text description.
        // Or if there isn't one, use the stem of the file name.
        // TODO: IMO if there isn't an alt tag, then the description should
        //       be empty or missing.

        attribute_map::iterator alt_pos = attributes.find("alt");
        std::string alt_text = alt_pos != attributes.end() ?
            alt_pos->second.get_quickbook() : stem;
        attributes.erase("alt");

        if(extension == ".svg")
        {
           //
           // SVG's need special handling:
           //
           // 1) We must set the "format" attribute, otherwise
           //    HTML generation produces code that will not display
           //    the image at all.
           // 2) We need to set the "contentwidth" and "contentdepth"
           //    attributes, otherwise the image will be displayed inside
           //    a tiny box with scrollbars (Firefox), or else cropped to
           //    fit in a tiny box (IE7).
           //

           attributes.insert(attribute_map::value_type("format", qbk_value("SVG")));

           //
           // Image paths are relative to the html subdirectory:
           //
           // TODO: This seems wrong to me.
           //
           fs::path img = detail::generic_to_path(fileref);
           if(img.root_path().empty())
              img = "html" / img;  // relative path

           //
           // Now load the SVG file:
           //
           std::string svg_text;
           fs::ifstream fs(img);
           char c;
           while(fs.get(c) && fs.good())
              svg_text.push_back(c);
           //
           // Extract the svg header from the file:
           //
           std::string::size_type a, b;
           a = svg_text.find("<svg");
           b = svg_text.find('>', a);
           svg_text = (a == std::string::npos) ? "" : svg_text.substr(a, b - a);
           //
           // Now locate the "width" and "height" attributes
           // and borrow their values:
           //
           a = svg_text.find("width");
           a = svg_text.find('=', a);
           a = svg_text.find('\"', a);
           b = svg_text.find('\"', a + 1);
           if(a != std::string::npos)
           {
              attributes.insert(std::make_pair(
                "contentwidth", qbk_value(std::string(
                    svg_text.begin() + a + 1, svg_text.begin() + b))
                ));
           }
           a = svg_text.find("height");
           a = svg_text.find('=', a);
           a = svg_text.find('\"', a);
           b = svg_text.find('\"', a + 1);
           if(a != std::string::npos)
           {
              attributes.insert(std::make_pair(
                "contentdepth", qbk_value(std::string(
                    svg_text.begin() + a + 1, svg_text.begin() + b))
                ));
           }
        }

        actions.phrase << "<inlinemediaobject>";

        actions.phrase << "<imageobject><imagedata";
        
        BOOST_FOREACH(attribute_map::value_type const& attr, attributes)
        {
            actions.phrase << " " << attr.first << "=\"";

            std::string value = attr.second.get_quickbook();
            for(std::string::const_iterator
                first = value.begin(), last  = value.end();
                first != last; ++first)
            {
                if (*first == '\\' && ++first == last) break;
                detail::print_char(*first, actions.phrase.get());
            }

            actions.phrase << "\"";
        }

        actions.phrase << "></imagedata></imageobject>";

        // Add a textobject containing the alt tag from earlier.
        // This will be used for the alt tag in html.
        actions.phrase << "<textobject><phrase>";
        detail::print_string(alt_text, actions.phrase.get());
        actions.phrase << "</phrase></textobject>";

        actions.phrase << "</inlinemediaobject>";
    }

    void macro_definition_action(quickbook::actions& actions, quickbook::value macro_definition)
    {
        if(actions.suppress) return;

        value_consumer values = macro_definition;
        std::string macro_id = values.consume().get_quickbook();
        std::string phrase = values.consume().get_boostbook();
        values.finish();

        actions.copy_macros_for_write();
        actions.macro.add(
            macro_id.begin()
          , macro_id.end()
          , phrase);
    }

    void template_body_action(quickbook::actions& actions, quickbook::value template_definition)
    {
        if(actions.suppress) return;

        value_consumer values = template_definition;
        std::string identifier = values.consume().get_quickbook();

        std::vector<std::string> template_values;
        BOOST_FOREACH(value const& p, values.consume()) {
            template_values.push_back(p.get_quickbook());
        }

        BOOST_ASSERT(values.check(template_tags::block) || values.check(template_tags::phrase));
        value body = values.consume();
        BOOST_ASSERT(!values.check());
    
        if (!actions.templates.add(
            template_symbol(
                identifier,
                template_values,
                body.get_quickbook(),
                actions.filename,
                body.get_position(),
                body.get_tag() == template_tags::block,
                &actions.templates.top_scope())))
        {
            file_position const pos = body.get_position();
            detail::outerr(actions.filename, pos.line)
                << "Template Redefinition: " << detail::utf8(identifier) << std::endl;
            ++actions.error_count;
        }
    }

    namespace
    {
        iterator find_bracket_end(iterator begin, iterator const& end)
        {
            unsigned int depth = 1;

            while(depth > 0) {
                char const* search_chars = "[]\\";
                begin = std::find_first_of(begin, end, search_chars, search_chars + 3);
                if(begin == end) return begin;

                if(*begin == '\\')
                {
                    if(++begin == end) return begin;
                    ++begin;
                }
                else
                {
                    depth += (*begin == '[') ? 1 : -1;
                    ++begin;
                }
            }

            return begin;
        }

        iterator find_first_seperator(iterator const& begin, iterator const& end)
        {
            if(qbk_version_n < 105) {
                char const* whitespace = " \t\r\n";
                return std::find_first_of(begin, end, whitespace, whitespace + 4);
            }
            else {
                iterator pos = begin;

                while(true)
                {
                    char const* search_chars = " \t\r\n\\[";
                    pos = std::find_first_of(pos, end, search_chars, search_chars + 6);
                    if(pos == end) return pos;

                    switch(*pos)
                    {
                    case '[':
                        pos = find_bracket_end(++pos, end);
                        break;
                    case '\\':
                        if(++pos == end) return pos;
                        ++pos;
                        break;
                    default:
                        return pos;
                    }
                }
            }
        }
    
        bool break_arguments(
            std::vector<template_body>& args
          , std::vector<std::string> const& params
          , fs::path const& filename
          , file_position const& pos
        )
        {
            // Quickbook 1.4-: If there aren't enough parameters seperated by
            //                 '..' then seperate the last parameter using
            //                 whitespace.
            // Quickbook 1.5+: If '..' isn't used to seperate the parameters
            //                 then use whitespace to separate them
            //                 (2 = template name + argument).

            if (qbk_version_n < 105 || args.size() == 1)
            {
           
                while (args.size() < params.size())
                {
                    // Try to break the last argument at the first space found
                    // and push it into the back of args. Do this
                    // recursively until we have all the expected number of
                    // arguments, or if there are no more spaces left.

                    template_body& body = args.back();
                    iterator begin(body.content.begin(), body.position);
                    iterator end(body.content.end());
                    
                    iterator l_pos = find_first_seperator(begin, end);
                    if (l_pos == end)
                        break;
                    char const* whitespace = " \t\r\n";
                    char const* whitespace_end = whitespace + 4;
                    iterator r_pos = l_pos;
                    while(r_pos != end && std::find(whitespace, whitespace_end, *r_pos) != whitespace_end) ++r_pos;
                    if (r_pos == end)
                        break;
                    template_body second(std::string(r_pos, end), body.filename, r_pos.get_position(), false);
                    body.content = std::string(begin, l_pos);
                    args.push_back(second);
                }
            }

            if (args.size() != params.size())
            {
                detail::outerr(filename, pos.line)
                    << "Invalid number of arguments passed. Expecting: "
                    << params.size()
                    << " argument(s), got: "
                    << args.size()
                    << " argument(s) instead."
                    << std::endl;
                return false;
            }
            return true;
        }

        std::pair<bool, std::vector<std::string>::const_iterator>
        get_arguments(
            std::vector<template_body>& args
          , std::vector<std::string> const& params
          , template_scope const& scope
          , file_position const& pos
          , quickbook::actions& actions
        )
        {
            std::vector<template_body>::const_iterator arg = args.begin();
            std::vector<std::string>::const_iterator tpl = params.begin();
            std::vector<std::string> empty_params;


            // Store each of the argument passed in as local templates:
            while (arg != args.end())
            {
                if (!actions.templates.add(
                        template_symbol(*tpl, empty_params, arg->content,
                            arg->filename, arg->position, arg->is_block, &scope)))
                {
                    detail::outerr(actions.filename, pos.line)
                        << "Duplicate Symbol Found" << std::endl;
                    ++actions.error_count;
                    return std::make_pair(false, tpl);
                }
                ++arg; ++tpl;
            }
            return std::make_pair(true, tpl);
        }
        
        bool parse_template(
            template_body const& body
          , bool escape
          , quickbook::actions& actions
        )
        {
            // How do we know if we are to parse the template as a block or
            // a phrase? We apply a simple heuristic: if the body starts with
            // a newline, then we regard it as a block, otherwise, we parse
            // it as a phrase.
            //
            // Note: this is now done in the grammar.

            if (escape)
            {
                //  escape the body of the template
                //  we just copy out the literal body
                (body.is_block ? actions.out : actions.phrase) << body.content;
                return true;
            }
            else
            {
                if (!body.is_block)
                {
                    //  do a phrase level parse
                    actions.filename = body.filename;
                    iterator first(body.content.begin(), body.position);
                    iterator last(body.content.end());
                    
                    return cl::parse(first, last, actions.grammar().simple_phrase).full;
                }
                else
                {
                    //  do a block level parse
                    //  ensure that we have enough trailing newlines to eliminate
                    //  the need to check for end of file in the grammar.
                    
                    actions.filename = body.filename;
                    std::string content = body.content + "\n\n";
                    iterator first(content.begin(), body.position);
                    iterator last(content.end());

                    return cl::parse(first, last, actions.grammar().block).full;
                }
            }
        }
    }

    namespace detail
    {
        int callout_id = 0;
    }

    void do_template_action::operator()(iterator first, iterator) const
    {
        if(actions.suppress) return;

        file_position const pos = first.get_position();
        
        // Get the arguments
        value_consumer values = actions.values.get();

        bool template_escape = values.check(template_tags::escape);
        if(template_escape) values.consume();

        std::string identifier = values.consume(template_tags::identifier).get_quickbook();

        std::vector<template_body> args;

        BOOST_FOREACH(value arg, values)
        {
            BOOST_ASSERT(
                arg.get_tag() == template_tags::block ||
                arg.get_tag() == template_tags::phrase);

            args.push_back(
                template_body(
                    arg.get_quickbook(),
                    actions.filename,
                    arg.get_position(),
                    arg.get_tag() == template_tags::block
                ));
        }
        
        values.finish();

        ++actions.template_depth;
        if (actions.template_depth > actions.max_template_depth)
        {
            detail::outerr(actions.filename, pos.line)
                << "Infinite loop detected" << std::endl;
            --actions.template_depth;
            ++actions.error_count;
            return;
        }

        // The template arguments should have the scope that the template was
        // called from, not the template's own scope.
        //
        // Note that for quickbook 1.4- this value is just ignored when the
        // arguments are expanded.
        template_scope const& call_scope = actions.templates.top_scope();

        template_symbol const* symbol = actions.templates.find(identifier);
        BOOST_ASSERT(symbol);

        std::string block;
        std::string phrase;

        actions.push(); // scope the actions' states
        {
            // Store the current section level so that we can ensure that
            // [section] and [endsect] tags in the template are balanced.
            actions.min_section_level = actions.section_level;

            // Quickbook 1.4-: When expanding the tempalte continue to use the
            //                 current scope (the dynamic scope).
            // Quickbook 1.5+: Use the scope the template was defined in
            //                 (the static scope).
            if (qbk_version_n >= 105)
                actions.templates.set_parent_scope(*symbol->parent);

            ///////////////////////////////////
            // Initialise the arguments
            
            if (!symbol->callout)
            {
                // Break the arguments for a template
            
                if (!break_arguments(args, symbol->params, actions.filename, pos))
                {
                    actions.pop(); // restore the actions' states
                    --actions.template_depth;
                    ++actions.error_count;
                    return;
                }
            }
            else
            {
                if (!args.empty())
                {
                    detail::outerr(actions.filename, pos.line)
                        << "Arguments for code snippet."
                        <<std::endl;
                    ++actions.error_count;

                    args.clear();
                }

                unsigned int size = symbol->params.size();

                for(unsigned int i = 0; i < size; ++i)
                {
                    std::string callout_id = actions.doc_id +
                        boost::lexical_cast<std::string>(detail::callout_id + i);

                    std::string code;
                    code += "'''";
                    code += "<co id=\"" + callout_id + "co\" ";
                    code += "linkends=\"" + callout_id + "\" />";
                    code += "'''";

                    args.push_back(template_body(code, actions.filename, pos, false));
                }
            }

            ///////////////////////////////////
            // Prepare the arguments as local templates
            bool get_arg_result;
            std::vector<std::string>::const_iterator tpl;
            boost::tie(get_arg_result, tpl) =
                get_arguments(args, symbol->params,
                    call_scope, pos, actions);

            if (!get_arg_result)
            {
                actions.pop(); // restore the actions' states
                --actions.template_depth;
                return;
            }

            ///////////////////////////////////
            // parse the template body:

            if (!parse_template(symbol->body, template_escape, actions))
            {
                file_position const pos = first.get_position();
                detail::outerr(actions.filename, pos.line)
                    << "Expanding "
                    << (symbol->body.is_block ? "block" : "phrase")
                    << " template: " << detail::utf8(symbol->identifier) << std::endl
                    << std::endl
                    << "------------------begin------------------" << std::endl
                    << detail::utf8(symbol->body.content)
                    << "------------------end--------------------" << std::endl
                    << std::endl;
                actions.pop(); // restore the actions' states
                --actions.template_depth;
                ++actions.error_count;
                return;
            }

            if (actions.section_level != actions.min_section_level)
            {
                file_position const pos = first.get_position();
                detail::outerr(actions.filename, pos.line)
                    << "Mismatched sections in template " << detail::utf8(identifier) << std::endl;
                actions.pop(); // restore the actions' states
                --actions.template_depth;
                ++actions.error_count;
                return;
            }
        }

        actions.out.swap(block);
        actions.phrase.swap(phrase);
        actions.pop(); // restore the actions' states

        if(symbol->callout && symbol->callouts.size() > 0)
        {
            BOOST_ASSERT(phrase.empty());
            block += "<calloutlist>";
            BOOST_FOREACH(template_body const& c, symbol->callouts)
            {
                std::string callout_id = actions.doc_id +
                    boost::lexical_cast<std::string>(detail::callout_id++);

                std::string callout_value;
                actions.push();
                bool r = parse_template(c, false, actions);
                actions.out.swap(callout_value);
                actions.pop();

                if(!r)
                {
                    detail::outerr(c.filename, c.position.line)
                        << "Expanding callout." << std::endl
                        << "------------------begin------------------" << std::endl
                        << detail::utf8(c.content)
                        << std::endl
                        << "------------------end--------------------" << std::endl
                        ;
                    ++actions.error_count;
                    return;
                }
                
                block += "<callout arearefs=\"" + callout_id + "co\" ";
                block += "id=\"" + callout_id + "\">";
                block += callout_value;
                block += "</callout>";
            }
            block += "</calloutlist>";
        }

        if(symbol->body.is_block || !block.empty()) {
            actions.paragraph(); // For paragraphs before the template call.
            actions.out << block;
            actions.phrase << phrase;
        }
        else {
            actions.phrase << phrase;
        }
        --actions.template_depth;
    }

    void link_action(quickbook::actions& actions, value link)
    {
        if(!actions.output_pre(actions.phrase)) return;
        detail::markup markup = detail::markups[link.get_tag()];

        value_consumer values = link;
        value dst = values.consume();
        value content = values.consume();
        values.finish();
        
        actions.phrase << markup.pre;
        detail::print_string(dst.get_quickbook(), actions.phrase.get());
        actions.phrase << "\">";

        if (content.empty())
            detail::print_string(dst.get_quickbook(), actions.phrase.get());
        else
            actions.phrase << content.get_boostbook();

        actions.phrase << markup.post;
    }

    void variable_list_action(quickbook::actions& actions, value variable_list)
    {
        if(actions.suppress) return;

        value_consumer values = variable_list;
        std::string title = values.consume(table_tags::title).get_quickbook();

        actions.out << "<variablelist>\n";

        actions.out << "<title>";
        detail::print_string(title, actions.out.get());
        actions.out << "</title>\n";

        BOOST_FOREACH(value_consumer entry, values) {
            actions.out << start_varlistentry_;
            
            if(entry.check()) {
                actions.out << start_varlistterm_;
                actions.out << entry.consume().get_boostbook();
                actions.out << end_varlistterm_;
            }
            
            if(entry.check()) {
                actions.out << start_varlistitem_;
                BOOST_FOREACH(value phrase, entry) actions.out << phrase.get_boostbook();
                actions.out << end_varlistitem_;
            }

            actions.out << end_varlistentry_;
        }

        actions.out << "</variablelist>\n";
        
        values.finish();
    }

    void table_action(quickbook::actions& actions, value table)
    {
        if(actions.suppress) return;

        value_consumer values = table;

        std::string element_id;
        if(values.check(general_tags::element_id))
            element_id = values.consume().get_quickbook();

        std::string title = values.consume(table_tags::title).get_quickbook();
        bool has_title = !title.empty();
        
        std::string table_id;
        if(qbk_version_n >= 105) {
            if(!element_id.empty()) {
                table_id = fully_qualified_id(actions.doc_id,
                    actions.qualified_section_id, element_id);
            }
            else if(has_title) {
                table_id = fully_qualified_id(actions.doc_id,
                    actions.qualified_section_id,
                    detail::make_identifier(title));
            }
        }

        // Emulating the old behaviour which used the width of the final
        // row for span_count.
        int row_count = 0;
        int span_count = 0;

        value_consumer lookahead = values;
        BOOST_FOREACH(value row, lookahead) {
            ++row_count;
            span_count = boost::distance(row);
        }
        lookahead.finish();

        if (has_title)
        {
            actions.out << "<table frame=\"all\"";
            if(!table_id.empty())
                actions.out << " id=\"" << table_id << "\"";
            actions.out << ">\n";
            actions.out << "<title>";
            detail::print_string(title, actions.out.get());
            actions.out << "</title>";
        }
        else
        {
            actions.out << "<informaltable frame=\"all\"";
            if(!table_id.empty())
                actions.out << " id=\"" << table_id << "\"";
            actions.out << ">\n";
        }

        actions.out << "<tgroup cols=\"" << span_count << "\">\n";

        if (row_count > 1)
        {
            actions.out << "<thead>" << start_row_;
            BOOST_FOREACH(value cell, values.consume()) {
                actions.out << start_cell_ << cell.get_boostbook() << end_cell_;
            }
            actions.out << end_row_ << "</thead>\n";
        }

        actions.out << "<tbody>\n";

        BOOST_FOREACH(value row, values) {
            actions.out << start_row_;
            BOOST_FOREACH(value cell, row) {
                actions.out << start_cell_ << cell.get_boostbook() << end_cell_;
            }
            actions.out << end_row_;
        }
        
        values.finish();

        actions.out << "</tbody>\n"
                     << "</tgroup>\n";

        if (has_title)
        {
            actions.out << "</table>\n";
        }
        else
        {
            actions.out << "</informaltable>\n";
        }
    }

    void begin_section_action(quickbook::actions& actions, value begin_section_list)
    {    
        if(actions.suppress) return;

        value_consumer values = begin_section_list;

        value element_id = values.optional_consume(general_tags::element_id);
        value content = values.consume();
        values.finish();

        actions.section_id = !element_id.empty() ?
            element_id.get_quickbook() :
            detail::make_identifier(content.get_quickbook());

        if (actions.section_level != 0)
            actions.qualified_section_id += '.';
        else
            BOOST_ASSERT(actions.qualified_section_id.empty());

        actions.qualified_section_id += actions.section_id;
        ++actions.section_level;

        actions::string_list saved_anchors;
        saved_anchors.swap(actions.anchors);

        actions.output_pre(actions.out);

        if (qbk_version_n < 103) // version 1.2 and below
        {
            actions.out << "\n<section id=\""
                << actions.doc_id << "." << actions.section_id << "\">\n";
        }
        else // version 1.3 and above
        {
            actions.out << "\n<section id=\"" << actions.doc_id
                << "." << actions.qualified_section_id << "\">\n";
        }

        actions.out << "<title>";

        actions.anchors.swap(saved_anchors);
        actions.output_pre(actions.out);

        if (qbk_version_n < 103) // version 1.2 and below
        {
            actions.out << content.get_boostbook();
        }
        else // version 1.3 and above
        {
            actions.out << "<link linkend=\"" << actions.doc_id
                << "." << actions.qualified_section_id << "\">"
                << content.get_boostbook()
                << "</link>"
                ;
        }
        
        actions.out << "</title>\n";
    }

    void end_section_action(quickbook::actions& actions, value end_section, file_position pos)
    {
        if(!actions.output_pre(actions.out)) return;

        if (actions.section_level <= actions.min_section_level)
        {
            detail::outerr(actions.filename, pos.line)
                << "Mismatched [endsect] near column " << pos.column << ".\n";
            ++actions.error_count;
            
            return;
        }

        --actions.section_level;
        actions.out << "</section>";

        if (actions.section_level == 0)
        {
            actions.qualified_section_id.clear();
        }
        else
        {
            std::string::size_type const n =
                actions.qualified_section_id.find_last_of('.');
            actions.qualified_section_id.erase(n, std::string::npos);
        }
    }
    
    void element_id_warning_action::operator()(iterator first, iterator) const
    {
        file_position const pos = first.get_position();
        detail::outwarn(actions.filename, pos.line) << "Empty id.\n";        
    }

    fs::path path_difference(fs::path const& outdir, fs::path const& path)
    {
        fs::path outtmp, temp;
        fs::path::iterator out = outdir.begin(), file = path.begin();
        for(; out != outdir.end() && file != path.end(); ++out, ++file)
        {
            if(!fs::equivalent(outtmp /= *out, temp /= *file))
                break;
        }
        out = (out == outdir.begin()) ? outdir.end() : out;

        fs::path result = fs::path();
        for(; out != outdir.end(); ++out)
            if(*out != ".") result /= "..";
        std::divides<fs::path> concat;
        return std::accumulate(file, path.end(), result, concat);
    }

    std::string check_path(value const& path, quickbook::actions& actions)
    {
        std::string path_text = path.get_quickbook();

        if(path_text.find('\\') != std::string::npos)
        {
            detail::outwarn(actions.filename, path.get_position().line)
                << "Path isn't portable: "
                << detail::utf8(path_text)
                << std::endl;
        }
        
        boost::replace(path_text, '\\', '/');
        
        return path_text;
    }

    fs::path calculate_relative_path(std::string const& name, quickbook::actions& actions)
    {
        // Given a source file and the current filename, calculate the
        // path to the source file relative to the output directory.

        fs::path path = detail::generic_to_path(name);
        if (!path.has_root_directory() && !path.has_root_name())
        {
            fs::path infile = fs::absolute(actions.filename).normalize();
            path = (infile.parent_path() / path).normalize();
            fs::path xinclude_base = fs::absolute(actions.xinclude_base).normalize();
            path = path_difference(xinclude_base, path);
        }
        return path;
    }

    void xinclude_action(quickbook::actions& actions, value xinclude)
    {
        if(!actions.output_pre(actions.out)) return;

        value_consumer values = xinclude;
        fs::path path = calculate_relative_path(
            check_path(values.consume(), actions), actions);
        values.finish();

        actions.out << "\n<xi:include href=\"";
        detail::print_string(detail::escape_uri(path.generic_string()), actions.out.get());
        actions.out << "\" />\n";
    }

    namespace
    {
        fs::path include_search(fs::path const & current, std::string const & name)
        {
            fs::path path(name);

            // If the path is relative, try and resolve it.
            if (!path.has_root_directory() && !path.has_root_name())
            {
                // See if it can be found locally first.
                if (fs::exists(current / path))
                {
                    return current / path;
                }

                // Search in each of the include path locations.
                BOOST_FOREACH(fs::path full, include_path)
                {
                    full /= path;
                    if (fs::exists(full))
                    {
                        return full;
                    }
                }
            }

            return path;
        }
    }

    void import_action(quickbook::actions& actions, value import)
    {
        if(!actions.output_pre(actions.out)) return;

        value_consumer values = import;
        fs::path path = include_search(actions.filename.parent_path(),
            check_path(values.consume(), actions));
        values.finish();

        std::string ext = path.extension().generic_string();
        std::vector<template_symbol> storage;
        actions.error_count +=
            load_snippets(path.string(), storage, ext, actions.doc_id);

        BOOST_FOREACH(template_symbol& ts, storage)
        {
            std::string tname = ts.identifier;
            ts.parent = &actions.templates.top_scope();
            if (!actions.templates.add(ts))
            {
                detail::outerr(ts.body.filename, ts.body.position.line)
                    << "Template Redefinition: " << detail::utf8(tname) << std::endl;
                ++actions.error_count;
            }
        }
    }

    void include_action(quickbook::actions& actions, value include)
    {
        if(!actions.output_pre(actions.out)) return;

        value_consumer values = include;
        value include_doc_id = values.optional_consume(general_tags::include_id);
        fs::path filein = include_search(actions.filename.parent_path(),
            check_path(values.consume(), actions));
        values.finish();

        std::string doc_type, doc_id;

        // swap the filenames
        std::swap(actions.filename, filein);

        // save the doc info strings and source mode
        if(qbk_version_n >= 106) {
            doc_type = actions.doc_type;
            doc_id = actions.doc_id;
        }
        else {
            actions.doc_type.swap(doc_type);
            actions.doc_id.swap(doc_id);
        }
        
        // save the source mode and version info (only restored for 1.6+)
        std::string source_mode = actions.source_mode;
        unsigned qbk_version_n_store = qbk_version_n;

        // scope the macros
        string_symbols macro = actions.macro;
        std::size_t macro_change_depth = actions.macro_change_depth;
        // scope the templates
        //~ template_symbols templates = actions.templates; $$$ fixme $$$

        // if an id is specified in this include (as in [include:id foo.qbk])
        // then use it as the doc_id.
        if (!include_doc_id.empty())
            actions.doc_id = include_doc_id.get_quickbook();

        // update the __FILENAME__ macro
        *boost::spirit::classic::find(actions.macro, "__FILENAME__")
            = detail::path_to_generic(actions.filename);

        // save values
        actions.values.builder.save();

        // parse the file
        quickbook::parse_file(actions.filename.string().c_str(), actions, true);

        // restore the values
        actions.values.builder.restore();

        std::swap(actions.filename, filein);

        actions.doc_type.swap(doc_type);
        actions.doc_id.swap(doc_id);
        
        if(qbk_version_n >= 106 || qbk_version_n_store >= 106)
        {
            actions.source_mode = source_mode;

            qbk_version_n = qbk_version_n_store;
        }

        // restore the macros
        actions.macro = macro;
        actions.macro_change_depth = macro_change_depth;
        // restore the templates
        //~ actions.templates = templates; $$$ fixme $$$
    }

    void phrase_to_docinfo_action_impl::operator()(iterator first, iterator last,
            value::tag_type tag) const
    {
        if(!actions.output_pre(actions.phrase)) return;

        std::string encoded;
        actions.phrase.swap(encoded);
        actions.values.builder.insert(
            qbk_bbk_value(first, last, encoded, tag));
    }

    void phrase_to_docinfo_action_impl::operator()(iterator first, iterator last) const
    {
        return (*this)(first, last, value::default_tag);
    }
    
    void collector_to_value_action::operator()(iterator first, iterator last) const
    {
        if(!actions.output_pre(output)) return;

        std::string value;
        output.swap(value);
        actions.values.builder.insert(bbk_value(value, value::default_tag));
    }
    
    bool pre_output_action::operator()(collector& tgt) const
    {
        if(actions.suppress) return false;

        for(quickbook::actions::string_list::iterator
            it = actions.anchors.begin(),
            end = actions.anchors.end();
            it != end; ++it)
        {
            tgt << "<anchor id=\"";
            detail::print_string(*it, tgt.get());
            tgt << "\"/>\n";
        }
        
        actions.anchors.clear();

        return true;
    }
    
    bool pre_output_action::operator()(iterator, iterator) const
    {
        return (*this)(actions.out);
    }

    bool scoped_output_push::start()
    {
        actions.out.push();
        actions.phrase.push();
        actions.anchors.swap(saved_anchors);

        return true;
    }
    
    void scoped_output_push::cleanup()
    {
        actions.phrase.pop();
        actions.out.pop();
        actions.anchors.swap(saved_anchors);
    }

    bool set_no_eols_scoped::start()
    {
        saved_no_eols = actions.no_eols;
        actions.no_eols = false;

        return true;
    }

    void set_no_eols_scoped::cleanup()
    {
        actions.no_eols = saved_no_eols;
    }

    bool scoped_context_impl::start(int new_context)
    {
        saved_context_ = actions_.context;
        actions_.context = new_context;

        return true;
    }

    void scoped_context_impl::cleanup()
    {
        actions_.context = saved_context_;
    }
}
