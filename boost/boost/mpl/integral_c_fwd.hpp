
#ifndef BOOST_MPL_INTEGRAL_C_FWD_HPP_INCLUDED
#define BOOST_MPL_INTEGRAL_C_FWD_HPP_INCLUDED

// + file: boost/mpl/integral_c_fwd.hpp
// + last modified: 08/mar/03

// Copyright (c) 2000-03
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

#include "boost/mpl/aux_/config/workaround.hpp"

namespace boost { namespace mpl {
#if BOOST_WORKAROUND(__HP_aCC, BOOST_TESTED_AT(53800))
// the type of non-type template arguments may not depend on template arguments
template< typename T, long N > struct integral_c;
#else
template< typename T, T N > struct integral_c;
#endif
}}

#endif // BOOST_MPL_INTEGRAL_C_FWD_HPP_INCLUDED
