/* boost random.hpp header file
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
 * See http://www.boost.org for most recent version including documentation.
 *
 * $Id$
 *
 * Revision history
 *  2000-02-18  portability fixes (thanks to Beman Dawes)
 *  2000-02-21  shuffle_output, inversive_congruential_schrage,
 *              generator_iterator, uniform_smallint
 *  2000-02-23  generic modulus arithmetic helper, removed *_schrage classes,
 *              implemented Streamable and EqualityComparable concepts for 
 *              generators, added Bernoulli distribution and Box-Muller
 *              transform
 *  2000-03-01  cauchy, lognormal, triangle distributions; fixed 
 *              uniform_smallint; renamed gaussian to normal distribution
 *  2000-03-05  implemented iterator syntax for distribution functions
 *  2000-04-21  removed some optimizations for better BCC/MSVC compatibility
 *  2000-05-10  adapted to BCC and MSVC
 *  2000-06-13  incorporated review results
 *  2000-07-06  moved basic templates from namespace detail to random
 *  2000-09-23  warning removals and int64 fixes (Ed Brey)
 */

#ifndef BOOST_RANDOM_HPP
#define BOOST_RANDOM_HPP

#include <iostream>
#include <limits>
#include <cmath>           // for std::log etc.
#include <cstddef>         // std::ptrdiff_t
#include <cassert>
#include <vector>
#include <functional>
#include <algorithm>       // std::transform, std::copy
#include <iterator>        // std::iterator_category

#include <boost/utility.hpp>
#include <boost/cstdint.hpp>  // exact bit-sized integers
#include <boost/operators.hpp>
#include <boost/integer_traits.hpp>


/*
 * Hack around various namespace challenged compilers
 */
#ifdef BOOST_NO_STDC_NAMESPACE
namespace std {
#ifndef BOOST_MSVC
  using ::exp;
  using ::log;
  using ::sqrt; 
  using ::sin; 
  using ::cos;
  using ::tan;
#else
  // Even the "using" workaround fails with MSVC. We reimplement the
  // functions.  This will get into trouble if we need these functions in
  // another file.  Future plan: Move this stuff into a separate header file.
  inline double exp(double x) { return ::exp(x); }
  inline double log(double x) { return ::log(x); }
  inline double sqrt(double x) { return ::sqrt(x); }
  inline double sin(double x) { return ::sin(x); }
  inline double cos(double x) { return ::cos(x); }
  inline double tan(double x) { return ::tan(x); }
#endif
} // namespace std
#endif

namespace boost {

#ifdef __GNUC__
// Special gcc workaround: gcc does not yet support using-declarations
// in template classes (confirmed by gcc author Martin v. Loewis)
  using std::sqrt;
  using std::exp;
  using std::log;
  using std::sin;
  using std::cos;
  using std::tan;
#endif

/*
 * End of hacks for various namespace challenged compilers
 */


/*
 * Some random number generators.
 */

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
  static IntType add(IntType x, IntType c)
  {
    if(c == 0)
      return x;
    else if(c <= traits::const_max - m)    // i.e. m+c < max
      return add_small(x, c);
    else if(traits::is_signed)
      return add_signed(x, c);
    else {
      // difficult
      assert(!"const_mod::add with c too large");
      return 0;
    }
  }

  static IntType mult(IntType a, IntType x)
  {
    if(a == 1)
      return x;
    else if(m <= traits::const_max/a)      // i.e. a*m <= max
      return mult_small(a, x);
    else if(traits::is_signed && (m%a < m/a))
      return mult_schrage(a, x);
    else {
      // difficult
      assert(!"const_mod::mult with a too large");
      return 0;
    }
  }

  static IntType mult_add(IntType a, IntType x, IntType c)
  { 
    if(m <= (traits::const_max-c)/a)   // i.e. a*m+c <= max
      return (a*x+c) % m;
    else
      return add(mult(a, x), c);
  }

  static IntType invert(IntType x)
  { return x == 0 ? 0 : invert_euclidian(x); }

private:
  typedef integer_traits<IntType> traits;

  const_mod();      // don't instantiate

  static IntType add_small(IntType x, IntType c)
  {
    x += c;
    if(x >= m)
      x -= m;
    return x;
  }

  static IntType add_signed(IntType x, IntType c)
  {
    x += (c-m);
    if(x < 0)
      x += m;
    return x;
  }

  static IntType mult_small(IntType a, IntType x)
  {
    return a*x % m;
  }

  static IntType mult_schrage(IntType a, IntType value)
  {
    const IntType q = m / a;
    const IntType r = m % a;

    assert(r < q);        // check that overflow cannot happen

    value = a*(value%q) - r*(value/q);
    while(value <= 0)
      value += m;
    return value;
  }

  // invert c in the finite field (mod m) (m must be prime)
  static IntType invert_euclidian(IntType c)
  {
    // we are interested in the gcd factor for c, because this is our inverse
    assert(c > 0);
    assert(m > 0);
    assert(boost::integer_traits<IntType>::is_signed);
    IntType l1 = 0;
    IntType l2 = 1;
    IntType n = c;
    IntType p = m;
    for(;;) {
      IntType q = p / n;
      l1 -= q * l2;           // this requires a signed IntType!
      p -= q * n;
      if(p == 0)
	return (l2 < 1 ? l2 + m : l2);
      IntType q2 = n / p;
      l2 -= q2 * l1;
      n -= q2 * p;
      if(n == 0)
	return (l1 < 1 ? l1 + m : l1);
    }
  }
};

// The modulus is exactly the word size: rely on machine overflow handling.
// Due to a GCC bug, we cannot partially specialize in the presence of
// template value parameters.
template<>
class const_mod<unsigned int, 0>
{
  typedef unsigned int IntType;
public:
  static IntType add(IntType x, IntType c) { return x+c; }
  static IntType mult(IntType a, IntType x) { return a*x; }
  static IntType mult_add(IntType a, IntType x, IntType c) { return a*x+c; }

  // m is not prime, thus invert is not useful
private:                      // don't instantiate
  const_mod();
};

