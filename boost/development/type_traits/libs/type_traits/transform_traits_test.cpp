
//  (C) Copyright John Maddock 2000. Permission to copy, use, modify, sell and   
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

#include <boost/type_traits/transform_traits.hpp>
#include <boost/type_traits/cv_traits.hpp>
#include <boost/utility.hpp>

#ifdef __BORLANDC__
#pragma hrdstop
#endif
#include "boost/type_traits/type_traits_test.hpp"

//
// some of these tests, particularly those involving
// the use of the transform_check macro are tantamount
// to "compiler-abuse", and actually hide a *lot* of
// template test code.  To prevent "Internal Compiler Error"
// type messages, we have to split these up into lots of
// separate functions:
#define BOOST_DECL_TRANSFORM_TEST(name, type, from, to)\
void name(){ transform_check(type, from, to) }
#define BOOST_DECL_TRANSFORM_TEST3(name, type, from)\
void name(){ transform_check(type, from, boost_dummy_macro_param) }
#define BOOST_DECL_TRANSFORM_TEST2(name, type)\
void name(){ transform_check(type, boost_dummy_macro_param, boost_dummy_macro_param) }

/***********************************************************************
 *
 * tests for remove_const:
 *
 **********************************************************************/

BOOST_DECL_TRANSFORM_TEST3(remove_const_test_1, ::boost::remove_const, const)
BOOST_DECL_TRANSFORM_TEST(remove_const_test_2, ::boost::remove_const, volatile, volatile)
BOOST_DECL_TRANSFORM_TEST(remove_const_test_3, ::boost::remove_const, const volatile, volatile)
BOOST_DECL_TRANSFORM_TEST2(remove_const_test_4, ::boost::remove_const)
BOOST_DECL_TRANSFORM_TEST(remove_const_test_6, ::boost::remove_const, *const, *)
BOOST_DECL_TRANSFORM_TEST(remove_const_test_7, ::boost::remove_const, *volatile, *volatile)
BOOST_DECL_TRANSFORM_TEST(remove_const_test_8, ::boost::remove_const, *const volatile, *volatile)
BOOST_DECL_TRANSFORM_TEST(remove_const_test_9, ::boost::remove_const, *, *)
BOOST_DECL_TRANSFORM_TEST(remove_const_test_11, ::boost::remove_const, volatile*, volatile*)
BOOST_DECL_TRANSFORM_TEST(remove_const_test_12, ::boost::remove_const, const[2], [2])
BOOST_DECL_TRANSFORM_TEST(remove_const_test_13, ::boost::remove_const, volatile[2], volatile[2])
BOOST_DECL_TRANSFORM_TEST(remove_const_test_14, ::boost::remove_const, const volatile[2], volatile[2])
BOOST_DECL_TRANSFORM_TEST(remove_const_test_15, ::boost::remove_const, [2], [2])
BOOST_DECL_TRANSFORM_TEST(remove_const_test_16, ::boost::remove_const, const*, const*)
BOOST_DECL_TRANSFORM_TEST(remove_const_test_17, ::boost::remove_const, const*const, const*)

void check_remove_const()
{
   remove_const_test_1();
   remove_const_test_2();
   remove_const_test_3();
   remove_const_test_4();
   remove_const_test_6();
   remove_const_test_7();
   remove_const_test_8();
   remove_const_test_9();
   remove_const_test_11();
   remove_const_test_12();
   remove_const_test_13();
   remove_const_test_14();
   remove_const_test_15();
   remove_const_test_16();
   remove_const_test_17();
}

/***********************************************************************
 *
 * tests for remove_volatile:
 *
 **********************************************************************/

