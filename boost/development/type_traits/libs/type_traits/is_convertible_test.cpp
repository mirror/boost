
//  (C) Copyright John Maddock 2000. Permission to copy, use, modify, sell and   
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

#include <boost/type_traits/conversion_traits.hpp>
#include <boost/utility.hpp>
#include "boost/type_traits/type_traits_test.hpp"


int main(int argc, char* argv[])
{
   value_test(true, (boost::is_convertible<Deriverd,Base>::value));
   value_test(true, (boost::is_convertible<Deriverd,Deriverd>::value));
   value_test(true, (boost::is_convertible<Base,Base>::value));
   value_test(false, (boost::is_convertible<Base,Deriverd>::value));
   value_test(true, (boost::is_convertible<Deriverd,Deriverd>::value));
   value_test(false, (boost::is_convertible<NonDerived,Base>::value));
   value_test(false, (boost::is_convertible<boost::noncopyable, int>::value));
   value_test(true, (boost::is_convertible<float,int>::value));
#if defined(BOOST_MSVC6_MEMBER_TEMPLATES) || !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
   value_test(false, (boost::is_convertible<float,void>::value));
   value_test(false, (boost::is_convertible<void,float>::value));
   value_test(true, (boost::is_convertible<void,void>::value));
#endif
   value_test(true, (boost::is_convertible<enum1, int>::value));
   value_test(true, (boost::is_convertible<Deriverd*, Base*>::value));
   value_test(false, (boost::is_convertible<Base*, Deriverd*>::value));
   value_test(true, (boost::is_convertible<Deriverd&, Base&>::value));
   value_test(false, (boost::is_convertible<Base&, Deriverd&>::value));
   value_test(true, (boost::is_convertible<const Deriverd*, const Base*>::value));
   value_test(false, (boost::is_convertible<const Base*, const Deriverd*>::value));
   value_test(true, (boost::is_convertible<const Deriverd&, const Base&>::value));
   value_test(false, (boost::is_convertible<const Base&, const Deriverd&>::value));

   value_test(false, (boost::is_convertible<const int *, int*>::value));
   value_test(false, (boost::is_convertible<const int&, int&>::value));
   value_test(true, (boost::is_convertible<int*, int[2]>::value));
   value_test(false, (boost::is_convertible<const int*, int[3]>::value));
   value_test(true, (boost::is_convertible<const int&, int>::value));
   value_test(true, (boost::is_convertible<int(&)[4], const int*>::value));
   value_test(true, (boost::is_convertible<int(&)(int), int(*)(int)>::value));
   value_test(true, (boost::is_convertible<int *, const int*>::value));
   value_test(true, (boost::is_convertible<int&, const int&>::value));
   value_test(true, (boost::is_convertible<int[2], int*>::value));
   value_test(true, (boost::is_convertible<int[2], const int*>::value));
   value_test(false, (boost::is_convertible<const int[2], int*>::value));

   value_test(true, (boost::is_convertible<non_pointer, void*>::value));
   value_test(false, (boost::is_convertible<non_pointer, int*>::value));
   value_test(true, (boost::is_convertible<non_int_pointer, int*>::value));
   value_test(true, (boost::is_convertible<non_int_pointer, void*>::value));
   value_test(true, (boost::is_convertible<int, int_constructible>::value));

   return check_result(argc, argv);
}

//
// define the number of failures expected for given compilers:
#ifdef __BORLANDC__
unsigned int expected_failures = 1;
#else
unsigned int expected_failures = 0;
#endif







