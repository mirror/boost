//  (C) Copyright Eric Niebler 2004.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

/*
 Revision history:
   25 August 2005 : Initial version.
*/

#include <boost/test/minimal.hpp>
#include <boost/iterator/counting_iterator.hpp>
#include "../../../boost/foreach.hpp"
#include "./utility.hpp"

///////////////////////////////////////////////////////////////////////////////
// int_iterator
//
typedef boost::counting_iterator<int> int_iterator;

///////////////////////////////////////////////////////////////////////////////
// define come containers
//
int my_array[] = { 1,2,3,4,5 };
int const (&my_const_array)[5] = my_array;

///////////////////////////////////////////////////////////////////////////////
// test_main
//   
int test_main( int, char*[] )
{
    // non-const containers by reference
    BOOST_CHECK(to_vector_foreach_byref(my_array) == to_vector_for(my_array));

    // const containers by reference
    BOOST_CHECK(to_vector_foreach_byref(my_const_array) == to_vector_for(my_const_array));

    // mutate the mutable collections
    mutate_foreach_byref(my_array);

    // compare the mutated collections to the actual results
    std::pair<int_iterator,int_iterator> results(int_iterator(2),int_iterator(7));
    BOOST_CHECK(to_vector_foreach_byval(my_array) == to_vector_for(results));

    return 0;
}
