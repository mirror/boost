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
#include <boost/xpressive/proto/traits.hpp>
#include <boost/xpressive/proto/generate.hpp>
#include <boost/xpressive/proto/detail/suffix.hpp>

namespace boost { namespace proto
{
    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_DEFINE_FUN_OP(Z, N, DATA)\
        template<typename This BOOST_PP_ENUM_TRAILING_PARAMS_Z(Z, N, typename A)>\
        struct result<This(BOOST_PP_ENUM_PARAMS_Z(Z, N, A))>\
          : boost::proto::generate<\
                Domain\
              , typename boost::proto::result_of::BOOST_PP_CAT(funop, N)<\
                    Derived\
                    BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_Z(\
                        Z\
                      , N\
                      , typename remove_reference<A\
                      , >::type BOOST_PP_INTERCEPT\
                    )\
                >::type\
            >\
        {};\
        \
        template<BOOST_PP_ENUM_PARAMS_Z(Z, N, typename A)>\
        typename boost::proto::generate<\
            Domain\
          , typename boost::proto::result_of::BOOST_PP_CAT(funop, N)<\
                Derived\
                BOOST_PP_ENUM_TRAILING_PARAMS_Z(Z, N, const A)\
            >::type\
        >::type const\
        operator ()(BOOST_PP_ENUM_BINARY_PARAMS_Z(Z, N, A, const &a)) const\
        {\
            typedef boost::proto::result_of::BOOST_PP_CAT(funop, N)<\
                Derived\
                BOOST_PP_ENUM_TRAILING_PARAMS_Z(Z, N, const A)\
            > funop;\
            return boost::proto::generate<Domain, typename funop::type>::make(\
                funop::call(this->derived() BOOST_PP_ENUM_TRAILING_PARAMS_Z(Z, N, a))\
            );\
        }\
        /**/

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_EXTENDS_ARG(z, n, Expr)\
        typedef\
            typename Expr::BOOST_PP_CAT(BOOST_PP_CAT(arg, n), _type)\
        BOOST_PP_CAT(BOOST_PP_CAT(arg, n), _type);\
        /**/

    #define BOOST_PROTO_EXTENDS(Expr, Derived, Domain)\
        Expr expr;\
        \
        typedef Expr type;\
        typedef Domain domain;\
        typedef Derived boost_proto_expr_type_;\
        typedef typename Expr::tag_type tag_type;\
        typedef typename Expr::args_type args_type;\
        typedef typename Expr::arity arity;\
        typedef void is_boost_proto_expr_;\
        \
        BOOST_PROTO_IDENTITY_TRANSFORM();\
        BOOST_PP_REPEAT(BOOST_PROTO_MAX_ARITY, BOOST_PROTO_EXTENDS_ARG, Expr)\
        \
        static Derived const make(Expr const &expr)\
        {\
            Derived that = {expr};\
            return that;\
        }\
        \
        Expr &cast()\
        {\
            return this->expr;\
        }\
        \
        Expr const &cast() const\
        {\
            return this->expr;\
        }\
        \
        Derived const &derived() const\
        {\
            return *static_cast<Derived const *>(this);\
        }\
        \
        template<typename Fun>\
        typename boost::proto::result_of::eval<Expr, Fun>::type\
        eval(Fun &fun) const\
        {\
            return this->expr.eval(fun);\
        }\
        \
        template<typename Fun>\
        typename boost::proto::result_of::eval<Expr, Fun const>::type\
        eval(Fun const &fun) const\
        {\
            return this->expr.eval(fun);\
        }\
        /**/

