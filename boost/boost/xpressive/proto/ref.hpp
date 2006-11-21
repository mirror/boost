///////////////////////////////////////////////////////////////////////////////
/// \file ref.hpp
/// Utility for storing a sub-expr by reference
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_REF_HPP_EAN_04_01_2005
#define BOOST_PROTO_REF_HPP_EAN_04_01_2005

#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/xpressive/proto/proto_fwd.hpp>

namespace boost { namespace proto
{

#define BOOST_PROTO_ARG(z, n, data)\
    typedef typename Expr::BOOST_PP_CAT(BOOST_PP_CAT(arg, n), _type) BOOST_PP_CAT(BOOST_PP_CAT(arg, n), _type);

    template<typename Expr>
    struct ref
    {
        typedef Expr expr_type;
        typedef typename Expr::tag_type tag_type;
        typedef typename Expr::args_type args_type;
        typedef typename Expr::arity arity;
        typedef typename Expr::id_type id_type;
        typedef proto_ref_tag fusion_tag;
        typedef void is_boost_proto_ref_;
        typedef void is_boost_proto_expr_;

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
        template<typename T>
        struct unref<T, false>
        {
            typedef T type;
        };

        template<typename T>
        struct unref<T, true>
        {
            typedef typename T::expr_type type;
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
                return unref::call(t, meta::is_expr<T>());
            }

        private:
            template<typename T>
            static typename meta::unref<T>::type const &call(T const &t, mpl::true_)
            {
                return t.cast();
            }

            template<typename T>
            static typename meta::unref<T>::type const &call(T const &t, mpl::false_)
            {
                return t;
            }
        };
    }

    op::unref const unref = {};
}}

#endif
