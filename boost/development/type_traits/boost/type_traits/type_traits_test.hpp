//  (C) Copyright John Maddock 2000. Permission to copy, use, modify, sell and   
//  distribute this software is granted provided this copyright notice appears   
//  in all copies. This software is provided "as is" without express or implied   
//  warranty, and with no claim as to its suitability for any purpose.   

//  common test code for type-traits tests
//  WARNING: contains code as well as declarations!


#ifndef BOOST_TYPE_TRAITS_TEST_HPP
#define BOOST_TYPE_TRAITS_TEST_HPP
#include <iostream>
#include <typeinfo>
//
// define tests here
unsigned failures = 0;
unsigned test_count = 0;
//
// This must get defined within the test file.
// All compilers have bugs, set this to the number of
// regressions *expected* from a given compiler,
// if there are no workarounds for the bugs, *and*
// the regressions have been investigated.
//
extern unsigned int expected_failures;
//
// proc check_result()
// Checks that there were no regressions:
//
int check_result(int argc, char** argv)
{
   std::cout << test_count << " tests completed, "
      << failures << " failures found, "
      << expected_failures << " failures expected from this compiler." << std::endl;
   if((argc == 2) 
   	&& (argv[1][0] == '-')
   	&& (argv[1][1] == 'a')
   	&& (argv[1][2] == 0))
   {
      std::cout << "Press any key to continue...";
      std::cin.get();
   }
   return (failures == expected_failures) ? 0 : failures;
}


//
// this one is to verify that a constant is indeed a
// constant-integral-expression:
//
template <bool>
struct checker
{
   static void check(bool, bool, const char*, bool){ ++test_count; }
};

template <>
struct checker<false>
{
   static void check(bool o, bool n, const char* name, bool soft)
   {
      ++test_count;
      ++failures;
      // if this is a soft test, then failure is expected,
      // or may depend upon factors outside our control
      // (like compiler options)...
      if(soft)++expected_failures;
      std::cout << "checking value of " << name << "...failed" << std::endl;
      std::cout << "\tfound: " << n << " expected " << o << std::endl;
   }
};

template <class T, class U>
struct type_checker
{
   static void check(const char* TT, const char* TU, const char* expression)
   {
      ++test_count;
#ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
      if((typeid(T) != typeid(U))
         || (::boost::is_reference<T>::value != ::boost::is_reference<U>::value)
         || (::boost::is_const<T>::value != ::boost::is_const<U>::value)
         || (::boost::is_volatile<T>::value != ::boost::is_volatile<U>::value))
      {
#endif
         ++failures;
         std::cout << "checking type of " << expression << "...failed" << std::endl;
         std::cout << "   expected type was " << TT << std::endl;
         std::cout << "   typeid(" << TT << ") was: " << typeid(T).name() << std::endl;
         std::cout << "   typeid(" << TU << ") was: " << typeid(U).name() << std::endl;
         std::cout << "   In template class " << typeid(type_checker<T,U>).name() << std::endl;
#ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
      }
#endif
   }
};

#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
template <class T>
struct type_checker<T,T>
{
   static void check(const char*, const char*, const char*)
   {
      ++test_count;
   }
};
#endif


#define value_test(v, x) checker<(v == x)>::check(v, x, #x, false);
#define soft_value_test(v, x) checker<(v == x)>::check(v, x, #x, true);

#define value_fail(v, x) \
      ++test_count; \
      ++failures; \
      std::cout << "checking value of " << #x << "...failed" << std::endl; \
      std::cout << "   " #x " does not compile on this compiler" << std::endl;


#define type_test(v, x) type_checker<v,x>::check(#v, #x, #x);
#define type_test3(v, x, z) type_checker<v,x,z>::check(#v, #x "," #z, #x "," #z);