// the modulus is some power of 2: rely partly on machine overflow handling
// we only specialize for rand48 at the moment
#ifndef BOOST_NO_INT64_T
template<>
class const_mod<uint64_t, uint64_t(1) << 48>
{
  typedef uint64_t IntType;
public:
  static IntType add(IntType x, IntType c) { return c == 0 ? x : mod(x+c); }
  static IntType mult(IntType a, IntType x) { return mod(a*x); }
  static IntType mult_add(IntType a, IntType x, IntType c)
    { return mod(a*x+c); }
  static IntType mod(IntType x) { return x &= ((uint64_t(1) << 48)-1); }

  // m is not prime, thus invert is not useful
private:                      // don't instantiate
  const_mod();
};
#endif /* !BOOST_NO_INT64_T */


// compile-time configurable linear congruential generator
template<class IntType, IntType a, IntType c, IntType m, IntType val>
class linear_congruential
{
public:
  typedef IntType result_type;
#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
  static const IntType multiplier = a;
  static const IntType increment = c;
  static const IntType modulus = m;
  static const bool has_fixed_range = true;
  static const result_type min_value = ( c == 0 ? 1 : 0 );
  static const result_type max_value = m-1;
#else
  enum {
    multiplier = a,
    increment = c,
    modulus = m,
    has_fixed_range = false
  };
#endif
  result_type min() const { return c == 0 ? 1 : 0; }
  result_type max() const { return m-1; }
  explicit linear_congruential(IntType x0 = 1) : _x(x0) { 
    assert(c || x0); /* if c == 0 and x(0) == 0 then x(n) = 0 for all n */
    // overflow check
    // disabled because it gives spurious "divide by zero" gcc warnings
    // assert(m == 0 || (a*(m-1)+c) % m == (c < a ? c-a+m : c-a)); 
  }
  // compiler-generated copy constructor and assignment operator are fine
  void seed(IntType x0) { assert(c || x0); _x = x0; }
  IntType operator()() {
    _x = const_mod<IntType, m>::mult_add(a, _x, c);
    return _x;
  }
  bool validation(IntType x) const { return val == x; }

#ifndef  BOOST_NO_OPERATORS_IN_NAMESPACE
  friend std::ostream& operator<<(std::ostream& os, linear_congruential lcg)
  { os << lcg._x; return os; }
  friend std::istream& operator>>(std::istream& is, linear_congruential& lcg)
  { is >> lcg._x; return is; }
  friend bool operator==(linear_congruential x, linear_congruential y)
  { return x._x == y._x; }
#else
  // Use a member function; Streamable concept not supported.
  bool operator==(linear_congruential rhs) const
  { return _x == rhs._x; }
#endif
private:
  IntType _x;
};

} // namespace random

// validation values from the publications
typedef random::linear_congruential<int32_t, 16807, 0, 2147483647, 
  1043618065> minstd_rand0;
typedef random::linear_congruential<int32_t, 48271, 0, 2147483647,
  399268537> minstd_rand;


#if !defined(BOOST_NO_INT64_T) && \
    !defined(BOOST_NO_INCLASS_MEMBER_INITIALIZATION)
// emulate the lrand48() C library function; requires support for uint64_t
class rand48 
{
public:
  typedef int32_t result_type;
#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
  static const bool has_fixed_range = true;
  static const int32_t min_value = 0;
  static const int32_t max_value = integer_traits<int32_t>::const_max;
#else
  enum { has_fixed_range = false };
#endif
  int32_t min() const { return 0; }
  int32_t max() const { return std::numeric_limits<int32_t>::max(); }
  
  explicit rand48(int32_t x0 = 1) : lcf(cnv(x0)) { }
  explicit rand48(uint64_t x0) : lcf(x0) { }
  // compiler-generated copy ctor and assignment operator are fine
  void seed(int32_t x0) { lcf.seed(cnv(x0)); }
  void seed(uint64_t x0) { lcf.seed(x0); }
  int32_t operator()() { return lcf() >> 17; }
  // by experiment from lrand48()
  bool validation(int32_t x) const { return x == 1993516219; }

#ifndef BOOST_NO_OPERATORS_IN_NAMESPACE
  friend std::ostream& operator<<(std::ostream& os, const rand48& r)
  { os << r.lcf; return os; }
  friend std::istream& operator>>(std::istream& is, rand48& r)
  { is >> r.lcf; return is; }
  friend bool operator==(const rand48& x, const rand48& y)
  { return x.lcf == y.lcf; }
#else
  // Use a member function; Streamable concept not supported.
  bool operator==(const rand48& rhs) const
  { return lcf == rhs.lcf; }
#endif
private:
  random::linear_congruential<uint64_t,
    uint64_t(0xDEECE66DUL) | (uint64_t(0x5) << 32), // xxxxULL is not portable
    0xB, uint64_t(1)<<48, /* unknown */ 0> lcf;
  static uint64_t cnv(int32_t x) 
  { return (static_cast<uint64_t>(x) << 16) | 0x330e;  }
};
#endif /* !BOOST_NO_INT64_T && !BOOST_NO_INCLASS_MEMBER_INITIALIZATION */


namespace random {

// L'Ecuyer 1988
template<class MLCG1, class MLCG2,
#ifndef BOOST_NO_DEPENDENT_TYPES_IN_TEMPLATE_VALUE_PARAMETERS
  typename MLCG1::result_type 
#else
  int32_t
#endif
  val>
class additive_combine
{
public:
  typedef MLCG1 first_base;
  typedef MLCG2 second_base;
  typedef typename MLCG1::result_type result_type;
#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
  static const bool has_fixed_range = true;
  static const result_type min_value = 1;
  static const result_type max_value = MLCG1::max_value-1;
#else
  enum { has_fixed_range = false };
#endif
  result_type min() const { return 1; }
  result_type max() const { return _mlcg1.max()-1; }

