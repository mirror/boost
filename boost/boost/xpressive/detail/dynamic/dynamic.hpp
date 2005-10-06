///////////////////////////////////////////////////////////////////////////////
// dynamic.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_DYNAMIC_DYNAMIC_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_DYNAMIC_DYNAMIC_HPP_EAN_10_04_2005

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <list>
#include <utility>
#include <algorithm>
#include <boost/assert.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/detail/core/quant_style.hpp>
#include <boost/xpressive/detail/dynamic/matchable.hpp>
#include <boost/xpressive/detail/core/icase.hpp>

namespace boost { namespace xpressive { namespace detail
{

///////////////////////////////////////////////////////////////////////////////
// invalid_xpression
//
template<typename BidiIterT>
struct invalid_xpression
  : matchable<BidiIterT>
{
    bool match(state_type<BidiIterT> &) const
    {
        BOOST_ASSERT(false);
        return false;
    }

    std::size_t get_width(state_type<BidiIterT> *) const
    {
        return 0;
    }

    static void noop(matchable<BidiIterT> const *)
    {
    }
};

///////////////////////////////////////////////////////////////////////////////
// get_invalid_xpression
//
template<typename BidiIterT>
inline shared_ptr<matchable<BidiIterT> const> const &get_invalid_xpression()
{
    static invalid_xpression<BidiIterT> const invalid_xpr;

    static shared_ptr<matchable<BidiIterT> const> const invalid_ptr
    (
        static_cast<matchable<BidiIterT> const *>(&invalid_xpr)
      , &invalid_xpression<BidiIterT>::noop
    );

    return invalid_ptr;
}

///////////////////////////////////////////////////////////////////////////////
// dynamic_xpression
//
template<typename MatcherT, typename BidiIterT>
struct dynamic_xpression
  : MatcherT
  , matchable<BidiIterT>
{
    typedef typename iterator_value<BidiIterT>::type char_type;

    shared_ptr<matchable<BidiIterT> const> next_;

    dynamic_xpression(MatcherT const &matcher = MatcherT())
      : MatcherT(matcher)
      , next_(get_invalid_xpression<BidiIterT>())
    {
    }

    bool match(state_type<BidiIterT> &state) const
    {
        return this->MatcherT::match(state, *this->next_);
    }

    std::size_t get_width(state_type<BidiIterT> *state) const
    {
        std::size_t this_width = this->MatcherT::get_width(state);
        if(this_width == unknown_width())
            return unknown_width();
        std::size_t that_width = this->next_->get_width(state);
        if(that_width == unknown_width())
            return unknown_width();
        return this_width + that_width;
    }

    void link(xpression_linker<char_type> &linker) const
    {
        linker.link(*static_cast<MatcherT const *>(this), this->next_.get());
        this->next_->link(linker);
    }

    void peek(xpression_peeker<char_type> &peeker) const
    {
        this->peek_next_(peeker.peek(*static_cast<MatcherT const *>(this)), peeker);
    }

    sequence<BidiIterT> quantify
    (
        quant_spec const &spec
      , std::size_t &hidden_mark_count
      , sequence<BidiIterT> seq
      , alternates_factory<BidiIterT> const &factory
    ) const
    {
        return this->quantify_(spec, hidden_mark_count, seq, quant_type<MatcherT>(), factory, this);
    }

    bool is_quantifiable() const
    {
        return quant_type<MatcherT>::value != (int)quant_none;
    }

private:

    void peek_next_(mpl::true_, xpression_peeker<char_type> &peeker) const
    {
        this->next_->peek(peeker);
    }

    void peek_next_(mpl::false_, xpression_peeker<char_type> &) const
    {
        // no-op
    }

    sequence<BidiIterT> quantify_
    (
        quant_spec const &
      , std::size_t &
      , sequence<BidiIterT>
      , mpl::int_<quant_none>
      , alternates_factory<BidiIterT> const &
      , void const *
    ) const;

    sequence<BidiIterT> quantify_
    (
        quant_spec const &
      , std::size_t &
      , sequence<BidiIterT>
      , mpl::int_<quant_fixed_width>
      , alternates_factory<BidiIterT> const &
      , void const *
    ) const;

    sequence<BidiIterT> quantify_
    (
        quant_spec const &
      , std::size_t &
      , sequence<BidiIterT>
      , mpl::int_<quant_variable_width>
      , alternates_factory<BidiIterT> const &
      , void const *
    ) const;

    sequence<BidiIterT> quantify_
    (
        quant_spec const &
      , std::size_t &
      , sequence<BidiIterT>
      , mpl::int_<quant_fixed_width>
      , alternates_factory<BidiIterT> const &
      , mark_begin_matcher const *
    ) const;
};

///////////////////////////////////////////////////////////////////////////////
// make_dynamic_xpression
//
template<typename BidiIterT, typename MatcherT>
inline sequence<BidiIterT> make_dynamic_xpression(MatcherT const &matcher)
{
    typedef dynamic_xpression<MatcherT, BidiIterT> xpression_type;
    std::auto_ptr<xpression_type> xpr(new xpression_type(matcher));

    sequence<BidiIterT> seq;
    seq.second = &xpr->next_;
    seq.first = xpr;

    return seq;
}

///////////////////////////////////////////////////////////////////////////////
// alternates_factory
//
template<typename BidiIterT>
struct alternates_factory
{
    typedef std::vector<shared_ptr<matchable<BidiIterT> const> > alternates_vector;

