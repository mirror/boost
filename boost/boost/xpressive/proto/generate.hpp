///////////////////////////////////////////////////////////////////////////////
/// \file generate.hpp
/// Contains definition of generate\<\> class template, which end users can
/// specialize for generating domain-specific expression wrappers.
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_GENERATE_HPP_EAN_02_13_2007
#define BOOST_PROTO_GENERATE_HPP_EAN_02_13_2007

#include <boost/xpressive/proto/detail/prefix.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/xpressive/proto/proto_fwd.hpp>
#include <boost/xpressive/proto/matches.hpp>
#include <boost/xpressive/proto/detail/suffix.hpp>

namespace boost { namespace proto
{

    namespace generatorns_
    {
        struct default_generator
        {
            template<typename Expr>
            struct apply
            {
                typedef Expr type;
            };

            template<typename Expr>
            static Expr const &make(Expr const &expr)
            {
                return expr;
            };
        };

        template<template<typename> class Extends>
        struct generator
        {
            template<typename Expr>
            struct apply
            {
                typedef Extends<Expr> type;
            };

            template<typename Expr>
            static Extends<Expr> make(Expr const &expr)
            {
                return Extends<Expr>(expr);
            }
        };

        template<template<typename> class Extends>
        struct pod_generator
        {
            template<typename Expr>
            struct apply
            {
                typedef Extends<Expr> type;
            };

            template<typename Expr>
            static Extends<Expr> make(Expr const &expr)
            {
                Extends<Expr> that = {expr};
                return that;
            }
        };
    }

    namespace detail
    {
        template<typename Domain, typename Expr>
        struct generate_if
          : lazy_enable_if<
                matches<Expr, typename Domain::grammar>
              , typename Domain::template apply<Expr>
            >
        {};

        // Optimization, generate fewer templates...
        template<typename Expr>
        struct generate_if<proto::default_domain, Expr>
        {
            typedef Expr type;
        };
    }

}}

#endif
