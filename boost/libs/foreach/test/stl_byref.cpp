//  (C) Copyright Eric Niebler 2004.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

/*
 Revision history:
   25 August 2005: Initial version.
*/

#include <list>
#include <boost/iterator/counting_iterator.hpp>
#include <boost/test/minimal.hpp>
#include "../../../boost/foreach.hpp"
#include "./utility.hpp"

///////////////////////////////////////////////////////////////////////////////
// int_iterator
//
typedef boost::counting_iterator<int> int_iterator;

///////////////////////////////////////////////////////////////////////////////
// initialize a std::list<int>
std::list<int> get_list()
{
    std::list<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.push_back(5);
    return l;
}

///////////////////////////////////////////////////////////////////////////////
// define come containers
//
std::list<int> my_list(get_list());
std::list<int> const &my_const_list = my_list;

///////////////////////////////////////////////////////////////////////////////
// test_main
//   
int test_main( int, char*[] )
{
    // non-const containers by reference
    BOOST_CHECK(to_vector_foreach_byref(my_list)  == to_vector_for(my_list));

    // const containers by reference
    BOOST_CHECK(to_vector_foreach_byref(my_const_list)  == to_vector_for(my_const_list));

    // mutate the mutable collections
    mutate_foreach_byref(my_list);

    // compare the mutated collections to the actual results
    std::pair<int_iterator,int_iterator> results(int_iterator(2),int_iterator(7));
    BOOST_CHECK(to_vector_foreach_byval(my_list)  == to_vector_for(results));

    return 0;
}
