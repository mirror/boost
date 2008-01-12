#ifndef BOOST_PP_IS_ITERATING
    ///////////////////////////////////////////////////////////////////////////////
    /// \file fold.hpp
    /// Contains definition of the fold<> and reverse_fold<> transforms.
    //
    //  Copyright 2007 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #ifndef BOOST_PROTO_TRANSFORM_FOLD_HPP_EAN_11_04_2007
    #define BOOST_PROTO_TRANSFORM_FOLD_HPP_EAN_11_04_2007

    #include <boost/xpressive/proto/detail/prefix.hpp>
    #include <boost/preprocessor/cat.hpp>
    #include <boost/preprocessor/iteration/iterate.hpp>
    #include <boost/preprocessor/arithmetic/inc.hpp>
    #include <boost/preprocessor/arithmetic/sub.hpp>
    #include <boost/preprocessor/repetition/repeat.hpp>
    #include <boost/fusion/include/fold.hpp>
    #include <boost/fusion/include/reverse.hpp>
    #include <boost/xpressive/proto/proto_fwd.hpp>
    #include <boost/xpressive/proto/fusion.hpp>
    #include <boost/xpressive/proto/traits.hpp>
    #include <boost/xpressive/proto/detail/suffix.hpp>

    namespace boost { namespace proto
    {

        namespace transform
        {

            namespace detail
            {

                template<typename Transform, typename Visitor>
                struct as_callable
                {
                    as_callable(Visitor &v)
                      : v_(v)
                    {}

                    typedef when<_, Transform> Tfx;

                    template<typename Sig>
                    struct result;

                    template<typename This, typename Expr, typename State>
                    struct result<This(Expr, State)>
                      : Tfx::template result<void(typename proto::detail::remove_cv_ref<Expr>::type
                                                , typename proto::detail::remove_cv_ref<State>::type
                                                , Visitor)>
                    {};

                    template<typename Expr, typename State>
                    typename Tfx::template result<void(Expr, State, Visitor)>::type
                    operator ()(Expr const &expr, State const &state) const
                    {
                        return Tfx()(expr, state, this->v_);
                    }

                private:
                    Visitor &v_;
                };


                template<typename Fun, typename Expr, typename State, typename Visitor, long Arity = Expr::proto_arity::value>
                struct fold_impl
                {};

                template<typename Fun, typename Expr, typename State, typename Visitor, long Arity = Expr::proto_arity::value>
                struct reverse_fold_impl
                {};

                #define BOOST_PROTO_ARG_N_TYPE(n)\
                    BOOST_PP_CAT(proto_arg, n)\
                    /**/

                #define BOOST_PROTO_FOLD_STATE_TYPE(z, n, data)\
                    typedef typename when<_, Fun>::template\
                        result<void(typename Expr::BOOST_PROTO_ARG_N_TYPE(n)::proto_base_expr, BOOST_PP_CAT(state, n), Visitor)>::type\
                    BOOST_PP_CAT(state, BOOST_PP_INC(n));\
                    /**/

                #define BOOST_PROTO_FOLD_STATE(z, n, data)\
                    BOOST_PP_CAT(state, BOOST_PP_INC(n)) const &BOOST_PP_CAT(s, BOOST_PP_INC(n)) =\
                        when<_, Fun>()(expr.BOOST_PP_CAT(arg, n).proto_base(), BOOST_PP_CAT(s, n), visitor);\
                    /**/

                #define BOOST_PROTO_REVERSE_FOLD_STATE_TYPE(z, n, data)\
                    typedef typename when<_, Fun>::template\
                        result<void(typename Expr::BOOST_PROTO_ARG_N_TYPE(BOOST_PP_SUB(data, BOOST_PP_INC(n)))::proto_base_expr, BOOST_PP_CAT(state, BOOST_PP_SUB(data, n)), Visitor)>::type\
                    BOOST_PP_CAT(state, BOOST_PP_SUB(data, BOOST_PP_INC(n)));\
                    /**/

                #define BOOST_PROTO_REVERSE_FOLD_STATE(z, n, data)\
                    BOOST_PP_CAT(state, BOOST_PP_SUB(data, BOOST_PP_INC(n))) const &BOOST_PP_CAT(s, BOOST_PP_SUB(data, BOOST_PP_INC(n))) =\
                        when<_, Fun>()(expr.BOOST_PP_CAT(arg, BOOST_PP_SUB(data, BOOST_PP_INC(n))).proto_base(), BOOST_PP_CAT(s, BOOST_PP_SUB(data, n)), visitor);\
                    /**/

                #define BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_PROTO_MAX_ARITY, <boost/xpressive/proto/transform/fold.hpp>))
                #include BOOST_PP_ITERATE()

                #undef BOOST_PROTO_REVERSE_FOLD_STATE
                #undef BOOST_PROTO_REVERSE_FOLD_STATE_TYPE
                #undef BOOST_PROTO_FOLD_STATE
                #undef BOOST_PROTO_FOLD_STATE_TYPE
                #undef BOOST_PROTO_ARG_N_TYPE

            } // namespace detail

            template<typename Sequence, typename State0, typename Fun>
            struct fold : callable
            {
                template<typename Sig>
                struct result;

                template<typename This, typename Expr, typename State, typename Visitor>
                struct result<This(Expr, State, Visitor)>
                  : fusion::result_of::fold<
                        typename when<_, Sequence>::template result<void(Expr, State, Visitor)>::type
                      , typename when<_, State0>::template result<void(Expr, State, Visitor)>::type
                      , detail::as_callable<Fun, Visitor>
                    >
                {};

                template<typename Expr, typename State, typename Visitor>
                typename result<void(Expr, State, Visitor)>::type
                operator ()(Expr const &expr, State const &state, Visitor &visitor) const
                {
                    detail::as_callable<Fun, Visitor> fun(visitor);
                    return fusion::fold(
                        when<_, Sequence>()(expr, state, visitor)
                      , when<_, State0>()(expr, state, visitor)
                      , fun
                    );
                }
            };

            template<typename Sequence, typename State, typename Fun>
            struct reverse_fold
              : fold<_reverse(Sequence), State, Fun>
            {};

            // A fold transform that transforms the left sub-tree and
            // uses the result as state while transforming the right.
            template<typename State0, typename Fun>
            struct fold<_, State0, Fun> : callable
            {
                template<typename Sig>
                struct result;

                template<typename This, typename Expr, typename State, typename Visitor>
                struct result<This(Expr, State, Visitor)>
                  : detail::fold_impl<
                        Fun
                      , typename Expr::proto_base_expr
                      , typename when<_, State0>::template result<void(Expr, State, Visitor)>::type
                      , Visitor
                    >
                {};

                template<typename Expr, typename State, typename Visitor>
                typename result<void(Expr, State, Visitor)>::type
                operator ()(Expr const &expr, State const &state, Visitor &visitor) const
                {
                    return result<void(Expr, State, Visitor)>::call(
                        expr.proto_base()
                      , when<_, State0>()(expr, state, visitor)
                      , visitor
                    );
                }
            };

            // A reverse_fold compiler that compiles the right sub-tree and
            // uses the result as state while compiling the left.
            template<typename State0, typename Fun>
            struct reverse_fold<_, State0, Fun> : callable
            {
                template<typename Sig>
                struct result;

                template<typename This, typename Expr, typename State, typename Visitor>
                struct result<This(Expr, State, Visitor)>
                  : detail::reverse_fold_impl<
                        Fun
                      , typename Expr::proto_base_expr
                      , typename when<_, State0>::template result<void(Expr, State, Visitor)>::type
                      , Visitor
                    >
                {};

                template<typename Expr, typename State, typename Visitor>
                typename result<void(Expr, State, Visitor)>::type
                operator ()(Expr const &expr, State const &state, Visitor &visitor) const
                {
                    return result<void(Expr, State, Visitor)>::call(
                        expr.proto_base()
                      , when<_, State0>()(expr, state, visitor)
                      , visitor
                    );
                }
            };
        }

        template<typename Sequence, typename State, typename Fun>
        struct is_callable<transform::fold<Sequence, State, Fun> >
          : mpl::true_
        {};

        template<typename Sequence, typename State, typename Fun>
        struct is_callable<transform::reverse_fold<Sequence, State, Fun> >
          : mpl::true_
        {};

    }}

    #endif

