
#ifndef BOOST_MPL_NUMERIC_CAST_HPP_INCLUDED
#define BOOST_MPL_NUMERIC_CAST_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/apply_wrap.hpp>

namespace boost { namespace mpl {

// no default implementation; the definition is needed to make MSVC happy

template< typename SourceTag, typename TargetTag > struct numeric_cast
{
    template< typename N > struct apply;
};


namespace aux {

template<
      typename F
    , typename Tag1
    , typename Tag2
    >
struct cast1st_impl
{
    template< typename N1, typename N2 > struct apply
        : apply_wrap2< 
              F
            , typename apply_wrap1< numeric_cast<Tag1,Tag2>,N1 >::type
            , N2
            >
    {
    };
};

template<
      typename F
    , typename Tag1
    , typename Tag2
    >
struct cast2nd_impl
{
    template< typename N1, typename N2 > struct apply
        : apply_wrap2< 
              F
            , N1
            , typename apply_wrap1< numeric_cast<Tag2,Tag1>,N2 >::type
            >
    {
    };
};

} // namespace aux

}}

#endif // BOOST_MPL_NUMERIC_CAST_HPP_INCLUDED
