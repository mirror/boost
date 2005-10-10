///////////////////////////////////////////////////////////////////////////////
// linker.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_CORE_LINKER_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_CORE_LINKER_HPP_EAN_10_04_2005

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <stack>
#include <limits>
#include <boost/shared_ptr.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/spirit/fusion/algorithm/for_each.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/detail/dynamic/matchable.hpp>
#include <boost/xpressive/detail/core/matchers.hpp>
#include <boost/xpressive/detail/core/peeker.hpp>
#include <boost/xpressive/detail/utility/never_true.hpp>

namespace boost { namespace xpressive { namespace detail
{

///////////////////////////////////////////////////////////////////////////////
// icase_modifier
//
//   wrapped by the modifier<> template and inserted into the xpression
//   template with the icase() helper function. icase_modifier morphs
//   a case-sensitive visitor into a case-insensitive visitor, which
//   causes all matchers visited to become case-insensitive.
//
struct icase_modifier
{
    template<typename VisitorT>
    struct apply;

    template<typename BidiIterT, typename ICaseT, typename TraitsT>
    struct apply<xpression_visitor<BidiIterT, ICaseT, TraitsT> >
    {
        typedef xpression_visitor<BidiIterT, mpl::true_, TraitsT> type;
    };

    template<typename VisitorT>
    static typename apply<VisitorT>::type
    call(VisitorT &visitor)
    {
        return typename apply<VisitorT>::type(visitor.traits(), visitor.self());
    }
};

///////////////////////////////////////////////////////////////////////////////
// regex_traits_type : wrap a locale in the appropriate regex_traits
//
template<typename LocaleT, typename BidiIterT>
struct regex_traits_type
{
#ifndef BOOST_NO_STD_LOCALE

    typedef typename iterator_value<BidiIterT>::type char_type;

    // if LocaleT is std::locale, wrap it in a cpp_regex_traits<CharT>
    typedef typename mpl::if_
    <
        is_same<LocaleT, std::locale>
      , cpp_regex_traits<char_type>
      , LocaleT
    >::type type;

#else

    typedef LocaleT type;

#endif
};

///////////////////////////////////////////////////////////////////////////////
// locale_modifier
//
//   wrapped by the modifier<> template and inserted into the xpression
//   template with the imbue() helper function. Causes a sub-xpression to
//   use the specified LocaleT
//
template<typename LocaleT>
struct locale_modifier
{
    locale_modifier(LocaleT const &loc)
      : loc_(loc)
    {
    }

    template<typename VisitorT>
    struct apply;

    template<typename BidiIterT, typename ICaseT, typename OtherTraitsT>
    struct apply<xpression_visitor<BidiIterT, ICaseT, OtherTraitsT> >
    {
        typedef typename regex_traits_type<LocaleT, BidiIterT>::type traits_type;
        typedef xpression_visitor<BidiIterT, ICaseT, traits_type> type;
    };

    template<typename VisitorT>
    typename apply<VisitorT>::type
    call(VisitorT &) const
    {
        return typename apply<VisitorT>::type(this->loc_);
    }

    LocaleT getloc() const
    {
        return this->loc_;
    }

private:
    LocaleT loc_;
};

///////////////////////////////////////////////////////////////////////////////
// xpression_linker
//
template<typename CharT>
struct xpression_linker
{
    template<typename TraitsT>
    explicit xpression_linker(TraitsT const &traits)
      : back_stack_()
      , traits_(&traits)
      , traits_type_(&typeid(TraitsT))
    {
    }

    template<typename MatcherT>
    void link(MatcherT const &, xpression_base const *)
    {
        // no-op
    }

    void link(repeat_begin_matcher const &, xpression_base const *next)
    {
        this->back_stack_.push(next);
    }

    template<bool GreedyT>
    void link(repeat_end_matcher<GreedyT> const &matcher, xpression_base const *)
    {
        matcher.back_ = this->back_stack_.top();
        this->back_stack_.pop();
    }

    template<typename AlternatesT, typename TraitsT>
    void link(alternate_matcher<AlternatesT, TraitsT> const &matcher, xpression_base const *next)
    {
        xpression_peeker<CharT> peeker(&matcher.bset_, this->get_traits<TraitsT>());
        this->alt_link(matcher.alternates_, next, peeker);
    }

    void link(alternate_end_matcher const &matcher, xpression_base const *)
    {
        matcher.back_ = this->back_stack_.top();
        this->back_stack_.pop();
    }

    template<typename XprT>
    void link(keeper_matcher<XprT> const &matcher, xpression_base const *)
    {
        get_pointer(matcher.xpr_)->link(*this);
    }

    template<typename XprT>
    void link(lookahead_matcher<XprT> const &matcher, xpression_base const *)
    {
        get_pointer(matcher.xpr_)->link(*this);
    }

    template<typename XprT>
    void link(lookbehind_matcher<XprT> const &matcher, xpression_base const *)
    {
        get_pointer(matcher.xpr_)->link(*this);
    }

    template<typename XprT, bool GreedyT>
    void link(simple_repeat_matcher<XprT, GreedyT> const &matcher, xpression_base const *)
    {
        matcher.xpr_.link(*this);
    }

private:

    ///////////////////////////////////////////////////////////////////////////////
    // alt_link_pred
    //
    struct alt_link_pred
    {
        xpression_linker<CharT> &linker_;
        xpression_peeker<CharT> &peeker_;
        xpression_base const *next_;

        alt_link_pred
        (
            xpression_linker<CharT> &linker
          , xpression_peeker<CharT> &peeker
          , xpression_base const *next
        )
          : linker_(linker)
          , peeker_(peeker)
          , next_(next)
        {
        }

        template<typename XprT>
        void operator ()(XprT const &xpr) const
        {
            this->linker_.back_stack_.push(this->next_);
            get_pointer(xpr)->link(this->linker_);
            get_pointer(xpr)->peek(this->peeker_);
        }

    private:
        alt_link_pred &operator =(alt_link_pred const &);
    };

    template<typename BidiIterT>
    void alt_link
    (
        std::vector<shared_ptr<matchable<BidiIterT> const> > const &alternates
      , xpression_base const *next
      , xpression_peeker<CharT> &peeker
    )
    {
        std::for_each(alternates.begin(), alternates.end(), alt_link_pred(*this, peeker, next));
    }

    template<typename AlternatesT>
    void alt_link
    (
        fusion::sequence_base<AlternatesT> const &alternates
      , xpression_base const *next
      , xpression_peeker<CharT> &peeker
    )
    {
        fusion::for_each(alternates.cast(), alt_link_pred(*this, peeker, next));
    }

    template<typename TraitsT>
    TraitsT const &get_traits() const
    {
        BOOST_ASSERT(*this->traits_type_ == typeid(TraitsT));
        return *static_cast<TraitsT const *>(this->traits_);
    }

    std::stack<xpression_base const *> back_stack_;
    void const *traits_;
    std::type_info const *traits_type_;
};

}}} // namespace boost::xpressive::detail

#endif
