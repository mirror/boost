// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_ADAPT_HPP_INCLUDED
#define BOOST_IOSTREAMS_ADAPT_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/iostreams/detail/adapter/unary_adapter.hpp>
#include <boost/iostreams/detail/adapter/binary_adapter.hpp>
#include <boost/iostreams/detail/enable_if_stream.hpp>
#include <boost/iostreams/detail/wrap_unwrap.hpp>

namespace boost { namespace iostreams {

//------------------Definition of adapt---------------------------------------//

template<typename T>
detail::unary_adapter<typename detail::wrapped_type<T>::type> 
adapt(const T& t BOOST_IOSTREAMS_DISABLE_IF_STREAM(T))
{   
    typedef typename detail::wrapped_type<T>::type wrapped_type;
    return detail::unary_adapter<wrapped_type>(detail::wrap(t)); 
}

template<typename T>
detail::unary_adapter<typename detail::wrapped_type<T>::type> 
adapt(T& t BOOST_IOSTREAMS_ENABLE_IF_STREAM(T))
{ 
    typedef typename detail::wrapped_type<T>::type wrapped_type;
    return detail::unary_adapter<wrapped_type>(detail::wrap(t)); 
}

template<typename Iter>
detail::binary_adapter<Iter> adapt(const Iter& first, const Iter& last)
{ return detail::binary_adapter<Iter>(first, last); }

//----------------------------------------------------------------------------//

} } // End namespaces iostreams, boost.

#endif // BOOST_IOSTREAMS_ADAPT_HPP_INCLUDED
