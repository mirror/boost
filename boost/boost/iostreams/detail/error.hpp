// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_ERROR_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_ERROR_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif              
                 
#include <boost/iostreams/detail/failure.hpp>

namespace boost { namespace iostreams { namespace detail {

inline failure cant_read() { return failure("no read access"); }

inline failure cant_write() { return failure("no write access"); }

inline failure cant_seek() { return failure("no random access"); }

inline failure bad_read() { return failure("bad read"); }

inline failure bad_putback() { return failure("putback buffer full"); }

inline failure bad_write() { return failure("bad write"); }

inline failure write_area_exhausted() 
{ return failure("write area exhausted"); }

inline failure bad_seek() { return failure("bad seek"); }

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_ERROR_HPP_INCLUDED
