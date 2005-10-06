///////////////////////////////////////////////////////////////////////////////
// quant_compilers.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_STATIC_PRODUCTIONS_QUANT_COMPILERS_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_STATIC_PRODUCTIONS_QUANT_COMPILERS_HPP_EAN_10_04_2005

#include <limits.h>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/xpressive/proto/proto.hpp>
#include <boost/xpressive/proto/compiler/branch.hpp>
#include <boost/xpressive/proto/compiler/transform.hpp>
#include <boost/xpressive/proto/compiler/conditional.hpp>
#include <boost/xpressive/detail/static/productions/quant_traits.hpp>
#include <boost/xpressive/detail/static/productions/quant_transforms.hpp>
#include <boost/xpressive/detail/static/productions/independent_compiler.hpp>
#include <boost/xpressive/detail/static/productions/domain_tags.hpp>

namespace boost { namespace xpressive { namespace detail
{

    template<bool GreedyT = true, uint_t MinT = 1, uint_t MaxT = UINT_MAX-1>
    struct plus_compiler
      : proto::conditional_compiler
        <
            use_simple_repeat_predicate
          , proto::branch_compiler<simple_repeat_branch<GreedyT, MinT, MaxT>, ind_tag>
          , proto::transform_compiler<plus_transform<GreedyT, MinT, MaxT>, seq_tag>
        >
    {
    };

    template<bool GreedyT = true, uint_t MaxT = UINT_MAX-1>
    struct star_compiler
      : proto::conditional_compiler
        <
            use_simple_repeat_predicate
          , proto::branch_compiler<simple_repeat_branch<GreedyT, 0, MaxT>, ind_tag>
          , proto::transform_compiler<star_transform<GreedyT, MaxT>, seq_tag>
        >
    {
    };

    template<bool GreedyT = true>
    struct optional_compiler
      : proto::transform_compiler<optional_transform<GreedyT>, seq_tag>
    {
    };

    ///////////////////////////////////////////////////////////////////////////////
    // generic_quant_compiler
    template<bool GreedyT, uint_t MinT, uint_t MaxT>
    struct generic_quant_compiler
      : plus_compiler<GreedyT, MinT, MaxT>
    {
    };

    template<bool GreedyT, uint_t MaxT>
    struct generic_quant_compiler<GreedyT, 0, MaxT>
      : star_compiler<GreedyT, MaxT>
    {
    };

    template<bool GreedyT>
    struct generic_quant_compiler<GreedyT, 0, 1>
      : optional_compiler<GreedyT>
    {
    };

    template<bool GreedyT>
    struct generic_quant_compiler<GreedyT, 1, 1>
      : proto::transform_compiler<proto::arg_transform, seq_tag>
    {
    };

    template<bool GreedyT>
    struct generic_quant_compiler<GreedyT, 0, 0>
      : proto::transform_compiler<epsilon_transform, seq_tag>
    {
    };

    ///////////////////////////////////////////////////////////////////////////////
    // non_greedy_compiler
    //
    struct non_greedy_compiler
    {
        template<typename OpT, typename StateT, typename VisitorT>
        struct apply
        {
            // Did you apply operator- to something that wasn't a quantifier?
            BOOST_MPL_ASSERT((is_greedy_quant<typename proto::arg_type<OpT>::type>));

            typedef typename proto::tag_type<typename proto::arg_type<OpT>::type>::type tag_type;
            typedef typename min_type<tag_type>::type min_type;
            typedef typename max_type<tag_type>::type max_type;

            typedef generic_quant_compiler
            <
                false
              , min_type::value
              , max_type::value
            > compiler_type;

            typedef typename compiler_type::BOOST_NESTED_TEMPLATE apply
            <
                typename proto::arg_type<OpT>::type
              , StateT
              , VisitorT
            >::type type;
        };

        template<typename OpT, typename StateT, typename VisitorT>
        static typename apply<OpT, StateT, VisitorT>::type
        call(OpT const &op, StateT const &state, VisitorT &visitor)
        {
            typedef typename apply<OpT, StateT, VisitorT>::compiler_type compiler_type;
            return compiler_type::call(proto::arg(op), state, visitor);
        }
    };

}}}


namespace boost { namespace proto
{

    // production for one or more quant
    template<>
    struct compiler<unary_plus_tag, xpressive::detail::seq_tag>
      : xpressive::detail::plus_compiler<>
    {
    };

    // production for zero or more quant
    template<>
    struct compiler<unary_star_tag, xpressive::detail::seq_tag>
      : xpressive::detail::star_compiler<>
    {
    };

    // production for optional
    template<>
    struct compiler<logical_not_tag, xpressive::detail::seq_tag>
      : xpressive::detail::optional_compiler<>
    {
    };

    // production for generic quantifiers
    template<unsigned int MinT, unsigned int MaxT>
    struct compiler<xpressive::detail::generic_quant_tag<MinT, MaxT>, xpressive::detail::seq_tag>
      : xpressive::detail::generic_quant_compiler<true, MinT, MaxT>
    {
    };

    // production for non-greedy quantifiers
    template<>
    struct compiler<unary_minus_tag, xpressive::detail::seq_tag>
      : xpressive::detail::non_greedy_compiler
    {
    };

}}


#endif
