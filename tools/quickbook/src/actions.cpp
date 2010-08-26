/*=============================================================================
    Copyright (c) 2002 2004 2006 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    Copyright (c) 2005 Thomas Guest
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#include <sstream>
#include <numeric>
#include <functional>
#include <algorithm>
#include <boost/bind.hpp>
#include <boost/filesystem/v2/convenience.hpp>
#include <boost/filesystem/v2/fstream.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/join.hpp>
#include "./quickbook.hpp"
#include "./actions.hpp"
#include "./utils.hpp"
#include "./markups.hpp"
#include "./actions_class.hpp"
#include "./block.hpp"
#include "./phrase.hpp"
#include "./code_snippet.hpp"

namespace quickbook
{
    char const* quickbook_get_date = "__quickbook_get_date__";
    char const* quickbook_get_time = "__quickbook_get_time__";

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

    // Handles line-breaks (DEPRECATED!!!)
    void break_action::operator()(iterator first, iterator) const
    {
        boost::spirit::classic::file_position const pos = first.get_position();
        detail::outwarn(pos.file,pos.line) << "in column:" << pos.column << ", "
            << "[br] and \\n are deprecated" << ".\n";
        phrase << break_mark;
    }

    void error_action::operator()(iterator first, iterator /*last*/) const
    {
        boost::spirit::classic::file_position const pos = first.get_position();
        detail::outerr(pos.file,pos.line)
            << "Syntax Error near column " << pos.column << ".\n";
        ++error_count;
    }

    void phrase_action::operator()(iterator first, iterator last) const
    {
        std::string str;
        phrase.swap(str);
        out << pre << str << post;
    }

    void implicit_paragraph_action::operator()() const
    {
        std::string str;
        phrase.swap(str);

        // TODO: Use spirit to do this?

        std::string::const_iterator
            pos = str.begin(),
            end = str.end();

        while(pos != end && (
            *pos == ' ' || *pos == '\t' || *pos == '\n' || *pos == '\r'))
        {
            ++pos;
        }

        if(pos != end) {
            out << pre << str << post;
        }
    }

    void header_action::operator()(iterator first, iterator last) const
    {
        std::string str;
        phrase.swap(str);

        if (qbk_version_n < 103) // version 1.2 and below
        {
            out << "<anchor id=\""
                << section_id << '.'
                << detail::make_identifier(str.begin(), str.end())
                << "\" />"
                << pre << str << post
                ;
        }
        else // version 1.3 and above
        {
            std::string id =
                !element_id.empty() ? element_id :
                qbk_version_n >= 106 ? detail::make_identifier(first, last) :
                detail::make_identifier(str.begin(), str.end());

            std::string anchor =
                fully_qualified_id(library_id, qualified_section_id, id);

            out << "<anchor id=\"" << anchor << "\"/>"
                << pre
                << "<link linkend=\"" << anchor << "\">"
                << str
                << "</link>"
                << post
                ;
        }
    }

    void generic_header_action::operator()(iterator first, iterator last) const
    {
        int level_ = section_level + 2;     // section_level is zero-based. We need to use a
                                            // 0ne-based heading which is one greater
                                            // than the current. Thus: section_level + 2.
        if (level_ > 6)                     // The max is h6, clip it if it goes
            level_ = 6;                     // further than that
        std::string str;
        phrase.swap(str);

        std::string id =
            !element_id.empty() ? element_id :
            qbk_version_n >= 106 ? detail::make_identifier(first, last) :
            detail::make_identifier(str.begin(), str.end());

        std::string anchor =
            fully_qualified_id(library_id, qualified_section_id, id);

        out
            << "<anchor id=\"" << anchor << "\"/>"
            << "<bridgehead renderas=\"sect" << level_ << "\">"
            << "<link linkend=\"" << anchor << "\">"
            << str
            << "</link>"
            << "</bridgehead>"
            ;
    }

    void simple_phrase_action::operator()(iterator first, iterator last) const
    {
        out << pre;
        std::string str(first, last);
        if (std::string const* ptr = find(macro, str.c_str()))
        {
            out << *ptr;
        }
        else
        {
            while (first != last)
                detail::print_char(*first++, out.get());
        }
        out << post;
    }

    void cond_phrase_action_pre::operator()(iterator first, iterator last) const
    {
        std::string str(first, last);
        conditions.push_back(find(macro, str.c_str()));
        out.push(); // save the stream
    }

    void cond_phrase_action_post::operator()(iterator first, iterator last) const
    {
        bool symbol_found = conditions.back();
        conditions.pop_back();

        if (first == last || !symbol_found)
        {
            out.pop(); // restore the stream
        }
        else
        {
            std::string save;
            out.swap(save);
            out.pop(); // restore the stream
            out << save; // print the body
        }
    }

    void list_action::operator()(iterator first, iterator last) const
    {
        BOOST_ASSERT(!list_marks.empty()); // there must be at least one item in the stack
        out << list_buffer.str();
        list_buffer.clear();

        while (!list_marks.empty())
        {
            char mark = list_marks.top().first;
            list_marks.pop();
            out << std::string((mark == '#') ? "\n</orderedlist>" : "\n</itemizedlist>");
            if (list_marks.size() >= 1)
                out << "</listitem>";
        }

        list_indent = -1; // reset
    }

    void list_format_action::operator()(iterator first, iterator last) const
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

        if (list_indent == -1) // the very start
        {
            BOOST_ASSERT(new_indent == 0);
        }

        if (new_indent > list_indent)
        {
            list_indent = new_indent;
            list_marks.push(mark_type(mark, list_indent));
            if (list_marks.size() > 1)
            {
                // Make this new list a child of the previous list.
                // The previous listelem has already ended so we erase
                // "</listitem>" to accomodate this sub-list. We'll close
                // the listelem later.

                std::string str;
                out.swap(str);
                std::string::size_type pos = str.rfind("</listitem>");
                BOOST_ASSERT(pos <= str.size());
                str.erase(str.begin()+pos, str.end());
                out << str;
            }
            out << std::string((mark == '#') ? "<orderedlist>\n" : "<itemizedlist>\n");
        }

        else if (new_indent < list_indent)
        {
            BOOST_ASSERT(!list_marks.empty());
            list_indent = new_indent;

            while (!list_marks.empty() && (list_indent < list_marks.top().second))
            {
                char mark = list_marks.top().first;
                list_marks.pop();
                out << std::string((mark == '#') ? "\n</orderedlist>" : "\n</itemizedlist>");
                if (list_marks.size() >= 1)
                    out << "</listitem>";
            }
        }

        if (mark != list_marks.top().first) // new_indent == list_indent
        {
            boost::spirit::classic::file_position const pos = first.get_position();
            detail::outerr(pos.file,pos.line)
                << "Illegal change of list style near column " << pos.column << ".\n";
            detail::outwarn(pos.file,pos.line)
                << "Ignoring change of list style" << std::endl;
            ++error_count;
        }
    }

    void span::operator()(iterator first, iterator last) const
    {
        out << "<phrase role=\"" << name << "\">";
        while (first != last)
            detail::print_char(*first++, out.get());
        out << "</phrase>";
    }

    void unexpected_char::operator()(iterator first, iterator last) const
    {
        boost::spirit::classic::file_position const pos = first.get_position();

        detail::outwarn(pos.file, pos.line)
            << "in column:" << pos.column
            << ", unexpected character: " << std::string(first, last)
            << "\n";

        // print out an unexpected character
        out << "<phrase role=\"error\">";
        while (first != last)
            detail::print_char(*first++, out.get());
        out << "</phrase>";
    }

    void anchor_action::operator()(iterator first, iterator last) const
    {
        out << "<anchor id=\"";
        while (first != last)
            detail::print_char(*first++, out.get());
        out << "\" />\n";
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
        out << escape_actions.phrase.str();
        escape_actions.phrase.pop(); // restore the stream
    }

    void code_action::operator()(iterator first, iterator last) const
    {
        // preprocess the code section to remove the initial indentation
        std::string program(first, last);
        detail::unindent(program);
        if (program.size() == 0)
            return; // Nothing left to do here. The program is empty.

        iterator first_(program.begin(), program.end());
        iterator last_(program.end(), program.end());
        first_.set_position(first.get_position());

        std::string save;
        phrase.swap(save);

        // print the code with syntax coloring
        std::string str = syntax_p(first_, last_);

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
        std::string save;
        out.swap(save);

        // print the code with syntax coloring
        std::string str = syntax_p(first, last);

        out.swap(save);

        out << "<code>";
        out << str;
        out << "</code>";
    }

    void raw_char_action::operator()(char ch) const
    {
        phrase << ch;
    }

    void raw_char_action::operator()(iterator first, iterator /*last*/) const
    {
        phrase << *first;
    }

    void plain_char_action::operator()(char ch) const
    {
        detail::print_char(ch, phrase.get());
    }

    void plain_char_action::operator()(iterator first, iterator /*last*/) const
    {
        detail::print_char(*first, phrase.get());
    }

    void escape_unicode_action::operator()(iterator first, iterator last) const
    {
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

    void attribute_action::operator()(iterator first, iterator last) const
    {
        boost::spirit::classic::file_position const pos = first.get_position();

        if (!attributes.insert(
                attribute_map::value_type(attribute_name, std::string(first, last))
            ).second)
        {
            detail::outwarn(pos.file,pos.line)
                << "Repeated attribute: " << attribute_name << ".\n";
        }
    }

    void image_action::operator()(iterator, iterator) const
    {
        fs::path const img_path(image_fileref);
        
        attribute_map::iterator it = attributes.find("alt");
        std::string alt_text = it != attributes.end() ? it->second : img_path.stem();
        attributes.erase("alt");

        attributes.insert(attribute_map::value_type("fileref", image_fileref));

        if(img_path.extension() == ".svg")
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
           attributes.insert(attribute_map::value_type("format", "SVG"));
           //
           // Image paths are relative to the html subdirectory:
           //
           fs::path img;
           if(img_path.root_path().empty())
              img = "html" / img_path;  // relative path
           else
              img = img_path;   // absolute path
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
              attributes.insert(attribute_map::value_type("contentwidth",
                std::string(svg_text.begin() + a + 1, svg_text.begin() + b)));
           }
           a = svg_text.find("height");
           a = svg_text.find('=', a);
           a = svg_text.find('\"', a);
           b = svg_text.find('\"', a + 1);
           if(a != std::string::npos)
           {
              attributes.insert(attribute_map::value_type("contentdepth",
                std::string(svg_text.begin() + a + 1, svg_text.begin() + b)));
           }
        }

        phrase << "<inlinemediaobject>";

        phrase << "<imageobject><imagedata";
        
        for(attribute_map::const_iterator
            attr_first = attributes.begin(), attr_last  = attributes.end();
            attr_first != attr_last; ++attr_first)
        {
            phrase << " " << attr_first->first << "=\"";

            for(std::string::const_iterator
                first = attr_first->second.begin(),
                last  = attr_first->second.end();
                first != last; ++first)
            {
                if (*first == '\\' && ++first == last) break;
                detail::print_char(*first, phrase.get());
            }

            phrase << "\"";
        }

        phrase << "></imagedata></imageobject>";

        // Also add a textobject -- use the basename of the image file.
        // This will mean we get "alt" attributes of the HTML img.
        phrase << "<textobject><phrase>";
        detail::print_string(alt_text, phrase.get());
        phrase << "</phrase></textobject>";

        phrase << "</inlinemediaobject>";
    }

    void macro_identifier_action::operator()(iterator first, iterator last) const
    {
        actions.macro_id.assign(first, last);
        actions.phrase.push(); // save the phrase
    }

    void macro_definition_action::operator()(iterator first, iterator last) const
    {
        actions.macro.add(
            actions.macro_id.begin()
          , actions.macro_id.end()
          , actions.phrase.str());
        actions.phrase.pop(); // restore the phrase
    }

    void template_body_action::operator()(iterator first, iterator last) const
    {
        if (!actions.templates.add(
            template_symbol(actions.template_identifier, actions.template_info,
                std::string(first, last), first.get_position(),
                actions.template_block, &actions.templates.top_scope())))
        {
            boost::spirit::classic::file_position const pos = first.get_position();
            detail::outerr(pos.file,pos.line)
                << "Template Redefinition: " << actions.template_identifier << std::endl;
            ++actions.error_count;
        }

        actions.template_identifier.clear();
        actions.template_info.clear();
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
          , boost::spirit::classic::file_position const& pos
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
                    iterator begin(body.content.begin(), body.content.end(), body.position.file);
                    iterator end(body.content.end(), body.content.end());
                    
                    iterator l_pos = find_first_seperator(begin, end);
                    if (l_pos == end)
                        break;
                    char const* whitespace = " \t\r\n";
                    char const* whitespace_end = whitespace + 4;
                    iterator r_pos = l_pos;
                    while(r_pos != end && std::find(whitespace, whitespace_end, *r_pos) != whitespace_end) ++r_pos;
                    if (r_pos == end)
                        break;
                    template_body second(std::string(r_pos, end), begin.get_position(), false);
                    body.content = std::string(begin, l_pos);
                    args.push_back(second);
                }
            }

            if (args.size() != params.size())
            {
                detail::outerr(pos.file, pos.line)
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
          , boost::spirit::classic::file_position const& pos
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
                            arg->position, arg->is_block, &scope)))
                {
                    detail::outerr(pos.file,pos.line)
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
          , std::string& result
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
                result = body.content;
                return true;
            }
            else if (!body.is_block)
            {
                simple_phrase_grammar phrase_p(actions);

                //  do a phrase level parse
                iterator first(body.content.begin(), body.content.end(), body.position);
                iterator last(body.content.end(), body.content.end());
                bool r = boost::spirit::classic::parse(first, last, phrase_p).full;
                actions.phrase.swap(result);
                return r;
            }
            else
            {
                block_grammar block_p(actions, true);

                //  do a block level parse
                //  ensure that we have enough trailing newlines to eliminate
                //  the need to check for end of file in the grammar.
                
                std::string content = body.content + "\n\n";
                iterator first(content.begin(), content.end(), body.position);
                iterator last(content.end(), content.end());
                bool r = boost::spirit::classic::parse(first, last, block_p).full;
                actions.inside_paragraph();
                actions.out.swap(result);
                return r;
            }
        }
    }

    namespace detail
    {
        int callout_id = 0;
    }

    void template_arg_action::operator()(iterator first, iterator last) const
    {
        actions.template_args.push_back(
            template_body(
                std::string(first, last),
                first.get_position(),
                actions.template_block));
    }

    void do_template_action::operator()(iterator first, iterator) const
    {
        // Get the arguments and clear values stored in action.

        std::vector<template_body> args;
        std::string identifier;
        std::swap(args, actions.template_args);
        std::swap(identifier, actions.template_identifier);
        boost::spirit::classic::file_position const pos = first.get_position();

        ++actions.template_depth;
        if (actions.template_depth > actions.max_template_depth)
        {
            detail::outerr(pos.file,pos.line)
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
            
        std::string result;
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
            
                if (!break_arguments(args, symbol->params, pos))
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
                    detail::outerr(pos.file, pos.line)
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

                    args.push_back(template_body(code, first.get_position(), false));
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

            if (!parse_template(symbol->body, actions.template_escape, result, actions))
            {
                boost::spirit::classic::file_position const pos = first.get_position();
                detail::outerr(pos.file,pos.line)
                    << "Expanding "
                    << (symbol->body.is_block ? "block" : "phrase")
                    << " template: " << symbol->identifier << std::endl
                    << std::endl
                    << "------------------begin------------------" << std::endl
                    << symbol->body.content
                    << "------------------end--------------------" << std::endl
                    << std::endl;
                actions.pop(); // restore the actions' states
                --actions.template_depth;
                ++actions.error_count;
                return;
            }

            if (actions.section_level != actions.min_section_level)
            {
                boost::spirit::classic::file_position const pos = first.get_position();
                detail::outerr(pos.file,pos.line)
                    << "Mismatched sections in template " << identifier << std::endl;
                actions.pop(); // restore the actions' states
                --actions.template_depth;
                ++actions.error_count;
                return;
            }
        }

        actions.pop(); // restore the actions' states

        if(symbol->callout && symbol->callouts.size() > 0)
        {
            result += "<calloutlist>";
            BOOST_FOREACH(template_body const& c, symbol->callouts)
            {
                std::string callout_id = actions.doc_id +
                    boost::lexical_cast<std::string>(detail::callout_id++);

                std::string callout_value;
                actions.push();
                bool r = parse_template(c, false, callout_value, actions);
                actions.pop();

                if(!r)
                {
                    detail::outerr(c.position.file, c.position.line)
                        << "Expanding callout." << std::endl;
                    ++actions.error_count;
                    return;
                }
                
                result += "<callout arearefs=\"" + callout_id + "co\" ";
                result += "id=\"" + callout_id + "\">";
                result += callout_value;
                result += "</callout>";
            }
            result += "</calloutlist>";
        }

        if(symbol->body.is_block) {
            actions.inside_paragraph();
            actions.temp_para << result; // print it!!!
        }
        else {
            actions.phrase << result; // print it!!!
        }
        --actions.template_depth;
    }

    void link_action::operator()(iterator first, iterator last) const
    {
        iterator save = first;
        phrase << tag;
        while (first != last)
            detail::print_char(*first++, phrase.get());
        phrase << "\">";

        // Yes, it is safe to dereference last here. When we
        // reach here, *last is certainly valid. We test if
        // *last == ']'. In which case, the url is the text.
        // Example: [@http://spirit.sourceforge.net/]

        if (*last == ']')
        {
            first = save;
            while (first != last)
                detail::print_char(*first++, phrase.get());
        }
    }

    void variablelist_action::operator()(iterator, iterator) const
    {
        actions.out << "<variablelist>\n";

        actions.out << "<title>";
        std::string::iterator first = actions.table_title.begin();
        std::string::iterator last = actions.table_title.end();
        while (first != last)
            detail::print_char(*first++, actions.out.get());
        actions.out << "</title>\n";

        std::string str;
        actions.phrase.swap(str);
        actions.out << str;

        actions.out << "</variablelist>\n";
        actions.table_span = 0;
        actions.table_header.clear();
        actions.table_title.clear();
    }

    void start_varlistitem_action::operator()() const
    {
        phrase << start_varlistitem_;
        phrase.push();
    }

    void end_varlistitem_action::operator()() const
    {
        std::string str;
        temp_para.swap(str);
        phrase.pop();
        phrase << str << end_varlistitem_;
    }

    void table_action::operator()(iterator, iterator) const
    {
        std::string::iterator first = actions.table_title.begin();
        std::string::iterator last = actions.table_title.end();
        bool has_title = first != last;
        
        std::string table_id;
        if(qbk_version_n >= 105) {
            if(!actions.element_id.empty()) {
                table_id = fully_qualified_id(actions.doc_id,
                    actions.qualified_section_id, actions.element_id);
            }
            else if(has_title) {
                table_id = fully_qualified_id(actions.doc_id,
                    actions.qualified_section_id,
                    detail::make_identifier(first, last));
            }
        }

        if (has_title)
        {
            actions.out << "<table frame=\"all\"";
            if(!table_id.empty())
                actions.out << " id=\"" << table_id << "\"";
            actions.out << ">\n";
            actions.out << "<title>";
            while (first != last)
                detail::print_char(*first++, actions.out.get());
            actions.out << "</title>";
        }
        else
        {
            actions.out << "<informaltable frame=\"all\"";
            if(!table_id.empty())
                actions.out << " id=\"" << table_id << "\"";
            actions.out << ">\n";
        }

        actions.out << "<tgroup cols=\"" << actions.table_span << "\">\n";

        if (!actions.table_header.empty())
        {
            actions.out << "<thead>" << actions.table_header << "</thead>\n";
        }

        actions.out << "<tbody>\n";

        std::string str;
        actions.phrase.swap(str);
        actions.out << str;

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

        actions.table_span = 0;
        actions.table_header.clear();
        actions.table_title.clear();
    }

    void start_row_action::operator()(char) const
    {
        // the first row is the header
        if (header.empty() && !phrase.str().empty())
        {
            phrase.swap(header);
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
        phrase.push();
        ++span;
    }

    void end_col_action::operator()(char) const
    {
        std::string str;
        temp_para.swap(str);
        phrase.pop();
        phrase << str << end_cell_;
    }

    void begin_section_action::operator()(iterator first, iterator last) const
    {
        section_id = element_id.empty() ?
            detail::make_identifier(first, last) :
            element_id;

        if (section_level != 0)
            qualified_section_id += '.';
        else
            BOOST_ASSERT(qualified_section_id.empty());
        qualified_section_id += section_id;
        ++section_level;

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
        phrase.swap(str);

        if (qbk_version_n < 103) // version 1.2 and below
        {
            out << "<title>" << str << "</title>\n";
        }
        else // version 1.3 and above
        {
            out << "<title>"
                << "<link linkend=\"" << library_id
                    << "." << qualified_section_id << "\">"
                << str
                << "</link>"
                << "</title>\n"
                ;
        }
    }

    void end_section_action::operator()(iterator first, iterator last) const
    {
        if (section_level <= min_section_level)
        {
            boost::spirit::classic::file_position const pos = first.get_position();
            detail::outerr(pos.file,pos.line)
                << "Mismatched [endsect] near column " << pos.column << ".\n";
            ++error_count;
            
            return;
        }

        --section_level;
        out << "</section>";

        if (section_level == 0)
        {
            qualified_section_id.clear();
        }
        else
        {
            std::string::size_type const n =
                qualified_section_id.find_last_of('.');
            qualified_section_id.erase(n, std::string::npos);
        }
    }
    
    void element_id_warning_action::operator()(iterator first, iterator) const
    {
        boost::spirit::classic::file_position const pos = first.get_position();
        detail::outwarn(pos.file,pos.line) << "Empty id.\n";        
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

    fs::path calculate_relative_path(
        iterator first, iterator last, quickbook::actions& actions)
    {
        // Given a source file and the current filename, calculate the
        // path to the source file relative to the output directory.
        fs::path path(std::string(first, last));
        if (!path.is_complete())
        {
            fs::path infile = fs::complete(actions.filename).normalize();
            path = (infile.parent_path() / path).normalize();
            fs::path outdir = fs::complete(actions.outdir).normalize();
            path = path_difference(outdir, path);
        }
        return path;
    }

    void xinclude_action::operator()(iterator first, iterator last) const
    {
        fs::path path = calculate_relative_path(first, last, actions);
        out << "\n<xi:include href=\"";
        detail::print_string(detail::escape_uri(path.string()), out.get());
        out << "\" />\n";
    }

    void code_snippet_actions::append_code()
    {
        if(snippet_stack.empty()) return;
        snippet_data& snippet = snippet_stack.top();
    
        if (!code.empty())
        {
            detail::unindent(code); // remove all indents

            if(snippet.content.empty())
            {
                snippet.start_code = true;
            }
            else if(!snippet.end_code)
            {
                snippet.content += "\n\n";
                snippet.content += source_type;
                snippet.content += "```\n";
            }
            
            snippet.content += code;
            snippet.end_code = true;

            code.clear();
        }
    }

    void code_snippet_actions::close_code()
    {
        if(snippet_stack.empty()) return;
        snippet_data& snippet = snippet_stack.top();
    
        if(snippet.end_code)
        {
            snippet.content += "```\n\n";
            snippet.end_code = false;
        }
    }

    void code_snippet_actions::pass_thru(iterator first, iterator last)
    {
        if(snippet_stack.empty()) return;
        code += *first;
    }

    void code_snippet_actions::pass_thru_char(char c)
    {
        if(snippet_stack.empty()) return;
        code += c;
    }

    void code_snippet_actions::callout(iterator first, iterator last)
    {
        if(snippet_stack.empty()) return;
        code += "``[[callout" + boost::lexical_cast<std::string>(callout_id) + "]]``";
    
        snippet_stack.top().callouts.push_back(
            template_body(std::string(first, last), first.get_position(), true));
        ++callout_id;
    }

    void code_snippet_actions::escaped_comment(iterator first, iterator last)
    {
        if(snippet_stack.empty()) return;
        snippet_data& snippet = snippet_stack.top();
        append_code();
        close_code();

        std::string temp(first, last);
        detail::unindent(temp); // remove all indents
        if (temp.size() != 0)
        {
            snippet.content += "\n" + temp; // add a linebreak to allow block markups
        }
    }

    void code_snippet_actions::start_snippet(iterator first, iterator last)
    {
        append_code();
        snippet_stack.push(snippet_data(id, callout_id));
        id.clear();
    }

    void code_snippet_actions::end_snippet(iterator first, iterator last)
    {
        // TODO: Error?
        if(snippet_stack.empty()) return;

        append_code();

        snippet_data snippet = snippet_stack.top();
        snippet_stack.pop();

        std::string body;
        if(snippet.start_code) {
            body += "\n\n";
            body += source_type;
            body += "```\n";
        }
        body += snippet.content;
        if(snippet.end_code) {
            body += "```\n\n";
        }
        
        std::vector<std::string> params;
        for (size_t i = 0; i < snippet.callouts.size(); ++i)
        {
            params.push_back("[callout" + boost::lexical_cast<std::string>(snippet.callout_base_id + i) + "]");
        }
        
        // TODO: Save position in start_snippet
        template_symbol symbol(snippet.id, params, body, first.get_position(), true);
        symbol.callout = true;
        symbol.callouts = snippet.callouts;
        storage.push_back(symbol);

        // Merge the snippet into its parent

        if(!snippet_stack.empty())
        {
            snippet_data& next = snippet_stack.top();
            if(!snippet.content.empty()) {
                if(!snippet.start_code) {
                    close_code();
                }
                else if(!next.end_code) {
                    next.content += "\n\n";
                    next.content += source_type;
                    next.content += "```\n";
                }
                
                next.content += snippet.content;
                next.end_code = snippet.end_code;
            }
            
            next.callouts.insert(next.callouts.end(), snippet.callouts.begin(), snippet.callouts.end());
        }
    }

    int load_snippets(
        std::string const& file
      , std::vector<template_symbol>& storage   // snippets are stored in a
                                                // vector of template_symbols
      , std::string const& extension
      , std::string const& doc_id)
    {
        std::string code;
        int err = detail::load(file, code);
        if (err != 0)
            return err; // return early on error

        typedef position_iterator<std::string::const_iterator> iterator_type;
        iterator_type first(code.begin(), code.end(), file);
        iterator_type last(code.end(), code.end());

        size_t fname_len = file.size();
        bool is_python = fname_len >= 3
            && file[--fname_len]=='y' && file[--fname_len]=='p' && file[--fname_len]=='.';
        code_snippet_actions a(storage, doc_id, is_python ? "[python]" : "[c++]");
        // TODO: Should I check that parse succeeded?
        if(is_python) {
            boost::spirit::classic::parse(first, last, python_code_snippet_grammar(a));
        }
        else {
            boost::spirit::classic::parse(first, last, cpp_code_snippet_grammar(a));
        }

        return 0;
    }

    namespace
    {
        fs::path include_search(fs::path const & current, std::string const & name)
        {
            fs::path path(name);

            // If the path is relative, try and resolve it.
            if (!path.is_complete())
            {
                // See if it can be found locally first.
                if (fs::exists(current / path))
                {
                    return current / path;
                }

                // Search in each of the include path locations.
                BOOST_FOREACH(std::string const & p, include_path)
                {
                    fs::path full(p);
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

    void import_action::operator()(iterator first, iterator last) const
    {
        fs::path path = include_search(actions.filename.parent_path(), std::string(first,last));
        std::string ext = path.extension();
        std::vector<template_symbol> storage;
        actions.error_count +=
            load_snippets(path.string(), storage, ext, actions.doc_id);

        BOOST_FOREACH(template_symbol& ts, storage)
        {
            std::string tname = ts.identifier;
            ts.parent = &actions.templates.top_scope();
            if (!actions.templates.add(ts))
            {
                boost::spirit::classic::file_position const pos = ts.body.position;
                detail::outerr(pos.file, pos.line)
                    << "Template Redefinition: " << tname << std::endl;
                ++actions.error_count;
            }
        }
    }

    void include_action::operator()(iterator first, iterator last) const
    {
        fs::path filein = include_search(actions.filename.parent_path(), std::string(first,last));
        std::string doc_type, doc_id;
        docinfo_string doc_dirname, doc_last_revision;

        // swap the filenames
        std::swap(actions.filename, filein);

        // save the doc info strings
        if(qbk_version_n >= 106) {
            doc_type = actions.doc_type;
            doc_id = actions.doc_id;
            doc_dirname = actions.doc_dirname;
            doc_last_revision = actions.doc_last_revision;
        }
        else {
            actions.doc_type.swap(doc_type);
            actions.doc_id.swap(doc_id);
            actions.doc_dirname.swap(doc_dirname);
            actions.doc_last_revision.swap(doc_last_revision);
        }
        
        // save the version info
        unsigned qbk_major_version_store = qbk_major_version;
        unsigned qbk_minor_version_store = qbk_minor_version;
        unsigned qbk_version_n_store = qbk_version_n;

        // scope the macros
        string_symbols macro = actions.macro;
        // scope the templates
        //~ template_symbols templates = actions.templates; $$$ fixme $$$

        // if an id is specified in this include (as in [include:id foo.qbk])
        // then use it as the doc_id.
        if (!actions.include_doc_id.empty())
        {
            actions.doc_id = actions.include_doc_id;
            actions.include_doc_id.clear();
        }

        // update the __FILENAME__ macro
        *boost::spirit::classic::find(actions.macro, "__FILENAME__") = actions.filename.file_string();

        // parse the file
        quickbook::parse_file(actions.filename.file_string().c_str(), actions, true);

        // restore the values
        std::swap(actions.filename, filein);

        actions.doc_type.swap(doc_type);
        actions.doc_id.swap(doc_id);
        actions.doc_dirname.swap(doc_dirname);
        actions.doc_last_revision.swap(doc_last_revision);
        
        if(qbk_version_n >= 106 || qbk_version_n_store >= 106)
        {
            qbk_major_version = qbk_major_version_store;
            qbk_minor_version = qbk_minor_version_store;
            qbk_version_n = qbk_version_n_store;
        }

        // restore the macros
        actions.macro = macro;
        // restore the templates
        //~ actions.templates = templates; $$$ fixme $$$
    }

    std::string const& docinfo_string::get(unsigned version) const
    {
        return (qbk_version_n < version) ? raw : encoded;
    }

    static void write_document_title(collector& out, quickbook::actions& actions);
    static void write_document_info(collector& out, quickbook::actions& actions);

    void pre(collector& out, quickbook::actions& actions, bool ignore_docinfo)
    {
        // The doc_info in the file has been parsed. Here's what we'll do
        // *before* anything else.

        if (!actions.doc_id_tmp.empty())
            actions.doc_id = actions.doc_id_tmp.get(103);

        if (actions.doc_id.empty())
            actions.doc_id = detail::make_identifier(
                actions.doc_title.raw.begin(),actions.doc_title.raw.end());

        if (actions.doc_dirname.empty() && actions.doc_type == "library") {
            if (!actions.doc_id_tmp.empty()) {
                actions.doc_dirname = actions.doc_id_tmp;
            }
            else {
                actions.doc_dirname.raw = actions.doc_dirname.encoded = actions.doc_id;
            }
        }

        actions.doc_id_tmp.clear();

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
            actions.doc_last_revision.raw = actions.doc_last_revision.encoded = strdate;
        }

        // if we're ignoring the document info, we're done.
        if (ignore_docinfo)
        {
            return;
        }

        // Quickbook version

        if (qbk_major_version == -1)
        {
            // hard code quickbook version to v1.1
            qbk_major_version = 1;
            qbk_minor_version = 1;
            qbk_version_n = 101;
            detail::outwarn(actions.filename.file_string(),1)
                << "Warning: Quickbook version undefined. "
                "Version 1.1 is assumed" << std::endl;
        }
        else
        {
            qbk_version_n = ((unsigned) qbk_major_version * 100) +
                (unsigned) qbk_minor_version;
        }
        
        if (qbk_version_n == 106)
        {
            detail::outwarn(actions.filename.file_string(),1)
                << "Quickbook 1.6 is still under development and is "
                "likely to change in the future." << std::endl;
        }
        else if(qbk_version_n < 100 || qbk_version_n > 106)
        {
            detail::outerr(actions.filename.file_string(),1)
                << "Unknown version of quickbook: quickbook "
                << qbk_major_version
                << "."
                << qbk_minor_version
                << std::endl;
            ++actions.error_count;
        }

        // Warn about invalid fields

        if (actions.doc_type != "library")
        {
            std::vector<std::string> invalid_attributes;

            if (!actions.doc_purpose.empty())
                invalid_attributes.push_back("purpose");

            if (!actions.doc_categories.empty())
                invalid_attributes.push_back("category");

            if (!actions.doc_dirname.empty())
                invalid_attributes.push_back("dirname");

            if(!invalid_attributes.empty())
            {
                detail::outwarn(actions.filename.file_string(),1)
                    << (invalid_attributes.size() > 1 ?
                        "Invalid attributes" : "Invalid attribute")
                    << " for '" << actions.doc_type << " document info': "
                    << boost::algorithm::join(invalid_attributes, ", ")
                    << "\n"
                    ;
            }
        }

        // Write out header

        out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            << "<!DOCTYPE "
            << actions.doc_type
            << " PUBLIC \"-//Boost//DTD BoostBook XML V1.0//EN\"\n"
            << "     \"http://www.boost.org/tools/boostbook/dtd/boostbook.dtd\">\n"
            << '<' << actions.doc_type << "\n"
            << "    id=\""
            << actions.doc_id
            << "\"\n";
        
        if(actions.doc_type == "library")
        {
            out << "    name=\"" << actions.doc_title.get(103) << "\"\n";
        }

        if(!actions.doc_dirname.empty())
        {
            out << "    dirname=\""
                << actions.doc_dirname.get(103)
                << "\"\n";
        }

        out << "    last-revision=\""
            << actions.doc_last_revision.get(103)
            << "\" \n"
            << "    xmlns:xi=\"http://www.w3.org/2001/XInclude\">\n";
            
        if(actions.doc_type == "library") {
            write_document_info(out, actions);
            write_document_title(out, actions);
        }
        else {
            write_document_title(out, actions);
            write_document_info(out, actions);
        }
    }
    
    void post(collector& out, quickbook::actions& actions, bool ignore_docinfo)
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

    void write_document_title(collector& out, quickbook::actions& actions)
    {
        if (!actions.doc_title.empty())
        {
            out << "  <title>"
                << actions.doc_title.get(103);
            if (!actions.doc_version.empty()) {
                out << ' ' << actions.doc_version.get(103);
            }
            out<< "</title>\n\n\n";
        }
    }

    void write_document_info(collector& out, quickbook::actions& actions)
    {
        std::ostringstream tmp;

        if(!actions.doc_authors.empty())
        {
            tmp << "    <authorgroup>\n";
            for(actions::author_list::const_iterator
                it = actions.doc_authors.begin(),
                end = actions.doc_authors.end();
                it != end; ++it)
            {
                tmp << "      <author>\n"
                    << "        <firstname>"
                    << it->first.get(103)
                    << "</firstname>\n"
                    << "        <surname>"
                    << it->second.get(103)
                    << "</surname>\n"
                    << "      </author>\n";
            }
            tmp << "    </authorgroup>\n";
        }

        if (!actions.doc_copyrights.empty())
        {
            for(actions::copyright_list::const_iterator
                it = actions.doc_copyrights.begin(),
                end = actions.doc_copyrights.end();
                it != end; ++it)
            {
                tmp << "\n" << "    <copyright>\n";
        
                for(actions::string_list::const_iterator
                    it2 = it->first.begin(),
                    end = it->first.end();
                    it2 != end; ++it2)
                {
                    tmp << "      <year>" << *it2 << "</year>\n";
                }
        
                tmp << "      <holder>"
                    << it->second.get(103)
                    << "</holder>\n"
                    << "    </copyright>\n"
                    << "\n"
                ;
            }
        }

        if (!actions.doc_license.empty())
        {
            tmp << "    <legalnotice>\n"
                << "      <para>\n"
                << "        " << actions.doc_license.get(103) << "\n"
                << "      </para>\n"
                << "    </legalnotice>\n"
                << "\n"
            ;
        }

        if (!actions.doc_purpose.empty())
        {
            tmp << "    <" << actions.doc_type << "purpose>\n"
                << "      " << actions.doc_purpose.get(103)
                << "    </" << actions.doc_type << "purpose>\n"
                << "\n"
                ;
        }

        if (!actions.doc_categories.empty())
        {
            for(actions::docinfo_list::const_iterator
                it = actions.doc_categories.begin(),
                end = actions.doc_categories.end();
                it != end; ++it)
            {
                tmp << "    <" << actions.doc_type << "category name=\"category:"
                    << it->get(103)
                    << "\"></" << actions.doc_type << "category>\n"
                    << "\n"
                ;
            }
        }

        std::string value = tmp.str();
        if(!value.empty())
        {
            out << "  <" << actions.doc_type << "info>\n"
                << value
                << "  </" << actions.doc_type << "info>\n"
                << "\n"
            ;
        }
    }

    void phrase_to_string_action::operator()(iterator first, iterator last) const
    {
        out.clear();
        phrase.swap(out);
    }

    void phrase_to_docinfo_action::operator()(iterator first, iterator last) const
    {
        out.encoded.clear();
        phrase.swap(out.encoded);
        out.raw = std::string(first, last);
    }

    void copy_stream_action::operator()(iterator first, iterator last) const
    {
        std::string str;
        phrase.swap(str);
        out << str;
    }
}
