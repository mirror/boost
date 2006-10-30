///////////////////////////////////////////////////////////////////////////////
// marker_transform.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_STATIC_PRODUCTIONS_MARKER_TRANSFORM_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_STATIC_PRODUCTIONS_MARKER_TRANSFORM_HPP_EAN_10_04_2005

#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/proto/proto.hpp>
#include <boost/xpressive/proto/compiler/transform.hpp>

namespace boost { namespace xpressive { namespace detail
{
    ///////////////////////////////////////////////////////////////////////////////
    // is_marker
    // (s1= ...) is a marker
    template<typename Expr, long Arity = Expr::arity::value>
    struct is_marker
      : mpl::false_
    {};

    template<typename Expr>
    struct is_marker<Expr, 2>
      : mpl::and_<
            is_same<proto::assign_tag, typename Expr::tag_type>
          , is_same<mark_tag, typename proto::meta::unref<typename Expr::arg0_type>::type>
        >
    {};

    ///////////////////////////////////////////////////////////////////////////////
    // is_marker_predicate
    struct is_marker_predicate
    {
        template<typename Expr, typename, typename>
        struct apply
          : is_marker<Expr>
        {};
    };

    ///////////////////////////////////////////////////////////////////////////////
    // marker_insert_transform
    //   Insert mark tags before and after the expression
    struct marker_insert_transform
    {
        template<typename Expr, typename, typename>
        struct apply
        {
            typedef typename proto::meta::binary_expr
            <
                proto::right_shift_tag
              , proto::meta::terminal<mark_begin_matcher>::type
              , typename proto::meta::binary_expr
                <
                    proto::right_shift_tag
                  , Expr
                  , proto::meta::terminal<mark_end_matcher>::type
                >::type
            >::type type;
        };

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &, Visitor &visitor, int mark_nbr = 0)
        {
            // if we're inserting a mark, and we're not being told the mark number,
            // we're inserting a hidden mark ... so grab the next hidden mark number.
            if(0 == mark_nbr)
            {
                mark_nbr = visitor.get_hidden_mark();
            }

            typename apply<Expr, State, Visitor>::type that =
                {
                    {mark_begin_matcher(mark_nbr)}
                  , {
                        expr
                      , {mark_end_matcher(mark_nbr)}
                    }
                };
            return that;
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // marker_replace_transform
    struct marker_replace_transform
      : proto::compose_transforms<proto::right_transform, marker_insert_transform>
    {
        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &state, Visitor &visitor)
        {
            return marker_insert_transform::call
            (
                expr.cast().arg1 //proto::right(expr)
              , state
              , visitor
              , proto::arg(proto::left(expr)).mark_number_
            );
        }
    };

}}}

#endif
