///////////////////////////////////////////////////////////////////////////////
// attr_matcher.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_CORE_MATCHER_ATTR_MATCHER_HPP_EAN_06_09_2007
#define BOOST_XPRESSIVE_DETAIL_CORE_MATCHER_ATTR_MATCHER_HPP_EAN_06_09_2007

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
    // char_cmp
    //
    template<typename Traits, bool ICase>
    struct char_cmp
    {
        typedef typename Traits::char_type char_type;
        Traits const &traits_;

        bool operator ()(char_type ch1, char_type ch2) const
        {
            return this->traits_.translate(ch1) == this->traits_.translate(ch2);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // char_cmp
    //
    template<typename Traits>
    struct char_cmp<Traits, true>
    {
        typedef typename Traits::char_type char_type;
        Traits const &traits_;

        bool operator ()(char_type ch1, char_type ch2) const
        {
            return this->traits_.translate_nocase(ch1) == this->traits_.translate_nocase(ch2);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // attr_matcher
    //
    template<typename Matcher, typename Traits, bool ICase>
    struct attr_matcher
      : quant_style<quant_none, 0, false>
    {
        attr_matcher(int slot, Matcher const &matcher)
          : slot_(slot-1)
          , matcher_(matcher)
        {}

        template<typename BidiIter, typename Next>
        bool match(match_state<BidiIter> &state, Next const &next) const
        {
            BidiIter tmp = state.cur_;
            char_cmp<Traits, ICase> cmp = {traits_cast<Traits>(state)};
            typename Matcher::result_type const &result = this->matcher_(state.cur_, state.end_, cmp);
            if(result)
            {
                void const *old_slot = state.attr_context_.attr_slots_[this->slot_];
                state.attr_context_.attr_slots_[this->slot_] = &*result;
                if(next.match(state))
                {
                    return true;
                }
                state.attr_context_.attr_slots_[this->slot_] = old_slot;
            }
            state.cur_ = tmp;
            return false;
        }

        int slot_;
        Matcher const &matcher_;
    };

}}}

#endif
