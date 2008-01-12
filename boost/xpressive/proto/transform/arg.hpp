///////////////////////////////////////////////////////////////////////////////
/// \file arg.hpp
/// Contains definition of the argN transforms.
//
//  Copyright 2007 Eric Niebler. Distributed under the Boost
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

        struct _expr : callable
        {
            template<typename Sig>
            struct result;

            template<typename This, typename Expr, typename State, typename Visitor>
            struct result<This(Expr, State, Visitor)>
            {
                typedef Expr type;
            };

            //template<typename This, typename Expr, typename State, typename Visitor>
            //struct result<This(Expr &, State, Visitor)>
            //{
            //    typedef Expr const &type;
            //};

            template<typename Expr, typename State, typename Visitor>
            Expr const &
            operator ()(Expr const &expr, State const &, Visitor &) const
            {
                return expr;
            }
        };

        struct _state : callable
        {
            template<typename Sig>
            struct result;

            template<typename This, typename Expr, typename State, typename Visitor>
            struct result<This(Expr, State, Visitor)>
            {
                typedef State type;
            };

            //template<typename This, typename Expr, typename State, typename Visitor>
            //struct result<This(Expr, State &, Visitor)>
            //{
            //    typedef State const &type;
            //};

            template<typename Expr, typename State, typename Visitor>
            State const &
            operator ()(Expr const &, State const &state, Visitor &) const
            {
                return state;
            }
        };

        struct _visitor : callable
        {
            template<typename Sig>
            struct result;

            template<typename This, typename Expr, typename State, typename Visitor>
            struct result<This(Expr, State, Visitor)>
            {
                typedef Visitor type;
            };

            template<typename Expr, typename State, typename Visitor>
            Visitor &
            operator ()(Expr const &, State const &, Visitor &visitor) const
            {
                return visitor;
            }
        };

        template<int I>
        struct _arg_c : callable
        {
            template<typename Sig>
            struct result;

            //template<typename This, typename Expr, typename State, typename Visitor>
            //struct result<This(Expr, State, Visitor)>
            //  : proto::result_of::value_at_c<Expr, I>
            //{};

            //template<typename This, typename Expr, typename State, typename Visitor>
            //struct result<This(Expr &, State, Visitor)>
            //  : proto::result_of::arg_c<Expr const &, I>
            //{};

            template<typename This, typename Expr, typename State, typename Visitor>
            struct result<This(Expr, State, Visitor)>
              : proto::result_of::arg_c<Expr, I>
            {};

            template<typename Expr, typename State, typename Visitor>
            typename proto::result_of::arg_c<Expr, I>::type
            operator ()(Expr const &expr, State const &, Visitor &) const
            {
                return proto::arg_c<I>(expr);
            }
        };

        struct _arg0 : _arg_c<0> {};
        struct _arg1 : _arg_c<1> {};
        struct _arg2 : _arg_c<2> {};
        struct _arg3 : _arg_c<3> {};
        struct _arg4 : _arg_c<4> {};
        struct _arg5 : _arg_c<5> {};
        struct _arg6 : _arg_c<6> {};
        struct _arg7 : _arg_c<7> {};
        struct _arg8 : _arg_c<8> {};
        struct _arg9 : _arg_c<9> {};

        typedef _arg0 _arg;
        typedef _arg0 _left;
        typedef _arg1 _right;
    }

    template<int I>
    struct is_callable<transform::_arg_c<I> >
      : mpl::true_
    {};

}}

#endif