BOOST_DECL_TRANSFORM_TEST(remove_volatile_test_1, ::boost::remove_volatile, const, const)
BOOST_DECL_TRANSFORM_TEST3(remove_volatile_test_2, ::boost::remove_volatile, volatile)
BOOST_DECL_TRANSFORM_TEST(remove_volatile_test_3, ::boost::remove_volatile, const volatile, const)
BOOST_DECL_TRANSFORM_TEST2(remove_volatile_test_4, ::boost::remove_volatile)
BOOST_DECL_TRANSFORM_TEST2(remove_volatile_test_5, ::boost::remove_volatile)
BOOST_DECL_TRANSFORM_TEST(remove_volatile_test_6, ::boost::remove_volatile, *const, *const)
BOOST_DECL_TRANSFORM_TEST(remove_volatile_test_7, ::boost::remove_volatile, *volatile, *)
BOOST_DECL_TRANSFORM_TEST(remove_volatile_test_8, ::boost::remove_volatile, *const volatile, *const)
BOOST_DECL_TRANSFORM_TEST(remove_volatile_test_9, ::boost::remove_volatile, *, *)
BOOST_DECL_TRANSFORM_TEST(remove_volatile_test_10, ::boost::remove_volatile, *, *)
BOOST_DECL_TRANSFORM_TEST(remove_volatile_test_11, ::boost::remove_volatile, volatile*, volatile*)
BOOST_DECL_TRANSFORM_TEST(remove_volatile_test_12, ::boost::remove_volatile, const[2], const[2])
BOOST_DECL_TRANSFORM_TEST(remove_volatile_test_13, ::boost::remove_volatile, volatile[2], [2])
BOOST_DECL_TRANSFORM_TEST(remove_volatile_test_14, ::boost::remove_volatile, const volatile[2], const[2])
BOOST_DECL_TRANSFORM_TEST(remove_volatile_test_15, ::boost::remove_volatile, [2], [2])
BOOST_DECL_TRANSFORM_TEST(remove_volatile_test_16, ::boost::remove_volatile, const*, const*)
BOOST_DECL_TRANSFORM_TEST(remove_volatile_test_17, ::boost::remove_volatile, const*volatile, const*)

void check_remove_volatile()
{
   remove_volatile_test_1();
   remove_volatile_test_2();
   remove_volatile_test_3();
   remove_volatile_test_4();
   remove_volatile_test_5();
   remove_volatile_test_6();
   remove_volatile_test_7();
   remove_volatile_test_8();
   remove_volatile_test_9();
   remove_volatile_test_10();
   remove_volatile_test_11();
   remove_volatile_test_12();
   remove_volatile_test_13();
   remove_volatile_test_14();
   remove_volatile_test_15();
   remove_volatile_test_16();
   remove_volatile_test_17();
}

/***********************************************************************
 *
 * tests for remove_cv:
 *
 **********************************************************************/

BOOST_DECL_TRANSFORM_TEST3(remove_cv_test_1, ::boost::remove_cv, const)
BOOST_DECL_TRANSFORM_TEST3(remove_cv_test_2, ::boost::remove_cv, volatile)
BOOST_DECL_TRANSFORM_TEST3(remove_cv_test_3, ::boost::remove_cv, const volatile)
BOOST_DECL_TRANSFORM_TEST2(remove_cv_test_4, ::boost::remove_cv)
BOOST_DECL_TRANSFORM_TEST(remove_cv_test_5, ::boost::remove_cv, const &, const&)
BOOST_DECL_TRANSFORM_TEST(remove_cv_test_6, ::boost::remove_cv, *const, *)
BOOST_DECL_TRANSFORM_TEST(remove_cv_test_7, ::boost::remove_cv, *volatile, *)
BOOST_DECL_TRANSFORM_TEST(remove_cv_test_8, ::boost::remove_cv, *const volatile, *)
BOOST_DECL_TRANSFORM_TEST(remove_cv_test_9, ::boost::remove_cv, *, *)
BOOST_DECL_TRANSFORM_TEST(remove_cv_test_10, ::boost::remove_cv, const*, const*)
BOOST_DECL_TRANSFORM_TEST(remove_cv_test_11, ::boost::remove_cv, volatile*, volatile*)
BOOST_DECL_TRANSFORM_TEST(remove_cv_test_12, ::boost::remove_cv, const[2], [2])
BOOST_DECL_TRANSFORM_TEST(remove_cv_test_13, ::boost::remove_cv, volatile[2], [2])
BOOST_DECL_TRANSFORM_TEST(remove_cv_test_14, ::boost::remove_cv, const volatile[2], [2])
BOOST_DECL_TRANSFORM_TEST(remove_cv_test_15, ::boost::remove_cv, [2], [2])
BOOST_DECL_TRANSFORM_TEST(remove_cv_test_16, ::boost::remove_cv, const*, const*)
BOOST_DECL_TRANSFORM_TEST(remove_cv_test_17, ::boost::remove_cv, const*volatile, const*)

