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
#include <cassert>
#include <functional>
#include <boost/function.hpp>

struct id_mixin
{       
  id_mixin(const id_mixin& rhs) : id(rhs.id) {}
  id_mixin& operator=(const id_mixin& rhs){id = rhs.id; return *this;}
  id_mixin(int i = 0){ id = i;}
  int id;
};

static int do_plus(int x, int y) { return x+y; }

typedef boost::function<int,int,int>::mixin<id_mixin>::type func;

int test_main(int, char*[])
{
  func f(id_mixin(3));  
  f = std::plus<int>();
  BOOST_TEST(f.id == 3);
  
  f = &do_plus;
  BOOST_TEST(f.id == 3);

  f.clear();
  f.id = 7;    
  BOOST_TEST(f.id == 7);
    
  func g(f);
  BOOST_TEST(g.id == 7);

  f.id = 21;    
  BOOST_TEST(f.id == 21);
          
  boost::swap(f,g);  
  BOOST_TEST(f.id == 7);
  BOOST_TEST(g.id == 21);

  g = f;          
  BOOST_TEST(g.id == 7);  
  return 0;
}
