
#ifndef BOOST_MPL_AUX_SINGLE_ELEMENT_ITER_HPP_INCLUDED
#define BOOST_MPL_AUX_SINGLE_ELEMENT_ITER_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/aux_/value_wknd.hpp>
#include <boost/mpl/aux_/iterator_names.hpp>
#include <boost/mpl/aux_/lambda_spec.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>
#include <boost/mpl/aux_/nttp_decl.hpp>

namespace boost { namespace mpl { 

namespace aux {

template< typename T, int N >
struct single_element_iter;

// random access support
template< typename T, BOOST_MPL_AUX_NTTP_DECL(int, N) >
struct single_iter_base
{
    typedef random_access_iterator_tag category;
    typedef mpl::int_<N> position;

    template< typename D >
    struct BOOST_MPL_AUX_ITERATOR_ADVANCE
    {
        typedef plus< mpl::int_<N>,D > n_;
        typedef single_element_iter<
              T
            , BOOST_MPL_AUX_VALUE_WKND(n_)::value
            > type;
    };

    template< typename U >
    struct BOOST_MPL_AUX_ITERATOR_DISTANCE
    {
        typedef typename minus<
              typename U::position
            , mpl::int_<N>
            >::type type;
    };
};

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< typename T >
struct single_element_iter<T,0>
    : single_iter_base<T,0>
{
    typedef single_element_iter<T,1> next;
    typedef T type;
};

template< typename T >
struct single_element_iter<T,1>
    : single_iter_base<T,1>
{
    typedef single_element_iter<T,0> prior;
};

#else

template< BOOST_MPL_AUX_NTTP_DECL(int, N) > struct single_iter_impl
{
    template< typename T > struct result_;
};

template<>
struct single_iter_impl<0>
{
    template< typename T > struct result_
        : single_iter_base<T,0>
    {
        typedef single_element_iter<T,1> next;
        typedef T type;
    };
};

template<>
struct single_iter_impl<1>
{
    template< typename T > struct result_
        : single_iter_base<T,1>
    {
        typedef single_element_iter<T,0> prior;
    };
};

template< typename T, BOOST_MPL_AUX_NTTP_DECL(int, N) >
struct single_element_iter
    : single_iter_impl<N>::template result_<T>
{
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

} // namespace aux

}}

#endif // BOOST_MPL_AUX_SINGLE_ELEMENT_ITER_HPP_INCLUDED
