/* boost random/gamma_distribution.hpp header file
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
 */

#ifndef BOOST_RANDOM_GAMMA_DISTRIBUTION_HPP
#define BOOST_RANDOM_GAMMA_DISTRIBUTION_HPP

#include <cmath>
#include <cassert>
#include <boost/random/uniform_01.hpp>

namespace boost {

// Knuth
// deterministic polar method, uses trigonometric functions
template<class UniformRandomNumberGenerator, class RealType = double>
class gamma_distribution
{
public:
  typedef UniformRandomNumberGenerator base_type;
  typedef RealType result_type;

  explicit gamma_distribution(base_type & rng, const result_type& alpha)
    : _rng(rng), _exp(rng, 1), _alpha(alpha)
  {
    assert(alpha > 0);
 #ifndef BOOST_NO_STDC_NAMESPACE
    // allow for Koenig lookup
    using std::exp;
#endif
   _p = exp(result_type(1.0)) / (_alpha + exp(result_type(1.0)));
  }

  // compiler-generated copy ctor and assignment operator are fine

  base_type& base() const { return _rng.base(); }
  RealType alpha() const { return _alpha; }

  void reset() { _rng.reset(); _exp.reset(); }

  result_type operator()()
  {
#ifndef BOOST_NO_STDC_NAMESPACE
    // allow for Koenig lookup
    using std::tan; using std::sqrt; using std::exp; using std::log;
    using std::pow;
#endif
    if(_alpha == 1) {
      return _exp();
    } else if(_alpha > 1) {
      // Can we have a boost::mathconst please?
      const double pi = 3.14159265358979323846;
      for(;;) {
        result_type y = tan(pi * _rng());
        result_type x = sqrt(2*_alpha-1)*y + _alpha-1;
        if(x <= 0)
          continue;
        if(_rng() > (1+y*y) * exp((_alpha-1)*log(x/(_alpha-1)) - 
                                  sqrt(2*_alpha-1)*y))
          continue;
        return x;
      }
    } else /* alpha < 1 */ {
      for(;;) {
        result_type u = _rng();
        result_type y = _exp();
        result_type x, q;
        if(u < _p) {
          x = exp(-y/_alpha);
          q = _p*exp(-x);
        } else {
          x = 1+y;
          q = _p + (result_type(1.0)-_p) * pow(x, _alpha-result_type(1.0));
        }
        if(u >= q)
          continue;
        return x;
      }
    }
  }
#ifndef BOOST_NO_OPERATORS_IN_NAMESPACE
  friend bool operator==(const gamma_distribution& x, 
                         const gamma_distribution& y)
  {
    return x._mean == y._mean && x._sigma == y._sigma && 
      x._valid == y._valid && x._rng == y._rng;
  }
#else
  // Use a member function
  bool operator==(const gamma_distribution& rhs) const
  {
    return _mean == rhs._mean && _sigma == rhs._sigma && 
      _valid == rhs._valid && _rng == rhs._rng;
  }
#endif
private:
  uniform_01<base_type, RealType> _rng;
  exponential_distribution<base_type, RealType> _exp;
  result_type _alpha;
  // some data precomputed from the parameters
  result_type _p;
};

} // namespace boost

#endif // BOOST_RANDOM_GAMMA_DISTRIBUTION_HPP
