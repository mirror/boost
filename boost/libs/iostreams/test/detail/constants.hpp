// (C) Copyright Jonathan Turkanis 2004
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Contains the definitions of several constants used by the test program.

#ifndef BOOST_IOSTREAMS_TEST_CONSTANTS_HPP_INCLUDED
#define BOOST_IOSTREAMS_TEST_CONSTANTS_HPP_INCLUDED

#include <string.h>
#include <boost/config.hpp>

namespace boost { namespace iostreams { namespace test {

// Chunk size for reading or writing in chunks.
const int chunk_size = 59;       

// Chunk size for reading or writing in chunks.
const int small_buffer_size = 23;       

// Number of times data is repeated in test files.
const int data_reps = 300;

namespace detail {

// Returns string which is used to generate test files.
inline const char* data(char*) 
{
    static const char* c =
        "!\"#$%&'()*+,-./0123456879:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    return c;
}

// Returns string which is used to generate test files.
inline const wchar_t* data(wchar_t*) 
{
    static const wchar_t* c =
        L"!\"#$%&'()*+,-./0123456879:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        L"[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    return c;
}

} // End namespace detail.

inline const char* narrow_data() { return detail::data((char*)0); }

inline const wchar_t* wide_data() { return detail::data((wchar_t*)0); }

// Length of string returned by data().
inline int data_length() 
{ 
    static int len = (int) strlen(narrow_data());
    return len;
}

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_TEST_CONSTANTS_HPP_INCLUDED
