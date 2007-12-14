/*
 * Distributed under the Boost Software License, Version 1.0.(See accompanying 
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)
 * 
 * See http://www.boost.org/libs/iostreams for documentation.

 * File:        boost/iostreams/detail/functional.hpp
 * Date:        Sun Dec 09 05:38:03 MST 2007
 * Copyright:   2007 CodeRage
 * Author:      Jonathan Turkanis

 * Defines several function objects and object generators for use with 
 * execute_all()
 */

#ifndef BOOST_IOSTREAMS_DETAIL_FUNCTIONAL_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_FUNCTIONAL_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/iostreams/close.hpp>
#include <boost/iostreams/detail/ios.hpp> // BOOST_IOS

namespace boost { namespace iostreams { namespace detail {

    // Function objects and object generators for invoking
    // boost::iostreams::close

template<typename T>
struct device_close_operation {
    typedef void result_type;
    device_close_operation(T& t, BOOST_IOS::openmode which) 
        : t(t), which(which) 
        { }
    void operator()() const { boost::iostreams::close(t, which); }
    T&                   t;
    BOOST_IOS::openmode  which;
};

template<typename T, typename Sink>
struct filter_close_operation {
    typedef void result_type;
    filter_close_operation(T& t, Sink& snk, BOOST_IOS::openmode which)
        : t(t), snk(snk), which(which)
        { }
    void operator()() const { boost::iostreams::close(t, snk, which); }
    T&                   t;
    Sink&                snk;
    BOOST_IOS::openmode  which;
};

template<typename T>
device_close_operation<T> 
call_close(T& t, BOOST_IOS::openmode which) 
{ return device_close_operation<T>(t, which); }

template<typename T, typename Sink>
filter_close_operation<T, Sink> 
call_close(T& t, Sink& snk, BOOST_IOS::openmode which) 
{ return filter_close_operation<T, Sink>(t, snk, which); }

    // Function objects and object generators for invoking
    // boost::iostreams::detail::close_all

template<typename T>
struct device_close_all_operation {
    typedef void result_type;
    device_close_all_operation(T& t) : t(t) { }
    void operator()() const { detail::close_all(t); }
    T& t;
};

template<typename T, typename Sink>
struct filter_close_all_operation {
    typedef void result_type;
    filter_close_all_operation(T& t, Sink& snk) : t(t), snk(snk) { }
    void operator()() const { detail::close_all(t, snk); }
    T&     t;
    Sink&  snk;
};

template<typename T>
device_close_all_operation<T> call_close_all(T& t) 
{ return device_close_all_operation<T>(t); }

template<typename T, typename Sink>
filter_close_all_operation<T, Sink> 
call_close_all(T& t, Sink& snk) 
{ return filter_close_all_operation<T, Sink>(t, snk); }

    // Function object and object generator for invoking a
    // member function void close(std::ios_base::openmode)

template<typename T>
struct member_close_operation {
    typedef void result_type;
    member_close_operation(T& t, BOOST_IOS::openmode which) 
        : t(t), which(which) 
        { }
    void operator()() const { t.close(which); }
    T&                   t;
    BOOST_IOS::openmode  which;
};

template<typename T>
member_close_operation<T> call_member_close(T& t, BOOST_IOS::openmode which) 
{ return member_close_operation<T>(t, which); }

    // Function object and object generator for invoking a
    // member function void reset()

template<typename T>
struct reset_operation {
    reset_operation(T& t) : t(t) { }
    void operator()() const { t.reset(); }
    T& t;
};

template<typename T>
reset_operation<T> call_reset(T& t) { return reset_operation<T>(t); }

    // Function object and object generator for clearing a flag

template<typename T>
struct clear_flags_operation {
    typedef void result_type;
    clear_flags_operation(T& t) : t(t) { }
    void operator()() const { t = 0; }
    T& t;
};

template<typename T>
clear_flags_operation<T> clear_flags(T& t) 
{ return clear_flags_operation<T>(t); }

    // Function object and generator for flushing a buffer

// Function object for use with execute_all()
template<typename Buffer, typename Device>
struct flush_buffer_operation {
    typedef void result_type;
    flush_buffer_operation(Buffer& buf, Device& dev, bool flush)
        : buf(buf), dev(dev), flush(flush)
        { }
    void operator()() const
    {
        if (flush) 
            buf.flush(dev);
    }
    Buffer&  buf;
    Device&  dev;
    bool     flush;
};

template<typename Buffer, typename Device>
flush_buffer_operation<Buffer, Device> 
flush_buffer(Buffer& buf, Device& dev, bool flush)
{ return flush_buffer_operation<Buffer, Device>(buf, dev, flush); }

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_FUNCTIONAL_HPP_INCLUDED
