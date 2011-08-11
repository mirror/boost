
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(TTI_MEMBER_FUNCTION_GEN_HPP)
#define TTI_MEMBER_FUNCTION_GEN_HPP

#include <boost/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include "trait_gen.hpp"

/*

  The succeeding comments in this file are in doxygen format.

*/

/** \file
*/

/// Generates the macro metafunction name for BOOST_TTI_HAS_MEMBER_FUNCTION.
/**
    name  = the name of the member function.

    returns = the generated macro metafunction name.
*/
#define BOOST_TTI_HAS_MEMBER_FUNCTION_GEN_BASE(name) \
  BOOST_PP_CAT(has_member_function_,name) \
/**/

/// Generates the macro metafunction name for BOOST_TTI_MTFC_HAS_MEMBER_FUNCTION.
/**
    name  = the name of the member function.

    returns = the generated macro metafunction name.
*/
#define BOOST_TTI_MTFC_HAS_MEMBER_FUNCTION_GEN_BASE(name) \
  BOOST_PP_CAT(mtfc_has_member_function_,name) \
/**/

/// Generates the macro metafunction name within the Boost TTI namespace for BOOST_TTI_HAS_MEMBER_FUNCTION.
/**
    name  = the name of the member function.

    returns = the generated macro metafunction name.
*/
#define BOOST_TTI_HAS_MEMBER_FUNCTION_GEN(name) \
  BOOST_TTI_NAMESPACE::BOOST_TTI_HAS_MEMBER_FUNCTION_GEN_BASE(name) \
/**/

/// Generates the macro metafunction name within the Boost TTI namespace for BOOST_TTI_MTFC_HAS_MEMBER_FUNCTION.
/**
    name  = the name of the member function.

    returns = the generated macro metafunction name.
*/
#define BOOST_TTI_MTFC_HAS_MEMBER_FUNCTION_GEN(name) \
  BOOST_TTI_NAMESPACE::BOOST_TTI_MTFC_HAS_MEMBER_FUNCTION_GEN_BASE(name) \
/**/

#endif // TTI_MEMBER_FUNCTION_GEN_HPP
