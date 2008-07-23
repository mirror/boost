//  boost Issue #2134 test program  ------------------------------------------//

//  Copyright Daryle Walker 2008.  Distributed under the Boost
//  Software License, Version 1.0. (See the accompanying file
//  LICENSE_1_0.txt or a copy at <http://www.boost.org/LICENSE_1_0.txt>.)

//  See <http://www.boost.org/libs/integer> for documentation.
//  See <http://svn.boost.org/trac/boost/ticket/2134> for the issue involved.

//  Revision History
//   23 Jul 2008  Initial version

// Control if the inclusion error is triggered
#ifndef CONTROL_INCLUDE_TRAITS
#define CONTROL_INCLUDE_TRAITS  1
#endif

#if CONTROL_INCLUDE_TRAITS
// This file defines boost::detail::integer_traits.
#include <boost/detail/numeric_traits.hpp>
#endif

// This is the file with the issue.  It has items within the boost::detail
// namespace that referenced an unadorned "integer_traits".  This was meant to
// refer to boost::integer_traits.  However, <boost/detail/numeric_traits.hpp>
// defines a boost::detail::integer_traits.  If that header is #included before
// this one, then b.d.integer_traits (rightfully) took priority, which lead to a
// syntax error.
#include <boost/integer.hpp>


// Main program, minimal (since this is a compile test)
int  main()  { return 0; }
