
//  (C) Copyright John Maddock 2000. Permission to copy, use, modify, sell and   
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

#include <boost/type_traits.hpp>
#include <boost/test/execution_monitor.hpp>
#include "boost/type_traits/type_traits_test.hpp"

template <class T>
struct is_function_tester
{
   static void check();
};

template <class T>
void is_function_tester<T>::check()
{
   // if we're a function then we must not be a
   // function pointer:
   value_test(true, ::boost::is_function<T>::value);
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
   value_test(false, ::boost::is_pointer<T>::value);
   value_test(false, ::boost::is_void<T>::value);
   value_test(false, ::boost::is_integral<T>::value);
   value_test(false, ::boost::is_float<T>::value);
   value_test(false, ::boost::is_arithmetic<T>::value);
   value_test(false, ::boost::is_fundamental<T>::value);
   value_test(false, ::boost::is_reference<T>::value);
   value_test(false, ::boost::is_member_pointer<T>::value);
   value_test(false, ::boost::is_enum<T>::value);
   value_test(false, ::boost::is_union<T>::value);
   value_test(false, ::boost::is_object<T>::value);
   value_test(false, ::boost::is_scalar<T>::value);
   value_test(false, ::boost::is_class<T>::value);
   value_test(false, ::boost::is_compound<T>::value);
   value_test(false, ::boost::is_POD<T>::value);
   value_test(false, ::boost::has_trivial_constructor<T>::value);
   value_test(false, ::boost::has_trivial_copy<T>::value);
   value_test(false, ::boost::has_trivial_assign<T>::value);
   value_test(false, ::boost::has_trivial_destructor<T>::value);
   value_test(false, ::boost::is_empty<T>::value);
#endif
}

int cpp_main(int argc, char* argv[])
{
   typedef void foo0_t();
   typedef void foo1_t(int);
   typedef void foo2_t(int&, double);
   typedef void foo3_t(int&, bool, int, int);
   typedef void foo4_t(int, bool, int*, int[], int, int, int, int, int);

   is_function_tester<foo0_t>::check();
   is_function_tester<foo1_t>::check();
   is_function_tester<foo2_t>::check();
   is_function_tester<foo3_t>::check();
   is_function_tester<foo4_t>::check();

   value_test(false, ::boost::is_function<void>::value);
   value_test(false, ::boost::is_function<int>::value);
   value_test(false, ::boost::is_function<int*>::value);
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
   value_test(false, ::boost::is_function<const int&>::value);
   value_test(false, ::boost::is_function<int (&)(int)>::value);
#endif
   value_test(false, ::boost::is_function<int[]>::value);
   value_test(false, ::boost::is_function<test_abc1>::value);
   value_test(false, ::boost::is_function<int (*)(int)>::value);

   return check_result(argc, argv);
}

//
// define the number of failures expected for given compilers:
unsigned int expected_failures = 0;





