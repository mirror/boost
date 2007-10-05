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
#include <map>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <sstream>
#include <boost/spirit/iterator/position_iterator.hpp>
#include <boost/filesystem/operations.hpp>
#include "../syntax_highlight.hpp"
#include "utils.hpp"

#ifdef BOOST_MSVC
// disable copy/assignment could not be generated, unreferenced formal params
#pragma warning(disable : 4511 4512 4100)
#endif

namespace quickbook
{
    namespace fs = boost::filesystem;
    typedef std::vector<char> file_storage;
    typedef position_iterator<file_storage::const_iterator> iterator;
    typedef std::string::const_iterator string_iterator;
    struct actions;
    extern tm* current_time; // the current time
    extern tm* current_gm_time; // the current UTC time
    extern bool debug_mode; 
    extern unsigned qbk_major_version;
    extern unsigned qbk_minor_version;
    extern unsigned qbk_version_n; // qbk_major_version * 100 + qbk_minor_version

    // forward declarations
    struct actions;
    int parse(char const* filein_, actions& actor, bool ignore_docinfo = false);

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
        const char* preformatted_pre    = "<programlisting>";
        const char* preformatted_post   = "</programlisting>";
        const char* warning_pre         = "<warning><para>";
        const char* warning_post        = "</para></warning>";
        const char* caution_pre         = "<caution><para>";
        const char* caution_post        = "</para></caution>";
        const char* important_pre     = "<important><para>";
        const char* important_post    = "</para></important>";
        const char* note_pre            = "<note><para>";
        const char* note_post           = "</para></note>";
        const char* tip_pre             = "<tip><para>";
        const char* tip_post            = "</para></tip>";
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
        const char* strikethrough_pre_  = "<emphasis role=\"strikethrough\">";
        const char* strikethrough_post_ = "</emphasis>";
        const char* quote_pre_          = "<quote>";
        const char* quote_post_         = "</quote>";
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
        const char* footnote_pre_       = "<footnote><para>";
        const char* footnote_post_      = "</para></footnote>";
        const char* escape_pre_         = "<!--quickbook-escape-prefix-->";
        const char* escape_post_        = "<!--quickbook-escape-postfix-->";
        const char* replaceable_pre_    = "<replaceable>";
        const char* replaceable_post_   = "</replaceable>";
    }
    
    struct error_action
    {
        // Prints an error message to std::cerr

        void operator()(iterator const& first, iterator const& /*last*/) const;
    };

    struct phrase_action
    {
        //  blurb, blockquote, preformatted, list_item,
        //  unordered_list, ordered_list

        phrase_action(
            std::ostream&       out,
            std::stringstream&  phrase,
            std::string const&  pre,
            std::string const&  post)
        : out(out)
        , phrase(phrase)
        , pre(pre)
        , post(post) {}

        void operator()(iterator const& first, iterator const& last) const;

        std::ostream&       out;
        std::stringstream&  phrase;
        std::string         pre;
        std::string         post;
    };

    struct anchored_phrase_action
    {
        //  Handles paragraph, h1, h2, h3, h4, h5, h6,

        anchored_phrase_action(
            std::ostream&       out,
            std::stringstream&  phrase,
            std::string const&  library_id,
            std::string const&  section_id,
            std::string const&  qualified_section_id,
            std::string const&  pre,
            std::string const&  post)
        : out(out)
        , phrase(phrase)
        , library_id(library_id)
        , section_id(section_id)
        , qualified_section_id(qualified_section_id)
        , pre(pre)
        , post(post) {}

        void operator()(iterator const& first, iterator const& last) const;

        std::ostream&       out;
        std::stringstream&  phrase;
        std::string const&  library_id;
        std::string const&  section_id;
        std::string const&  qualified_section_id;
        std::string         pre;
        std::string         post;
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

        void operator()(iterator first, iterator const& last) const;

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

        void operator()(iterator const& first, iterator const& last) const;

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

        void operator()(iterator first, iterator const& last) const;

        std::stringstream& out;
        int& indent;
        std::stack<mark_type>& list_marks;
    };

    struct span
    {
        // Decorates c++ code fragments

        span(char const* name, std::ostream& out)
        : name(name), out(out) {}

        void operator()(iterator first, iterator const& last) const;

        char const* name;
        std::ostream& out;
    };

    struct unexpected_char
    {
        // Handles unexpected chars in c++ syntax

        unexpected_char(std::ostream& out)
        : out(out) {}

        void operator()(char) const;

        std::ostream& out;
    };

    struct anchor_action
    {
        // Handles anchors

        anchor_action(std::ostream& out)
            : out(out) {}

        void operator()(iterator first, iterator const& last) const;

        std::ostream& out;
    };

    namespace
    {
        char const* quickbook_get_date = "__quickbook_get_date__";
        char const* quickbook_get_time = "__quickbook_get_time__";
    }

    struct do_macro_action
    {
        // Handles macro substitutions

        do_macro_action(std::ostream& phrase)
        : phrase(phrase) {}

        void operator()(std::string const& str) const;
        std::ostream& phrase;
    };

    struct space
    {
        // Prints a space

        space(std::ostream& out)
        : out(out) {}

        void operator()(iterator first, iterator const& last) const;
        void operator()(char ch) const;

        std::ostream& out;
    };

    struct pre_escape_back
    {
        // Escapes back from code to quickbook (Pre)

        pre_escape_back(actions& escape_actions, std::string& save)
            : escape_actions(escape_actions), save(save) {}

        void operator()(iterator const& first, iterator const& last) const;

        actions& escape_actions;
        std::string& save;
    };

    struct post_escape_back
    {
        // Escapes back from code to quickbook (Post)

        post_escape_back(std::ostream& out, actions& escape_actions, std::string& save)
            : out(out), escape_actions(escape_actions), save(save) {}

        void operator()(iterator const& first, iterator const& last) const;

        std::ostream& out;
        actions& escape_actions;
        std::string& save;
    };

    typedef symbols<std::string> macros_type;
    typedef cpp_highlight<
        span
      , space
      , macros_type
      , do_macro_action
      , pre_escape_back
      , post_escape_back
      , actions
      , unexpected_char
      , std::ostream>
    cpp_p_type;
        
    typedef python_highlight<
        span
      , space
      , macros_type
      , do_macro_action
      , pre_escape_back
      , post_escape_back
      , actions
      , unexpected_char
      , std::ostream>
    python_p_type;

    struct code_action
    {
        // Does the actual syntax highlighing of code

        code_action(std::ostream& out,
                    std::stringstream& phrase,
                    std::stringstream& temp,
                    std::string const& source_mode,
                    macros_type const& macro,
                    actions& escape_actions)
        : out(out)
        , phrase(phrase)
        , temp(temp)
        , source_mode(source_mode)
        , cpp_p(temp, macro, do_macro_action(temp), escape_actions)
        , python_p(temp, macro, do_macro_action(temp), escape_actions)
        {
        }

        void operator()(iterator const& first, iterator const& last) const;

        std::ostream& out;
        std::stringstream& phrase;
        std::stringstream& temp;
        std::string const& source_mode;

        cpp_p_type cpp_p;
        python_p_type python_p;
    };

    struct inline_code_action
    {
        // Does the actual syntax highlighing of code inlined in text

        inline_code_action(std::stringstream& out,
                           std::stringstream& temp,
                           std::string const& source_mode,
                           macros_type const& macro,
                           actions& escape_actions)
        : out(out)
        , source_mode(source_mode)
        , temp(temp)
        , cpp_p(temp, macro, do_macro_action(temp), escape_actions)
        , python_p(temp, macro, do_macro_action(temp), escape_actions)
        {}

        void operator()(iterator const& first, iterator const& last) const;

        std::stringstream& out;
        std::string const& source_mode;
        std::stringstream& temp;

        cpp_p_type cpp_p;
        python_p_type python_p;
    };

    struct raw_char_action
    {
        // Prints a single raw (unprocessed) char.
        // Allows '<', '>'... etc.

        raw_char_action(std::ostream& phrase)
        : phrase(phrase) {}

        void operator()(char ch) const;
        void operator()(iterator const& first, iterator const& /*last*/) const;

        std::ostream& phrase;
    };

    struct plain_char_action
    {
        // Prints a single plain char.
        // Converts '<' to "&lt;"... etc See utils.hpp

        plain_char_action(std::ostream& phrase)
        : phrase(phrase) {}

        void operator()(char ch) const;
        void operator()(iterator const& first, iterator const& /*last*/) const;

        std::ostream& phrase;
    };

    struct image_action
    {
        // Handles inline images

        image_action(std::ostream& phrase)
        : phrase(phrase) {}

        void operator()(iterator first, iterator const& last) const;

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

    struct indentifier_action
    {
        // Handles macro identifiers

        indentifier_action(quickbook::actions& actions)
        : actions(actions) {}

        void operator()(iterator const& first, iterator const& last) const;

        quickbook::actions& actions;
    };

    struct macro_def_action
    {
        // Handles macro definitions

        macro_def_action(quickbook::actions& actions)
        : actions(actions) {}

        void operator()(iterator const& first, iterator const& last) const;

        quickbook::actions& actions;
    };

    struct link_action
    {
        // Handles links (URL, XML refentry, function, class, member)

        link_action(std::ostream& phrase, char const* tag)
        : phrase(phrase), tag(tag) {}

        void operator()(iterator first, iterator const& last) const;

        std::ostream& phrase;
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

        start_row_action(std::stringstream& phrase, unsigned& span, std::string& header)
            : phrase(phrase), span(span), header(header) {}

        void operator()(char) const;
        void operator()(iterator f, iterator) const;

        std::stringstream& phrase;
        unsigned& span;
        std::string& header;
    };

    struct start_col_action
    {
        // Handles table columns

        start_col_action(std::ostream& phrase, unsigned& span)
        : phrase(phrase), span(span) {}

        void operator()(char) const;

        std::ostream& phrase;
        unsigned& span;
    };

    struct begin_section_action
    {
        // Handles begin page

        begin_section_action(
            std::ostream& out
          , std::stringstream& phrase
          , std::string& library_id
          , std::string& section_id
          , int& level
          , std::string& qualified_section_id)
        : out(out)
        , phrase(phrase)
        , library_id(library_id)
        , section_id(section_id)
        , level(level)
        , qualified_section_id(qualified_section_id) {}

        void operator()(iterator first, iterator const& last) const;

        std::ostream& out;
        std::stringstream& phrase;
        std::string& library_id;
        std::string& section_id;
        int& level;
        std::string& qualified_section_id;
    };

    struct end_section_action
    {
        end_section_action(
            std::ostream& out
          , int& level
          , std::string& qualified_section_id)
        : out(out)
        , level(level)
        , qualified_section_id(qualified_section_id) {}

        void operator()(iterator const& first, iterator const& last) const;

        std::ostream& out;
        int& level;
        std::string& qualified_section_id;
   };

    struct xinclude_action
    {
        // Handles XML includes
        xinclude_action(std::ostream& out_, quickbook::actions& actions_)
            : out(out_), actions(actions_) {}

        void operator()(iterator const& first, iterator const& last) const;

        std::ostream& out;
        quickbook::actions& actions;
    };

    struct include_action
    {
        // Handles QBK includes

        include_action(quickbook::actions& actions_)
            : actions(actions_) {}

        void operator()(iterator const& first, iterator const& last) const;

        quickbook::actions& actions;
    };

    struct xml_author
    {
        // Handles xml author

        xml_author(std::ostream& out)
        : out(out) {}

        void operator()(std::pair<std::string, std::string> const& author) const;

        std::ostream& out;
    };

    struct xml_year
    {
        // Handles xml year

        xml_year(std::ostream& out)
            : out(out) {}

        void operator()(std::string const &year) const;

        std::ostream& out;
    };

    void pre(std::ostream& out, quickbook::actions& actions, bool ignore_docinfo = false);
    void post(std::ostream& out, quickbook::actions& actions, bool ignore_docinfo = false);

    struct phrase_to_string_action
    {
        phrase_to_string_action(std::string& out, std::stringstream& phrase)
            : out(out) , phrase(phrase) {}

        void operator()(iterator const& first, iterator const& last) const;

        std::string&        out;
        std::stringstream&  phrase;
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  Our actions
    //
    ///////////////////////////////////////////////////////////////////////////
    struct actions
    {
        actions(char const* filein_, fs::path const& outdir, std::ostream &out_);

        fs::path                filename;
        fs::path                outdir;
        std::string             macro_id;
        std::string             phrase_save;
        std::string             table_title;
        std::ostream&           out;
        error_action            error;

        typedef std::vector<std::string> copyright_list;
        typedef std::vector<std::pair<std::string, std::string> > author_list;

        std::string             doc_type;
        std::string             doc_title;
        std::string             doc_version;
        std::string             doc_id;
        std::string             doc_dirname;
        copyright_list          doc_copyright_years;
        std::string             doc_copyright_holder;
        std::string             doc_purpose;
        std::string             doc_category;
        author_list             doc_authors;
        std::string             doc_license;
        std::string             doc_last_revision;
        std::string             include_doc_id;
        phrase_to_string_action extract_doc_license;
        phrase_to_string_action extract_doc_purpose;
        std::string             doc_license_1_1;
        std::string             doc_purpose_1_1;

        std::string             page_title;
        std::string             section_id;
        std::string             previous;
        std::stringstream       phrase;
        std::stringstream       temp;
        unsigned                table_span;
        std::string             table_header;

        macros_type             macro;
        std::string             source_mode;
        code_action             code;
        code_action             code_block;
        inline_code_action      inline_code;
        phrase_action           paragraph;
        anchored_phrase_action  h1, h2, h3, h4, h5, h6;
        markup_action           hr;
        phrase_action           blurb, blockquote, preformatted;
        phrase_action           warning, caution, important, note, tip;
        plain_char_action       plain_char;
        raw_char_action         raw_char;
        image_action            image;

        typedef std::pair<char, int> mark_type;
        std::stringstream       list_buffer;
        std::stack<mark_type>   list_marks;
        int                     indent;
        list_action             list;
        list_format_action      list_format;
        phrase_action           list_item;

        link_action             funcref_pre;
        markup_action           funcref_post;
        link_action             classref_pre;
        markup_action           classref_post;
        link_action             memberref_pre;
        markup_action           memberref_post;
        link_action             enumref_pre;
        markup_action           enumref_post;
        link_action             headerref_pre;
        markup_action           headerref_post;

        markup_action           bold_pre;
        markup_action           bold_post;
        markup_action           italic_pre;
        markup_action           italic_post;
        markup_action           underline_pre;
        markup_action           underline_post;
        markup_action           teletype_pre;
        markup_action           teletype_post;
        markup_action           strikethrough_pre;
        markup_action           strikethrough_post;
        markup_action           quote_pre;
        markup_action           quote_post;
        markup_action           replaceable_pre;
        markup_action           replaceable_post;
        markup_action           footnote_pre;
        markup_action           footnote_post;

        simple_phrase_action    simple_bold;
        simple_phrase_action    simple_italic;
        simple_phrase_action    simple_underline;
        simple_phrase_action    simple_teletype;
        simple_phrase_action    simple_strikethrough;

        variablelist_action     variablelist;
        markup_action           start_varlistentry;
        markup_action           end_varlistentry;
        markup_action           start_varlistterm;
        markup_action           end_varlistterm;
        markup_action           start_varlistitem;
        markup_action           end_varlistitem;

        markup_action           break_;
        indentifier_action      identifier;
        macro_def_action        macro_def;
        do_macro_action         do_macro;
        link_action             url_pre;
        markup_action           url_post;
        link_action             link_pre;
        markup_action           link_post;
        table_action            table;
        start_row_action        start_row;
        markup_action           end_row;
        start_col_action        start_cell;
        markup_action           end_cell;
        anchor_action           anchor;

        begin_section_action    begin_section;
        end_section_action      end_section;
        xinclude_action         xinclude;
        include_action          include;

        markup_action           escape_pre;
        markup_action           escape_post;

        int                     level;
        std::string             qualified_section_id;
    };
}

#endif // BOOST_SPIRIT_QUICKBOOK_UTILS_HPP

