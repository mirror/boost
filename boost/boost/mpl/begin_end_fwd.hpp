//-----------------------------------------------------------------------------
// boost mpl/begin_end_fwd.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_BEGIN_END_FWD_HPP_INCLUDED
#define BOOST_MPL_BEGIN_END_FWD_HPP_INCLUDED

namespace boost {
namespace mpl {

template< typename Tag > struct begin_traits;
template< typename Tag > struct end_traits;

template< typename Sequence > struct begin;
template< typename Sequence > struct end;

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_BEGIN_END_FWD_HPP_INCLUDED
