// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#include <iostream>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include "uncommenting_input_filter.hpp"

//
// Demonstrates the use of uncommenting_input_filter.
//
void test_uncommenting()
{
    using namespace std;
    using namespace boost::iostreams;
    using namespace boost::iostreams::example;

    std::string script = // from boost configure
        "# Be Bourne compatible\n"
        "if test -n \"${ZSH_VERSION+set}\" && (emulate sh) >/dev/null 2>&1; then\n"
        "emulate sh\n"
        "NULLCMD=:\n"
        "# Zsh 3.x and 4.x performs word splitting on ${1+\"$@\"}, which\n"
        "# is contrary to our usage.  Disable this feature.\n"
        "alias -g '${1+\"$@\"}'='\"$@\"'\n"
        "elif test -n \"${BASH_VERSION+set}\" && (set -o posix) >/dev/null 2>&1; then\n"
        "set -o posix\n"
        "fi\n"
        "\n"
        "# Support unset when possible.\n"
        "if (FOO=FOO; unset FOO) >/dev/null 2>&1; then\n"
        "as_unset=unset\n"
        "else\n"
        "as_unset=false\n"
        "fi";

    filtering_istream in;
    in.push(uncommenting_input_filter());
    in.push(script.begin(), script.end());

    // Print unfiltered script.
    cout << "**** Script with comments ****\n\n" << script << "\n\n";

    // Print filtered script:
    cout << "**** Script with comments removed ****\n\n";
    boost::iostreams::copy(in, cout);
    cout << "\n\n";
}

int main()
{
    test_uncommenting();
    return 0;
}
