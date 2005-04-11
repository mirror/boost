// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// To do: handle bidirection streams and output-seekable components.

#ifndef BOOST_IOSTREAMS_OPERATIONS_HPP_INCLUDED
#define BOOST_IOSTREAMS_OPERATIONS_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/iostreams/detail/ios.hpp> // streamoff, seekdir constants.
#include <boost/iostreams/operations.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost { namespace iostreams {

namespace detail {

template<typename Device>
std::streamoff skip(Device& dev, std::streamoff off, mpl::true_)
{ return iostreams::seek(dev, off, BOOST_IOS::cur); }

template<typename Device>
std::streamoff skip(Device& dev, std::streamoff off, mpl::false_)
{ 
    for (std::streamoff z = 0; z < off; ++z)
        iostreams::get(dev);
    return off;
}

template<typename Filter, typename Device>
std::streamoff skip(Filter& flt, Device& dev, std::streamoff off, mpl::true_)
{ return flt.seek(dev, off, BOOST_IOS::cur); }

template<typename Filter, typename Device>
std::streamoff skip(Filter& flt, Device& dev, std::streamoff off, mpl::false_)
{ 
    char c;
    for (std::streamoff z = 0; z < off; ++z)
        iostreams::read(flt, dev, &c, 1);
    return off;
}

} // End namespace detail.

template<typename Device>
std::streamoff skip(Device& dev, std::streamoff off)
{ 
    typedef typename io_mode<Device>::type mode;
    return detail::skip(dev, off, is_convertible<mode, seekable>());
}

template<typename Filter, typename Device>
std::streamoff skip(Filter& flt, Device& dev, std::streamoff off)
{ 
    typedef typename io_mode<Filter>::type                     filter_mode;
    typedef typename io_mode<Device>::type                     device_mode;
    typedef mpl::and_<
                is_convertible<filter_mode, output_seekable>,
                is_convertible<device_mode, output_seekable>
            >                                                  can_seek;
    return detail::skip(flt, dev, off, can_seek());
}

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_SKIP_HPP_INCLUDED //------------------------//
