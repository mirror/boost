/*
 * Distributed under the Boost Software License, Version 1.0.(See accompanying 
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)
 * 
 * See http://www.boost.org/libs/iostreams for documentation.
 *
 * File:        boost/iostreams/detail/file_times.hpp
 * Date:        Sun Jun 22 14:23:12 MDT 2008
 * Copyright:   Jorge Lodos and 2008 CodeRage, LLC
 * Author:      Jorge Lodos and Jonathan Turkanis
 * Contact:     turkanis at coderage dot com
 *
 * Declares functions for accessing and manipulating timestamps associated
 * with a file descriptor.
 */

#ifndef BOOST_IOSTREAMS_DETAIL_FILE_TIMES_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_FILE_TIMES_HPP_INCLUDED

#include <ctime>
#include <boost/iostreams/detail/file_handle.hpp>

namespace boost { namespace iostreams { namespace detail {

// Returns the last access time of the file associated with the given handle.
// Reports errors by throwing instances of std::failure.
std::time_t last_read_time(file_handle);

// Sets the last access time of the file associated with the given handle.
// Reports errors by throwing instances of std::failure.
void set_last_read_time(file_handle, std::time_t);

// Returns the last modification time of the file associated with the given 
// handle. Reports errors by throwing instances of std::failure.
std::time_t last_write_time(file_handle);

// Sets the last modification time of the file associated with the given 
// handle. Reports errors by throwing instances of std::failure.
void set_last_write_time(file_handle, std::time_t);

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_FILE_TIMES_HPP_INCLUDED
