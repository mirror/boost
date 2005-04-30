/*=============================================================================
    Copyright (c) 2002 2004 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#include "../quickbook.hpp"
#include "../doc_info.hpp"
#include "utils.hpp"
#include "actions.hpp"
#include <boost/spirit/iterator/position_iterator.hpp>
#include <boost/program_options.hpp>

#include <fstream>
#include <iostream>
#include <sstream>

#if (defined(BOOST_MSVC) && (BOOST_MSVC <= 1310))
#pragma warning(disable:4355)
#endif

#define QUICKBOOK_VERSION "Quickbook Version 1.1"

namespace quickbook
{
    using namespace boost::spirit;

    ///////////////////////////////////////////////////////////////////////////
    //
    //  Our actions
    //
    ///////////////////////////////////////////////////////////////////////////
    struct actions
    {
        actions(char const* filein_, char const* fileout_)
            : filename(filein_)
            , out(fileout_)
            , table_span(0)
            , table_header()
            , source_mode("c++")
            , code(out, source_mode, macro)
            , inline_code(phrase, source_mode, macro)
            , paragraph(out, phrase, section_id, paragraph_pre, paragraph_post)
            , h1(out, phrase, section_id, h1_pre, h1_post, true)
            , h2(out, phrase, section_id, h2_pre, h2_post, true)
            , h3(out, phrase, section_id, h3_pre, h3_post, true)
            , h4(out, phrase, section_id, h4_pre, h4_post, true)
            , h5(out, phrase, section_id, h5_pre, h5_post, true)
            , h6(out, phrase, section_id, h6_pre, h6_post, true)
            , hr(out, hr_)
            , blurb(out, phrase, section_id, blurb_pre, blurb_post)
            , blockquote(out, phrase, section_id, blockquote_pre, blockquote_post)
            , preformatted(out, phrase, section_id, preformatted_pre, preformatted_post)
            , plain_char(phrase)
            , raw_char(phrase)
            , image(phrase)
            , list_buffer()
            , list_marks()
            , indent(-1)
            , list(out, list_buffer, indent, list_marks)
            , list_format(list_buffer, indent, list_marks)
            , list_item(list_buffer, phrase, section_id, list_item_pre, list_item_post)
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
            , simple_bold(phrase, bold_pre_, bold_post_)
            , simple_italic(phrase, italic_pre_, italic_post_)
            , simple_underline(phrase, underline_pre_, underline_post_)
            , simple_teletype(phrase, teletype_pre_, teletype_post_)
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
            , begin_section(out, doc_id, section_id)
            , end_section(out, "</section>")
            , xinclude(out)
        {
            std::cout << "Generating Output File: "
                << fileout_
                << std::endl;

            // add the predefined macros
            macro.add
                ("__DATE__", std::string(quickbook_get_date))
                ("__TIME__", std::string(quickbook_get_time))
                ("__FILENAME__", std::string(filein_))
            ;
        }

        typedef indentifier_action<actions> indentifier_action;
        typedef macro_def_action<actions> macro_def_action;
        typedef table_action<actions> table_action;
        typedef variablelist_action<actions> variablelist_action;

        char const*             filename;
        std::string             directory;
        std::string             macro_id;
        std::string             phrase_save;
        std::string             table_title;
        std::ofstream           out;
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

        std::string             page_title;
        std::string             section_id;
        std::string             previous;
        std::stringstream       phrase;
        unsigned                table_span;
        std::string             table_header;

        symbols<std::string>    macro;
        std::string             source_mode;
        code_action             code;
        inline_code_action      inline_code;
        phrase_action           paragraph, h1, h2, h3, h4, h5, h6;
        markup_action           hr;
        phrase_action           blurb, blockquote, preformatted;
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

        simple_phrase_action    simple_bold;
        simple_phrase_action    simple_italic;
        simple_phrase_action    simple_underline;
        simple_phrase_action    simple_teletype;

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
        markup_action           end_section;
        xinclude_action         xinclude;
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  Load a file
    //
    ///////////////////////////////////////////////////////////////////////////
    typedef std::vector<char> file_storage;

    static int
    load(char const* filename, file_storage& storage)
    {
        using std::cerr;
        using std::endl;
        using std::ios;
        using std::ifstream;
        using std::istream_iterator;

        ifstream in(filename);

        if (!in)
        {
            cerr << "Could not open input file: " << filename << endl;
            return 1;
        }

        // Turn off white space skipping on the stream
        in.unsetf(ios::skipws);

        std::copy(
            istream_iterator<char>(in),
            istream_iterator<char>(),
            std::back_inserter(storage));

        //  ensure that we have enough trailing newlines to eliminate
        //  the need to check for end of file in the grammar.
        storage.push_back('\n');
        storage.push_back('\n');
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////////
    //
    //  Parse a file
    //
    ///////////////////////////////////////////////////////////////////////////
    static int
    parse(char const* filein_, char const* fileout_)
    {
        using std::cerr;
        using std::vector;
        using std::string;

        file_storage storage;
        int err = quickbook::load(filein_, storage);
        if (err != 0)
            return err;

        typedef position_iterator<file_storage::const_iterator> iterator_type;
        iterator_type first(storage.begin(), storage.end(), filein_);
        iterator_type last(storage.end(), storage.end());

        actions actor(filein_, fileout_);

        doc_info_grammar<actions> l(actor);
        parse_info<iterator_type> info = parse(first, last, l);

        if (info.hit)
        {
            pre(actor.out, actor);

            first = info.stop;
            quickbook_grammar<actions> g(actor);
            info = parse(first, last, g);
            if (info.full)
            {
                post(actor.out, actor);
            }
        }

        if (!info.full)
        {
    	    file_position const pos = info.stop.get_position();
    	    cerr
    		    << "Syntax error at \"" << pos.file
    		    << "\" line " << pos.line
    		    << ", column " << pos.column << ".\n";
            return 1;
        }

        return 0;
    }
}

///////////////////////////////////////////////////////////////////////////
//
//  Main program
//
///////////////////////////////////////////////////////////////////////////
int
main(int argc, char* argv[])
{
    try 
    {
        using boost::program_options::options_description;
        using boost::program_options::variables_map;
        using boost::program_options::store;
        using boost::program_options::parse_command_line;
        using boost::program_options::notify;

        options_description desc("Allowed options");
        desc.add_options()
            ("help", "produce help message")
            ("version,v", "print version string")
        ;
    
        variables_map vm;
        store(parse_command_line(argc, argv, desc), vm);
        notify(vm);    
    
        if (vm.count("help")) 
        {
            std::cout << desc << "\n";
            return 0;
        }

        if (vm.count("version"))
        {
            std::cout << QUICKBOOK_VERSION << std::endl;
            return 0;
        }

        if (argc > 1)
        {
            std::string fileout;
            if (argc == 2)
            {
                fileout = quickbook::detail::remove_extension(argv[1]);
                fileout += ".xml";
            }
            else
            {
                fileout = argv[2];
            }
    
            return quickbook::parse(argv[1], fileout.c_str());
        }
        else
        {
            std::cerr << "Error: No filename given" << std::endl;
        }
    }
    
    catch(std::exception& e) 
    {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    catch(...) 
    {
        std::cerr << "Error: Exception of unknown type caught\n";
    }

    return 0;
}
