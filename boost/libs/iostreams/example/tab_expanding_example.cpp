// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

//
// Demonstrates the use of tab_expanding_output_filter.
//

#include <iostream>
#include <boost/iostreams/filtering_stream.hpp>
#include "tab_expanding_output_filter.hpp"

void test_tab_expanding()
{
    using namespace std;
    using namespace boost::iostreams;
    using namespace boost::iostreams::example;

    const char* code =
        "class tab_expanding_output_filter : public output_filter {\n"
        "public:\n"
        "\texplicit tab_expanding_output_filter(int tab_size = 8)\n"
        "\t\t: tab_size_(tab_size), col_no_(0)\n"
        "\t\t{ assert(tab_size > 0); }\n\n"
        "\ttemplate<typename Sink>\n"
        "\tvoid put(Sink& dest, int c)\n"
        "\t\t{\n"
        "\t\t\tif (c == '\\t') {\n"
        "\t\t\t\tdo {\n"
        "\t\t\t\t\tthis->put(dest, ' ');\n"
        "\t\t\t\t} while(col_no_ % tab_size_ != 0);\n"
        "\t\t\t} else {\n"
        "\t\t\t\tboost::iostreams::put(dest, c);\n"
        "\t\t\t\tif (c == '\\n')\n"
        "\t\t\t\t\tcol_no_ = 0;\n"
        "\t\t\t\telse\n"
        "\t\t\t\t\t++col_no_;\n"
        "\t\t\t}\n"
        "\t\t}\n"
        "\ttemplate<typename Sink>\n"
        "\tvoid close(Sink&) { col_no_ = 0; }\n"
        "private:\n"
        "\tint\ttab_size_;\n"
        "\tint\tcol_no_;\n"
        "};\n";

    filtering_ostream out;
    out.push(tab_expanding_output_filter(4));
    out.push(cout);

    // Print unfiltered code.
    cout << "**** Code with tabs ****\n\n" << code << "\n\n";

    // Print filtered code:
    out << "**** Code with tabs replaced ****\n\n" << code << "\n\n";
}

int main()
{
    test_tab_expanding();
    return 0;
}
