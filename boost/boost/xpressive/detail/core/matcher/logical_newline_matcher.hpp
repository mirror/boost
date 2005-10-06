///////////////////////////////////////////////////////////////////////////////
// logical_newline_matcher.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_CORE_MATCHER_LOGICAL_NEWLINE_MATCHER_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_CORE_MATCHER_LOGICAL_NEWLINE_MATCHER_HPP_EAN_10_04_2005

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/detail/core/quant_style.hpp>
#include <boost/xpressive/detail/core/state.hpp>

namespace boost { namespace xpressive { namespace detail
{

    //////////////////////////////////////////////////////////////////////////
    // logical_newline_matcher
    //
    template<typename TraitsT>
    struct logical_newline_matcher
      : quant_style_variable_width
    {
        typedef typename TraitsT::char_type char_type;
        typedef typename TraitsT::char_class_type char_class_type;

        logical_newline_matcher(TraitsT const &traits)
          : newline_(lookup_classname(traits, "newline"))
          , nl_(traits.widen('\n'))
          , cr_(traits.widen('\r'))
        {
        }

        template<typename BidiIterT, typename NextT>
        bool match(state_type<BidiIterT> &state, NextT const &next) const
        {
            if(state.eos())
            {
                return false;
            }

            char_type ch = *state.cur_;
            if(traits_cast<TraitsT>(state).isctype(ch, this->newline_))
            {
                ++state.cur_;
                if(this->cr_ == ch && !state.eos() && this->nl_ == *state.cur_)
                {
                    ++state.cur_;
                    if(next.match(state))
                    {
                        return true;
                    }
                    --state.cur_;
                }
                else if(next.match(state))
                {
                    return true;
                }

                --state.cur_;
            }
            return false;
        }

    private:
        char_class_type newline_;
        char_type nl_, cr_;
    };

}}}

#endif
