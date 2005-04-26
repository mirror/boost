// Copyright 2005 Alexander Nasonov.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/any.hpp>
#include <boost/test/test_tools.hpp>

using namespace boost;

void test_cast_to_reference()
{
    int i = 7;
    any a(i), b(a);
    const any c(i);
    
    int&                ra1 = any_cast<int&               >(a);
    int const&          ra2 = any_cast<int const&         >(a);
    int const volatile& ra3 = any_cast<int const volatile&>(a);
    
    BOOST_CHECK(&ra1 == &ra2 && &ra2 == &ra3);

    int&                rb1 = any_cast<int&               >(b);
    int const&          rb2 = any_cast<int const&         >(b);
    int const volatile& rb3 = any_cast<int const volatile&>(b);
    
    BOOST_CHECK(&rb1 == &rb2 && &rb2 == &rb3);
    
    int const&          rc1 = any_cast<int const&         >(c);
    int const volatile& rc2 = any_cast<int const volatile&>(c);
    
    BOOST_CHECK(&rc1 == &rc2);
    
    BOOST_CHECK(&ra1 != &rb1 && &rb1 != &rc1 && &rc1 != &ra1);
    
    BOOST_CHECK(&ra1 != &i && &rb1 != &i && &rc1 != &i);
    
    ++ra1;
    int v = any_cast<int>(a);
    BOOST_CHECK(v == i + 1);
    
    --rb1;
    int v2 = any_cast<int>(b);
    BOOST_CHECK(v2 == i - 1);
    
    BOOST_CHECK_THROW(
        any_cast<char&>(a),
        bad_any_cast);
}

int test_main(int, char* av[])
{
    test_cast_to_reference();
    return 0;
}

