// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Forward declarations of templates defined in traits.hpp.

#ifndef BOOST_IOSTREAMS_IO_TRAITS_FWD_HPP_INCLUDED
#define BOOST_IOSTREAMS_IO_TRAITS_FWD_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif              

#include <iosfwd> // stream types, char_traits.

namespace boost { namespace iostreams {      

template<typename T>
struct is_istream;

template<typename T>
struct is_ostream;

template<typename T>
struct is_iostream;

template<typename T>
struct is_streambuf;

template<typename T>
struct is_stringstream;

template<typename T>
struct is_stringbuf;

template<typename T>
struct is_std_io;

template<typename T>
struct io_char;

template<typename T>
struct io_category;

template<typename T>
struct io_int;

template<typename T>
struct io_mode;

template<typename T>
struct is_device;

template<typename T>
struct is_filter;

template<typename T>
struct is_direct;

namespace detail {

template<typename T>
struct is_linked;

} // End namespace detail.

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_IO_TRAITS_FWD_HPP_INCLUDED
