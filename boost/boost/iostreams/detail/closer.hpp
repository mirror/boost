// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_CLOSER_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CLOSER_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif              

#include <exception>                            // exception.
#include <boost/iostreams/detail/openmode.hpp>
#include <boost/iostreams/operations.hpp>       // close.

namespace boost { namespace iostreams { namespace detail {

template<typename T>
struct closer {
    closer(T& t) : t_(&t) { }
    ~closer() { try { t_->close(); } catch (std::exception&) { } }
    T* t_;
};

template<typename T>
struct external_closer {
    external_closer(T& t, std::ios::openmode mode) 
        : t_(&t), mode_(mode) 
        { }
    ~external_closer() 
    { 
        try { 
            boost::iostreams::close(*t_, mode_); 
        } catch (std::exception&) { } 
    }
    T* t_;
    std::ios::openmode  mode_;
};

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CLOSER_HPP_INCLUDED
