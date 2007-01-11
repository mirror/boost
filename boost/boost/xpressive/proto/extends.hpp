///////////////////////////////////////////////////////////////////////////////
/// \file extends.hpp
/// A base class for defining end-user expression types
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_EXTENDS_HPP_EAN_11_1_2006
#define BOOST_PROTO_EXTENDS_HPP_EAN_11_1_2006

#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/iteration/local.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>

#if !defined(__WAVE__) || !defined(BOOST_PROTO_DOXYGEN_INVOKED)
#include <boost/xpressive/proto/proto_fwd.hpp>
#include <boost/xpressive/proto/traits.hpp>
#include <boost/xpressive/proto/expr.hpp>
#include <boost/xpressive/proto/args.hpp>
#else
/// INTERNAL ONLY
/// Needed to work around doxygen bug
struct a_dummy_global;
#endif

namespace boost { namespace proto
{
    template<typename Expr, typename Derived, typename Domain>
    struct extends
      : Expr
    {
        typedef Domain domain;
        typedef typename Expr::type type;
        typedef void is_boost_proto_extends_private_extends_;
        typedef Derived boost_proto_expr_type_;

        extends()
          : Expr()
        {}

        extends(Expr const &expr)
          : Expr(expr)
        {}

        Derived const &derived() const
        {
            return *static_cast<Derived const *>(this);
        }

        void assign(Expr const &that)
        {
            *static_cast<Expr *>(this) = that;
        }

        template<typename A>
        typename meta::generate<Domain, expr<tag::assign, args2<ref<Derived>, typename meta::as_expr_ref<A>::type> >, tag::assign>::type const
        operator =(A const &a) const
        {
            expr<tag::assign, args2<ref<Derived>, typename meta::as_expr_ref<A>::type> > that = {{this->derived()}, proto::as_expr_ref(a)};
            return meta::generate<Domain, expr<tag::assign, args2<ref<Derived>, typename meta::as_expr_ref<A>::type> >, tag::assign>::make(that);
        }

        template<typename A>
        typename meta::generate<Domain, expr<tag::subscript, args2<ref<Derived>, typename meta::as_expr_ref<A>::type> >, tag::subscript>::type const
        operator [](A const &a) const
        {
            expr<tag::subscript, args2<ref<Derived>, typename meta::as_expr_ref<A>::type> > that = {{this->derived()}, proto::as_expr_ref(a)};
            return meta::generate<Domain, expr<tag::subscript, args2<ref<Derived>, typename meta::as_expr_ref<A>::type> >, tag::subscript>::make(that);
        }

        template<typename Sig>
        struct result;

        template<typename This>
        struct result<This()>
        {
            typedef typename meta::generate<Domain, expr<tag::function, args1<ref<Derived> > >, tag::function>::type type;
        };

        typename meta::generate<Domain, expr<tag::function, args1<ref<Derived> > >, tag::function>::type const
        operator ()() const
        {
            expr<tag::function, args1<ref<Derived> > > that = {{this->derived()}};
            return meta::generate<Domain, expr<tag::function, args1<ref<Derived> > >, tag::function>::make(that);
        }

    #define BOOST_PROTO_AS_OP(z, n, data)\
        proto::as_expr_ref(BOOST_PP_CAT(a,n))\
        /**/

    #define BOOST_PP_LOCAL_MACRO(N) \
        template<typename This BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>\
        struct result<This(BOOST_PP_ENUM_PARAMS(N, A))>\
        {\
            typedef typename meta::generate<Domain, expr<tag::function, BOOST_PP_CAT(args, BOOST_PP_INC(N))<ref<Derived> BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(N, typename meta::as_expr_ref<A, >::type BOOST_PP_INTERCEPT)> >, tag::function>::type type;\
        };\
        template<BOOST_PP_ENUM_PARAMS(N, typename A)>\
        typename meta::generate<Domain, expr<tag::function, BOOST_PP_CAT(args, BOOST_PP_INC(N))<ref<Derived> BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(N, typename meta::as_expr_ref<A, >::type BOOST_PP_INTERCEPT)> > >::type const\
        operator ()(BOOST_PP_ENUM_BINARY_PARAMS(N, A, const &a)) const\
        {\
            expr<tag::function, BOOST_PP_CAT(args, BOOST_PP_INC(N))<ref<Derived> BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(N, typename meta::as_expr_ref<A, >::type BOOST_PP_INTERCEPT)> > that = {{this->derived()} BOOST_PP_ENUM_TRAILING(N, BOOST_PROTO_AS_OP, _)};\
            return meta::generate<Domain, expr<tag::function, BOOST_PP_CAT(args, BOOST_PP_INC(N))<ref<Derived> BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(N, typename meta::as_expr_ref<A, >::type BOOST_PP_INTERCEPT)> >, tag::function>::make(that);\
        }\
        /**/

    #define BOOST_PP_LOCAL_LIMITS (1, BOOST_PP_DEC(BOOST_PROTO_MAX_ARITY))
    #include BOOST_PP_LOCAL_ITERATE()
    #undef BOOST_PROTO_AS_OP
    };

}}

#endif
