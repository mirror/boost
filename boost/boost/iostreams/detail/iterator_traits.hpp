// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_ITERATOR_TRAITS_HPP_INCLUDED
#define BOOST_IOSTREAMS_ITERATOR_TRAITS_HPP_INCLUDED      

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif               
 
#include <boost/config.hpp>                         // partial spec.
#include <boost/iostreams/detail/ios_traits.hpp> 
#include <boost/iterator/iterator_categories.hpp> 
#include <boost/iterator/iterator_traits.hpp> 
#include <boost/mpl/eval_if.hpp>          
          
namespace boost { namespace iostreams { namespace detail {

template<typename T>
struct iter_val {

    template<typename U>
    struct container_value {
        typedef typename U::container_type           container_type;
        typedef typename container_type::value_type  type;
    };

    typedef typename 
            mpl::eval_if<
                is_back_inserter<T>,
                container_value<T>,
                iterator_value<T>
            >::type type;
};

#ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

template<> struct iter_val<char*> { typedef char type; };
template<> struct iter_val<const char*> { typedef char type; };
template<> struct iter_val<wchar_t*> { typedef wchar_t type; };
template<> struct iter_val<const wchar_t*> { typedef wchar_t type; };

#endif          // #ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_ITERATOR_TRAITS_HPP_INCLUDED
