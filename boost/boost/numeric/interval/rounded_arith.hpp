/* Boost interval/rounded_arith.hpp template implementation file
 *
 * Copyright Jens Maurer 2000
 * Copyright Hervé Brönnimann, Guillaume Melquiond, Sylvain Pion 2002
 * Permission to use, copy, modify, sell, and distribute this software
 * is hereby granted without fee provided that the above copyright notice
 * appears in all copies and that both that copyright notice and this
 * permission notice appear in supporting documentation,
 *
 * None of the above authors nor Polytechnic University make any
 * representation about the suitability of this software for any
 * purpose. It is provided "as is" without express or implied warranty.
 *
 * $Id$
 *
 * Revision history:
 *   2002-08-31	 Prepared for boost formal review
 *   2000-09-24	 Separated from interval.hpp
 */

#ifndef BOOST_NUMERIC_INTERVAL_ROUNDED_ARITH_HPP
#define BOOST_NUMERIC_INTERVAL_ROUNDED_ARITH_HPP

#include <boost/numeric/interval/rounding.hpp>
#include <boost/numeric/interval/detail/bugs.hpp>
#include <cmath>

namespace boost {
namespace numeric {
namespace interval_lib {

/*
 * Three classes of rounding: exact, std, opp
 * See documentation for details.
 */

template<class T, class Rounding>
struct rounded_arith_exact: Rounding {
  void init() { }
  T add_down (const T& x, const T& y) { return x + y; }
  T add_up   (const T& x, const T& y) { return x + y; }
  T sub_down (const T& x, const T& y) { return x - y; }
  T sub_up   (const T& x, const T& y) { return x - y; }
  T mul_down (const T& x, const T& y) { return x * y; }
  T mul_up   (const T& x, const T& y) { return x * y; }
  T div_down (const T& x, const T& y) { return x / y; }
  T div_up   (const T& x, const T& y) { return x / y; }
  T median   (const T& x, const T& y) { return (x + y) / 2; }
  T sqrt_down(const T& x)
  { BOOST_NUMERIC_INTERVAL_using_math(sqrt); return sqrt(x); }
  T sqrt_up  (const T& x)
  { BOOST_NUMERIC_INTERVAL_using_math(sqrt); return sqrt(x); }
  T int_down (const T& x)
  { BOOST_NUMERIC_INTERVAL_using_math(floor); return floor(x); }
  T int_up   (const T& x)
  { BOOST_NUMERIC_INTERVAL_using_math(ceil); return ceil(x); }
};

template<class T, class Rounding>
struct rounded_arith_std: Rounding {
  #define BOOST_DN(EXPR) (downward(),   force_rounding( EXPR ))
  #define BOOST_NR(EXPR) (to_nearest(), force_rounding( EXPR ))
  #define BOOST_UP(EXPR) (upward(),     force_rounding( EXPR ))
  void init() { }
  T add_down (const T& x, const T& y) { return BOOST_DN( x + y        ); }
  T add_up   (const T& x, const T& y) { return BOOST_UP( x + y        ); }
  T sub_down (const T& x, const T& y) { return BOOST_DN( x - y        ); }
  T sub_up   (const T& x, const T& y) { return BOOST_UP( x - y        ); }
  T mul_down (const T& x, const T& y) { return BOOST_DN( x * y        ); }
  T mul_up   (const T& x, const T& y) { return BOOST_UP( x * y        ); }
  T div_down (const T& x, const T& y) { return BOOST_DN( x / y        ); }
  T div_up   (const T& x, const T& y) { return BOOST_UP( x / y        ); }
  T median   (const T& x, const T& y) { return BOOST_NR( (x+y)/2      ); }
  T sqrt_down(const T& x)             { BOOST_NUMERIC_INTERVAL_using_math(sqrt);
                                        return BOOST_DN( sqrt(x) ); }
  T sqrt_up  (const T& x)             { BOOST_NUMERIC_INTERVAL_using_math(sqrt);
				        return BOOST_UP( sqrt(x) ); }
  T int_down (const T& x)             { return BOOST_DN( to_int(x)    ); }
  T int_up   (const T& x)             { return BOOST_UP( to_int(x)    ); }
  #undef BOOST_DN
  #undef BOOST_NR
  #undef BOOST_UP
};
  
template<class T, class Rounding>
struct rounded_arith_opp: Rounding {
  void init() { upward(); }
  #define BOOST_DN(EXPR) (downward(),   force_rounding( EXPR ))
  #define BOOST_NR(EXPR) (to_nearest(), force_rounding( EXPR ))
  #define BOOST_UP(EXPR)                force_rounding( EXPR )
  T add_down (const T& x, const T& y) { return -BOOST_UP( (-x) - y ); }
  T add_up   (const T& x, const T& y) { return  BOOST_UP( x + y    ); }
  T sub_down (const T& x, const T& y) { return -BOOST_UP( y - x    ); }
  T sub_up   (const T& x, const T& y) { return  BOOST_UP( x - y    ); }
  T mul_down (const T& x, const T& y) { return -BOOST_UP( x * (-y) ); }
  T mul_up   (const T& x, const T& y) { return  BOOST_UP( x * y    ); }
  T div_down (const T& x, const T& y) { return -BOOST_UP( x / (-y) ); }
  T div_up   (const T& x, const T& y) { return  BOOST_UP( x / y    ); }
  T median   (const T& x, const T& y) { T r =   BOOST_NR( (x + y) / 2 );
                                        upward();
                                        return r;
                                      }
  T sqrt_down(const T& x)             { BOOST_NUMERIC_INTERVAL_using_math(sqrt);
    				        T r = BOOST_DN ( sqrt(x) );
                                        upward();
                                        return r;
				      }
  T sqrt_up  (const T& x)             { BOOST_NUMERIC_INTERVAL_using_math(sqrt);
	    				return  BOOST_UP( sqrt(x) ); }
  T int_down (const T& x)             { return -to_int(-x); }
  T int_up   (const T& x)             { return to_int(x); }
  #undef BOOST_DN
  #undef BOOST_NR
  #undef BOOST_UP
};

} // namespace interval_lib
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_INTERVAL_ROUNDED_ARITH_HPP
