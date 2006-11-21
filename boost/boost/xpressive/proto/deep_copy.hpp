///////////////////////////////////////////////////////////////////////////////
/// \file deep_copy.hpp
/// Replace all nodes stored by reference by nodes stored by value.
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PP_IS_ITERATING

    #ifndef BOOST_PROTO_DEEP_COPY_HPP_EAN_11_21_2006
    #define BOOST_PROTO_DEEP_COPY_HPP_EAN_11_21_2006

    #include <boost/preprocessor/cat.hpp>
    #include <boost/preprocessor/enum.hpp>
    #include <boost/preprocessor/iterate.hpp>
    #include <boost/xpressive/proto/proto_fwd.hpp>
    #include <boost/xpressive/proto/expr.hpp>

    namespace boost { namespace proto
    {
        namespace detail
        {
            template<typename Expr, typename Tag = typename Expr::tag_type, long Arity = Expr::arity::value>
            struct deep_copy_impl;

            template<typename Expr>
            struct deep_copy_impl<Expr, terminal_tag, 1>
            {
                static typename Expr::expr_type const &
                call(Expr const &expr)
                {
                    return expr.cast();
                }
            };
        }

        namespace meta
        {
            template<typename Expr>
            struct deep_copy
            {
                typedef typename Expr::id type;
            };
        }

        template<typename Expr>
        typename Expr::id deep_copy(Expr const &expr)
        {
            return detail::deep_copy_impl<Expr>::call(expr);
        }

        namespace detail
        {
        #define BOOST_PROTO_DEFINE_DEEP_COPY(z, n, data)\
            proto::deep_copy(BOOST_PP_CAT(expr.cast().arg, n).cast())

        #define BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_PROTO_MAX_ARITY, <boost/xpressive/proto/deep_copy.hpp>))

        #include BOOST_PP_ITERATE()

        #undef BOOST_PP_ITERATION_PARAMS_1
        #undef BOOST_PROTO_DEFINE_DEEP_COPY
        }

    }}

    #endif // BOOST_PROTO_COMPILER_DEEP_COPY_HPP_EAN_11_21_2006

#else

    #define N BOOST_PP_ITERATION()

            template<typename Expr, typename Tag>
            struct deep_copy_impl<Expr, Tag, N>
            {
                static typename Expr::id
                call(Expr const &expr)
                {
                    typename Expr::id that = {
                        BOOST_PP_ENUM(N, BOOST_PROTO_DEFINE_DEEP_COPY, ~)
                    };
                    return that;
                }
            };

    #undef N

#endif
