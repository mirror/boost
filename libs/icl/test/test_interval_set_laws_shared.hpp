/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef LIBS_ICL_TEST_TEST_ICL_interval_set_laws_shared_h_JOFA_090201__
#define LIBS_ICL_TEST_TEST_ICL_interval_set_laws_shared_h_JOFA_090201__


//------------------------------------------------------------------------------
// Monoid EAN
//------------------------------------------------------------------------------
template <class T,
          template<class T,
                   ICL_COMPARE Compare = ICL_COMPARE_INSTANCE(std::less, U),
                   ICL_INTERVAL(ICL_COMPARE)  Interval = ICL_INTERVAL_INSTANCE(ICL_INTERVAL_DEFAULT, T, Compare),
                   ICL_ALLOC   Alloc   = std::allocator
                  >class IntervalSet
          >
void interval_set_check_monoid_plus_4_bicremental_types()
{
    typedef IntervalSet<T> IntervalSetT;

    IntervalSetT set_a, set_b, set_c;
    set_a.add(I_D(3,6)).add(I_I(5,7));
    set_b.add(C_D(1,3)).add(I_D(8,9));
    set_c.add(I_D(0,9)).add(I_I(3,6)).add(I_D(5,7));

    typename IntervalSetT::segment_type segm = I_D(6,9);
    T elem = make<T>(5);

    CHECK_MONOID_INSTANCE_WRT(plus) (set_a, set_b, set_c, segm, elem);
    CHECK_MONOID_INSTANCE_WRT(pipe) (set_a, set_b, set_c, segm, elem);
}


template <class T,
          template<class T,
                   ICL_COMPARE Compare = ICL_COMPARE_INSTANCE(std::less, U),
                   ICL_INTERVAL(ICL_COMPARE)  Interval = ICL_INTERVAL_INSTANCE(ICL_INTERVAL_DEFAULT, T, Compare),
                   ICL_ALLOC   Alloc   = std::allocator
                  >class IntervalSet
          >
void interval_set_check_monoid_et_4_bicremental_types()
{
    typedef IntervalSet<T> IntervalSetT;

    IntervalSetT set_a, set_b, set_c;
    set_a.add(I_D(3,6)).add(I_I(5,7));
    set_b.add(C_D(1,3)).add(I_D(8,9));
    set_c.add(I_D(0,9)).add(I_I(3,6)).add(I_D(5,7));

    typename IntervalSetT::segment_type segm = I_D(6,9);
    T elem = make<T>(5);

    CHECK_MONOID_INSTANCE_WRT(et)   (set_a, set_b, set_c, segm, elem);
    CHECK_MONOID_INSTANCE_WRT(caret)(set_a, set_b, set_c, segm, elem);
}

//------------------------------------------------------------------------------
// Abelian monoid EANC
//------------------------------------------------------------------------------

template <class T,
          template<class T,
                   ICL_COMPARE Compare = ICL_COMPARE_INSTANCE(std::less, U),
                   ICL_INTERVAL(ICL_COMPARE)  Interval = ICL_INTERVAL_INSTANCE(ICL_INTERVAL_DEFAULT, T, Compare),
                   ICL_ALLOC   Alloc   = std::allocator
                  >class IntervalSet
          >
void interval_set_check_abelian_monoid_plus_4_bicremental_types()
{
    typedef IntervalSet<T> IntervalSetT;

    IntervalSetT set_a, set_b, set_c;
    set_a.add(I_D(3,6)).add(I_I(5,7));
    set_b.add(C_D(1,3)).add(I_D(8,9));
    set_c.add(I_D(0,9)).add(I_I(3,6)).add(I_D(5,7));

    typename IntervalSetT::segment_type segm = I_D(6,9);
    T elem = make<T>(5);

    CHECK_ABELIAN_MONOID_INSTANCE_WRT(plus) (set_a, set_b, set_c, segm, elem);
    CHECK_ABELIAN_MONOID_INSTANCE_WRT(pipe) (set_a, set_b, set_c, segm, elem);
}


template <class T,
          template<class T,
                   ICL_COMPARE Compare = ICL_COMPARE_INSTANCE(std::less, U),
                   ICL_INTERVAL(ICL_COMPARE)  Interval = ICL_INTERVAL_INSTANCE(ICL_INTERVAL_DEFAULT, T, Compare),
                   ICL_ALLOC   Alloc   = std::allocator
                  >class IntervalSet
          >
void interval_set_check_abelian_monoid_et_4_bicremental_types()
{
    typedef IntervalSet<T> IntervalSetT;

    IntervalSetT set_a, set_b, set_c;
    set_a.add(I_D(3,6)).add(I_I(5,7));
    set_b.add(C_D(1,3)).add(I_D(8,9));
    set_c.add(I_D(0,9)).add(I_I(3,6)).add(I_D(5,7));

    typename IntervalSetT::segment_type segm = I_D(6,9);
    T elem = make<T>(5);

    CHECK_ABELIAN_MONOID_INSTANCE_WRT(et)   (set_a, set_b, set_c, segm, elem);
    CHECK_ABELIAN_MONOID_INSTANCE_WRT(caret)(set_a, set_b, set_c, segm, elem);
}


//------------------------------------------------------------------------------
// Abelian partial invertive monoid 
//------------------------------------------------------------------------------
template <class T,
          template<class T,
                   ICL_COMPARE Compare = ICL_COMPARE_INSTANCE(std::less, U),
                   ICL_INTERVAL(ICL_COMPARE)  Interval = ICL_INTERVAL_INSTANCE(ICL_INTERVAL_DEFAULT, T, Compare),
                   ICL_ALLOC   Alloc   = std::allocator
                  >class IntervalSet
          >
