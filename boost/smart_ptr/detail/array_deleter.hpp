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
                destroy(size);
            }
            void construct(T* memory) {
                std::size_t i = 0;
                try {
                    for (object = memory; i < size; i++) {
                        void* p1 = memory + i;
                        ::new(p1) T();
                    }
                } catch (...) {
                    destroy(i);
                    throw;
                }
            }
#if defined(BOOST_HAS_VARIADIC_TMPL) && defined(BOOST_HAS_RVALUE_REFS)
            template<typename... Args>
            void construct(T* memory, Args&&... args) {
                std::size_t i = 0;
                try {
                    for (object = memory; i < size; i++) {
                        void* p1 = memory + i;
                        ::new(p1) T(args...);
                    }
                } catch (...) {
                    destroy(i);
                    throw;
                }
            }
#endif
            void construct_list(T* memory, const T* list) {
                std::size_t i = 0;
                try {
                    for (object = memory; i < size; i++) {
                        void* p1 = memory + i;
                        ::new(p1) T(list[i]);
                    }
                } catch (...) {
                    destroy(i);
                    throw;
                }
            }
            void construct_list(T* memory, const T* list, std::size_t n) {
                std::size_t i = 0;
                try {
                    for (object = memory; i < size; i++) {
                        void* p1 = memory + i;
                        ::new(p1) T(list[i % n]);
                    }
                } catch (...) {
                    destroy(i);
                    throw;
                }
            }
            void construct_noinit(T* memory) {
                std::size_t i = 0;
                try {
                    for (object = memory; i < size; i++) {
                        void* p1 = memory + i;
                        ::new(p1) T;
                    }
                } catch (...) {
                    destroy(i);
                    throw;
                }
            }
            void operator()(const void*) {
                destroy(size);
            }
        private:
            void destroy(std::size_t n) {
                if (object) {
                    for (std::size_t i = n; i > 0; ) {
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
                destroy(N);
            }
            void construct(T* memory) {
                std::size_t i = 0;
                try {
                    for (object = memory; i < N; i++) {
                        void* p1 = memory + i;
                        ::new(p1) T();
                    }
                } catch (...) {
                    destroy(i);
                    throw;
                }
            }
#if defined(BOOST_HAS_VARIADIC_TMPL) && defined(BOOST_HAS_RVALUE_REFS)
            template<typename... Args>
            void construct(T* memory, Args&&... args) {
                std::size_t i = 0;
                try {
                    for (object = memory; i < N; i++) {
                        void* p1 = memory + i;
                        ::new(p1) T(args...);
                    }
                } catch (...) {
                    destroy(i);
                    throw;
                }
            }
#endif
            void construct_list(T* memory, const T* list) {
                std::size_t i = 0;
                try {
                    for (object = memory; i < N; i++) {
                        void* p1 = memory + i;
                        ::new(p1) T(list[i]);
                    }
                } catch (...) {
                    destroy(i);
                    throw;
                }
            }
            void construct_list(T* memory, const T* list, std::size_t n) {
                std::size_t i = 0;
                try {
                    for (object = memory; i < N; i++) {
                        void* p1 = memory + i;
                        ::new(p1) T(list[i % n]);
                    }
                } catch (...) {
                    destroy(i);
                    throw;
                }
            }
            void construct_noinit(T* memory) {
                std::size_t i = 0;
                try {
                    for (object = memory; i < N; i++) {
                        void* p1 = memory + i;
                        ::new(p1) T;
                    }
                } catch (...) {
                    destroy(i);
                    throw;
                }
            }
            void operator()(const void*) {
                destroy(N);
            }
        private:
            void destroy(std::size_t n) {
                if (object) {
                    for (std::size_t i = n; i > 0; ) {
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
