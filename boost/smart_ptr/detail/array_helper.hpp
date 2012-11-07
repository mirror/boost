/*
 * Copyright (c) 2012 Glen Joseph Fernandes 
 * glenfe at live dot com
 *
 * Distributed under the Boost Software License, 
 * Version 1.0. (See accompanying file LICENSE_1_0.txt 
 * or copy at http://boost.org/LICENSE_1_0.txt)
 */
#ifndef BOOST_SMART_PTR_DETAIL_ARRAY_HELPER_HPP
#define BOOST_SMART_PTR_DETAIL_ARRAY_HELPER_HPP

namespace boost {
    namespace detail {
        template<typename T>
        struct array_helper {
            static void create(T& value) {
                void* p1 = &value;
                ::new(p1) T();
            }
            static void create_noinit(T& value) {
                void* p1 = &value;
                ::new(p1) T;
            }
            static void destroy(T& value) {
                value.~T();        
            }
#if defined(BOOST_HAS_VARIADIC_TMPL) && defined(BOOST_HAS_RVALUE_REFS)
            template<typename... Args>
            static void create(T& value, Args... args) {
                void* p1 = &value;
                ::new(p1) T(args...);
            }
#endif
        };
#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
        template<typename T, size_t N>
        struct array_helper<T[N]> {
            static void create(T value[N]) {
                void* p1 = &value;
                ::new(p1) T[N]();
            }
            static void create_noinit(T value[N]) {
                void* p1 = &value;
                ::new(p1) T[N];
            }
            static void destroy(T value[N]) {
                array_helper<T>::destroy(value[N-1]);
                array_helper<T[N-1]>::destroy(value);
            }
#if defined(BOOST_HAS_VARIADIC_TMPL) && defined(BOOST_HAS_RVALUE_REFS)
            template<typename... Args>
            static void create(T value[N], Args... args) {
                array_helper<T[N-1]>::create(value, args);
                array_helper<T>::create(value[N-1], args);
            }
#endif
        };
        template<typename T>
        struct array_helper<T[0]> {
            static void destroy(T[]) {
            }
#if defined(BOOST_HAS_VARIADIC_TMPL) && defined(BOOST_HAS_RVALUE_REFS)
            template<typename... Args>            
            static void create(T[], Args...) {
            }
#endif
        };
#endif
    }
}

#endif
