/* tests for using class array<> specialization for size 0
 * (C) Copyright Alisdair Meredith 2006.
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include <string>
#include <iostream>
#include <boost/array.hpp>
#include <algorithm>
#ifndef BOOST_NO_CXX11_HDR_ARRAY
#include <array>
#endif

namespace {
unsigned int failed_tests = 0;

#ifndef BOOST_NO_CXX11_HDR_ARRAY
void    fail_test( const char * reason ) {
    ++failed_tests;
    std::cerr << "Test failure " << failed_tests << ": " << reason << std::endl;
}

template< class T >
void    RunTests()
{
    typedef boost::array< T, 5 >    test_type;
    typedef T arr[5];
    test_type           test_case; //   =   { 1, 1, 2, 3, 5 };
    
    T &aRef = std::get<0> ( test_case );
    if ( &*test_case.begin () != &aRef )
        fail_test ( "Array7: Same thing not equal?(1)" );
        
    const T &caRef = std::get<0> ( test_case );
    if ( &*test_case.cbegin () != &caRef )
        fail_test ( "Array7: Same thing not equal?(2)" );
}
#endif

}

int main()
{
#ifndef BOOST_NO_CXX11_HDR_ARRAY
    RunTests< bool >();
    RunTests< void * >();
    RunTests< long double >();
    RunTests< std::string >();
#endif
    return failed_tests;
}

