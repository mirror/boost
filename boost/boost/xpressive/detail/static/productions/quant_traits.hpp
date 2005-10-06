///////////////////////////////////////////////////////////////////////////////
// quant_traits.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_STATIC_PRODUCTIONS_QUANT_TRAITS_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_STATIC_PRODUCTIONS_QUANT_TRAITS_HPP_EAN_10_04_2005

#include <boost/mpl/or.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/not_equal_to.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/proto/proto_fwd.hpp>
#include <boost/xpressive/detail/static/width_of.hpp>
#include <boost/xpressive/detail/static/is_pure.hpp>

#ifdef BOOST_MSVC
# pragma warning(push)
# pragma warning(disable: 4307) // '+' : integral constant overflow
#endif

namespace boost { namespace xpressive { namespace detail
{

    ///////////////////////////////////////////////////////////////////////////////
    // generic_quant_tag
    template<uint_t MinT, uint_t MaxT>
    struct generic_quant_tag
      : proto::unary_tag
    {
        typedef mpl::integral_c<uint_t, MinT> min_type;
        typedef mpl::integral_c<uint_t, MaxT> max_type;
    };

    ///////////////////////////////////////////////////////////////////////////////
    // min_type / max_type
    template<typename TagT>
    struct min_type : TagT::min_type {};

    template<>
    struct min_type<proto::unary_plus_tag> : mpl::integral_c<uint_t, 1> {};

    template<>
    struct min_type<proto::unary_star_tag> : mpl::integral_c<uint_t, 0> {};

    template<>
    struct min_type<proto::logical_not_tag> : mpl::integral_c<uint_t, 0> {};

    template<typename TagT>
    struct max_type : TagT::max_type {};

    template<>
    struct max_type<proto::unary_plus_tag> : mpl::integral_c<uint_t, UINT_MAX-1> {};

    template<>
    struct max_type<proto::unary_star_tag> : mpl::integral_c<uint_t, UINT_MAX-1> {};

    template<>
    struct max_type<proto::logical_not_tag> : mpl::integral_c<uint_t, 1> {};

    struct use_simple_repeat_predicate
    {
        template<typename OpT, typename, typename>
        struct apply
        {
            typedef typename use_simple_repeat<typename proto::arg_type<OpT>::type>::type type;
        };
    };

    ///////////////////////////////////////////////////////////////////////////////
    // is_greedy_quant
    template<typename XprT>
    struct is_greedy_quant
      : mpl::false_
    {
    };

    template<typename OpT, typename TagT>
    struct is_greedy_quant<proto::unary_op<OpT, TagT> >
      : mpl::or_
        <
            is_same<TagT, proto::unary_plus_tag>
          , is_same<TagT, proto::unary_star_tag>
          , is_same<TagT, proto::logical_not_tag>
        >
    {
    };

    template<typename OpT, uint_t MinT, uint_t MaxT>
    struct is_greedy_quant<proto::unary_op<OpT, generic_quant_tag<MinT, MaxT> > >
      : mpl::true_
    {
    };

}}}

#ifdef BOOST_MSVC
# pragma warning(pop)
#endif

#endif
