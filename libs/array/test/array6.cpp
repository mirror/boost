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

#include <boost/test/included/test_exec_monitor.hpp>


namespace {
    template< class T >
    void    RunTests()
    {
        typedef boost::array< T, 5 >    test_type;
        typedef T arr[5];
        test_type           test_case; //   =   { 1, 1, 2, 3, 5 };
    
        arr &aRef = get_c_array ( test_case );
        BOOST_CHECK ( &*test_case.begin () == &aRef[0] );
        
        const arr &caRef = get_c_array ( test_case );
        typename test_type::const_iterator iter = test_case.begin ();
        BOOST_CHECK ( &*iter == &caRef[0] );
    }
}

int test_main( int , char* [] )
{
    RunTests< bool >();
    RunTests< void * >();
    RunTests< long double >();
    RunTests< std::string >();
    return 0;
}

