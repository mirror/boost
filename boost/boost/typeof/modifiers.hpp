// Copyright (C) 2004 Arkadiy Vertleyb
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_MODIFIERS_HPP_INCLUDED
#define BOOST_TYPEOF_MODIFIERS_HPP_INCLUDED

#include <boost/typeof/encode_decode.hpp>
#include <boost/preprocessor/facilities/identity.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

// modifiers

#define BOOST_TYPEOF_modifier_support(ID, Fun)\
    template<class V, class T> struct encode_type_impl<V, Fun(T)>\
    {\
        typedef\
            typename encode_type<\
            typename push_back<\
            V\
            , mpl::size_t<ID> >::type\
            , T>::type\
            type;\
    };\
    template<class Iter> struct decode_type_impl<mpl::size_t<ID>, Iter>\
    {\
        typedef decode_type<Iter> d1;\
        typedef Fun(typename d1::type) type;\
        typedef typename d1::iter iter;\
    }

#define BOOST_TYPEOF_const_fun(T) const T
#define BOOST_TYPEOF_volatile_fun(T) volatile T
#define BOOST_TYPEOF_volatile_const_fun(T) volatile const T
#define BOOST_TYPEOF_pointer_fun(T) T*
#define BOOST_TYPEOF_reference_fun(T) T&

namespace boost { namespace type_of { namespace {

    BOOST_TYPEOF_modifier_support(BOOST_TYPEOF_UNIQUE_ID(), BOOST_TYPEOF_const_fun);
    BOOST_TYPEOF_modifier_support(BOOST_TYPEOF_UNIQUE_ID(), BOOST_TYPEOF_volatile_fun);
    BOOST_TYPEOF_modifier_support(BOOST_TYPEOF_UNIQUE_ID(), BOOST_TYPEOF_volatile_const_fun);
    BOOST_TYPEOF_modifier_support(BOOST_TYPEOF_UNIQUE_ID(), BOOST_TYPEOF_pointer_fun);
    BOOST_TYPEOF_modifier_support(BOOST_TYPEOF_UNIQUE_ID(), BOOST_TYPEOF_reference_fun);

}}}

#undef BOOST_TYPEOF_modifier_support
#undef BOOST_TYPEOF_const_fun
#undef BOOST_TYPEOF_volatile_fun
#undef BOOST_TYPEOF_volatile_const_fun
#undef BOOST_TYPEOF_pointer_fun
#undef BOOST_TYPEOF_reference_fun

// arrays

#define BOOST_TYPEOF_array_support(ID, Qualifier)\
    template<class V, class T, int N>\
    struct encode_type_impl<V, Qualifier() T[N]>\
    {\
        typedef\
            typename encode_type<\
            typename push_back<\
            typename push_back<\
            V\
            , mpl::size_t<ID> >::type\
            , mpl::size_t<N> >::type\
            , T>::type\
        type;\
    };\
    template<class Iter>\
    struct decode_type_impl<mpl::size_t<ID>, Iter>\
    {\
        enum{n = Iter::type::value};\
        typedef decode_type<typename Iter::next> d;\
        typedef typename d::type Qualifier() type[n];\
        typedef typename d::iter iter;\
    }

namespace boost { namespace type_of { namespace {

    BOOST_TYPEOF_array_support(BOOST_TYPEOF_UNIQUE_ID(), BOOST_PP_EMPTY);
    BOOST_TYPEOF_array_support(BOOST_TYPEOF_UNIQUE_ID(), BOOST_PP_IDENTITY(const));
    BOOST_TYPEOF_array_support(BOOST_TYPEOF_UNIQUE_ID(), BOOST_PP_IDENTITY(volatile));
    BOOST_TYPEOF_array_support(BOOST_TYPEOF_UNIQUE_ID(), BOOST_PP_IDENTITY(volatile const));

}}}

#undef BOOST_TYPEOF_array_support

#endif//BOOST_TYPEOF_MODIFIERS_HPP_INCLUDED
