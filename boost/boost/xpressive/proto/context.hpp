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

#include <boost/xpressive/proto/detail/prefix.hpp>
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
#include <boost/xpressive/proto/detail/suffix.hpp>

#include <boost/xpressive/proto/fusion.hpp>
#include <boost/fusion/functional/adapter/fused.hpp>
#include <boost/fusion/sequence/view/transform_view.hpp>
#include <boost/fusion/algorithm/transformation/pop_front.hpp>
#include <boost/fusion/algorithm/transformation/push_front.hpp>

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

        template<typename T>
        struct as_param
          : add_reference<typename add_const<T>::type>
        {};

        template<typename T, typename U = T>
        struct result_of_fixup
          : mpl::if_<is_function<T>, T *, U>
        {};

        template<typename T, typename U>
        struct result_of_fixup<T &, U>
          : result_of_fixup<T, T>
        {};

        template<typename T, typename U>
        struct result_of_fixup<T *, U>
          : result_of_fixup<T, U>
        {};

        template<typename T, typename U>
        struct result_of_fixup<T const, U>
          : result_of_fixup<T, U>
        {};

        //// Tests for result_of_fixup
        //struct bar {};
        //BOOST_MPL_ASSERT((is_same<bar,        result_of_fixup<bar>::type>));
        //BOOST_MPL_ASSERT((is_same<bar const,  result_of_fixup<bar const>::type>));
        //BOOST_MPL_ASSERT((is_same<bar,        result_of_fixup<bar &>::type>));
        //BOOST_MPL_ASSERT((is_same<bar const,  result_of_fixup<bar const &>::type>));
        //BOOST_MPL_ASSERT((is_same<void(*)(),  result_of_fixup<void(*)()>::type>));
        //BOOST_MPL_ASSERT((is_same<void(*)(),  result_of_fixup<void(* const)()>::type>));
        //BOOST_MPL_ASSERT((is_same<void(*)(),  result_of_fixup<void(* const &)()>::type>));
        //BOOST_MPL_ASSERT((is_same<void(*)(),  result_of_fixup<void(&)()>::type>));

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

        template<typename Context>
        struct eval_transform
        {
            eval_transform(Context &ctx)
              : ctx_(ctx)
            {}

            template<typename Arg>
            struct result
            {
                typedef typename Context::template eval<typename remove_cv_ref<Arg>::type>::result_type type;
            };

            template<typename Arg>
            typename result<Arg>::type operator()(Arg &arg) const
            {
                return arg.eval(ctx_);
            }

            Context &ctx_;
        };
    }

    /// INTERNAL ONLY
    ///
#define BOOST_PROTO_TYPEOF_2(Expr, Type)\
    BOOST_PROTO_DECLTYPE_NESTED_TYPEDEF_TPL(BOOST_PP_CAT(nested_, Type), (Expr))\
    typedef typename BOOST_PP_CAT(nested_, Type)::type Type;\
    /**/

    template<typename Expr, typename Context, typename Tag = typename Expr::tag_type>
    struct default_eval;

    /// INTERNAL ONLY
    ///
#define BOOST_PROTO_UNARY_OP_RESULT_2(Op, Tag)\
    template<typename Expr, typename Context>\
    struct default_eval<Expr, Context, Tag>\
    {\
        static Expr const &sexpr;\
        static Context &sctx;\
        BOOST_PROTO_TYPEOF_2(Op proto::arg_c<0>(sexpr).eval(sctx), result_type)\
        result_type operator()(Expr const &expr, Context &ctx) const\
        {\
            return Op proto::arg_c<0>(expr).eval(ctx);\
        }\
    };\
    /**/

    /// INTERNAL ONLY
    ///
