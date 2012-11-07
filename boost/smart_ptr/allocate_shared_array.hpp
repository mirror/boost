/*
 * Copyright (c) 2012 Glen Joseph Fernandes 
 * glenfe at live dot com
 *
 * Distributed under the Boost Software License, 
 * Version 1.0. (See accompanying file LICENSE_1_0.txt 
 * or copy at http://boost.org/LICENSE_1_0.txt)
 */
#ifndef BOOST_SMART_PTR_ALLOCATE_SHARED_ARRAY_HPP
#define BOOST_SMART_PTR_ALLOCATE_SHARED_ARRAY_HPP

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/detail/allocate_array_helper.hpp>
#include <boost/smart_ptr/detail/array_deleter.hpp>
#include <boost/smart_ptr/detail/sp_if_array.hpp>
#include <boost/type_traits/remove_cv.hpp>

namespace boost {
    template<typename T, typename A>
    inline typename detail::sp_if_array<T>::type 
    allocate_shared(const A& allocator, size_t size) {
        typedef typename remove_cv<typename shared_ptr<T>::element_type>::type T1;
        T1* p1 = 0;
        detail::allocate_array_helper<A, T1> a1(allocator, size, &p1);
        detail::array_deleter<T1> d1;
        shared_ptr<T> s1(p1, d1, a1);
        detail::array_deleter<T1>* d2;
        d2 = get_deleter<detail::array_deleter<T1> >(s1);
        d2->construct(p1, size);
        return shared_ptr<T>(s1, p1);
    }
#if defined(BOOST_HAS_VARIADIC_TMPL) && defined(BOOST_HAS_RVALUE_REFS)
    template<typename T, typename A, typename... Args>
    inline typename detail::sp_if_array<T>::type
    allocate_shared(const A& allocator, size_t size, Args&&... args) {
        typedef typename remove_cv<typename shared_ptr<T>::element_type>::type T1;
        T1* p1 = 0;
        detail::allocate_array_helper<A, T1> a1(allocator, size, &p1);
        detail::array_deleter<T1> d1;
        shared_ptr<T> s1(p1, d1, a1);
        detail::array_deleter<T1>* d2;
        d2 = get_deleter<detail::array_deleter<T1> >(s1);
        d2->construct(p1, size, std::forward<Args>(args)...);
        return shared_ptr<T>(s1, p1);
    }
#endif
}

#endif
