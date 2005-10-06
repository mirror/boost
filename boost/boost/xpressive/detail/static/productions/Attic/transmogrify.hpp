///////////////////////////////////////////////////////////////////////////////
// transmogrify.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_STATIC_PRODUCTIONS_TRANSMOGRIFY_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_STATIC_PRODUCTIONS_TRANSMOGRIFY_HPP_EAN_10_04_2005

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/mpl/if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/detail/core/matchers.hpp>
#include <boost/xpressive/detail/static/placeholders.hpp>
#include <boost/xpressive/detail/utility/dont_care.hpp>
#include <boost/xpressive/detail/utility/traits_utils.hpp>

namespace boost { namespace xpressive { namespace detail
{
    ///////////////////////////////////////////////////////////////////////////////
    // transmogrify
    //
    template<typename BidiIterT, typename ICaseT, typename TraitsT, typename MatcherT>
    struct transmogrify
    {
        typedef MatcherT type;

        static type const &call(MatcherT const &m, dont_care)
        {
            return m;
        }
    };

    template<typename BidiIterT, typename ICaseT, typename TraitsT>
    struct transmogrify<BidiIterT, ICaseT, TraitsT, assert_bol_placeholder>
    {
        typedef assert_bol_matcher<TraitsT> type;

        template<typename VisitorT>
        static type call(assert_bol_placeholder, VisitorT &visitor)
        {
            return type(visitor.traits());
        }
    };

    template<typename BidiIterT, typename ICaseT, typename TraitsT>
    struct transmogrify<BidiIterT, ICaseT, TraitsT, assert_eol_placeholder>
    {
        typedef assert_eol_matcher<TraitsT> type;

        template<typename VisitorT>
        static type call(assert_eol_placeholder, VisitorT &visitor)
        {
            return type(visitor.traits());
        }
    };

    template<typename BidiIterT, typename ICaseT, typename TraitsT>
    struct transmogrify<BidiIterT, ICaseT, TraitsT, logical_newline_placeholder>
    {
        typedef logical_newline_matcher<TraitsT> type;

        template<typename VisitorT>
        static type call(logical_newline_placeholder, VisitorT &visitor)
        {
            return type(visitor.traits());
        }
    };

    template<typename BidiIterT, typename ICaseT, typename TraitsT, typename CharT, bool NotT>
    struct transmogrify<BidiIterT, ICaseT, TraitsT, literal_placeholder<CharT, NotT> >
    {
        typedef typename iterator_value<BidiIterT>::type char_type;
        typedef literal_matcher<TraitsT, ICaseT::value, NotT> type;

        template<typename VisitorT>
        static type call(literal_placeholder<CharT, NotT> const &m, VisitorT &visitor)
        {
            char_type ch = char_cast<char_type>(m.ch_, visitor.traits());
            return type(ch, visitor.traits());
        }
    };

    template<typename BidiIterT, typename ICaseT, typename TraitsT, typename CharT>
    struct transmogrify<BidiIterT, ICaseT, TraitsT, range_placeholder<CharT> >
    {
        // By design, we don't widen character ranges.
        typedef typename iterator_value<BidiIterT>::type char_type;
        BOOST_MPL_ASSERT((is_same<CharT, char_type>));
        typedef range_matcher<TraitsT, ICaseT::value> type;

        template<typename VisitorT>
        static type call(range_placeholder<CharT> const &m, VisitorT &visitor)
        {
            return type(m.ch_min_, m.ch_max_, m.not_, visitor.traits());
        }
    };

    template<typename BidiIterT, typename ICaseT, typename TraitsT, typename CharT>
    struct transmogrify<BidiIterT, ICaseT, TraitsT, string_placeholder<CharT> >
    {
        typedef typename iterator_value<BidiIterT>::type char_type;
        typedef string_matcher<TraitsT, ICaseT::value> type;

        template<typename VisitorT>
        static type call(string_placeholder<CharT> const &m, VisitorT &visitor)
        {
            return type(string_cast<char_type>(m.str_, visitor.traits()), visitor.traits());
        }
    };

    template<typename BidiIterT, typename ICaseT, typename TraitsT>
    struct transmogrify<BidiIterT, ICaseT, TraitsT, mark_placeholder>
    {
        typedef mark_matcher<TraitsT, ICaseT::value> type;

        template<typename VisitorT>
        static type call(mark_placeholder const &m, VisitorT &visitor)
        {
            return type(m.mark_number_, visitor.traits());
        }
    };

    template<typename BidiIterT, typename ICaseT, typename TraitsT>
    struct transmogrify<BidiIterT, ICaseT, TraitsT, posix_charset_placeholder>
    {
        typedef posix_charset_matcher<TraitsT, ICaseT::value> type;

        template<typename VisitorT>
        static type call(posix_charset_placeholder const &m, VisitorT &visitor)
        {
            char const *name_end = m.name_ + std::strlen(m.name_);
            return type(visitor.traits().lookup_classname(m.name_, name_end, ICaseT::value), m.not_);
        }
    };

    template<typename BidiIterT, typename TraitsT, int SizeT>
    struct transmogrify<BidiIterT, mpl::true_, TraitsT, set_matcher<TraitsT, SizeT> >
    {
        typedef set_matcher<TraitsT, SizeT> type;

        template<typename VisitorT>
        static type call(set_matcher<TraitsT, SizeT> m, VisitorT &visitor)
        {
            m.nocase(visitor.traits());
            return m;
        }
    };

    template<typename BidiIterT, typename ICaseT, typename TraitsT, typename CondT>
    struct transmogrify<BidiIterT, ICaseT, TraitsT, assert_word_placeholder<CondT> >
    {
        typedef assert_word_matcher<CondT, TraitsT> type;

        template<typename VisitorT>
        static type call(dont_care, VisitorT &visitor)
        {
            return type(visitor.traits());
        }
    };

    template<typename BidiIterT, typename ICaseT, typename TraitsT, bool ByRefT>
    struct transmogrify<BidiIterT, ICaseT, TraitsT, regex_placeholder<BidiIterT, ByRefT> >
    {
        typedef typename mpl::if_c
        <
            ByRefT
          , regex_byref_matcher<BidiIterT>
          , regex_matcher<BidiIterT>
        >::type type;

        static type call(regex_placeholder<BidiIterT, ByRefT> const &m, dont_care)
        {
            return type(m.impl_);
        }
    };

    template<typename BidiIterT, typename ICaseT, typename TraitsT>
    struct transmogrify<BidiIterT, ICaseT, TraitsT, self_placeholder>
    {
        typedef regex_byref_matcher<BidiIterT> type;

        template<typename VisitorT>
        static type call(self_placeholder, VisitorT &visitor)
        {
            return type(visitor.self());
        }
    };

}}}

#endif
