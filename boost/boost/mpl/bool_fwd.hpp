
#ifndef BOOST_MPL_BOOL_FWD_HPP_INCLUDED
#define BOOST_MPL_BOOL_FWD_HPP_INCLUDED

// + file: boost/mpl/bool_fwd.hpp
// + last modified: 08/mar/03

// Copyright (c) 2000-03
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

namespace boost { namespace mpl {

template< bool C_ > struct bool_;

// shorcuts
typedef bool_<true> true_;
typedef bool_<false> false_;

}}

#endif // BOOST_MPL_BOOL_FWD_HPP_INCLUDED
