///////////////////////////////////////////////////////////////////////////////
/// \file context.hpp
/// Definintion of context\<\>, a default evaluation context for
/// expr\<\>::eval() that uses Boost.Typeof to deduce return types
/// of the built-in operators.
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_CONTEXT_HPP_EAN_01_08_2007
#define BOOST_PROTO_CONTEXT_HPP_EAN_01_08_2007

#include <boost/xpressive/proto/detail/prefix.hpp> // must be first include
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/facilities/apply.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>
#include <boost/preprocessor/repetition/enum_shifted_binary_params.hpp>
#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/mpl/if.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/xpressive/proto/proto_fwd.hpp>
#include <boost/xpressive/proto/tags.hpp>
#include <boost/xpressive/proto/fusion.hpp>
#include <boost/fusion/functional/invocation/invoke.hpp>
#include <boost/fusion/sequence/view/transform_view.hpp>
#include <boost/fusion/algorithm/transformation/pop_front.hpp>
#include <boost/fusion/algorithm/transformation/push_front.hpp>
#include <boost/xpressive/proto/detail/suffix.hpp> // must be last include

/// INTERNAL ONLY
///
#define BOOST_PROTO_DECLTYPE_NESTED_TYPEDEF_TPL(Nested, Expr)\
    BOOST_TYPEOF_NESTED_TYPEDEF_TPL(BOOST_PP_CAT(nested_and_hidden_, Nested), Expr)\
    struct Nested\
      : mpl::if_c<\
            1==sizeof(detail::check_reference(Expr))\
          , typename BOOST_PP_CAT(nested_and_hidden_, Nested)::type &\
          , typename BOOST_PP_CAT(nested_and_hidden_, Nested)::type\
        >\
    {};\
    /**/

namespace boost { namespace proto
{
    namespace detail
    {
        template<typename T> T make();

        template<typename T>
        char check_reference(T &);

        template<typename T>
        char (&check_reference(T const &))[2];

        template<typename A0, typename A1>
        struct comma_result
        {
            BOOST_PROTO_DECLTYPE_NESTED_TYPEDEF_TPL(nested, (detail::make<A0>(), detail::make<A1>()))
            typedef typename nested::type type;
        };

        template<typename A0>
        struct comma_result<A0, void>
        {
            typedef void type;
        };

        template<typename A1>
        struct comma_result<void, A1>
        {
            typedef A1 type;
        };

        template<>
        struct comma_result<void, void>
        {
            typedef void type;
        };
    }

    /// INTERNAL ONLY
    ///
#define BOOST_PROTO_TYPEOF(Expr, Type)\
    BOOST_PROTO_DECLTYPE_NESTED_TYPEDEF_TPL(BOOST_PP_CAT(nested_, Type), (Expr))\
    typedef typename BOOST_PP_CAT(nested_, Type)::type Type;\
    /**/

    template<typename Expr, typename Context, typename Tag = typename Expr::tag_type>
    struct default_eval;

    /// INTERNAL ONLY
    ///
#define BOOST_PROTO_UNARY_OP_RESULT(Op, Tag)\
    template<typename Expr, typename Context>\
    struct default_eval<Expr, Context, Tag>\
    {\
        static Expr const &sexpr;\
        static Context &sctx;\
        BOOST_PROTO_TYPEOF(Op proto::arg_c<0>(sexpr).eval(sctx), result_type)\
        result_type operator()(Expr const &expr, Context &ctx) const\
        {\
            return Op proto::arg_c<0>(expr).eval(ctx);\
        }\
    };\
    /**/

    /// INTERNAL ONLY
    ///
#define BOOST_PROTO_BINARY_OP_RESULT(Op, Tag)\
    template<typename Expr, typename Context>\
    struct default_eval<Expr, Context, Tag>\
    {\
        static Expr const &sexpr;\
        static Context &sctx;\
        BOOST_PROTO_TYPEOF(proto::arg_c<0>(sexpr).eval(sctx) Op proto::arg_c<1>(sexpr).eval(sctx), result_type)\
        result_type operator()(Expr const &expr, Context &ctx) const\
        {\
            return proto::arg_c<0>(expr).eval(ctx) Op proto::arg_c<1>(expr).eval(ctx);\
        }\
    };\
    /**/

