/*=============================================================================
    Copyright (c) 2002 2004 2006 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_QUICKBOOK_ACTIONS_HPP)
#define BOOST_SPIRIT_QUICKBOOK_ACTIONS_HPP

#include <map>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <boost/filesystem/v2/operations.hpp>
#include <boost/foreach.hpp>
#include <boost/tuple/tuple.hpp>
#include "fwd.hpp"
#include "collector.hpp"
#include "template_stack.hpp"
#include "utils.hpp"

#ifdef BOOST_MSVC
// disable copy/assignment could not be generated, unreferenced formal params
#pragma warning (push)
#pragma warning(disable : 4511 4512 4100)
#endif

namespace quickbook
{
    namespace cl = boost::spirit::classic;
    namespace fs = boost::filesystem;

    extern int qbk_major_version;
    extern int qbk_minor_version;
    extern unsigned qbk_version_n; // qbk_major_version * 100 + qbk_minor_version

    struct quickbook_range {
        template <typename Arg>
        struct result
        {
            typedef bool type;
        };
        
        quickbook_range(unsigned min_, unsigned max_)
            : min_(min_), max_(max_) {}
        
        bool operator()() const {
            return qbk_version_n >= min_ && qbk_version_n < max_;
        }

        unsigned min_, max_;
    };
    
    inline quickbook_range qbk_since(unsigned min_) {
        return quickbook_range(min_, 999);
    }
    
    inline quickbook_range qbk_before(unsigned max_) {
        return quickbook_range(0, max_);
    }

    typedef cl::symbols<std::string> string_symbols;
    typedef std::map<std::string, std::string> attribute_map;

    int load_snippets(std::string const& file, std::vector<template_symbol>& storage,
        std::string const& extension, std::string const& doc_id);
    std::string syntax_highlight(
        iterator first, iterator last,
        actions& escape_actions,
        std::string const& source_mode);        

    struct error_action
    {
        // Prints an error message to std::cerr

        error_action(
            int& error_count)
        : error_count(error_count) {}

        void operator()(iterator first, iterator /*last*/) const;

        int& error_count;
    };

    struct tagged_action
    {
        tagged_action(
            collector& out,
            std::string const& pre,
            std::string const& post)
        : out(out)
        , pre(pre)
        , post(post) {}

        void operator()(std::string const&) const;

        collector& out;
        std::string pre;
        std::string post;
    };

    struct phrase_action
    {
        //  blurb, blockquote, preformatted, list_item,
        //  unordered_list, ordered_list

        phrase_action(
            collector& out,
            collector& phrase,
            std::string const& pre,
            std::string const& post)
        : out(out)
        , phrase(phrase)
        , pre(pre)
        , post(post) {}

        void operator()(iterator first, iterator last) const;

        collector& out;
        collector& phrase;
        std::string pre;
        std::string post;
    };

    struct implicit_paragraph_action
    {
        //  implicit paragraphs
        //  doesn't output the paragraph if it's only whitespace.

        implicit_paragraph_action(
            collector& out,
            collector& phrase,
            std::string const& pre,
            std::string const& post)
        : out(out)
        , phrase(phrase)
        , pre(pre)
        , post(post) {}

        void operator()() const;
        void operator()(iterator first, iterator last) const { (*this)(); }

        collector& out;
        collector& phrase;
        std::string pre;
        std::string post;
    };

    struct header_action
    {
        //  Handles paragraph, h1, h2, h3, h4, h5, h6,

        header_action(
            collector& out,
            collector& phrase,
            std::string const& element_id,
            std::string const& library_id,
            std::string const& section_id,
            std::string const& qualified_section_id,
            std::string const& pre,
            std::string const& post)
        : out(out)
        , phrase(phrase)
        , element_id(element_id)
        , library_id(library_id)
        , section_id(section_id)
        , qualified_section_id(qualified_section_id)
        , pre(pre)
        , post(post) {}

        void operator()(iterator first, iterator last) const;

        collector& out;
        collector& phrase;
        std::string const& element_id;
        std::string const& library_id;
        std::string const& section_id;
        std::string const& qualified_section_id;
        std::string pre;
        std::string post;
    };

    struct generic_header_action
    {
        //  Handles h

        generic_header_action(
            collector& out,
            collector& phrase,
            std::string const& element_id,
            std::string const& library_id,
            std::string const& section_id,
            std::string const& qualified_section_id,
            int const& section_level)
        : out(out)
        , phrase(phrase)
        , element_id(element_id)
        , library_id(library_id)
        , section_id(section_id)
        , qualified_section_id(qualified_section_id)
        , section_level(section_level) {}

        void operator()(iterator first, iterator last) const;

        collector& out;
        collector& phrase;
        std::string const& element_id;
        std::string const& library_id;
        std::string const& section_id;
        std::string const& qualified_section_id;
        int const& section_level;
    };

    struct simple_phrase_action
    {
        //  Handles simple text formats

        simple_phrase_action(
            collector& out
          , std::string const& pre
          , std::string const& post
          , string_symbols const& macro)
        : out(out)
        , pre(pre)
        , post(post)
        , macro(macro) {}

        void operator()(iterator first, iterator last) const;

        collector& out;
        std::string pre;
        std::string post;
        string_symbols const& macro;
    };

    struct cond_phrase_action_pre
    {
        //  Handles conditional phrases

        cond_phrase_action_pre(
            collector& out
          , std::vector<bool>& conditions
          , string_symbols const& macro)
        : out(out)
        , conditions(conditions)
        , macro(macro) {}

        void operator()(iterator first, iterator last) const;

        collector& out;
        std::vector<bool>& conditions;
        string_symbols const& macro;
    };

    struct cond_phrase_action_post
    {
        //  Handles conditional phrases

        cond_phrase_action_post(
            collector& out
          , std::vector<bool>& conditions
          , string_symbols const& macro)
        : out(out)
        , conditions(conditions)
        , macro(macro) {}

        void operator()(iterator first, iterator last) const;

        collector& out;
        std::vector<bool>& conditions;
        string_symbols const& macro;
    };

    struct list_action
    {
        //  Handles lists

        typedef std::pair<char, int> mark_type;
        list_action(
            collector& out
          , collector& list_buffer
          , int& list_indent
          , std::stack<mark_type>& list_marks)
        : out(out)
        , list_buffer(list_buffer)
        , list_indent(list_indent)
        , list_marks(list_marks) {}

        void operator()(iterator first, iterator last) const;

        collector& out;
        collector& list_buffer;
        int& list_indent;
        std::stack<mark_type>& list_marks;
    };

    struct list_format_action
    {
        //  Handles list formatting and hierarchy

        typedef std::pair<char, int> mark_type;
        list_format_action(
            collector& out
          , int& list_indent
          , std::stack<mark_type>& list_marks
          , int& error_count)
        : out(out)
        , list_indent(list_indent)
        , list_marks(list_marks)
        , error_count(error_count) {}

        void operator()(iterator first, iterator last) const;

        collector& out;
        int& list_indent;
        std::stack<mark_type>& list_marks;
        int& error_count;
    };

    struct span
    {
        // Decorates c++ code fragments

        span(char const* name, collector& out)
        : name(name), out(out) {}

        void operator()(iterator first, iterator last) const;

        char const* name;
        collector& out;
    };

    struct unexpected_char
    {
        // Handles unexpected chars in c++ syntax

        unexpected_char(collector& out)
        : out(out) {}

        void operator()(iterator first, iterator last) const;

        collector& out;
    };

    struct anchor_action
    {
        // Handles anchors

        anchor_action(collector& out)
            : out(out) {}

        void operator()(iterator first, iterator last) const;

        collector& out;
    };

    extern char const* quickbook_get_date;
    extern char const* quickbook_get_time;

    struct do_macro_action
    {
        // Handles macro substitutions

        do_macro_action(collector& phrase)
            : phrase(phrase) {}

        void operator()(std::string const& str) const;
        collector& phrase;
    };

    struct space
    {
        // Prints a space

        space(collector& out)
            : out(out) {}

        void operator()(iterator first, iterator last) const;
        void operator()(char ch) const;

        collector& out;
    };

    struct pre_escape_back
    {
        // Escapes back from code to quickbook (Pre)

        pre_escape_back(actions& escape_actions, std::string& save)
            : escape_actions(escape_actions), save(save) {}

        void operator()(iterator first, iterator last) const;

        actions& escape_actions;
        std::string& save;
    };

    struct post_escape_back
    {
        // Escapes back from code to quickbook (Post)

        post_escape_back(collector& out, actions& escape_actions, std::string& save)
            : out(out), escape_actions(escape_actions), save(save) {}

        void operator()(iterator first, iterator last) const;

        collector& out;
        actions& escape_actions;
        std::string& save;
    };

    struct raw_char_action
    {
        // Prints a single raw (unprocessed) char.
        // Allows '<', '>'... etc.

        raw_char_action(collector& phrase)
        : phrase(phrase) {}

        void operator()(char ch) const;
        void operator()(iterator first, iterator /*last*/) const;

        collector& phrase;
    };

    struct plain_char_action
    {
        // Prints a single plain char.
        // Converts '<' to "&lt;"... etc See utils.hpp

        plain_char_action(collector& phrase)
        : phrase(phrase) {}

        void operator()(char ch) const;
        void operator()(iterator first, iterator /*last*/) const;

        collector& phrase;
    };
    
    struct escape_unicode_action
    {
        escape_unicode_action(collector& phrase) : phrase(phrase) {}
        void operator()(iterator first, iterator last) const;

        collector& phrase;
    };

    struct attribute_action
    {
        // Handle image attributes
        
        attribute_action(
            attribute_map& attributes
          , std::string& attribute_name
          , int& error_count)
        : attributes(attributes)
        , attribute_name(attribute_name)
        , error_count(error_count) {}

        void operator()(iterator first, iterator last) const;

        attribute_map& attributes;
        std::string& attribute_name;
        int& error_count;
    };

    struct image_action
    {
        // Handles inline images

        image_action(
            collector& phrase
          , attribute_map& attributes
          , std::string& image_fileref)
        : phrase(phrase)
        , attributes(attributes)
        , image_fileref(image_fileref) {}

        void operator()(iterator first, iterator last) const;

        collector& phrase;
        attribute_map& attributes;
        std::string& image_fileref;
    };

    struct markup_action
    {
        // A generic markup action

        markup_action(collector& phrase, std::string const& str)
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

        collector& phrase;
        std::string str;
    };
    
    struct code_action
    {
        // Does the actual syntax highlighing of code

        code_action(
            collector& out
          , collector& phrase
          , quickbook::actions& actions)
        : out(out)
        , phrase(phrase)
        , actions(actions)
        {
        }

        void operator()(iterator first, iterator last) const;

        collector& out;
        collector& phrase;
        quickbook::actions& actions;
    };

    struct inline_code_action
    {
        // Does the actual syntax highlighing of code inlined in text

        inline_code_action(
            collector& out
          , quickbook::actions& actions)
        : out(out)
        , actions(actions)
        {}

        void operator()(iterator first, iterator last) const;

        collector& out;
        quickbook::actions& actions;
    };

    struct break_action
    {
        // Handles line-breaks (DEPRECATED!!!)

        break_action(collector& phrase)
        : phrase(phrase) {}

        void operator()(iterator f, iterator) const;

        collector& phrase;
    };

    struct macro_identifier_action
    {
        // Handles macro identifiers

        macro_identifier_action(quickbook::actions& actions)
        : actions(actions) {}

        void operator()(iterator first, iterator last) const;

        quickbook::actions& actions;
    };

    struct macro_definition_action
    {
        // Handles macro definitions

        macro_definition_action(quickbook::actions& actions)
        : actions(actions) {}

        void operator()(iterator first, iterator last) const;

        quickbook::actions& actions;
    };

    struct template_body_action
    {
        // Handles template definitions

        template_body_action(quickbook::actions& actions)
        : actions(actions) {}

        void operator()(iterator first, iterator last) const;

        quickbook::actions& actions;
    };
    
    struct template_arg_action
    {
        // Handles a template argument

        template_arg_action(quickbook::actions& actions)
        : actions(actions) {}
        
        void operator()(iterator first, iterator last) const;

        quickbook::actions& actions;
    };

    struct do_template_action
    {
        // Handles template substitutions

        do_template_action(quickbook::actions& actions)
        : actions(actions) {}

        void operator()(iterator first, iterator last) const;

        quickbook::actions& actions;
    };

    struct link_action
    {
        // Handles links (URL, XML refentry, function, class, member)

        link_action(collector& phrase, char const* tag)
        : phrase(phrase), tag(tag) {}

        void operator()(iterator first, iterator last) const;

        collector& phrase;
        char const* tag;
    };

    struct variablelist_action
    {
        // Handles variable lists

        variablelist_action(quickbook::actions& actions)
        : actions(actions) {}

        void operator()(iterator, iterator) const;

        quickbook::actions& actions;
    };

    struct table_action
    {
        // Handles tables

        table_action(quickbook::actions& actions)
        : actions(actions) {}

        void operator()(iterator, iterator) const;

        quickbook::actions& actions;
    };

    struct start_row_action
    {
        // Handles table rows

        start_row_action(collector& phrase, unsigned& span, std::string& header)
            : phrase(phrase), span(span), header(header) {}

        void operator()(char) const;
        void operator()(iterator f, iterator) const;

        collector& phrase;
        unsigned& span;
        std::string& header;
    };

    struct col_action
    {
        col_action(collector& phrase, unsigned& span)
        : phrase(phrase), span(span) {}

        void operator()(std::string const&) const;

        collector& phrase;
        unsigned& span;
    };

    struct begin_section_action
    {
        // Handles begin page

        begin_section_action(
            collector& out
          , collector& phrase
          , std::string& library_id
          , std::string& section_id
          , int& section_level
          , std::string& qualified_section_id
          , std::string& element_id)
        : out(out)
        , phrase(phrase)
        , library_id(library_id)
        , section_id(section_id)
        , section_level(section_level)
        , qualified_section_id(qualified_section_id)
        , element_id(element_id) {}

        void operator()(iterator first, iterator last) const;

        collector& out;
        collector& phrase;
        std::string& library_id;
        std::string& section_id;
        int& section_level;
        std::string& qualified_section_id;
        std::string& element_id;
    };

    struct end_section_action
    {
        end_section_action(
            collector& out
          , int& section_level
          , int& min_section_level
          , std::string& qualified_section_id
          , int& error_count)
        : out(out)
        , section_level(section_level)
        , min_section_level(min_section_level)
        , qualified_section_id(qualified_section_id)
        , error_count(error_count) {}

        void operator()(iterator first, iterator last) const;

        collector& out;
        int& section_level;
        int& min_section_level;
        std::string& qualified_section_id;
        int& error_count;
   };
   
   struct element_id_warning_action
   {
       void operator()(iterator first, iterator last) const;
   };

    struct xinclude_action
    {
        // Handles XML includes
        xinclude_action(collector& out_, quickbook::actions& actions_)
            : out(out_), actions(actions_) {}

        void operator()(iterator first, iterator last) const;

        collector& out;
        quickbook::actions& actions;
    };

    struct include_action
    {
        // Handles QBK includes

        include_action(quickbook::actions& actions_)
            : actions(actions_) {}

        void operator()(iterator first, iterator last) const;

        quickbook::actions& actions;
    };

    struct import_action
    {
        // Handles import of source code files (e.g. *.cpp *.py)
        import_action(collector& out_, quickbook::actions& actions_)
            : out(out_), actions(actions_) {}

        void operator()(iterator first, iterator last) const;

        collector& out;
        quickbook::actions& actions;
    };

    struct docinfo_string {
        std::string raw;
        std::string encoded;

        docinfo_string() : raw(), encoded() {}

        void swap(docinfo_string& x) {
            raw.swap(x.raw);
            encoded.swap(x.encoded);
        }

        void clear() {
            raw.clear();
            encoded.clear();
        }

        bool empty() const {
            return raw.empty();
        }

        std::string const& get(unsigned version) const;
    };

    void pre(collector& out, quickbook::actions& actions, bool ignore_docinfo = false);
    void post(collector& out, quickbook::actions& actions, bool ignore_docinfo = false);

    struct phrase_to_string_action
    {
        phrase_to_string_action(std::string& out, collector& phrase)
            : out(out) , phrase(phrase) {}

        void operator()(iterator first, iterator last) const;

        std::string& out;
        collector& phrase;
    };

    struct phrase_to_docinfo_action
    {
        phrase_to_docinfo_action(docinfo_string& out, collector& phrase)
            : out(out)
            , phrase(phrase) {}

        void operator()(iterator first, iterator last) const;

        docinfo_string& out;
        collector& phrase;
    };
}

#ifdef BOOST_MSVC
#pragma warning (pop)
#endif

#endif // BOOST_SPIRIT_QUICKBOOK_ACTIONS_HPP

