///////////////////////////////////////////////////////////////////////////////
// assert_bol_matcher.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_CORE_MATCHER_ASSERT_BOL_MATCHER_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_CORE_MATCHER_ASSERT_BOL_MATCHER_HPP_EAN_10_04_2005

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/detail/core/quant_style.hpp>
#include <boost/xpressive/detail/core/state.hpp>
#include <boost/xpressive/detail/core/matcher/assert_line_base.hpp>

namespace boost { namespace xpressive { namespace detail
{

    ///////////////////////////////////////////////////////////////////////////////
    // assert_bol_matcher
    //
    template<typename TraitsT>
    struct assert_bol_matcher
      : assert_line_base<TraitsT>
    {
        assert_bol_matcher(TraitsT const &traits)
          : assert_line_base<TraitsT>(traits)
        {
        }

        template<typename BidiIterT, typename NextT>
        bool match(state_type<BidiIterT> &state, NextT const &next) const
        {
            if(state.bos())
            {
                if(!state.flags_.match_bol_)
                {
                    return false;
                }
            }
            else if(!this->is_line_break(state))
            {
                return false;
            }

            return next.match(state);
        }
    };

}}}

#endif
