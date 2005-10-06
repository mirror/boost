///////////////////////////////////////////////////////////////////////////////
// mark_matcher.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_CORE_MATCHER_MARK_MATCHER_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_CORE_MATCHER_MARK_MATCHER_HPP_EAN_10_04_2005

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/assert.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/detail/core/quant_style.hpp>
#include <boost/xpressive/detail/core/state.hpp>
#include <boost/xpressive/detail/utility/traits_utils.hpp>

namespace boost { namespace xpressive { namespace detail
{

    ///////////////////////////////////////////////////////////////////////////////
    // mark_matcher
    //
    template<typename TraitsT, bool ICaseT>
    struct mark_matcher
      : quant_style_fixed_unknown_width
    {
        typedef mpl::bool_<ICaseT> icase_type;
        int mark_number_;

        mark_matcher(int mark_number, TraitsT const &)
          : mark_number_(mark_number)
        {
        }

        template<typename BidiIterT, typename NextT>
            bool match(state_type<BidiIterT> &state, NextT const &next) const
        {
            BOOST_ASSERT(this->mark_number_ < static_cast<int>(state.mark_count_));
            sub_match_impl<BidiIterT> const &br = state.sub_match(this->mark_number_);

            if(!br.matched)
            {
                return false;
            }

            BidiIterT const tmp = state.cur_;
            for(BidiIterT begin = br.first, end = br.second; begin != end; ++begin, ++state.cur_)
            {
                if(state.eos()
                    || detail::translate(*state.cur_, traits_cast<TraitsT>(state), icase_type())
                    != detail::translate(*begin, traits_cast<TraitsT>(state), icase_type()))
                {
                    state.cur_ = tmp;
                    return false;
                }
            }

            if(next.match(state))
            {
                return true;
            }

            state.cur_ = tmp;
            return false;
        }

        template<typename BidiIterT>
        std::size_t get_width(state_type<BidiIterT> *state) const
        {
            if(0 == state)
            {
                return unknown_width();
            }
            sub_match_impl<BidiIterT> &br = state->sub_match(this->mark_number_);
            return br.matched ? static_cast<std::size_t>(std::distance(br.first, br.second)) : 1U;
        }
    };

}}}

#endif
