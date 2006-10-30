///////////////////////////////////////////////////////////////////////////////
/// \file compile.hpp
/// The compile function object and meta::compile meta-function.
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_COMPILE_HPP_EAN_04_01_2005
#define BOOST_PROTO_COMPILE_HPP_EAN_04_01_2005

#include <boost/xpressive/proto/proto_fwd.hpp>
#include <boost/xpressive/proto/ref.hpp>
#include <boost/xpressive/proto/traits.hpp>

namespace boost { namespace proto
{
    namespace meta
    {
        template<typename Expr, typename State, typename Visitor, typename DomainTag>
        struct compile
        {
            typedef typename meta::unref<typename meta::as_expr<Expr>::type>::type expr_type;
            typedef compiler<typename meta::tag<expr_type>::type, DomainTag> compiler;
            typedef typename compiler::BOOST_NESTED_TEMPLATE apply<expr_type, State, Visitor>::type type;
        };
    }

    namespace op
    {
        struct compile
        {
            template<typename Sig>
            struct result;

            template<typename This, typename Expr, typename State, typename Visitor, typename DomainTag>
            struct result<This(Expr, State, Visitor, DomainTag)>
              : meta::compile<
                    typename meta::value_type<Expr>::type
                  , typename meta::value_type<State>::type
                  , typename meta::value_type<Visitor>::type
                  , typename meta::value_type<DomainTag>::type
                >
            {};

            template<typename Expr, typename State, typename Visitor, typename DomainTag>
            typename meta::compile<Expr, State, Visitor, DomainTag>::type
            operator()(Expr const &expr, State const &state, Visitor &visitor, DomainTag) const
            {
                typedef typename meta::unref<typename meta::as_expr<Expr>::type>::type expr_type;
                typedef compiler<typename meta::tag<expr_type>::type, DomainTag> compiler;
                return compiler::call(proto::unref(proto::as_expr(expr)), state, visitor);
            }
        };
    }

    op::compile const compile = {};

}} // namespace boost::proto

#endif
