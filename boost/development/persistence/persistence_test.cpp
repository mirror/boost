/* boost persistence_test.cpp regression tests
 *
 * Copyright Jens Maurer 2000
 * Permission to use, copy, modify, sell, and distribute this software
 * is hereby granted without free provided that the above copyright notice
 * appears in all copies and that both that copyright notice and this
 * permission notice appear in supporting documentation,
 *
 * Jens Maurer makes no representations about the suitability of this
 * software for any purpose. It is provided "as is" without express or
 * implied warranty.
 *
 * $Id$
 *
 * Test persistent.hpp and related headers.
 */


#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <deque>
#include <functional>
#include <algorithm>
#include <string>
#include <cmath>          // std::fabs

#include "persistence.hpp"
#include "binary.hpp"
#include "text.hpp"
#include "xdr.hpp"

template<class Container, class Reader, class Writer, class Value>
void test_seq(Value v, const std::string & s)
{
  std::cout << s << std::endl;
  Container orig;
  {
    orig.push_back(v);
    v += 65;
    orig.push_back(v);
    // Note: remove "std::ios::trunc" for stock gcc 2.95.2
    std::ofstream file("test.dat", std::ios::trunc);
    Writer w(file);
    boost::save(w, orig);
  }

  {
    std::ifstream file("test.dat");
    Container k;
    Reader r(file);
    boost::load(r, k);

    if(orig.size() != k.size())
      std::cout << " size differs!\n";
    else if(!std::equal(orig.begin(), orig.end(), k.begin())) {
      std::cout << "difference: ";
      std::copy(orig.begin(), orig.end(), 
		std::ostream_iterator<Value>(std::cout, " "));
      std::cout << "--- ";
      std::copy(k.begin(), k.end(),
		std::ostream_iterator<Value>(std::cout, " "));
      std::cout << std::endl;
    }
  }

}

struct test_value
{
  int a;
  double b;
  test_value() { };
  test_value(int a, double b) : a(a), b(b) { }
  test_value& operator+=(int i) { a += i*2; b += i; return *this; }
  bool operator==(const test_value & rhs)
  { return a == rhs.a && std::fabs(b-rhs.b) < 1e-6; }
  bool operator!=(const test_value & rhs) { return !(*this == rhs); }

  template<class Desc>
  void describe(Desc & d) { d & a & b; }
};

std::ostream & operator<<(std::ostream & os, const test_value & v)
{
  os << v.a << " " << v.b;
  return os;
}

std::istream & operator>>(std::istream & is, test_value & v)
{
  is >> v.a >> std::ws >> v.b;
  return is;
}

template<class Reader, class Writer, class Value>
void runtest_linear(Value v, const std::string & name)
{
  test_seq<std::vector<Value>, Reader, Writer>(v, name + " vector");
  test_seq<std::list<Value>, Reader, Writer>(v, name + " list");
  test_seq<std::deque<Value>, Reader, Writer>(v, name + " deque");
}

template<class Reader, class Writer>
void runtest(const std::string & name)
{
  runtest_linear<Reader,Writer>(5, name + " int");
  runtest_linear<Reader,Writer>(1.3, name + " double");
  runtest_linear<Reader,Writer>(test_value(5,3.3), name + " test_value");
  runtest_linear<Reader,Writer>(std::string("hello"), name + " string");

  runtest_linear<Reader,Writer>(std::string("h\"el\n l\\o"),
				name + " string control characters");
}

int main()
{
  // operator<< and operator>>
  runtest<boost::text_reader, boost::text_writer>("text operators<<, >>");
  // binary I/O
  runtest<boost::binary_istream_reader, boost::binary_ostream_writer>("binary");
  // XDR I/O
  runtest<boost::xdr_reader, boost::xdr_writer>("XDR");
}
