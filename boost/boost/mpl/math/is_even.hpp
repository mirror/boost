//-----------------------------------------------------------------------------
// boost/mpl/is_even.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-01
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_MATH_IS_EVEN_HPP_INCLUDED
#define BOOST_MPL_MATH_IS_EVEN_HPP_INCLUDED

#include "boost/mpl/bool.hpp"
#include "boost/mpl/aux_/void_spec.hpp"
#include "boost/mpl/aux_/lambda_support.hpp"
#include "boost/mpl/aux_/config/eti.hpp"
#include "boost/detail/workaround.hpp"

namespace boost { namespace mpl {

namespace math {

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
namespace aux
{
  template <class N>
  struct is_even_base
  {
      enum { value = (N::value % 2) == 0 };
      typedef bool_<value> type;
  };
}
#endif 
template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(N)
    >
struct is_even
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
  : aux::is_even_base<N>::type
#else
  : bool_<((N::value % 2) == 0)>
#endif 
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_even,(N))
};

} // namespace math

BOOST_MPL_AUX_VOID_SPEC(1, math::is_even)

}} // namespace boost::mpl

#endif // BOOST_MPL_MATH_IS_EVEN_HPP_INCLUDED
