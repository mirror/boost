///////////////////////////////////////////////////////////////////////////////
/// \file extends.hpp
/// A base class for defining end-user expression types
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_EXTENDS_HPP_EAN_11_1_2006
#define BOOST_PROTO_EXTENDS_HPP_EAN_11_1_2006

#include <boost/xpressive/proto/detail/prefix.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/iteration/local.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/xpressive/proto/proto_fwd.hpp>
#include <boost/xpressive/proto/traits.hpp>
#include <boost/xpressive/proto/expr.hpp>
#include <boost/xpressive/proto/args.hpp>
#include <boost/xpressive/proto/generate.hpp>
#include <boost/xpressive/proto/detail/suffix.hpp>

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
        typename generate<Domain, expr<tag::assign, args2<ref<Derived const>, typename result_of::as_arg<A>::type> > >::type const
        operator =(A &a) const
        {
            typedef expr<tag::assign, args2<ref<Derived const>, typename result_of::as_arg<A>::type> > that_type;
            that_type that = {{this->derived()}, proto::as_arg(a)};
            return generate<Domain, that_type>::make(that);
        }

        template<typename A>
        typename generate<Domain, expr<tag::assign, args2<ref<Derived const>, typename result_of::as_arg<A const>::type> > >::type const
        operator =(A const &a) const
        {
            typedef expr<tag::assign, args2<ref<Derived const>, typename result_of::as_arg<A const>::type> > that_type;
            that_type that = {{this->derived()}, proto::as_arg(a)};
            return generate<Domain, that_type>::make(that);
        }

        template<typename A>
        typename generate<Domain, expr<tag::subscript, args2<ref<Derived const>, typename result_of::as_arg<A>::type> > >::type const
        operator [](A &a) const
        {
            typedef expr<tag::subscript, args2<ref<Derived const>, typename result_of::as_arg<A>::type> > that_type;
            that_type that = {{this->derived()}, proto::as_arg(a)};
            return generate<Domain, that_type>::make(that);
        }

        template<typename A>
        typename generate<Domain, expr<tag::subscript, args2<ref<Derived const>, typename result_of::as_arg<A const>::type> > >::type const
        operator [](A const &a) const
        {
            typedef expr<tag::subscript, args2<ref<Derived const>, typename result_of::as_arg<A const>::type> > that_type;
            that_type that = {{this->derived()}, proto::as_arg(a)};
            return generate<Domain, that_type>::make(that);
        }

        template<typename Sig>
        struct result;

        template<typename This>
        struct result<This()>
        {
            typedef typename generate<Domain, expr<tag::function, args1<ref<Derived const> > > >::type type;
        };

        typename generate<Domain, expr<tag::function, args1<ref<Derived const> > > >::type const
        operator ()() const
        {
            expr<tag::function, args1<ref<Derived const> > > that = {{this->derived()}};
            return generate<Domain, expr<tag::function, args1<ref<Derived const> > > >::make(that);
        }

    #define BOOST_PP_LOCAL_MACRO(N) \
        template<typename This BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>\
        struct result<This(BOOST_PP_ENUM_PARAMS(N, A))>\
          : generate<\
                Domain\
              , typename result_of::BOOST_PP_CAT(funop, N)<\
                    Derived\
                    BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(\
                        N\
                      , typename remove_reference<A\
                      , >::type BOOST_PP_INTERCEPT\
                    )\
                >::type\
            >\
        {};\
        template<BOOST_PP_ENUM_PARAMS(N, typename A)>\
        typename generate<\
            Domain\
          , typename result_of::BOOST_PP_CAT(funop, N)<\
                Derived\
                BOOST_PP_ENUM_TRAILING_PARAMS(N, const A)\
            >::type\
        >::type const\
        operator ()(BOOST_PP_ENUM_BINARY_PARAMS(N, A, const &a)) const\
        {\
            typedef result_of::BOOST_PP_CAT(funop, N)<\
                Derived\
                BOOST_PP_ENUM_TRAILING_PARAMS(N, const A)\
            > funop;\
            return generate<Domain, typename funop::type>::make(\
                funop::call(this->derived() BOOST_PP_ENUM_TRAILING_PARAMS(N, a))\
            );\
        }\
        /**/

    #define BOOST_PP_LOCAL_LIMITS (1, BOOST_PP_DEC(BOOST_PROTO_MAX_ARITY))
    #include BOOST_PP_LOCAL_ITERATE()
    };

}}

#endif
