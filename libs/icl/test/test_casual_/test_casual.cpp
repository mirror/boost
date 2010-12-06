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

#include <boost/icl/interval_map.hpp>

using namespace std;
using namespace boost;
using namespace unit_test;
using namespace boost::icl;


BOOST_AUTO_TEST_CASE(casual)
{
    typedef int* T;
    typedef int U;
    typedef interval_map<T,U, total_absorber> IntervalMapT;
    typedef interval_set<T>                   IntervalSetT;
    typedef IntervalMapT::interval_type       IntervalT;

    int values[100];
    for(int idx=0; idx < 100; idx++)
        values[idx] = idx;
    
    IntervalSetT ptr_set;

    cout << IntervalT::right_open(values,   values+3) << endl;

    ptr_set += IntervalT::right_open(values,   values+3);
    ptr_set += IntervalT::right_open(values+4, values+7);
    IntervalSetT::difference_type count = ptr_set.size();

    ICL_const_FORALL(IntervalSetT, it_, ptr_set)
    {
        for(T ptr = first(*it_); ptr <= last(*it_); ++ptr)
            cout << *ptr << " ";
    }
    cout << endl;

    cout << ptr_set << endl;

    BOOST_CHECK_EQUAL(true, true);
}

