// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_UNARY_ADAPTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_UNARY_ADAPTER_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif              

#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/detail/adapter/mode_adapter.hpp>
#include <boost/iostreams/detail/adapter/output_iterator_adapter.hpp>
#include <boost/iostreams/detail/config/smart_adapter_support.hpp>
#include <boost/iostreams/detail/select.hpp>
#include <boost/iostreams/detail/ios_traits.hpp>         // is_std_io.
#include <boost/iostreams/detail/wrap_unwrap.hpp>
#include <boost/iostreams/io_traits.hpp>                 // is_smart.
#include <boost/mpl/if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/type_traits/remove_bounds.hpp>

namespace boost { namespace iostreams {

namespace detail {

//------------------Definition of unary_adapter-------------------------------//

// Deduces the return type of unary_adapter::resolve. 
// This definition is external to unary_adapter for Borland 5.x.
template<typename Mode, typename Ch, typename T>
struct unary_adapter_traits {
    typedef typename
            select<
                is_std_io<typename unwrapped_type<T>::type>,
                mode_adapter<T, Mode>,
                is_array<T>,
                array_adapter<Mode, Ch>,
                mpl::true_,
                output_iterator_adapter<Mode, Ch, T>
            >::type                                          type;
};

// Return type of adapt() when called with a single argument.
template<typename T>
struct unary_adapter {

        // char_type and category.

    typedef typename unwrap_reference<T>::type             unwrapped_type;
    typedef typename
            select<
                is_std_io<unwrapped_type>, 
                lazy< member_char_type<unwrapped_type> >,
                is_array<T>,               
                lazy< remove_bounds<T> >,
                mpl::true_,                
                smart_tag // Output iterator
            >::type                                        char_type;
    typedef smart_tag                                      category;

        // Return type of resolve.

    #ifndef BOOST_IOSTREAMS_NO_FULL_SMART_ADAPTER_SUPPORT
        template<typename Mode, typename Ch>
        struct result_type { 
            // Use whichever of Ch, char_type is not smart.
            typedef typename mpl::if_<is_smart<Ch>, char_type, Ch>::type  Ch2;
            BOOST_STATIC_ASSERT(!is_smart<Ch2>::value);
            typedef typename unary_adapter_traits<Mode, Ch2, T>::type     type;
        };
    #else 
        typedef T           policy_type;
        typedef mpl::true_  is_unary;
    #endif

        // Constuctor.

    unary_adapter(const T& t) : t_(t) { }


        // Member function resolve.

    #ifndef BOOST_IOSTREAMS_NO_FULL_SMART_ADAPTER_SUPPORT
        template<typename Mode, typename Ch>
        typename result_type<Mode, Ch>::type
        resolve() const
        {
            typedef typename result_type<Mode, Ch>::type type;
            return type(t_);
        }
    #else
        template<typename Mode, typename Ch>
        typename unary_adapter_traits<Mode, Ch, T>::type
        resolve() const
        {
            typedef typename unary_adapter_traits<Mode, Ch, T>::type type;
            return type(t_);
        }
    #endif

    T t_;
};

} } } // End namespaces detail, iostreams, boost.

#endif // BOOST_IOSTREAMS_DETAIL_UNARY_ADAPTER_HPP_INCLUDED
