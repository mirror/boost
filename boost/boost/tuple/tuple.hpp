//  tuple.hpp - Boost Tuple Library --------------------------------------

// Copyright (C) 1999, 2000 Jaakko Järvi (jaakko.jarvi@cs.utu.fi)
//
// Permission to copy, use, sell and distribute this software is granted
// provided this copyright notice appears in all copies. 
// Permission to modify the code and to distribute modified code is granted
// provided this copyright notice appears in all copies, and a notice 
// that the code was modified is included with the copyright notice.
//
// This software is provided "as is" without express or implied warranty, 
// and with no claim as to its suitability for any purpose.

// For more information, see http://www.boost.org

// ----------------------------------------------------------------- 

#ifndef BOOST_TUPLE_HPP
#define BOOST_TUPLE_HPP

#include "boost/config.hpp"
#include "boost/static_assert.hpp"

#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
// The MSVC version
#include "boost/tuple/detail/tuple_basic_no_partial_spec.hpp"

#else
// other compilers
#include "boost/tuple/reference_wrappers.hpp"
#include "boost/tuple/detail/tuple_basic.hpp"

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION


#endif	// BOOST_TUPLE_HPP