  additive_combine() : _mlcg1(), _mlcg2() { }
  additive_combine(typename MLCG1::result_type seed1, 
		   typename MLCG2::result_type seed2)
    : _mlcg1(seed1), _mlcg2(seed2) { }
  result_type operator()() {
    result_type z = _mlcg1() - _mlcg2();
    if(z < 1)
      z += MLCG1::modulus-1;
    return z;
  }
  bool validation(result_type x) const { return val == x; }

#ifndef BOOST_NO_OPERATORS_IN_NAMESPACE
  friend std::ostream& operator<<(std::ostream& os, const additive_combine& r)
  { os << r._mlcg1 << " " << r._mlcg2; return os; }
  friend std::istream& operator>>(std::istream& is, additive_combine& r)
  { is >> r._mlcg1 >> std::ws >> r._mlcg2; return is; }
  friend bool operator==(const additive_combine& x, const additive_combine& y)
  { return x._mlcg1 == y._mlcg1 && x._mlcg2 == y._mlcg2; }
#else
  // Use a member function; Streamable concept not supported.
  bool operator==(const additive_combine& rhs) const
  { return _mlcg1 == rhs._mlcg1 && _mlcg2 == rhs._mlcg2; }
#endif
private:
  MLCG1 _mlcg1;
  MLCG2 _mlcg2;
};

} // namespace random

typedef random::additive_combine<
    random::linear_congruential<int32_t, 40014, 0, 2147483563, 0>,
    random::linear_congruential<int32_t, 40692, 0, 2147483399, 0>,
  /* unknown */ 0> ecuyer1988;


namespace random {

// Carter Bays and S.D. Durham 1979
template<class UniformRandomNumberGenerator, int k, 
  class IntType = typename UniformRandomNumberGenerator::result_type,
#ifndef BOOST_NO_DEPENDENT_TYPES_IN_TEMPLATE_VALUE_PARAMETERS
  typename UniformRandomNumberGenerator::result_type 
#else
  uint32_t
#endif
  val = 0>
class shuffle_output
{
public:
  typedef UniformRandomNumberGenerator base_type;
  typedef typename base_type::result_type result_type;

#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
  static const bool has_fixed_range = false;
  static const int buffer_size = k;
#else
  enum { 
    has_fixed_range = false,
    buffer_size = k
  };
#endif
  shuffle_output() : _rng() { init(); }
#if defined(BOOST_MSVC) && _MSC_VER <= 1200
  // MSVC does not implicitly generate the copy constructor here
  shuffle_output(const shuffle_output & x)
    : _rng(x._rng), y(x.y) { std::copy(x.v, x.v+k, v); }
#endif
  template<class T>
  explicit shuffle_output(T seed) : _rng(seed) { init(); }
  explicit shuffle_output(const base_type & rng) : _rng(rng) { init(); }
  template<class T>
  void seed(T s) { _rng.seed(s); init(); }

  result_type operator()() {
    // calculating the range every time may seem wasteful.  However, this
    // makes the information locally available for the optimizer.
    result_type range = max()-min()+1;
    int j = k*IntType(y-min())/range;
    // assert(0 <= j && j < k);
    y = v[j];
    v[j] = _rng();
    return y;
  }

  result_type min() const { return _rng.min(); }
  result_type max() const { return _rng.max(); }
  bool validation(result_type x) const { return val == x; }

#ifndef BOOST_NO_OPERATORS_IN_NAMESPACE
  friend std::ostream& operator<<(std::ostream& os, const shuffle_output& s)
  {
    os << s._rng << " " << s.y << " ";
    std::copy(s.v, s.v+k, std::ostream_iterator<result_type>(os, " "));
    return os;
  }
  friend std::istream& operator>>(std::istream& is, shuffle_output& s)
  {
    is >> s._rng >> std::ws >> s.y >> std::ws;
    for(int i = 0; i < s.buffer_size; ++i)
      is >> s.v[i] >> std::ws;
    return is;
  }
  friend bool operator==(const shuffle_output& x, const shuffle_output& y)
  { return x._rng == y._rng && x.y == y.y && std::equal(x.v, x.v+k, y.v); }
#else
  // Use a member function; Streamable concept not supported.
  bool operator==(const shuffle_output& rhs) const
  { return _rng == rhs._rng && y == rhs.y && std::equal(v, v+k, rhs.v); }
#endif
private:
  void init() {
    // TODO: should be a compile-time assert
    assert(std::numeric_limits<result_type>::is_integer);
    result_type range = max()-min();
    assert(range > 0);      // otherwise there would be little choice
    if(IntType(k * range) < IntType(range))  // not a sufficient condition
      // likely overflow with bucket number computation
      assert(!"overflow will occur");

    // we cannot use std::generate, because it uses pass-by-value for _rng
    for(result_type * p = v; p != v+k; ++p)
      *p = _rng();
    y = _rng();
  }

  base_type _rng;
  result_type v[k];
  result_type y;
};

} // namespace random

// validation by experiment from Harry Erwin's generator.h (private e-mail)
typedef random::shuffle_output<
    random::linear_congruential<uint32_t, 1366, 150889, 714025, 0>,
  97, uint32_t, 139726> kreutzer1986;


namespace random {

// Eichenauer and Lehn 1986
template<class IntType, IntType a, IntType b, IntType p, IntType val>
class inversive_congruential
{
public:
  typedef IntType result_type;
#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
  static const bool has_fixed_range = false;
  static const result_type min_value = (b == 0 ? 1 : 0);
  static const result_type max_value = p-1;
  static const result_type multiplier = a;
  static const result_type increment = b;
  static const result_type modulus = p;
#else
  enum { 
    has_fixed_range = false,
    multiplier = a,
    increment = b,
    modulus = p
  };
#endif
  result_type min() const { return b == 0 ? 1 : 0; }
  result_type max() const { return p-1; }

  explicit inversive_congruential(IntType y0 = 1) : value(y0) {
    if(b == 0) 
      assert(y0 > 0); 
    // TODO: should be compile-time asserts
    assert(b >= 0);
    assert(p > 1);
    assert(a >= 1);
  }
  void seed(IntType y0) { value = y0; if(b == 0) assert(y0 > 0); }
  IntType operator()() {
    typedef const_mod<IntType, p> do_mod;
    value = do_mod::mult_add(a, do_mod::invert(value), b);
    return value;
  }
  bool validation(result_type x) const { return val == x; }

#ifndef BOOST_NO_OPERATORS_IN_NAMESPACE
  friend std::ostream& operator<<(std::ostream& os, inversive_congruential x)
  { os << x.value; return os; }
  friend std::istream& operator>>(std::istream& is, inversive_congruential& x)
  { is >> x.value; return is; }
  friend bool operator==(inversive_congruential x, inversive_congruential y)
  { return x.value == y.value; }
#else
  // Use a member function; Streamable concept not supported.
  bool operator==(inversive_congruential rhs) const
  { return value == rhs.value; }
#endif
private:
  IntType value;
};

} // namespace random

