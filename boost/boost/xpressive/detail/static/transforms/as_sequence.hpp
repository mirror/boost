///////////////////////////////////////////////////////////////////////////////
// as_sequence.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_STATIC_TRANSFORMS_AS_SEQUENCE_HPP_EAN_04_01_2007
#define BOOST_XPRESSIVE_DETAIL_STATIC_TRANSFORMS_AS_SEQUENCE_HPP_EAN_04_01_2007

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/detail/static/static.hpp>
#include <boost/xpressive/detail/static/transforms/fold_to_xxx.hpp>

namespace boost { namespace xpressive { namespace detail
{

    template<typename Grammar>
    struct in_sequence
      : Grammar
    {
        in_sequence();

        template<typename Expr, typename State, typename Visitor>
        struct apply
        {
            typedef static_xpression<
                typename Grammar::template apply<Expr, State, Visitor>::type
              , State
            > type;
        };

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &state, Visitor &visitor)
        {
            return typename apply<Expr, State, Visitor>::type(
                Grammar::call(expr, state, visitor)
              , state
            );
        }
    };

    //template<typename Grammar>
    //struct as_sequence
    //  : reverse_fold_to_xxx<
    //        typename Grammar::tag_type
    //      , typename Grammar::arg0_type
    //      , in_sequence
    //    >
    //{
    //    BOOST_MPL_ASSERT((
    //        is_same<
    //            typename Grammar::arg0_type
    //          , typename Grammar::arg1_type
    //        >
    //    ));
    //};

}}}

#endif