    virtual ~alternates_factory() {}

    virtual std::pair<sequence<BidiIterT>, alternates_vector *>
    operator ()() const = 0;
};

template<typename BidiIterT, typename TraitsT>
struct alternates_factory_impl
  : alternates_factory<BidiIterT>
{
    typedef typename alternates_factory<BidiIterT>::alternates_vector alternates_vector;

    std::pair<sequence<BidiIterT>, alternates_vector *>
    operator ()() const
    {
        typedef alternate_matcher<alternates_vector, TraitsT> alternate_matcher;
        typedef dynamic_xpression<alternate_matcher, BidiIterT> alternate_xpression;
        shared_ptr<alternate_xpression> alt_xpr(new alternate_xpression);
        sequence<BidiIterT> seq(alt_xpr, &alt_xpr->next_);
        return std::make_pair(seq, &alt_xpr->alternates_);
    }
};

///////////////////////////////////////////////////////////////////////////////
// alternates_to_matchable
//
template<typename BidiIterT>
inline sequence<BidiIterT> alternates_to_matchable
(
    std::list<sequence<BidiIterT> > const &alternates
  , alternates_factory<BidiIterT> const &factory
)
{
    BOOST_ASSERT(0 != alternates.size());

    // If there is only 1 alternate, just return it.
    if(1 == alternates.size())
    {
        return alternates.front();
    }

    typedef std::vector<shared_ptr<matchable<BidiIterT> const> > alternates_vector;
    std::pair<sequence<BidiIterT>, alternates_vector *> result = factory();

    // through the wonders of reference counting, all alternates can share an end_alternate
    typedef dynamic_xpression<alternate_end_matcher, BidiIterT> alternate_end_xpression;
    shared_ptr<alternate_end_xpression> end_alt_xpr(new alternate_end_xpression);

    // terminate each alternate with an alternate_end_matcher
    result.second->reserve(alternates.size());
    typedef std::list<sequence<BidiIterT> > alternates_list;
    typename alternates_list::const_iterator begin = alternates.begin(), end = alternates.end();
    for(; begin != end; ++begin)
    {
        if(!begin->is_empty())
        {
            result.second->push_back(begin->first);
            *begin->second = end_alt_xpr;
        }
        else
        {
            result.second->push_back(end_alt_xpr);
        }
    }

    return result.first;
}

///////////////////////////////////////////////////////////////////////////////
// matcher_wrapper
//
template<typename MatcherT>
struct matcher_wrapper
  : MatcherT
{
    matcher_wrapper(MatcherT const &matcher = MatcherT())
      : MatcherT(matcher)
    {
    }

    template<typename BidiIterT>
    bool match(state_type<BidiIterT> &state) const
    {
        return this->MatcherT::match(state, matcher_wrapper<true_matcher>());
    }

    template<typename CharT>
    void link(xpression_linker<CharT> &linker) const
    {
        linker.link(*static_cast<MatcherT const *>(this), 0);
    }

    template<typename CharT>
    void peek(xpression_peeker<CharT> &peeker) const
    {
        peeker.peek(*static_cast<MatcherT const *>(this));
    }
};

//////////////////////////////////////////////////////////////////////////
// dynamic_xpression::quantify_
//
//   unquantifiable
template<typename MatcherT, typename BidiIterT>
inline sequence<BidiIterT> dynamic_xpression<MatcherT, BidiIterT>::quantify_
(
    quant_spec const &
  , std::size_t &
  , sequence<BidiIterT>
  , mpl::int_<quant_none>
  , alternates_factory<BidiIterT> const &
  , void const *
) const
{
    BOOST_ASSERT(false); // should never get here
    throw regex_error(regex_constants::error_badrepeat, "expression cannot be quantified");
}

//   fixed-width matchers
template<typename MatcherT, typename BidiIterT>
inline sequence<BidiIterT> dynamic_xpression<MatcherT, BidiIterT>::quantify_
(
    quant_spec const &spec
  , std::size_t &hidden_mark_count
  , sequence<BidiIterT> seq
  , mpl::int_<quant_fixed_width>
  , alternates_factory<BidiIterT> const &factory
  , void const *
) const
{
    if(this->next_ != get_invalid_xpression<BidiIterT>())
    {
        return this->quantify_(spec, hidden_mark_count, seq, mpl::int_<quant_variable_width>(), factory, this);
    }

    typedef matcher_wrapper<MatcherT> xpr_type;

    if(spec.greedy_)
    {
        simple_repeat_matcher<xpr_type, true> quant(*this, spec.min_, spec.max_);
        return make_dynamic_xpression<BidiIterT>(quant);
    }
    else
    {
        simple_repeat_matcher<xpr_type, false> quant(*this, spec.min_, spec.max_);
        return make_dynamic_xpression<BidiIterT>(quant);
    }
}

//   variable-width, no mark
template<typename MatcherT, typename BidiIterT>
inline sequence<BidiIterT> dynamic_xpression<MatcherT, BidiIterT>::quantify_
(
    quant_spec const &spec
  , std::size_t &hidden_mark_count
  , sequence<BidiIterT> seq
  , mpl::int_<quant_variable_width>
  , alternates_factory<BidiIterT> const &factory
  , void const *
) const
{
    // create a hidden mark so this expression can be quantified
    int mark_nbr = -static_cast<int>(++hidden_mark_count);
    mark_begin_matcher mark_begin(mark_nbr);
    mark_end_matcher mark_end(mark_nbr);
    sequence<BidiIterT> new_seq = make_dynamic_xpression<BidiIterT>(mark_begin);
    new_seq += seq;
    new_seq += make_dynamic_xpression<BidiIterT>(mark_end);
    return new_seq.first->quantify(spec, hidden_mark_count, new_seq, factory);
}

//   variable-width with mark
template<typename MatcherT, typename BidiIterT>
inline sequence<BidiIterT> dynamic_xpression<MatcherT, BidiIterT>::quantify_
(
    quant_spec const &spec
  , std::size_t &
  , sequence<BidiIterT> seq
  , mpl::int_<quant_fixed_width>
  , alternates_factory<BidiIterT> const &factory
  , mark_begin_matcher const *
) const
{
    BOOST_ASSERT(spec.max_); // we should never get here if max is 0

    // only bother creating a quantifier if max is greater than one
    if(1 < spec.max_)
    {
        int mark_number = this->mark_number_;
        unsigned int min = spec.min_ ? spec.min_ : 1U;
        detail::sequence<BidiIterT> seq_quant;
        // TODO: statically bind the repeat_begin_matcher to the mark_begin for better perf
        seq_quant += make_dynamic_xpression<BidiIterT>(repeat_begin_matcher(mark_number));
        // TODO: statically bind the mark_end to the quantifier_end for better perf
        if(spec.greedy_)
        {
            repeat_end_matcher<true> end_quant(mark_number, min, spec.max_);
            seq += make_dynamic_xpression<BidiIterT>(end_quant);
        }
        else
        {
            repeat_end_matcher<false> end_quant(mark_number, min, spec.max_);
            seq += make_dynamic_xpression<BidiIterT>(end_quant);
        }
        seq_quant += seq;
        seq = seq_quant;
    }

    // if min is 0, the quant must be made alternate with an empty matcher.
    if(0 == spec.min_)
    {
        std::list<sequence<BidiIterT> > alts(2);
        (spec.greedy_ ? alts.front() : alts.back()) = seq;
        seq = alternates_to_matchable(alts, factory);
    }

    return seq;
}

}}} // namespace boost::xpressive::detail

#endif
