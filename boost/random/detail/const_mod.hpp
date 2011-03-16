/* boost random/detail/const_mod.hpp header file
 *
 * Copyright Jens Maurer 2000-2001
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org for most recent version including documentation.
 *
 * $Id$
 *
 * Revision history
 *  2001-02-18  moved to individual header files
 */

#ifndef BOOST_RANDOM_CONST_MOD_HPP
#define BOOST_RANDOM_CONST_MOD_HPP

#include <algorithm>
#include <boost/assert.hpp>
#include <boost/static_assert.hpp>
#include <boost/cstdint.hpp>
#include <boost/integer_traits.hpp>
#include <boost/type_traits/make_unsigned.hpp>
#include <boost/detail/workaround.hpp>

#include <boost/random/detail/disable_warnings.hpp>

namespace boost {
namespace random {

/*
 * Some random number generators require modular arithmetic.  Put
 * everything we need here.
 * IntType must be an integral type.
 */

template<class IntType, IntType m>
class const_mod
{
public:
  static IntType apply(IntType x)
  {
    if(((unsigned_m() - 1) & unsigned_m()) == 0)
      return (unsigned_type(x)) & (unsigned_m() - 1);
    else {
      IntType supress_warnings = (m == 0);
      BOOST_ASSERT(supress_warnings == 0);
      return x % (m + supress_warnings);
    }
  }

  static IntType add(IntType x, IntType c)
  {
    if(((unsigned_m() - 1) & unsigned_m()) == 0)
      return (unsigned_type(x) + unsigned_type(c)) & (unsigned_m() - 1);
    else if(c == 0)
      return x;
    else if(x < m - c)
      return x + c;
    else
      return x - (m - c);
  }

  static IntType mult(IntType a, IntType x)
  {
    if(((unsigned_m() - 1) & unsigned_m()) == 0)
      return unsigned_type(a) * unsigned_type(x) & (unsigned_m() - 1);
    else if(a == 0)
      return 0;
    else if(a == 1)
      return x;
    else if(m <= traits::const_max/a)      // i.e. a*m <= max
      return mult_small(a, x);
    else if(traits::is_signed && (m%a < m/a))
      return mult_schrage(a, x);
    else if(x == 1)
      return a;
    else
      return mult_general(a, x);
  }

  static IntType mult_add(IntType a, IntType x, IntType c)
  {
    if(((unsigned_m() - 1) & unsigned_m()) == 0)
      return (unsigned_type(a) * unsigned_type(x) + unsigned_type(c)) & (unsigned_m() - 1);
    else if(a == 0)
      return c;
    else if(m <= (traits::const_max-c)/a) {  // i.e. a*m+c <= max
      IntType supress_warnings = (m == 0);
      BOOST_ASSERT(supress_warnings == 0);
      return (a*x+c) % (m + supress_warnings);
    } else
      return add(mult(a, x), c);
  }

  static IntType pow(IntType a, boost::uintmax_t exponent)
  {
      IntType result = 1;
      while(exponent != 0) {
          if(exponent % 2 == 1) {
              result = mult(result, a);
          }
          a = mult(a, a);
          exponent /= 2;
      }
      return result;
  }

  static IntType invert(IntType x)
  { return x == 0 ? 0 : (m == 0? invert_euclidian0(x) : invert_euclidian(x)); }

private:
  typedef integer_traits<IntType> traits;
  typedef typename make_unsigned<IntType>::type unsigned_type;

  const_mod();      // don't instantiate

  static IntType mult_small(IntType a, IntType x)
  {
    IntType supress_warnings = (m == 0);
    BOOST_ASSERT(supress_warnings == 0);
    return a*x % (m + supress_warnings);
  }

  static IntType mult_schrage(IntType a, IntType value)
  {
    const IntType q = m / a;
    const IntType r = m % a;

    BOOST_ASSERT(r < q);        // check that overflow cannot happen

    return sub(a*(value%q), r*(value/q));
  }

  static IntType mult_general(IntType a, IntType b) {
    IntType q, r;
    IntType value = 0;

    IntType supress_warnings = (m == 0);
    BOOST_ASSERT(supress_warnings == 0);

    while(true) {
      if(a == 0 || b <= traits::const_max/a)
        return add(value, IntType(a * b % (m + supress_warnings)));

      if(b < a) std::swap(a, b);
      q = m / a;
      r = m % a;

      value = add(value, IntType(a*(b%q)));
        
      a = r;
      b = IntType(b/q);
      if(a == 0 || b <= traits::const_max/a)
        return sub(value, IntType(a * b % (m + supress_warnings)));
        
      if(b < a) std::swap(a, b);
      q = m / a;
      r = m % a;
      
      value = sub(value, IntType(a*(b%q)));
          
      a = r;
      b = IntType(b/q);
    }
  }

  static IntType sub(IntType a, IntType b)
  {
    if(a < b)
      return m - (b - a);
    else
      return a - b;
  }

  static unsigned_type unsigned_m()
  {
      if(m == 0) {
          return unsigned_type((std::numeric_limits<IntType>::max)()) + 1;
      } else {
          return unsigned_type(m);
      }
  }

  // invert c in the finite field (mod m) (m must be prime)
  static IntType invert_euclidian(IntType c)
  {
    // we are interested in the gcd factor for c, because this is our inverse
    BOOST_ASSERT(c > 0);
    IntType l1 = 0;
    IntType l2 = 1;
    IntType n = c;
    IntType p = m;
    for(;;) {
      IntType q = p / n;
      l1 += q * l2;
      p -= q * n;
      if(p == 0)
        return l2;
      IntType q2 = n / p;
      l2 += q2 * l1;
      n -= q2 * p;
      if(n == 0)
        return m - l1;
    }
  }

  // invert c in the finite field (mod m) (c must be relatively prime to m)
  static IntType invert_euclidian0(IntType c)
  {
    // we are interested in the gcd factor for c, because this is our inverse
    BOOST_ASSERT(c > 0);
    if(c == 1) return 1;
    IntType l1 = 0;
    IntType l2 = 1;
    IntType n = c;
    IntType p = m;
    IntType max = (std::numeric_limits<IntType>::max)();
    IntType q = max / n;
    BOOST_ASSERT(max % n != n - 1 && "c must be relatively prime to m.");
    l1 += q * l2;
    p = max - q * n + 1;
    for(;;) {
      if(p == 0)
        return l2;
      IntType q2 = n / p;
      l2 += q2 * l1;
      n -= q2 * p;
      if(n == 0)
        return m - l1;
      q = p / n;
      l1 += q * l2;
      p -= q * n;
    }
  }
};

} // namespace random
} // namespace boost

#include <boost/random/detail/enable_warnings.hpp>

#endif // BOOST_RANDOM_CONST_MOD_HPP