typedef random::inversive_congruential<int32_t, 9102, 2147483647-36884165,
  2147483647, 0> hellekalek1995;


namespace random {

// http://www.math.keio.ac.jp/matumoto/emt.html
template<class DataType, int n, int m, int r, DataType a, int u,
  int s, DataType b, int t, DataType c, int l, DataType val>
class mersenne_twister
{
public:
  typedef DataType result_type;
#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
  static const int state_size = n;
  static const int shift_size = m;
  static const int mask_bits = r;
  static const DataType parameter_a = a;
  static const int output_u = u;
  static const int output_s = s;
  static const DataType output_b = b;
  static const int output_t = t;
  static const DataType output_c = c;
  static const int output_l = l;
  static const bool has_fixed_range = true;
  static const result_type min_value = integer_traits<result_type>::const_min;
  static const result_type max_value = integer_traits<result_type>::const_max;
#else
  enum {
    state_size = n, shift_size = m, mask_bits = r,
    parameter_a = a, output_u = u, output_s = s, output_b = b,
    output_t = t, output_c = c, output_l = l, has_fixed_range = false };
#endif
  result_type min() const { return std::numeric_limits<result_type>::min(); }
  result_type max() const { return std::numeric_limits<result_type>::max(); }
  
  mersenne_twister() { seed(); }
  explicit mersenne_twister(DataType value) { seed(value); }
  template<class Generator>
  explicit mersenne_twister(Generator & gen) { seed(gen); }
  // compiler-generated copy ctor and assignment operator are fine
  void seed() { seed(4357u); }
  void seed(DataType value) {
    random::linear_congruential<uint32_t, 69069, 0, 0, /* unknown */ 0> 
      gen(value);
    seed(gen);
  }
  template<class Generator>
  void seed(Generator & gen) {
    // TODO: should be a compile-time assert
    assert(!std::numeric_limits<result_type>::is_signed);
    // I could have used std::generate_n, but it takes "gen" by value
    for(int j = 0; j < n; j++)
      x[j] = gen();
    i = n;
  }
  
  result_type operator()();
  bool validation(result_type x) const { return val == x; }

#ifndef BOOST_NO_OPERATORS_IN_NAMESPACE
  friend std::ostream& operator<<(std::ostream& os, const mersenne_twister& mt)
  {
    os << mt.i << " ";
    std::copy(mt.x, mt.x+n, std::ostream_iterator<data_type>(os, " "));
    return os;
  }
  friend std::istream& operator>>(std::istream& is, mersenne_twister& mt)
  {
    is >> mt.i >> std::ws;
    for(int i = 0; i < mt.state_size; ++i)
      is >> mt.x[i] >> std::ws;
    return is;
  }
  friend bool operator==(const mersenne_twister& x, const mersenne_twister& y)
  { return x.i == y.i && std::equal(x.x, x.x+n, y.x); }
#else
  // Use a member function; Streamable concept not supported.
  bool operator==(const mersenne_twister& rhs) const
  { return i == rhs.i && std::equal(x, x+n, rhs.x); }
#endif

private:
  typedef DataType data_type;
  void twist();
  int i;
  data_type x[n];
};

template<class DataType, int n, int m, int r, DataType a, int u,
  int s, DataType b, int t, DataType c, int l, DataType val>
void mersenne_twister<DataType,n,m,r,a,u,s,b,t,c,l,val>::twist()
{
  const int upper_mask = static_cast<data_type>(-1) << r;
  const int lower_mask = ~upper_mask;
  /*
  for(int j = 0; j < n; j++) {
    // Step 2
    data_type y = (x[j] & upper_mask) | (x[(j+1)%n] & lower_mask);
    // Step 3
    x[j] = x[(j+m)%n] ^ (y >> 1) ^ (y&1 ? a : 0);
  }
  */
  // split loop to avoid costly modulo operations
  {  // extra scope for MSVC brokenness w.r.t. for scope
  for(int j = 0; j < n-m; j++) {
    data_type y = (x[j] & upper_mask) | (x[j+1] & lower_mask);
    x[j] = x[j+m] ^ (y >> 1) ^ (y&1 ? a : 0);
  }
  }

  for(int j = n-m; j < n-1; j++) {
    data_type y = (x[j] & upper_mask) | (x[j+1] & lower_mask);
    x[j] = x[j+m-n] ^ (y >> 1) ^ (y&1 ? a : 0);
  }
  // last iteration
  data_type y = (x[n-1] & upper_mask) | (x[0] & lower_mask);
  x[n-1] = x[n-1+m-n] ^ (y >> 1) ^ (y&1 ? a : 0);
  
  i = 0;
}

template<class DataType, int n, int m, int r, DataType a, int u,
  int s, DataType b, int t, DataType c, int l, DataType val>
inline typename mersenne_twister<DataType,n,m,r,a,u,s,b,t,c,l,val>::result_type
mersenne_twister<DataType,n,m,r,a,u,s,b,t,c,l,val>::operator()()
{
  if(i >= n)
    twist();
  // Step 4
  data_type z = x[i];
  ++i;
  z ^= (z >> u);
  z ^= ((z << s) & b);
  z ^= ((z << t) & c);
  z ^= (z >> l);
  return z;
}

} // namespace random


typedef random::mersenne_twister<uint32_t,351,175,19,0xccab8ee7,11,
  7,0x31b6ab00,15,0xffe50000,17, /* unknown */ 0> mt11213b;

// validation by experiment from mt19937.c
typedef random::mersenne_twister<uint32_t,624,397,31,0x9908b0df,11,
  7,0x9d2c5680,15,0xefc60000,18, 3346425566U> mt19937;


/*
 * Some decorators providing additional interfaces and misc. functionality
 */

namespace detail {

// TODO: check out if this is really useful.

template<class NumberGenerator>
class generator_reference_t
{
public:
  typedef typename NumberGenerator::result_type result_type;
#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
  // doing this properly requires partial specialization, avoid for now
  static const bool has_fixed_range = false;
#else
  enum { has_fixed_range = false };
#endif
  result_type min() const { return generator->min(); }
  result_type max() const { return generator->max(); }
  explicit generator_reference_t(NumberGenerator & gen) : generator(&gen) { }
  // compiler-generated copy ctor and assignment operator are fine

