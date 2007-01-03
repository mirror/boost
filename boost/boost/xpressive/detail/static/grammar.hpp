///////////////////////////////////////////////////////////////////////////////
// grammar.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_STATIC_GRAMMAR_HPP_EAN_11_12_2006
#define BOOST_XPRESSIVE_DETAIL_STATIC_GRAMMAR_HPP_EAN_11_12_2006

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/mpl/or.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/xpressive/proto/proto_fwd.hpp>
#include <boost/xpressive/proto/matches.hpp>
#include <boost/xpressive/proto/traits.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>

#ifdef BOOST_XPRESSIVE_BETTER_ERRORS
# define BOOST_XPRESSIVE_CHECK_GRAMMAR(Expr, Char)\
    BOOST_MPL_ASSERT((boost::proto::matches<Expr, boost::xpressive::XpressiveGrammar<Char> >))
#else
# define BOOST_XPRESSIVE_CHECK_GRAMMAR(Expr, Char)\
    BOOST_MPL_ASSERT((mpl::true_))
#endif

namespace boost { namespace xpressive
{
    namespace detail
    {
        // is_generic_repeat
        template<typename T>
        struct is_generic_repeat
          : mpl::false_
        {};

        template<uint_t Min, uint_t Max>
        struct is_generic_repeat<generic_quant_tag<Min, Max> >
          : mpl::true_
        {};

        // is_xpressive_literal_impl
        template<typename Char, typename T>
        struct is_xpressive_literal_impl
          : mpl::false_
        {};

        template<typename Char>
        struct is_xpressive_literal_impl<Char, Char>
          : mpl::true_
        {};

        template<typename Char>
        struct is_xpressive_literal_impl<Char, Char const *>
          : mpl::true_
        {};

        template<typename Char, std::size_t N>
        struct is_xpressive_literal_impl<Char, Char (&)[N]>
          : mpl::true_
        {};

        template<typename Char, std::size_t N>
        struct is_xpressive_literal_impl<Char, Char const (&)[N]>
          : mpl::true_
        {};

        template<typename Char>
        struct is_xpressive_literal_impl<Char, string_placeholder<Char> >
          : mpl::true_
        {};

        template<typename Char, typename Not>
        struct is_xpressive_literal_impl<Char, literal_placeholder<Char, Not> >
          : mpl::true_
        {};

        template<typename Char, typename Traits, typename Alloc>
        struct is_xpressive_literal_impl<Char, std::basic_string<Char, Traits, Alloc> >
          : mpl::true_
        {};

        // is_xpressive_literal
        template<typename Char, typename T>
        struct is_xpressive_literal
          : mpl::or_<
                is_xpressive_literal_impl<Char, T>
              , is_xpressive_literal_impl<char, T>
            >
        {};

        template<typename T>
        struct is_xpressive_literal<char, T>
          : is_xpressive_literal_impl<char, T>
        {};

        // is_xpressive_terminal
        template<typename Char, typename T>
        struct is_xpressive_terminal
          : is_xpressive_literal<Char, T>
        {};

        template<typename Char>
        struct is_xpressive_terminal<Char, posix_charset_placeholder>
          : mpl::true_
        {};

        template<typename Char>
        struct is_xpressive_terminal<Char, assert_bos_matcher>
          : mpl::true_
        {};

        template<typename Char>
        struct is_xpressive_terminal<Char, assert_eos_matcher>
          : mpl::true_
        {};

        template<typename Char>
        struct is_xpressive_terminal<Char, epsilon_matcher>
          : mpl::true_
        {};

        template<typename Char>
        struct is_xpressive_terminal<Char, assert_bol_placeholder>
          : mpl::true_
        {};

        template<typename Char>
        struct is_xpressive_terminal<Char, assert_eol_placeholder>
          : mpl::true_
        {};

        template<typename Char, typename Cond>
        struct is_xpressive_terminal<Char, assert_word_placeholder<Cond> >
          : mpl::true_
        {};

        template<typename Char>
        struct is_xpressive_terminal<Char, logical_newline_placeholder>
          : mpl::true_
        {};

        template<typename Char>
        struct is_xpressive_terminal<Char, any_matcher>
          : mpl::true_
        {};

        template<typename Char>
        struct is_xpressive_terminal<Char, self_placeholder>
          : mpl::true_
        {};

        template<typename Char>
        struct is_xpressive_terminal<Char, mark_placeholder>
          : mpl::true_
        {};

        template<typename Char>
        struct is_xpressive_terminal<Char, range_placeholder<Char> >
          : mpl::true_
        {};

        template<typename Char, typename BidiIter, typename ByRef>
        struct is_xpressive_terminal<Char, regex_placeholder<BidiIter, ByRef> >
          : mpl::true_
        {};

