// Copyright (C) 2004 Arkadiy Vertleyb
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_ENCODE_DECODE_HPP_INCLUDED
#define BOOST_TYPEOF_ENCODE_DECODE_HPP_INCLUDED

#include <boost/mpl/deref.hpp>
#include <boost/mpl/next.hpp>

namespace boost{namespace type_of{namespace{

    template<class V, class Type_Not_Registered_With_Typeof_System> 
    struct encode_type_impl;
    
    template<class T, class Iter> 
    struct decode_type_impl
    {
        typedef int type;  // MSVC ETI workaround
    };

    template<class V, class T> 
    struct encode_type : encode_type_impl<V, T>
    {};

    template<class Iter> 
    struct decode_type : decode_type_impl<
        typename Iter::type,
        typename Iter::next
    >
    {};
}}}

#endif//BOOST_TYPEOF_ENCODE_DECODE_HPP_INCLUDED