  result_type operator()() { return (*generator)(); }
private:
  NumberGenerator * generator;    // no ownership, is never 0
};

template<class Generator>
generator_reference_t<Generator> generator_reference(Generator & gen)
{
  return generator_reference_t<Generator>(gen);
}

} // namespace detail


template<class Generator>
class generator_iterator
  : equality_comparable<generator_iterator<Generator> >,
  incrementable<generator_iterator<Generator> >,
  dereferenceable<generator_iterator<Generator>, 
      typename Generator::result_type>
{
public:
  // Note: deriving from std::iterator<> is useless
  typedef typename Generator::result_type value_type;
  typedef std::ptrdiff_t difference_type;
  typedef const typename Generator::result_type * pointer;
  typedef const typename Generator::result_type & reference;
  typedef std::input_iterator_tag iterator_category;

  explicit generator_iterator(Generator & g) : gen(g), value(gen()) { }
  generator_iterator& operator++() { value = gen(); return *this; }
  reference operator*() const { return value; }

  friend bool operator==(const generator_iterator<Generator>& x, 
			 const generator_iterator<Generator>& y)
  { return x.gen == y.gen; }
private:
  Generator & gen;
  value_type value;
};



/*
 * Some distribution functions
 */

namespace random {

/*
 * Correctly compare two numbers whose types possibly differ in signedness.
 * See boost::numeric_cast<> for the general idea.
 * Most "if" statements involve only compile-time constants, so the
 * optimizing compiler can do its job easily.
 */

template<class T1, class T2>
int equal_signed_unsigned(T1 x, T2 y)
{
  typedef std::numeric_limits<T1> x_traits;
  typedef std::numeric_limits<T2> y_traits;
  if(x_traits::is_signed == y_traits::is_signed) {
    // no difference in signedness, cast to the larger type
    if(x_traits::digits > y_traits::digits)
      return x == static_cast<T1>(y);
    else
      return static_cast<T2>(x) == y;
  } else if(x_traits::is_signed) {
    // y must be unsigned, i.e. non-negative
    if(x < 0)
      return false;
    else 
      return static_cast<T2>(x) == y;
  } else {          // !x_traits::is_signed && y_traits::is_signed
    // x must be unsigned, i.e. non-negative
    if(y < 0)
      return false;
    else
      return x == static_cast<T1>(y);
  }
}

template<class T1, class T2>
int lessthan_signed_unsigned(T1 x, T2 y)
{
  typedef std::numeric_limits<T1> x_traits;
  typedef std::numeric_limits<T2> y_traits;
  if(x_traits::is_signed == y_traits::is_signed) {
    // no difference in signedness, everything ok
    if(x_traits::digits > y_traits::digits)
      return x < static_cast<T1>(y);
    else
      return static_cast<T2>(x) < y;
  } else if(x_traits::is_signed) {
    // y must be unsigned, i.e. non-negative
    if(x < 0)
      return true;
    else 
      return static_cast<T2>(x) < y;
  } else {          // !x_traits::is_signed && y_traits::is_signed
    // x must be unsigned, i.e. non-negative
    if(y < 0)
      return false;
    else
      return x < static_cast<T1>(y);
  }
}

} // namespace random

// must be in boost namespace, otherwise the inline friend trick fails
template<class Generator, class ResultType>
class generator_iterator_mixin_adapter
  : incrementable<Generator>, equality_comparable<Generator>
{
public:
  typedef std::input_iterator_tag iterator_category;
  typedef ResultType value_type;
  typedef std::ptrdiff_t difference_type;
  typedef const value_type * pointer;
  typedef const value_type & reference;
  Generator& operator++() { v = cast()(); return cast(); }
  const value_type& operator*() const { return v; }

protected:
  // instantiate from derived classes only
  generator_iterator_mixin_adapter() { }
  void iterator_init() { operator++(); }
private:
  Generator & cast() { return static_cast<Generator&>(*this); }
  value_type v;
};


// uniform integer distribution on a small range [min, max]
template<class UniformRandomNumberGenerator, class IntType = int>
class uniform_smallint
  : public generator_iterator_mixin_adapter<
        uniform_smallint<UniformRandomNumberGenerator, IntType>, IntType >
{
public:
  typedef UniformRandomNumberGenerator base_type;
  typedef IntType result_type;
#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
  static const bool has_fixed_range = false;
#else
  enum { has_fixed_range = false };
#endif
  uniform_smallint(base_type & rng, IntType min, IntType max);
  result_type operator()()
  {
    // we must not use the low bits here, because LCGs get very bad then
    return ((_rng() - _rng.min()) / _factor) % _range + _min;
  }
  result_type min() const { return _min; }
  result_type max() const { return _max; }
#ifndef BOOST_NO_OPERATORS_IN_NAMESPACE
  friend bool operator==(const uniform_smallint& x, const uniform_smallint& y)
  { return x._min == y._min && x._max == y._max && x._rng == y._rng; }
#else
  // Use a member function
  bool operator==(const uniform_smallint& rhs) const
  { return _min == rhs._min && _max == rhs._max && _rng == rhs._rng;  }
#endif
private:
  typedef typename base_type::result_type base_result;
  base_type & _rng;
  IntType _min, _max;
  base_result _range;
  int _factor;
};

template<class UniformRandomNumberGenerator, class IntType>
uniform_smallint<UniformRandomNumberGenerator, IntType>::
uniform_smallint(base_type & rng, IntType min, IntType max) 
  : _rng(rng), _min(min), _max(max),
    _range(static_cast<base_result>(_max-_min)+1), _factor(1)
{
  // TODO: should be a compile-time assert
  assert(std::numeric_limits<IntType>::is_integer);
  
  // check how many low bits we can ignore before we get too much
  // quantization error
  base_result r_base = _rng.max() - _rng.min();
  if(r_base == std::numeric_limits<base_result>::max()) {
    _factor = 2;
    r_base /= 2;
  }
  r_base += 1;
  if(r_base % _range == 0) {
    // no quantization effects, good
    _factor = r_base / _range;
  } else {
    const base_result r = 32*_range*_range;
    for(; r_base >= r; _factor *= 2)
      r_base /= 2;
  }
  iterator_init();  // initialize iterator interface
}


