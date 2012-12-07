/*
 * Copyright (c) 2012 Glen Joseph Fernandes 
 * glenfe at live dot com
 *
 * Distributed under the Boost Software License, 
 * Version 1.0. (See accompanying file LICENSE_1_0.txt 
 * or copy at http://boost.org/LICENSE_1_0.txt)
 */
#ifndef BOOST_SMART_PTR_DETAIL_ARRAY_UTILITY_HPP
#define BOOST_SMART_PTR_DETAIL_ARRAY_UTILITY_HPP

#include <boost/config.hpp>
#include <boost/type_traits/has_trivial_constructor.hpp>
#include <boost/type_traits/has_trivial_destructor.hpp>

namespace boost {
    namespace detail {
        template<typename T>
        inline void array_destroy(T*, std::size_t, boost::true_type) {
            // do nothing
        }
        template<typename T>
        inline void array_destroy(T* memory, std::size_t size, boost::false_type) {
            for (std::size_t i = size; i > 0; ) {
                memory[--i].~T();
            }
        }
        template<typename T>
        inline void array_destroy(T* memory, std::size_t size) {
            boost::has_trivial_destructor<T> type;
            array_destroy(memory, size, type);
        }
        template<typename T>
        inline void array_construct(T* memory, std::size_t size, boost::true_type) {
            for (std::size_t i = 0; i < size; i++) {
                memory[i] = T();
            }
        }
        template<typename T>
        inline void array_construct(T* memory, std::size_t size, boost::false_type) {
            std::size_t i = 0;
            try {
                for (; i < size; i++) {
                    void* p1 = memory + i;
                    ::new(p1) T();
                }
            } catch (...) {
                array_destroy(memory, i);
                throw;
            }
        }
        template<typename T>
        inline void array_construct(T* memory, std::size_t size) {
            boost::has_trivial_default_constructor<T> type;            
            array_construct(memory, size, type);
        }
#if defined(BOOST_HAS_RVALUE_REFS)
        template<typename T>
        inline void array_construct_value(T* memory, std::size_t size, T&& value) {
            std::size_t i = 0;
            try {
                for (; i < size; i++) {
                    void* p1 = memory + i;
                    ::new(p1) T(value);
                }
            } catch (...) {
                array_destroy(memory, i);
                throw;
            }
        }
#if defined(BOOST_HAS_VARIADIC_TMPL)
        template<typename T, typename... Args>
        inline void array_construct_args(T* memory, std::size_t size, Args&&... args) {
            std::size_t i = 0;
            try {
                for (; i < size; i++) {
                    void* p1 = memory + i;
                    ::new(p1) T(args...);
                }
            } catch (...) {
                array_destroy(memory, i);
                throw;
            }
        }
#endif
#endif
        template<typename T>
        inline void array_construct_list(T* memory, std::size_t size, const T* list) {
            std::size_t i = 0;
            try {
                for (; i < size; i++) {
                    void* p1 = memory + i;
                    ::new(p1) T(list[i]);
                }
            } catch (...) {
                array_destroy(memory, i);
                throw;
            }
        }
        template<typename T>
        inline void array_construct_list(T* memory, std::size_t size, const T* list, std::size_t n) {
            std::size_t i = 0;
            try {
                for (; i < size; i++) {
                    void* p1 = memory + i;
                    ::new(p1) T(list[i % n]);
                }
            } catch (...) {
                array_destroy(memory, i);
                throw;
            }
        }
        template<typename T>
        inline void array_construct_noinit(T*, std::size_t, boost::true_type) {
            // do nothing
        }
        template<typename T>
        inline void array_construct_noinit(T* memory, std::size_t size, boost::false_type) {
            std::size_t i = 0;
            try {
                for (; i < size; i++) {
                    void* p1 = memory + i;
                    ::new(p1) T;
                }
            } catch (...) {
                array_destroy(memory, i);
                throw;
            }
        }
        template<typename T>
        inline void array_construct_noinit(T* memory, std::size_t size) {
            boost::has_trivial_default_constructor<T> type;
            array_construct_noinit(memory, size, type);
        }
    }
}

#endif
