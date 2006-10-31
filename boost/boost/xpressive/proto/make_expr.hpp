///////////////////////////////////////////////////////////////////////////////
/// \file make_expr.hpp
/// Given a Fusion sequence of arguments and the type of a proto Expression,
/// unpacks the sequence into the Expression.
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PP_IS_ITERATING

    #ifndef BOOST_PROTO_MAKE_EXPR_HPP_EAN_04_01_2005
    #define BOOST_PROTO_MAKE_EXPR_HPP_EAN_04_01_2005

    #include <boost/preprocessor/inc.hpp>
    #include <boost/preprocessor/cat.hpp>
    #include <boost/preprocessor/punctuation/paren.hpp>
    #include <boost/preprocessor/iterate.hpp>
    #include <boost/preprocessor/facilities/intercept.hpp>
    #include <boost/preprocessor/repetition/enum.hpp>
    #include <boost/preprocessor/repetition/enum_params.hpp>
    #include <boost/preprocessor/repetition/enum_trailing_params.hpp>
    #include <boost/preprocessor/repetition/enum_binary_params.hpp>
    #include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>

    #include <boost/detail/workaround.hpp>
    #include <boost/ref.hpp>
    #include <boost/mpl/vector.hpp>
    #include <boost/xpressive/proto/proto_fwd.hpp>
    #include <boost/xpressive/proto/traits.hpp>
    #include <boost/fusion/sequence/intrinsic/size.hpp>
    #include <boost/fusion/sequence/utility/unpack_args.hpp>

    namespace boost { namespace proto
    {

        namespace detail
        {
            template<typename Tag, long Arity>
            struct msvc_make_expr_impl_result;

            template<typename Tag, long Arity>
            struct make_expr_impl;

        #define BOOST_PROTO_AS_EXPR(z, n, data) proto::as_expr(BOOST_PP_CAT(a, n))
        #define BOOST_PP_ITERATION_PARAMS_1 (4, (1, BOOST_PROTO_MAX_ARITY, <boost/xpressive/proto/make_expr.hpp>, 1))
        #include BOOST_PP_ITERATE()
        #undef BOOST_PP_ITERATION_PARAMS_1
        #undef BOOST_PROTO_AS_EXPR
        }

        namespace meta
        {
            template<typename Tag BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(BOOST_PROTO_MAX_ARITY, typename A, = void BOOST_PP_INTERCEPT), typename Dummy = void>
            struct make_expr;
        }

    #define BOOST_PP_ITERATION_PARAMS_1 (4, (1, BOOST_PROTO_MAX_ARITY, <boost/xpressive/proto/make_expr.hpp>, 2))
    #include BOOST_PP_ITERATE()
    #undef BOOST_PP_ITERATION_PARAMS_1

        namespace meta
        {
            template<typename Tag, typename Sequence>
            struct unpack_expr
              : fusion::result_of::unpack_args<
                    detail::make_expr_impl<Tag, fusion::result_of::size<Sequence>::type::value>
                  , Sequence
                >
            {};
        }

        template<typename Tag, typename Sequence>
        typename meta::unpack_expr<Tag, Sequence const>::type
        unpack_expr(Sequence const &sequence)
        {
            detail::make_expr_impl<Tag, fusion::result_of::size<Sequence>::type::value> make_expr;
            return fusion::unpack_args(make_expr, sequence);
        }

    }}

    #endif // BOOST_PROTO_MAKE_EXPR_HPP_EAN_04_01_2005

#elif 1 == BOOST_PP_ITERATION_FLAGS()

    #define N BOOST_PP_ITERATION()

            template<typename Tag>
            struct msvc_make_expr_impl_result<Tag, N>
            {
                template<BOOST_PP_ENUM_PARAMS(N, typename A)>
                struct result_
                {
                    typedef basic_expr<Tag, BOOST_PP_CAT(mpl::vector, N)<
                        BOOST_PP_ENUM_BINARY_PARAMS(N, typename meta::as_expr<A, >::type BOOST_PP_INTERCEPT)
                    > > type;
                };

                template<typename Sig>
                struct result;

                template<typename This BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
                struct result<This(BOOST_PP_ENUM_PARAMS(N, A))>
                  : result_<BOOST_PP_ENUM_BINARY_PARAMS(N, typename meta::value_type<A, >::type BOOST_PP_INTERCEPT)>
                {};
            };

            template<typename Tag>
            struct make_expr_impl<Tag, N>
              : msvc_make_expr_impl_result<Tag, N>
            {
                template<BOOST_PP_ENUM_PARAMS(N, typename A)>
                typename msvc_make_expr_impl_result<Tag, N>
                    ::BOOST_NESTED_TEMPLATE result_<BOOST_PP_ENUM_PARAMS(N, A)>::type
                operator ()(BOOST_PP_ENUM_BINARY_PARAMS(N, A, const &a)) const
                {
                    typename msvc_make_expr_impl_result<Tag, N>
                        ::BOOST_NESTED_TEMPLATE result_<BOOST_PP_ENUM_PARAMS(N, A)>::type that =
                            {BOOST_PP_ENUM(N, BOOST_PROTO_AS_EXPR, _)};
                    return that;
                }
            };

    #undef N

#elif 2 == BOOST_PP_ITERATION_FLAGS()

    #define N BOOST_PP_ITERATION()

    namespace meta
    {
        template<typename Tag BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
        struct make_expr<Tag BOOST_PP_ENUM_TRAILING_PARAMS(N, A)>
          : detail::make_expr_impl<Tag, N>::BOOST_NESTED_TEMPLATE result_<BOOST_PP_ENUM_PARAMS(N, A)>
        {};
    }

    template<typename Tag BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    typename detail::make_expr_impl<Tag, N>::BOOST_NESTED_TEMPLATE result_<BOOST_PP_ENUM_PARAMS(N, A)>::type
    make_expr(BOOST_PP_ENUM_BINARY_PARAMS(N, A, const &a))
    {
        return detail::make_expr_impl<Tag, N>()(BOOST_PP_ENUM_PARAMS(N, a));
    }

    #undef N

#endif
