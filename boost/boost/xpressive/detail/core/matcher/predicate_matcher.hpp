///////////////////////////////////////////////////////////////////////////////
// predicate_matcher.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_CORE_MATCHER_PREDICATE_MATCHER_HPP_EAN_03_22_2007
#define BOOST_XPRESSIVE_DETAIL_CORE_MATCHER_PREDICATE_MATCHER_HPP_EAN_03_22_2007

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/detail/core/quant_style.hpp>
#include <boost/xpressive/detail/core/state.hpp>

namespace boost { namespace xpressive { namespace detail
{

    ///////////////////////////////////////////////////////////////////////////////
    // predicate_matcher
    //
    template<typename Predicate>
    struct predicate_matcher
      : quant_style_assertion
    {
        int sub_;
        Predicate predicate_;

        predicate_matcher(Predicate const &pred, int sub)
          : sub_(sub)
          , predicate_(pred)
        {
        }

        template<typename BidiIter, typename Next>
        bool match(state_type<BidiIter> &state, Next const &next) const
        {
            sub_match<BidiIter> const &sub = state.sub_match(this->sub_);
            return proto::arg(this->predicate_).pred(sub) && next.match(state);
        }
    };

}}}

#endif // BOOST_XPRESSIVE_DETAIL_CORE_MATCHER_PREDICATE_MATCHER_HPP_EAN_03_22_2007
