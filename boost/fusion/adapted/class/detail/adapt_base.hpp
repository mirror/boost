/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_DETAIL_CLASS_ADAPT_BASE_HPP
#define BOOST_FUSION_ADAPTED_DETAIL_CLASS_ADAPT_BASE_HPP

#include <boost/fusion/adapted/struct/detail/adapt_base.hpp>

#define BOOST_FUSION_ADAPT_CLASS_C_BASE(\
    TEMPLATE_PARAMS_SEQ,NAME_SEQ,I,ATTRIBUTE,ATTRIBUTE_TUPEL_SIZE)              \
                                                                                \
    template<                                                                   \
        BOOST_FUSION_ADAPT_STRUCT_UNPACK_TEMPLATE_PARAMS(TEMPLATE_PARAMS_SEQ)   \
    >                                                                           \
    struct class_member_proxy<                                                  \
        BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME(NAME_SEQ)                         \
      , I                                                                       \
    >                                                                           \
    {                                                                           \
        typedef                                                                 \
            BOOST_PP_TUPLE_ELEM(ATTRIBUTE_TUPEL_SIZE, 0, ATTRIBUTE)             \
        type;                                                                   \
                                                                                \
        class_member_proxy(BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME(NAME_SEQ)& obj)\
          : obj(obj)                                                            \
        {}                                                                      \
                                                                                \
        template<class Arg>                                                     \
        class_member_proxy&                                                     \
        operator=(Arg val)                                                      \
        {                                                                       \
            BOOST_PP_TUPLE_ELEM(ATTRIBUTE_TUPEL_SIZE, 3, ATTRIBUTE);            \
            return *this;                                                       \
        }                                                                       \
                                                                                \
        operator type()                                                         \
        {                                                                       \
            return BOOST_PP_TUPLE_ELEM(ATTRIBUTE_TUPEL_SIZE, 2, ATTRIBUTE);     \
        }                                                                       \
                                                                                \
        BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME(NAME_SEQ)& obj;                   \
    };                                                                          \
                                                                                \
    template<                                                                   \
        BOOST_FUSION_ADAPT_STRUCT_UNPACK_TEMPLATE_PARAMS(TEMPLATE_PARAMS_SEQ)   \
    >                                                                           \
    struct struct_member<BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME(NAME_SEQ), I>    \
    {                                                                           \
        typedef BOOST_PP_TUPLE_ELEM(ATTRIBUTE_TUPEL_SIZE, 0, ATTRIBUTE) type;   \
        typedef                                                                 \
            BOOST_PP_TUPLE_ELEM(ATTRIBUTE_TUPEL_SIZE, 1, ATTRIBUTE)             \
        get_type;                                                               \
        typedef                                                                 \
            class_member_proxy<                                                 \
                BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME(NAME_SEQ)                 \
              , I                                                               \
            >                                                                   \
        proxy;                                                                  \
                                                                                \
        static get_type                                                         \
        call(BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME(NAME_SEQ) const& obj)        \
        {                                                                       \
            return BOOST_PP_TUPLE_ELEM(ATTRIBUTE_TUPEL_SIZE, 2, ATTRIBUTE);     \
        };                                                                      \
                                                                                \
        static proxy                                                            \
        call(BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME(NAME_SEQ)& obj)              \
        {                                                                       \
            return proxy(obj);                                                  \
        };                                                                      \
    };

namespace boost { namespace fusion { namespace extension
{
    template <typename T, int N>
    struct class_member_proxy;
}}}

#endif
