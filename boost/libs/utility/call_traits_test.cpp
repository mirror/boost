 // boost::compressed_pair test program   
    
 //  (C) Copyright John Maddock 2000. Permission to copy, use, modify, sell and   
 //  distribute this software is granted provided this copyright notice appears   
 //  in all copies. This software is provided "as is" without express or implied   
 //  warranty, and with no claim as to its suitability for any purpose.   

// standalone test program for <boost/call_traits.hpp>

#include <cassert>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <typeinfo>
#include <boost/call_traits.hpp>

#include "type_traits_test.hpp"
//
// struct contained models a type that contains a type (for example std::pair)
// arrays are contained by value, and have to be treated as a special case:
//
template <class T>
struct contained
{
   // define our typedefs first, arrays are stored by value
   // so value_type is not the same as result_type:
   typedef typename boost::call_traits<T>::param_type       param_type;
   typedef typename boost::call_traits<T>::reference        reference;
   typedef typename boost::call_traits<T>::const_reference  const_reference;
   typedef T                                                value_type;
   typedef typename boost::call_traits<T>::value_type       result_type;

   // stored value:
   value_type v_;
   
   // constructors:
   contained() {}
   contained(param_type p) : v_(p){}
   // return byval:
   result_type value()const { return v_; }
   // return by_ref:
   reference get() { return v_; }
   const_reference const_get()const { return v_; }
   // pass value:
   void call(param_type p){}

};

#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
template <class T, std::size_t N>
struct contained<T[N]>
{
   typedef typename boost::call_traits<T[N]>::param_type       param_type;
   typedef typename boost::call_traits<T[N]>::reference        reference;
   typedef typename boost::call_traits<T[N]>::const_reference  const_reference;
   typedef T                                                   value_type[N];
   typedef typename boost::call_traits<T[N]>::value_type       result_type;

   value_type v_;

   contained(param_type p)
   {
      std::copy(p, p+N, v_);
   }
   // return byval:
   result_type value()const { return v_; }
   // return by_ref:
   reference get() { return v_; }
   const_reference const_get()const { return v_; }
   void call(param_type p){}
};
#endif

template <class T>
contained<typename boost::call_traits<T>::value_type> wrap(const T& t)
{
   typedef typename boost::call_traits<T>::value_type ct;
   return contained<ct>(t);
}

namespace test{

template <class T1, class T2>
std::pair<
   typename boost::call_traits<T1>::value_type,
   typename boost::call_traits<T2>::value_type>
      make_pair(const T1& t1, const T2& t2)
{
   return std::pair<
      typename boost::call_traits<T1>::value_type,
      typename boost::call_traits<T2>::value_type>(t1, t2);
}

} // namespace test

using namespace std;

//
// struct checker:
// verifies behaviour of contained example:
//
template <class T>
struct checker
{
   typedef typename boost::call_traits<T>::param_type param_type;
   void operator()(param_type);
};

template <class T>
void checker<T>::operator()(param_type p)
{
   T t(p);
   contained<T> c(t);
   cout << "checking contained<" << typeid(T).name() << ">..." << endl;
   assert(t == c.value());
   assert(t == c.get());
   assert(t == c.const_get());

   cout << "typeof contained<" << typeid(T).name() << ">::v_ is:           " << typeid(&contained<T>::v_).name() << endl;
   cout << "typeof contained<" << typeid(T).name() << ">::value() is:      " << typeid(&contained<T>::value).name() << endl;
   cout << "typeof contained<" << typeid(T).name() << ">::get() is:        " << typeid(&contained<T>::get).name() << endl;
   cout << "typeof contained<" << typeid(T).name() << ">::const_get() is:  " << typeid(&contained<T>::const_get).name() << endl;
   cout << "typeof contained<" << typeid(T).name() << ">::call() is:       " << typeid(&contained<T>::call).name() << endl;
   cout << endl;
}

