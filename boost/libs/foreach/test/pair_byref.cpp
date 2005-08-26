//  (C) Copyright Eric Niebler 2004.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

/*
 Revision history:
   13 December 2004 : Initial version.
   25 August 2005 : Initial version.
*/

#include <list>
#include <vector>
#include <boost/test/minimal.hpp>
#include <boost/iterator/iterator_traits.hpp>
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
std::pair<int*,int*> my_pair(my_array,my_array+5);
std::pair<int const*,int const*> const my_const_pair(my_array,my_array+5);

///////////////////////////////////////////////////////////////////////////////
// test_main
//   
int test_main( int, char*[] )
{
    // non-const containers by reference
    BOOST_CHECK(to_vector_foreach_byref(my_pair)  == to_vector_for(my_pair));

    // const containers by reference
    BOOST_CHECK(to_vector_foreach_byref(my_const_pair)  == to_vector_for(my_const_pair));

    // mutate the mutable collections
    mutate_foreach_byref(my_pair);

    // compare the mutated collections to the actual results
    std::pair<int_iterator,int_iterator> results(int_iterator(2),int_iterator(7));
    BOOST_CHECK(to_vector_foreach_byval(my_pair) == to_vector_for(results));

    return 0;
}
