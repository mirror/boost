/*=============================================================================
    Copyright (c) 2006-2007 Tobias Schwinger
  
    Use modification and distribution are subject to the Boost Software 
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

// No include guard - this file is included multiple times intentionally.

#if !defined(BOOST_PP_IS_ITERATING)

#   if !defined(BOOST_FUSION_FUNCTIONAL_ADAPTER_DETAIL_GEN_RESULT_OF_SPEC_HPP_INCLUDED)

#       include <boost/preprocessor/iteration/iterate.hpp>
#       include <boost/preprocessor/repetition/enum_params.hpp>
#       include <boost/preprocessor/repetition/enum_binary_params.hpp>
#       include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#       include <boost/preprocessor/facilities/intercept.hpp>

#       include <boost/utility/result_of.hpp>

#       include <boost/fusion/functional/adapter/detail/access.hpp>

#       define BOOST_FUSION_FUNCTIONAL_ADAPTER_DETAIL_GEN_RESULT_OF_SPEC_HPP_INCLUDED
#   endif

#   if !defined(BOOST_FUSION_CLASS_TPL_PARAMS)
#       error "BOOST_FUSION_CLASS_TPL_PARAMS undefined"
#   endif
#   if !defined(BOOST_FUSION_CLASS_TPL_SPEC)
#       error "BOOST_FUSION_CLASS_TPL_SPEC undefined"
#   endif

#   if !defined(BOOST_FUSION_FUNC_OBJ_ARITY)
#       define  BOOST_PP_ITERATION_LIMITS (1,1)
#   else
#       define  BOOST_PP_ITERATION_LIMITS (0,BOOST_FUSION_FUNC_OBJ_ARITY)
#   endif
#   define  BOOST_PP_FILENAME_1                                                \
       <boost/fusion/functional/adapter/detail/gen_result_of_spec.hpp>

namespace boost
{
    #include BOOST_PP_ITERATE()
}

#   undef BOOST_FUSION_CLASS_TPL_PARAMS
#   undef BOOST_FUSION_CLASS_TPL_SPEC
#   if defined(BOOST_FUSION_FUNC_OBJ_ARITY)
#       undef BOOST_FUSION_FUNC_OBJ_ARITY
#   endif

#else // defined(BOOST_PP_IS_ITERATING)
///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////

#   define N BOOST_PP_ITERATION()

    template< BOOST_FUSION_CLASS_TPL_PARAMS 
        BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A) >
    struct result_of< BOOST_FUSION_CLASS_TPL_SPEC (BOOST_PP_ENUM_PARAMS(N,A)) >
    {
        typedef typename BOOST_FUSION_CLASS_TPL_SPEC ::template result
            <BOOST_PP_ENUM_BINARY_PARAMS(N, typename fusion::detail::r2fp<A,
                >::type BOOST_PP_INTERCEPT)>::type type;
    };

    template< BOOST_FUSION_CLASS_TPL_PARAMS 
        BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A) >
    struct result_of< BOOST_FUSION_CLASS_TPL_SPEC & (BOOST_PP_ENUM_PARAMS(N,A)) >
    {
        typedef typename BOOST_FUSION_CLASS_TPL_SPEC ::template result
            <BOOST_PP_ENUM_BINARY_PARAMS(N, typename fusion::detail::r2fp<A,
                >::type BOOST_PP_INTERCEPT)>::type type;
    };

    template< BOOST_FUSION_CLASS_TPL_PARAMS 
        BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A) >
    struct result_of< BOOST_FUSION_CLASS_TPL_SPEC const (BOOST_PP_ENUM_PARAMS(N,A)) >
    {
        typedef typename BOOST_FUSION_CLASS_TPL_SPEC ::template result
            <BOOST_PP_ENUM_BINARY_PARAMS(N, typename fusion::detail::r2fp<A,
                >::type BOOST_PP_INTERCEPT)>::type type;
    };

    template< BOOST_FUSION_CLASS_TPL_PARAMS 
        BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A) >
    struct result_of< BOOST_FUSION_CLASS_TPL_SPEC const & (BOOST_PP_ENUM_PARAMS(N,A)) >
    {
        typedef typename BOOST_FUSION_CLASS_TPL_SPEC ::template result
            <BOOST_PP_ENUM_BINARY_PARAMS(N, typename fusion::detail::r2fp<A,
                >::type BOOST_PP_INTERCEPT)>::type type;
    };

#   undef N

#endif

