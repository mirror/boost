/* boost random/subtract_with_carry.hpp header file
 *
 * Copyright Jens Maurer 2002
 * Permission to use, copy, modify, sell, and distribute this software
 * is hereby granted without fee provided that the above copyright notice
 * appears in all copies and that both that copyright notice and this
 * permission notice appear in supporting documentation,
 *
 * Jens Maurer makes no representations about the suitability of this
 * software for any purpose. It is provided "as is" without express or
 * implied warranty.
 *
 * See http://www.boost.org for most recent version including documentation.
 *
 * $Id$
 *
 * Revision history
 *  2002-03-02  created
 */

#ifndef BOOST_RANDOM_SUBTRACT_WITH_CARRY_HPP
#define BOOST_RANDOM_SUBTRACT_WITH_CARRY_HPP

#include <iostream>
#include <algorithm>     // std::equal
#include <boost/config.hpp>
#include <boost/limits.hpp>
#include <boost/cstdint.hpp>
#include <boost/random/linear_congruential.hpp>


namespace boost {
namespace random {

// subtract-with-carry generator for integers
// by Martin Luscher

template<class IntType, unsigned int b, unsigned int s, unsigned int r,
  IntType val>
class subtract_with_carry
{
public:
  typedef IntType result_type;
  BOOST_STATIC_CONSTANT(bool, has_fixed_range = true);
  BOOST_STATIC_CONSTANT(bool, min_value = 0);
  BOOST_STATIC_CONSTANT(bool, max_value = b-1);
  BOOST_STATIC_CONSTANT(unsigned int, base = b);
  BOOST_STATIC_CONSTANT(unsigned int, long_lag = r);
  BOOST_STATIC_CONSTANT(unsigned int, short_lag = s);

  result_type min() const { return min_value; }
  result_type max() const { return max_value; }

  subtract_with_carry() { seed(); }
  explicit subtract_with_carry(uint32_t value) { seed(value); }
  template<class Generator>
  explicit subtract_with_carry(Generator & gen) { seed(gen); }
  // compiler-generated copy ctor and assignment operator are fine

  void seed(uint32_t value = 19780503u)
  {
    random::linear_congruential<int32_t, 40014, 0, 2147483563, 0> intgen(value);
    seed(intgen);
  }

  // For GCC, moving this function out-of-line prevents inlining, which may
  // reduce overall object code size.  However, MSVC does not grok
  // out-of-line template member functions.
  template<class Generator>
  void seed(Generator & gen)
  {
    // I could have used std::generate_n, but it takes "gen" by value
    for(unsigned int j = 0; j < long_lag; ++j)
      x[j] = gen() % base;
    carry = (x[long_lag-1] == 0);
    // call fill() next time operator() is called
    i = long_lag;
  }

  result_type operator()()
  {
    if(i >= long_lag)
      fill();
    return x[i++];
  }

  static bool validation(result_type x) { return x == val; }
  
#ifndef BOOST_NO_OPERATORS_IN_NAMESPACE
  friend std::ostream& operator<<(std::ostream& os, const subtract_with_carry& f)
  {
    os << f.i << " " << f.carry << " ";
    for(unsigned int i = 0; i < long_lag; ++i)
      os << f.x[i] << " ";
    return os;
  }
  friend std::istream& operator>>(std::istream& is, subtract_with_carry& f)
  {
    is >> f.i >> std::ws >> f.carry >> std::ws;
    for(unsigned int i = 0; i < long_lag; ++i)
      is >> f.x[i] >> std::ws;
    return is;
  }
  friend bool operator==(const subtract_with_carry& x, const subtract_with_carry& y)
  { return x.i == y.i && std::equal(x.x, x.x+long_lag, y.x); }
#else
  // Use a member function; Streamable concept not supported.
  bool operator==(const subtract_with_carry& rhs) const
  { return i == rhs.i && std::equal(x, x+long_lag, rhs.x); }
#endif

private:
  void fill();
  unsigned int i;
  unsigned int carry;
  IntType x[long_lag];
};

#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
//  A definition is required even for integral static constants
template<class IntType, unsigned int b, unsigned int s, unsigned int r, IntType val>
const bool subtract_with_carry<IntType, b, s, r, val>::has_fixed_range;
template<class IntType, unsigned int b, unsigned int s, unsigned int r, IntType val>
const unsigned int subtract_with_carry<IntType, b, s, r, val>::base;
template<class IntType, unsigned int b, unsigned int s, unsigned int r, IntType val>
const unsigned int subtract_with_carry<IntType, b, s, r, val>::long_lag;
template<class IntType, unsigned int b, unsigned int s, unsigned int r, IntType val>
const unsigned int subtract_with_carry<IntType, b, s, r, val>::short_lag;
#endif

template<class IntType, unsigned int b, unsigned int s, unsigned int r, IntType val>
void subtract_with_carry<IntType, b, s, r, val>::fill()
{
  // two loops to avoid costly modulo operations
  {  // extra scope for MSVC brokenness w.r.t. for scope
  for(unsigned int j = 0; j < short_lag; ++j) {
    IntType delta = x[j+(long_lag-short_lag)] - x[j] - carry;
    if(delta < 0) {
      delta += base;
      carry = 1;
    } else {
      carry = 0;
    }
    x[j] = delta;
  }
  }
  for(unsigned int j = short_lag; j < long_lag; ++j) {
    IntType delta = x[j-short_lag] - x[j] - carry;
    if(delta < 0) {
      delta += base;
      carry = 1;
    } else {
      carry = 0;
    }
    x[j] = delta;
  }
  i = 0;
}


typedef random::subtract_with_carry<int, (1<<24), 10, 24, 0> ranlux_base;

#if !defined(BOOST_NO_INT64_T) && !defined(BOOST_NO_INTEGRAL_INT64_T)
typedef random::subtract_with_carry<int64_t, (int64_t(1)<<48), 10, 24, 0> ranlux64_base;
#endif /* !BOOST_NO_INT64_T && !BOOST_NO_INTEGRAL_INT64_T */

} // namespace random
} // namespace boost

#endif // BOOST_RANDOM_SUBTRACT_WITH_CARRY_HPP
