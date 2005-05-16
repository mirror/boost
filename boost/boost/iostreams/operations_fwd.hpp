// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_OPERATIONS_FWD_HPP_INCLUDED
#define BOOST_IOSTREAMS_OPERATIONS_FWD_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <utility>                          // pair.
#include <boost/config.hpp>                 // DEDUCED_TYPENAME.
#include <boost/iostreams/detail/ios.hpp>
#include <boost/iostreams/positioning.hpp>  // stream_offset.
#include <boost/iostreams/traits.hpp>

namespace boost { namespace iostreams {

template<typename T>
struct operations;

namespace detail {

template<typename T> struct read_device_impl;
template<typename T> struct write_device_impl;
template<typename T> struct read_filter_impl;
template<typename T> struct write_filter_impl;
template<typename T> struct input_sequence_impl;
template<typename T> struct output_sequence_impl;
template<typename T> struct seek_impl;
template<typename T> struct close_impl;
template<typename T> struct flush_device_impl;
template<typename T> struct flush_filter_impl;
template<typename T> struct imbue_impl;
template<typename T> struct optimal_buffer_size_impl;

template<> struct read_device_impl<int> { typedef int type; };
template<> struct write_device_impl<int> { typedef int type; };
template<> struct read_filter_impl<int> { typedef int type; };
template<> struct write_filter_impl<int> { typedef int type; };
template<> struct input_sequence_impl<int> { typedef int type; };
template<> struct output_sequence_impl<int> { typedef int type; };
template<> struct seek_impl<int> { typedef int type; };
template<> struct close_impl<int> { typedef int type; };
template<> struct flush_device_impl<int> { typedef int type; };
template<> struct flush_filter_impl<int> { typedef int type; };
template<> struct imbue_impl<int> { typedef int type; };
template<> struct optimal_buffer_size_impl<int> { typedef int type; };

} // End namespace detail.

template<typename T>
typename io_int<T>::type get(T&);

template<typename T>
std::streamsize read(T&, typename io_char<T>::type*, std::streamsize);

template<typename T, typename Source>
std::streamsize read(T&, Source&, typename io_char<T>::type*, std::streamsize);

template<typename T>
bool putback(T&, typename io_char<T>::type);

template<typename T>
bool put(T&, typename io_char<T>::type);

template<typename T>
std::streamsize write(T&, const typename io_char<T>::type*, std::streamsize);

template<typename T, typename Sink>
std::streamsize write(T&, Sink&, const typename io_char<T>::type*, std::streamsize);

template<typename T>
std::streampos seek( T& t, stream_offset off, BOOST_IOS::seekdir way,
                     BOOST_IOS::openmode which = BOOST_IOS::in | BOOST_IOS::out );

template<typename T>
std::pair<
    BOOST_DEDUCED_TYPENAME io_char<T>::type*,
    BOOST_DEDUCED_TYPENAME io_char<T>::type*
>
input_sequence(T&);

template<typename T>
std::pair<
    BOOST_DEDUCED_TYPENAME io_char<T>::type*,
    BOOST_DEDUCED_TYPENAME io_char<T>::type*
>
output_sequence(T&);

template<typename T>
void close(T&, BOOST_IOS::openmode);

template<typename T, typename Sink>
void close(T&, Sink& snk, BOOST_IOS::openmode);

template<typename T>
bool flush(T&);

template<typename T, typename Sink>
bool flush(T&, Sink&);

template<typename T, typename Locale>
void imbue(T&, const Locale&);

template<typename T>
std::streamsize optimal_buffer_size(const T&);

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_OPERATIONS_FWD_HPP_INCLUDED //--------------//
