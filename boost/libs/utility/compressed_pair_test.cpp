// boost::compressed_pair test program

//  (C) Copyright John Maddock 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

#include <iostream>
#include <typeinfo>
#include <cassert>

#include <boost/compressed_pair.hpp>

using namespace boost;

#ifdef __BORLANDC__
#pragma option -w-ccc -w-rch -w-eff -w-aus
#endif

//
// define tests here
unsigned failures = 0;
unsigned test_count = 0;

#define value_test(v, x) ++test_count;\
                         if(v != x){++failures; std::cout << "checking value of " << #x << "...failed" << std::endl;}

#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#define type_test(v, x)  ++test_count;\
                         if(boost::is_same<v, x>::value == false){\
                           ++failures; \
                           std::cout << "checking type of " << #x << "...failed" << std::endl; \
                           std::cout << "   expected type was " << #v << std::endl; \
                           std::cout << "   " << typeid(boost::is_same<v, x>).name() << "::value is false" << std::endl; }
#else
#define type_test(v, x)  ++test_count;\
                         if(typeid(v) != typeid(x)){\
                           ++failures; \
                           std::cout << "checking type of " << #x << "...failed" << std::endl; \
                           std::cout << "   expected type was " << #v << std::endl; \
                           std::cout << "   " << "typeid(" #v ") != typeid(" #x ")" << std::endl; }
#endif

struct empty_POD_UDT{};
struct empty_UDT
{
  ~empty_UDT(){};
};
namespace boost {
#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
template <> struct is_empty<empty_UDT>
{ static const bool value = true; };
template <> struct is_empty<empty_POD_UDT>
{ static const bool value = true; };
template <> struct is_POD<empty_POD_UDT>
{ static const bool value = true; };
#else
template <> struct is_empty<empty_UDT>
{ enum{ value = true }; };
template <> struct is_empty<empty_POD_UDT>
{ enum{ value = true }; };
template <> struct is_POD<empty_POD_UDT>
{ enum{ value = true }; };
#endif
}


int main()
{
   compressed_pair<int, double> cp1(1, 1.3);
   assert(cp1.first() == 1);
   assert(cp1.second() == 1.3);
   compressed_pair<int, double> cp1b(2, 2.3);
   assert(cp1b.first() == 2);
   assert(cp1b.second() == 2.3);
   swap(cp1, cp1b);
   assert(cp1b.first() == 1);
   assert(cp1b.second() == 1.3);
   assert(cp1.first() == 2);
   assert(cp1.second() == 2.3);
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
   compressed_pair<empty_UDT, int> cp2(2);
   assert(cp2.second() == 2);
#endif
   compressed_pair<int, empty_UDT> cp3(1);
   assert(cp3.first() ==1);
   compressed_pair<empty_UDT, empty_UDT> cp4;
   compressed_pair<empty_UDT, empty_POD_UDT> cp5;
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
   int i = 0;
   compressed_pair<int&, int&> cp6(i,i);
   assert(cp6.first() == i);
   assert(cp6.second() == i);
   assert(&cp6.first() == &i);
   assert(&cp6.second() == &i);
   compressed_pair<int, double[2]> cp7;
   cp7.first();
   double* pd = cp7.second();
#endif
   value_test(true, (sizeof(compressed_pair<empty_UDT, int>) < sizeof(std::pair<empty_UDT, int>)))
   value_test(true, (sizeof(compressed_pair<int, empty_UDT>) < sizeof(std::pair<int, empty_UDT>)))
   value_test(true, (sizeof(compressed_pair<empty_UDT, empty_UDT>) < sizeof(std::pair<empty_UDT, empty_UDT>)))
   value_test(true, (sizeof(compressed_pair<empty_UDT, empty_POD_UDT>) < sizeof(std::pair<empty_UDT, empty_POD_UDT>)))
   value_test(true, (sizeof(compressed_pair<empty_UDT, compressed_pair<empty_POD_UDT, int> >) < sizeof(std::pair<empty_UDT, std::pair<empty_POD_UDT, int> >)))

   std::cout << std::endl << test_count << " tests completed (" << failures << " failures)... press any key to exit";
   std::cin.get();
   return failures;
}

//
// instanciate some compressed pairs:
template class boost::compressed_pair<int, double>;
template class boost::compressed_pair<int, int>;
template class boost::compressed_pair<empty_UDT, int>;
template class boost::compressed_pair<int, empty_UDT>;
template class boost::compressed_pair<empty_UDT, empty_UDT>;
template class boost::compressed_pair<empty_UDT, empty_POD_UDT>;

#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
//
// now some for which only a few specific members can be instantiated,
// first references:
template double& compressed_pair<double, int&>::first();
template int& compressed_pair<double, int&>::second();
template compressed_pair<double, int&>::compressed_pair(int&);
template compressed_pair<double, int&>::compressed_pair(call_traits<double>::param_type,int&);
//
// and then arrays:
#ifndef __BORLANDC__
template call_traits<int[2]>::reference compressed_pair<double, int[2]>::second();
#endif
template call_traits<double>::reference compressed_pair<double, int[2]>::first();
template compressed_pair<double, int[2]>::compressed_pair(const double&);
template compressed_pair<double, int[2]>::compressed_pair();
#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION




