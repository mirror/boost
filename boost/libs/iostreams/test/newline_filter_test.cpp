// (C) Copyright Jonathan Turkanis 2004
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#include <algorithm>  // count.
#include <string>
#include <string.h>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/filter/newline_filter.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test.hpp>
#include "detail/verification.hpp"

using namespace std;
using namespace boost;
using namespace boost::iostreams;
using namespace boost::iostreams::newline;
using namespace boost::iostreams::test;
using boost::unit_test_framework::test_suite; 

const char* text =
    "abcde\r" "abcde\n" "abcde\r\n"
    "abcd\r"  "abcd\n"  "abcd\r\n"
    "abc\r"   "abc\n"   "abc\r\n"
    "ab\r"    "ab\n"    "ab\r\n"
    "a\r"     "a\n"     "a\r\n"
    "\r"      "\n"      "\r\n"
    "a\r"     "a\n"     "a\r\n"
    "ab\r"    "ab\n"    "ab\r\n"
    "abc\r"   "abc\n"   "abc\r\n"
    "abcd\r"  "abcd\n"  "abcd\r\n"
    "abcde\r" "abcde\n" "abcde\r\n"
    "abcde\r" "abcde\n" "abcde";

bool verify_text(std::string text, int print)
{
    switch (print) {
    case print_LF:
        return text.find('\r') == string::npos;
    case print_CR:
        return text.find('\n') == string::npos;
    case print_CRLF:
        {
            text += (char) 0;
            char prev = 0;
            string::size_type n = text.size();
            for (string::size_type z = 0; z < n; ++z)
            {
                if ( (text[z] == '\n') != (prev == '\r') )
                    return false;
                prev = text[z];
            }
            return true;
        }
    default: return false;
    }
}

int count_lines(const std::string text, int print)
{
    return (int) std::count( text.begin(),
                             text.end(),
                             print == print_CR ? '\r' : '\n' );
}

bool test_input_options(int flags, int count)
{
    namespace io = boost::iostreams;
    string result;
    io::filtering_istreambuf in;
    in.push(io::newline_filter(flags));
    in.push(boost::make_iterator_range(text, text + strlen(text)));
    io::copy(in, boost::iostreams::back_inserter(result));
    return count_lines(result, flags & io::newline::print_mask) == count;
}

bool test_output_options(int flags, int count)
{
    namespace io = boost::iostreams;
    string result;
    io::filtering_ostreambuf out;
    out.push(io::newline_filter(flags));
    out.push(boost::iostreams::back_inserter(result));
    io::copy(boost::make_iterator_range(text, text + strlen(text)), out);
    out.reset();
    return count_lines(result, flags & io::newline::print_mask) == count;
}

bool test_options(int flags, int count)
{
    return test_input_options(flags, count) &&
           test_output_options(flags, count);
}

void newline_filter_test()
{
    {
        BOOST_CHECK(test_options(posix, 34));
        BOOST_CHECK(test_options(mac, 34));
        BOOST_CHECK(test_options(windows, 34));
        BOOST_CHECK(test_options(posix | final_newline, 35));
        BOOST_CHECK(test_options(mac | final_newline, 35));
        BOOST_CHECK(test_options(windows | final_newline, 35));
        BOOST_CHECK(test_options(posix, 34));
        BOOST_CHECK(test_options(mac, 34));
        BOOST_CHECK(test_options(windows, 34));
        BOOST_CHECK(test_options(print_CR | accept_CR, 23));
        BOOST_CHECK(test_options(print_LF | accept_LF, 23));
        BOOST_CHECK(test_options(print_CRLF | accept_LF | accept_CR, 46));
        BOOST_CHECK(test_options(print_CRLF | accept_LF | accept_CR | accept_CRLF, 46));
    }
}

test_suite* init_unit_test_suite(int, char* []) 
{
    test_suite* test = BOOST_TEST_SUITE("newline_filter test");
    test->add(BOOST_TEST_CASE(&newline_filter_test));
    return test;
}
