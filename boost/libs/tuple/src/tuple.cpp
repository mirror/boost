//  tuple.cpp -----------------------------------------------------

// Copyright (C) 1999, 2000, 2001 Jaakko Järvi (jaakko.jarvi@cs.utu.fi)
// Copyright (C) 2001 Gary Powell (gary.powell@sierra.com)
//
// Permission to copy, use, sell and distribute this software is granted
// provided this copyright notice appears in all copies. 
// Permission to modify the code and to distribute modified code is granted
// provided this copyright notice appears in all copies, and a notice 
// that the code was modified is included with the copyright notice.
//
// This software is provided "as is" without express or implied warranty, 
// and with no claim as to its suitability for any purpose.

// For more information, see http://lambda.cs.utu.fi 

// Revision History 

// 16 02 01 Initial Version (GWP)
// ----------------------------------------------------------------- 

#include "boost/tuple/tuple_io.hpp"

namespace boost {
namespace detail {
namespace tuples {
const int
 format_info::stream_index[number_of_manipulators] 
   = { std::ios::xalloc(), std::ios::xalloc(), std::ios::xalloc() };
   
} // namespace tuples   
} // namespace detail
} // namespace boost
