///////////////////////////////////////////////////////////////////////////////
/// \file pass_through.hpp
/// 
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_COMPILER_PASS_THROUGH_HPP_EAN_04_23_2006
#define BOOST_PROTO_COMPILER_PASS_THROUGH_HPP_EAN_04_23_2006

#include <boost/type_traits/is_same.hpp>
#include <boost/fusion/sequence/view/transform_view.hpp>
#include <boost/xpressive/proto/proto.hpp>
#include <boost/xpressive/proto/traits.hpp>
#include <boost/xpressive/proto/fusion.hpp>
#include <boost/xpressive/proto/make_expr.hpp>

namespace boost { namespace proto
{

    template<typename State, typename Visitor, typename DomainTag>
    struct pass_through_transformer
    {
        template<typename Expr>
        struct result
          : meta::compile<typename meta::unref<Expr>::type, State, Visitor, DomainTag>
        {};

        pass_through_transformer(State const &state, Visitor &visitor)
          : state_(state)
          , visitor_(visitor)
        {}

        template<typename Expr>
        typename result<Expr>::type operator ()(Expr const &expr) const
        {
            return proto::compile(expr.cast(), this->state_, this->visitor_, DomainTag());
        }

    private:
        State const &state_;
        Visitor &visitor_;
    };

    template<typename DomainTag>
    struct pass_through_compiler
    {
        template<typename Expr, typename State, typename Visitor, typename Tag = typename Expr::tag_type>
        struct apply
        {
            typedef typename meta::as_expr_ref<Expr>::type ref_type;
            typedef pass_through_transformer<State, Visitor, DomainTag> trans_type;
            typedef fusion::transform_view<ref_type const, trans_type> view_type;
            typedef typename meta::unpack_expr<Tag, view_type>::type type;
        };

        template<typename Expr, typename State, typename Visitor>
        struct apply<Expr, State, Visitor, terminal_tag>
        {
            typedef Expr type;
        };

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &state, Visitor &visitor)
        {
            return pass_through_compiler::call_impl(expr, state, visitor, typename Expr::tag_type());
        }

        template<typename Expr, typename State, typename Visitor, typename Tag>
        static typename apply<Expr, State, Visitor>::type
        call_impl(Expr const &expr, State const &state, Visitor &visitor, Tag)
        {
            typedef typename meta::as_expr_ref<Expr>::type ref_type;
            typedef pass_through_transformer<State, Visitor, DomainTag> trans_type;
            trans_type trans(state, visitor);
            fusion::transform_view<ref_type const, trans_type> view(proto::as_expr_ref(expr), trans);
            return proto::unpack_expr<Tag>(view);
        }

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call_impl(Expr const &expr, State const &, Visitor &, terminal_tag)
        {
            return expr;
        }
    };

}}

#endif
