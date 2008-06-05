// Boost.Units - A C++ library for zero-overhead dimensional analysis and 
// unit/quantity manipulation and conversion
//
// Copyright (C) 2003-2008 Matthias Christian Schabel
// Copyright (C) 2008 Steven Watanabe
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_UNITS_DIMENSION_IMPL_HPP
#define BOOST_UNITS_DIMENSION_IMPL_HPP

#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/less.hpp>

#include <boost/units/config.hpp>
#include <boost/units/dimensionless_type.hpp>
#include <boost/units/static_rational.hpp>
#include <boost/units/units_fwd.hpp>
#include <boost/units/detail/dimension_list.hpp>
#include <boost/units/detail/push_front_if.hpp>
#include <boost/units/detail/push_front_or_add.hpp>

/// \file 
/// \brief Core class and metaprogramming utilities for compile-time dimensional analysis.

namespace boost {

namespace units {

namespace detail {

template<bool second_is_less>
struct sort_dims_conditional_swap;

template<>
struct sort_dims_conditional_swap<true>
{
    template<class T0, class T1>
    struct apply
    {
        typedef T1 first;
        typedef T0 second;
    };
};

template<>
struct sort_dims_conditional_swap<false>
{
    template<class T0, class T1>
    struct apply
    {
        typedef T0 first;
        typedef T1 second;
    };
};

template<int N>
struct sort_dims_pass_impl
{
    template<class Begin, class Current>
    struct apply
    {
        typedef typename mpl::deref<Begin>::type val;
        typedef typename sort_dims_conditional_swap<mpl::less<val, Current>::value>::template apply<Current, val> pair;
        typedef typename sort_dims_pass_impl<N-1>::template apply<typename mpl::next<Begin>::type, typename pair::second> next;
        typedef typename push_front_or_add<typename next::type, typename pair::first>::type type;
        enum { value = next::value || mpl::less<val, Current>::value };
    };
};

template<>
struct sort_dims_pass_impl<0>
{
    template<class Begin, class Current>
    struct apply
    {
        typedef typename mpl::push_front<dimensionless_type, Current>::type type;
        enum { value = false };
    };
};

template<bool>
struct sort_dims_impl;

template<>
struct sort_dims_impl<true>
{
    template<class T>
    struct apply
    {
        typedef typename mpl::begin<T>::type begin;
        typedef typename sort_dims_pass_impl<mpl::size<T>::value - 1>::template apply<
            typename mpl::next<begin>::type,
            typename mpl::deref<begin>::type
        > single_pass;
        typedef typename sort_dims_impl<(single_pass::value)>::template apply<typename single_pass::type>::type type;
    };
};

template<>
struct sort_dims_impl<false>
{
    template<class T>
    struct apply
    {
        typedef T type;
    };
};

template<int N>
struct sort_dims_one_or_zero
{
    template<class T>
    struct apply
    {
        typedef typename sort_dims_impl<true>::template apply<T>::type type;
    };
};

template<>
struct sort_dims_one_or_zero<0>
{
    template<class T>
    struct apply
    {
        typedef dimensionless_type type;
    };
};

template<>
struct sort_dims_one_or_zero<1>
{
    template<class T>
    struct apply
    {
        typedef typename mpl::push_front<dimensionless_type, typename mpl::front<T>::type>::type type;
    };
};

template<class T>
struct sort_dims
{
    typedef typename sort_dims_one_or_zero<mpl::size<T>::value>::template apply<T>::type type;
};

/// sorted sequences can be merged in linear time
template<bool less, bool greater>
struct merge_dimensions_func;

template<int N1, int N2>
struct merge_dimensions_impl;

template<>
struct merge_dimensions_func<true, false>
{
    template<typename Begin1, typename Begin2, int N1, int N2>
    struct apply
    {
        typedef typename mpl::push_front<
            typename merge_dimensions_impl<N1 - 1, N2>::template apply<
                typename boost::mpl::next<Begin1>::type,
                Begin2
            >::type,
            typename boost::mpl::deref<Begin1>::type
        >::type type;
    };
};

template<>
struct merge_dimensions_func<false, true> {
    template<typename Begin1, typename Begin2, int N1, int N2>
    struct apply
    {
        typedef typename mpl::push_front<
            typename merge_dimensions_impl<N2 - 1, N1>::template apply<
                typename boost::mpl::next<Begin2>::type,
                Begin1
            >::type,
            typename boost::mpl::deref<Begin2>::type
        >::type type;
    };
};

template<>
struct merge_dimensions_func<false, false> {
    template<typename Begin1, typename Begin2, int N1, int N2>
    struct apply
    {
        typedef typename mpl::plus<typename boost::mpl::deref<Begin1>::type, typename boost::mpl::deref<Begin2>::type>::type combined;
        typedef typename push_front_if<!is_empty_dim<combined>::value>::template apply<
            typename merge_dimensions_impl<N1 - 1, N2 - 1>::template apply<
                typename boost::mpl::next<Begin1>::type,
                typename boost::mpl::next<Begin2>::type
            >::type,
            combined
        >::type type;
    };
};

template<int N1, int N2>
struct merge_dimensions_impl {
    template<typename Begin1, typename Begin2>
    struct apply
    {
        typedef typename boost::mpl::deref<Begin1>::type dim1;
        typedef typename boost::mpl::deref<Begin2>::type dim2;

