
//  (C) Copyright John Maddock 2000. Permission to copy, use, modify, sell and   
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

#include "test.hpp"
#include "check_integral_constant.hpp"
#include TYPE_TRAITS(alignment_of)
#include TYPE_TRAITS(has_nothrow_assign)
#include TYPE_TRAITS(has_nothrow_constructor)
#include TYPE_TRAITS(has_nothrow_copy)
#include TYPE_TRAITS(is_base_and_derived)
#include TYPE_COMPARE(is_same)
#include TYPE_COMPARE(is_convertible)

//
// VC++ emits an awful lot of warnings unless we define these:
#ifdef BOOST_MSVC
#  pragma warning(disable:4244)
#endif


template <class T>
struct align_calc
{
   char padding;
   T instance;
   static std::ptrdiff_t get()
   {
      static align_calc<T> a;
      return reinterpret_cast<const char*>(&(a.instance)) - reinterpret_cast<const char*>(&(a.padding));
   }
};

#define ALIGNOF(x) align_calc<x>::get()


TT_TEST_BEGIN(partial_specialization_tricky_tests)
//
// corner cases which don't compile without partial specialization
// support:
//

BOOST_CHECK_INTEGRAL_CONSTANT(::tt::alignment_of<char&>::value, ALIGNOF(void*));
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::alignment_of<char (&)(int)>::value, ALIGNOF(void*));
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::alignment_of<char(&)[4]>::value, ALIGNOF(void*));

BOOST_CHECK_INTEGRAL_CONSTANT((::tt::is_base_and_derived<Base&,Derived>::value), false);
BOOST_CHECK_INTEGRAL_CONSTANT((::tt::is_base_and_derived<Base&,Derived&>::value), false);
BOOST_CHECK_INTEGRAL_CONSTANT((::tt::is_base_and_derived<Base,Derived&>::value), false);
BOOST_CHECK_INTEGRAL_CONSTANT((::tt::is_base_and_derived<Base,void>::value), false);

BOOST_CHECK_INTEGRAL_CONSTANT((::tt::is_same<void, int>::value), false);
BOOST_CHECK_INTEGRAL_CONSTANT((::tt::is_same<void, void>::value), true);
BOOST_CHECK_INTEGRAL_CONSTANT((::tt::is_same<void, const void>::value), false);
BOOST_CHECK_INTEGRAL_CONSTANT((::tt::is_same<test_abc1, test_abc1>::value), true);
BOOST_CHECK_INTEGRAL_CONSTANT((::tt::is_same<test_abc1, const test_abc1>::value), false);

BOOST_CHECK_INTEGRAL_CONSTANT((::tt::is_convertible<void,float>::value), false);

TT_TEST_END







