// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_ERROR_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_ERROR_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif              
                 
#include <ios> // failure.

namespace boost { namespace iostreams { namespace detail {

inline std::ios::failure cant_read() 
{ return std::ios::failure("no read access"); }

inline std::ios::failure cant_write() 
{ return std::ios::failure("no write access"); }

inline std::ios::failure cant_seek() 
{ return std::ios::failure("no random access"); }

inline std::ios::failure bad_read() 
{ return std::ios::failure("bad read"); }

inline std::ios::failure bad_putback() 
{ return std::ios::failure("putback buffer full"); }

inline std::ios::failure bad_write() 
{ return std::ios::failure("bad write"); }

inline std::ios::failure write_area_exhausted() 
{ return std::ios::failure("write area exhausted"); }

inline std::ios::failure bad_seek() 
{ return std::ios::failure("bad seek"); }

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_ERROR_HPP_INCLUDED
