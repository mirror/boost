///////////////////////////////////////////////////////////////////////////////
/// \file literal.hpp
/// The literal\<\> terminal wrapper, and the proto::lit() function for
/// creating literal\<\> wrappers.
//
//  Copyright 2007 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_LITERAL_HPP_EAN_01_03_2007
#define BOOST_PROTO_LITERAL_HPP_EAN_01_03_2007

#include <boost/xpressive/proto/proto_fwd.hpp>
#include <boost/xpressive/proto/expr.hpp>
#include <boost/xpressive/proto/traits.hpp>
#include <boost/xpressive/proto/extends.hpp>

namespace boost { namespace proto
{
    template<typename T>
    struct literal
      : extends<typename meta::terminal<T>::type, literal<T> >
    {
        typedef typename meta::terminal<T>::type terminal_type;

        template<typename U>
        literal(U &u)
          : extends<terminal_type, literal<T> >(terminal_type::make(u))
        {}

        template<typename U>
        literal(U const &u)
          : extends<terminal_type, literal<T> >(terminal_type::make(u))
        {}

        template<typename U>
        literal(literal<U> const &u)
          : extends<terminal_type, literal<T> >(terminal_type::make(proto::arg(u)))
        {}

        using extends<terminal_type, literal<T> >::operator =;
    };

    template<typename T>
    inline literal<T &> lit(T &t)
    {
        return literal<T &>(t);
    }

    template<typename T>
    inline literal<T const &> lit(T const &t)
    {
        return literal<T const &>(t);
    }

}}

#endif
