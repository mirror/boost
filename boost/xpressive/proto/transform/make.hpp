#ifndef BOOST_PP_IS_ITERATING
    ///////////////////////////////////////////////////////////////////////////////
    /// \file make.hpp
    /// Contains definition of the make<> transform.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #ifndef BOOST_PROTO_TRANSFORM_MAKE_HPP_EAN_12_02_2007
    #define BOOST_PROTO_TRANSFORM_MAKE_HPP_EAN_12_02_2007

    #include <boost/xpressive/proto/detail/prefix.hpp>
    #include <boost/detail/workaround.hpp>
    #include <boost/preprocessor/repetition/enum.hpp>
    #include <boost/preprocessor/repetition/enum_params.hpp>
    #include <boost/preprocessor/repetition/enum_trailing_params.hpp>
    #include <boost/preprocessor/repetition/enum_binary_params.hpp>
    #include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
    #include <boost/preprocessor/repetition/repeat_from_to.hpp>
    #include <boost/preprocessor/facilities/intercept.hpp>
    #include <boost/preprocessor/cat.hpp>
    #include <boost/preprocessor/iteration/iterate.hpp>
    #include <boost/preprocessor/selection/max.hpp>
    #include <boost/preprocessor/arithmetic/inc.hpp>
    #include <boost/mpl/aux_/has_type.hpp>
    #include <boost/mpl/aux_/template_arity.hpp>
    #include <boost/mpl/aux_/lambda_arity_param.hpp>
    #include <boost/utility/result_of.hpp>
    #include <boost/xpressive/proto/proto_fwd.hpp>
    #include <boost/xpressive/proto/traits.hpp>
    #include <boost/xpressive/proto/args.hpp>
    #include <boost/xpressive/proto/detail/as_lvalue.hpp>
    #include <boost/xpressive/proto/detail/suffix.hpp>

    namespace boost { namespace proto
    {

        namespace transform
        {
            namespace detail
            {
                using proto::detail::as_lvalue;

                template<BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(BOOST_PROTO_MAX_ARITY, typename A, void)>
                struct typelist
                {
                    typedef void type;
                };

                template<typename T, bool HasType = mpl::aux::has_type<T>::value>
                struct nested_type
                {
                    typedef typename T::type type;
                };

                template<typename T>
                struct nested_type<T, false>
                {
                    typedef T type;
                };

                template<typename T, typename Args, typename Void = void>
                struct nested_type_if
                  : nested_type<T>
                {};

                template<typename R, typename Expr, typename State, typename Visitor
                    , bool IsTransform = is_callable<R>::value
                >
                struct make_if_;

                template<typename R, typename Expr, typename State, typename Visitor
                    BOOST_MPL_AUX_LAMBDA_ARITY_PARAM(long Arity = mpl::aux::template_arity<R>::value)
                >
                struct make_
                {
                    typedef R type;
                    typedef void not_applied_;
                };

                template<typename R, typename Expr, typename State, typename Visitor>
                struct make_if_<R, Expr, State, Visitor, false>
                  : make_<R, Expr, State, Visitor>
                {};

                #if BOOST_WORKAROUND(__GNUC__, == 3)
                // work around GCC bug
                template<typename Tag, typename Args, long N, typename Expr, typename State, typename Visitor>
                struct make_if_<proto::expr<Tag, Args, N>, Expr, State, Visitor, false>
                {
                    typedef proto::expr<Tag, Args, N> type;
                    typedef void not_applied_;
                };
                #endif

                template<typename R, typename Expr, typename State, typename Visitor>
                struct make_if_<R, Expr, State, Visitor, true>
                  : boost::result_of<R(Expr, State, Visitor)>
                {};

                template<typename Type, bool IsAggregate = is_aggregate<Type>::value>
                struct construct_
                {
                    typedef Type result_type;

                    Type operator ()() const
                    {
                        return Type();
                    }

                    #define TMP(Z, N, DATA)                                                             \
                    template<BOOST_PP_ENUM_PARAMS_Z(Z, N, typename A)>                                  \
                    Type operator ()(BOOST_PP_ENUM_BINARY_PARAMS_Z(Z, N, A, &a)) const                  \
                    {                                                                                   \
                        return Type(BOOST_PP_ENUM_PARAMS_Z(Z, N, a));                                   \
                    }
                    BOOST_PP_REPEAT_FROM_TO(1, BOOST_PP_INC(BOOST_PROTO_MAX_ARITY), TMP, ~)
                    #undef TMP
                };

                template<typename Type>
                struct construct_<Type, true>
                {
                    typedef Type result_type;

                    Type operator ()() const
                    {
                        return Type();
                    }

                    #define TMP(Z, N, DATA)                                                             \
                    template<BOOST_PP_ENUM_PARAMS_Z(Z, N, typename A)>                                  \
                    Type operator ()(BOOST_PP_ENUM_BINARY_PARAMS_Z(Z, N, A, &a)) const                  \
                    {                                                                                   \
                        Type that = {BOOST_PP_ENUM_PARAMS_Z(Z, N, a)};                                  \
                        return that;                                                                    \
                    }
                    BOOST_PP_REPEAT_FROM_TO(1, BOOST_PP_INC(BOOST_PROTO_MAX_ARITY), TMP, ~)
                    #undef TMP
                };

                template<typename T, typename A, long N>
                struct construct_<proto::expr<T, A, N>, true>
                {
                    typedef proto::expr<T, A, N> result_type;

                    #define TMP(Z, N, DATA)                                                             \
                    template<BOOST_PP_ENUM_PARAMS_Z(Z, N, typename A)>                                  \
                    result_type operator ()(BOOST_PP_ENUM_BINARY_PARAMS_Z(Z, N, A, &a)) const           \
                    {                                                                                   \
                        return result_type::make(BOOST_PP_ENUM_PARAMS_Z(Z, N, a));          \
                    }
                    BOOST_PP_REPEAT_FROM_TO(1, BOOST_PP_INC(BOOST_PROTO_MAX_ARITY), TMP, ~)
                    #undef TMP
                };

                #define TMP(Z, N, DATA)                                                                 \
                template<typename Type BOOST_PP_ENUM_TRAILING_PARAMS_Z(Z, N, typename A)>               \
                Type construct(BOOST_PP_ENUM_BINARY_PARAMS_Z(Z, N, A, &a))                              \
                {                                                                                       \
                    return construct_<Type>()(BOOST_PP_ENUM_PARAMS_Z(Z, N, a));                         \
                }
                BOOST_PP_REPEAT(BOOST_PROTO_MAX_ARITY, TMP, ~)
                #undef TMP
            }

            template<typename Fun>
            struct make : proto::callable
            {
                template<typename Sig>
                struct result;

                template<typename This, typename Expr, typename State, typename Visitor>
                struct result<This(Expr, State, Visitor)>
                {
                    typedef typename detail::make_<Fun, Expr, State, Visitor>::type type;
                };

                template<typename Expr, typename State, typename Visitor>
                typename result<void(Expr, State, Visitor)>::type
                operator ()(Expr const &, State const &, Visitor &) const
                {
                    typedef typename result<void(Expr, State, Visitor)>::type result_type;
                    return result_type();
                }
            };

            #define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PROTO_MAX_ARITY, <boost/xpressive/proto/transform/make.hpp>))
            #include BOOST_PP_ITERATE()
        }

        /// INTERNAL ONLY
        ///
        template<typename Fun>
        struct is_callable<transform::make<Fun> >
          : mpl::true_
        {};

    }}

    #endif