void check_remove_cv()
{
   remove_cv_test_1();
   remove_cv_test_2();
   remove_cv_test_3();
   remove_cv_test_4();
   remove_cv_test_5();
   remove_cv_test_6();
   remove_cv_test_7();
   remove_cv_test_8();
   remove_cv_test_9();
   remove_cv_test_10();
   remove_cv_test_11();
   remove_cv_test_12();
   remove_cv_test_13();
   remove_cv_test_14();
   remove_cv_test_15();
   remove_cv_test_16();
   remove_cv_test_17();
}

/***********************************************************************
 *
 * tests for remove_reference:
 *
 **********************************************************************/

BOOST_DECL_TRANSFORM_TEST(remove_reference_test_1, ::boost::remove_reference, const, const)
BOOST_DECL_TRANSFORM_TEST(remove_reference_test_2, ::boost::remove_reference, volatile, volatile)
BOOST_DECL_TRANSFORM_TEST3(remove_reference_test_3, ::boost::remove_reference, &)
BOOST_DECL_TRANSFORM_TEST2(remove_reference_test_4, ::boost::remove_reference)
BOOST_DECL_TRANSFORM_TEST(remove_reference_test_5, ::boost::remove_reference, const &, const)
BOOST_DECL_TRANSFORM_TEST(remove_reference_test_6, ::boost::remove_reference, *, *)
BOOST_DECL_TRANSFORM_TEST(remove_reference_test_7, ::boost::remove_reference, *volatile, *volatile)
BOOST_DECL_TRANSFORM_TEST3(remove_reference_test_8, ::boost::remove_reference, &)
BOOST_DECL_TRANSFORM_TEST(remove_reference_test_9, ::boost::remove_reference, const &, const)
BOOST_DECL_TRANSFORM_TEST(remove_reference_test_10, ::boost::remove_reference, const*, const*)
BOOST_DECL_TRANSFORM_TEST(remove_reference_test_11, ::boost::remove_reference, volatile*, volatile*)
BOOST_DECL_TRANSFORM_TEST(remove_reference_test_12, ::boost::remove_reference, const[2], const[2])
BOOST_DECL_TRANSFORM_TEST(remove_reference_test_13, ::boost::remove_reference, (&)[2], [2])

void check_remove_reference()
{
   remove_reference_test_1();
   remove_reference_test_2();
   remove_reference_test_3();
   remove_reference_test_4();
   remove_reference_test_5();
   remove_reference_test_6();
   remove_reference_test_7();
   remove_reference_test_8();
   remove_reference_test_9();
   remove_reference_test_10();
   remove_reference_test_11();
   remove_reference_test_12();
   remove_reference_test_13();
}

/***********************************************************************
 *
 * tests for remove_bounds:
 *
 **********************************************************************/

BOOST_DECL_TRANSFORM_TEST(remove_bounds_test_1, ::boost::remove_bounds, const, const)
BOOST_DECL_TRANSFORM_TEST(remove_bounds_test_2, ::boost::remove_bounds, volatile, volatile)
BOOST_DECL_TRANSFORM_TEST3(remove_bounds_test_3, ::boost::remove_bounds, [2])
BOOST_DECL_TRANSFORM_TEST2(remove_bounds_test_4, ::boost::remove_bounds)
BOOST_DECL_TRANSFORM_TEST(remove_bounds_test_5, ::boost::remove_bounds, const &, const&)
BOOST_DECL_TRANSFORM_TEST(remove_bounds_test_6, ::boost::remove_bounds, *, *)
BOOST_DECL_TRANSFORM_TEST(remove_bounds_test_7, ::boost::remove_bounds, *volatile, *volatile)
BOOST_DECL_TRANSFORM_TEST(remove_bounds_test_8, ::boost::remove_bounds, const [2], const)
BOOST_DECL_TRANSFORM_TEST(remove_bounds_test_9, ::boost::remove_bounds, const &, const&)
BOOST_DECL_TRANSFORM_TEST(remove_bounds_test_10, ::boost::remove_bounds, const*, const*)
BOOST_DECL_TRANSFORM_TEST(remove_bounds_test_11, ::boost::remove_bounds, volatile*, volatile*)
BOOST_DECL_TRANSFORM_TEST(remove_bounds_test_12, ::boost::remove_bounds, const[2][3], const[3])
BOOST_DECL_TRANSFORM_TEST(remove_bounds_test_13, ::boost::remove_bounds, (&)[2], (&)[2])