#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
template <class T, std::size_t N>
struct checker<T[N]>
{
   typedef typename boost::call_traits<T[N]>::param_type param_type;
   void operator()(param_type t)
   {
      contained<T[N]> c(t);
      cout << "checking contained<" << typeid(T[N]).name() << ">..." << endl;
      unsigned int i = 0;
      for(i = 0; i < N; ++i)
         assert(t[i] == c.value()[i]);
      for(i = 0; i < N; ++i)
         assert(t[i] == c.get()[i]);
      for(i = 0; i < N; ++i)
         assert(t[i] == c.const_get()[i]);

      cout << "typeof contained<" << typeid(T[N]).name() << ">::v_ is:         " << typeid(&contained<T[N]>::v_).name() << endl;
      cout << "typeof contained<" << typeid(T[N]).name() << ">::value is:      " << typeid(&contained<T[N]>::value).name() << endl;
      cout << "typeof contained<" << typeid(T[N]).name() << ">::get is:        " << typeid(&contained<T[N]>::get).name() << endl;
      cout << "typeof contained<" << typeid(T[N]).name() << ">::const_get is:  " << typeid(&contained<T[N]>::const_get).name() << endl;
      cout << "typeof contained<" << typeid(T[N]).name() << ">::call is:       " << typeid(&contained<T[N]>::call).name() << endl;
      cout << endl;
   }
};
#endif

//
// check_wrap:
template <class T, class U>
void check_wrap(const contained<T>& w, const U& u)
{
   cout << "checking contained<" << typeid(T).name() << ">..." << endl;
   assert(w.value() == u);
}

//
// check_make_pair:
// verifies behaviour of "make_pair":
//
template <class T, class U, class V>
void check_make_pair(T c, U u, V v)
{
   cout << "checking std::pair<" << typeid(c.first).name() << ", " << typeid(c.second).name() << ">..." << endl;
   assert(c.first == u);
   assert(c.second == v);
   cout << endl;
}


struct UDT
{
   int i_;
   UDT() : i_(2){}
   bool operator == (const UDT& v){ return v.i_ == i_; }
};

int main()
{
   checker<UDT> c1;
   UDT u;
   c1(u);
   checker<int> c2;
   int i = 2;
   c2(i);
   int* pi = &i;
   checker<int*> c3;
   c3(pi);
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
   checker<int&> c4;
   c4(i);
   checker<const int&> c5;
   c5(i);

   int a[2] = {1,2};
   checker<int[2]> c6;
   c6(a);
#endif

   check_wrap(wrap(2), 2);
   const char ca[4] = "abc";
   // compiler can't deduce this for some reason:
   //check_wrap(wrap(ca), ca);
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
   check_wrap(wrap(a), a);
   check_make_pair(test::make_pair(a, a), a, a);
#endif

   // cv-qualifiers applied to reference types should have no effect
   // declare these here for later use with is_reference and remove_reference:
   typedef int& r_type;
   typedef const r_type cr_type;

   type_test(UDT, boost::call_traits<UDT>::value_type)
   type_test(UDT&, boost::call_traits<UDT>::reference)
   type_test(const UDT&, boost::call_traits<UDT>::const_reference)
   type_test(const UDT&, boost::call_traits<UDT>::param_type)
   type_test(int, boost::call_traits<int>::value_type)
   type_test(int&, boost::call_traits<int>::reference)
   type_test(const int&, boost::call_traits<int>::const_reference)
   type_test(const int, boost::call_traits<int>::param_type)
   type_test(int*, boost::call_traits<int*>::value_type)
   type_test(int*&, boost::call_traits<int*>::reference)
   type_test(int*const&, boost::call_traits<int*>::const_reference)
   type_test(int*const, boost::call_traits<int*>::param_type)
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
   type_test(int&, boost::call_traits<int&>::value_type)
   type_test(int&, boost::call_traits<int&>::reference)
   type_test(const int&, boost::call_traits<int&>::const_reference)
   type_test(int&, boost::call_traits<int&>::param_type)
#if !(defined(__GNUC__) && (__GNUC__ < 3))
   type_test(int&, boost::call_traits<cr_type>::value_type)
   type_test(int&, boost::call_traits<cr_type>::reference)
   type_test(const int&, boost::call_traits<cr_type>::const_reference)
   type_test(int&, boost::call_traits<cr_type>::param_type)
#else
   std::cout << "Your compiler cannot instantiate call_traits<int&const>, skipping four tests (4 errors)" << std::endl;
   failures += 4;
   test_count += 4;
#endif
   type_test(const int&, boost::call_traits<const int&>::value_type)
   type_test(const int&, boost::call_traits<const int&>::reference)
   type_test(const int&, boost::call_traits<const int&>::const_reference)
   type_test(const int&, boost::call_traits<const int&>::param_type)
   type_test(const int*, boost::call_traits<int[3]>::value_type)
   type_test(int(&)[3], boost::call_traits<int[3]>::reference)
   type_test(const int(&)[3], boost::call_traits<int[3]>::const_reference)
   type_test(const int*const, boost::call_traits<int[3]>::param_type)
   type_test(const int*, boost::call_traits<const int[3]>::value_type)
   type_test(const int(&)[3], boost::call_traits<const int[3]>::reference)
   type_test(const int(&)[3], boost::call_traits<const int[3]>::const_reference)
   type_test(const int*const, boost::call_traits<const int[3]>::param_type)
#else
   std::cout << "You're compiler does not support partial template instantiation, skipping 20 tests (20 errors)" << std::endl;
   failures += 20;
   test_count += 20;
#endif

   std::cout << std::endl << test_count << " tests completed (" << failures << " failures)... press any key to exit";
   std::cin.get();
   return failures;
}

