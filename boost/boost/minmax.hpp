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

namespace boost
{

template< typename T >
inline T const & std_min( T const & a, T const & b )
{
#if defined(__COMO__) || defined(BOOST_INTEL) || defined(BOOST_NO_STD_MIN_MAX)
    using std::min;
#elif defined(BOOST_NO_STDC_NAMESPACE)
    using ::min;
#else
    using std::min;
#endif

    return min BOOST_PREVENT_MACRO_SUBSTITUTION ( a, b );
}

template< typename T >
inline T const & std_max( T const & a, T const & b )
{
#if defined(__COMO__) || defined(BOOST_INTEL) || defined(BOOST_NO_STD_MIN_MAX)
    using std::max;
#elif defined(BOOST_NO_STDC_NAMESPACE)
    using ::max;
#else
    using std::max;
#endif

    return max BOOST_PREVENT_MACRO_SUBSTITUTION ( a, b );
}

}

#endif // BOOST_MINMAX_HPP
