// Copyright (C) 2004, 2005 Arkadiy Vertleyb
// Copyright (C) 2005 Peder Holt
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_TYPEOF_IMPL_HPP_INCLUDED
#define BOOST_TYPEOF_TYPEOF_IMPL_HPP_INCLUDED

#include <boost/mpl/size_t.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/typeof/encode_decode.hpp>
#include <boost/typeof/vector.hpp>

#define BOOST_TYPEOF_VECTOR(n) BOOST_PP_CAT(boost::type_of::vector, n)

#define BOOST_TYPEOF_sizer_item(z, n, _)\
    char item ## n[V::item ## n ::value];

namespace boost { namespace type_of {
    
    template<class V> 
    struct sizer
    {
        // char item0[V::item0::value];
        // char item1[V::item1::value];
        // ...

        BOOST_PP_REPEAT(BOOST_TYPEOF_LIMIT_SIZE, BOOST_TYPEOF_sizer_item, ~)
    };

    template<class T> 
    sizer<typename encode_type<BOOST_TYPEOF_VECTOR(0)<>, T>::type> encode(const T&);
}}

#undef BOOST_TYPEOF_sizer_item

namespace boost { namespace type_of {

    template<class V>
    struct decode_begin
    {
        typedef typename decode_type<typename V::begin>::type type;
    };
}}

#define BOOST_TYPEOF_TYPEITEM(z, n, expr)\
    boost::mpl::size_t<sizeof(boost::type_of::encode(expr).item ## n)>

#define BOOST_TYPEOF_ENCODED_VECTOR(Expr)                                   \
    BOOST_TYPEOF_VECTOR(BOOST_TYPEOF_LIMIT_SIZE)<                           \
        BOOST_PP_ENUM(BOOST_TYPEOF_LIMIT_SIZE, BOOST_TYPEOF_TYPEITEM, Expr) \
    >

#define BOOST_TYPEOF(Expr)\
    boost::type_of::decode_begin<BOOST_TYPEOF_ENCODED_VECTOR(Expr) >::type

#define BOOST_TYPEOF_TPL typename BOOST_TYPEOF

#endif//BOOST_TYPEOF_COMPLIANT_TYPEOF_IMPL_HPP_INCLUDED
