
#ifndef BOOST_MPL_LAMBDA_FWD_HPP_INCLUDED
#define BOOST_MPL_LAMBDA_FWD_HPP_INCLUDED

// + file: boost/mpl/labmda_fwd.hpp
// + last modified: 02/aug/03

// Copyright (c) 2001-03
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

#include "boost/mpl/aux_/lambda_arity_param.hpp"
#include "boost/mpl/aux_/config/lambda.hpp"

namespace boost {
namespace mpl {

#if !defined(BOOST_MPL_NO_FULL_LAMBDA_SUPPORT)

template< 
      typename T
    , typename Tag
    BOOST_MPL_AUX_LAMBDA_ARITY_PARAM(typename Arity)
    >
struct lambda;

#else

template< 
      typename T
    , typename Tag
    , bool Protect
    > 
struct lambda;

#endif

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_LAMBDA_FWD_HPP_INCLUDED
