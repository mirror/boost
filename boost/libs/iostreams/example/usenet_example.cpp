// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#include <iostream>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include "usenet_input_filter.hpp"

//
// Demonstrates the use of usenet_input_filter.
//
void test_usenet_filter()
{
    using namespace std;
    using namespace boost::iostreams;
    using namespace boost::iostreams::example;

    string post =
        "> I don't understand the usenet example --\n"
        "> the comments don't make any sense.\n\n"
        "IMO you should RTFM or STFW. HTH. HAND.\n";

    filtering_istream in;
    in.push(usenet_input_filter());
    in.push(post.begin(), post.end());

    // Print unfiltered post.
    cout << "**** Post unfiltered ****\n\n" << post << "\n\n";

    // Print filtered post:
    cout << "**** Post with abbreviations expanded ****\n\n";
    boost::iostreams::copy(in, std::cout);
    cout << "\n\n";
}

int main()
{
    test_usenet_filter();
    return 0;
}
