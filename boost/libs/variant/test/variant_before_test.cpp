//-----------------------------------------------------------------------------
// boost-libs variant/test/variant_before_test.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2003
// Eric Friedman, Itay Maman
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#include "boost/variant.hpp"
#include "boost/test/minimal.hpp"

#include <iostream>
#include <sstream>
#include <string>

#include <algorithm>
#include <vector>

template <typename T, typename Comp>
void assert_less_than_comparable(
      const T& x, const T& y, const T& z, Comp comp
    )
{
    // irreflexivity check
    BOOST_CHECK( !comp(x,x) );
    BOOST_CHECK( !comp(y,y) );
    BOOST_CHECK( !comp(z,z) );

    // transitivity check
    BOOST_CHECK( comp(x,y) );
    BOOST_CHECK( comp(y,z) );
    BOOST_CHECK( comp(x,z) );

    // antisymmetry check
    BOOST_CHECK( !comp(y,x) );
    BOOST_CHECK( !comp(z,y) );
    BOOST_CHECK( !comp(z,x) );
}

template <typename It>
std::string print_range(It first, It last)
{
    std::ostringstream result;

    while (first != last)
    {
        result << *first << ' ';
        ++first;
    }

    return result.str();
}

int test_main(int , char* [])
{
    typedef boost::variant<int, std::string> var_t;
    typedef boost::variant_before<var_t> comp_t;

    comp_t comp;
    var_t var1(3);
    var_t var2(5);
    var_t var3("goodbye");
    var_t var4("hello");

    assert_less_than_comparable(var1, var2, var3, comp);
    assert_less_than_comparable(var2, var3, var4, comp);

    std::vector<var_t> vec;
    vec.push_back( var3 );
    vec.push_back( var2 );
    vec.push_back( var4 );
    vec.push_back( var1 );
    std::sort(vec.begin(), vec.end(), comp);

    std::string sort_result( print_range(vec.begin(), vec.end()) );
    BOOST_CHECK( sort_result == "3 5 goodbye hello " );

    return boost::exit_success;
}
