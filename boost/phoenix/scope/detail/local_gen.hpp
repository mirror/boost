
#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)
#ifndef BOOST_PHOENIX_SCOPE_DETAIL_LOCAL_GEN_HPP
#define BOOST_PHOENIX_SCOPE_DETAIL_LOCAL_GEN_HPP

#include <boost/phoenix/support/iterate.hpp>

#include <boost/phoenix/scope/detail/preprocessed/local_gen.hpp>

#endif
#else

#if !BOOST_PHOENIX_IS_ITERATING

#ifndef BOOST_PHOENIX_SCOPE_DETAIL_LOCAL_GEN_HPP
#define BOOST_PHOENIX_SCOPE_DETAIL_LOCAL_GEN_HPP

#include <boost/phoenix/support/iterate.hpp>

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/local_gen_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif

/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

#define BOOST_PHOENIX_LOCAL_GEN_KEY_TYPES(_, N, __)                             \
    BOOST_PP_COMMA_IF(N)                                                        \
    typename proto::result_of::value<                                           \
        typename proto::result_of::child_c<                                     \
            typename proto::result_of::child_c<A ## N, 0>::type                 \
          , 0                                                                   \
        >::type                                                                 \
    >::type::type::key_type                                                     \
/**/

#define BOOST_PHOENIX_LOCAL_GEN_ACTOR(_, N, __)                                 \
    BOOST_PP_COMMA_IF(N) proto::child_c<1>(a ## N)                              \
/**/

#define BOOST_PHOENIX_LOCAL_GEN_ACTOR_TYPES(_, n, __)                           \
    BOOST_PP_COMMA_IF(n) typename proto::result_of::child_c<A ## n, 1>::type    \
/**/

#define BOOST_PHOENIX_ITERATION_PARAMS                                          \
    (3, (3, BOOST_PHOENIX_LOCAL_LIMIT,                                          \
    <boost/phoenix/scope/detail/local_gen.hpp>))
#include BOOST_PHOENIX_ITERATE()

#undef BOOST_PHOENIX_LOCAL_GEN_KEY_TYPES
#undef BOOST_PHOENIX_LOCAL_GEN_ACTOR
#undef BOOST_PHOENIX_LOCAL_GEN_ACTOR_TYPES

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif

#else

        template <BOOST_PHOENIX_typename_A>
        BOOST_PHOENIX_LOCAL_GEN_NAME<
            BOOST_PP_CAT(
                vector
              , BOOST_PHOENIX_ITERATION)<BOOST_PHOENIX_LOCAL_GEN_ACTOR_TYPES>
          , detail::map_local_index_to_tuple<
                BOOST_PP_REPEAT(
                    BOOST_PHOENIX_ITERATION
                  , BOOST_PHOENIX_LOCAL_GEN_KEY_TYPES
                  , _
                )
            >
        > const
        operator()(BOOST_PHOENIX_A_const_ref_a) const
        {
            return
                BOOST_PP_CAT(
                     vector
                  , BOOST_PHOENIX_ITERATION
                )<
                    BOOST_PP_REPEAT(
                        BOOST_PHOENIX_ITERATION
                      , BOOST_PHOENIX_LOCAL_GEN_ACTOR_TYPES_I
                      , _
                    )
                >(
                    BOOST_PP_REPEAT(
                        BOOST_PHOENIX_ITERATION
                      , BOOST_PHOENIX_LOCAL_GEN_ACTOR
                      , _
                    )
                );
        }

#endif

#endif // BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES
