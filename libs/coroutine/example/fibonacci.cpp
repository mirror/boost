
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <cstdlib>
#include <iostream>

#include <boost/range.hpp>
#include <boost/coroutine/all.hpp>

#ifdef BOOST_COROUTINES_UNIDIRECT
void fibonacci( boost::coroutines::push_coroutine< int > & c)
{
    int first = 1, second = 1;
    while ( true)
    {
        int third = first + second;
        first = second;
        second = third;
        c( third);     
    }
}

int main()
{
    boost::coroutines::pull_coroutine< int > c( fibonacci);
    boost::range_iterator<
       boost::coroutines::pull_coroutine< int >
    >::type   it( boost::begin( c) );
    for ( int i = 0; i < 10; ++i)
    {
        std::cout << * it <<  " ";
        ++it;
    }

    std::cout << "\nDone" << std::endl;

    return EXIT_SUCCESS;
}
#else
void fibonacci( boost::coroutines::coroutine< void( int) > & c)
{
    int first = 1, second = 1;
    while ( true)
    {
        int third = first + second;
        first = second;
        second = third;
        c( third);
    }
}

int main()
{
    boost::coroutines::coroutine< int() > c( fibonacci);
    boost::range_iterator<
       boost::coroutines::coroutine< int() >
    >::type   it( boost::begin( c) );
    for ( int i = 0; i < 10; ++i)
    {
        std::cout << * it <<  " ";
        ++it;
    }

    std::cout << "\nDone" << std::endl;

    return EXIT_SUCCESS;
}
#endif
