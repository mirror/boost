/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_FUNCTION_ADAPT_FUNCTION_HPP
#define BOOST_PHOENIX_FUNCTION_ADAPT_FUNCTION_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/function/function.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/facilities/identity.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

#define BOOST_PHOENIX_ADAPT_FUNCTION_NULLARY(NAME, FUNC)                        \
    expression::function<FUNC>::type const                                      \
    inline NAME()                                                               \
    {                                                                           \
        return expression::function<FUNC>::make(FUNC());                        \
    }                                                                           \
/**/


#define BOOST_PHOENIX_ADAPT_FUNCTION(NAME, FUNC, N)                             \
    template <BOOST_PHOENIX_typename_A(N)>                                      \
    typename expression::function<FUNC, BOOST_PHOENIX_A(N)>::type const         \
    inline NAME(BOOST_PHOENIX_A_const_ref_a(N))                                 \
    {                                                                           \
        return expression::                                                     \
            function<FUNC, BOOST_PHOENIX_A(N)>::                                \
                make(FUNC(), BOOST_PHOENIX_a(N));                               \
    }                                                                           \
/**/


#define BOOST_PHOENIX_ADAPT_FUNCTION_VARARG(NAME, FUNC)                         \
    BOOST_PHOENIX_ADAPT_FUNCTION_NULLARY(NAME, FUNC)                            \
    BOOST_PP_REPEAT_FROM_TO(                                                    \
        1                                                                       \
      , BOOST_PHOENIX_LIMIT                                                     \
      , BOOST_PHOENIX_ADAPT_FUNCTION_VARARG_R                                   \
      , (NAME, FUNC)                                                            \
    )                                                                           \
/**/

#define BOOST_PHOENIX_ADAPT_FUNCTION_VARARG_R(Z, N, D)                          \
    BOOST_PHOENIX_ADAPT_FUNCTION(                                               \
        BOOST_PP_TUPLE_ELEM(2, 0, D)                                            \
      , BOOST_PP_TUPLE_ELEM(2, 1, D)                                            \
      , N                                                                       \
    )                                                                           \
/**/

#endif
