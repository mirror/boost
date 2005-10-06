///////////////////////////////////////////////////////////////////////////////
// accesss.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_CORE_ACCESS_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_CORE_ACCESS_HPP_EAN_10_04_2005

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <vector>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/detail/dynamic/matchable.hpp>

namespace boost { namespace xpressive { namespace detail
{

///////////////////////////////////////////////////////////////////////////////
// core_access
//
template<typename BidiIterT>
struct core_access
{
    // BUGBUG give basic_regex move semantics!
    static basic_regex<BidiIterT> make_regex(regex_impl<BidiIterT> const &impl)
    {
        return basic_regex<BidiIterT>(impl);
    }

    static std::size_t get_hidden_mark_count(basic_regex<BidiIterT> const &rex)
    {
        return rex.impl_->hidden_mark_count_;
    }

    static bool invalid(basic_regex<BidiIterT> const &rex)
    {
        return rex.invalid_();
    }

    static bool match(basic_regex<BidiIterT> const &rex, state_type<BidiIterT> &state)
    {
        return rex.match_(state);
    }

    static shared_ptr<detail::regex_impl<BidiIterT> > const &
    get_regex_impl(basic_regex<BidiIterT> const &rex)
    {
        return rex.impl_.get();
    }

    static void init_sub_match_vector
    (
        sub_match_vector<BidiIterT> &subs_vect
      , sub_match_impl<BidiIterT> *subs_ptr
      , std::size_t size
    )
    {
        subs_vect.init_(subs_ptr, size);
    }

    static void init_sub_match_vector
    (
        sub_match_vector<BidiIterT> &subs_vect
      , sub_match_impl<BidiIterT> *subs_ptr
      , std::size_t size
      , sub_match_vector<BidiIterT> const &that
    )
    {
        subs_vect.init_(subs_ptr, size, that);
    }

    static void init_match_results
    (
        match_results<BidiIterT> &what
      , regex_id_type regex_id
      , sub_match_impl<BidiIterT> *sub_matches
      , std::size_t size
    )
    {
        what.init_(regex_id, sub_matches, size);
    }

    static sub_match_vector<BidiIterT> &get_sub_match_vector(match_results<BidiIterT> &what)
    {
        return what.sub_matches_;
    }

    static sub_match_impl<BidiIterT> *get_sub_matches(sub_match_vector<BidiIterT> &subs)
    {
        return subs.sub_matches_;
    }

    static results_extras<BidiIterT> &get_extras(match_results<BidiIterT> &what)
    {
        return what.get_extras_();
    }

    static nested_results<BidiIterT> &get_nested_results(match_results<BidiIterT> &what)
    {
        return what.nested_results_;
    }

    static action_state &get_action_state(match_results<BidiIterT> &what)
    {
        return what.action_state_;
    }

    static void set_prefix_suffix(match_results<BidiIterT> &what, BidiIterT begin, BidiIterT end)
    {
        what.set_prefix_suffix_(begin, end);
    }

    static void reset(match_results<BidiIterT> &what)
    {
        what.reset_();
    }

    static void set_base(match_results<BidiIterT> &what, BidiIterT base)
    {
        what.set_base_(base);
    }
};

}}} // namespace boost::xpressive::detail

#endif
