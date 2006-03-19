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

    template<class V,class T> 
    sizer<typename encode_type<V, T>::type> encode(const T&);
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
    boost::mpl::size_t<sizeof(boost::type_of::encode<BOOST_TYPEOF_VECTOR(0)<> >(expr).item ## n)>

#define BOOST_TYPEOF_ENCODED_VECTOR(Expr)                                   \
    BOOST_TYPEOF_VECTOR(BOOST_TYPEOF_LIMIT_SIZE)<                           \
        BOOST_PP_ENUM(BOOST_TYPEOF_LIMIT_SIZE, BOOST_TYPEOF_TYPEITEM, Expr) \
    >

#define BOOST_TYPEOF(Expr)\
    boost::type_of::decode_begin<BOOST_TYPEOF_ENCODED_VECTOR(Expr) >::type

#define BOOST_TYPEOF_TPL typename BOOST_TYPEOF

//offset_vector is used to delay the insertion of data into the vector in order to allow 
//encoding to be done in many steps
namespace boost { namespace type_of {
    template<typename V,typename Offset>
    struct offset_vector {
    };

    template<class V,class Offset,class T>
    struct push_back<boost::type_of::offset_vector<V,Offset>,T> {
        typedef offset_vector<V,typename Offset::prior> type;
    };

    template<class V,class T>
    struct push_back<boost::type_of::offset_vector<V,mpl::size_t<0> >,T> {
        typedef typename push_back<V,T>::type type;
    };
}}

#define BOOST_TYPEOF_NESTED_TYPEITEM(z, n, expr)\
    BOOST_STATIC_CONSTANT(int,BOOST_PP_CAT(value,n) = sizeof(boost::type_of::encode<_typeof_start_vector>(expr).item ## n));\
    typedef boost::mpl::size_t<BOOST_PP_CAT(value,n)> BOOST_PP_CAT(item,n);

#define BOOST_TYPEOF_NESTED_TYPEDEF_IMPL(expr) \
        template<int _Typeof_Iteration>\
        struct _typeof_encode_fraction {\
            BOOST_STATIC_CONSTANT(int,_typeof_encode_offset = (_Typeof_Iteration*BOOST_TYPEOF_LIMIT_SIZE));\
            typedef boost::type_of::offset_vector<BOOST_TYPEOF_VECTOR(0)<>,boost::mpl::size_t<_typeof_encode_offset> > _typeof_start_vector;\
            BOOST_PP_REPEAT(BOOST_TYPEOF_LIMIT_SIZE,BOOST_TYPEOF_NESTED_TYPEITEM,expr)\
        };\
        template<typename Pos>\
        struct _typeof_fraction_iter {\
            BOOST_STATIC_CONSTANT(int,pos=(Pos::value));\
            BOOST_STATIC_CONSTANT(int,iteration=(pos/BOOST_TYPEOF_LIMIT_SIZE));\
            BOOST_STATIC_CONSTANT(int,where=pos%BOOST_TYPEOF_LIMIT_SIZE);\
            typedef typename boost::type_of::v_iter<_typeof_encode_fraction<iteration>,boost::mpl::int_<where> >::type type;\
            typedef _typeof_fraction_iter<typename Pos::next> next;\
        };

# define BOOST_TYPEOF_NESTED_TYPEDEF_TPL(name,expr) \
    struct name {\
        BOOST_TYPEOF_NESTED_TYPEDEF_IMPL(expr)\
        typedef typename boost::type_of::decode_type<_typeof_fraction_iter<boost::mpl::size_t<0> > >::type type;\
    };

# define BOOST_TYPEOF_NESTED_TYPEDEF(name,expr) \
    struct name {\
        BOOST_TYPEOF_NESTED_TYPEDEF_IMPL(expr)\
        typedef boost::type_of::decode_type<_typeof_fraction_iter<boost::mpl::size_t<0> > >::type type;\
    };

#endif//BOOST_TYPEOF_COMPLIANT_TYPEOF_IMPL_HPP_INCLUDED
