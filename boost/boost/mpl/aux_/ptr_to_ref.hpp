
#ifndef BOOST_MPL_AUX_PTR_TO_REF_HPP_INCLUDED
#define BOOST_MPL_AUX_PTR_TO_REF_HPP_INCLUDED

// + file: boost/mpl/aux_/ptr_to_ref.hpp
// + last modified: 03/may/03

// Copyright (c) 2002-03
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

namespace boost { namespace mpl { namespace aux {

template< typename T > static T const& ptr_to_ref(T*);

}}}

#endif // BOOST_MPL_AUX_PTR_TO_REF_HPP_INCLUDED
