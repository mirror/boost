/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman
    Copyright (c) 2009-2010 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_ADAPT_STRUCT_NAMED_SEP_29_2009_0748PM)
#define BOOST_FUSION_ADAPT_STRUCT_NAMED_SEP_29_2009_0748PM

#include <boost/fusion/support/tag_of_fwd.hpp>
#include <boost/fusion/adapted/struct/extension.hpp>
#include <boost/fusion/adapted/struct/struct_iterator.hpp>
#include <boost/fusion/adapted/struct/detail/is_view_impl.hpp>
#include <boost/fusion/adapted/struct/detail/is_sequence_impl.hpp>
#include <boost/fusion/adapted/struct/detail/category_of_impl.hpp>
#include <boost/fusion/adapted/struct/detail/begin_impl.hpp>
#include <boost/fusion/adapted/struct/detail/end_impl.hpp>
#include <boost/fusion/adapted/struct/detail/size_impl.hpp>
#include <boost/fusion/adapted/struct/detail/at_impl.hpp>
#include <boost/fusion/adapted/struct/detail/value_at_impl.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/mpl/int.hpp>
#include <boost/config/no_tr1/utility.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/add_const.hpp>

#define BOOST_FUSION_ADAPT_STRUCT_NAMED(name, newname, bseq)                    \
    BOOST_FUSION_ADAPT_STRUCT_NAMED_I(name, (boost)(fusion)(adapted), newname,  \
        BOOST_PP_CAT(BOOST_FUSION_ADAPT_STRUCT_NAMED_X bseq, 0))                \
    /***/

#define BOOST_FUSION_ADAPT_STRUCT_NAMED_NS(name, ns, newname, bseq)             \
    BOOST_FUSION_ADAPT_STRUCT_NAMED_I(name, ns, newname,                        \
        BOOST_PP_CAT(BOOST_FUSION_ADAPT_STRUCT_NAMED_X bseq, 0))                \
    /***/

#define BOOST_FUSION_ADAPT_STRUCT_NAMED_X(x, y) ((x, y)) BOOST_FUSION_ADAPT_STRUCT_NAMED_Y
#define BOOST_FUSION_ADAPT_STRUCT_NAMED_Y(x, y) ((x, y)) BOOST_FUSION_ADAPT_STRUCT_NAMED_X
#define BOOST_FUSION_ADAPT_STRUCT_NAMED_X0
#define BOOST_FUSION_ADAPT_STRUCT_NAMED_Y0

// BOOST_FUSION_ADAPT_STRUCT_NAMED_I generates the overarching structure and uses
// uses SEQ_FOR_EACH_I to generate the "linear" substructures.
// Thanks to Paul Mensonides for the PP macro help

#define BOOST_FUSION_ADAPT_STRUCT_NAMED_I(name, ns, newname, seq)               \
    BOOST_PP_SEQ_FOR_EACH_R(1, BOOST_FUSION_ADAPT_STRUCT_NAMED_NS_B, _, ns)     \
        struct newname                                                          \
        {                                                                       \
            newname(name& s) : s_(s) {}                                         \
            name& s_;                                                           \
        };                                                                      \
    BOOST_PP_SEQ_FOR_EACH_R(1, BOOST_FUSION_ADAPT_STRUCT_NAMED_NS_E, _, ns)     \
                                                                                \
    namespace boost { namespace fusion { namespace traits                       \
    {                                                                           \
        template <>                                                             \
        struct tag_of<BOOST_FUSION_ADAPT_STRUCT_NAMED_NAME(ns, newname)>        \
        {                                                                       \
            typedef struct_tag type;                                            \
        };                                                                      \
    }}}                                                                         \
                                                                                \
    namespace boost { namespace mpl                                             \
    {                                                                           \
        template<typename>                                                      \
        struct sequence_tag;                                                    \
                                                                                \
        template<>                                                              \
        struct sequence_tag<BOOST_FUSION_ADAPT_STRUCT_NAMED_NAME(ns, newname)>  \
        {                                                                       \
            typedef fusion::fusion_sequence_tag type;                           \
        };                                                                      \
                                                                                \
        template<>                                                              \
        struct sequence_tag<BOOST_FUSION_ADAPT_STRUCT_NAMED_NAME(ns, newname) const> \
        {                                                                       \
            typedef fusion::fusion_sequence_tag type;                           \
        };                                                                      \
    }}                                                                          \
                                                                                \
    namespace boost { namespace fusion { namespace extension                    \
    {                                                                           \
        template <>                                                             \
        struct struct_size<BOOST_FUSION_ADAPT_STRUCT_NAMED_NAME(ns, newname)>   \
          : mpl::int_<BOOST_PP_SEQ_SIZE(seq)> {};                               \
        template <typename T, int N> struct class_member_proxy;                 \
        BOOST_PP_SEQ_FOR_EACH_I(BOOST_FUSION_ADAPT_STRUCT_NAMED_C,              \
            (BOOST_FUSION_ADAPT_STRUCT_NAMED_NAME(ns, newname), name), seq)     \
    }}}                                                                         \
    /***/

#define BOOST_FUSION_ADAPT_STRUCT_NAMED_NAME(ns, newname)                       \
    BOOST_PP_SEQ_FOR_EACH_R(1, BOOST_FUSION_ADAPT_STRUCT_NAMED_NS_D, _, ns)     \
    newname                                                                     \
    /***/

#define BOOST_FUSION_ADAPT_STRUCT_NAMED_NS_B(r, _, ns) namespace ns { 
#define BOOST_FUSION_ADAPT_STRUCT_NAMED_NS_D(r, _, ns) ns::
#define BOOST_FUSION_ADAPT_STRUCT_NAMED_NS_E(r, _, ns) }

#define BOOST_FUSION_ADAPT_STRUCT_NAMED_C(r, names, i, xy)                      \
    template <>                                                                 \
    struct struct_member<BOOST_PP_TUPLE_ELEM(2, 0, names), i>                   \
    {                                                                           \
        typedef boost::mpl::if_<                                                \
            boost::is_const<BOOST_PP_TUPLE_ELEM(2, 1, names)>                   \
          , boost::add_const<BOOST_PP_TUPLE_ELEM(2, 0, xy)>::type               \
          , BOOST_PP_TUPLE_ELEM(2, 0, xy)>::type type;                          \
        static type& call(BOOST_PP_TUPLE_ELEM(2, 0, names)& struct_)            \
        {                                                                       \
            return struct_.s_.BOOST_PP_TUPLE_ELEM(2, 1, xy);                    \
        }                                                                       \
    };                                                                          \
    /***/

#endif