// uniform integer distribution on [min, max]
template<class UniformRandomNumberGenerator, class IntType = int>
class uniform_int
  : public generator_iterator_mixin_adapter<
        uniform_int<UniformRandomNumberGenerator, IntType>, IntType >
{
public:
  typedef UniformRandomNumberGenerator base_type;
  typedef IntType result_type;
#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
  static const bool has_fixed_range = false;
#else
  enum { has_fixed_range = false };
#endif
  uniform_int(base_type & rng, IntType min, IntType max) 
    : _rng(rng), _min(min), _max(max), _range(_max - _min),
      _bmin(_rng.min()), _brange(_rng.max() - _bmin) {
    // TODO: should be a compile-time assert
    assert(std::numeric_limits<IntType>::is_integer);
    iterator_init();
  }
  result_type operator()();
  result_type min() const { return _min; }
  result_type max() const { return _max; }
#ifndef BOOST_NO_OPERATORS_IN_NAMESPACE
  friend bool operator==(const uniform_int& x, const uniform_int& y)
  { return x._min == y._min && x._max == y._max && x._rng == y._rng; }
#else
  // Use a member function
  bool operator==(const uniform_int& rhs) const
  { return _min == rhs._min && _max == rhs._max && _rng == rhs._rng;  }
#endif
private:
  typedef typename base_type::result_type base_result;
  base_type & _rng;
  result_type _min, _max, _range;
  base_result _bmin, _brange;
};

template<class UniformRandomNumberGenerator, class IntType>
inline IntType uniform_int<UniformRandomNumberGenerator, IntType>::operator()()
{
  if(random::equal_signed_unsigned(_range, _brange)) {
    // this will probably never happen in real life
    // basically nothing to do; just take care we don't overflow / underflow
    return static_cast<result_type>(_rng() - _bmin) + _min;
  } else if(random::lessthan_signed_unsigned(_brange, _range)) {
    // use rejection method to handle things like 0..3 --> 0..4
    // note: this still does not have perfect efficiency
    for(;;) {
      // we have to concatenate several invocations of the base RNG
      result_type result = 0;
      for(result_type mult = 1;
	  mult-1 <= _range;
	  mult *= static_cast<result_type>(_brange)+1) {
	result += (_rng() - _bmin) * mult;
      }
      if(result <= _range)
	return result + _min;
    }
  } else {                   // brange > range
    if(_brange / _range > 4 /* quantization_cutoff */ ) {
      // the new range is vastly smaller than the source range,
      // so quantization effects are not relevant
      return uniform_smallint<base_type,result_type>(_rng, _min, _max)();
    } else {
      // use rejection method to handle things like 0..5 -> 0..4
      for(;;) {
	base_result result = _rng() - _bmin;
	// result and range are non-negative, and result is possibly larger
	// than range, so the cast is safe
	if(result <= static_cast<base_result>(_range))
	  return result + _min;
      }
    }
  }
}


// a model for RandomNumberGenerator std:25.2.11 [lib.alg.random.shuffle]
template<class UniformRandomNumberGenerator, class IntType = long>
class random_number_generator
{
public:
  typedef UniformRandomNumberGenerator base_type;
  typedef IntType argument_type;
  typedef IntType result_type;
  random_number_generator(base_type & rng) : _rng(rng) { 
    // TODO: should be compile-time asserts
    // MSVC requires the typedef workaround
    typedef typename base_type::result_type base_result_type; 
    assert(std::numeric_limits<base_result_type>::is_integer);
    assert(std::numeric_limits<result_type>::is_integer);
  }
  // compiler-generated copy ctor is fine
  // assignment is disallowed because there is a reference member

  result_type operator()(argument_type n) {
    return uniform_int<base_type>(_rng, 0, n-1)();
  }

private:
  base_type & _rng;
};


// Because it is so commonly used: uniform distribution on the real [0..1)
// range.  This allows for specializations to avoid a costly FP division
template<class UniformRandomNumberGenerator, class RealType = double>
class uniform_01
  : public generator_iterator_mixin_adapter<
        uniform_01<UniformRandomNumberGenerator, RealType>, RealType >
{
public:
  typedef UniformRandomNumberGenerator base_type;
  typedef RealType result_type;
#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
  static const bool has_fixed_range = false;
#else
  enum { has_fixed_range = false };
#endif
  explicit uniform_01(base_type & rng) : _rng(rng) { 
    // TODO: should be a compile-time assert
    assert(!std::numeric_limits<RealType>::is_integer);
    iterator_init();
  }
  // compiler-generated copy ctor is fine
  // assignment is disallowed because there is a reference member

  result_type operator()() {
    return static_cast<result_type>(_rng() - _rng.min()) /
      (static_cast<result_type>(_rng.max()-_rng.min()) +
       (std::numeric_limits<base_result>::is_integer ? 1.0 : 0.0));
  }
  result_type min() const { return 0.0; }
  result_type max() const { return 1.0; }

#ifndef BOOST_NO_OPERATORS_IN_NAMESPACE
  friend bool operator==(const uniform_01& x, const uniform_01& y)
  { return x._rng == y._rng; }
#else
  // Use a member function
  bool operator==(const uniform_01& rhs) const
  { return _rng == rhs._rng;  }
#endif
private:
  typedef typename base_type::result_type base_result;
  base_type & _rng;
};


// uniform distribution on a real range
template<class UniformRandomNumberGenerator, class RealType = double>
class uniform_real
  : public generator_iterator_mixin_adapter<
        uniform_real<UniformRandomNumberGenerator, RealType>, RealType>
{
public:
  typedef UniformRandomNumberGenerator base_type;
  typedef RealType result_type;
#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
  static const bool has_fixed_range = false;
#else
  enum { has_fixed_range = false };
#endif
  uniform_real(base_type & rng, RealType min, RealType max) 
    : _rng(rng), _min(min), _max(max) { 
    // TODO: should be a compile-time assert
    assert(!std::numeric_limits<RealType>::is_integer);
    iterator_init();
  }
  // compiler-generated copy ctor is fine
  // uniform_01 cannot be assigned, neither can this class

  result_type operator()() { return _rng() * (_max - _min) + _min; }
  result_type min() const { return _min; }
  result_type max() const { return _max; }

#ifndef BOOST_NO_OPERATORS_IN_NAMESPACE
  friend bool operator==(const uniform_real& x, const uniform_real& y)
  { return x._min == y._min && x._max == y._max && x._rng == y._rng; }
#else
  // Use a member function
  bool operator==(const uniform_real& rhs) const
  { return _min == rhs._min && _max == rhs._max && _rng == rhs._rng;  }
#endif
private:
  uniform_01<base_type, result_type> _rng;
  RealType _min, _max;
};


