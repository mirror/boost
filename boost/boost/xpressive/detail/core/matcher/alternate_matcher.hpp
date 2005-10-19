///////////////////////////////////////////////////////////////////////////////
// alternate_matcher.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_CORE_MATCHER_ALTERNATE_MATCHER_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_CORE_MATCHER_ALTERNATE_MATCHER_HPP_EAN_10_04_2005

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <vector>

#include <boost/version.hpp>
#if BOOST_VERSION <= 103200
// WORKAROUND for Fusion bug in Boost 1.32
namespace boost { namespace fusion
{
    namespace detail { struct iterator_root; }
    using detail::iterator_root;
}}
#endif

#include <boost/shared_ptr.hpp>
#include <boost/spirit/fusion/sequence/range.hpp>
#include <boost/spirit/fusion/algorithm/for_each.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/detail/core/quant_style.hpp>
#include <boost/xpressive/detail/core/state.hpp>
#include <boost/xpressive/detail/static/width_of.hpp>
#include <boost/xpressive/detail/static/is_pure.hpp>
#include <boost/xpressive/detail/dynamic/matchable.hpp>
#include <boost/xpressive/detail/utility/hash_peek_bitset.hpp>
#include <boost/xpressive/detail/utility/algorithm.hpp>
#include <boost/xpressive/detail/utility/any.hpp>

namespace boost { namespace xpressive { namespace detail
{

    ///////////////////////////////////////////////////////////////////////////////
    // alt_match_pred
    //
    template<typename BidiIterT, typename NextT>
    struct alt_match_pred
    {
        state_type<BidiIterT> &state_;

        alt_match_pred(state_type<BidiIterT> &state)
          : state_(state)
        {
        }

        template<typename XprT>
        bool operator ()(XprT const &xpr) const
        {
            return get_pointer(xpr)->BOOST_NESTED_TEMPLATE push_match<NextT>(this->state_);
        }

    private:
        alt_match_pred &operator =(alt_match_pred const &);
    };

    ///////////////////////////////////////////////////////////////////////////////
    // alt_match
    //
    template<typename BidiIterT>
    inline bool alt_match
    (
        std::vector<shared_ptr<matchable<BidiIterT> const> > const &alternates
      , state_type<BidiIterT> &state
      , matchable<BidiIterT> const &
    )
    {
        typedef alt_match_pred<BidiIterT, matchable<BidiIterT> > alt_match_pred;
        return detail::any(alternates.begin(), alternates.end(), alt_match_pred(state));
    }

    template<typename BidiIterT, typename NextT, typename AlternatesT>
    inline bool alt_match
    (
        fusion::sequence_base<AlternatesT> const &alternates
      , state_type<BidiIterT> &state
      , NextT const &
    )
    {
        typedef alt_match_pred<BidiIterT, NextT> alt_match_pred;
        return fusion::any(alternates.cast(), alt_match_pred(state));
    }

    ///////////////////////////////////////////////////////////////////////////////
    // make_range
    template<typename BeginT, typename EndT>
    inline fusion::range<BeginT, EndT> make_range(BeginT const &begin, EndT const &end)
    {
        return fusion::range<BeginT, EndT>(begin, end);
    }

    ///////////////////////////////////////////////////////////////////////////////
    // alt_get_width_pred
    //
    template<typename BidiIterT>
    struct alt_get_width_pred
    {
        state_type<BidiIterT> *state_;
        std::size_t *width_;

        alt_get_width_pred(state_type<BidiIterT> *state, std::size_t *width)
          : state_(state)
          , width_(width)
        {
        }

        template<typename XprT>
        void operator ()(XprT const &xpr) const
        {
            if(*this->width_ != unknown_width())
            {
                std::size_t that_width = get_pointer(xpr)->get_width(this->state_);
                if(*this->width_ != that_width)
                {
                    *this->width_ = unknown_width();
                }
            }
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // alt_get_width
    //
    template<typename BidiIterT>
    inline std::size_t alt_get_width
    (
        std::vector<shared_ptr<matchable<BidiIterT> const> > const &alternates
      , state_type<BidiIterT> *state
    )
    {
        typedef alt_get_width_pred<BidiIterT> alt_get_width_pred;
        std::size_t width = alternates.front()->get_width(state);
        std::for_each(alternates.begin() + 1, alternates.end(), alt_get_width_pred(state, &width));
        return width;
    }

    template<typename BidiIterT, typename AlternatesT>
    inline std::size_t alt_get_width
    (
        fusion::sequence_base<AlternatesT> const &alternates
      , state_type<BidiIterT> *state
    )
    {
        typedef alt_get_width_pred<BidiIterT> alt_get_width_pred;
        std::size_t width = (*fusion::begin(alternates.cast())).get_width(state);
        fusion::for_each
        (
            make_range(fusion::next(fusion::begin(alternates.cast())), fusion::end(alternates.cast()))
          , alt_get_width_pred(state, &width)
        );
        return width;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // alternate_matcher
    //
    template<typename AlternatesT, typename TraitsT>
    struct alternate_matcher
      : quant_style_auto<width_of<AlternatesT>, is_pure<AlternatesT> >
    {
        typedef AlternatesT alternates_type;
        typedef typename TraitsT::char_type char_type;

        AlternatesT alternates_;
        mutable hash_peek_bitset<char_type> bset_;

        explicit alternate_matcher(AlternatesT const &alternates = AlternatesT())
          : alternates_(alternates)
          , bset_()
        {
        }

        template<typename BidiIterT, typename NextT>
        bool match(state_type<BidiIterT> &state, NextT const &next) const
        {
            if(!this->can_match_(*state.cur_, traits_cast<TraitsT>(state)))
            {
                return false;
            }

            return detail::alt_match(this->alternates_, state, next);
        }

        template<typename BidiIterT>
        std::size_t get_width(state_type<BidiIterT> *state) const
        {
            return detail::alt_get_width(this->alternates_, state);
        }

    private:
        alternate_matcher &operator =(alternate_matcher const &);

        bool can_match_(char_type ch, TraitsT const &traits) const
        {
            return this->bset_.test(ch, traits);
        }
    };

}}}

#endif
