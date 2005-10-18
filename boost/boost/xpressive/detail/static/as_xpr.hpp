///////////////////////////////////////////////////////////////////////////////
// as_xpr.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_STATIC_AS_XPR_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_STATIC_AS_XPR_HPP_EAN_10_04_2005

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/ref.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/logical.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/type_traits/remove_bounds.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/proto/proto.hpp>
#include <boost/xpressive/detail/static/placeholders.hpp>

namespace boost { namespace xpressive { namespace detail
{

    template<typename T>
    struct wrap { wrap(T); };

    ///////////////////////////////////////////////////////////////////////////////
    // is_string_literal
    //
    template<typename T>
    struct is_string_literal
      : mpl::or_
        <
            is_convertible<T, wrap<char const *> >
          , is_convertible<T, wrap<wchar_t const *> >
        >
    {
    };

    ///////////////////////////////////////////////////////////////////////////////
    // string_generator
    //
    template<typename StringT>
    struct string_placeholder_generator
    {
        typedef typename remove_cv
        <
            typename mpl::eval_if
            <
                is_array<StringT>
              , remove_bounds<StringT>
              , remove_pointer<StringT>
            >::type
        >::type char_type;

        typedef string_placeholder<char_type> type;
    };

    ///////////////////////////////////////////////////////////////////////////////
    // as_matcher
    template<typename MatcherT, bool IsXprT = is_xpr<MatcherT>::value>
    struct as_matcher_type
    {
        typedef MatcherT type;

        static type const &call(MatcherT const &matcher)
        {
            return matcher;
        }
    };

    template<typename LiteralT>
    struct as_matcher_type<LiteralT, false>
    {
        typedef typename mpl::eval_if
        <
            is_string_literal<LiteralT>
          , string_placeholder_generator<LiteralT>
          , mpl::identity<literal_placeholder<LiteralT, false> >
        >::type type;

        static type call(LiteralT const &literal)
        {
            return type(literal);
        }
    };

    template<typename BidiIterT>
    struct as_matcher_type<basic_regex<BidiIterT>, false>
    {
        typedef regex_placeholder<BidiIterT, false> type;

        static type call(basic_regex<BidiIterT> const &rex)
        {
            typedef core_access<BidiIterT> access;
            shared_ptr<regex_impl<BidiIterT> > impl = access::get_regex_impl(rex);
            return type(impl);
        }
    };

    template<typename BidiIterT>
    struct as_matcher_type<reference_wrapper<basic_regex<BidiIterT> const>, false>
    {
        typedef regex_placeholder<BidiIterT, false> type;

        static type call(reference_wrapper<basic_regex<BidiIterT> const> const &rex)
        {
            typedef core_access<BidiIterT> access;
            shared_ptr<regex_impl<BidiIterT> > impl = access::get_regex_impl(rex.get());
            return type(impl);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // as_xpr_type
    //
    template<typename XprT>
    struct as_xpr_type<XprT, true> // is_op == true
    {
        typedef XprT type;

        static XprT const &call(XprT const &xpr)
        {
            return xpr;
        }
    };

    template<typename XprT>
    struct as_xpr_type<XprT, false>
    {
        typedef proto::unary_op
        <
            typename as_matcher_type<XprT>::type
          , proto::noop_tag
        > type;

        static type const call(XprT const &xpr)
        {
            return proto::noop(detail::as_matcher_type<XprT>::call(xpr));
        }
    };

}}} // namespace boost::xpressive::detail


namespace boost { namespace xpressive
{

    ///////////////////////////////////////////////////////////////////////////////
    // as_xpr (from a literal to an xpression)
    //
    template<typename XprT>
    inline typename mpl::if_
    <
        proto::is_op<XprT>
      , XprT const &
      , typename detail::as_xpr_type<XprT>::type const
    >::type
    as_xpr(XprT const &xpr)
    {
        return detail::as_xpr_type<XprT>::call(xpr);
    }

}} // namespace boost::xpressive

#endif
