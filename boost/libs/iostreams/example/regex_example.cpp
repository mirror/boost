// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#include <iostream>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/regex_filter.hpp>

//
// Demonstrates the use of regex_output_filter to remove C- and C++-style
// comments (without regard to quotation marks or line continuations).
//

void test_regex()
{
    using namespace std;
    using namespace boost;
    using namespace boost::iostreams;

    string code = // From regex_format.hpp
        "/*\n"
        " *\n"
        " * Copyright (c) 1998-2002\n"
        " * Dr John Maddock\n"
        " *\n"
        " * Permission to use, copy, modify, distribute and sell this software\n"
        " * and its documentation for any purpose is hereby granted without fee,\n"
        " * provided that the above copyright notice appear in all copies and\n"
        " * that both that copyright notice and this permission notice appear\n"
        " * in supporting documentation.  Dr John Maddock makes no representations\n"
        " * about the suitability of this software for any purpose.\n"
        " * It is provided \"as is\" without express or implied warranty.\n"
        " *\n"
        " */\n"
        "\n"
        " /*\n"
        "  *   LOCATION:    see http://www.boost.org for most recent version.\n"
        "  *   FILE         regex_format.hpp\n"
        "  *   VERSION      see <boost/version.hpp>\n"
        "  *   DESCRIPTION: Provides formatting output routines for search and replace\n"
        "  *                operations.  Note this is an internal header file included\n"
        "  *                by regex.hpp, do not include on its own.\n"
        "  */\n"
        "\n"
        "#ifndef BOOST_REGEX_FORMAT_HPP\n"
        "#define BOOST_REGEX_FORMAT_HPP\n"
        "\n"
        "\n"
        "namespace boost{\n"
        "\n"
        "enum format_flags_t{\n"
        "   format_all = 0,                      // enable all extentions to sytax\n"
        "   format_sed = match_max << 1,         // sed style replacement.\n"
        "   format_perl = format_sed << 1,       // perl style replacement.\n"
        "   format_no_copy = format_perl << 1,   // don't copy non-matching segments.\n"
        "   format_first_only = format_no_copy << 1,   // Only replace first occurance.\n"
        "   format_is_if = format_first_only << 1   // internal use only.\n"
        "};\n";

    filtering_ostream out;
    regex pattern("(/\\*.*?\\*/)|(//[^\n]*)"); // Matches C and C++ comments.
    out.push(regex_filter(pattern, ""));       // Replaces comments with "".
    out.push(cout);

    // Print unfiltered code.
    cout << "**** Code unfiltered ****\n\n" << code << "\n\n";

    // Print filtered code:
    cout << "**** Code with comments removed ****\n\n";
    out << code << "\n\n";
}

int main()
{
    test_regex();
    return 0;
}