//
// define call_traits tests to check that the assertions in the docs do actually work
// this is an instantiate only set of tests:
//
template <typename T, bool isarray = false>
struct call_traits_test
{
   typedef ::boost::call_traits<T> ct;
   typedef typename ct::param_type param_type;
   typedef typename ct::reference reference;
   typedef typename ct::const_reference const_reference;
   typedef typename ct::value_type value_type;
   static void assert_construct(param_type val);
};

template <typename T, bool isarray>
void call_traits_test<T, isarray>::assert_construct(typename call_traits_test<T, isarray>::param_type val)
{
   //
   // this is to check that the call_traits assertions are valid:
   T t(val);
   value_type v(t);
   reference r(t);
   const_reference cr(t);
   param_type p(t);
   value_type v2(v);
   value_type v3(r);
   value_type v4(p);
   reference r2(v);
   reference r3(r);
   const_reference cr2(v);
   const_reference cr3(r);
   const_reference cr4(cr);
   const_reference cr5(p);
   param_type p2(v);
   param_type p3(r);
   param_type p4(p);
}
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
template <typename T>
struct call_traits_test<T, true>
{
   typedef ::boost::call_traits<T> ct;
   typedef typename ct::param_type param_type;
   typedef typename ct::reference reference;
   typedef typename ct::const_reference const_reference;
   typedef typename ct::value_type value_type;
   static void assert_construct(param_type val);
};

template <typename T>
void call_traits_test<T, true>::assert_construct(boost::call_traits<T>::param_type val)
{
   //
   // this is to check that the call_traits assertions are valid:
   T t;
   value_type v(t);
   value_type v5(val);
   reference r = t;
   const_reference cr = t;
   reference r2 = r;
   #ifndef __BORLANDC__
   // C++ Builder buglet:
   const_reference cr2 = r;
   #endif
   param_type p(t);
   value_type v2(v);
   const_reference cr3 = cr;
   value_type v3(r);
   value_type v4(p);
   param_type p2(v);
   param_type p3(r);
   param_type p4(p);
}
#endif //BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
//
// now check call_traits assertions by instantiating call_traits_test:
template struct call_traits_test<int>;
template struct call_traits_test<const int>;
template struct call_traits_test<int*>;
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
template struct call_traits_test<int&>;
template struct call_traits_test<const int&>;
template struct call_traits_test<int[2], true>;
#endif

