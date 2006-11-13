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

#include <boost/xpressive/proto/proto_fwd.hpp>
#include <boost/xpressive/proto/matches.hpp>
#include <boost/xpressive/proto/traits.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_pointer.hpp>

namespace boost { namespace xpressive
{
    namespace detail
    {
        template<typename T>
        struct is_generic_repeat
          : mpl::false_
        {};

        template<uint_t Min, uint_t Max>
        struct is_generic_repeat<generic_quant_tag<Min, Max> >
          : mpl::true_
        {};
    }

    struct XpressiveGrammar;

    struct XpressiveListSet
      : proto::or_<
            proto::and_<
                proto::meta::comma< XpressiveListSet, mpl::_ >
              , proto::if_< is_integral< proto::meta::arg<proto::meta::right<mpl::_> > > >
            >
          , proto::and_<
                proto::meta::assign<detail::set_initializer_type, mpl::_>
              , proto::if_< is_integral< proto::meta::arg<proto::meta::right<mpl::_> > > >
            >
        >
    {};

    struct XpressiveSet
      : proto::or_<
            proto::meta::subscript<detail::set_initializer_type, mpl::_>
          , XpressiveListSet
        >
    {};

    struct XpressiveComplementedSet
      : proto::or_<
            proto::meta::complement<XpressiveSet>
          , XpressiveSet
        >
    {};

    struct XpressiveTaggedSubExpression
      : proto::meta::assign<detail::basic_mark_tag, mpl::_>
    {};

    struct XpressiveLiterals
      : proto::or_<
            proto::meta::terminal<std::basic_string<mpl::_, mpl::_, mpl::_> >
          , proto::and_<
                proto::meta::terminal<mpl::_>
              , proto::or_<
                    proto::if_<is_integral<proto::meta::arg<mpl::_> > >
                  , proto::if_<is_pointer<proto::meta::arg<mpl::_> > >
                >
            >
        >
    {};

    struct XpressiveTerminal
      : proto::or_<
            proto::meta::terminal<detail::epsilon_matcher>
          , proto::meta::terminal<detail::posix_charset_placeholder>
          , proto::meta::terminal<detail::assert_bos_matcher>
          , proto::meta::terminal<detail::assert_eos_matcher>
          , proto::or_<
                proto::meta::terminal<detail::assert_bol_placeholder>
              , proto::meta::terminal<detail::assert_eol_placeholder>
              , proto::meta::terminal<detail::assert_word_placeholder<mpl::_> >
              , proto::meta::terminal<detail::literal_placeholder<mpl::_, mpl::_> >
              , proto::or_<
                    proto::meta::terminal<detail::logical_newline_placeholder>
                  , proto::meta::terminal<detail::any_matcher>
                  , proto::meta::terminal<detail::self_placeholder>
                  , proto::meta::terminal<detail::mark_placeholder>
                  , proto::or_<
                        proto::meta::terminal<detail::range_placeholder<mpl::_> >
                      , proto::meta::terminal<detail::regex_placeholder<mpl::_, mpl::_> >
                      , proto::or_<
                            XpressiveLiterals
                          , XpressiveComplementedSet
                          , XpressiveTaggedSubExpression
                        >
                    >
                >
            >
        >
    {};

    struct XpressiveQuantified
      : proto::or_<
            proto::meta::unary_star< XpressiveGrammar >
          , proto::meta::unary_plus< XpressiveGrammar >
          , proto::meta::logical_not< XpressiveGrammar >
          , proto::and_<
                proto::if_<detail::is_generic_repeat<proto::meta::tag<mpl::_> > >
              , proto::if_<proto::matches<proto::meta::arg<mpl::_>, XpressiveGrammar> >
            >
        >
    {};

    struct XpressiveLazyQuantified
      : proto::or_<
            proto::meta::unary_minus< XpressiveQuantified >
          , XpressiveQuantified
          , XpressiveTerminal
        >
    {};

    struct XpressiveSequence
      : proto::or_<
            proto::meta::right_shift< XpressiveGrammar, XpressiveGrammar >
          , XpressiveLazyQuantified
        >
    {};

    struct XpressiveAlternate
      : proto::or_<
            proto::meta::bitwise_or< XpressiveGrammar, XpressiveGrammar >
          , XpressiveSequence
        >
    {};

    struct XpressiveGrammar
      : XpressiveAlternate
    {};

}}

#endif
