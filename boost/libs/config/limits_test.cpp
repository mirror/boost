/* boost limits_test.cpp   test your <limits> file for important
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
 */

#include <boost/limits.hpp>
#include <math.h>
#include <cassert>
#include <iostream>

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
void test_integral_limits(const T &, const char * msg)
{
  std::cout << "Testing " << msg << " (size " << sizeof(T) << ")" << std::endl;
  typedef std::numeric_limits<T> lim;

  assert(lim::is_specialized);
  assert(lim::is_integer);
  // assert(lim::is_modulo);

  std::cout << "min: " << lim::min() << ", max: " << lim::max() << '\n';
}

template <class T>
void print_hex_val(T t, const char* name)
{
	const unsigned char* p = (const unsigned char*)&t;
	std::cout << "hex value of " << name << " is: ";
	for (int i = 0; i < sizeof(T); ++i)
	{
		if(p[i] <= 0xF)
			std::cout << "0";
		std:: cout << std::hex << (int)p[i];
	}
	std::cout << endl;
}

template<class T>
void test_float_limits(const T &, const char * msg)
{
  std::cout << "Testing " << msg << std::endl;
  typedef std::numeric_limits<T> lim;

  assert(lim::is_specialized);
  assert(!lim::is_modulo);
  assert(!lim::is_integer);
  assert(lim::is_signed);
  
  assert(lim::epsilon() > 0);

  assert(lim::has_infinity);
  assert(lim::has_quiet_NaN);
  assert(lim::has_signaling_NaN);
  
  const T infinity = lim::infinity();
  const T qnan = lim::quiet_NaN();
  const T snan = lim::signaling_NaN();
  (void) snan;

  // make sure those values are not 0 or similar nonsense

  std::cout << "IEEE-compatible: " << lim::is_iec559
	    << ", traps: " << lim::traps
	    << ", bounded: " << lim::is_bounded
	    << ", exact: " << lim::is_exact << '\n'
	    << "min: " << lim::min() << ", max: " << lim::max() << '\n'
	    << "infinity: " << infinity << ", QNaN: " << qnan << '\n';
	print_hex_val(lim::max(), "max");
	print_hex_val(infinity, "infinity");
	print_hex_val(qnan, "qnan");
	print_hex_val(snan, "snan");
  // infinity is beyond the representable range
  assert(lim::max() > 1000);
  assert(lim::infinity() > lim::max());
  assert(-lim::infinity() < -lim::max());
  assert(lim::min() < 0.001);
  assert(lim::min() > 0);

  // NaNs shall always compare "false"
  // If one of these fail, your compiler may be optimizing incorrectly
  assert(! (qnan < 42));
  assert(! (qnan > 42));
  assert(! (qnan <= 42));
  assert(! (qnan >= 42));
  assert(! (qnan == qnan));
}


int main()
{
  test_integral_limits(bool(), "bool");
  test_integral_limits(char(), "char");
  typedef signed char signed_char;
  test_integral_limits(signed_char(), "signed char");
  typedef unsigned char unsigned_char;
  test_integral_limits(unsigned_char(), "unsigned char");
  test_integral_limits(wchar_t(), "wchar_t");
  test_integral_limits(short(), "short");
  typedef unsigned short unsigned_short;
  test_integral_limits(unsigned_short(), "unsigned short");
  test_integral_limits(int(), "int");
  typedef unsigned int unsigned_int;
  test_integral_limits(unsigned_int(), "unsigned int");
  test_integral_limits(long(), "long");
  typedef unsigned long unsigned_long;
  test_integral_limits(unsigned_long(), "unsigned long");
#ifdef __GNUC__
  typedef long long long_long;
  test_integral_limits(long_long(), "long long");
  typedef unsigned long long unsigned_long_long;
  test_integral_limits(unsigned_long_long(), "unsigned long long");
#endif

  test_float_limits(float(), "float");
  test_float_limits(double(), "double");
  typedef long double long_double;
  test_float_limits(long_double(), "long double");
  // Some compilers don't pay attention to std:3.6.1/5 and issue a
  // warning here if "return 0;" is omitted.
  return 0;
}

