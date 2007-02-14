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
#include <boost/mpl/if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/xpressive/proto/proto_fwd.hpp>
#include <boost/xpressive/proto/matches.hpp>
#include <boost/xpressive/proto/detail/suffix.hpp>

namespace boost { namespace proto
{

    template<typename Domain, typename Expr>
    struct generate
    {
        typedef Expr type;

        static Expr const &make(Expr const &expr)
        {
            return expr;
        }
    };

    template<typename Domain, typename Expr, typename EnableIf>
    struct is_allowed
      : matches<Expr, typename Domain::grammar>
    {};

    namespace detail
    {
        struct empty
        {};

        template<typename Domain, typename Expr>
        struct generate_if
          : mpl::if_<
                is_allowed<Domain, Expr>
              , generate<Domain, Expr>
              , detail::empty
            >::type
        {};

    }

}}

#endif
