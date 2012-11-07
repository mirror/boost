/*
 * Copyright (c) 2012 Glen Joseph Fernandes 
 * glenfe at live dot com
 *
 * Distributed under the Boost Software License, 
 * Version 1.0. (See accompanying file LICENSE_1_0.txt 
 * or copy at http://boost.org/LICENSE_1_0.txt)
 */
#ifndef BOOST_SMART_PTR_DETAIL_ARRAY_TRAITS_HPP
#define BOOST_SMART_PTR_DETAIL_ARRAY_TRAITS_HPP

#include <boost/type_traits/remove_cv.hpp>

namespace boost {
    namespace detail {
        template<typename T>
        struct array_type {
            typedef typename boost::remove_cv<T>::type type;
        };
        template<typename T, size_t N>
        struct array_type<T[N]> {
            typedef typename array_type<T>::type type;
        };
        template<typename T>
        struct array_size {
            enum {
                size = 1
            };
        };
        template<typename T, size_t N>
        struct array_size<T[N]> {
            enum {
                size = N * array_size<T>::size
            };
        };
    }
}

#endif
