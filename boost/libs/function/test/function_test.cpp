// Boost.Function library

// Copyright (C) 2001 Doug Gregor (gregod@cs.rpi.edu)
//
// Permission to copy, use, sell and distribute this software is granted
// provided this copyright notice appears in all copies.
// Permission to modify the code and to distribute modified code is granted
// provided this copyright notice appears in all copies, and a notice
// that the code was modified is included with the copyright notice.
//
// This software is provided "as is" without express or implied warranty,
// and with no claim as to its suitability for any purpose.

// For more information, see http://www.boost.org

#define BOOST_INCLUDE_MAIN
#include <boost/test/test_tools.hpp>
#include <boost/function.hpp>
#include <functional>
#include <cassert>
#include <string>

using namespace boost;
using std::string;
using std::negate;

static int global_int;

struct write_five_obj { void operator()() const { global_int = 5; } };
struct write_three_obj { int operator()() const { global_int = 3; return 7; }};
static void write_five() { global_int = 5; }
static void write_three() { global_int = 3; }
struct generate_five_obj { int operator()() const { return 5; } };
struct generate_three_obj { int operator()() const { return 3; } };
static int generate_five() { return 5; }
static int generate_three() { return 3; }
static string identity_str(const string& s) { return s; }
static string string_cat(const string& s1, const string& s2) { return s1+s2; }
static int sum_ints(int x, int y) { return x+y; }

struct write_const_1_nonconst_2
{
  void operator()() { global_int = 2; }
  void operator()() const { global_int = 1; }
};

