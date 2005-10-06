///////////////////////////////////////////////////////////////////////////////
// charset_matcher.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_CORE_MATCHER_CHARSET_MATCHER_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_CORE_MATCHER_CHARSET_MATCHER_HPP_EAN_10_04_2005

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
    // charset_matcher
    //
    template<typename TraitsT, bool ICaseT, typename CharSetT>
    struct charset_matcher
      : quant_style_fixed_width<1>
    {
        typedef typename TraitsT::char_type char_type;
        typedef TraitsT traits_type;
        typedef mpl::bool_<ICaseT> icase_type;

        charset_matcher(CharSetT const &charset = CharSetT())
          : charset_(charset)
        {
        }

        template<typename BidiIterT, typename NextT>
        bool match(state_type<BidiIterT> &state, NextT const &next) const
        {
            if(state.eos() || !this->charset_.test(*state.cur_, traits_cast<TraitsT>(state), icase_type()))
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

        CharSetT charset_;
    };

}}}

#endif
