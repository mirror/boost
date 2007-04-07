///////////////////////////////////////////////////////////////////////////////
/// \file conditional.hpp
/// A special-purpose proto transform for selecting between two transforms
/// based on a compile-time predicate.
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_TRANSFORM_CONDITIONAL_HPP_EAN_04_02_2007
#define BOOST_PROTO_TRANSFORM_CONDITIONAL_HPP_EAN_04_02_2007

#include <boost/xpressive/proto/detail/prefix.hpp>
#include <boost/xpressive/proto/proto_fwd.hpp>
#include <boost/xpressive/proto/detail/suffix.hpp>

namespace boost { namespace proto { namespace transform
{

    template<typename Predicate, typename Grammar0, typename Grammar1>
    struct conditional
      : proto::or_<
            proto::and_<
                proto::if_<Predicate>
              , Grammar0
            >
          , proto::and_<
                proto::not_<proto::if_<Predicate> >
              , Grammar1
            >
        >
    {};

}}}

#endif
