//-----------------------------------------------------------------------------
// boost/mpl/apply_if.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2004
// Robert Ramey
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

// apply_if is deprecated.  Use eval_if instead.  This is only included
// to support older code like spirit 1.6

#ifndef BOOST_MPL_APPLY_IF_HPP_INCLUDED
#define BOOST_MPL_APPLY_IF_HPP_INCLUDED

#include "boost/mpl/eval_if.hpp"

namespace boost {
namespace mpl {

template<
      typename C
    , typename F1
    , typename F2
    >
struct apply_if
{
    typedef BOOST_DEDUCED_TYPENAME eval_if<C,F1,F2>::type type;
};

// (almost) copy & paste in order to save one more 
// recursively nested template instantiation to user
template<
      bool C
    , typename F1
    , typename F2
    >
struct apply_if_c
{
    typedef BOOST_DEDUCED_TYPENAME eval_if_c<C,F1,F2>::type type;
};

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_APPLY_IF_HPP_INCLUDED