void check_remove_bounds()
{
   remove_bounds_test_1();
   remove_bounds_test_2();
   remove_bounds_test_3();
   remove_bounds_test_4();
   remove_bounds_test_5();
   remove_bounds_test_6();
   remove_bounds_test_7();
   remove_bounds_test_8();
   remove_bounds_test_9();
   remove_bounds_test_10();
   remove_bounds_test_11();
   remove_bounds_test_12();
   remove_bounds_test_13();
}

/***********************************************************************
 *
 * tests for remove_pointer:
 *
 **********************************************************************/

BOOST_DECL_TRANSFORM_TEST(remove_pointer_test_1, ::boost::remove_pointer, const, const)
BOOST_DECL_TRANSFORM_TEST(remove_pointer_test_2, ::boost::remove_pointer, volatile, volatile)
BOOST_DECL_TRANSFORM_TEST3(remove_pointer_test_3, ::boost::remove_pointer, *)
BOOST_DECL_TRANSFORM_TEST2(remove_pointer_test_4, ::boost::remove_pointer)
BOOST_DECL_TRANSFORM_TEST(remove_pointer_test_5, ::boost::remove_pointer, const &, const&)
BOOST_DECL_TRANSFORM_TEST(remove_pointer_test_6, ::boost::remove_pointer, &, &)
BOOST_DECL_TRANSFORM_TEST3(remove_pointer_test_7, ::boost::remove_pointer, *volatile)
BOOST_DECL_TRANSFORM_TEST(remove_pointer_test_8, ::boost::remove_pointer, const [2], const[2])
BOOST_DECL_TRANSFORM_TEST(remove_pointer_test_9, ::boost::remove_pointer, const &, const&)
BOOST_DECL_TRANSFORM_TEST(remove_pointer_test_10, ::boost::remove_pointer, const*, const)
BOOST_DECL_TRANSFORM_TEST(remove_pointer_test_11, ::boost::remove_pointer, volatile*, volatile)
BOOST_DECL_TRANSFORM_TEST(remove_pointer_test_12, ::boost::remove_pointer, const[2][3], const[2][3])
BOOST_DECL_TRANSFORM_TEST(remove_pointer_test_13, ::boost::remove_pointer, (&)[2], (&)[2])

void check_remove_pointer()
{
   remove_pointer_test_1();
   remove_pointer_test_2();
   remove_pointer_test_3();
   remove_pointer_test_4();
   remove_pointer_test_5();
   remove_pointer_test_6();
   remove_pointer_test_7();
   remove_pointer_test_8();
   remove_pointer_test_9();
   remove_pointer_test_10();
   remove_pointer_test_11();
   remove_pointer_test_12();
   remove_pointer_test_13();
}

/***********************************************************************
 *
 * tests for add_reference:
 *
 **********************************************************************/

BOOST_DECL_TRANSFORM_TEST(add_reference_test_1, ::boost::add_reference, const, const&)
BOOST_DECL_TRANSFORM_TEST(add_reference_test_2, ::boost::add_reference, volatile, volatile&)
BOOST_DECL_TRANSFORM_TEST(add_reference_test_3, ::boost::add_reference, *, *&)
//BOOST_DECL_TRANSFORM_TEST2(add_reference_test_4, ::boost::add_reference)
BOOST_DECL_TRANSFORM_TEST(add_reference_test_5, ::boost::add_reference, const &, const&)
BOOST_DECL_TRANSFORM_TEST(add_reference_test_6, ::boost::add_reference, &, &)
BOOST_DECL_TRANSFORM_TEST(add_reference_test_7, ::boost::add_reference, *volatile, *volatile&)
BOOST_DECL_TRANSFORM_TEST(add_reference_test_8, ::boost::add_reference, const [2], const (&)[2])
BOOST_DECL_TRANSFORM_TEST(add_reference_test_9, ::boost::add_reference, const &, const&)
BOOST_DECL_TRANSFORM_TEST(add_reference_test_10, ::boost::add_reference, const*, const*&)
BOOST_DECL_TRANSFORM_TEST(add_reference_test_11, ::boost::add_reference, volatile*, volatile*&)
BOOST_DECL_TRANSFORM_TEST(add_reference_test_12, ::boost::add_reference, const[2][3], const (&)[2][3])
BOOST_DECL_TRANSFORM_TEST(add_reference_test_13, ::boost::add_reference, (&)[2], (&)[2])

