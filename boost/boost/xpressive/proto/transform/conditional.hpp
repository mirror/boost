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
#include <boost/mpl/assert.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/xpressive/proto/proto_fwd.hpp>
#include <boost/xpressive/proto/detail/suffix.hpp>

namespace boost { namespace proto { namespace transform
{

    template<typename Predicate, typename Grammar0, typename Grammar1>
    struct conditional
      : Grammar0
    {
        conditional();
        BOOST_MPL_ASSERT((is_same<typename Grammar0::type, typename Grammar1::type>));

        template<typename Expr, typename State, typename Visitor>
        struct apply
        {
            typedef typename mpl::if_<
                typename mpl::apply1<Predicate, Expr>::type
              , Grammar0
              , Grammar1
            >::type grammar_type;

            typedef typename grammar_type::template apply<Expr, State, Visitor>::type type;
        };

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &state, Visitor &visitor)
        {
            typedef typename mpl::if_<
                typename mpl::apply1<Predicate, Expr>::type
              , Grammar0
              , Grammar1
            >::type grammar_type;

            return grammar_type::call(expr, state, visitor);
        }
    };

}}}

#endif
