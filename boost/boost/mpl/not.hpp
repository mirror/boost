
#ifndef BOOST_MPL_NOT_HPP_INCLUDED
#define BOOST_MPL_NOT_HPP_INCLUDED

// + file: boost/mpl/not.hpp
// + last modified: 25/feb/03

// Copyright (c) 2000-03
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

#include "boost/mpl/bool.hpp"
#include "boost/mpl/aux_/nested_type_wknd.hpp"
#include "boost/mpl/aux_/void_spec.hpp"
#include "boost/mpl/aux_/lambda_support.hpp"

namespace boost {
namespace mpl {

namespace aux {

template< long C_ > // 'long' is intentional here
struct not_impl
    : bool_<!C_>
{
};

} // namespace aux


template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(T)
    >
struct not_
    : aux::not_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T)::value
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,not_,(T))
};

BOOST_MPL_AUX_VOID_SPEC(1,not_)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_NOT_HPP_INCLUDED
