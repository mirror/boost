/* boost integer_traits.hpp tests
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
 * Revision history
 *  2000-02-22  Small improvements by Beman Dawes
 *  2000-06-27  Rework for better MSVC and BCC co-operation
 */

#include <iostream>
#include <cassert>
#include <boost/integer_traits.hpp>
// use int64_t instead of long long for better portability
#include <boost/cstdint.hpp>

#ifdef NDEBUG
#error This test relies on assert() and thus makes no sense with NDEBUG defined
#endif


/*
 * General portability note:
 * MSVC mis-compiles explicit function template instantiations.
 * For example, f<A>() and f<B>() are both compiled to call f<A>().
 * BCC is unable to implicitly convert a "const char *" to a std::string
 * when using explicit function template instantiations.
 *
 * Therefore, avoid explicit function template instantiations.
 */

template<class T>
void runtest(const char * type, T)
{
  typedef boost::integer_traits<T> traits;
  std::cout << "Checking " << type
	    << "; min is " << traits::min()
            << ", max is " << traits::max()
	    << std::endl;
  assert(traits::is_specialized);
  assert(traits::is_integer);
  assert(traits::is_integral);
  assert(traits::const_min == traits::min());
  assert(traits::const_max == traits::max());
}

int main()
{
  runtest("bool", bool());
  runtest("char", char());
  typedef signed char signed_char;
  runtest("signed char", signed_char());
  typedef unsigned char unsigned_char;
  runtest("unsigned char", unsigned_char());
  runtest("short", short());
  typedef unsigned short unsigned_short;
  runtest("unsigned short", unsigned_short());
  runtest("int", int());
  typedef unsigned int unsigned_int;
  runtest("unsigned int", unsigned_int());
  runtest("long", long());
  typedef unsigned long unsigned_long;
  runtest("unsigned long", unsigned_long());
#if !defined(BOOST_NO_INT64_T) && !defined(BOOST_MSVC) && !defined(__BORLANDC__) && !defined(__BEOS__)
  //
  // MS/Borland compilers can't support 64-bit member constants
  // BeOS doesn't have specialisations for long long in SGI's <limits> header.
  runtest("int64_t (possibly long long)", boost::int64_t());
  runtest("uint64_t (possibly unsigned long long)", boost::uint64_t());
#endif
  // Some compilers don't pay attention to std:3.6.1/5 and issue a
  // warning here if "return 0;" is omitted.
  return 0;
}

