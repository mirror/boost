// Copyright (C) 2004 Arkadiy Vertleyb
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_LIMIT_SIZE_HPP_INCLUDED
#define BOOST_TYPEOF_LIMIT_SIZE_HPP_INCLUDED

#include "boost/mpl/vector.hpp"
#include "boost/mpl/aux_/config/ctps.hpp"
#include "boost/preprocessor/iterate.hpp"
#include "boost/preprocessor/if.hpp"
#include "boost/config.hpp"

#ifndef BOOST_TYPEOF_LIMIT_SIZE
#define BOOST_TYPEOF_LIMIT_SIZE 50
#endif//BOOST_TYPEOF_LIMIT_SIZE

#if (BOOST_TYPEOF_LIMIT_SIZE > BOOST_MPL_LIMIT_VECTOR_SIZE)

namespace boost
{ 
    namespace mpl 
    {
        #define BOOST_PP_ITERATION_PARAMS_1 (3,(        \
            BOOST_PP_INC(BOOST_MPL_LIMIT_VECTOR_SIZE),  \
            BOOST_TYPEOF_LIMIT_SIZE,                    \
            "boost/mpl/vector/aux_/numbered.hpp"))

        #include BOOST_PP_ITERATE()
    }
}

#endif//BOOST_TYPEOF_LIMIT_SIZE > BOOST_MPL_LIMIT_VECTOR_SIZE

#endif//BOOST_TYPEOF_LIMIT_SIZE_HPP_INCLUDED
