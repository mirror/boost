///////////////////////////////////////////////////////////////////////////////
/// \file arg.hpp
/// Contains definition of the argN transforms.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_TRANSFORM_ARG_HPP_EAN_11_01_2007
#define BOOST_PROTO_TRANSFORM_ARG_HPP_EAN_11_01_2007

#include <boost/xpressive/proto/detail/prefix.hpp>
#include <boost/xpressive/proto/proto_fwd.hpp>
#include <boost/xpressive/proto/traits.hpp>
#include <boost/xpressive/proto/detail/suffix.hpp>

namespace boost { namespace proto
{

    namespace transform
    {

        struct expr : proto::callable
        {
            template<typename Sig> struct result {};

            template<typename This, typename Expr, typename State, typename Visitor>
            struct result<This(Expr, State, Visitor)>
            {
                typedef Expr type;
            };

            template<typename Expr, typename State, typename Visitor>
            Expr const &
            operator ()(Expr const &expr_, State const &, Visitor &) const
            {
                return expr_;
            }
        };

        struct state : proto::callable
        {
            template<typename Sig> struct result {};

            template<typename This, typename Expr, typename State, typename Visitor>
            struct result<This(Expr, State, Visitor)>
            {
                typedef State type;
            };

            template<typename Expr, typename State, typename Visitor>
            State const &
            operator ()(Expr const &, State const &state_, Visitor &) const
            {
                return state_;
            }
        };

        struct visitor : proto::callable
        {
            template<typename Sig> struct result {};

            template<typename This, typename Expr, typename State, typename Visitor>
            struct result<This(Expr, State, Visitor)>
            {
                typedef Visitor type;
            };

            template<typename Expr, typename State, typename Visitor>
            Visitor &
            operator ()(Expr const &, State const &, Visitor &visitor_) const
            {
                return visitor_;
            }
        };

        template<int I>
        struct arg_c : proto::callable
        {
            template<typename Sig> struct result {};

            template<typename This, typename Expr, typename State, typename Visitor>
            struct result<This(Expr, State, Visitor)>
            {
                typedef typename proto::result_of::arg_c<Expr, I>::type type;
            };

            template<typename Expr, typename State, typename Visitor>
            typename proto::result_of::arg_c<Expr, I>::type
            operator ()(Expr const &expr, State const &, Visitor &) const
            {
                return proto::arg_c<I>(expr);
            }
        };
    }

    template<int I>
    struct _arg_c
      : transform::arg_c<I>
    {};

    template<>
    struct is_callable<transform::expr>
      : mpl::true_
    {};

    template<>
    struct is_callable<transform::state>
      : mpl::true_
    {};

    template<>
    struct is_callable<transform::visitor>
      : mpl::true_
    {};

    template<int I>
    struct is_callable<transform::arg_c<I> >
      : mpl::true_
    {};

    template<int I>
    struct is_callable<_arg_c<I> >
      : mpl::true_
    {};

}}

#endif
