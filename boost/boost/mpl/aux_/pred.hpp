//-----------------------------------------------------------------------------
// boost mpl/aux/pred.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2001-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_AUX_PRED_HPP_INCLUDED
#define BOOST_MPL_AUX_PRED_HPP_INCLUDED

namespace boost {
namespace mpl {
namespace aux {

// wrapper class to help users to deal with "legacy" metafunctions 
// (i.e. the ones that do not provide the '::type' interface)
//
// usage example: mpl::pred< boost::is_same<mpl::_1, int> >

template< typename Pred >
struct pred : Pred
{
    typedef pred type;
};

} // namespace aux
} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_AUX_PRED_HPP_INCLUDED