        typedef typename merge_dimensions_func<(mpl::less<dim1,dim2>::value == true),
                (mpl::less<dim2,dim1>::value == true)>::template apply<
            Begin1,
            Begin2,
            N1,
            N2
        >::type type;
    };
};

template<typename Sequence1, typename Sequence2>
struct merge_dimensions
{
    typedef typename detail::merge_dimensions_impl<boost::mpl::size<Sequence1>::value, 
                                                   boost::mpl::size<Sequence2>::value>::template 
        apply<
            typename boost::mpl::begin<Sequence1>::type,
            typename boost::mpl::begin<Sequence2>::type
        >::type type;
};

template<int N>
struct iterator_to_list
{
    template<typename Begin>
    struct apply
    {
        typedef typename mpl::push_front<
            typename iterator_to_list<N - 1>::template apply<
                typename boost::mpl::next<Begin>::type
            >::type,
            typename boost::mpl::deref<Begin>::type
        >::type type;
    };
};

template<>
struct iterator_to_list<0>
{
    template<typename Begin>
    struct apply {
        typedef dimensionless_type type;
    };
};

template<int N>
struct merge_dimensions_impl<N, 0>
{
    template<typename Begin1, typename Begin2>
    struct apply
    {
        typedef typename iterator_to_list<N>::template apply<Begin1>::type type;
    };
};

template<int N>
struct merge_dimensions_impl<0, N>
{
    template<typename Begin1, typename Begin2>
    struct apply
    {
        typedef typename iterator_to_list<N>::template apply<Begin2>::type type;
    };
};

template<>
struct merge_dimensions_impl<0, 0>
{
    template<typename Begin1, typename Begin2>
    struct apply
    {
        typedef dimensionless_type type;
    };
};

template<int N>
struct static_inverse_impl
{
    template<typename Begin>
    struct apply {
        typedef typename boost::mpl::push_front<
            typename static_inverse_impl<N - 1>::template apply<
                typename boost::mpl::next<Begin>::type
            >::type,
            typename mpl::negate<typename boost::mpl::deref<Begin>::type>::type
        >::type type;
    };
};

template<>
struct static_inverse_impl<0>
{
    template<typename Begin>
    struct apply
    {
        typedef dimensionless_type type;
    };
};

template<int N>
struct static_power_impl
{
    template<typename Begin, typename Ex>
    struct apply
    {
        typedef typename mpl::push_front<
            typename detail::static_power_impl<N - 1>::template apply<typename mpl::next<Begin>::type, Ex>::type,
            typename mpl::times<typename mpl::deref<Begin>::type, Ex>::type
        >::type type;
    };
};

template<>
struct static_power_impl<0>
{
    template<typename Begin, typename Ex>
    struct apply
    {
        typedef dimensionless_type type;
    };
};

template<int N>
struct static_root_impl {
    template<class Begin, class Ex>
    struct apply {
        typedef typename mpl::push_front<
            typename detail::static_root_impl<N - 1>::template apply<typename mpl::next<Begin>::type, Ex>::type,
            typename mpl::divides<typename mpl::deref<Begin>::type, Ex>::type
        >::type type;
    };
};

template<>
struct static_root_impl<0> {
    template<class Begin, class Ex>
    struct apply 
    {
        typedef dimensionless_type type;
    };
};

} // namespace detail

} // namespace units

} // namespace boost

#endif // BOOST_UNITS_DIMENSION_IMPL_HPP
