
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>
#include <boost/mpl/aux_/config/preprocessor.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)
#   define AUX_VECTOR_INCLIDE_DIR typeof_based
#elif defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
   || defined(BOOST_MPL_CFG_NO_NONTYPE_TEMPLATE_PARTIAL_SPEC)
#   define AUX_VECTOR_INCLIDE_DIR no_ctps
#else
#   define AUX_VECTOR_INCLIDE_DIR plain
#endif

#if !defined(BOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING)
#   define AUX_PREPROCESSED_HEADER \
    AUX_VECTOR_INCLIDE_DIR/BOOST_MPL_PREPROCESSED_HEADER \
/**/
#else
#   define AUX_PREPROCESSED_HEADER \
    BOOST_PP_CAT(AUX_VECTOR_INCLIDE_DIR,/)##BOOST_MPL_PREPROCESSED_HEADER \
/**/
#endif


#   include BOOST_PP_STRINGIZE(boost/mpl/vector/aux_/preprocessed/AUX_PREPROCESSED_HEADER)

#   undef AUX_PREPROCESSED_HEADER
#   undef AUX_VECTOR_INCLIDE_DIR

#undef BOOST_MPL_PREPROCESSED_HEADER
