//  tuple_test_bench.cpp  --------------------------------

// Defining any of E1 to E5 or E7 to E11 opens some illegal code that 
// should cause the compliation to fail.

#define BOOST_INCLUDE_MAIN  // for testing, include rather than link
#include <boost/test/test_tools.hpp>    // see "Header Implementation Option"

#include "boost/tuple/tuple.hpp"

#include "boost/tuple/tuple_comparison.hpp"

#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>

using namespace std;
using namespace boost;



template<class T> void dummy(const T&) {}

class A {}; class B {}; class C {};

typedef int(t)(float);

// some arbitrary tuple definitions
typedef tuple<int> t1;
#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
typedef tuple<double&, const double&, const double, double*, const double*> t2;
typedef tuple<A, int(*)(char, int), C> t3;
typedef tuple<std::string, std::pair<A, B> > t4;
typedef tuple<A*, tuple<const A*, const B&, C>, bool, void*> t5;
typedef tuple<volatile int, const volatile char&, int(&)(float) > t6;

# if !defined(__BORLANDC__) || __BORLAND__ > 0x0551
typedef tuple<B(A::*)(C&), A&> t7;
#endif

#endif

// A non-copyable class
class no_copy {
  no_copy(const no_copy&) {}
public:
  no_copy() {};
};

no_copy y;

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
tuple<no_copy&> x = tuple<no_copy&>(y); // ok
#endif
#ifdef E1
tuple<no_copy> v1;  // should faild
#endif

char cs[10];
#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
tuple<char(&)[10]> v2(cs);  // ok
#endif
#ifdef E2
tuple<char[10]> v3;  // should fail, arrays must be stored as references
#endif


// -tuple construction tests ------------------------------------

// a class without a public default constructor
class no_def_constructor {
  no_def_constructor() {}
public:
  no_def_constructor(std::string) {} // can be constructed with a string
  };


void foo1() {

#ifdef E3
  dummy(tuple<no_def_constructor, no_def_constructor, no_def_constructor>()); 
  // should fail

#endif
  dummy( tuple<no_def_constructor, no_def_constructor, no_def_constructor>(
                      std::string("Jaba"),   // ok, since the default 
                      std::string("Daba"),   // constructor is not used
                      std::string("Doo")));
}

void foo2() {
// testing default values
  dummy(tuple<int, double>());
  dummy(tuple<int, double>(1));
  dummy(tuple<int, double>(1,3.14)); 

#ifdef E4
  dummy(tuple<double&>()); // should fail, not defaults for references
  dummy(tuple<const double&>()); // likewise
#endif

  double dd = 5;
#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
  dummy(tuple<double&>(dd)); // ok
#endif

#ifdef E5
  dummy(tuple<double&>(dd+3.14)); // should fail, temporary to non-const reference
#endif
#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
  dummy(tuple<const double&>(dd+3.14)); // ok, but potentially dangerous
#endif
}



// make_tuple ------------------------------------------


   void foo3() {
#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
    A a; B b;
    const A ca = a;
    make_tuple(cref(a), b);
    make_tuple(ref(a), b);
    make_tuple(ref(a), cref(b));

    make_tuple(ref(ca));
#endif
     

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
    make_tuple("Donald", "Daisy"); // should work;
#endif
#ifdef E7
    std::make_pair("Doesn't","Work"); // fails
#endif
// You can store a reference to a function in a tuple
#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
    tuple<void(&)()> adf(foo3);

    dummy(adf); // avoid warning for unused variable
#endif
 
// But make_tuple doesn't work 
// with function references, since it creates a const qualified function type

//   make_tuple(foo3);
  
// With function pointers, make_tuple works just fine

#if !defined(__BORLANDC__) || __BORLAND__ > 0x0551
   make_tuple(&foo3);
#endif
      


      
// NOTE:
//
// wrapping it the function reference with ref helps on gcc 2.95.2.
// on edg 2.43. it results in a catastrophic error?

// make_tuple(ref(foo3));

// It seems that edg can't use implicitly the ref's conversion operator, e.g.:
// typedef void (&foo3type) (void);
// foo3type foo3ref = static_cast<foo3type>(ref(foo3)); // works fine 
// foo3type foo3ref = ref(foo3);                        // error

// This is probably not a very common situation, so currently
// I don't know how which compiler is right (JJ)
      
}



// - testing element access

void foo4() 
{
#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
  double d = 2.7; 
  A a;
  tuple<int, double&, const A&> t(1, d, a);
  const tuple<int, double&, const A> ct = t;

  int i = get<0>(t);
  int j = get<0>(ct);
  BOOST_TEST(i == 1 && j == 1);
   
  get<0>(t) = 5;
  BOOST_TEST(t.head == 5);
   
#ifdef E8
  get<0>(ct) = 5; // can't assign to const
#endif

  double e = get<1>(t);
  BOOST_TEST(e > 2.69 && e < 2.71);
	     
  get<1>(t) = 3.14+i;
  BOOST_TEST(get<1>(t) > 4.13 && get<1>(t) < 4.15);

#ifdef E9
  get<4>(t) = A(); // can't assign to const
#endif
#ifdef E10
  dummy(get<5>(ct)); // illegal index
#endif

  ++get<0>(t);
  BOOST_TEST(get<0>(t) == 6);

  dummy(i); dummy(j); dummy(e); // avoid warns for unused variables
#endif
}

// testing copy and assignment with implicit conversions between elements
// testing tie

  class AA {};
  class BB : public AA {};
  struct CC { CC() {} CC(const BB& b) {} };
  struct DD { operator CC() const { return CC(); }; };

  void foo5() {
    tuple<char, BB*, BB, DD> t;
    tuple<int, AA*, CC, CC> a(t);
    a = t;
  }

  void foo6() {
    int i; char c; double d;
    tie(i, c, d) = make_tuple(1, 'a', 5.5);
    BOOST_TEST(i==1);
    BOOST_TEST(c=='a');
    BOOST_TEST(d==5.5);
  }

// testing tie
// testing assignment from std::pair
void foo7() {
#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
   int i, j; 
   tie (i, j) = std::make_pair(1, 2);
   BOOST_TEST(i == 1 && j == 2);
#endif
   tuple<int, int, float> a;
#ifdef E11
   a = std::make_pair(1, 2); // should fail, tuple is of length 3, not 2
#endif

// the result of make_tuple is assignable:
   BOOST_TEST(make_tuple(2, 4, 6) == 
	     (make_tuple(1, 2, 3) = make_tuple(2, 4, 6)));
  
    dummy(a);
}

// Testing cons lists
void foo8()
{
  cons<volatile float, null_type> a(1, null_type());
  cons<const int, cons<volatile float, null_type> > b(2,a);
  int i = 3;
  cons<int&, cons<const int, cons<volatile float, null_type> > > c(i, b);
  BOOST_TEST(make_tuple(3,2,1)==c);
}


// --------------------------------
// ----------------------------
int test_main(int, char *[]) {

  foo1();
  foo2();
  foo3();
  foo4();
  foo5();
  foo6();
  foo7();
  foo8();

  return 0;
}
