///////////////////////////////////////////////////////////////////////////////
// detail_fwd.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_DETAIL_FWD_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_DETAIL_FWD_HPP_EAN_10_04_2005

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <climits> // for INT_MAX
#include <boost/mpl/bool.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/xpressive/xpressive_fwd.hpp>

namespace boost { namespace xpressive { namespace detail
{
    typedef unsigned int uint_t;

    template<uint_t MinT, uint_t MaxT>
    struct generic_quant_tag;

    struct modifier_tag;

    typedef mpl::size_t<INT_MAX / 2 - 1> unknown_width;

    ///////////////////////////////////////////////////////////////////////////////
    // placeholders
    //
    template<typename CharT, bool NotT = false>
    struct literal_placeholder;

    template<typename CharT>
    struct string_placeholder;

    struct mark_placeholder;

    template<typename BidiIterT, bool ByRefT>
    struct regex_placeholder;

    struct posix_charset_placeholder;

    template<typename CondT>
    struct assert_word_placeholder;

    template<typename CharT>
    struct range_placeholder;

    struct assert_bol_placeholder;

    struct assert_eol_placeholder;

    struct logical_newline_placeholder;

    struct self_placeholder;

    ///////////////////////////////////////////////////////////////////////////////
    // matchers
    //
    struct end_matcher;

    struct assert_bos_matcher;

    struct assert_eos_matcher;

    template<typename TraitsT>
    struct assert_bol_matcher;

    template<typename TraitsT>
    struct assert_eol_matcher;

    template<typename CondT, typename TraitsT>
    struct assert_word_matcher;

    struct true_matcher;

    template<typename AlternatesT, typename TraitsT>
    struct alternate_matcher;

    struct alternate_end_matcher;

    template<typename TraitsT, bool ICaseT>
    struct posix_charset_matcher;

    template<typename BidiIterT>
    struct alternates_factory;

    template<typename BidiIterT>
    struct sequence;

    template<typename TraitsT, bool ICaseT>
    struct mark_matcher;

    struct mark_begin_matcher;

    struct mark_end_matcher;

    template<typename BidiIterT>
    struct regex_matcher;

    template<typename BidiIterT>
    struct regex_byref_matcher;

    template<typename TraitsT>
    struct compound_charset;

    template<typename TraitsT, bool ICaseT, typename CharSetT = compound_charset<TraitsT> >
    struct charset_matcher;

    template<typename TraitsT, bool ICaseT>
    struct range_matcher;

    template<typename TraitsT, int SizeT>
    struct set_matcher;

    template<typename XprT, bool GreedyT>
    struct simple_repeat_matcher;

    struct repeat_begin_matcher;

    template<bool GreedyT>
    struct repeat_end_matcher;

    template<typename TraitsT, bool ICaseT, bool NotT>
    struct literal_matcher;

    template<typename TraitsT, bool ICaseT>
    struct string_matcher;

    template<typename ActionT>
    struct action_matcher;

    template<typename XprT>
    struct as_xpr_type;

    template<typename XprT>
    struct is_modifiable;

    template<typename AlternatesT>
    struct alternates_list;

    template<typename ModifierT>
    struct modifier_op;

    template<typename LeftT, typename RightT>
    struct modifier_sequencer;

    struct icase_modifier;

    template<typename BidiIterT, typename ICaseT, typename TraitsT>
    struct xpression_visitor;

    template<typename BidiIterT>
    struct regex_impl;

    template<typename BidiIterT>
    struct regex_matcher;

    struct epsilon_matcher;

    typedef proto::unary_op<epsilon_matcher, proto::noop_tag> epsilon_type;

    template<typename BidiIterT>
    struct nested_results;

    template<typename BidiIterT>
    struct regex_id_filter_predicate;

    template<typename XprT>
    struct keeper_matcher;

    template<typename XprT>
    struct lookahead_matcher;

    template<typename XprT>
    struct lookbehind_matcher;

