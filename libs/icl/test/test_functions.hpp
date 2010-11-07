/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------+
Auxiliary functions to reduce redundancies in test case code.
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TEST_FUNCTIONS_H_JOFA_091003
#define BOOST_ICL_TEST_FUNCTIONS_H_JOFA_091003

#include <boost/icl/detail/notate.hpp>
#include <boost/icl/type_traits/interval_type_default.hpp>
#include <boost/icl/discrete_interval.hpp>

#include <boost/icl/type_traits/identity_element.hpp>
#include <boost/icl/functors.hpp>

namespace boost{namespace icl
{

template <class T, class U, class Trt,
          template<class T, class U,
                   class Traits = Trt,
                   ICL_COMPARE Compare = ICL_COMPARE_INSTANCE(std::less, T),
                   ICL_COMBINE Combine = ICL_COMBINE_INSTANCE(icl::inplace_plus, U),
                   ICL_SECTION Section = ICL_SECTION_INSTANCE(icl::inter_section, U),
                   ICL_INTERVAL(ICL_COMPARE)  Interval = ICL_INTERVAL_INSTANCE(ICL_INTERVAL_DEFAULT, T, Compare),
                   ICL_ALLOC   Alloc   = std::allocator
                  >class IntervalMap,
          class SequenceT
>
void itl_map_copy(const SequenceT& segments, 
                  IntervalMap<T,U,Trt>& destination)
{
    ICL_const_FORALL(typename SequenceT, segment_, segments)
        destination.insert(*segment_);
}


template <class T, class U, class Trt,
          template<class T, class U,
                   class Traits = Trt,
                   ICL_COMPARE Compare = ICL_COMPARE_INSTANCE(std::less, U),
                   ICL_COMBINE Combine = ICL_COMBINE_INSTANCE(icl::inplace_plus, U),
                   ICL_SECTION Section = ICL_SECTION_INSTANCE(icl::inter_section, U),
                   ICL_INTERVAL(ICL_COMPARE)  Interval = ICL_INTERVAL_INSTANCE(ICL_INTERVAL_DEFAULT, T, Compare),
                   ICL_ALLOC   Alloc   = std::allocator
                  >class IntervalMap,
          class SequenceT
>
void test_interval_map_copy_via_inserter(const SequenceT& segments, IntervalMap<T,U,Trt>& std_copied_map)
{
    // The second parameter (std_copied_map) could be omitted and only held as a 
    // local variable. I is there to help gcc-3.4.4 resolving the function template type.
    typedef IntervalMap<T,U,Trt> IntervalMapT;
    IntervalMapT looped_copied_map;
    std_copied_map.clear();
    itl_map_copy(segments, looped_copied_map);
    std::copy(segments.begin(), segments.end(), std::inserter(std_copied_map, std_copied_map.end()));
    BOOST_CHECK_EQUAL( looped_copied_map, std_copied_map );
}

}} // namespace icl boost

#endif // BOOST_ICL_TEST_FUNCTIONS_H_JOFA_091003