        template<typename Char, typename BidiIter>
        struct is_xpressive_terminal<Char, xpressive::basic_regex<BidiIter> >
          : mpl::true_
        {};
    }

    template<typename Char>
    struct XpressiveGrammar;

    template<typename Char>
    struct XpressiveListSet
      : proto::or_<
            proto::meta::comma< XpressiveListSet<Char>, proto::meta::terminal<Char> >
          , proto::meta::comma< XpressiveListSet<Char>, proto::meta::terminal<char> >
          , proto::meta::assign<detail::set_initializer_type, proto::meta::terminal<Char> >
          , proto::meta::assign<detail::set_initializer_type, proto::meta::terminal<char> >
        >
    {};

    template<>
    struct XpressiveListSet<char>
      : proto::or_<
            proto::meta::comma< XpressiveListSet<char>, proto::meta::terminal<char> >
          , proto::meta::assign<detail::set_initializer_type, proto::meta::terminal<char> >
        >
    {};

    template<typename Char>
    struct XpressiveSet
      : proto::or_<
            proto::meta::subscript<detail::set_initializer_type, XpressiveGrammar<Char> >
          , XpressiveListSet<Char>
        >
    {};

    template<typename Char>
    struct XpressiveTaggedSubExpression
      : proto::meta::assign< detail::basic_mark_tag, XpressiveGrammar<Char> >
    {};

    template<typename Char>
    struct XpressiveLookAroundAssertion
      : proto::or_<
            proto::meta::unary_expr<detail::lookahead_tag<true>, XpressiveGrammar<Char> >
          , proto::meta::unary_expr<detail::lookbehind_tag<true>, XpressiveGrammar<Char> >
        >
    {};

    template<typename Char>
    struct XpressiveIndependentSubExpression
      : proto::meta::unary_expr<detail::keeper_tag, XpressiveGrammar<Char> >
    {};

    template<typename Char>
    struct XpressiveModifiedSubExpression
      : proto::meta::binary_expr<detail::modifier_tag, mpl::_, XpressiveGrammar<Char> >
    {};

    template<typename Char>
    struct XpressiveComplementedCharacterLiteral
      : proto::or_<
            proto::meta::complement<proto::meta::terminal<detail::literal_placeholder<Char, mpl::_> > >
          , proto::meta::complement<proto::meta::terminal<detail::literal_placeholder<char, mpl::_> > >
        >
    {};

    template<>
    struct XpressiveComplementedCharacterLiteral<char>
      : proto::meta::complement<proto::meta::terminal<detail::literal_placeholder<char, mpl::_> > >
    {};

    template<typename Char>
    struct XpressiveComplementedExpression
      : proto::and_<
            proto::meta::complement<mpl::_>
          , proto::or_<
                proto::meta::complement<proto::meta::terminal<detail::posix_charset_placeholder> >
              , proto::meta::complement<proto::meta::terminal<detail::logical_newline_placeholder> >
              , XpressiveComplementedCharacterLiteral<Char>
              , proto::meta::complement<XpressiveSet<Char> >
              , proto::meta::complement<XpressiveLookAroundAssertion<Char> >
            >
        >
    {};

    template<typename Char>
    struct XpressiveTerminal
      : proto::or_<
            proto::and_<
                proto::meta::terminal<mpl::_>
              , proto::if_<detail::is_xpressive_terminal<Char, proto::meta::arg<mpl::_> > >
            >
          , XpressiveComplementedExpression<Char>
          , proto::or_<
                XpressiveTaggedSubExpression<Char>
              , XpressiveLookAroundAssertion<Char>
              , XpressiveModifiedSubExpression<Char>
              , XpressiveIndependentSubExpression<Char>
              , XpressiveSet<Char>
            >
        >
    {};

    template<typename Char>
    struct XpressiveQuantified
      : proto::and_<
            proto::meta::unary_expr<mpl::_, XpressiveGrammar<Char> >
          , proto::or_<
                proto::meta::unary_star< mpl::_ >
              , proto::meta::unary_plus< mpl::_ >
              , proto::meta::logical_not< mpl::_ >
              , proto::if_<detail::is_generic_repeat<proto::meta::tag<mpl::_> > >
            >
        >
    {};

    template<typename Char>
    struct XpressiveGrammar
      : proto::or_<
            proto::meta::right_shift< XpressiveGrammar<Char>, XpressiveGrammar<Char> >
          , proto::meta::bitwise_or< XpressiveGrammar<Char>, XpressiveGrammar<Char> >
          , proto::meta::unary_minus< XpressiveQuantified<Char> >
          , XpressiveQuantified<Char>
          , XpressiveTerminal<Char>
        >
    {};

}}

#endif
