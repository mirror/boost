//
// bind_lookup_problem_test.cpp
//
// Copyright (C) Markus Schöpflin 2005.
//
// Use, modification, and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/bind.hpp>

template<class T> void value();

void foo() { }
void foo(int) { }
void foo(int, int) { }
void foo(int, int, int) { }
void foo(int, int, int, int) { }
void foo(int, int, int, int, int) { }
void foo(int, int, int, int, int, int) { }
void foo(int, int, int, int, int, int, int) { }
void foo(int, int, int, int, int, int, int, int) { }
void foo(int, int, int, int, int, int, int, int, int) { }

int main()
{
  boost::bind(foo);
  boost::bind(foo, 0);
  boost::bind(foo, 0, 0);
  boost::bind(foo, 0, 0, 0);
  boost::bind(foo, 0, 0, 0, 0);
  boost::bind(foo, 0, 0, 0, 0, 0);
  boost::bind(foo, 0, 0, 0, 0, 0, 0);
  boost::bind(foo, 0, 0, 0, 0, 0, 0, 0);
  boost::bind(foo, 0, 0, 0, 0, 0, 0, 0, 0);
  boost::bind(foo, 0, 0, 0, 0, 0, 0, 0, 0, 0);

  return 0;
}