#define BOOST_PROTO_BINARY_OP_RESULT_2(Op, Tag)\
    template<typename Expr, typename Context>\
    struct default_eval<Expr, Context, Tag>\
    {\
        static Expr const &sexpr;\
        static Context &sctx;\
        BOOST_PROTO_TYPEOF_2(proto::arg_c<0>(sexpr).eval(sctx) Op proto::arg_c<1>(sexpr).eval(sctx), result_type)\
        result_type operator()(Expr const &expr, Context &ctx) const\
        {\
            return proto::arg_c<0>(expr).eval(ctx) Op proto::arg_c<1>(expr).eval(ctx);\
        }\
    };\
    /**/

    BOOST_PROTO_UNARY_OP_RESULT_2(+, proto::tag::unary_plus)
    BOOST_PROTO_UNARY_OP_RESULT_2(-, proto::tag::unary_minus)
    BOOST_PROTO_UNARY_OP_RESULT_2(*, proto::tag::unary_star)
    BOOST_PROTO_UNARY_OP_RESULT_2(~, proto::tag::complement)
    BOOST_PROTO_UNARY_OP_RESULT_2(&, proto::tag::address_of)
    BOOST_PROTO_UNARY_OP_RESULT_2(!, proto::tag::logical_not)
    BOOST_PROTO_UNARY_OP_RESULT_2(++, proto::tag::pre_inc)
    BOOST_PROTO_UNARY_OP_RESULT_2(--, proto::tag::pre_dec)

    BOOST_PROTO_BINARY_OP_RESULT_2(<<, proto::tag::left_shift)
    BOOST_PROTO_BINARY_OP_RESULT_2(>>, proto::tag::right_shift)
    BOOST_PROTO_BINARY_OP_RESULT_2(*, proto::tag::multiply)
    BOOST_PROTO_BINARY_OP_RESULT_2(/, proto::tag::divide)
    BOOST_PROTO_BINARY_OP_RESULT_2(%, proto::tag::modulus)
    BOOST_PROTO_BINARY_OP_RESULT_2(+, proto::tag::add)
    BOOST_PROTO_BINARY_OP_RESULT_2(-, proto::tag::subtract)
    BOOST_PROTO_BINARY_OP_RESULT_2(<, proto::tag::less)
    BOOST_PROTO_BINARY_OP_RESULT_2(>, proto::tag::greater)
    BOOST_PROTO_BINARY_OP_RESULT_2(<=, proto::tag::less_equal)
    BOOST_PROTO_BINARY_OP_RESULT_2(>=, proto::tag::greater_equal)
    BOOST_PROTO_BINARY_OP_RESULT_2(==, proto::tag::equal)
    BOOST_PROTO_BINARY_OP_RESULT_2(!=, proto::tag::not_equal)
    BOOST_PROTO_BINARY_OP_RESULT_2(||, proto::tag::logical_or)
    BOOST_PROTO_BINARY_OP_RESULT_2(&&, proto::tag::logical_and)
    BOOST_PROTO_BINARY_OP_RESULT_2(&, proto::tag::bitwise_and)
    BOOST_PROTO_BINARY_OP_RESULT_2(|, proto::tag::bitwise_or)
    BOOST_PROTO_BINARY_OP_RESULT_2(^, proto::tag::bitwise_xor)
    BOOST_PROTO_BINARY_OP_RESULT_2(->*, proto::tag::mem_ptr)
    BOOST_PROTO_BINARY_OP_RESULT_2(=, proto::tag::assign)

    BOOST_PROTO_BINARY_OP_RESULT_2(<<=, proto::tag::left_shift_assign)
    BOOST_PROTO_BINARY_OP_RESULT_2(>>=, proto::tag::right_shift_assign)
    BOOST_PROTO_BINARY_OP_RESULT_2(*=, proto::tag::multiply_assign)
    BOOST_PROTO_BINARY_OP_RESULT_2(/=, proto::tag::divide_assign)
    BOOST_PROTO_BINARY_OP_RESULT_2(%=, proto::tag::modulus_assign)
    BOOST_PROTO_BINARY_OP_RESULT_2(+=, proto::tag::add_assign)
    BOOST_PROTO_BINARY_OP_RESULT_2(-=, proto::tag::subtract_assign)
    BOOST_PROTO_BINARY_OP_RESULT_2(&=, proto::tag::bitwise_and_assign)
    BOOST_PROTO_BINARY_OP_RESULT_2(|=, proto::tag::bitwise_or_assign)
    BOOST_PROTO_BINARY_OP_RESULT_2(^=, proto::tag::bitwise_xor_assign)

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
        typedef typename result_of::eval<typename result_of::arg_c<Expr, 0>::type, Context>::type arg0_type;
        typedef typename result_of::eval<typename result_of::arg_c<Expr, 1>::type, Context>::type arg1_type;
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
        BOOST_PROTO_TYPEOF_2(proto::arg_c<0>(sexpr).eval(sctx) ++, result_type)
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
        BOOST_PROTO_TYPEOF_2(proto::arg_c<0>(sexpr).eval(sctx) --, result_type)
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
        BOOST_PROTO_TYPEOF_2(proto::arg_c<0>(sexpr).eval(sctx)[proto::arg_c<1>(sexpr).eval(sctx)], result_type)
        result_type operator()(Expr const &expr, Context &ctx) const
        {
            return proto::arg_c<0>(expr).eval(ctx)[proto::arg_c<1>(expr).eval(ctx)];
        }
    };

    // Handle function specially.
    template<typename Expr, typename Context>
    struct default_eval<Expr, Context, proto::tag::function>
    {
        static Expr const &sexpr;
        static Context &sctx;
        BOOST_PROTO_TYPEOF_2(proto::arg_c<0>(sexpr).eval(sctx), function_type)
        typedef
            typename fusion::fused<function_type>
                ::template result<
                    fusion::transform_view<
                        typename fusion::result_of::pop_front<ref<Expr const> >::type const
                      , detail::eval_transform<Context>
                    >
                >
            ::type
        result_type;
        result_type operator()(Expr const &expr, Context &ctx) const
        {
            ref<Expr const> ref_expr = {expr};
            return fusion::fused<function_type>(proto::arg_c<0>(expr).eval(ctx))
                (
                    fusion::transform_view<
                        typename fusion::result_of::pop_front<ref<Expr const> >::type const
                      , detail::eval_transform<Context>
                    >(
                        fusion::pop_front(ref_expr)
                      , detail::eval_transform<Context>(ctx)
                    )
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

    /// fanout_context
    ///
    template<typename Derived>
    struct fanout_context
    {
        template<typename Expr>
        struct eval
        {
            typedef typename fusion::fused<Derived &>::template result<
                typename fusion::result_of::push_front<proto::ref<Expr const>, typename Expr::tag_type>::type const
            >::type result_type;

            result_type operator()(Expr const &expr, Derived &ctx)
            {
                proto::ref<Expr const> ref = {expr};
                return fusion::fused<Derived &>(ctx)(fusion::push_front(ref, typename Expr::tag_type()));
            }

            result_type operator()(Expr const &expr, Derived const &ctx)
            {
                proto::ref<Expr const> ref = {expr};
                return fusion::fused<Derived const &>(ctx)(fusion::push_front(ref, typename Expr::tag_type()));
            }
        };
    };

}}

#endif

