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

#include <boost/smart_ptr/detail/array_utility.hpp>
#include <boost/smart_ptr/detail/sp_forward.hpp>

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
                if (object) {
                    array_destroy(object, size);
                }
            }
            void construct(T* memory) {
                array_construct(memory, size);
                object = memory;
            }
#if defined(BOOST_HAS_RVALUE_REFS)
            void construct(T* memory, T&& value) {
                array_construct_value(memory, size, sp_forward<T>(value));
                object = memory;                
            }
#if defined(BOOST_HAS_VARIADIC_TMPL)
            template<typename... Args>
            void construct(T* memory, Args&&... args) {
                array_construct_args(memory, size, sp_forward<Args>(args)...);
                object = memory;
            }
#endif
#endif
            void construct_list(T* memory, const T* list) {
                array_construct_list(memory, size, list);
                object = memory;
            }
            template<std::size_t M>
            void construct_list(T* memory, const T* list) {
                array_construct_list<T, M>(memory, size, list);
                object = memory;
            }
            void construct_noinit(T* memory) {
                array_construct_noinit(memory, size);
                object = memory;
            }
            void operator()(const void*) {
                if (object) {
                    array_destroy(object, size);
                    object = 0;
                }
            }
        private:
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
                if (object) {
                    array_destroy(object, N);
                }
            }
            void construct(T* memory) {
                array_construct(memory, N);
                object = memory;
            }
#if defined(BOOST_HAS_RVALUE_REFS)
            void construct(T* memory, T&& value) {
                array_construct_value(memory, N, sp_forward<T>(value));
                object = memory;                
            }
#if defined(BOOST_HAS_VARIADIC_TMPL)
            template<typename... Args>
            void construct(T* memory, Args&&... args) {
                array_construct_args(memory, N, sp_forward<Args>(args)...);
                object = memory;
            }
#endif
#endif
            void construct_list(T* memory, const T* list) {
                array_construct_list(memory, N, list);
                object = memory;
            }
            template<std::size_t M>
            void construct_list(T* memory, const T* list) {
                array_construct_list<T, M>(memory, N, list);
                object = memory;
            }
            void construct_noinit(T* memory) {
                array_construct_noinit(memory, N);
                object = memory;
            }
            void operator()(const void*) {
                if (object) {
                    array_destroy(object, N);
                    object = 0;
                }
            }
        private:
            T* object;
        };
    }
}

#endif
