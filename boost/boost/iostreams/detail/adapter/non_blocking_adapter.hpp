// (C) Copyright Jonathan Turkanis 2005.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_NON_BLOCKING_ADAPTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_NON_BLOCKING_ADAPTER_HPP_INCLUDED

#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/call_traits.hpp>
#include <boost/iostreams/detail/ios.hpp>
#include <boost/iostreams/operations.hpp>
#include <boost/iostreams/traits.hpp>

namespace boost { namespace iostreams { namespace detail {

template<typename Device>
class non_blocking_adapter {
private:
    typedef typename detail::value_type<Device>::type  value_type;
public:
    typedef typename io_char<Device>::type             char_type;
    struct io_category
        : io_mode<Device>::type, device_tag
        { };
    explicit non_blocking_adapter(Device& dev) : device_(dev) { }
    std::streamsize read(char_type* s, std::streamsize n)
    { 
        std::streamsize result = 0;
        while (result < n) {
            std::streamsize amt = iostreams::read(device_, s, n);
            if (amt == -1)
                break;
            result += amt;
        }
        return result != 0 ? result : -1;
    }
    std::streamsize write(const char_type* s, std::streamsize n)
    { 
        std::streamsize result = 0;
        while (result < n) {
            std::streamsize amt = 
                iostreams::write(device_, s + result, n - result);
            result += amt;
        }
        return result;    
    }
    stream_offset seek( stream_offset off, BOOST_IOS::seekdir way,
                        BOOST_IOS::openmode which = 
                            BOOST_IOS::in | BOOST_IOS::out )
    { return iostreams::seek(device_, off, way, which); }
public:
    value_type device_;
};

//----------------------------------------------------------------------------//

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_NON_BLOCKING_ADAPTER_HPP_INCLUDED
