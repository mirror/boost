// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_HAS_TRAITS_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_HAS_TRAITS_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif              

#include <boost/config.hpp> // BOOST_STATIC_CONSTANT, BOOST_DEDUCED_TYPENAME.
#include <boost/iostreams/traits.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>   
#include <boost/mpl/bool.hpp>   
#include <boost/type_traits/is_convertible.hpp> 

namespace boost { namespace iostreams { namespace detail {

template<typename T, typename Tag>
struct has_trait_impl {
    typedef typename io_category<T>::type category;
    BOOST_STATIC_CONSTANT(bool, value = (is_convertible<category, Tag>::value));
};

template<typename T, typename Tag>
struct has_trait : mpl::bool_<has_trait_impl<T, Tag>::value>
{ BOOST_MPL_AUX_LAMBDA_SUPPORT(2, has_trait, (T, Tag)) }; 

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_HAS_TRAITS_HPP_INCLUDED
