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
          : proto::matches<Expr, proto::subscript<set_initializer_type, proto::_> >
        {};
    };

    ///////////////////////////////////////////////////////////////////////////////
    // action_transform
    //  turn A[B] into (mark_begin(n) >> A >> mark_end(n) >> action_matcher<B>(n))
    struct action_transform
    {
        template<typename Expr, typename State, typename Visitor>
        struct apply
        {
            typedef typename proto::result_of::left<Expr>::type expr_type;
            typedef typename proto::result_of::right<Expr>::type action_type;
            typedef typename proto::result_of::deep_copy<action_type>::type action_copy_type;

            typedef typename marker_transform::
                template apply<expr_type, State, Visitor>::type
            marked_expr_type;

            typedef typename mpl::if_<
                proto::matches<action_type, proto::terminal<predicate_placeholder<proto::_> > >
              , predicate_matcher<action_copy_type>
              , action_matcher<action_copy_type>
            >::type matcher_type;

            typedef typename proto::right_shift
            <
                marked_expr_type
              , typename proto::terminal<matcher_type>::type
            >::type type;
        };

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &state, Visitor &visitor)
        {
            typedef apply<Expr, State, Visitor> apply_type;
            typedef typename apply_type::matcher_type matcher_type;

            typename apply_type::marked_expr_type marked_expr =
                marker_transform::call(proto::left(expr), state, visitor);

            typename apply_type::type that =
            {
                marked_expr
              , {
                    matcher_type
                    (
                        proto::deep_copy(proto::right(expr))
                      , proto::arg(proto::left(marked_expr)).mark_number_
                    )
                }
            };
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
    struct compiler<tag::right_shift, xpressive::detail::seq_tag, void>
      : reverse_fold_compiler<xpressive::detail::seq_tag>
    {
    };

    template<>
    struct compiler<tag::subscript, xpressive::detail::seq_tag, void>
      : xpressive::detail::subscript_compiler
    {
    };
}}

#endif
