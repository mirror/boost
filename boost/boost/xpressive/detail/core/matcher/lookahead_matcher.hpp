///////////////////////////////////////////////////////////////////////////////
// lookahead_matcher.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_CORE_MATCHER_LOOKAHEAD_MATCHER_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_CORE_MATCHER_LOOKAHEAD_MATCHER_HPP_EAN_10_04_2005

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/detail/core/quant_style.hpp>
#include <boost/xpressive/detail/core/state.hpp>
#include <boost/xpressive/detail/static/is_pure.hpp>
#include <boost/xpressive/detail/utility/save_restore.hpp>
#include <boost/xpressive/detail/utility/ignore_unused.hpp>

namespace boost { namespace xpressive { namespace detail
{

    ///////////////////////////////////////////////////////////////////////////////
    // lookahead_matcher
    //   XprT can be either a static_xpression, or a shared_ptr<matchable>
    //
    template<typename XprT>
    struct lookahead_matcher
      : quant_style<quant_none, mpl::size_t<0>, is_pure<XprT> >
    {
        lookahead_matcher(XprT const &xpr, bool no = false, bool do_save = !is_pure<XprT>::value)
          : xpr_(xpr)
          , not_(no)
          , do_save_(do_save)
        {
        }

        template<typename BidiIterT, typename NextT>
        bool match(state_type<BidiIterT> &state, NextT const &next) const
        {
            // Note that if is_pure<XprT>::value is true, the compiler can optimize this.
            return is_pure<XprT>::value || !this->do_save_
                ? this->match_(state, next, mpl::true_())
                : this->match_(state, next, mpl::false_());
        }

        template<typename BidiIterT, typename NextT>
        bool match_(state_type<BidiIterT> &state, NextT const &next, mpl::true_) const
        {
            BidiIterT const tmp = state.cur_;

            if(this->not_)
            {
                // negative look-ahead assertions do not trigger partial matches.
                restore partial_match = save(state.found_partial_match_);
                ignore_unused(&partial_match);

                if(get_pointer(this->xpr_)->match(state))
                {
                    state.cur_ = tmp;
                    return false;
                }
                else if(next.match(state))
                {
                    return true;
                }
            }
            else
            {
                if(!get_pointer(this->xpr_)->match(state))
                {
                    return false;
                }
                state.cur_ = tmp;
                if(next.match(state))
                {
                    return true;
                }
            }

            BOOST_ASSERT(state.cur_ == tmp);
            return false;
        }

        template<typename BidiIterT, typename NextT>
        bool match_(state_type<BidiIterT> &state, NextT const &next, mpl::false_) const
        {
            BidiIterT const tmp = state.cur_;

            // matching xpr could produce side-effects, save state
            memento<BidiIterT> mem = save_sub_matches(state);

            if(this->not_)
            {
                // negative look-ahead assertions do not trigger partial matches.
                restore partial_match = save(state.found_partial_match_);
                ignore_unused(&partial_match);

                if(get_pointer(this->xpr_)->match(state))
                {
                    restore_sub_matches(mem, state);
                    state.cur_ = tmp;
                    return false;
                }
                else if(next.match(state))
                {
                    reclaim_sub_matches(mem, state);
                    return true;
                }
                reclaim_sub_matches(mem, state);
            }
            else
            {
                if(!get_pointer(this->xpr_)->match(state))
                {
                    reclaim_sub_matches(mem, state);
                    return false;
                }
                state.cur_ = tmp;
                if(next.match(state))
                {
                    reclaim_sub_matches(mem, state);
                    return true;
                }
                restore_sub_matches(mem, state);
            }

            BOOST_ASSERT(state.cur_ == tmp);
            return false;
        }

        XprT xpr_;
        bool not_;
        bool do_save_; // true if matching xpr_ could modify the sub-matches
    };

}}}

#endif
