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

#define BOOST_ICL_USE_STATIC_BOUNDED_INTERVALS
#include <boost/icl/interval_map.hpp>
#include <boost/icl/interval_set.hpp>
#include <boost/icl/interval.hpp>

using namespace std;
using namespace boost;
using namespace unit_test;
using namespace boost::icl;



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

BOOST_AUTO_TEST_CASE(generalized_find)
{
  typedef icl::interval_set<int>::const_iterator int_set_iterator;
  icl::interval_set<int> int_set;

  icl::interval<int>::type to_be_found(1,5);
  int_set += icl::interval<int>::type(0,2);
  int_set += icl::interval<int>::type(4,7);
  int_set += icl::interval<int>::type(8,9);

  int_set_iterator found;
  found = int_set.lower_bound(to_be_found); 
  cout << *found << endl; // [0,2)
  found = int_set.find(to_be_found); 
  cout << *found << endl; // [0,2)
  found = int_set.upper_bound(to_be_found); 
  cout << *found << endl; // [8,9)
  std::pair<int_set_iterator,int_set_iterator> exterior;
  exterior = int_set.equal_range(to_be_found); 
  cout << "[" << *exterior.first 
    << "," << *exterior.second << ")" << endl;
  // [[0,2),[8,9))
}

BOOST_AUTO_TEST_CASE(using_vaious_interval_types)
{
  interval_set<int, std::less, discrete_interval<int,std::less> > dyn_int_set;
  interval_set<int, std::less, right_open_interval<int,std::less> > stat_int_set;
  interval_set<float, std::less, continuous_interval<float,std::less> > dyn_float_set;

  dyn_int_set += discrete_interval<int>(1);
  BOOST_CHECK(( contains(dyn_int_set,1) ));

  stat_int_set += right_open_interval<int>(1);
  BOOST_CHECK(( contains(stat_int_set,1) ));

  dyn_float_set += continuous_interval<float>(1.0);
  BOOST_CHECK(( contains(dyn_float_set, 1.0) ));
}

    template <class IncrementableT>
    inline static IncrementableT succ_(IncrementableT x) { return ++x; }

    template <class DecrementableT>
    inline static DecrementableT pred_(DecrementableT x) { return --x; }


BOOST_AUTO_TEST_CASE(casual)
{
    //typedef int T;
    //typedef int U;
    //typedef interval_map<T,U, total_absorber> IntervalMapT;
    //typedef interval_set<T>                   IntervalSetT;
    //typedef IntervalMapT::interval_type       IntervalT;

	int i;
	int j = int();
	chrono::duration<int> cd1 = chrono::duration<int>();
	chrono::duration<int> cd2(0);
	chrono::duration<int> dur1(0);
	chrono::duration<int> dur2, dur3, dur4;
	dur2 = dur3 = dur4 = dur1;
	int itg1(0);
	int itg2, itg3, itg4;
	itg2 = itg3 = itg4 = itg1;

	cout << "uninitialized       i = " << i << endl;
	cout << "default constructed j = " << j << endl;
	cout << (cd1==cd2 ? "eq" : "!eq") << endl;
	cout << "chrono::duration cd1()  = " << cd1 << endl;
	cout << "chrono::duration cd2(0) = " << cd2 << endl;

	(dur2++)--;
	(dur3--)++;
	dur4++;
	dur4--;
	cout << dur1 << ", " << dur2 << ", " << dur3 << ", " << dur4 << endl;
	//---------
	dur2 = dur3 = dur4 = dur1;
	cout << icl::pred(icl::succ(dur2)) << endl;
	//---------
	//(itg2++)--;
	//(itg3--)++;
	//itg4++;
	//itg4--;
	//cout << itg1 << ", " << itg2 << ", " << itg3 << ", " << itg4 << endl;


	dur2 = dur3 = dur4 = dur1;
	--(++dur2);
	++(--dur3);
	--dur4;
	++dur4;
	cout << dur1 << ", " << dur2 << ", " << dur3 << ", " << dur4 << endl;


    BOOST_CHECK_EQUAL(true, true);
}

