///////////////////////////////////////////////////////////////////////////////
/// \file domain.hpp
/// Contains definition of domain\<\> class template, for defining domains
/// with a grammar for controlling operator overloading.
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_DOMAIN_HPP_EAN_02_13_2007
#define BOOST_PROTO_DOMAIN_HPP_EAN_02_13_2007

#include <boost/xpressive/proto/detail/prefix.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/xpressive/proto/proto_fwd.hpp>
#include <boost/xpressive/proto/detail/suffix.hpp>

namespace boost { namespace proto
{

    template<typename Grammar>
    struct domain
    {
        typedef Grammar grammar;

        /// INTERNAL ONLY
        ///
        typedef void boost_proto_is_domain_;
    };

    template<typename T, typename EnableIf>
    struct is_domain
      : mpl::false_
    {};

    template<typename T>
    struct is_domain<T, typename T::boost_proto_is_domain_>
      : mpl::true_
    {};

}}

#endif
