/*=============================================================================
    Copyright (c) 2002 2004 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#include "../block.hpp"
#include "../doc_info.hpp"
#include "./post_process.hpp"
#include "utils.hpp"
#include "actions.hpp"
#include <boost/spirit/iterator/position_iterator.hpp>
#include <boost/program_options.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/ref.hpp>

#include <stdexcept>
#include <fstream>
#include <iostream>
#include <sstream>

#if (defined(BOOST_MSVC) && (BOOST_MSVC <= 1310))
#pragma warning(disable:4355)
#endif

#define QUICKBOOK_VERSION "Quickbook Version 1.3"

namespace quickbook
{
    using namespace boost::spirit;
    namespace fs = boost::filesystem;
    tm* current_time; // the current time
    tm* current_gm_time; // the current UTC time
    bool debug_mode; // for quickbook developers only
    unsigned qbk_major_version = 0;
    unsigned qbk_minor_version = 0;
    unsigned qbk_version_n = 0; // qbk_major_version * 100 + qbk_minor_version
    bool ms_errors = false; // output errors/warnings as if for VS

    ///////////////////////////////////////////////////////////////////////////
    //
    //  Load a file
    //
    ///////////////////////////////////////////////////////////////////////////
    static int
    load(char const* filename, file_storage& storage)
    {
        using std::cerr;
        using std::endl;
        using std::ios;
        using std::ifstream;
        using std::istream_iterator;

        ifstream in(filename, std::ios_base::in);

        if (!in)
        {
            detail::outerr(filename,1)
                << "Could not open input file." << endl;
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
    int
    parse(char const* filein_, actions& actor, bool ignore_docinfo)
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

        doc_info_grammar<actions> l(actor);
        parse_info<iterator_type> info = parse(first, last, l);

        if (info.hit || ignore_docinfo)
        {
            pre(actor.out, actor, ignore_docinfo);

            block_grammar<actions> g(actor);
            info = parse(info.hit ? info.stop : first, last, g);
            if (info.full)
            {
                post(actor.out, actor, ignore_docinfo);
            }
        }

        if (!info.full)
        {
            file_position const pos = info.stop.get_position();
            detail::outerr(pos.file,pos.line)
                << "Syntax Error near column " << pos.column << ".\n";
            return 1;
        }

        return 0;
    }

    static int
        parse(char const* filein_, fs::path const& outdir, std::ostream& out, bool ignore_docinfo = false)
    {
        actions actor(filein_, outdir, out);
        bool r = parse(filein_, actor);
        if (actor.level != 0)
            detail::outwarn(filein_,1)
                << "Warning missing [endsect] detected at end of file."
                << std::endl;
        return r;
    }

    static int
    parse(
        char const* filein_
      , char const* fileout_
      , int indent
      , int linewidth
      , bool pretty_print)
    {
        int result = 0;
        std::ofstream fileout(fileout_);
        fs::path outdir = fs::path(fileout_, fs::native).branch_path();
        if (outdir.empty())
            outdir = ".";
        if (pretty_print)
        {
            std::stringstream buffer;
            result = parse(filein_, outdir, buffer);
            if (result == 0)
            {
                post_process(buffer.str(), fileout, indent, linewidth);
            }
        }
        else
        {
            result = parse(filein_, outdir, fileout);
        }
        return result;
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
        using boost::program_options::command_line_parser;
        using boost::program_options::notify;
        using boost::program_options::value;
        using boost::program_options::positional_options_description;

        // First thing, the filesystem should record the current working directory.
        boost::filesystem::initial_path();

        options_description desc("Allowed options");
        desc.add_options()
            ("help", "produce help message")
            ("version", "print version string")
            ("no-pretty-print", "disable XML pretty printing")
            ("indent", value<int>(), "indent spaces")
            ("linewidth", value<int>(), "line width")
            ("input-file", value<std::string>(), "input file")
            ("output-file", value<std::string>(), "output file")
            ("debug", "debug mode (for developers)")
            ("ms-errors", "use Microsoft Visual Studio style error & warn message format")
        ;
        
        positional_options_description p;
        p.add("input-file", -1);
    
        variables_map vm;
        int indent = -1;
        int linewidth = -1;
        bool pretty_print = true;
        store(command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
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
    
        if (vm.count("ms-errors"))
            quickbook::ms_errors = true;

        if (vm.count("no-pretty-print"))
            pretty_print = false;

        if (vm.count("indent"))
            indent = vm["indent"].as<int>();

        if (vm.count("linewidth"))
            linewidth = vm["linewidth"].as<int>();
        
        if (vm.count("debug"))
        {
            static tm timeinfo;
            timeinfo.tm_year = 2000 - 1900;
            timeinfo.tm_mon = 12 - 1;
            timeinfo.tm_mday = 20;
            timeinfo.tm_hour = 12;
            timeinfo.tm_min = 0;
            timeinfo.tm_sec = 0;
            timeinfo.tm_isdst = -1;
            mktime(&timeinfo);
            quickbook::current_time = &timeinfo;
            quickbook::current_gm_time = &timeinfo;
            quickbook::debug_mode = true;
        }
        else
        {
            time_t t = std::time(0);
            static tm lt = *localtime(&t);
            static tm gmt = *gmtime(&t);
            quickbook::current_time = &lt;
            quickbook::current_gm_time = &gmt;
            quickbook::debug_mode = false;
        }

        if (vm.count("input-file"))
        {
            std::string filein = vm["input-file"].as<std::string>();
            std::string fileout;

            if (vm.count("output-file"))
            {
                fileout = vm["output-file"].as<std::string>();
            }
            else
            {
                fileout = quickbook::detail::remove_extension(filein.c_str());
                fileout += ".xml";
            }

            std::cout << "Generating Output File: "
                << fileout
                << std::endl;
    
            return quickbook::parse(filein.c_str(), fileout.c_str(), indent, linewidth, pretty_print);
        }
        else
        {
            quickbook::detail::outerr("",0) << "Error: No filename given" << std::endl;
        }
    }
    
    catch(std::exception& e) 
    {
        quickbook::detail::outerr("",0) << "Error: " << e.what() << "\n";
        return 1;
    }

    catch(...) 
    {
        quickbook::detail::outerr("",0) << "Error: Exception of unknown type caught\n";
    }

    return 0;
}
