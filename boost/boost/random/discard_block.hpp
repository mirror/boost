/* boost random/discard_block.hpp header file
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
 *  2001-03-02  created
 */

#ifndef BOOST_RANDOM_DISCARD_BLOCK_HPP
#define BOOST_RANDOM_DISCARD_BLOCK_HPP

#include <iostream>
#include <cassert>
#include <boost/config.hpp>
#include <boost/limits.hpp>
#include <boost/static_assert.hpp>
#include <boost/cstdint.hpp>     // uint32_t


namespace boost {
namespace random {

template<class UniformRandomNumberGenerator, unsigned int p, unsigned int r,
#ifndef BOOST_NO_DEPENDENT_TYPES_IN_TEMPLATE_VALUE_PARAMETERS
  typename UniformRandomNumberGenerator::result_type 
#else
  uint32_t
#endif
  val = 0>
class discard_block
{
public:
  typedef UniformRandomNumberGenerator base_type;
  typedef typename base_type::result_type result_type;

  BOOST_STATIC_CONSTANT(bool, has_fixed_range = base_type::has_fixed_range);
  BOOST_STATIC_CONSTANT(unsigned int, total_block = p);
  BOOST_STATIC_CONSTANT(unsigned int, returned_block = r);

  discard_block() : _rng(), _n(0) { }
  explicit discard_block(const base_type & rng) : _rng(rng), _n(0) { }
  template<class T>
  void seed(T s) { _rng.seed(s); _n = 0; }

  result_type operator()()
  {
    if(_n >= returned_block) {
      for( ; _n < total_block; ++_n)
        // discard value of random number generator
        _rng();
      _n = 0;
    }
    ++_n;
    return _rng();
  }

  result_type min() const { return _rng.min(); }
  result_type max() const { return _rng.max(); }
  static bool validation(result_type x) { return val == x; }

#ifndef BOOST_NO_OPERATORS_IN_NAMESPACE
  friend std::ostream& operator<<(std::ostream& os, const discard_block& s)
  {
    os << s._rng << " " << s._n << " ";
    return os;
  }
  friend std::istream& operator>>(std::istream& is, discard_block& s)
  {
    is >> s._rng >> std::ws >> s._n >> std::ws;
    return is;
  }
  friend bool operator==(const discard_block& x, const discard_block& y)
  { return x._rng == y._rng && x._n == y._n; }
#else
  // Use a member function; Streamable concept not supported.
  bool operator==(const discard_block& rhs) const
  { return _rng == rhs._rng && _n == rhs._n; }
#endif

private:
  base_type _rng;
  int _n;
};

#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
//  A definition is required even for integral static constants
template<class UniformRandomNumberGenerator, unsigned int p, unsigned int r, 
#ifndef BOOST_NO_DEPENDENT_TYPES_IN_TEMPLATE_VALUE_PARAMETERS
  typename UniformRandomNumberGenerator::result_type 
#else
  uint32_t
#endif
  val>
const bool discard_block<UniformRandomNumberGenerator, p, r, val>::has_fixed_range;

template<class UniformRandomNumberGenerator, unsigned int p, unsigned int r,
#ifndef BOOST_NO_DEPENDENT_TYPES_IN_TEMPLATE_VALUE_PARAMETERS
  typename UniformRandomNumberGenerator::result_type 
#else
  uint32_t
#endif
  val>
const unsigned int discard_block<UniformRandomNumberGenerator, p, r, val>::total_block;

template<class UniformRandomNumberGenerator, unsigned int p, unsigned int r,
#ifndef BOOST_NO_DEPENDENT_TYPES_IN_TEMPLATE_VALUE_PARAMETERS
  typename UniformRandomNumberGenerator::result_type 
#else
  uint32_t
#endif
  val>
const unsigned int discard_block<UniformRandomNumberGenerator, p, r, val>::returned_block;
#endif

} // namespace random

} // namespace boost

#endif // BOOST_RANDOM_DISCARD_BLOCK_HPP
