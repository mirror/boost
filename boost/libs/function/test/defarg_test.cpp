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

using namespace std;
using namespace boost;

static int sub_ints(int x = 5, int y = 3, int z = 1) { return x-y-z; }

static void 
test_zero_args()
{
  function<int> one(&sub_ints);
  BOOST_TEST(one() == 1);
}

static void
test_one_arg()
{
  function<int, int> minus_four(&sub_ints);
  BOOST_TEST(minus_four(7) == 3);
}

static void
test_two_args()
{
  function<int, int, int> sub(&sub_ints);
  BOOST_TEST(sub(10, 2) == 7);
}

int
test_main(int, char* [])
{
  test_zero_args();
  test_one_arg();
  test_two_args();
  return 0;
}
