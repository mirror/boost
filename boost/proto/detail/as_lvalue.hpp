///////////////////////////////////////////////////////////////////////////////
/// \file as_lvalue.hpp
/// Contains definition the as_lvalue() functions.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_TRANSFORM_AS_LVALUE_HPP_EAN_12_27_2007
#define BOOST_PROTO_TRANSFORM_AS_LVALUE_HPP_EAN_12_27_2007

#include <boost/proto/detail/prefix.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/detail/suffix.hpp>

namespace boost { namespace proto
{
    namespace detail
    {
        struct int_
        {
            int_() {}
            int_(int) {}
        };

        template<typename T>
        T &as_lvalue(T &t, int = 0)
        {
            return t;
        }

        template<typename T>
        T const &as_lvalue(T const &t, int = 0)
        {
            return t;
        }

        template<typename Ret, typename T>
        Ret as_lvalue(T &t, int_ = int_() BOOST_PROTO_DISABLE_IF_IS_CONST(T))
        {
            return t;
        }

        template<typename Ret, typename T>
        Ret as_lvalue(T const &t, int_ = int_())
        {
            return t;
        }
    }
}}

#endif
