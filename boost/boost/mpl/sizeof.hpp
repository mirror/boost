
#ifndef BOOST_MPL_SIZEOF_HPP_INCLUDED
#define BOOST_MPL_SIZEOF_HPP_INCLUDED

// + file: boost/mpl/sizeof.hpp
// + last modified: 08/mar/03

// Copyright (c) 2000-03
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

#include "boost/mpl/size_t.hpp"
#include "boost/mpl/aux_/void_spec.hpp"
#include "boost/mpl/aux_/lambda_support.hpp"

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(T)
    >
struct sizeof_
    : size_t< sizeof(T) >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,sizeof_,(T))
};

BOOST_MPL_AUX_VOID_SPEC(1, sizeof_)

}} // namespace boost::mpl

#endif // BOOST_MPL_SIZEOF_HPP_INCLUDED