template <class T>
struct test_align
{
   struct padded
   {
      char c;
      T t;
   };
   static void do_it()
   {
      padded p;
      unsigned a = reinterpret_cast<char*>(&(p.t)) - reinterpret_cast<char*>(&p);
      ++test_count;
      // only fail if we do not have a multiple of the actual value:
      if((a > ::boost::alignment_of<T>::value) || (a % ::boost::alignment_of<T>::value))
      {
         ++failures;
         std::cout << "checking value of " << typeid(boost::alignment_of<T>).name() << "...failed" << std::endl;
         std::cout << "\tfound: " << boost::alignment_of<T>::value << " expected " << a << std::endl;
      }
   }
};
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
template <class T>
struct test_align<T&>
{
   static void do_it()
   {
      //
      // we can't do the usual test because we can't take the address
      // of a reference, so check that the result is the same as for a
      // pointer type instead:
      unsigned a = boost::alignment_of<T*>::value;
      ++test_count;
      if(a != boost::alignment_of<T&>::value)
      {
         ++failures;
         std::cout << "checking value of " << typeid(boost::alignment_of<T&>).name() << "...failed" << std::endl;
         std::cout << "\tfound: " << boost::alignment_of<T&>::value << " expected " << a << std::endl;
      }
   }
};
#endif

#define align_test(T) test_align<T>::do_it()

//
// the following code allows us to test that a particular
// template functions correctly when instanciated inside another template
// (some bugs only show up in that situation).  For each template
// we declare one NESTED_DECL(classname) that sets up the template class
// and multiple NESTED_TEST(classname, template-arg) declarations, to carry
// the actual tests:
template <bool b>
struct nested_test
{
   typedef nested_test type;
   bool run_time_value;
   const char* what;
   nested_test(bool b2, const char* w) : run_time_value(b2), what(w) { check(); }
   void check()
   {
      ++test_count;
      if(b != run_time_value)
      {
         ++failures;
         std::cerr << "Mismatch between runtime and compile time values in " << what << std::endl;
      }
   }
};

#define NESTED_DECL(what)\
template <class T> \
struct BOOST_TT_JOIN(nested_tester_,what){\
   nested_test< (0 != ::boost::what<T>::value)> tester;\
   BOOST_TT_JOIN(nested_tester_,what)(const char* s) : tester(::boost::what<T>::value, s){}\
};
#define NESTED_TEST(what, with)\
{BOOST_TT_JOIN(nested_tester_,what)<with> check(#what "<" #with ">");}

#define BOOST_TT_JOIN( X, Y ) BOOST_DO_TT_JOIN( X, Y )
#define BOOST_DO_TT_JOIN( X, Y ) X##Y



//
// define some types to test with:
//
enum enum_UDT{ one, two, three };
struct UDT
{
   UDT();
   ~UDT();
   UDT(const UDT&);
   UDT& operator=(const UDT&);
   int i;

   void f1();
   int f2();
   int f3(int);
   int f4(int, float);
};

typedef void(*f1)();
typedef int(*f2)(int);
typedef int(*f3)(int, bool);
typedef void (UDT::*mf1)();
typedef int (UDT::*mf2)();
typedef int (UDT::*mf3)(int);
typedef int (UDT::*mf4)(int, float);
typedef int (UDT::*mp);

// cv-qualifiers applied to reference types should have no effect
// declare these here for later use with is_reference and remove_reference:
# ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable: 4181)
# endif // BOOST_MSVC
typedef int& r_type;
typedef const r_type cr_type;
# ifdef BOOST_MSVC
#  pragma warning(pop)
# endif // BOOST_MSVC

struct POD_UDT { int x; };
struct empty_UDT{ ~empty_UDT(){}; };
struct empty_POD_UDT{};
union union_UDT
{
  int x;
  double y;
  ~union_UDT();
};
union POD_union_UDT
{
  int x;
  double y;
};
union empty_union_UDT
{
  ~empty_union_UDT();
};
union empty_POD_union_UDT{};

class Base { };

class Deriverd : public Base { };

class NonDerived { };

enum enum1
{
   one_,two_
};

enum enum2
{
   three_,four_
};

struct VB
{
   virtual ~VB(){};
};

struct VD : VB
{
   ~VD(){};
};
//
// struct non_pointer:
// used to verify that is_pointer does not return
// true for class types that implement operator void*()
//
struct non_pointer
{
   operator void*(){return this;}
};
struct non_int_pointer
{
   int i;
   operator int*(){return &i;}
};
struct int_constructible
{
   int_constructible(int);
};
struct int_convertible
{
   operator int();
};
//
// struct non_empty:
// used to verify that is_empty does not emit
// spurious warnings or errors.
//
struct non_empty : boost::noncopyable
{
   int i;
};



#endif // BOOST_TYPE_TRAITS_TEST_HPP




