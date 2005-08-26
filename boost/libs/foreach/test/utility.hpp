///////////////////////////////////////////////////////////////////////////////
// utility.hpp header file
//
// Copyright 2005 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_FOREACH_TEST_UTILITY_HPP
#define BOOST_FOREACH_TEST_UTILITY_HPP

#include <boost/config.hpp>
#include "../../../boost/foreach.hpp"

///////////////////////////////////////////////////////////////////////////////
// sequence_equal_byval
inline bool sequence_equal_byval( container_type & rng, char const * result )
{
    BOOST_FOREACH( value_type i, rng )
    {
        if(0 == *result || i != *result)
            return false;
        ++result;
    }
    return 0 == *result;
}

///////////////////////////////////////////////////////////////////////////////
// sequence_equal_byval
inline bool sequence_equal_byval( const_container_type & rng, char const * result )
{
    BOOST_FOREACH( value_type i, rng )
    {
        if(0 == *result || i != *result)
            return false;
        ++result;
    }
    return 0 == *result;
}

///////////////////////////////////////////////////////////////////////////////
// sequence_equal_byref
inline bool sequence_equal_byref( container_type & rng, char const * result )
{
    BOOST_FOREACH( reference_type i, rng )
    {
        if(0 == *result || i != *result)
            return false;
        ++result;
    }
    return 0 == *result;
}

///////////////////////////////////////////////////////////////////////////////
// sequence_equal_byref
inline bool sequence_equal_byref( const_container_type & rng, char const * result )
{
    BOOST_FOREACH( const_reference_type i, rng )
    {
        if(0 == *result || i != *result)
            return false;
        ++result;
    }
    return 0 == *result;
}

///////////////////////////////////////////////////////////////////////////////
// mutate_foreach_byref
//
inline void mutate_foreach_byref( container_type & rng )
{
    BOOST_FOREACH( reference_type i, rng )
    {
        ++i;
    }
}

#endif
