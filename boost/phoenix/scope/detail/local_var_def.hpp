
#if !BOOST_PHOENIX_IS_ITERATING

/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_SCOPE_LOCAL_VAR_DEF_HPP
#define BOOST_PHOENIX_SCOPE_LOCAL_VAR_DEF_HPP

#include <boost/phoenix/support/iterate.hpp>

#define M0(Z, N, D)                                                             \
    fusion::pair<BOOST_PP_CAT(Tag, N), BOOST_PP_CAT(A, N)>                      \
/**/

#define M1(Z, N, D)                                                             \
    fusion::pair<                                                               \
        BOOST_PP_CAT(Tag, N)                                                    \
      , typename evaluator::impl<                                               \
            BOOST_PP_CAT(A, N) const &                                          \
          , Context                                                             \
          , int                                                                 \
        >::result_type                                                          \
    >                                                                           \
/**/

#define M2(Z, N, D)                                                             \
    typedef                                                                     \
        fusion::pair<                                                           \
            BOOST_PP_CAT(Tag, N)                                                \
          , typename evaluator::impl<                                           \
                BOOST_PP_CAT(A, N) const &                                      \
              , Context                                                         \
              , int                                                             \
            >::result_type                                                      \
        >                                                                       \
        BOOST_PP_CAT(pair, N);                                                  \
/**/

#define M3(Z, N, D)                                                             \
    BOOST_PP_CAT(pair, N)(                                                      \
        boost::phoenix::eval(fusion::at_key<BOOST_PP_CAT(Tag, N)>(locals), ctx)                 \
    )                                                                           \
/**/

        template <typename Tag0, typename A0, typename Context>
        struct local_var_def_is_nullary<
            fusion::map<
                fusion::pair<Tag0, A0>
            >
          , Context
        >
            : evaluator::impl<A0 const &, Context, int>::result_type
        {};

#define BOOST_PHOENIX_ITERATION_PARAMS                                          \
    (4, (2, BOOST_PHOENIX_LOCAL_LIMIT,                                          \
    <boost/phoenix/scope/detail/local_var_def.hpp>, 1))
#include BOOST_PHOENIX_ITERATE()


        struct local_var_def_eval
        {
            template <typename Sig>
            struct result;
#define BOOST_PHOENIX_ITERATION_PARAMS                                          \
    (4, (1, BOOST_PHOENIX_LOCAL_LIMIT,                                          \
    <boost/phoenix/scope/detail/local_var_def.hpp>, 2))
#include BOOST_PHOENIX_ITERATE()

        };

#undef M0
#undef M1
#undef M2
#undef M3

#endif

#else

#if BOOST_PP_ITERATION_FLAGS() == 1
        template <
            BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, typename Tag)
          , BOOST_PHOENIX_typename_A
          , typename Context
        >
        struct local_var_def_is_nullary<
            fusion::map<
                BOOST_PP_ENUM(BOOST_PHOENIX_ITERATION, M0, _)
            >
          , Context
        >
            : mpl::and_<
                typename evaluator::impl<
                    BOOST_PP_CAT(
                        A
                      , BOOST_PP_DEC(BOOST_PHOENIX_ITERATION)
                    ) const &
                  , Context
                  , int
                >::result_type
              , local_var_def_is_nullary<
                    fusion::map<
                        BOOST_PP_ENUM(
                            BOOST_PP_DEC(BOOST_PHOENIX_ITERATION)
                          , M0
                          , _
                        )
                    >
                  , Context
                >
            >
        {};

#endif
            
#if BOOST_PP_ITERATION_FLAGS() == 2
            template <
                typename This
              , BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, typename Tag)
              , BOOST_PHOENIX_typename_A
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        BOOST_PP_ENUM(BOOST_PHOENIX_ITERATION, M0, _)
                    > const &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        BOOST_PP_ENUM(BOOST_PHOENIX_ITERATION, M1, _)
                    >
                    type;
            };

            template <
                typename This
              , BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, typename Tag)
              , BOOST_PHOENIX_typename_A
              , typename Context
            >
            struct result<
                This(
                    fusion::map<
                        BOOST_PP_ENUM(BOOST_PHOENIX_ITERATION, M0, _)
                    > &
                  , Context
                )
            >
            {
                typedef
                    fusion::map<
                        BOOST_PP_ENUM(BOOST_PHOENIX_ITERATION, M1, _)
                    >
                    type;
            };
            
            template <
                BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, typename Tag)
              , BOOST_PHOENIX_typename_A
              , typename Context
            >
            typename result<
                local_var_def_eval(
                    fusion::map<
                        BOOST_PP_ENUM(BOOST_PHOENIX_ITERATION, M0, _)
                    > const &
                  , Context const &)
            >::type const
            operator()(
                fusion::map<
                    BOOST_PP_ENUM(BOOST_PHOENIX_ITERATION, M0, _)
                > const & locals
              , Context const & ctx
            ) const
            {
                BOOST_PP_REPEAT(BOOST_PHOENIX_ITERATION, M2, _)

                return
                    typename result<
                        local_var_def_eval(
                            fusion::map<
                                BOOST_PP_ENUM(BOOST_PHOENIX_ITERATION, M0, _)
                            > const&
                          , Context const&
                        )
                    >::type(
                        BOOST_PP_ENUM(BOOST_PHOENIX_ITERATION, M3, _)
                    );
            }
#endif

#endif
