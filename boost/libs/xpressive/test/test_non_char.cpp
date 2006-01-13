///////////////////////////////////////////////////////////////////////////////
// test_non_char.cpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <algorithm>
#include <boost/xpressive/traits/null_regex_traits.hpp>
#include "./test.hpp"

///////////////////////////////////////////////////////////////////////////////
// test_main
//   read the tests from the input file and execute them
int test_main( int, char*[] )
{
    static int const data[] = {0, 1, 2, 3, 4, 5, 6};
    null_regex_traits<int> nul;
    basic_regex<int const *> rex = imbue(nul)(1 >> +((set= 2,3) | 4) >> 5);
    match_results<int const *> what;

    if(!regex_search(data, data + (sizeof(data)/sizeof(*data)), what, rex))
    {
        BOOST_ERROR("regex_search on integral data failed");
    }
    else
    {
        BOOST_CHECK(*what[0].first == 1);
        BOOST_CHECK(*what[0].second == 6);
    }

    return 0;
}
