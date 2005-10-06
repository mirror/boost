///////////////////////////////////////////////////////////////////////////////
// action.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_CORE_ACTION_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_CORE_ACTION_HPP_EAN_10_04_2005

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <typeinfo>
#include <stdexcept>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/detail/core/quant_style.hpp>
#include <boost/xpressive/detail/core/action_state.hpp>
#include <boost/xpressive/detail/core/matcher/action_matcher.hpp>

namespace boost { namespace xpressive
{

///////////////////////////////////////////////////////////////////////////////
// action
//
template<typename ActionT, typename SavedT>
struct action
  : detail::action_matcher<ActionT>
{
    typedef ActionT action_type;
    typedef SavedT saved_type;

    SavedT &save()
    {
        return *static_cast<SavedT *>(this);
    }

    template<typename BidiIterT>
    bool operator ()(match_results<BidiIterT> const &match, BidiIterT cur)
    {
        return true;
    }

    void restore(SavedT const &saved)
    {
        this->action_() = saved;
    }
};

template<typename ActionT>
struct action<ActionT, void>
  : action<ActionT, int>
{
    int save()
    {
        return 0;
    }

    void restore(int)
    {
    }
};

}} // namespace boost::xpressive

#endif