// Bernoulli distribution: p(true) = p, p(false) = 1-p   (boolean)
template<class UniformRandomNumberGenerator>
class bernoulli_distribution
  : public generator_iterator_mixin_adapter<
        bernoulli_distribution<UniformRandomNumberGenerator>, bool>
{
public:
  typedef UniformRandomNumberGenerator base_type;
  typedef bool result_type;
  bernoulli_distribution(base_type & rng, double p) 
    : _rng(rng),
      _threshold(static_cast<base_result>
		 (p * (_rng.max() - _rng.min())) + _rng.min())
  {
    // for p == 0, we can only set _threshold = 0, which is not enough
    assert(p > 0);
  }
  // compiler-generated copy ctor is fine
  // assignment is disallowed because there is a reference member

  result_type operator()() { return _rng() <= _threshold; }
#ifndef BOOST_NO_OPERATORS_IN_NAMESPACE
  friend bool operator==(const bernoulli_distribution& x, 
			 const bernoulli_distribution& y)
  { return x._threshold == y._threshold && x._rng == y._rng; }
#else
  // Use a member function
  bool operator==(const bernoulli_distribution& rhs) const
  { return _threshold == rhs._threshold && _rng == rhs._rng;  }
#endif
private:
  typedef typename base_type::result_type base_result;
  base_type & _rng;
  const base_result _threshold;
};

// geometric distribution: p(i) = (1-p) * pow(p, i-1)   (integer)
template<class UniformRandomNumberGenerator, class IntType = int>
class geometric_distribution
  : public generator_iterator_mixin_adapter<
      geometric_distribution<UniformRandomNumberGenerator, IntType>, IntType>
{
public:
  typedef UniformRandomNumberGenerator base_type;
  typedef IntType result_type;

  geometric_distribution(base_type & rng, double p)
    : _rng(rng) {
    assert(0.0 < p && p < 1.0);
    using std::log;
    _log_p = log(p);
    iterator_init();
  }
  // compiler-generated copy ctor is fine
  // uniform_01 cannot be assigned, neither can this class

  result_type operator()() {
    using std::log;
    return IntType (log(1-_rng()) / _log_p) + 1;
  }

#ifndef BOOST_NO_OPERATORS_IN_NAMESPACE
  friend bool operator==(const geometric_distribution& x, 
			 const geometric_distribution& y)
  { return x._log_p == y._log_p && x._rng == y._rng; }
#else
  // Use a member function
  bool operator==(const geometric_distribution& rhs) const
  { return _log_p == rhs._log_p && _rng == rhs._rng;  }
#endif
private:
  uniform_01<base_type> _rng;
  typename uniform_01<base_type>::result_type _log_p;
};


// triangle distribution, with a smallest, b most probable, and c largest
// value.
template<class UniformRandomNumberGenerator, class RealType = double>
class triangle_distribution
  : public generator_iterator_mixin_adapter<
      triangle_distribution<UniformRandomNumberGenerator, RealType>, RealType>
{
public:
  typedef UniformRandomNumberGenerator base_type;
  typedef RealType result_type;
  triangle_distribution(base_type & rng, result_type a, result_type b,
			result_type c)
    : _rng(rng), _a(a), _b(b), _c(c),
      d1(_b-_a), d2(_c-_a), d3(_c-_b), q1(d1/d2), p1(d1*d2)
  {
    d3 = sqrt(d3);
    p1 = sqrt(p1);
    assert(_a <= _b && _b <= _c);
    iterator_init();
  }
  // compiler-generated copy ctor is fine
  // uniform_01 cannot be assigned, neither can this class
  result_type operator()() {
    using std::sqrt;
    result_type u = _rng();
    if( u <= q1 )
      return _a + p1*sqrt(u);
    else
      return _c - d3*sqrt(d2*u-d1);
  }
#ifndef BOOST_NO_OPERATORS_IN_NAMESPACE
  friend bool operator==(const triangle_distribution& x, 
			 const triangle_distribution& y)
  { return x._a == y._a && x._b == y._b && x._c == y._c && x._rng == y._rng; }
#else
  // Use a member function
  bool operator==(const triangle_distribution& rhs) const
  { return _a == rhs._a && _b == rhs._b && _c == rhs._c && _rng == rhs._rng;  }
#endif
private:
  uniform_01<base_type, result_type> _rng;
  result_type _a, _b, _c;
  result_type d1, d2, d3, q1, p1;
};


// exponential distribution: p(x) = lambda * exp(-lambda * x)
template<class UniformRandomNumberGenerator, class RealType = double>
class exponential_distribution
  : public generator_iterator_mixin_adapter<
    exponential_distribution<UniformRandomNumberGenerator, RealType>, RealType>
{
public:
  typedef UniformRandomNumberGenerator base_type;
  typedef RealType result_type;

  exponential_distribution(base_type& rng, result_type lambda)
    : _rng(rng), _lambda(lambda) { assert(lambda > 0); iterator_init(); }
  // compiler-generated copy ctor is fine
  // uniform_01 cannot be assigned, neither can this class
  result_type operator()() { 
    using std::log;
    return -1.0 / _lambda * log(1-_rng());
  }

#ifndef BOOST_NO_OPERATORS_IN_NAMESPACE
  friend bool operator==(const exponential_distribution& x, 
			 const exponential_distribution& y)
  { return x._lambda == y._lambda && x._rng == y._rng; }
#else
  // Use a member function
  bool operator==(const exponential_distribution& rhs) const
  { return _lambda == rhs._lambda && _rng == rhs._rng;  }
#endif
private:
  uniform_01<base_type, RealType> _rng;
  const result_type _lambda;
};


