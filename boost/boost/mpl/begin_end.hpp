//-----------------------------------------------------------------------------
// boost mpl/begin_end.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_BEGIN_END_HPP_INCLUDED
#define BOOST_MPL_BEGIN_END_HPP_INCLUDED

#include "boost/mpl/begin_end_fwd.hpp"
#include "boost/mpl/aux_/begin_end_impl.hpp"
#include "boost/mpl/aux_/sequence_tag.hpp"
#include "boost/mpl/aux_/void_spec.hpp"
#include "boost/mpl/aux_/lambda_support.hpp"

namespace boost {
namespace mpl {

// agurt, 13/sep/02: switched from inheritance to typedef; MSVC is more
// happy this way (less ETI-related errors), and it doesn't affect 
// anything else
template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(Sequence)
    >
struct begin
{
    typedef typename BOOST_MPL_AUX_SEQUENCE_TAG(Sequence) tag_;
    typedef typename begin_traits< tag_ >
        ::template algorithm< Sequence >::type type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,begin,(Sequence))
};

template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(Sequence)
    >
struct end
{
    typedef typename BOOST_MPL_AUX_SEQUENCE_TAG(Sequence) tag_;
    typedef typename end_traits< tag_ >
        ::template algorithm< Sequence >::type type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,end,(Sequence))
};

BOOST_MPL_AUX_VOID_SPEC(1, begin)
BOOST_MPL_AUX_VOID_SPEC(1, end)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_BEGIN_END_HPP_INCLUDED
