///////////////////////////////////////////////////////////////////////////////
// range_matcher.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_CORE_MATCHER_RANGE_MATCHER_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_CORE_MATCHER_RANGE_MATCHER_HPP_EAN_10_04_2005

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/mpl/bool.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/detail/core/quant_style.hpp>
#include <boost/xpressive/detail/core/state.hpp>

namespace boost { namespace xpressive { namespace detail
{

    ///////////////////////////////////////////////////////////////////////////////
    // range_matcher
    //
    template<typename TraitsT, bool ICaseT>
    struct range_matcher
      : quant_style_fixed_width<1>
    {
        typedef typename TraitsT::char_type char_type;
        typedef mpl::bool_<ICaseT> icase_type;
        char_type ch_min_;
        char_type ch_max_;
        bool not_;

        range_matcher(char_type ch_min, char_type ch_max, bool no, TraitsT const &)
          : ch_min_(ch_min)
          , ch_max_(ch_max)
          , not_(no)
        {
        }

        bool in_range(TraitsT const &traits, char_type ch, mpl::false_) const // case-sensitive
        {
            return traits.in_range(this->ch_min_, this->ch_max_, ch);
        }

        bool in_range(TraitsT const &traits, char_type ch, mpl::true_) const // case-insensitive
        {
            return traits.in_range_nocase(this->ch_min_, this->ch_max_, ch);
        }

        template<typename BidiIterT, typename NextT>
        bool match(state_type<BidiIterT> &state, NextT const &next) const
        {
            if(state.eos() || this->not_ ==
                this->in_range(traits_cast<TraitsT>(state), *state.cur_, icase_type()))
            {
                return false;
            }

            ++state.cur_;
            if(next.match(state))
            {
                return true;
            }

            --state.cur_;
            return false;
        }
    };

}}}

#endif
