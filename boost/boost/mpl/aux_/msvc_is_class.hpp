
#ifndef BOOST_MPL_AUX_MSVC_IS_CLASS_HPP_INCLUDED
#define BOOST_MPL_AUX_MSVC_IS_CLASS_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/type_wrapper.hpp>
#include <boost/mpl/aux_/yes_no.hpp>
#include <boost/mpl/aux_/adl_barrier.hpp>

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN

namespace aux {

template< typename T > struct is_class_helper
{
    typedef int (T::* type)();
};

// MSVC 6.x-specific lightweight 'is_class' implementation; 
// Distinguishing feature: does not instantiate the type being tested.
template< typename T >
struct msvc_is_class
{
    template< typename U>
    static yes_tag  test(type_wrapper<U>*, /*typename*/ is_class_helper<U>::type = 0);
    static no_tag   test(void const volatile*, ...);

    enum { value = sizeof(test((type_wrapper<T>*)0)) == sizeof(yes_tag) };
    typedef bool_<value> type;
};

} // namespace aux

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE

#endif // BOOST_MPL_AUX_MSVC_IS_CLASS_HPP_INCLUDED