#else

    #define N BOOST_PP_ITERATION()

        namespace detail
        {
            #if N > 0
            template<typename T BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
            struct nested_type_if<
                T
              , typelist<BOOST_PP_ENUM_PARAMS(N, A)>
              , typename typelist<
                    BOOST_PP_ENUM_BINARY_PARAMS(N, typename A, ::not_applied_ BOOST_PP_INTERCEPT)
                >::type
            >
            {
                typedef T type;
                typedef void not_applied_;
            };

            template<
                template<BOOST_PP_ENUM_PARAMS(N, typename BOOST_PP_INTERCEPT)> class R
                BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)
              , typename Expr, typename State, typename Visitor
            >
            struct make_<R<BOOST_PP_ENUM_PARAMS(N, A)>, Expr, State, Visitor
                BOOST_MPL_AUX_LAMBDA_ARITY_PARAM(N)
            >
              : nested_type_if<
                    #define TMP0(Z, M, DATA) make_if_<BOOST_PP_CAT(A, M), Expr, State, Visitor>
                    #define TMP1(Z, M, DATA) typename TMP0(Z, M, DATA) ::type
                    R<BOOST_PP_ENUM(N, TMP1, ~)>
                  , typelist<BOOST_PP_ENUM(N, TMP0, ~) >
                    #undef TMP0
                    #undef TMP1
                >
            {};
            #endif

            template<
                typename R
                BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)
              , typename Expr, typename State, typename Visitor
            >
            struct make_if_<R(BOOST_PP_ENUM_PARAMS(N, A)), Expr, State, Visitor, false>
            {
                typedef typename when<_, R(BOOST_PP_ENUM_PARAMS(N, A))>::template result<void(Expr, State, Visitor)>::type type;
            };

            template<
                typename R
                BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)
              , typename Expr, typename State, typename Visitor
            >
            struct make_if_<R(*)(BOOST_PP_ENUM_PARAMS(N, A)), Expr, State, Visitor, false>
            {
                typedef typename when<_, R(BOOST_PP_ENUM_PARAMS(N, A))>::template result<void(Expr, State, Visitor)>::type type;
            };

            template<typename T, typename A>
            struct construct_<proto::expr<T, A, N>, true>
            {
                typedef proto::expr<T, A, N> result_type;

                template<BOOST_PP_ENUM_PARAMS(BOOST_PP_MAX(N, 1), typename A)>
                result_type operator ()(BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PP_MAX(N, 1), A, &a)) const
                {
                    return result_type::make(BOOST_PP_ENUM_PARAMS(BOOST_PP_MAX(N, 1), a));
                }
            };
        }

        template<typename Return BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
        struct make<Return(BOOST_PP_ENUM_PARAMS(N, A))> : proto::callable
        {
            template<typename Sig>
            struct result;

            template<typename This, typename Expr, typename State, typename Visitor>
            struct result<This(Expr, State, Visitor)>
            {
                typedef typename detail::make_<Return, Expr, State, Visitor>::type type;
            };

            template<typename Expr, typename State, typename Visitor>
            typename result<void(Expr, State, Visitor)>::type
            operator ()(Expr const &expr, State const &state, Visitor &visitor) const
            {
                typedef typename result<void(Expr, State, Visitor)>::type result_type;
                return detail::construct<result_type>(
                    #define TMP(Z, M, DATA) detail::as_lvalue(when<_, BOOST_PP_CAT(A, M)>()(expr, state, visitor))
                    BOOST_PP_ENUM(N, TMP, DATA)
                    #undef TMP
                );
            }
        };

        #if BOOST_WORKAROUND(__GNUC__, == 3)
        // work around GCC bug
        template<typename Tag, typename Args, long Arity BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
        struct make<proto::expr<Tag, Args, Arity>(BOOST_PP_ENUM_PARAMS(N, A))>
          : proto::callable
        {
            template<typename Sig>
            struct result;

            template<typename This, typename Expr, typename State, typename Visitor>
            struct result<This(Expr, State, Visitor)>
            {
                typedef proto::expr<Tag, Args, Arity> type;
            };

            template<typename Expr, typename State, typename Visitor>
            proto::expr<Tag, Args, Arity> operator ()(Expr const &expr, State const &state, Visitor &visitor) const
            {
                return proto::expr<Tag, Args, Arity>::make(
                    #define TMP(Z, M, DATA) detail::as_lvalue(when<_, BOOST_PP_CAT(A, M)>()(expr, state, visitor))
                    BOOST_PP_ENUM(N, TMP, DATA)
                    #undef TMP
                );
            }
        };
        #endif

    #undef N

#endif
