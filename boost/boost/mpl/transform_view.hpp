//-----------------------------------------------------------------------------
// boost mpl/transform_view.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#ifndef BOOST_MPL_TRANSFORM_VIEW_HPP_INCLUDED
#define BOOST_MPL_TRANSFORM_VIEW_HPP_INCLUDED

#include "boost/mpl/begin_end.hpp"
#include "boost/mpl/lambda.hpp"
#include "boost/mpl/apply.hpp"
#include "boost/mpl/aux_/void_spec.hpp"
#include "boost/mpl/aux_/lambda_spec.hpp"

namespace boost {
namespace mpl {

template< typename Iterator, typename F >
struct transform_iter
{
    typedef Iterator base;
    typedef typename base::category category;
    typedef transform_iter<typename base::next,F> next;
    
    typedef typename apply1<
          F
        , typename base::type
        >::type type;
};

template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(Sequence)
    , typename BOOST_MPL_AUX_VOID_SPEC_PARAM(F)
    >
struct transform_view
{
    struct tag;
    typedef transform_view type;
    typedef typename lambda<F>::type f_;
    typedef transform_iter< typename begin<Sequence>::type,f_ > begin;
    typedef transform_iter< typename end<Sequence>::type,f_ > end;
};

BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(2,transform_iter)
BOOST_MPL_AUX_VOID_SPEC(2, transform_view)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_TRANSFORM_VIEW_HPP_INCLUDED
