/* Boost test/bugs.hpp
 * Handles namespace resolution quirks in older compilers and braindead
 * warnings [Herve, June 3rd 2003]
 *
 * Copyright Herve Bronnimann2002-2003
 * Permission to use, copy, modify, sell, and distribute this software
 * is hereby granted without fee provided that the above copyright
 * notice appears in all copies and that both that copyright notice and
 * this permission notice appear in supporting documentation.
 *
 * None of the above authors nor Polytechnic University make any
 * representation about the suitability of this software for any
 * purpose. It is provided "as is" without express or implied warranty.
 *
 * $Id$
 */

// this should never hurt

namespace detail {

  template <class T> inline void ignore_unused_variable_warning(const T&) { }

  inline void ignore_warnings() {
#   ifdef BOOST_NUMERIC_INTERVAL_CONSTANTS_HPP
    using namespace boost::numeric::interval_lib::constants;
    detail::ignore_unused_variable_warning( pi_f_l );
    detail::ignore_unused_variable_warning( pi_f_u );
    detail::ignore_unused_variable_warning( pi_d_l );
    detail::ignore_unused_variable_warning( pi_d_u );
#   endif
  }

}

// this would never hurt in theory, unless some conflict occurs (which
// does not happen in this test suite...) but is not necessary unless the
// platform is really bad with namespace resolution

#if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)

using namespace boost;
using namespace numeric;
using namespace interval_lib;

#endif
