/*
 * Copyright (c) 2012 Glen Joseph Fernandes 
 * glenfe at live dot com
 *
 * Distributed under the Boost Software License, 
 * Version 1.0. (See accompanying file LICENSE_1_0.txt 
 * or copy at http://boost.org/LICENSE_1_0.txt)
 */
#ifndef BOOST_SMART_PTR_DETAIL_ARRAY_DELETER_HPP
#define BOOST_SMART_PTR_DETAIL_ARRAY_DELETER_HPP

#include <boost/config.hpp>
#include <cstddef>

namespace boost {
    namespace detail {
        template<typename T>
        class array_deleter;
        template<typename T>
        class array_deleter<T[]> {
        public:
            array_deleter(std::size_t size) 
                : size(size),
                  object(0) {
            }
            ~array_deleter() {
                destroy();
            }
            void construct(T* memory) {
                object = memory;
                for (std::size_t i = 0; i < size; i++) {
                    void* p1 = object + i;
                    ::new(p1) T();
                }
            }
#if defined(BOOST_HAS_VARIADIC_TMPL) && defined(BOOST_HAS_RVALUE_REFS)
            template<typename... Args>
            void construct(T* memory, Args&&... args) {
                object = memory;
                for (std::size_t i = 0; i < size; i++) {
                    void* p1 = object + i;
                    ::new(p1) T(args...);
                }
            }
#endif
            void construct_list(T* memory, const T* list) {
                object = memory;
                for (std::size_t i = 0; i < size; i++) {
                    void* p1 = object + i;
                    ::new(p1) T(list[i]);
                }
            }
            void construct_list(T* memory, const T* list, std::size_t n) {
                object = memory;
                for (std::size_t i = 0; i < size; i++) {
                    void* p1 = object + i;
                    ::new(p1) T(list[i % n]);
                }
            }
            void construct_noinit(T* memory) {
                object = memory;
                for (std::size_t i = 0; i < size; i++) {
                    void* p1 = object + i;
                    ::new(p1) T;
                }
            }
            void operator()(const void*) {
                destroy();
            }
        private:
            void destroy() {
                if (object) {
                    for (std::size_t i = size; i > 0; ) {
                        object[--i].~T();
                    }
                    object = 0;
                }
            }
            std::size_t size;
            T* object;
        };
        template<typename T, std::size_t N>
        class array_deleter<T[N]> {
        public:
            array_deleter() 
                : object(0) {
            }
            ~array_deleter() {
                destroy();
            }
            void construct(T* memory) {
                object = memory;
                for (std::size_t i = 0; i < N; i++) {
                    void* p1 = object + i;
                    ::new(p1) T();
                }
            }
#if defined(BOOST_HAS_VARIADIC_TMPL) && defined(BOOST_HAS_RVALUE_REFS)
            template<typename... Args>
            void construct(T* memory, Args&&... args) {
                object = memory;
                for (std::size_t i = 0; i < N; i++) {
                    void* p1 = object + i;
                    ::new(p1) T(args...);
                }
            }
#endif
            void construct_list(T* memory, const T* list) {
                object = memory;
                for (std::size_t i = 0; i < N; i++) {
                    void* p1 = object + i;
                    ::new(p1) T(list[i]);
                }
            }
            void construct_list(T* memory, const T* list, std::size_t n) {
                object = memory;
                for (std::size_t i = 0; i < N; i++) {
                    void* p1 = object + i;
                    ::new(p1) T(list[i % n]);
                }
            }
            void construct_noinit(T* memory) {
                object = memory;
                for (std::size_t i = 0; i < N; i++) {
                    void* p1 = object + i;
                    ::new(p1) T;
                }
            }
            void operator()(const void*) {
                destroy();
            }
        private:
            void destroy() {
                if (object) {
                    for (std::size_t i = N; i > 0; ) {
                        object[--i].~T();
                    }
                    object = 0;
                }
            }
            T* object;
        };
    }
}

#endif
