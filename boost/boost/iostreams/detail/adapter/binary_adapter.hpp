// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_BINARY_ADAPTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_BINARY_ADAPTER_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif              

#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/adapter/range_adapter.hpp>
#include <boost/iostreams/detail/config/smart_adapter_support.hpp>
#include <boost/iostreams/detail/wrap_unwrap.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_pointer.hpp>

namespace boost { namespace iostreams {

namespace detail {

//------------------Definition of binary_adapter------------------------------//

// Deduces the return type of binary_adapter::resolve. 
// This definition is external to binary_adapter for Borland 5.x.
template<typename Mode, typename Ch, typename T>
struct binary_adapter_traits {
    typedef typename 
            mpl::if_<
                is_pointer<T>,
                array_adapter<Mode, Ch>,
                range_adapter<Mode, T>
            >::type type;
};

// Return type of adapt() when called with two arguments.
template<typename Iter>
struct binary_adapter {

        // char_type and category.

    typedef typename iter_val<Iter>::type  char_type;
    typedef smart_tag                      category;

        // Return type of resolve.

    #ifndef BOOST_IOSTREAMS_NO_FULL_SMART_ADAPTER_SUPPORT
        template<typename Mode, typename Ch>
        struct result_type // Ch parameter is not needed; allows for extra smarts.
            : binary_adapter_traits<Mode, char_type, Iter> 
            { };
    #else
        typedef Iter                       policy_type;
        typedef mpl::false_                is_unary;
    #endif

        // Constructor.

    binary_adapter(Iter first, Iter second) : first_(first), second_(second) { }

        // Member function resolve.
    
    #ifndef BOOST_IOSTREAMS_NO_FULL_SMART_ADAPTER_SUPPORT
        template<typename Mode, typename Ch>
        typename result_type<Mode, Ch>::type
        resolve() const
        {
            typedef typename result_type<Mode, Ch>::type type;
            return type(first_, second_);
        }
    #else
        template<typename Mode, typename Ch>
        typename binary_adapter_traits<Mode, Ch, Iter>::type
        resolve() const
        {
            typedef typename binary_adapter_traits<Mode, Ch, Iter>::type type;
            return type(first_, second_);
        }
    #endif

    Iter first_, second_;
};

} } } // End namespaces detail, iostreams, boost.

#endif // BOOST_IOSTREAMS_DETAIL_BINARY_ADAPTER_HPP_INCLUDED
