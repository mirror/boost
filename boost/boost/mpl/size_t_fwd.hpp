
#ifndef BOOST_MPL_SIZE_T_FWD_HPP_INCLUDED
#define BOOST_MPL_SIZE_T_FWD_HPP_INCLUDED

// + file: boost/mpl/size_t_fwd.hpp
// + last modified: 08/mar/03

// Copyright (c) 2000-03
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

#include "boost/config.hpp" // make sure 'size_t' is placed into 'std'
#include <cstddef>

namespace boost { namespace mpl {
template< std::size_t N > struct size_t;
}}

#endif // BOOST_MPL_SIZE_T_FWD_HPP_INCLUDED
