// Boost.Units - A C++ library for zero-overhead dimensional analysis and 
// unit/quantity manipulation and conversion
//
// Copyright (C) 2003-2008 Matthias Christian Schabel
// Copyright (C) 2008 Steven Watanabe
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_UNITS_DETAIL_HETEROGENEOUS_CONVERSION_HPP
#define BOOST_UNITS_DETAIL_HETEROGENEOUS_CONVERSION_HPP

#include <boost/mpl/list/list0.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/push_front.hpp>

#include <boost/mpl/print.hpp>

#include <boost/units/static_rational.hpp>
#include <boost/units/homogeneous_system.hpp>
#include <boost/units/detail/linear_algebra.hpp>

namespace boost {

namespace units {

namespace detail {

struct solve_end {
    template<class Begin, class Y>
    struct apply {
        typedef mpl::list0<> type;
    };
};

struct no_solution {};

template<class X1, class X2, class Next>
struct solve_normal {
    template<class Begin, class Y>
    struct apply {
        typedef typename mpl::next<Begin>::type next;
        typedef typename mpl::push_front<
            typename Next::template apply<next, Y>::type,
            typename mpl::minus<
                typename mpl::times<X1, Y>::type,
                typename mpl::times<X2, typename mpl::deref<Begin>::type>::type
            >::type
        >::type type;
    };
};

template<class Next>
struct solve_leading_zeroes {
    template<class Begin>
    struct apply {
        typedef typename mpl::push_front<
            typename Next::template apply<typename mpl::next<Begin>::type>::type,
            typename mpl::deref<Begin>::type
        >::type type;
    };
    typedef solve_leading_zeroes type;
};

template<>
struct solve_leading_zeroes<no_solution> {
    typedef no_solution type;
};

template<class Next>
struct solve_first_non_zero {
    template<class Begin>
    struct apply {
        typedef typename Next::template apply<
            typename mpl::next<Begin>::type,
            typename mpl::deref<Begin>::type
        >::type type;
    };
};

template<class Next>
struct solve_internal_zero {
    template<class Begin, class Y>
    struct apply {
        typedef typename mpl::push_front<
            typename Next::template apply<typename mpl::next<Begin>::type, Y>::type,
            typename mpl::deref<Begin>::type
        >::type type;
    };
};

template<class T>
struct make_solve_list_internal_zero {
    template<class Next, class X>
    struct apply {
        typedef solve_normal<X, T, Next> type;
    };
};

template<>
struct make_solve_list_internal_zero<static_rational<0> > {
    template<class Next, class X>
    struct apply {
        typedef solve_internal_zero<Next> type;
    };
};

template<int N>
struct make_solve_list_normal {
    template<class Begin, class X>
    struct apply {
        typedef typename make_solve_list_internal_zero<
            typename mpl::deref<Begin>::type
        >::template apply<
            typename make_solve_list_normal<N-1>::template apply<typename mpl::next<Begin>::type, X>::type,
            X
        >::type type;
    };
};

template<>
struct make_solve_list_normal<0> {
    template<class Begin, class X>
    struct apply {
        typedef solve_end type;
    };
};

template<int N>
struct make_solve_list_leading_zeroes;

template<class T>
struct make_solve_list_first_non_zero {
    template<class Begin, int N>
    struct apply {
        typedef solve_first_non_zero<
            typename make_solve_list_normal<N-1>::template apply<
                typename mpl::next<Begin>::type,
                typename mpl::deref<Begin>::type
            >::type
        > type;
    };
};

template<>
struct make_solve_list_first_non_zero<static_rational<0> > {
    template<class Begin, int N>
    struct apply {
        typedef typename solve_leading_zeroes<
            typename make_solve_list_leading_zeroes<N-1>::template apply<
                typename mpl::next<Begin>::type
            >::type
        >::type type;
    };
};

template<int N>
struct make_solve_list_leading_zeroes {
    template<class Begin>
    struct apply {
        typedef typename make_solve_list_first_non_zero<typename mpl::deref<Begin>::type>::template apply<Begin, N>::type type;
    };
};

template<>
struct make_solve_list_leading_zeroes<0> {
    template<class Begin>
    struct apply {
        typedef no_solution type;
    };
};

template<int N>
struct try_add_unit_impl {
    template<class Begin, class L>
    struct apply {
        typedef typename try_add_unit_impl<N-1>::template apply<typename mpl::next<Begin>::type, L>::type next;
        typedef typename mpl::deref<Begin>::type::template apply<typename mpl::begin<next>::type>::type type;
        BOOST_STATIC_ASSERT((mpl::size<next>::value - 1 == mpl::size<type>::value));
    };
};

template<>
struct try_add_unit_impl<0> {
    template<class Begin, class L>
    struct apply {
        typedef L type;
    };
};

template<int N>
struct make_homogeneous_system_impl;

template<class T, bool is_done>
struct make_homogeneous_system_func;

template<class T>
struct make_homogeneous_system_func<T, false> {
    template<class Begin, class Current, class Units, class Dimensions, int N>
    struct apply {
        typedef typename make_homogeneous_system_impl<N-1>::template apply<
            typename mpl::next<Begin>::type,
            typename mpl::push_front<Current, T>::type,
            typename mpl::push_front<Units, typename mpl::deref<Begin>::type>::type,
            Dimensions
        >::type type;
    };
};

template<class T>
struct make_homogeneous_system_func<T, true> {
    template<class Begin, class Current, class Units, class Dimensions, int N>
    struct apply {
        typedef typename mpl::push_front<Units, typename mpl::deref<Begin>::type>::type type;
    };
};

template<>
struct make_homogeneous_system_func<no_solution, false> {
    template<class Begin, class Current, class Units, class Dimensions, int N>
    struct apply {
        typedef typename make_homogeneous_system_impl<N-1>::template apply<
            typename mpl::next<Begin>::type,
            Current,
            Units,
            Dimensions
        >::type type;
    };
};

template<>
struct make_homogeneous_system_func<no_solution, true> {
    template<class Begin, class Current, class Units, class Dimensions, int N>
    struct apply {
        typedef typename make_homogeneous_system_impl<N-1>::template apply<
            typename mpl::next<Begin>::type,
            Current,
            Units,
            Dimensions
        >::type type;
    };
};

template<int N>
struct make_homogeneous_system_impl {
    template<class Begin, class Current, class Units, class Dimensions>
    struct apply {
        typedef typename expand_dimensions<mpl::size<Dimensions>::value>::template apply<
            typename mpl::begin<Dimensions>::type,
            typename mpl::begin<typename mpl::deref<Begin>::type::dimension_type>::type
        >::type dimensions;
        typedef typename try_add_unit_impl<mpl::size<Current>::value>::template apply<typename mpl::begin<Current>::type, dimensions>::type new_element;
        typedef typename make_solve_list_leading_zeroes<mpl::size<new_element>::value>::template apply<typename mpl::begin<new_element>::type>::type new_func;
        typedef typename make_homogeneous_system_func<
            new_func,
            ((mpl::size<Current>::value)+1) == (mpl::size<Dimensions>::value)
        >::template apply<Begin, Current, Units, Dimensions, N>::type type;
    };
};

template<>
struct make_homogeneous_system_impl<0> {
    template<class Begin, class Current, class Units, class Dimensions>
    struct apply {
        typedef Units type;
    };
};

template<class Units>
struct make_homogeneous_system {
    typedef typename find_base_dimensions<Units>::type base_dimensions;
    typedef homogeneous_system<
        typename bubble_sort<
            typename make_homogeneous_system_impl<
                mpl::size<Units>::value
            >::template apply<
                typename mpl::begin<Units>::type,
                mpl::list0<>,
                mpl::list0<>,
                base_dimensions
            >::type
        >::type
    > type;
};

template<int N>
struct extract_base_units {
    template<class Begin, class T>
    struct apply {
        typedef typename mpl::push_front<
            typename extract_base_units<N-1>::template apply<typename mpl::next<Begin>::type, T>::type,
            typename mpl::deref<Begin>::type::tag_type
        >::type type;
    };
};

template<>
struct extract_base_units<0> {
    template<class Begin, class T>
    struct apply {
        typedef T type;
    };
};

}

}

}

#endif
