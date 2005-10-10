///////////////////////////////////////////////////////////////////////////////
// peeker.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_CORE_PEEKER_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_CORE_PEEKER_HPP_EAN_10_04_2005

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <string>
#include <typeinfo>
#include <boost/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/detail/core/matchers.hpp>
#include <boost/xpressive/detail/utility/hash_peek_bitset.hpp>
#include <boost/xpressive/detail/utility/never_true.hpp>

namespace boost { namespace xpressive { namespace detail
{

///////////////////////////////////////////////////////////////////////////////
// peek_next
//   tell whether or not to keep looking for a peek optimization
template<typename MatcherT>
struct peek_next 
    : mpl::equal_to<typename MatcherT::width, mpl::size_t<0> >
{
};

template<>
struct peek_next<mark_begin_matcher>
    : mpl::true_
{
};

template<>
struct peek_next<repeat_begin_matcher>
    : mpl::true_
{
};

///////////////////////////////////////////////////////////////////////////////
// xpression_peeker
//
template<typename CharT>
struct xpression_peeker
{
    template<typename TraitsT>
    explicit xpression_peeker(hash_peek_bitset<CharT> *bset, TraitsT const &traits)
      : bset_(bset)
      , str_(0)
      , str_icase_(false)
      , line_start_(false)
      , traits_(0)
      , traits_type_(0)
    {
        this->set_traits(traits);
    }

    ///////////////////////////////////////////////////////////////////////////////
    // accessors
    std::pair<std::basic_string<CharT> const *, bool> get_string() const
    {
        return std::make_pair(this->str_, this->str_icase_);
    }

    bool line_start() const
    {
        return this->line_start_;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // modifiers
    void fail(bool do_fail = true)
    {
        if(do_fail)
        {
            this->bset_->set_all();
        }
    }

    template<typename XprT>
    peek_next<XprT> peek(XprT const &)
    {
        this->fail(!peek_next<XprT>::value);
        return peek_next<XprT>();
    }

    template<typename TraitsT>
    mpl::true_ peek(assert_bol_matcher<TraitsT> const &)
    {
        this->line_start_ = true;
        return mpl::true_();
    }

    template<typename TraitsT, bool ICaseT>
    mpl::false_ peek(literal_matcher<TraitsT, ICaseT, false> const &xpr)
    {
        this->bset_->set_char(xpr.ch_, ICaseT, this->get_traits_<TraitsT>());
        return mpl::false_();
    }

    template<typename TraitsT, bool ICaseT>
    mpl::false_ peek(string_matcher<TraitsT, ICaseT> const &xpr)
    {
        this->bset_->set_char(xpr.str_[0], ICaseT, this->get_traits_<TraitsT>());
        this->str_ = &xpr.str_;
        this->str_icase_ = ICaseT;
        return mpl::false_();
    }

    template<typename AlternatesT, typename TraitsT>
    mpl::false_ peek(alternate_matcher<AlternatesT, TraitsT> const &xpr)
    {
        BOOST_ASSERT(0 != xpr.bset_.count());
        this->bset_->set_bitset(xpr.bset_);
        return mpl::false_();
    }

    template<typename TraitsT, bool ICaseT>
    mpl::false_ peek(posix_charset_matcher<TraitsT, ICaseT> const &xpr)
    {
        this->bset_->set_class(xpr.mask_, xpr.not_, ICaseT, this->get_traits_<TraitsT>());
        return mpl::false_();
    }

    template<typename DummyT = void>
    struct is_char_8bit : mpl::bool_<1 == sizeof(CharT)> {};

    template<bool ICaseT, typename TraitsT>
    typename enable_if<is_char_8bit<TraitsT>, mpl::false_>::type
    peek(charset_matcher<TraitsT, ICaseT, basic_chset<CharT> > const &xpr)
    {
        BOOST_ASSERT(0 != xpr.charset_.base().count());
        this->bset_->set_charset(xpr.charset_, ICaseT);
        return mpl::false_();
    }

    template<typename TraitsT, bool ICaseT>
    mpl::false_ peek(range_matcher<TraitsT, ICaseT> const &xpr)
    {
        this->bset_->set_range(xpr.ch_min_, xpr.ch_max_, xpr.not_, ICaseT, this->get_traits_<TraitsT>());
        return mpl::false_();
    }

    template<typename XprT, bool GreedyT>
    mpl::false_ peek(simple_repeat_matcher<XprT, GreedyT> const &xpr)
    {
        0 != xpr.min_ ? xpr.xpr_.peek(*this) : this->fail(); // could be a union of xpr and next
        return mpl::false_();
    }

    template<typename TraitsT>
    void set_traits(TraitsT const &traits)
    {
        if(0 == this->traits_)
        {
            this->traits_ = &traits;
            this->traits_type_ = &typeid(TraitsT);
        }
        else if(*this->traits_type_ != typeid(TraitsT) || this->get_traits_<TraitsT>() != traits)
        {
            this->fail(); // traits mis-match! set all and bail
        }
    }

private:

    template<typename TraitsT>
    TraitsT const &get_traits_() const
    {
        BOOST_ASSERT(!!(*this->traits_type_ == typeid(TraitsT)));
        return *static_cast<TraitsT const *>(this->traits_);
    }

    hash_peek_bitset<CharT> *bset_;
    std::basic_string<CharT> const *str_;
    bool str_icase_;
    bool line_start_;
    void const *traits_;
    std::type_info const *traits_type_;
};

}}} // namespace boost::xpressive::detail

#endif
