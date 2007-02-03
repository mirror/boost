#ifndef BOOST_PP_IS_ITERATING
    ///////////////////////////////////////////////////////////////////////////////
    /// \file deep_copy.hpp
    /// Replace all nodes stored by reference by nodes stored by value.
    //
    //  Copyright 2004 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #ifndef BOOST_PROTO_DEEP_COPY_HPP_EAN_11_21_2006
    #define BOOST_PROTO_DEEP_COPY_HPP_EAN_11_21_2006

    #include <boost/xpressive/proto/detail/prefix.hpp>
    #include <boost/preprocessor/cat.hpp>
    #include <boost/preprocessor/enum.hpp>
    #include <boost/preprocessor/iterate.hpp>
    #include <boost/call_traits.hpp>
    #include <boost/xpressive/proto/proto_fwd.hpp>
    #include <boost/xpressive/proto/expr.hpp>
    #include <boost/xpressive/proto/detail/suffix.hpp>

    namespace boost { namespace proto
    {
        namespace detail
        {
            template<typename Expr, typename Tag = typename Expr::tag_type, long Arity = Expr::arity::value>
            struct deep_copy_impl;

            template<typename Expr>
            struct deep_copy_impl<Expr, tag::terminal, 1>
            {
                typedef typename terminal<
                    typename result_of::arg<Expr>::type
                >::type type;

                static type call(Expr const &expr)
                {
                    type that = {proto::arg(expr)};
                    return that;
                }
            };
        }

        namespace result_of
        {
            template<typename Expr>
            struct deep_copy
              : detail::deep_copy_impl<Expr>
            {};
        }

        namespace op
        {
            struct deep_copy
            {
                template<typename Sig>
                struct result;

                template<typename This, typename Expr>
                struct result<This(Expr)>
                  : result_of::deep_copy<typename detail::remove_cv_ref<Expr>::type>
                {};

                template<typename Expr>
                typename result_of::deep_copy<Expr>::type
                operator()(Expr const &expr) const
                {
                    return result_of::deep_copy<Expr>::call(expr);
                }
            };
        }

        op::deep_copy const deep_copy = {};

        namespace detail
        {
        #define BOOST_PROTO_DEFINE_DEEP_COPY_TYPE(z, n, data)\
            typename deep_copy_impl<typename Expr:: BOOST_PP_CAT(BOOST_PP_CAT(arg, n), _type) ::type>::type

        #define BOOST_PROTO_DEFINE_DEEP_COPY_FUN(z, n, data)\
            proto::deep_copy(expr.cast(). BOOST_PP_CAT(arg, n) .cast())

        #define BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_PROTO_MAX_ARITY, <boost/xpressive/proto/deep_copy.hpp>))

        #include BOOST_PP_ITERATE()

        #undef BOOST_PP_ITERATION_PARAMS_1
        #undef BOOST_PROTO_DEFINE_DEEP_COPY_FUN
        #undef BOOST_PROTO_DEFINE_DEEP_COPY_TYPE
        }

    }}

    #endif // BOOST_PROTO_COMPILER_DEEP_COPY_HPP_EAN_11_21_2006

#else

    #define N BOOST_PP_ITERATION()

            template<typename Expr, typename Tag>
            struct deep_copy_impl<Expr, Tag, N>
            {
                typedef expr<Tag, BOOST_PP_CAT(args, N)<
                    BOOST_PP_ENUM(N, BOOST_PROTO_DEFINE_DEEP_COPY_TYPE, ~)
                > > type;

                static type call(Expr const &expr)
                {
                    type that = {
                        BOOST_PP_ENUM(N, BOOST_PROTO_DEFINE_DEEP_COPY_FUN, ~)
                    };
                    return that;
                }
            };

    #undef N

#endif
