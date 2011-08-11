
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(TTI_TRAIT_GEN_HPP)
#define TTI_TRAIT_GEN_HPP

#include "namespace_gen.hpp"

/*

  The succeeding comments in this file are in doxygen format.

*/

/** \file
*/

/// Generates the macro metafunction name for any macro metafunction using the 'trait' form.
/**
    trait  = the name of the trait.

    returns = the generated macro metafunction name.
*/
#define BOOST_TTI_TRAIT_GEN_BASE(trait) \
  trait \
/**/

/// Generates the macro metafunction name within the Boost TTI namespace for any macro metafunction using the 'trait' form.
/**
    trait  = the name of the trait.

    returns = the generated macro metafunction name.
*/
#define BOOST_TTI_TRAIT_GEN(trait) \
  BOOST_TTI_NAMESPACE::BOOST_TTI_TRAIT_GEN_BASE(trait) \
/**/

#endif // TTI_TRAIT_GEN_HPP
