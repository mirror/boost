//-----------------------------------------------------------------------------
// boost-libs variant/test/variant_reference_test.cpp source file
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

template <typename T>
void test_reference_content(T& t, const T& value1, const T& value2)
{
    BOOST_CHECK( !(value1 == value2) );

    /////

    boost::variant< T& > var(t);
    BOOST_CHECK(( boost::get<T>(&var) == &t ));

    t = value1;
    BOOST_CHECK(( boost::get<T>(var) == value1 ));

    /////

    boost::variant< T > var2(var);
    BOOST_CHECK(( boost::get<T>(var2) == value1 ));

    t = value2;
    BOOST_CHECK(( boost::get<T>(var2) == value1 ));
}

int test_main(int , char* [])
{
    int i = 0;
    test_reference_content(i, 1, 2);

    return boost::exit_success;
}