void check_add_reference()
{
   add_reference_test_1();
   add_reference_test_2();
   add_reference_test_3();
   //add_reference_test_4();
   add_reference_test_5();
   add_reference_test_6();
   add_reference_test_7();
   add_reference_test_8();
   add_reference_test_9();
   add_reference_test_10();
   add_reference_test_11();
   add_reference_test_12();
   add_reference_test_13();
}

/***********************************************************************
 *
 * tests for add_pointer:
 *
 **********************************************************************/

BOOST_DECL_TRANSFORM_TEST(add_pointer_test_1, ::boost::add_pointer, const, const*)
BOOST_DECL_TRANSFORM_TEST(add_pointer_test_2, ::boost::add_pointer, volatile, volatile*)
BOOST_DECL_TRANSFORM_TEST(add_pointer_test_3, ::boost::add_pointer, *, **)
//BOOST_DECL_TRANSFORM_TEST2(add_pointer_test_4, ::boost::add_pointer)
BOOST_DECL_TRANSFORM_TEST(add_pointer_test_5, ::boost::add_pointer, const &, const*)
BOOST_DECL_TRANSFORM_TEST(add_pointer_test_6, ::boost::add_pointer, &, *)
BOOST_DECL_TRANSFORM_TEST(add_pointer_test_7, ::boost::add_pointer, *volatile, *volatile*)
BOOST_DECL_TRANSFORM_TEST(add_pointer_test_8, ::boost::add_pointer, const [2], const *)
BOOST_DECL_TRANSFORM_TEST(add_pointer_test_9, ::boost::add_pointer, const &, const*)
BOOST_DECL_TRANSFORM_TEST(add_pointer_test_10, ::boost::add_pointer, const*, const**)
BOOST_DECL_TRANSFORM_TEST(add_pointer_test_11, ::boost::add_pointer, volatile*, volatile**)
BOOST_DECL_TRANSFORM_TEST(add_pointer_test_12, ::boost::add_pointer, const[2][3], const (*)[3])
BOOST_DECL_TRANSFORM_TEST(add_pointer_test_13, ::boost::add_pointer, (&)[2], *)

void check_add_pointer()
{
   add_pointer_test_1();
   add_pointer_test_2();
   add_pointer_test_3();
   //add_pointer_test_4();
   add_pointer_test_5();
   add_pointer_test_6();
   add_pointer_test_7();
   add_pointer_test_8();
   add_pointer_test_9();
   add_pointer_test_10();
   add_pointer_test_11();
   add_pointer_test_12();
   add_pointer_test_13();
}


int main(int argc, char* argv[])
{
   check_remove_const();
   check_remove_volatile();
   check_remove_cv();
   check_remove_reference();
   check_remove_bounds();
   check_remove_pointer();
   check_add_reference();
   check_add_pointer();

   type_test(void, boost::remove_const<void>::type)
   type_test(void, boost::remove_volatile<void>::type)
   type_test(void, boost::remove_cv<void>::type)

   type_test(int, boost::remove_reference<cr_type>::type)
   type_test(void, boost::remove_reference<void>::type)

   type_test(void, boost::remove_bounds<void>::type)
   type_test(void, boost::remove_pointer<void>::type)

   return check_result(argc, argv);
}

//
// define the number of failures expected for given compilers:
#ifdef __BORLANDC__
unsigned int expected_failures = 4; // cv-qualifiers
#elif defined(__GNUC__)
unsigned int expected_failures = 1; // cv-qualified references
#else
unsigned int expected_failures = 0;
#endif