// Cauchy distribution: p(x) = sigma/(pi*(sigma**2 + (x-median)**2))
template<class UniformRandomNumberGenerator, class RealType = double>
class cauchy_distribution
  : public generator_iterator_mixin_adapter<
      cauchy_distribution<UniformRandomNumberGenerator, RealType>, RealType>
{
public:
  typedef UniformRandomNumberGenerator base_type;
  typedef RealType result_type;

  cauchy_distribution(base_type & rng, result_type median = 0, 
		      result_type sigma = 1)
    : _rng(rng), _median(median), _sigma(sigma) { iterator_init(); }
  // compiler-generated copy constructor is fine
  // uniform_01 cannot be assigned, neither can this class
  result_type operator()()
  {
    const double pi = 3.14159265358979323846;
    using std::tan;
    return _median + _sigma * tan(pi*(_rng()-0.5));
  }
#ifndef BOOST_NO_OPERATORS_IN_NAMESPACE
  friend bool operator==(const cauchy_distribution& x, 
			 const cauchy_distribution& y)
  {
    return x._median == y._median && x._sigma == y._sigma && x._rng == y._rng; 
  }
#else
  // Use a member function
  bool operator==(const cauchy_distribution& rhs) const
  {
    return _median == rhs._median && _sigma == rhs._sigma && _rng == rhs._rng;
  }
#endif
private:
  uniform_01<base_type, result_type> _rng;
  result_type _median, _sigma;
};

// deterministic polar method, uses trigonometric functions
template<class UniformRandomNumberGenerator, class RealType = double>
class normal_distribution
  : public generator_iterator_mixin_adapter<
      normal_distribution<UniformRandomNumberGenerator, RealType>, RealType>
{
public:
  typedef UniformRandomNumberGenerator base_type;
  typedef RealType result_type;

  explicit normal_distribution(base_type & rng, const result_type& mean = 0,
			       const result_type& sigma = 1)
    : _rng(rng), _mean(mean), _sigma(sigma), _valid(false)
  { assert(sigma > 0); iterator_init(); }
  // compiler-generated copy constructor is fine
  // uniform_01 cannot be assigned, neither can this class
  result_type operator()()
  {
    // allow for Koenig lookup
    using std::sqrt; using std::log; using std::sin; using std::cos;
    if(!_valid) {
      _r1 = _rng();
      _r2 = _rng();
      _cached_rho = sqrt(-2 * log(1.0-_r2));
      _valid = true;
    } else {
      _valid = false;
    }
    // Can we have a boost::mathconst please?
    const double pi = 3.14159265358979323846;
    
    return _cached_rho * (_valid ? cos(2*pi*_r1) : sin(2*pi*_r1)) * _sigma +
      _mean;
  }
#ifndef BOOST_NO_OPERATORS_IN_NAMESPACE
  friend bool operator==(const normal_distribution& x, 
			 const normal_distribution& y)
  {
    return x._mean == y._mean && x._sigma == y._sigma && 
      x._valid == y._valid && x._rng == y._rng;
  }
#else
  // Use a member function
  bool operator==(const normal_distribution& rhs) const
  {
    return _mean == rhs._mean && _sigma == rhs._sigma && 
      _valid == rhs._valid && _rng == rhs._rng;
  }
#endif
private:
  uniform_01<base_type, RealType> _rng;
  const result_type _mean, _sigma;
  result_type _r1, _r2, _cached_rho;
  bool _valid;
};

template<class UniformRandomNumberGenerator, class RealType = double>
class lognormal_distribution
  : public generator_iterator_mixin_adapter<
      lognormal_distribution<UniformRandomNumberGenerator, RealType>, RealType>
{
public:
  typedef UniformRandomNumberGenerator base_type;
  typedef RealType result_type;
  lognormal_distribution(base_type & rng, result_type mean, 
			 result_type sigma)
    : _rng(rng, std::log(mean*mean/std::sqrt(sigma*sigma + mean*mean)),
	   std::sqrt(std::log(sigma*sigma/mean/mean+1)))
  { 
    assert(mean > 0);
    iterator_init();
  }
  // compiler-generated copy constructor is fine
  // normal_distribution cannot be assigned, neither can this class
  result_type operator()() {
    // allow for Koenig lookup
    using std::exp;
    return exp(_rng());
  }

#ifndef BOOST_NO_OPERATORS_IN_NAMESPACE
  friend bool operator==(const lognormal_distribution& x, 
			 const lognormal_distribution& y)
  { return x._rng == y._rng; }
#else
  // Use a member function
  bool operator==(const lognormal_distribution& rhs) const
  { return _rng == rhs._rng;  }
#endif
private:
  normal_distribution<base_type, result_type> _rng;
};

template<class UniformRandomNumberGenerator, class RealType = double,
   class Cont = std::vector<RealType> >
class uniform_on_sphere
  : public generator_iterator_mixin_adapter<
      uniform_on_sphere<UniformRandomNumberGenerator, RealType, Cont>,
      std::vector<RealType> >
{
public:
  typedef UniformRandomNumberGenerator base_type;
  typedef Cont result_type;

  explicit uniform_on_sphere(base_type & rng, int dim = 2)
    : _rng(rng), _container(dim), _dim(dim) { iterator_init(); }
  // compiler-generated copy ctor is fine
  // normal_distribution cannot be assigned, neither can this class
  const result_type & operator()()
  {
    RealType sqsum = 0;
    for(typename Cont::iterator it = _container.begin();
	it != _container.end();
	++it) {
      RealType val = _rng();
      *it = val;
      sqsum += val * val;
    }
    using std::sqrt;
    // for all i: result[i] /= sqrt(sqsum)
    std::transform(_container.begin(), _container.end(), _container.begin(),
		   std::bind2nd(std::divides<RealType>(), sqrt(sqsum)));
    return _container;
  }

#ifndef BOOST_NO_OPERATORS_IN_NAMESPACE
  friend bool operator==(const uniform_on_sphere& x, 
			 const uniform_on_sphere& y)
  { return x._dim == y._dim && x._rng == y._rng; }
#else
  // Use a member function
  bool operator==(const uniform_on_sphere& rhs) const
  { return _dim == rhs._dim && _rng == rhs._rng; }
#endif
private:
  normal_distribution<base_type, RealType> _rng;
  result_type _container;
  const int _dim;
};

} // namespace boost

#endif // BOOST_RANDOM_HPP
