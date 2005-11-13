///////////////////////////////////////////////////////////////////////////////
// static.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_STATIC_STATIC_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_STATIC_STATIC_HPP_EAN_10_04_2005

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/mpl/assert.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/detail/core/state.hpp>
#include <boost/xpressive/detail/core/linker.hpp>
#include <boost/xpressive/detail/core/peeker.hpp>

//  Random thoughts:
//  set[ a + b - c ]
//  set[ a ] + set[ b ] - set[ c ]
//  -set[ a + b + c ] (set negation)
//  must support indirect repeat counts {$n,$m}
//  must support logical newline and intelligent negation of logical newline
//  add ws to eat whitespace (make *_ws illegal)
//  a{n}      -> a[n]
//  a{n,m}    -> a[n][m]
//  a{n,m}?   -> -a[n][m] // yuk, breaks quantifier up.
//  a{n,m}    -> repeat<n,m>(a)
//  a{$n,$m}  -> repeat(n,m)(a)
//  add nil to match nothing

//
// instead of s1, s2, etc., how about s[1], s[2], etc.? Needlessly verbose?
//

namespace boost { namespace xpressive { namespace detail
{

#ifdef BOOST_XPR_DEBUG_STACK
///////////////////////////////////////////////////////////////////////////////
// top_type
//
template<typename TopT>
struct top_type
{
    typedef TopT type;
};

///////////////////////////////////////////////////////////////////////////////
// top_type
//
template<typename TopT, typename NextT>
struct top_type<stacked_xpression<TopT, NextT> >
{
    typedef NextT type;
};
#endif

///////////////////////////////////////////////////////////////////////////////
// stacked_xpression
//
template<typename TopT, typename NextT>
struct stacked_xpression
  : NextT
{
    // match
    //  delegates to NextT
    template<typename BidiIterT>
    bool match(state_type<BidiIterT> &state) const
    {
        return static_cast<NextT const *>(this)->
            BOOST_NESTED_TEMPLATE push_match<TopT>(state);
    }

    // top_match
    //   jump back to the xpression on top of the xpression stack,
    //   and keep the xpression on the stack.
    template<typename BidiIterT>
    static bool top_match(state_type<BidiIterT> &state, xpression_base const *top)
    {
        BOOST_XPR_DEBUG_STACK_ASSERT(typeid(*top) == typeid(typename top_type<TopT>::type));
        return static_cast<TopT const *>(top)->
            BOOST_NESTED_TEMPLATE push_match<TopT>(state);
    }

    // pop_match
    //   jump back to the xpression on top of the xpression stack,
    //   pop the xpression off the stack.
    template<typename BidiIterT>
    static bool pop_match(state_type<BidiIterT> &state, xpression_base const *top)
    {
        BOOST_XPR_DEBUG_STACK_ASSERT(typeid(*top) == typeid(typename top_type<TopT>::type));
        return static_cast<TopT const *>(top)->match(state);
    }

    // skip_match
    //   pop the xpression off the top of the stack and ignore it; call
    //   match on next.
    template<typename BidiIterT>
    bool skip_match(state_type<BidiIterT> &state) const
    {
        // could be static_xpression::skip_impl or stacked_xpression::skip_impl
        // depending on if there is 1 or more than 1 xpression on the
        // xpression stack
        return TopT::skip_impl(*static_cast<NextT const *>(this), state);
    }

//protected:

    // skip_impl
    //   implementation of skip_match.
    template<typename ThatT, typename BidiIterT>
    static bool skip_impl(ThatT const &that, state_type<BidiIterT> &state)
    {
        return that.BOOST_NESTED_TEMPLATE push_match<TopT>(state);
    }
};

///////////////////////////////////////////////////////////////////////////////
// stacked_xpression_cast
//
template<typename TopT, typename NextT>
inline stacked_xpression<TopT, NextT> const &stacked_xpression_cast(NextT const &next)
{
    // NOTE: this is a little white lie. The "next" object doesn't really have
    // the type to which we're casting it. It is harmless, though. We are only using
    // the cast to decorate the next object with type information. It is done
    // this way to save stack space.
    BOOST_MPL_ASSERT_RELATION(sizeof(stacked_xpression<TopT, NextT>), ==, sizeof(NextT));
    return *static_cast<stacked_xpression<TopT, NextT> const *>(&next);
}

///////////////////////////////////////////////////////////////////////////////
// static_xpression
//
template<typename MatcherT, typename NextT>
struct static_xpression
  : MatcherT
{
    NextT next_;

    static_xpression(MatcherT const &matcher = MatcherT(), NextT const &next = NextT())
      : MatcherT(matcher)
      , next_(next)
    {
    }

    // match
    //  delegates to the MatcherT
    template<typename BidiIterT>
    bool match(state_type<BidiIterT> &state) const
    {
        return this->MatcherT::match(state, this->next_);
    }

    // push_match
    //   call match on this, but also push "TopT" onto the xpression
    //   stack so we know what we are jumping back to later.
    template<typename TopT, typename BidiIterT>
    bool push_match(state_type<BidiIterT> &state) const
    {
        return this->MatcherT::match(state, stacked_xpression_cast<TopT>(this->next_));
    }

    // skip_impl
    //   implementation of skip_match, called from stacked_xpression::skip_match
    template<typename ThatT, typename BidiIterT>
    static bool skip_impl(ThatT const &that, state_type<BidiIterT> &state)
    {
        return that.match(state);
    }

    // for linking a compiled regular xpression
    template<typename CharT>
    void link(xpression_linker<CharT> &linker) const
    {
        linker.link(*static_cast<MatcherT const *>(this), &this->next_);
        this->next_.link(linker);
    }

    // for building a lead-follow
    template<typename CharT>
    void peek(xpression_peeker<CharT> &peeker) const
    {
        this->peek_next_(peeker.peek(*static_cast<MatcherT const *>(this)), peeker);
    }

    // for getting xpression width
    template<typename BidiIterT>
    std::size_t get_width(state_type<BidiIterT> *state) const
    {
        // BUGBUG this gets called from the simple_repeat_matcher::match(), so this is slow.
        // or will the compiler be able to optimize this all away?
        std::size_t this_width = this->MatcherT::get_width(state);
        if(this_width == unknown_width())
            return unknown_width();
        std::size_t that_width = this->next_.get_width(state);
        if(that_width == unknown_width())
            return unknown_width();
        return this_width + that_width;
    }

private: // hide this

    static_xpression &operator =(static_xpression const &);

    template<typename CharT>
    void peek_next_(mpl::true_, xpression_peeker<CharT> &peeker) const
    {
        this->next_.peek(peeker);
    }

    template<typename CharT>
    static void peek_next_(mpl::false_, xpression_peeker<CharT> &)
    {
        // no-op
    }

    using MatcherT::width;
    using MatcherT::pure;
};

// syntactic sugar so this xpression can be treated the same as
// (a smart pointer to) a dynamic xpression from templates
template<typename MatcherT, typename NextT>
inline static_xpression<MatcherT, NextT> const *
get_pointer(static_xpression<MatcherT, NextT> const &xpr)
{
	return &xpr;
}

///////////////////////////////////////////////////////////////////////////////
// make_static_xpression
//
template<typename MatcherT>
inline static_xpression<MatcherT> const
make_static_xpression(MatcherT const &matcher)
{
    return static_xpression<MatcherT>(matcher);
}

template<typename MatcherT, typename NextT>
inline static_xpression<MatcherT, NextT> const
make_static_xpression(MatcherT const &matcher, NextT const &next)
{
    return static_xpression<MatcherT, NextT>(matcher, next);
}

///////////////////////////////////////////////////////////////////////////////
// no_next
//
struct no_next
  : xpression_base
{
    template<typename CharT>
    void link(xpression_linker<CharT> &) const
    {
    }

    template<typename CharT>
    void peek(xpression_peeker<CharT> &peeker) const
    {
        peeker.fail();
    }

    template<typename BidiIterT>
    static std::size_t get_width(state_type<BidiIterT> *)
    {
        return 0;
    }
};

///////////////////////////////////////////////////////////////////////////////
// alternates_list
//
template<typename AlternatesT>
struct alternates_list
  : AlternatesT
{
    alternates_list(AlternatesT const &alternates)
      : AlternatesT(alternates)
    {
    }
private:
    alternates_list &operator =(alternates_list const &);
};

}}} // namespace boost::xpressive::detail

#endif
