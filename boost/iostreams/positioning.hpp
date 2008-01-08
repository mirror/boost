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

#include <boost/config.hpp>
#include <boost/cstdint.hpp>
#include <boost/integer_traits.hpp>
#include <boost/iostreams/detail/config/codecvt.hpp> // mbstate_t.
#include <boost/iostreams/detail/config/fpos.hpp>
#include <boost/iostreams/detail/ios.hpp> // streamoff, streampos.

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp> 

#ifdef BOOST_NO_STDC_NAMESPACE
namespace std { using ::fpos_t; }
#endif

namespace boost { namespace iostreams {
                    
//------------------Definition of stream_offset-------------------------------//

typedef boost::intmax_t stream_offset;

//------------------Definition of stream_offset_to_streamoff------------------//

inline std::streamoff stream_offset_to_streamoff(stream_offset off)
{ return static_cast<stream_offset>(off); }

//------------------Definition of offset_to_position--------------------------//

# ifndef BOOST_IOSTREAMS_HAS_DINKUMWARE_FPOS

inline std::streampos offset_to_position(stream_offset off) { return off; }

# else // # ifndef BOOST_IOSTREAMS_HAS_DINKUMWARE_FPOS

inline std::streampos offset_to_position(stream_offset off)
{ return std::streampos(std::mbstate_t(), off); }

# endif // # ifndef BOOST_IOSTREAMS_HAS_DINKUMWARE_FPOS

//------------------Definition of position_to_offset--------------------------//

// Hande custom pos_type's
template<typename PosType> 
inline stream_offset position_to_offset(PosType pos)
{ return std::streamoff(pos); }

# ifndef BOOST_IOSTREAMS_HAS_DINKUMWARE_FPOS

inline stream_offset position_to_offset(std::streampos pos) { return pos; }

# else // # ifndef BOOST_IOSTREAMS_HAS_DINKUMWARE_FPOS

// Helper function
inline stream_offset fpos_t_to_offset(std::fpos_t pos)
{
#  if defined(_POSIX_) || (_INTEGRAL_MAX_BITS >= 64)
    return pos;
#  else
    return _FPOSOFF(pos);
#  endif
}

// Helper function
inline std::fpos_t streampos_to_fpos_t(std::streampos pos)
{
#  ifdef _CPPLIB_VER
    return pos.seekpos();
#  else
    return pos.get_fpos_t();
#  endif
}

inline stream_offset position_to_offset(std::streampos pos)
{
    return fpos_t_to_offset(streampos_to_fpos_t(pos)) +
           static_cast<stream_offset>(static_cast<std::streamoff>(pos)) -
           static_cast<stream_offset>(_FPOSOFF(streampos_to_fpos_t(pos)));
}

# endif // # ifndef BOOST_IOSTREAMS_HAS_DINKUMWARE_FPOS 

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp> 

#endif // #ifndef BOOST_IOSTREAMS_POSITIONING_HPP_INCLUDED
