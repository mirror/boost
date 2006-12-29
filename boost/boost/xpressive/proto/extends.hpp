///////////////////////////////////////////////////////////////////////////////
/// \file entends.hpp
/// A base class for defining end-user expression types
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_EXTENDS_HPP_EAN_11_1_2006
#define BOOST_PROTO_EXTENDS_HPP_EAN_11_1_2006

#include <boost/mpl/bool.hpp>
#include <boost/xpressive/proto/ref.hpp>
#include <boost/xpressive/proto/args.hpp>
#include <boost/xpressive/proto/expr.hpp>
#include <boost/preprocessor/punctuation/comma.hpp>

namespace boost { namespace proto { namespace extends_private_
{
    template<typename Expr>
    struct extends
      : Expr
    {
        typedef Expr type;
        typedef Expr boost_proto_extends_private_extends_expr_type_;
        typedef void is_boost_proto_extends_private_extends_;

        extends()
          : Expr()
        {}

        extends(Expr const &expr)
          : Expr(expr)
        {}

        void assign(Expr const &that)
        {
            *static_cast<Expr *>(this) = that;
        }

        using Expr::operator =;
    };

}}}

#endif
