 // boost::compressed_pair test program   
    
 //  (C) Copyright John Maddock 2000. Permission to copy, use, modify, sell and   
 //  distribute this software is granted provided this copyright notice appears   
 //  in all copies. This software is provided "as is" without express or implied   
 //  warranty, and with no claim as to its suitability for any purpose.   

// standalone test program for <boost/compressed_pair.hpp>
// Revised 03 Oct 2000: 
//    Enabled tests for VC6.

#include <iostream>
#include <typeinfo>
#include <cassert>

#include <boost/compressed_pair.hpp>
#include "type_traits_test.hpp"

using namespace boost;

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

struct non_empty1
{ 
   int i;
   non_empty1() : i(1){}
   non_empty1(int v) : i(v){}
   friend bool operator==(const non_empty1& a, const non_empty1& b)
   { return a.i == b.i; }
};

struct non_empty2
{ 
   int i;
   non_empty2() : i(3){}
   non_empty2(int v) : i(v){}
   friend bool operator==(const non_empty2& a, const non_empty2& b)
   { return a.i == b.i; }
};

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
   compressed_pair<non_empty1, non_empty2> cp1c(non_empty1(9));
   assert(cp1c.second() == non_empty2());
   assert(cp1c.first() == non_empty1(9));
   compressed_pair<non_empty1, non_empty2> cp1d(non_empty2(9));
   assert(cp1d.second() == non_empty2(9));
   assert(cp1d.first() == non_empty1());
   compressed_pair<empty_UDT, int> cp2(2);
   assert(cp2.second() == 2);
   compressed_pair<int, empty_UDT> cp3(1);
   assert(cp3.first() ==1);
   compressed_pair<empty_UDT, empty_UDT> cp4;
   compressed_pair<empty_UDT, empty_POD_UDT> cp5;
   compressed_pair<int, empty_UDT> cp9(empty_UDT());
   compressed_pair<int, empty_UDT> cp10(1);
   assert(cp10.first() == 1);
#if defined(BOOST_MSVC6_MEMBER_TEMPLATES) || !defined(BOOST_NO_MEMBER_TEMPLATES) || !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
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
#ifdef __MWERKS__
template class compressed_pair<int, double>;
template class compressed_pair<int, int>;
template class compressed_pair<empty_UDT, int>;
template class compressed_pair<int, empty_UDT>;
template class compressed_pair<empty_UDT, empty_UDT>;
template class compressed_pair<empty_UDT, empty_POD_UDT>;
#else
template class boost::compressed_pair<int, double>;
template class boost::compressed_pair<int, int>;
template class boost::compressed_pair<empty_UDT, int>;
template class boost::compressed_pair<int, empty_UDT>;
template class boost::compressed_pair<empty_UDT, empty_UDT>;
template class boost::compressed_pair<empty_UDT, empty_POD_UDT>;
#endif

#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#ifndef __MWERKS__
//
// now some for which only a few specific members can be instantiated,
// first references:
template double& compressed_pair<double, int&>::first();
template int& compressed_pair<double, int&>::second();
#if !(defined(__GNUC__) && (__GNUC__ == 2) && (__GNUC_MINOR__ < 95))
template compressed_pair<double, int&>::compressed_pair(int&);
#endif
template compressed_pair<double, int&>::compressed_pair(call_traits<double>::param_type,int&);
//
// and then arrays:
#ifndef __BORLANDC__
template call_traits<int[2]>::reference compressed_pair<double, int[2]>::second();
#endif
template call_traits<double>::reference compressed_pair<double, int[2]>::first();
#if !(defined(__GNUC__) && (__GNUC__ == 2) && (__GNUC_MINOR__ < 95))
template compressed_pair<double, int[2]>::compressed_pair(call_traits<double>::param_type);
#endif
template compressed_pair<double, int[2]>::compressed_pair();
#endif // __MWERKS__
#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION




