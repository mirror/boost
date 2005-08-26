// Copyright (C) 2005 Arkadiy Vertleyb
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_ENCODE_DECODE_PARAMS_HPP_INCLUDED
#define BOOST_TYPEOF_ENCODE_DECODE_PARAMS_HPP_INCLUDED

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

// Assumes iter0 contains initial iterator

#define BOOST_TYPEOF_DECODE_PARAM(z, n, text)   \
    typedef decode_type<iter##n> decode##n;     \
    typedef typename decode##n::type p##n;      \
    typedef typename decode##n::iter BOOST_PP_CAT(iter, BOOST_PP_INC(n));

#define BOOST_TYPEOF_DECODE_PARAMS(n)\
    BOOST_PP_REPEAT(n, BOOST_TYPEOF_DECODE_PARAM, ~)

// The P0, P1, ... PN are encoded and added to V 

#define BOOST_TYPEOF_ENCODE_PARAMS_BEGIN(z, n, text)\
    typename encode_type<

#define BOOST_TYPEOF_ENCODE_PARAMS_END(z, n, text)\
    , BOOST_PP_CAT(P, n)>::type

#define BOOST_TYPEOF_ENCODE_PARAMS(n, ID)                   \
    BOOST_PP_REPEAT(n, BOOST_TYPEOF_ENCODE_PARAMS_BEGIN, ~) \
    typename push_back<V, mpl::size_t<ID> >::type      \
    BOOST_PP_REPEAT(n, BOOST_TYPEOF_ENCODE_PARAMS_END, ~)

#endif//BOOST_TYPEOF_ENCODE_DECODE_PARAMS_HPP_INCLUDED
