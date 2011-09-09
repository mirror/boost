#ifndef BOOST_PP_IS_ITERATING
/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_VECTOR50_FWD_HPP_INCLUDED)
#define BOOST_FUSION_VECTOR50_FWD_HPP_INCLUDED

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

namespace boost { namespace fusion
{
    // expand vector41 to vector50
    #define BOOST_PP_FILENAME_1 <boost/fusion/container/vector/vector50_fwd.hpp>
    #define BOOST_PP_ITERATION_LIMITS (41, 50)
    #include BOOST_PP_ITERATE()

}}

#endif

#else

    template <BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), typename T)>
    struct BOOST_PP_CAT(vector, BOOST_PP_ITERATION());

#endif
