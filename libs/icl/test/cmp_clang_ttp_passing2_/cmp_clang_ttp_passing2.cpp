/*-----------------------------------------------------------------------------+    
Copyright (c) 2011-2011: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#define BOOST_TEST_MODULE icl::cmp_clang_ttp_passing2 unit test
#include "../unit_test_unwarned.hpp"

#include <boost/icl/interval_set.hpp>

template 
<
	template
	<
		class _T,
		ICL_COMPARE Compare = ICL_COMPARE_INSTANCE(std::less, _T), 
		ICL_INTERVAL(ICL_COMPARE)  Interval = ICL_INTERVAL_INSTANCE(ICL_INTERVAL_DEFAULT, _T, Compare), 
		ICL_ALLOC   Alloc   = std::allocator
	>
	class IntervalSet,
	class T
>
bool test_ttp()
{
    typedef IntervalSet<T> IntervalSetT;
    IntervalSetT test_set;
    test_set.clear();
	return true;
}


BOOST_AUTO_TEST_CASE(dummy)
{
	bool result = test_ttp<boost::icl::interval_set, int>();
    BOOST_CHECK( result );
}

