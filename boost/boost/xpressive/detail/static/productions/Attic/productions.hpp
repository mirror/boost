///////////////////////////////////////////////////////////////////////////////
// productions.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_STATIC_PRODUCTIONS_PRODUCTIONS_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_STATIC_PRODUCTIONS_PRODUCTIONS_HPP_EAN_10_04_2005

#include <boost/ref.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>

#include <boost/xpressive/proto/proto.hpp>
#include <boost/xpressive/proto/compiler/fold.hpp>
#include <boost/xpressive/proto/compiler/transform.hpp>
#include <boost/xpressive/proto/compiler/conditional.hpp>

#include <boost/xpressive/detail/static/productions/domain_tags.hpp>
#include <boost/xpressive/detail/static/productions/visitor.hpp>
#include <boost/xpressive/detail/static/productions/quant_compilers.hpp>
#include <boost/xpressive/detail/static/productions/alt_compilers.hpp>
#include <boost/xpressive/detail/static/productions/independent_compiler.hpp>
#include <boost/xpressive/detail/static/productions/noop_compiler.hpp>
#include <boost/xpressive/detail/static/productions/modify_compiler.hpp>
#include <boost/xpressive/detail/static/productions/complement_compiler.hpp>
#include <boost/xpressive/detail/static/productions/set_compilers.hpp>
#include <boost/xpressive/detail/static/productions/marker_compiler.hpp>
#include <boost/xpressive/detail/static/productions/charset_transforms.hpp>

namespace boost { namespace xpressive { namespace detail
{

    ///////////////////////////////////////////////////////////////////////////////
    //
    struct is_set_initializer_predicate
    {
        template<typename Expr, typename, typename>
        struct apply
        {
            typedef typename is_same<
                typename proto::unref<typename Expr::arg0_type>::type
              , set_initializer_type
            >::type type;
        };
    };

    ///////////////////////////////////////////////////////////////////////////////
    //
    struct action_transform
    {
        template<typename Expr, typename, typename>
        struct apply
        {
            typedef typename proto::meta::binary_expr
            <
                proto::right_shift_tag
              , typename Expr::arg0_type
              , typename Expr::arg1_type
            >::type type;
        };

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &, Visitor &)
        {
            typename apply<Expr, State, Visitor>::type that =
                {proto::left(expr), proto::right(expr)};
            return that;
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // subscript_compiler
    struct subscript_compiler
      : proto::conditional_compiler
        <
            is_set_initializer_predicate
          , proto::transform_compiler<charset_transform, seq_tag>
          , proto::transform_compiler<action_transform, seq_tag>
        >
    {
    };

}}}


///////////////////////////////////////////////////////////////////////////////
// misc regex compiler productions
namespace boost { namespace proto
{
    // production for sequences in sequence
    template<>
    struct compiler<right_shift_tag, xpressive::detail::seq_tag, void>
      : reverse_fold_compiler<xpressive::detail::seq_tag>
    {
    };

    template<>
    struct compiler<subscript_tag, xpressive::detail::seq_tag, void>
      : xpressive::detail::subscript_compiler
    {
    };
}}

#endif
