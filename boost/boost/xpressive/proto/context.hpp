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
#include <boost/preprocessor/iteration/local.hpp>
#include <boost/preprocessor/punctuation/comma.hpp>
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
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/xpressive/proto/proto_fwd.hpp>
#include <boost/xpressive/proto/tags.hpp>
#include <boost/xpressive/proto/detail/suffix.hpp>

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
    }

    template<typename Derived>
    struct context
    {
        typedef typename mpl::if_<
            is_same<Derived, void>
          , context
          , Derived
        >::type derived_type;

        derived_type &cast()
        {
            return *static_cast<derived_type *>(this);
        }

        template<typename Sig>
        struct result;

        template<typename This, typename A0>
        struct result<This(proto::tag::terminal, A0 &)>
        {
            typedef A0 &type;
        };

    #define BOOST_PROTO_UNARY_OP_RESULT(Op, Tag)\
        template<typename This, typename A0>\
        struct result<This(Tag, A0 &)>\
        {\
            typedef typename proto::result_of::eval<A0, derived_type>::type eval_type0;\
            BOOST_TYPEOF_NESTED_TYPEDEF_TPL(nested, (Op detail::make<eval_type0>()))\
            typedef typename mpl::if_c<\
                1==sizeof(detail::check_reference((Op detail::make<eval_type0>())))\
              , typename nested::type &\
              , typename nested::type\
            >::type type;\
            static type call(typename detail::as_param<eval_type0>::type a0)\
            {\
                return Op a0;\
            }\
        }

    #define BOOST_PROTO_BINARY_OP_RESULT(Op, Tag)\
        template<typename This, typename A0, typename A1>\
        struct result<This(Tag, A0 &, A1 &)>\
        {\
            typedef typename proto::result_of::eval<A0, derived_type>::type eval_type0;\
            typedef typename proto::result_of::eval<A1, derived_type>::type eval_type1;\
            BOOST_TYPEOF_NESTED_TYPEDEF_TPL(nested, (detail::make<eval_type0>() Op detail::make<eval_type1>()))\
            typedef typename mpl::if_c<\
                1==sizeof(detail::check_reference((detail::make<eval_type0>() Op detail::make<eval_type1>())))\
              , typename nested::type &\
              , typename nested::type\
            >::type type;\
            static type call(typename detail::as_param<eval_type0>::type a0, typename detail::as_param<eval_type1>::type a1)\
            {\
                return a0 Op a1;\
            }\
        }

        BOOST_PROTO_UNARY_OP_RESULT(+, proto::tag::unary_plus);
        BOOST_PROTO_UNARY_OP_RESULT(-, proto::tag::unary_minus);
        BOOST_PROTO_UNARY_OP_RESULT(*, proto::tag::unary_star);
        BOOST_PROTO_UNARY_OP_RESULT(~, proto::tag::complement);
        BOOST_PROTO_UNARY_OP_RESULT(&, proto::tag::address_of);
        BOOST_PROTO_UNARY_OP_RESULT(!, proto::tag::logical_not);
        BOOST_PROTO_UNARY_OP_RESULT(++, proto::tag::pre_inc);
        BOOST_PROTO_UNARY_OP_RESULT(--, proto::tag::pre_dec);

        BOOST_PROTO_BINARY_OP_RESULT(<<, proto::tag::left_shift);
        BOOST_PROTO_BINARY_OP_RESULT(>>, proto::tag::right_shift);
        BOOST_PROTO_BINARY_OP_RESULT(*, proto::tag::multiply);
        BOOST_PROTO_BINARY_OP_RESULT(/, proto::tag::divide);
        BOOST_PROTO_BINARY_OP_RESULT(%, proto::tag::modulus);
        BOOST_PROTO_BINARY_OP_RESULT(+, proto::tag::add);
        BOOST_PROTO_BINARY_OP_RESULT(-, proto::tag::subtract);
        BOOST_PROTO_BINARY_OP_RESULT(<, proto::tag::less);
        BOOST_PROTO_BINARY_OP_RESULT(>, proto::tag::greater);
        BOOST_PROTO_BINARY_OP_RESULT(<=, proto::tag::less_equal);
        BOOST_PROTO_BINARY_OP_RESULT(>=, proto::tag::greater_equal);
        BOOST_PROTO_BINARY_OP_RESULT(==, proto::tag::equal);
        BOOST_PROTO_BINARY_OP_RESULT(!=, proto::tag::not_equal);
        BOOST_PROTO_BINARY_OP_RESULT(||, proto::tag::logical_or);
        BOOST_PROTO_BINARY_OP_RESULT(&&, proto::tag::logical_and);
        BOOST_PROTO_BINARY_OP_RESULT(&, proto::tag::bitwise_and);
        BOOST_PROTO_BINARY_OP_RESULT(|, proto::tag::bitwise_or);
        BOOST_PROTO_BINARY_OP_RESULT(^, proto::tag::bitwise_xor);
        BOOST_PROTO_BINARY_OP_RESULT(BOOST_PP_COMMA(), proto::tag::comma);
        BOOST_PROTO_BINARY_OP_RESULT(->*, proto::tag::mem_ptr);
        BOOST_PROTO_BINARY_OP_RESULT(=, proto::tag::assign);

    #if !BOOST_WORKAROUND(__GNUC__, BOOST_TESTED_AT(4))
        BOOST_PROTO_BINARY_OP_RESULT(<<=, proto::tag::left_shift_assign);
        BOOST_PROTO_BINARY_OP_RESULT(>>=, proto::tag::right_shift_assign);
        BOOST_PROTO_BINARY_OP_RESULT(*=, proto::tag::multiply_assign);
        BOOST_PROTO_BINARY_OP_RESULT(/=, proto::tag::divide_assign);
        BOOST_PROTO_BINARY_OP_RESULT(%=, proto::tag::modulus_assign);
        BOOST_PROTO_BINARY_OP_RESULT(+=, proto::tag::add_assign);
        BOOST_PROTO_BINARY_OP_RESULT(-=, proto::tag::subtract_assign);
        BOOST_PROTO_BINARY_OP_RESULT(&=, proto::tag::bitwise_and_assign);
        BOOST_PROTO_BINARY_OP_RESULT(|=, proto::tag::bitwise_or_assign);
        BOOST_PROTO_BINARY_OP_RESULT(^=, proto::tag::bitwise_xor_assign);
    #endif

        // Handle post-increment specially.
        template<typename This, typename A0>
        struct result<This(proto::tag::post_inc, A0 &)>
        {
            typedef typename proto::result_of::eval<A0, derived_type>::type eval_type0;
            BOOST_TYPEOF_NESTED_TYPEDEF_TPL(nested, (detail::make<eval_type0>() ++))
            typedef typename mpl::if_c<
                1==sizeof(detail::check_reference((detail::make<eval_type0>() ++)))
              , typename nested::type &
              , typename nested::type
            >::type type;
            static type call(typename detail::as_param<eval_type0>::type a0)
            {
                return a0 ++;
            }
        };

        // Handle post-decrement specially.
        template<typename This, typename A0>
        struct result<This(proto::tag::post_dec, A0 &)>
        {
            typedef typename proto::result_of::eval<A0, derived_type>::type eval_type0;
            BOOST_TYPEOF_NESTED_TYPEDEF_TPL(nested, (detail::make<eval_type0>() ++))
            typedef typename mpl::if_c<
                1==sizeof(detail::check_reference((detail::make<eval_type0>() ++)))
              , typename nested::type &
              , typename nested::type
            >::type type;
            static type call(typename detail::as_param<eval_type0>::type a0)
            {
                return a0 --;
            }
        };

        // Handle subscript specially.
        template<typename This, typename A0, typename A1>
        struct result<This(proto::tag::subscript, A0 &, A1 &)>
        {
            typedef typename proto::result_of::eval<A0, derived_type>::type eval_type0;
            typedef typename proto::result_of::eval<A1, derived_type>::type eval_type1;
            BOOST_TYPEOF_NESTED_TYPEDEF_TPL(nested, (detail::make<eval_type0>() [ detail::make<eval_type1>() ] ))
            typedef typename mpl::if_c<
                1==sizeof(detail::check_reference((detail::make<eval_type0>() [ detail::make<eval_type1>() ] )))
              , typename nested::type &
              , typename nested::type
            >::type type;
            static type call(typename detail::as_param<eval_type0>::type a0, typename detail::as_param<eval_type1>::type a1)
            {
                return a0 [ a1 ];
            }
        };

    // MSVC can't seem to handle typeof and function calls in templates
    #if !BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400))
    #define BOOST_PROTO_ARG(z, n, data)\
        typedef\
            typename proto::result_of::eval<BOOST_PP_CAT(A, n), derived_type>::type\
        BOOST_PP_CAT(eval_type, n);\
        /**/

    #define BOOST_PP_LOCAL_MACRO(N)\
        template<typename This BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>\
        struct result<This(proto::tag::function BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(N, A, & BOOST_PP_INTERCEPT))>\
        {\
            BOOST_PP_REPEAT(N, BOOST_PROTO_ARG, ~)\
            BOOST_TYPEOF_NESTED_TYPEDEF_TPL(\
                nested\
              , (detail::make<eval_type0>() (\
                    BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS(N, detail::make<eval_type, >() BOOST_PP_INTERCEPT)\
                ))\
            )\
            typedef typename mpl::if_c<\
                1==sizeof(detail::check_reference((detail::make<eval_type0>() (\
                    BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS(N, detail::make<eval_type, >() BOOST_PP_INTERCEPT)\
                ))))\
              , typename nested::type &\
              , typename nested::type\
            >::type type;\
            static type call(\
                BOOST_PP_ENUM_BINARY_PARAMS(N, typename detail::as_param<eval_type, >::type a)\
            )\
            {\
                return a0 ( BOOST_PP_ENUM_SHIFTED_PARAMS(N, a) );\
            }\
        };\
        /**/

    #define BOOST_PP_LOCAL_LIMITS (1, BOOST_PROTO_MAX_ARITY)
    #include BOOST_PP_LOCAL_ITERATE()
    #undef BOOST_PROTO_ARG
    #endif

        template<typename A0>
        A0 &
        operator()(proto::tag::terminal, A0 &a0)
        {
            return a0;
        }

    #define BOOST_PP_LOCAL_MACRO(N)\
        template<typename Tag BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>\
        typename result<derived_type(Tag BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(N, A, & BOOST_PP_INTERCEPT))>::type\
        operator()(Tag BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(N, A, & a))\
        {\
            return result<derived_type(Tag, BOOST_PP_ENUM_BINARY_PARAMS(N, A, & BOOST_PP_INTERCEPT))>::call(\
                BOOST_PP_ENUM_BINARY_PARAMS(N, a, .eval(this->cast()) BOOST_PP_INTERCEPT)\
            );\
        }\
        /**/

    #define BOOST_PP_LOCAL_LIMITS (1, BOOST_PROTO_MAX_ARITY)
    #include BOOST_PP_LOCAL_ITERATE()

    };

}}

#endif
