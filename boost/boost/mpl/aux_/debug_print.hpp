//-----------------------------------------------------------------------------
// boost mpl/aux_/debug_print.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2002
// Fernando Cacciola, Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_AUX_DEBUG_PRINT_HPP_INCLUDED
#define BOOST_MPL_AUX_DEBUG_PRINT_HPP_INCLUDED

namespace boost {
namespace mpl {
namespace aux {

template< typename T >
struct print_
{
    enum { value = T::not_existing_memeber };
};

} // namespace aux
} // namespace mpl
} // namespace boost

#define BOOST_MPL_AUX_DEBUG_PRINT(type) \
enum { mpl_debug_print_##type = boost::mpl::aux::print_<type>::value } ;\
/**/

#endif // BOOST_MPL_AUX_DEBUG_PRINT_HPP_INCLUDED