    BOOST_PROTO_UNARY_OP_RESULT(+, proto::tag::unary_plus)
    BOOST_PROTO_UNARY_OP_RESULT(-, proto::tag::unary_minus)
    BOOST_PROTO_UNARY_OP_RESULT(*, proto::tag::unary_star)
    BOOST_PROTO_UNARY_OP_RESULT(~, proto::tag::complement)
    BOOST_PROTO_UNARY_OP_RESULT(&, proto::tag::address_of)
    BOOST_PROTO_UNARY_OP_RESULT(!, proto::tag::logical_not)
    BOOST_PROTO_UNARY_OP_RESULT(++, proto::tag::pre_inc)
    BOOST_PROTO_UNARY_OP_RESULT(--, proto::tag::pre_dec)

    BOOST_PROTO_BINARY_OP_RESULT(<<, proto::tag::left_shift)
    BOOST_PROTO_BINARY_OP_RESULT(>>, proto::tag::right_shift)
    BOOST_PROTO_BINARY_OP_RESULT(*, proto::tag::multiply)
    BOOST_PROTO_BINARY_OP_RESULT(/, proto::tag::divide)
    BOOST_PROTO_BINARY_OP_RESULT(%, proto::tag::modulus)
    BOOST_PROTO_BINARY_OP_RESULT(+, proto::tag::add)
    BOOST_PROTO_BINARY_OP_RESULT(-, proto::tag::subtract)
    BOOST_PROTO_BINARY_OP_RESULT(<, proto::tag::less)
    BOOST_PROTO_BINARY_OP_RESULT(>, proto::tag::greater)
    BOOST_PROTO_BINARY_OP_RESULT(<=, proto::tag::less_equal)
    BOOST_PROTO_BINARY_OP_RESULT(>=, proto::tag::greater_equal)
    BOOST_PROTO_BINARY_OP_RESULT(==, proto::tag::equal)
    BOOST_PROTO_BINARY_OP_RESULT(!=, proto::tag::not_equal)
    BOOST_PROTO_BINARY_OP_RESULT(||, proto::tag::logical_or)
    BOOST_PROTO_BINARY_OP_RESULT(&&, proto::tag::logical_and)
    BOOST_PROTO_BINARY_OP_RESULT(&, proto::tag::bitwise_and)
    BOOST_PROTO_BINARY_OP_RESULT(|, proto::tag::bitwise_or)
    BOOST_PROTO_BINARY_OP_RESULT(^, proto::tag::bitwise_xor)
    BOOST_PROTO_BINARY_OP_RESULT(->*, proto::tag::mem_ptr)
    BOOST_PROTO_BINARY_OP_RESULT(=, proto::tag::assign)

    BOOST_PROTO_BINARY_OP_RESULT(<<=, proto::tag::left_shift_assign)
    BOOST_PROTO_BINARY_OP_RESULT(>>=, proto::tag::right_shift_assign)
    BOOST_PROTO_BINARY_OP_RESULT(*=, proto::tag::multiply_assign)
    BOOST_PROTO_BINARY_OP_RESULT(/=, proto::tag::divide_assign)
    BOOST_PROTO_BINARY_OP_RESULT(%=, proto::tag::modulus_assign)
    BOOST_PROTO_BINARY_OP_RESULT(+=, proto::tag::add_assign)
    BOOST_PROTO_BINARY_OP_RESULT(-=, proto::tag::subtract_assign)
    BOOST_PROTO_BINARY_OP_RESULT(&=, proto::tag::bitwise_and_assign)
    BOOST_PROTO_BINARY_OP_RESULT(|=, proto::tag::bitwise_or_assign)
    BOOST_PROTO_BINARY_OP_RESULT(^=, proto::tag::bitwise_xor_assign)

    template<typename Expr, typename Context>
    struct default_eval<Expr, Context, proto::tag::terminal>
    {
        typedef typename proto::result_of::arg<Expr>::const_reference result_type;
        result_type operator()(Expr const &expr, Context &) const
        {
            return proto::arg(expr);
        }
    };

