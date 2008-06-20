// Boost.Units - A C++ library for zero-overhead dimensional analysis and 
// unit/quantity manipulation and conversion
//
// Copyright (C) 2003-2008 Matthias Christian Schabel
// Copyright (C) 2008 Steven Watanabe
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_UNITS_DETAIL_SORT_HPP
#define BOOST_UNITS_DETAIL_SORT_HPP

#include <boost/mpl/size.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/less.hpp>

#include <boost/units/dimensionless_type.hpp>
#include <boost/units/detail/dimension_list.hpp>

namespace boost {

namespace units {

namespace detail {

template<bool second_is_less>
struct bubble_sort_conditional_swap;

template<>
struct bubble_sort_conditional_swap<true>
{
    template<class T0, class T1>
    struct apply
    {
        typedef T1 first;
        typedef T0 second;
    };
};

template<>
struct bubble_sort_conditional_swap<false>
{
    template<class T0, class T1>
    struct apply
    {
        typedef T0 first;
        typedef T1 second;
    };
};

template<int N>
struct bubble_sort_pass_impl
{
    template<class Begin, class Current>
    struct apply
    {
        typedef typename mpl::deref<Begin>::type val;
        typedef typename bubble_sort_conditional_swap<mpl::less<val, Current>::value>::template apply<Current, val> pair;
        typedef typename bubble_sort_pass_impl<N-1>::template apply<typename mpl::next<Begin>::type, typename pair::second> next;
        typedef typename mpl::push_front<typename next::type, typename pair::first>::type type;
        enum { value = next::value || mpl::less<val, Current>::value };
    };
};

template<>
struct bubble_sort_pass_impl<0>
{
    template<class Begin, class Current>
    struct apply
    {
        typedef typename mpl::push_front<dimensionless_type, Current>::type type;
        enum { value = false };
    };
};

template<bool>
struct bubble_sort_impl;

template<>
struct bubble_sort_impl<true>
{
    template<class T>
    struct apply
    {
        typedef typename mpl::begin<T>::type begin;
        typedef typename bubble_sort_pass_impl<mpl::size<T>::value - 1>::template apply<
            typename mpl::next<begin>::type,
            typename mpl::deref<begin>::type
        > single_pass;
        typedef typename bubble_sort_impl<(single_pass::value)>::template apply<typename single_pass::type>::type type;
    };
};

template<>
struct bubble_sort_impl<false>
{
    template<class T>
    struct apply
    {
        typedef T type;
    };
};

template<int N>
struct bubble_sort_one_or_zero
{
    template<class T>
    struct apply
    {
        typedef typename bubble_sort_impl<true>::template apply<T>::type type;
    };
};

template<>
struct bubble_sort_one_or_zero<0>
{
    template<class T>
    struct apply
    {
        typedef dimensionless_type type;
    };
};

template<>
struct bubble_sort_one_or_zero<1>
{
    template<class T>
    struct apply
    {
        typedef typename mpl::push_front<dimensionless_type, typename mpl::front<T>::type>::type type;
    };
};

template<class T>
struct bubble_sort
{
    typedef typename bubble_sort_one_or_zero<mpl::size<T>::value>::template apply<T>::type type;
};

} // namespace detail

} // namespace units

} // namespace boost

#endif
