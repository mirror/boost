//-----------------------------------------------------------------------------
// boost mpl/aux_/find_if_pred.hpp header file
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

#ifndef BOOST_MPL_AUX_FIND_IF_PRED_HPP_INCLUDED
#define BOOST_MPL_AUX_FIND_IF_PRED_HPP_INCLUDED

#include "boost/mpl/aux_/iter_apply.hpp"
#include "boost/mpl/apply.hpp"
#include "boost/mpl/not.hpp"
#include "boost/mpl/or.hpp"
#include "boost/type_traits/is_same.hpp"

namespace boost {
namespace mpl {
namespace aux {

template< typename Predicate, typename LastIterator >
struct find_if_pred
{
    template< typename State, typename Iterator >
    struct apply
    {
        typedef not_< or_<
              is_same<Iterator,LastIterator>
            , aux::iter_apply1<Predicate,Iterator>
            > > type;
    };
};

} // namespace aux
} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_AUX_FIND_IF_PRED_HPP_INCLUDED
