/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#define BOOST_TEST_MODULE icl::casual unit test
#include <libs/icl/test/disable_test_warnings.hpp>
#include <string>
#include <vector>
#include <boost/mpl/list.hpp>
#include "../unit_test_unwarned.hpp"
#include <boost/test/test_case_template.hpp>

// interval instance types
#include "../test_type_lists.hpp"
#include "../test_value_maker.hpp"

#include <boost/type_traits/is_same.hpp>

#include <boost/icl/gregorian.hpp>
#include <boost/icl/ptime.hpp>

#include <boost/icl/interval_map.hpp>
#include <boost/icl/interval_set.hpp>
#include <boost/icl/interval.hpp>

using namespace std;
using namespace boost;
using namespace unit_test;
using namespace boost::icl;


BOOST_AUTO_TEST_CASE(float_infinity)
{

    typedef size_type_of<interval<float>::type>::type itv_float_size_type;

    BOOST_CHECK( (boost::is_same<size_type_of<interval<float>::type>::type, std::size_t>::value) );
    BOOST_CHECK( (boost::is_same<itv_float_size_type, std::size_t>::value) );
    BOOST_CHECK( (boost::is_same<itv_float_size_type, unsigned int>::value) );

    cout << cardinality(interval<float>::closed(1,5))  << endl;
    cout << icl::infinity<size_type_of<interval<float>::type>::type>::value() << endl;
    //cout << (std::size_t)(icl::infinity<itv_float_size_type>::value) << endl;
    cout << (std::numeric_limits<unsigned int>::max)() << endl;

    BOOST_CHECK_EQUAL(
      cardinality(interval<float>::closed(1,5))
    , icl::infinity<itv_float_size_type>::value()
    );

    BOOST_CHECK_EQUAL(true, true);
}

BOOST_AUTO_TEST_CASE(ticket_5207)
{
    icl::interval< int >::type int_interval;
    icl::interval_set< int > int_set;
    icl::interval_map< int, int > int_map;
    icl::interval_map< int, int >::element_type int_element;
    icl::interval_map< int, int >::segment_type int_segment;

    /// AFAICT none of the following lines compiles and they all should:
    icl::lower( int_interval );
    icl::upper( int_interval );
    icl::first( int_interval );
    icl::last( int_interval );
    //icl::add( int_set, int_set );
    //icl::add( int_map, int_map );
    //icl::subtract( int_set, int_set );
    //icl::subtract( int_map, int_map );
    int_set += int_interval;
    icl::disjoint( int_map, int_element );
    icl::disjoint( int_map, int_segment );
    icl::intersects( int_map, int_segment );
    icl::intersects( int_map, int_element );
}

BOOST_AUTO_TEST_CASE(casual)
{
    //typedef int T;
    //typedef int U;
    //typedef interval_map<T,U, total_absorber> IntervalMapT;
    //typedef interval_set<T>                   IntervalSetT;
    //typedef IntervalMapT::interval_type       IntervalT;

    BOOST_CHECK_EQUAL(true, true);
}

