
//  (C) Copyright John Maddock 2000. Permission to copy, use, modify, sell and   
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

#include <boost/type_traits.hpp>
#include "boost/type_traits/type_traits_test.hpp"

template <class T>
#if !defined(__BORLANDC__) && !defined(__sgi) && !defined(__DECCXX) 
void is_function_test(T& foo)
#else
void is_function_test(const T& foo)
#endif
{
   value_test(true, ::boost::is_function<T>::value);
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
   value_test(false, ::boost::is_void<T>::value);
   value_test(false, ::boost::is_integral<T>::value);
   value_test(false, ::boost::is_float<T>::value);
   value_test(false, ::boost::is_arithmetic<T>::value);
   value_test(false, ::boost::is_fundamental<T>::value);
   value_test(false, ::boost::is_pointer<T>::value);
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

void foo0(){}
void foo1(int){}
void foo2(int&, double){}
void foo3(int&, bool, int, int){}
void foo4(int, bool, int*, int[], int, int, int, int, int){}


int main(int argc, char* argv[])
{
   is_function_test(foo0);
   is_function_test(foo1);
   is_function_test(foo2);
   is_function_test(foo3);
   is_function_test(foo4);

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