    #define BOOST_PROTO_EXTENDS_ASSIGN(Expr, Derived, Domain)\
        template<typename A>\
        typename boost::proto::generate<Domain, boost::proto::expr<boost::proto::tag::assign, boost::proto::args2<boost::proto::ref<Derived const>, typename boost::proto::result_of::as_arg<A>::type> > >::type const\
        operator =(A &a) const\
        {\
            typedef boost::proto::expr<boost::proto::tag::assign, boost::proto::args2<boost::proto::ref<Derived const>, typename boost::proto::result_of::as_arg<A>::type> > that_type;\
            that_type that = {{this->derived()}, boost::proto::as_arg(a)};\
            return boost::proto::generate<Domain, that_type>::make(that);\
        }\
        \
        template<typename A>\
        typename boost::proto::generate<Domain, boost::proto::expr<boost::proto::tag::assign, boost::proto::args2<boost::proto::ref<Derived const>, typename boost::proto::result_of::as_arg<A const>::type> > >::type const\
        operator =(A const &a) const\
        {\
            typedef boost::proto::expr<boost::proto::tag::assign, boost::proto::args2<boost::proto::ref<Derived const>, typename boost::proto::result_of::as_arg<A const>::type> > that_type;\
            that_type that = {{this->derived()}, boost::proto::as_arg(a)};\
            return boost::proto::generate<Domain, that_type>::make(that);\
        }\
        /**/

    #define BOOST_PROTO_EXTENDS_SUBSCRIPT(Expr, Derived, Domain)\
        template<typename A>\
        typename boost::proto::generate<Domain, boost::proto::expr<boost::proto::tag::subscript, boost::proto::args2<boost::proto::ref<Derived const>, typename boost::proto::result_of::as_arg<A>::type> > >::type const\
        operator [](A &a) const\
        {\
            typedef boost::proto::expr<boost::proto::tag::subscript, boost::proto::args2<boost::proto::ref<Derived const>, typename boost::proto::result_of::as_arg<A>::type> > that_type;\
            that_type that = {{this->derived()}, boost::proto::as_arg(a)};\
            return boost::proto::generate<Domain, that_type>::make(that);\
        }\
        \
        template<typename A>\
        typename boost::proto::generate<Domain, boost::proto::expr<boost::proto::tag::subscript, boost::proto::args2<boost::proto::ref<Derived const>, typename boost::proto::result_of::as_arg<A const>::type> > >::type const\
        operator [](A const &a) const\
        {\
            typedef boost::proto::expr<boost::proto::tag::subscript, boost::proto::args2<boost::proto::ref<Derived const>, typename boost::proto::result_of::as_arg<A const>::type> > that_type;\
            that_type that = {{this->derived()}, boost::proto::as_arg(a)};\
            return boost::proto::generate<Domain, that_type>::make(that);\
        }\
        /**/

    #define BOOST_PROTO_EXTENDS_FUNCTION(Expr, Derived, Domain)\
        template<typename Sig>\
        struct result;\
        \
        template<typename This>\
        struct result<This()>\
        {\
            typedef typename boost::proto::generate<Domain, boost::proto::expr<boost::proto::tag::function, boost::proto::args1<boost::proto::ref<Derived const> > > >::type type;\
        };\
        \
        typename boost::proto::generate<Domain, boost::proto::expr<boost::proto::tag::function, boost::proto::args1<boost::proto::ref<Derived const> > > >::type const\
        operator ()() const\
        {\
            typedef boost::proto::expr<boost::proto::tag::function, boost::proto::args1<boost::proto::ref<Derived const> > > type_type;\
            that_type that = {{this->derived()}};\
            return boost::proto::generate<Domain, that_type>::make(that);\
        }\
        \
        BOOST_PP_REPEAT_FROM_TO(1, BOOST_PP_DEC(BOOST_PROTO_MAX_ARITY), BOOST_PROTO_DEFINE_FUN_OP, ~)\
        /**/

    /// \brief extends<> class template for adding behaviors to a proto expression template
    ///
    template<typename Expr, typename Derived, typename Domain>
    struct extends
      : Expr
    {
        typedef Domain domain;
        typedef typename Expr::type type;
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

        /// INTERNAL ONLY
        ///
    #define BOOST_PP_LOCAL_MACRO(N) \
        BOOST_PROTO_DEFINE_FUN_OP(1, N, ~)\
        /**/

        /// INTERNAL ONLY
        ///
    #define BOOST_PP_LOCAL_LIMITS (1, BOOST_PP_DEC(BOOST_PROTO_MAX_ARITY))
    #include BOOST_PP_LOCAL_ITERATE()
    };

}}

#endif