#else

    #define N BOOST_PP_ITERATION()

            template<typename Fun, typename Expr, typename state0, typename Visitor>
            struct fold_impl<Fun, Expr, state0, Visitor, N>
            {
                BOOST_PP_REPEAT(N, BOOST_PROTO_FOLD_STATE_TYPE, N)
                typedef BOOST_PP_CAT(state, N) type;

                static type call(Expr const &expr, state0 const &s0, Visitor &visitor)
                {
                    BOOST_PP_REPEAT(N, BOOST_PROTO_FOLD_STATE, N)
                    return BOOST_PP_CAT(s, N);
                }
            };

            template<typename Fun, typename Expr, typename BOOST_PP_CAT(state, N), typename Visitor>
            struct reverse_fold_impl<Fun, Expr, BOOST_PP_CAT(state, N), Visitor, N>
            {
                BOOST_PP_REPEAT(N, BOOST_PROTO_REVERSE_FOLD_STATE_TYPE, N)
                typedef state0 type;

                static type call(Expr const &expr, BOOST_PP_CAT(state, N) const &BOOST_PP_CAT(s, N), Visitor &visitor)
                {
                    BOOST_PP_REPEAT(N, BOOST_PROTO_REVERSE_FOLD_STATE, N)
                    return s0;
                }
            };

    #undef N

#endif
