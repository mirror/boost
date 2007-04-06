///////////////////////////////////////////////////////////////////////////////
// as_modifier.hpp
//
//  Copyright 2007 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_STATIC_TRANSFORMS_AS_MODIFIER_HPP_EAN_04_05_2007
#define BOOST_XPRESSIVE_DETAIL_STATIC_TRANSFORMS_AS_MODIFIER_HPP_EAN_04_05_2007

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/mpl/sizeof.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/detail/static/static.hpp>
#include <boost/xpressive/proto/proto.hpp>
#include <boost/xpressive/proto/context.hpp>
#include <boost/xpressive/proto/transform/arg.hpp>

#include <boost/xpressive/detail/static/productions/modify_compiler.hpp>

namespace boost { namespace xpressive { namespace detail
{

    ///////////////////////////////////////////////////////////////////////////////
    // as_modifier
    template<typename Grammar>
    struct as_modifier
      : Grammar
    {
        as_modifier();

        template<typename Expr, typename State, typename Visitor>
        struct apply
        {
            typedef typename proto::result_of::arg<typename proto::result_of::left<Expr>::type>::type modifier_type;
            typedef typename modifier_type::BOOST_NESTED_TEMPLATE apply<Visitor>::type visitor_type;
            typedef typename proto::trans::right<Grammar>::template apply<Expr, State, visitor_type>::type type;
        };

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &state, Visitor &visitor)
        {
            typedef typename apply<Expr, State, Visitor>::visitor_type new_visitor_type;
            new_visitor_type new_visitor(proto::arg(proto::left(expr)).call(visitor));
            new_visitor.swap(visitor);
            scoped_swap<Visitor, new_visitor_type> const undo = {&visitor, &new_visitor};
            detail::ignore_unused(undo);
            return proto::trans::right<Grammar>::call(expr, state, new_visitor);
        }
    };

}}}

#endif