static void
test_zero_args()
{
  typedef function<void> func_void_type;

  write_five_obj five;
  write_three_obj three;

  // Default construction
  func_void_type v1;
  BOOST_TEST(v1.empty());

  // Assignment to an empty function 
  v1 = five;
  BOOST_TEST(!v1.empty());

  // Invocation of a function
  global_int = 0;
  v1();
  BOOST_TEST(global_int == 5);

  // clear() method
  v1.clear();
  BOOST_TEST(v1.empty());

  // Assignment to an empty function
  v1 = three;
  BOOST_TEST(!v1.empty());

  // Invocation and self-assignment
  global_int = 0;
  v1 = v1;
  v1();
  BOOST_TEST(global_int == 3);

  // Assignment to a non-empty function
  v1 = five;

  // Invocation and self-assignment
  global_int = 0;
  v1.set(v1);
  v1();
  BOOST_TEST(global_int == 5);

  // clear()
  v1.clear();
  BOOST_TEST(v1.empty());

  // Assignment to an empty function from a free function
  v1 = &write_five;
  BOOST_TEST(!v1.empty());

  // Invocation
  global_int = 0;
  v1();
  BOOST_TEST(global_int == 5);

  // Assignment to a non-empty function from a free function
  v1 = &write_three;
  BOOST_TEST(!v1.empty());

  // Invocation
  global_int = 0;
  v1();
  BOOST_TEST(global_int == 3);

  // Assignment
  v1 = five;
  BOOST_TEST(!v1.empty());

  // Invocation
  global_int = 0;
  v1();
  BOOST_TEST(global_int == 5);

  // Assignment to a non-empty function from a free function
  v1 = &write_three;
  BOOST_TEST(!v1.empty());

  // Invocation
  global_int = 0;
  v1();
  BOOST_TEST(global_int == 3);

  // Construction from another function (that is empty)
  v1.clear();
  func_void_type v2(v1);
  BOOST_TEST(!v2);

  // Assignment to an empty function
  v2 = three;
  BOOST_TEST(!v2.empty());

  // Invocation
  global_int = 0;
  v2();
  BOOST_TEST(global_int == 3);

  // Assignment to a non-empty function
  v2.set(five);

  // Invocation
  global_int = 0;
  v2();
  BOOST_TEST(global_int == 5);

  v2.clear();
  BOOST_TEST(v2.empty());

  // Assignment to an empty function from a free function
  v2.set(&write_five);
  BOOST_TEST(v2);

  // Invocation
  global_int = 0;
  v2();
  BOOST_TEST(global_int == 5);

  // Assignment to a non-empty function from a free function
  v2 = &write_three;
  BOOST_TEST(!v2.empty());

  // Invocation
  global_int = 0;
  v2();
  BOOST_TEST(global_int == 3);

  // Swapping
  v1 = five;
  swap(v1, v2);
  v2();
  BOOST_TEST(global_int == 5);
  v1();
  BOOST_TEST(global_int == 3);
  swap(v1, v2);
  v1.clear();

  // Assignment
  v2 = five;
  BOOST_TEST(!v2.empty());

  // Invocation
  global_int = 0;
  v2();
  BOOST_TEST(global_int == 5);

  // Assignment to a non-empty function from a free function
  v2 = &write_three;
  BOOST_TEST(!v2.empty());

  // Invocation
  global_int = 0;
  v2();
  BOOST_TEST(global_int == 3);

  // Assignment to a function from an empty function
  v2 = v1;
  BOOST_TEST(v2.empty()); 
  
  // Assignment to a function from a function with a functor
  v1 = three;
  v2 = v1;
  BOOST_TEST(!v1.empty());
  BOOST_TEST(!v2.empty());

  // Invocation
  global_int = 0;
  v1();
  BOOST_TEST(global_int == 3);
  global_int = 0;
  v2();
  BOOST_TEST(global_int == 3);

  // Assign to a function from a function with a function
  v2 = &write_five;
  v1 = v2;
  BOOST_TEST(!v1.empty());
  BOOST_TEST(!v2.empty());
  global_int = 0;
  v1();
  BOOST_TEST(global_int == 5);
  global_int = 0;
  v2();
  BOOST_TEST(global_int == 5);

  // Construct a function given another function containing a function
  func_void_type v3(v1);

  // Invocation of a function
  global_int = 0;
  v3();
  BOOST_TEST(global_int == 5);
  
  // clear() method
  v3.clear();
  BOOST_TEST(!v3);

  // Assignment to an empty function
  v3 = three;
  BOOST_TEST(!v3.empty());

  // Invocation
  global_int = 0;
  v3();
  BOOST_TEST(global_int == 3);

  // Assignment to a non-empty function
  v3 = five;

  // Invocation
  global_int = 0;
  v3();
  BOOST_TEST(global_int == 5);

  // clear()
  v3.clear();
  BOOST_TEST(v3.empty());

  // Assignment to an empty function from a free function
  v3 = &write_five;
  BOOST_TEST(!v3.empty());

  // Invocation
  global_int = 0;
  v3();
  BOOST_TEST(global_int == 5);

  // Assignment to a non-empty function from a free function
  v3 = &write_three;
  BOOST_TEST(!v3.empty());

  // Invocation
  global_int = 0;
  v3();
  BOOST_TEST(global_int == 3);

  // Assignment
  v3 = five;
  BOOST_TEST(!v3.empty());

  // Invocation
  global_int = 0;
  v3();
  BOOST_TEST(global_int == 5);

  // Construction of a function from a function containing a functor
  func_void_type v4(v3);

  // Invocation of a function
  global_int = 0;
  v4();
  BOOST_TEST(global_int == 5);
  
  // clear() method
  v4.clear();
  BOOST_TEST(v4.empty());

  // Assignment to an empty function
  v4 = three;
  BOOST_TEST(!v4.empty());

  // Invocation
  global_int = 0;
  v4();
  BOOST_TEST(global_int == 3);

  // Assignment to a non-empty function
  v4 = five;

  // Invocation
  global_int = 0;
  v4();
  BOOST_TEST(global_int == 5);

  // clear()
  v4.clear();
  BOOST_TEST(v4.empty());

  // Assignment to an empty function from a free function
  v4 = &write_five;
  BOOST_TEST(!v4.empty());

  // Invocation
  global_int = 0;
  v4();
  BOOST_TEST(global_int == 5);

  // Assignment to a non-empty function from a free function
  v4 = &write_three;
  BOOST_TEST(!v4.empty());

  // Invocation
  global_int = 0;
  v4();
  BOOST_TEST(global_int == 3);

  // Assignment
  v4 = five;
  BOOST_TEST(!v4.empty());

  // Invocation
  global_int = 0;
  v4();
  BOOST_TEST(global_int == 5);

  // Construction of a function from a functor
  func_void_type v5(five);

  // Invocation of a function
  global_int = 0;
  v5();
  BOOST_TEST(global_int == 5);
  
  // clear() method
  v5.clear();
  BOOST_TEST(v5.empty());

  // Assignment to an empty function
  v5 = three;
  BOOST_TEST(!v5.empty());

  // Invocation
  global_int = 0;
  v5();
  BOOST_TEST(global_int == 3);

  // Assignment to a non-empty function
  v5 = five;

  // Invocation
  global_int = 0;
  v5();
  BOOST_TEST(global_int == 5);

  // clear()
  v5.clear();
  BOOST_TEST(v5.empty());

  // Assignment to an empty function from a free function
  v5 = &write_five;
  BOOST_TEST(!v5.empty());

  // Invocation
  global_int = 0;
  v5();
  BOOST_TEST(global_int == 5);

  // Assignment to a non-empty function from a free function
  v5 = &write_three;
  BOOST_TEST(!v5.empty());

  // Invocation
  global_int = 0;
  v5();
  BOOST_TEST(global_int == 3);

  // Assignment
  v5 = five;
  BOOST_TEST(!v5.empty());

  // Invocation
  global_int = 0;
  v5();
  BOOST_TEST(global_int == 5);  

  // Construction of a function from a function
  func_void_type v6(&write_five);

  // Invocation of a function
  global_int = 0;
  v6();
  BOOST_TEST(global_int == 5);

  // clear() method
  v6.clear();
  BOOST_TEST(v6.empty());

  // Assignment to an empty function
  v6 = three;
  BOOST_TEST(!v6.empty());

  // Invocation
  global_int = 0;
  v6();
  BOOST_TEST(global_int == 3);

  // Assignment to a non-empty function
  v6 = five;

  // Invocation
  global_int = 0;
  v6();
  BOOST_TEST(global_int == 5);

  // clear()
  v6.clear();
  BOOST_TEST(v6.empty());

  // Assignment to an empty function from a free function
  v6 = &write_five;
  BOOST_TEST(!v6.empty());

  // Invocation
  global_int = 0;
  v6();
  BOOST_TEST(global_int == 5);

  // Assignment to a non-empty function from a free function
  v6 = &write_three;
  BOOST_TEST(!v6.empty());

  // Invocation
  global_int = 0;
  v6();
  BOOST_TEST(global_int == 3);

  // Assignment
  v6 = five;
  BOOST_TEST(!v6.empty());

  // Invocation
  global_int = 0;
  v6();
  BOOST_TEST(global_int == 5);  

  // Const vs. non-const
  write_const_1_nonconst_2 one_or_two;
  const function<void> v7(one_or_two);
  function <void> v8(one_or_two);

  global_int = 0;
  v7();
  BOOST_TEST(global_int == 1);
  
  global_int = 0;
  v8();
  BOOST_TEST(global_int == 2);

  // Test return values
  typedef function<int> func_int_type;
  generate_five_obj gen_five;
  generate_three_obj gen_three;

  func_int_type i0(gen_five);

  BOOST_TEST(i0() == 5);
  i0 = gen_three;
  BOOST_TEST(i0() == 3);
  i0 = &generate_five;
  BOOST_TEST(i0() == 5);
  i0 = &generate_three;
  BOOST_TEST(i0() == 3);
  BOOST_TEST(i0);
  i0.clear();
  BOOST_TEST(!i0);

  // Test return values with compatible types
  typedef function<long> func_long_type;
  func_long_type i1(gen_five);

  BOOST_TEST(i1() == 5);
  i1 = gen_three;
  BOOST_TEST(i1() == 3);
  i1 = &generate_five;
  BOOST_TEST(i1() == 5);
  i1 = &generate_three;
  BOOST_TEST(i1() == 3);
  BOOST_TEST(i1);
  i1.clear();
  BOOST_TEST(!i1);
}

static void
test_one_arg()
{
  negate<int> neg;

  function<int, int> f1(neg);
  BOOST_TEST(f1(5) == -5);

  function<string, string> id(&identity_str);
  BOOST_TEST(id("str") == "str");

  function<std::string, char*> id2(&identity_str);
  BOOST_TEST(id2("foo") == "foo");
}

static void
test_two_args()
{
  function<string, const string&, const string&> cat(&string_cat);
  BOOST_TEST(cat("str", "ing") == "string");  

  function<int, short, short> sum(&sum_ints);
  BOOST_TEST(sum(2, 3) == 5);
}

static void
test_emptiness()
{
  function<float> f1;
  BOOST_TEST(f1.empty());

  function<float> f2;
  f2 = f1;
  BOOST_TEST(f2.empty());

  function<double> f3;
  f3 = f2;
  BOOST_TEST(f3.empty());
}

int
test_main(int, char* [])
{
  test_zero_args();
  test_one_arg();
  test_two_args();
  test_emptiness();
  return 0;
}
