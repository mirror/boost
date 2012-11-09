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
#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
#include <initializer_list>
#endif
#include <cstddef>

namespace boost {
    namespace detail {
        template<typename T>
        struct array_base {
            typedef typename boost::remove_cv<T>::type type;
        };
        template<typename T, std::size_t N>
        struct array_base<T[N]> {
            typedef typename array_base<T>::type type;
        };
        template<typename T>
        struct array_size {
            enum {
                size = 1
            };
        };
        template<typename T, std::size_t N>
        struct array_size<T[N]> {
            enum {
                size = N * array_size<T>::size
            };
        };
        template<typename T> 
        struct array_inner {
        };
        template<typename T>
        struct array_inner<T[]> {
            typedef T type;
        };
        template<typename T, size_t N>
        struct array_inner<T[N]> {
            typedef T type;
        };
#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
        template<typename T>
        struct array_list {
        };
        template<typename T>
        struct array_list<T[]> {
            typedef std::initializer_list<T> type;
        };
        template<typename T, size_t N>
        struct array_list<T[N]> {
            typedef std::initializer_list<T> type;
        };
#endif
    }
}

#endif
