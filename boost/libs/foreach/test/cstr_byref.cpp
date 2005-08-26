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
char my_ntcs_buffer[] = "\1\2\3\4\5";
char *my_ntcs  = my_ntcs_buffer;
char const *my_const_ntcs  = my_ntcs;

///////////////////////////////////////////////////////////////////////////////
// test_main
//   
int test_main( int, char*[] )
{
    // non-const containers by reference
    BOOST_CHECK(to_vector_foreach_byref(my_ntcs)  == to_vector_for(my_ntcs));

    // const containers by reference
    BOOST_CHECK(to_vector_foreach_byref(my_const_ntcs)  == to_vector_for(my_const_ntcs));

    // mutate the mutable collections
    mutate_foreach_byref(my_ntcs);

    // compare the mutated collections to the actual results
    std::pair<int_iterator,int_iterator> results(int_iterator(2),int_iterator(7));
    BOOST_CHECK(to_vector_foreach_byval(my_ntcs)  == to_vector_for(results));

    return 0;
}
