//-----------------------------------------------------------------------------
// boost mpl/aux_/size_impl.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_AUX_SIZE_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_SIZE_IMPL_HPP_INCLUDED

#include "boost/mpl/size_fwd.hpp"
#include "boost/mpl/begin_end.hpp"
#include "boost/mpl/distance.hpp"
#include "boost/mpl/aux_/traits_lambda_spec.hpp"
#include "boost/config.hpp"

namespace boost {
namespace mpl {

// default implementation; conrete sequences might override it by 
// specializing either the 'size_traits' or the primary 'size' template

template< typename Tag >
struct size_traits
{
    template< typename Sequence > struct algorithm
#if !defined(__BORLANDC__) && (__BORLANDC__ <= 0x561 || !defined(BOOST_STRICT_CONFIG))
        : distance<
              typename begin<Sequence>::type
            , typename end<Sequence>::type
            >
    {
#else
    {
        typedef typename distance<
              typename begin<Sequence>::type
            , typename end<Sequence>::type
            >::type type;
#endif
    };
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(1,size_traits)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_AUX_SIZE_IMPL_HPP_INCLUDED