void interval_set_check_partial_invertive_monoid_plus_4_bicremental_types()
{
    typedef IntervalSet<T> IntervalSetT;

    IntervalSetT set_a, set_b, set_c;
    set_a.add(I_D(3,6)).add(I_I(5,7));
    set_b.add(C_D(1,3)).add(I_D(8,9));
    set_c.add(I_D(0,9)).add(I_I(3,6)).add(I_D(5,7));

    typename IntervalSetT::segment_type segm = I_D(6,9);
    T elem = make<T>(5);

    CHECK_PARTIAL_INVERTIVE_MONOID_INSTANCE_WRT(plus) (set_a, set_b, set_c, segm, elem);
    CHECK_PARTIAL_INVERTIVE_MONOID_INSTANCE_WRT(pipe) (set_a, set_b, set_c, segm, elem);
}

//------------------------------------------------------------------------------
// Abelian partial invertive monoid with protonic equality for inversion
//------------------------------------------------------------------------------
template <class T,
          template<class T,
                   ICL_COMPARE Compare = ICL_COMPARE_INSTANCE(std::less, U),
                   ICL_INTERVAL(ICL_COMPARE)  Interval = ICL_INTERVAL_INSTANCE(ICL_INTERVAL_DEFAULT, T, Compare),
                   ICL_ALLOC   Alloc   = std::allocator
                  >class IntervalSet
          >
void interval_set_check_partial_invertive_monoid_plus_prot_inv_4_bicremental_types()
{
    typedef IntervalSet<T> IntervalSetT;

    IntervalSetT set_a, set_b, set_c;
    set_a.add(I_D(3,6)).add(I_I(5,7));
    set_b.add(C_D(1,3)).add(I_D(8,9));
    set_c.add(I_D(0,9)).add(I_I(3,6)).add(I_D(5,7));

    typename IntervalSetT::segment_type segm = I_D(6,9);
    T elem = make<T>(5);

    CHECK_ABELIAN_MONOID_INSTANCE_WRT(plus)(set_a, set_b, set_c, segm, elem);
    CHECK_ABELIAN_MONOID_INSTANCE_WRT(pipe)(set_a, set_b, set_c, segm, elem);

    CHECK_PARTIAL_INVERTIVE_MONOID_INSTANCE_WRT_EQUAL(plus)(is_distinct_equal, set_a, set_b, set_c, segm, elem);
    CHECK_PARTIAL_INVERTIVE_MONOID_INSTANCE_WRT_EQUAL(pipe)(is_distinct_equal, set_a, set_b, set_c, segm, elem);
}


//------------------------------------------------------------------------------
// Abelian group EANIC
//------------------------------------------------------------------------------
template <class T,
          template<class T,
                   ICL_COMPARE Compare = ICL_COMPARE_INSTANCE(std::less, U),
                   ICL_INTERVAL(ICL_COMPARE)  Interval = ICL_INTERVAL_INSTANCE(ICL_INTERVAL_DEFAULT, T, Compare),
                   ICL_ALLOC   Alloc   = std::allocator
                  >class IntervalSet
          >
void interval_set_check_abelian_group_plus_4_bicremental_types()
{
    typedef IntervalSet<T> IntervalSetT;

    IntervalSetT set_a, set_b, set_c;
    set_a.add(I_D(3,6)).add(I_I(5,7));
    set_b.add(C_D(1,3)).add(I_D(8,9));
    set_c.add(I_D(0,9)).add(I_I(3,6)).add(I_D(5,7));

    typename IntervalSetT::segment_type segm = I_D(6,9);
    T elem = make<T>(5);

    CHECK_ABELIAN_GROUP_INSTANCE_WRT(plus) (set_a, set_b, set_c, segm, elem);
    CHECK_ABELIAN_GROUP_INSTANCE_WRT(pipe) (set_a, set_b, set_c, segm, elem);
}

//------------------------------------------------------------------------------
// (0 - x) + x =p= 0  |  
//------------------------------------------------------------------------------
template <class T,
          template<class T,
                   ICL_COMPARE Compare = ICL_COMPARE_INSTANCE(std::less, U),
                   ICL_INTERVAL(ICL_COMPARE)  Interval = ICL_INTERVAL_INSTANCE(ICL_INTERVAL_DEFAULT, T, Compare),
                   ICL_ALLOC   Alloc   = std::allocator
                  >class IntervalSet
          >
void interval_set_check_abelian_group_plus_prot_inv_4_bicremental_types()
{
    typedef IntervalSet<T> IntervalSetT;

    IntervalSetT set_a, set_b, set_c;
    set_a.add(I_D(3,6)).add(I_I(5,7));
    set_b.add(C_D(1,3)).add(I_D(8,9));
    set_c.add(I_D(0,9)).add(I_I(3,6)).add(I_D(5,7));

    typename IntervalSetT::segment_type segm = I_D(6,9);
    T elem = make<T>(5);

    CHECK_ABELIAN_MONOID_INSTANCE_WRT(plus) (set_a, set_b, set_c, segm, elem);
    CHECK_ABELIAN_MONOID_INSTANCE_WRT(pipe) (set_a, set_b, set_c, segm, elem);

    CHECK_ABELIAN_GROUP_INSTANCE_WRT_EQUAL(plus) (is_distinct_equal, set_a, set_b, set_c, segm, elem);
    CHECK_ABELIAN_GROUP_INSTANCE_WRT_EQUAL(pipe) (is_distinct_equal, set_a, set_b, set_c, segm, elem);
}

#endif // LIBS_ICL_TEST_TEST_ICL_interval_set_laws_shared_h_JOFA_090201__

