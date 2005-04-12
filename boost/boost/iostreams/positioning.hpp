// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Thanks to Gareth Sylvester-Bradley for the Dinkumware versions of the
// positioning functions.

#ifndef BOOST_IOSTREAMS_POSITIONING_HPP_INCLUDED
#define BOOST_IOSTREAMS_POSITIONING_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/cstdint.hpp>
#include <boost/iostreams/detail/config/codecvt.hpp> // mbstate_t.
#include <boost/iostreams/detail/ios.hpp> // streamoff, streampos.

namespace boost { namespace iostreams {

typedef boost::intmax_t stream_offset;

#if (defined(_YVALS) && !defined(__IBMCPP__)) //------------------------------//

inline std::streampos offset_to_position(stream_offset off)
{
    // use implementation-specific constructor
    return std::streampos(std::mbstate_t(), off);
}

#if defined(_POSIX_)
#error
#endif

inline stream_offset fpos_t_to_offset(fpos_t pos)
{
#if defined(_POSIX_) || (_INTEGRAL_MAX_BITS >= 64)
    return pos;
#else
    return _FPOSOFF(pos);
#endif
}

# if defined(_CPPLIB_VER) // Recent Dinkumware.

inline stream_offset position_to_offset(std::streampos pos)
{
    // use implementation-specific member function seekpos()
    return fpos_t_to_offset(pos.seekpos()) +
           stream_offset(std::streamoff(pos)) -
           stream_offset(std::streamoff(pos.seekpos()));
}

# else // Old Dinkumware.

inline stream_offset position_to_offset(std::streampos pos)
{
    // use implementation-specific member function seekpos()
    return fpos_t_to_offset(pos.get_fpos_t()) +
           stream_offset(std::streamoff(pos)) -
           stream_offset(std::streamoff(pos.get_fpos_t()));
}

# endif
#else // Dinkumware //--------------------------------------------------------//

inline std::streampos offset_to_position(stream_offset off) { return off; }

inline stream_offset position_to_offset(std::streampos pos) { return pos; }

#endif // Dinkumware //-------------------------------------------------------//

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_POSITIONING_HPP_INCLUDED
