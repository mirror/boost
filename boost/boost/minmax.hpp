//  (C) Copyright Eric Niebler 2004.
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

/*
 Revision history:
   25 February 2004
      Initial version.
*/

#ifndef BOOST_MINMAX_HPP
#define BOOST_MINMAX_HPP

#include <algorithm> // for std::min and std::max
#include <boost/config.hpp>

#define BOOST_USING_STD_MIN()\
	using std::min

#define BOOST_USING_STD_MAX()\
	using std::max

#endif // BOOST_MINMAX_HPP
