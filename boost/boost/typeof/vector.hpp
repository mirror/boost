// Copyright (C) 2005 Arkadiy Vertleyb
// Copyright (C) 2005 Peder Holt
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_VECTOR_HPP_INCLUDED
#define BOOST_TYPEOF_VECTOR_HPP_INCLUDED

#include <boost/mpl/int.hpp>
#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/repeat_from_to.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/inc.hpp>
#include <boost/preprocessor/comma_if.hpp>

#ifndef BOOST_TYPEOF_LIMIT_SIZE
#   define BOOST_TYPEOF_LIMIT_SIZE 50
#endif

// iterator

#define BOOST_TYPEOF_spec_iter(z, n, _)\
    template<class V>\
    struct v_iter<V, mpl::int_<n> >\
    {\
        typedef typename V::item ## n type;\
        typedef v_iter<V, mpl::int_<n + 1> > next;\
    };

namespace boost{ namespace type_of{

    template<class V, class Pos> struct v_iter; // not defined
    BOOST_PP_REPEAT(BOOST_TYPEOF_LIMIT_SIZE, BOOST_TYPEOF_spec_iter, ~)
}}

#undef BOOST_TYPEOF_spec_iter

// vector

#define BOOST_TYPEOF_typedef_item(z, n, _)\
    typedef P ## n item ## n;

#define BOOST_TYPEOF_typedef_fake_item(z, n, _)\
    typedef mpl::int_<1> item ## n;

#define BOOST_TYPEOF_define_vector(z, n, _)\
    template<BOOST_PP_ENUM_PARAMS(n, class P) BOOST_PP_COMMA_IF(n) class T = void>\
    struct vector ## n\
    {\
        typedef v_iter<vector ## n, boost::mpl::int_<0> > begin;\
        BOOST_PP_REPEAT(n, BOOST_TYPEOF_typedef_item, ~)\
        BOOST_PP_REPEAT_FROM_TO(n, BOOST_TYPEOF_LIMIT_SIZE, BOOST_TYPEOF_typedef_fake_item, ~)\
    };

namespace boost{ namespace type_of{

    BOOST_PP_REPEAT(BOOST_PP_INC(BOOST_TYPEOF_LIMIT_SIZE), BOOST_TYPEOF_define_vector, ~)
}}

#undef BOOST_TYPEOF_typedef_item
#undef BOOST_TYPEOF_typedef_fake_item
#undef BOOST_TYPEOF_define_vector

// push_back

#define BOOST_TYPEOF_spec_push_back(z, n, _)\
    template<BOOST_PP_ENUM_PARAMS(n, class P) BOOST_PP_COMMA_IF(n) class T>\
    struct push_back<BOOST_PP_CAT(boost::type_of::vector, n)<BOOST_PP_ENUM_PARAMS(n, P)>, T>\
    {\
        typedef BOOST_PP_CAT(boost::type_of::vector, BOOST_PP_INC(n))<\
            BOOST_PP_ENUM_PARAMS(n, P) BOOST_PP_COMMA_IF(n) T\
        > type;\
    };

namespace boost{ namespace type_of{

    template<class V, class T> struct push_back; // not defined
    BOOST_PP_REPEAT(BOOST_TYPEOF_LIMIT_SIZE, BOOST_TYPEOF_spec_push_back, ~)
}}

#undef BOOST_TYPEOF_spec_push_back

#endif//BOOST_TYPEOF_COMPLIANT_VECTOR_HPP_INCLUDED