    template<typename CondT>
    struct assert_word_placeholder;

    template<bool IsBoundaryT>
    struct word_boundary;

    template<typename BidiIterT, typename MatcherT>
    sequence<BidiIterT> make_dynamic_xpression(MatcherT const &matcher);

    template<typename CharT>
    struct xpression_linker;

    template<typename CharT>
    struct xpression_peeker;

    typedef proto::unary_op<mark_placeholder, proto::noop_tag> mark_tag;

    struct any_matcher;

    template<typename TraitsT>
    struct logical_newline_matcher;

    typedef proto::unary_op<logical_newline_placeholder, proto::noop_tag> logical_newline_xpression;

    struct set_initializer;

    typedef proto::unary_op<set_initializer, proto::noop_tag> set_initializer_type;

    struct seq_tag;

    template<bool PositiveT>
    struct lookahead_tag;

    template<bool PositiveT>
    struct lookbehind_tag;

    struct keeper_tag;

    template<typename LocaleT>
    struct locale_modifier;

    template<typename MatcherT>
    struct matcher_wrapper;

    template<typename LocaleT, typename BidiIterT>
    struct regex_traits_type;

    ///////////////////////////////////////////////////////////////////////////////
    // Misc.
    struct no_next;

    template<typename BidiIterT>
    struct core_access;

    template<typename BidiIterT>
    struct state_type;

    template<typename BidiIterT>
    struct matchable;

    template<typename MatcherT, typename BidiIterT>
    struct dynamic_xpression;

    template<typename MatcherT, typename NextT>
    struct static_xpression;

    typedef static_xpression<end_matcher, no_next> end_xpression;

    typedef static_xpression<alternate_end_matcher, no_next> alternate_end_xpression;

    typedef static_xpression<true_matcher, no_next> true_xpression;

    template<typename MatcherT, typename NextT = end_xpression>
    struct static_xpression;

    template<typename TopT, typename NextT>
    struct stacked_xpression;

    template<typename XprT>
    struct is_static_xpression;

    template<typename BidiIterT>
    struct sub_match_impl;

    template<typename BidiIterT>
    struct results_cache;

    template<typename T>
    struct sequence_stack;

    template<typename BidiIterT>
    struct results_extras;

    template<typename BidiIterT>
    struct match_context;

    template<typename BidiIterT>
    struct sub_match_vector;

    struct action_state;

    template<typename TraitsT, typename BidiIterT>
    TraitsT const &traits_cast(state_type<BidiIterT> const &state);

    template<typename CharT>
    struct basic_chset;

    template<typename BidiIterT>
    struct memento;

    template<typename CharT, typename TraitsT>
    void set_char(compound_charset<TraitsT> &chset, CharT ch, TraitsT const &traits, bool icase);

    template<typename CharT, typename TraitsT>
    void set_range(compound_charset<TraitsT> &chset, CharT from, CharT to, TraitsT const &traits, bool icase);

    template<typename TraitsT>
    void set_class(compound_charset<TraitsT> &chset, typename TraitsT::char_class_type char_class, bool no, TraitsT const &traits, bool icase);

    template<typename CharT, typename TraitsT>
    void set_char(basic_chset<CharT> &chset, CharT ch, TraitsT const &traits, bool icase);

    template<typename CharT, typename TraitsT>
    void set_range(basic_chset<CharT> &chset, CharT from, CharT to, TraitsT const &traits, bool icase);

    template<typename CharT, typename TraitsT>
    void set_class(basic_chset<CharT> &chset, typename TraitsT::char_class_type char_class, bool no, TraitsT const &traits, bool icase);

}}} // namespace boost::xpressive::detail

/// INTERNAL ONLY
namespace boost { namespace xpressive
{

    /// INTERNAL ONLY
    template<typename TraitsT, std::size_t N>
    typename TraitsT::char_class_type
    lookup_classname(TraitsT const &traits, char const (&cname)[N], bool icase = false);

}} // namespace boost::xpressive

#endif
