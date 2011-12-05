/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#define BOOST_TEST_MODULE icl::casual unit test

#define BOOST_ICL_TEST_CHRONO

#include <libs/icl/test/disable_test_warnings.hpp>

#include <string>
#include <vector>
#include <boost/mpl/list.hpp>
#include "../unit_test_unwarned.hpp"


// interval instance types
#include "../test_type_lists.hpp"
#include "../test_value_maker.hpp"

#include <boost/rational.hpp>

#include <boost/type_traits/is_same.hpp>

#include <boost/icl/gregorian.hpp>
#include <boost/icl/ptime.hpp>

#include <boost/icl/interval_map.hpp>
#include <boost/icl/interval_set.hpp>
#include <boost/icl/interval.hpp>

#include <boost/scoped_ptr.hpp>

using namespace std;
using namespace boost;
using namespace unit_test;
using namespace boost::icl;

void pass_it(shared_ptr<int> pi)
{
    *pi = 41;
    cout << "uses: " << pi.use_count() << " cont: " << *pi << endl;
}

void pass_it_ref(shared_ptr<int>& pi)
{
    *pi = 43;
    cout << "uses: " << pi.use_count() << " cont: " << *pi << endl;
}

BOOST_AUTO_TEST_CASE(casual)
{
    typedef int T;
    typedef int U;
    typedef interval_map<T,U, partial_absorber> IntervalMapT;
    typedef interval_set<T>                     IntervalSetT;
    typedef IntervalMapT::interval_type         IntervalT;

    shared_ptr<int> pi(new int(42));
    cout << "uses: " << pi.use_count() << " cont: " << *pi << endl;
    pass_it(pi);
    pass_it_ref(pi);

    BOOST_CHECK_EQUAL(true, true);
}

/*
BOOST_AUTO_TEST_CASE(isEmptyTest)
{
    typedef int                         Value;
    typedef boost::icl::interval<Value> Interval;
    typedef std::numeric_limits<Value>  Limits;

    Value const max(Limits::max());

    Interval::interval_type piff = Interval::open(max,     max);

    BOOST_CHECK(!icl::is_empty(Interval::open(max - 2, max)));
    BOOST_CHECK( icl::is_empty(Interval::open(max - 1, max)));
    BOOST_CHECK( icl::is_empty(Interval::open(max,     max)));
}
*/

BOOST_AUTO_TEST_CASE(totalRangeTest)
{
    typedef int                                                              Value;
    typedef boost::icl::interval<Value>                                      Interval;
    typedef std::numeric_limits<Value>                                       Limits;
    typedef boost::icl::interval_map<Value, int, boost::icl::total_enricher> Container;

    Value const min(Limits::min());
    Value const max(Limits::max());

    boost::icl::interval_map<Value, int, boost::icl::total_enricher> intervals;

    intervals += std::make_pair(Interval::closed(min, max), 0);
    intervals += std::make_pair(Interval::right_open(0, 10),  3);

    BOOST_CHECK_EQUAL(intervals.iterative_size(), 3);
}
