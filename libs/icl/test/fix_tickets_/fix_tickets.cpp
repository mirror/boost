/*-----------------------------------------------------------------------------+    
Copyright (c) 2011-2011: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#define BOOST_TEST_MODULE icl::fix_icl_after_thread unit test
#include <libs/icl/test/disable_test_warnings.hpp>
#include "../unit_test_unwarned.hpp"

//#define BOOST_ICL_USE_STATIC_BOUNDED_INTERVALS
#include <boost/icl/interval_map.hpp>
#include <boost/icl/split_interval_map.hpp>
#include <boost/icl/separate_interval_set.hpp>
#include <boost/icl/split_interval_set.hpp>

using namespace std;
using namespace boost;
using namespace unit_test;
using namespace boost::icl;


BOOST_AUTO_TEST_CASE(ticket_5482)
{
    typedef interval_map<int,int,partial_absorber,std::less>    m1_t;
    typedef interval_map<int,int,partial_absorber,std::greater> m2_t;
    m1_t m1;
    m2_t m2;
    m1.insert(make_pair(m1_t::interval_type(1), 20));
    m1.insert(make_pair(m1_t::interval_type(2), 20));
    m1.insert(make_pair(m1_t::interval_type(3), 20));

    m2.insert(make_pair(m2_t::interval_type(1), 20));
    m2.insert(make_pair(m2_t::interval_type(2), 20));
    m2.insert(make_pair(m2_t::interval_type(3), 20));

    BOOST_CHECK_EQUAL(m1.iterative_size(), m2.iterative_size());
    BOOST_CHECK_EQUAL(m1.iterative_size(), 1);
    BOOST_CHECK_EQUAL(m2.iterative_size(), 1);
}

