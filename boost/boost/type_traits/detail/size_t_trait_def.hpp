//-----------------------------------------------------------------------------
// boost/type_traits/detail/size_t_trait_def.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2002
// Aleksey Gurtovoy
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

// no include guards, the header is intended for multiple inclusion!

#include "boost/type_traits/detail/size_t_trait.hpp"
#include "boost/type_traits/detail/template_arity_spec.hpp"
#include "boost/mpl/aux_/lambda_support.hpp"

#define BOOST_TT_AUX_SIZE_T_TRAIT_DEF1(trait,T,value) \
template< typename T > struct trait \
    : ::boost::type_traits::size_t_trait< value > \
{ \
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,trait,(T)) \
}; \
\
BOOST_TT_AUX_TEMPLATE_ARITY_SPEC(1,trait) \
/**/

#define BOOST_TT_AUX_SIZE_T_TRAIT_SPEC1(trait,spec,value) \
template<> struct trait<spec> \
    : ::boost::type_traits::size_t_trait< value > \
{ \
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,trait,(spec)) \
}; \
/**/ 

// BOOST_TT_AUX_TEMPLATE_ARITY_SPEC(1,trait)

#define BOOST_TT_AUX_SIZE_T_TRAIT_PARTIAL_SPEC1_1(param,trait,spec,value) \
template< param > struct trait<spec> \
    : ::boost::type_traits::size_t_trait< value > \
{ \
}; \
/**/
