
// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

//
// Demonstrates the use of line_wrapping_output_filter.
//

#include <iostream>
#include <boost/iostreams/filtering_stream.hpp>
#include "line_wrapping_output_filter.hpp"

//
// Demonstrates the use of line_wrapping_output_filter.
//
void test_line_wrapping()
{
    using namespace std;
    using namespace boost::iostreams;
    using namespace boost::iostreams::example;

    const char* text =
        "In the country of Westphalia, in the castle of the most noble Baron "
        "of Thunder-ten-tronckh, lived a youth whom Nature had endowed with a "
        "most sweet disposition. His face was the true index of his mind. He "
        "had a solid judgment joined to the most unaffected simplicity; and "
        "hence, I presume, he had his name of Candide. The old servants of the "
        "house suspected him to have been the son of the Baron's sister, by a "
        "very good sort of a gentleman of the neighborhood, whom that young "
        "lady refused to marry, because he could produce no more than "
        "threescore and eleven quarterings in his arms; the rest of the "
        "genealogical tree belonging to the family having been lost through "
        "the injuries of time....\n";

    filtering_ostream out;
    out.push(line_wrapping_output_filter(50));
    out.push(cout);

    // Print unfiltered text.
    cout << "**** Candide ****\n\n" << text << "\n\n";

    // Print filtered text:
    out << "**** Candide with line wrapping ****\n\n" << text << "\n\n";
}

int main()
{
    test_line_wrapping();
    return 0;
}