    // Handle comma specially.
    template<typename Expr, typename Context>
    struct default_eval<Expr, Context, proto::tag::comma>
    {
        typedef typename proto::result_of::eval<typename proto::result_of::arg_c<Expr, 0>::type, Context>::type arg0_type;
        typedef typename proto::result_of::eval<typename proto::result_of::arg_c<Expr, 1>::type, Context>::type arg1_type;
        typedef typename detail::comma_result<arg0_type, arg1_type>::type result_type;

        result_type operator()(Expr const &expr, Context &ctx) const
        {
            return proto::arg_c<0>(expr).eval(ctx), proto::arg_c<1>(expr).eval(ctx);
        }
    };

    // Handle post-increment specially.
    template<typename Expr, typename Context>
    struct default_eval<Expr, Context, proto::tag::post_inc>
    {
        static Expr const &sexpr;
        static Context &sctx;
        BOOST_PROTO_TYPEOF(proto::arg_c<0>(sexpr).eval(sctx) ++, result_type)
        result_type operator()(Expr const &expr, Context &ctx) const
        {
            return proto::arg_c<0>(expr).eval(ctx) ++;
        }
    };

    // Handle post-decrement specially.
    template<typename Expr, typename Context>
    struct default_eval<Expr, Context, proto::tag::post_dec>
    {
        static Expr const &sexpr;
        static Context &sctx;
        BOOST_PROTO_TYPEOF(proto::arg_c<0>(sexpr).eval(sctx) --, result_type)
        result_type operator()(Expr const &expr, Context &ctx) const
        {
            return proto::arg_c<0>(expr).eval(ctx) --;
        }
    };

    // Handle subscript specially.
    template<typename Expr, typename Context>
    struct default_eval<Expr, Context, proto::tag::subscript>
    {
        static Expr const &sexpr;
        static Context &sctx;
        BOOST_PROTO_TYPEOF(proto::arg_c<0>(sexpr).eval(sctx)[proto::arg_c<1>(sexpr).eval(sctx)], result_type)
        result_type operator()(Expr const &expr, Context &ctx) const
        {
            return proto::arg_c<0>(expr).eval(ctx)[proto::arg_c<1>(expr).eval(ctx)];
        }
    };

    // Handle function specially.
    template<typename Expr, typename Context>
    struct default_eval<Expr, Context, proto::tag::function>
    {
        typedef
            typename proto::result_of::eval<
                typename proto::result_of::arg_c<Expr, 0>::type
              , Context
            >::type
        function_type;

        typedef
            fusion::transform_view<
                typename fusion::result_of::pop_front<children<Expr const> >::type const
              , eval_fun<Context>
            >
        arguments_type;

        typedef
            typename fusion::result_of::invoke<function_type, arguments_type>::type
        result_type;

        result_type operator()(Expr const &expr, Context &ctx) const
        {
            return fusion::invoke<function_type>(
                proto::arg_c<0>(expr).eval(ctx)
              , arguments_type(fusion::pop_front(proto::children_of(expr)), eval_fun<Context>(ctx))
            );
        }
    };

    /// default_context
    ///
    struct default_context
    {
        template<typename Expr>
        struct eval
          : default_eval<Expr, default_context>
        {};
    };

    /// callable_context
    ///
    template<typename Context>
    struct callable_context
    {
        template<typename Expr>
        struct eval
        {
            typedef typename fusion::result_of::invoke<
                Context &
              , typename fusion::result_of::push_front<children<Expr const>, typename Expr::tag_type>::type const
            >::type result_type;

            result_type operator()(Expr const &expr, Context &context)
            {
                return fusion::invoke<Context &>(
                    context
                  , fusion::push_front(proto::children_of(expr), typename Expr::tag_type())
                );
            }

            result_type operator()(Expr const &expr, Context const &context)
            {
                return fusion::invoke<Context const &>(
                    context
                  , fusion::push_front(proto::children_of(expr), typename Expr::tag_type())
                );
            }
        };
    };

}}

#endif

