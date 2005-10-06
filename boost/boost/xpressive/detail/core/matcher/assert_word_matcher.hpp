///////////////////////////////////////////////////////////////////////////////
// assert_word_matcher.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_CORE_MATCHER_ASSERT_WORD_MATCHER_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_CORE_MATCHER_ASSERT_WORD_MATCHER_HPP_EAN_10_04_2005

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/assert.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/detail/core/quant_style.hpp>
#include <boost/xpressive/detail/core/state.hpp>

namespace boost { namespace xpressive { namespace detail
{

    ///////////////////////////////////////////////////////////////////////////////
    // word_boundary
    //
    template<bool IsBoundaryT>
    struct word_boundary
    {
        template<typename BidiIterT>
        static bool eval(bool prevword, bool thisword, state_type<BidiIterT> &state)
        {
            if((state.flags_.match_not_bow_ && state.bos()) || (state.flags_.match_not_eow_ && state.eos()))
            {
                return !IsBoundaryT;
            }

            return IsBoundaryT == (prevword != thisword);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // word_begin
    //
    struct word_begin
    {
        template<typename BidiIterT>
        static bool eval(bool prevword, bool thisword, state_type<BidiIterT> &state)
        {
            if(state.flags_.match_not_bow_ && state.bos())
            {
                return false;
            }

            return !prevword && thisword;
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // word_end
    //
    struct word_end
    {
        template<typename BidiIterT>
        static bool eval(bool prevword, bool thisword, state_type<BidiIterT> &state)
        {
            if(state.flags_.match_not_eow_ && state.eos())
            {
                return false;
            }

            return prevword && !thisword;
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // assert_word_matcher
    //
    template<typename CondT, typename TraitsT>
    struct assert_word_matcher
      : quant_style_assertion
    {
        typedef typename TraitsT::char_type char_type;

        assert_word_matcher(TraitsT const &traits)
          : word_(lookup_classname(traits, "w"))
        {
            BOOST_ASSERT(0 != this->word_);
        }

        bool is_word(TraitsT const &traits, char_type ch) const
        {
            return traits.isctype(traits.translate(ch), this->word_);
        }

        template<typename BidiIterT, typename NextT>
        bool match(state_type<BidiIterT> &state, NextT const &next) const
        {
            BidiIterT cur = state.cur_;
            bool const thisword = !state.eos() && this->is_word(traits_cast<TraitsT>(state), *cur);
            bool const prevword = (!state.bos() || state.flags_.match_prev_avail_)
                && this->is_word(traits_cast<TraitsT>(state), *--cur);

            return CondT::eval(prevword, thisword, state) && next.match(state);
        }

        typename TraitsT::char_class_type word_;
    };

}}}

#endif
