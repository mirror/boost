//-----------------------------------------------------------------------------
// boost mpl/erase.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_ERASE_HPP_INCLUDED
#define BOOST_MPL_ERASE_HPP_INCLUDED

#include "boost/mpl/erase_fwd.hpp"
#include "boost/mpl/aux_/next.hpp"
#include "boost/mpl/aux_/erase_impl.hpp"
#include "boost/mpl/aux_/sequence_tag.hpp"
#include "boost/mpl/aux_/void_spec.hpp"
#include "boost/mpl/aux_/lambda_support.hpp"
#include "boost/mpl/aux_/config/msvc_typename.hpp"

namespace boost {
namespace mpl {

namespace aux {
template< typename T > struct erase_param
{
    typedef typename BOOST_MPL_AUX_NEXT(T) type;
};

template<> struct erase_param<void_>
{
    typedef void_ type;
};
} // namespace aux

template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(Sequence)
    , typename BOOST_MPL_AUX_VOID_SPEC_PARAM(First)
    , typename Last = BOOST_MSVC_TYPENAME aux::erase_param<First>::type
    >
struct erase
    : erase_traits< typename BOOST_MPL_AUX_SEQUENCE_TAG(Sequence) >
        ::template algorithm< Sequence,First,Last >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,erase,(Sequence,First,Last))
};

BOOST_MPL_AUX_VOID_SPEC_EXT(2,3,erase)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_ERASE_HPP_INCLUDED
