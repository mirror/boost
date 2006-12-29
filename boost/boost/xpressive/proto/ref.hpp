///////////////////////////////////////////////////////////////////////////////
/// \file ref.hpp
/// Utility for storing a sub-expr by reference
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_REF_HPP_EAN_04_01_2005
#define BOOST_PROTO_REF_HPP_EAN_04_01_2005

#include <boost/mpl/bool.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/xpressive/proto/proto_fwd.hpp>

namespace boost { namespace proto
{

#define BOOST_PROTO_ARG(z, n, data)\
    typedef\
        typename Expr::BOOST_PP_CAT(BOOST_PP_CAT(arg, n), _type)\
    BOOST_PP_CAT(BOOST_PP_CAT(arg, n), _type);\
    /**/

    template<typename Expr>
    struct ref
    {
        typedef Expr type;
        typedef typename Expr::tag_type tag_type;
        typedef typename Expr::args_type args_type;
        typedef typename Expr::arity arity;
        typedef proto_ref_tag fusion_tag;
        typedef void is_boost_proto_ref_;
        typedef void is_boost_proto_expr_;
        typedef Expr boost_proto_expr_type_;

        BOOST_PROTO_IDENTITY_TRANSFORM();
        BOOST_PP_REPEAT(BOOST_PROTO_MAX_ARITY, BOOST_PROTO_ARG, _)

        Expr const &cast() const
        {
            return this->expr;
        }

        Expr const &expr;
    };

#undef BOOST_PROTO_ARG

    namespace meta
    {
        template<typename T, typename EnableIf>
        struct unref
        {
            typedef T type;
            typedef T const &reference;

        private:
            friend struct op::unref;
            static T const &call(T const &t)
            {
                return t;
            }
        };

        template<typename T>
        struct unref<T, typename T::is_boost_proto_expr_>
        {
            typedef typename T::type type;
            typedef typename T::type const &reference;

        private:
            friend struct op::unref;
            static typename T::type const &call(T const &t)
            {
                return t.cast();
            }
        };

        template<typename T>
        struct unref<T &, void>
        {
            typedef T type;
            typedef T &reference;
        };

        template<typename T>
        struct unref<T const &, void>
        {
            typedef T type;
            typedef T const &reference;
        };

        template<typename T, std::size_t N>
        struct unref<T (&)[N], void>
        {
            typedef T (&type)[N];
            typedef T (&reference)[N];
        };

        template<typename T, std::size_t N>
        struct unref<T const (&)[N], void>
        {
            typedef T const (&type)[N];
            typedef T const (&reference)[N];
        };
    }

    namespace op
    {
        struct unref
        {
            template<typename T>
            struct result;

            template<typename This, typename T>
            struct result<This(T)>
              : meta::unref<typename meta::value_type<T>::type>
            {};

            template<typename T>
            typename meta::unref<T>::type const &operator()(T const &t) const
            {
                return meta::unref<T>::call(t);
            }
        };
    }

    op::unref const unref = {};
}}

#endif
