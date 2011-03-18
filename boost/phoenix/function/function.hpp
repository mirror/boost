/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_FUNCTION_FUNCTION_HPP
#define BOOST_PHOENIX_FUNCTION_FUNCTION_HPP

#include <boost/phoenix/function/function_handling.hpp>
#include <boost/phoenix/function/adapt_function.hpp>
#include <boost/preprocessor/facilities/expand.hpp>
#include <boost/preprocessor/logical/or.hpp>
#include <boost/utility/result_of.hpp>

namespace boost { namespace phoenix
{
    /////////////////////////////////////////////////////////////////////////////
    // Functions
    /////////////////////////////////////////////////////////////////////////////

/*

BOOST_PHOENIX_FUNCTION(
    test
  , (
        (
            N           // Number of Arguments
          , result_type // Result type, any 
          , (
                BODY
            )
        )
        (
            2
          , result_type
          , (
                BODY
            )
        )
    )
)

 */

#define BOOST_PHOENIX_FUNCTION_WHAT_POLYMORPH_RESULT                            \
    POLYMORPH
/**/

#define BOOST_PHOENIX_FUNCTION_WHAT_MONOMORPH_RESULT(_)                         \
    MONOMORPH
/**/

#define BOOST_PHOENIX_FUNCTION_MONOMORPH_RESULT(TYPE)                           \
    TYPE
/**/

#define BOOST_PHOENIX_FUNCTION_POLYMORPH_RESULT

#define BOOST_PHOENIX_FUNCTION_MONOMORPH(NAME, RESULT, BODIES)                  \
      BOOST_PHOENIX_FUNCTION_MONOMORPH_BASE(                                    \
            NAME                                                                \
          , RESULT                                                              \
          , BOOST_PP_CAT(BOOST_PHOENIX_FUNCTION_MONOMORPH_FILLER_0 BODIES,_END) \
        )                                                                       \
/**/
#define BOOST_PHOENIX_FUNCTION_POLYMORPH(NAME, RESULT, BODIES)                  \
      BOOST_PHOENIX_FUNCTION_POLYMOPRH_BASE(                                    \
            NAME                                                                \
          , BOOST_PP_CAT(BOOST_PHOENIX_FUNCTION_POLYMORPH_FILLER_0 BODIES,_END) \
        )                                                                       \

#define BOOST_PHOENIX_FUNCTION(NAME, TYPE, BODIES)                              \
    BOOST_PP_CAT(                                                               \
        BOOST_PHOENIX_FUNCTION_                                                 \
      , BOOST_PP_CAT(                                                           \
            BOOST_PHOENIX_FUNCTION_WHAT_                                        \
          , TYPE                                                                \
        )                                                                       \
    )(                                                                          \
        NAME                                                                    \
      , BOOST_PP_CAT(BOOST_PHOENIX_FUNCTION_, TYPE)                             \
      , BODIES                                                                  \
    )                                                                           \
/**/

#define BOOST_PHOENIX_FUNCTION_MONOMORPH_BASE(NAME, RESULT_TYPE, BODY_SEQ)      \
    namespace impl                                                              \
    {                                                                           \
        struct NAME                                                             \
        {                                                                       \
            typedef RESULT_TYPE result_type;                                    \
            BOOST_PP_SEQ_FOR_EACH(                                              \
                BOOST_PHOENIX_FUNCTION_MONOMORPH_DEFINE_BODY_S                  \
              , _                                                               \
              , BODY_SEQ                                                        \
            )                                                                   \
        };                                                                      \
    }                                                                           \
    BOOST_PP_SEQ_FOR_EACH(                                                      \
        BOOST_PHOENIX_FUNCTION_MONOMORPH_ADAPT_BODY_S                           \
      , NAME                                                                    \
      , BOOST_PP_SEQ_FOLD_LEFT(TEST, (BOOST_PP_TUPLE_ELEM(3, 0, BOOST_PP_SEQ_HEAD(BODY_SEQ))), BOOST_PP_SEQ_TAIL(BODY_SEQ)) \
    )                                                                           \
    
/**/

#define TEST(S, STATE, X)                                                       \
    BOOST_PP_IF(                                                                \
        TEST2(STATE, BOOST_PP_TUPLE_ELEM(3, 0, X)) \
      , STATE \
      , BOOST_PP_SEQ_PUSH_BACK(STATE, BOOST_PP_TUPLE_ELEM(3, 0, X)) \
    )

#define TEST2(SEQ, E)                                                           \
    BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_SEQ_FOLD_LEFT(TEST3, (0, E), SEQ))       \

#define TEST3(S, STATE, X)                                                          \
    (BOOST_PP_OR(BOOST_PP_TUPLE_ELEM(2, 0, STATE), BOOST_PP_EQUAL(BOOST_PP_TUPLE_ELEM(2, 1, STATE), X)), BOOST_PP_TUPLE_ELEM(2, 1, STATE))

#define BOOST_PHOENIX_FUNCTION_POLYMOPRH_BASE(NAME, BODY_SEQ)                   \
    namespace impl                                                              \
    {                                                                           \
        struct NAME                                                             \
        {                                                                       \
            template <typename Sig>                                             \
            struct result;                                                      \
        };                                                                      \
    }                                                                           \
    BOOST_PP_SEQ_FOR_EACH(                                                      \
        BOOST_PHOENIX_FUNCTION_POLYMORPH_ADAPT_BODY_S                           \
      , NAME                                                                    \
      , BODY_SEQ                                                                \
    )                                                                           \
/**/

#define BOOST_PHOENIX_FUNCTION_POLYMORPH_ADAPT_BODY_S(R, D, E)                  \
    BOOST_PHOENIX_ADAPT_FUNCTION(                                               \
        D                                                                       \
      , impl:: D                                                                \
      , BOOST_PP_TUPLE_ELEM(3, 0, E)                                            \
    )                                                                           \
/**/

#define BOOST_PHOENIX_FUNCTION_PARAMS(Z, N, D)                                  \
    BOOST_PP_COMMA_IF(N)                                                        \
    BOOST_PP_CAT(A, N)                                                          \
        BOOST_PP_TUPLE_ELEM(                                                    \
            BOOST_PP_TUPLE_ELEM(3, 0, D)                                        \
          , N                                                                   \
          , BOOST_PP_TUPLE_ELEM(3, 1, D)                                        \
        )                                                                       \

#define BOOST_PHOENIX_FUNCTION_MONOMORPH_DEFINE_BODY_S(R, D, E)                 \
    template <BOOST_PHOENIX_typename_A(BOOST_PP_TUPLE_ELEM(3, 0, E))>           \
    result_type operator()(                                                     \
        BOOST_PP_REPEAT(                                                        \
            BOOST_PP_TUPLE_ELEM(3, 0, E)                                        \
          , BOOST_PHOENIX_FUNCTION_PARAMS                                       \
          , E                                                                   \
        )                                                                       \
    )                                                                           \
    {                                                                           \
        BOOST_PP_EXPAND(                                                        \
            BOOST_PHOENIX_FUNCTION_BODY                                         \
            BOOST_PP_TUPLE_ELEM(3, 2, E)                                        \
        )                                                                       \
    }                                                                           \
/**/

#define BOOST_PHOENIX_FUNCTION_BODY(BODY) BODY

#define BOOST_PHOENIX_FUNCTION_ADAPT_BODY_S(R, D, E)                            \
    BOOST_PHOENIX_ADAPT_FUNCTION(                                               \
        D                                                                       \
      , impl:: D                                                                \
      , E                                                                       \
    )                                                                           \
/**/

#define BOOST_PHOENIX_FUNCTION_POLYMORPH_FILLER_0(X, Y, Z)                      \
    ((X, Y, Z)) BOOST_PHOENIX_FUNCTION_POLYMORPH_FILLER_1                       \
/**/

#define BOOST_PHOENIX_FUNCTION_POLYMORPH_FILLER_1(X, Y, Z)                      \
    ((X, Y, Z)) BOOST_PHOENIX_FUNCTION_POLYMORPH_FILLER_0                       \
/**/

#define BOOST_PHOENIX_FUNCTION_POLYMORPH_FILLER_0_END
#define BOOST_PHOENIX_FUNCTION_POLYMORPH_FILLER_1_END

#define BOOST_PHOENIX_FUNCTION_MONOMORPH_FILLER_0(X, Y, Z)                      \
    ((X, Y, Z)) BOOST_PHOENIX_FUNCTION_MONOMORPH_FILLER_1                       \
/**/

#define BOOST_PHOENIX_FUNCTION_MONOMORPH_FILLER_1(X, Y, Z)                      \
    ((X, Y, Z)) BOOST_PHOENIX_FUNCTION_MONOMORPH_FILLER_0                       \
/**/

#define BOOST_PHOENIX_FUNCTION_MONOMORPH_FILLER_0_END
#define BOOST_PHOENIX_FUNCTION_MONOMORPH_FILLER_1_END

    // functor which returns our lazy function call extension
    template<typename F>
    struct function
    {
        function() {}

        function(F f)
          : f(f)
        {}

        template <typename Sig>
        struct result;

        typename expression::function<F>::type const
        operator()() const
        {
            return expression::function<F>::make(f);
        }

        // Bring in the rest
        #include <boost/phoenix/function/detail/function_operator.hpp>

        F f;
    };

}

    template<typename F>
    struct result_of<phoenix::function<F>()>
      : phoenix::expression::function<F>
    {};

}

#endif

