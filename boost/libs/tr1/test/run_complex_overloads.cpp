//  (C) Copyright John Maddock 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifdef TEST_STD_HEADERS
#include <complex>
#else
#include <boost/tr1/complex.hpp>
#endif

#include <boost/test/test_tools.hpp>
#include <boost/test/included/test_exec_monitor.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/mpl/if.hpp>
#include <boost/static_assert.hpp>

#include <iostream>
#include <iomanip>

#ifndef VERBOSE
#undef BOOST_MESSAGE
#define BOOST_MESSAGE(x)
#endif

//
// This test verifies that the complex-algorithms that are
// overloaded for scalar types produce the same result as casting
// the argument to a complex type, and calling the complex version
// of the algorithm.  Relative errors must be within 2e in order for 
// the tests to pass.
//

template <class T, class U>
void check(const T& t, const U& u)
{
   BOOST_STATIC_ASSERT((::boost::is_same<T,U>::value));
   BOOST_CHECK_CLOSE(t, u, std::numeric_limits<T>::epsilon() * 100 * 2);
}

template <class T, class U>
void check(const std::complex<T>& t, const std::complex<U>& u)
{
   BOOST_STATIC_ASSERT((::boost::is_same<T,U>::value));
   check(t.real(), u.real());
   check(t.imag(), u.imag());
}

template <class T>
void check_val(const T& val)
{
   typedef typename boost::mpl::if_< boost::is_floating_point<T>, T, double>::type real_type;
   typedef std::complex<real_type> complex_type;

   real_type rval = static_cast<real_type>(val);
   complex_type cval = rval;

   check(std::arg(cval), std::arg(rval));
   check(std::arg(cval), std::arg(val));
   check(std::norm(cval), std::norm(rval));
   check(std::norm(cval), std::norm(val));
   check(std::conj(cval), std::conj(rval));
   check(std::conj(cval), std::conj(val));
   check(std::polar(val), std::polar(rval));
   check(std::polar(val, 0), std::polar(rval, 0));
   check(std::polar(val, val), std::polar(rval, rval));
   check(std::polar(val, rval), std::polar(rval, val));
   check(std::real(cval), std::real(rval));
   check(std::real(cval), std::real(val));
   check(std::imag(cval), std::imag(rval));
   check(std::imag(cval), std::imag(val));
   if(val)
   {
      check(std::pow(cval, cval), std::pow(cval, val));
      check(std::pow(cval, cval), std::pow(cval, rval));
      check(std::pow(cval, cval), std::pow(val, cval));
      check(std::pow(cval, cval), std::pow(rval, cval));
   }
}

void check(double i)
{
   check_val(i);
   check_val(static_cast<float>(i));
   check_val(static_cast<long double>(i));
}

void check(int i)
{
   check_val(static_cast<char>(i));
   check_val(static_cast<unsigned char>(i));
   check_val(static_cast<signed char>(i));
   check_val(static_cast<short>(i));
   check_val(static_cast<unsigned short>(i));
   check_val(static_cast<int>(i));
   check_val(static_cast<unsigned int>(i));
   check_val(static_cast<long>(i));
   check_val(static_cast<unsigned long>(i));
#ifdef BOOST_HAS_LONG_LONG
   check_val(static_cast<long long>(i));
   check_val(static_cast<unsigned long long>(i));
#elif defined(BOOST_HAS_MS_INT64)
   check_val(static_cast<__int64>(i));
   check_val(static_cast<unsigned __int64>(i));
#endif
   check(static_cast<double>(i));
}

int test_main(int, char*[])
{
   check(0);
   check(0.0);
   check(1);
   check(1.5);
   check(0.5);
   return 0;
}

