// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

//
// Demonstrates the use of presidential_output_filter.
//

#include <iostream>
#include <boost/iostreams/filtering_stream.hpp>
#include "presidential_output_filter.hpp"

void test_presidential_filter()
{
    using namespace std;
    using namespace boost::iostreams;
    using namespace boost::iostreams::example;

    const char* speech =
        "They sorely misunderestimate the American people if they "
        "think we will let them obtain nucular weapons. This "
        "malfeance will not stand.";

    // std::ostream which writes to standard output, filtered by a
    // presidential_output_filter.
    filtering_ostream out;
    out.push(presidential_output_filter());
    out.push(cout);

    // Print unfiltered code.
    cout << "**** Speech unfiltered ****\n\n" << speech << "\n\n";

    // Print filtered code:
    out << "**** Speech with presidential filter ****\n\n" << speech << "\n\n";
}

int main()
{
    test_presidential_filter();
    return 0;
}
