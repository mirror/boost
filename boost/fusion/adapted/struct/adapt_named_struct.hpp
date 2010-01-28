/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman
    Copyright (c) 2009-2010 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_NAMED_ADAPT_STRUCT_SEP_29_2009_0748PM)
#define BOOST_FUSION_NAMED_ADAPT_STRUCT_SEP_29_2009_0748PM

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

#define BOOST_FUSION_ADAPT_NAMED_STRUCT(name, newname, bseq)                    \
    BOOST_FUSION_ADAPT_NAMED_STRUCT_I((())(name)(newname),                      \
        BOOST_PP_CAT(BOOST_FUSION_ADAPT_NAMED_STRUCT_X bseq, 0))                \
    /***/

#define BOOST_FUSION_ADAPT_NAMED_STRUCT_NS(name, ns, newname, bseq)             \
    BOOST_FUSION_ADAPT_NAMED_STRUCT_I((ns)(name)(newname),                      \
        BOOST_PP_CAT(BOOST_FUSION_ADAPT_NAMED_STRUCT_X bseq, 0))                \
    /***/

#define BOOST_FUSION_ADAPT_NAMED_STRUCT_X(x, y) ((x, y)) BOOST_FUSION_ADAPT_NAMED_STRUCT_Y
#define BOOST_FUSION_ADAPT_NAMED_STRUCT_Y(x, y) ((x, y)) BOOST_FUSION_ADAPT_NAMED_STRUCT_X
#define BOOST_FUSION_ADAPT_NAMED_STRUCT_X0
#define BOOST_FUSION_ADAPT_NAMED_STRUCT_Y0

// BOOST_FUSION_ADAPT_NAMED_STRUCT_I generates the overarching structure and uses
// uses SEQ_FOR_EACH_I to generate the "linear" substructures.
// Thanks to Paul Mensonides for the PP macro help

#define BOOST_FUSION_ADAPT_NAMED_STRUCT_I(names, seq)                           \
    BOOST_PP_SEQ_FOR_EACH(                                                      \
        BOOST_FUSION_ADAPT_NAMED_STRUCT_NS_B, _, BOOST_PP_SEQ_ELEM(0, names))   \
        struct BOOST_PP_SEQ_ELEM(2, names)                                      \
        {                                                                       \
            BOOST_PP_SEQ_ELEM(2, names)(BOOST_PP_SEQ_ELEM(1, names)& s)         \
              : s_(s) {}                                                        \
            BOOST_PP_SEQ_ELEM(1, names)& s_;                                    \
        };                                                                      \
    BOOST_PP_SEQ_FOR_EACH(                                                      \
        BOOST_FUSION_ADAPT_NAMED_STRUCT_NS_E, _, BOOST_PP_SEQ_ELEM(0, names))   \
    namespace boost { namespace fusion { namespace traits                       \
    {                                                                           \
        template <>                                                             \
        struct tag_of<BOOST_PP_SEQ_ELEM(2, names)>                              \
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
        struct sequence_tag<BOOST_PP_SEQ_ELEM(2, names)>                        \
        {                                                                       \
            typedef fusion::fusion_sequence_tag type;                           \
        };                                                                      \
                                                                                \
        template<>                                                              \
        struct sequence_tag<BOOST_PP_SEQ_ELEM(2, names) const>                  \
        {                                                                       \
            typedef fusion::fusion_sequence_tag type;                           \
        };                                                                      \
    }}                                                                          \
                                                                                \
    namespace boost { namespace fusion { namespace extension                    \
    {                                                                           \
        template <>                                                             \
        struct struct_size<BOOST_PP_SEQ_ELEM(2, names)>                         \
          : mpl::int_<BOOST_PP_SEQ_SIZE(seq)> {};                               \
        BOOST_PP_SEQ_FOR_EACH_I(BOOST_FUSION_ADAPT_NAMED_STRUCT_C, names, seq)  \
    }}}                                                                         \
    /***/

#define BOOST_FUSION_ADAPT_NAMED_STRUCT_NS_B(r, _, ns) namespace ns {           \
    /***/
#define BOOST_FUSION_ADAPT_NAMED_STRUCT_NS_E(r, _, ns) }                        \
    /***/

#define BOOST_FUSION_ADAPT_NAMED_STRUCT_C(r, names, i, xy)                      \
    template <>                                                                 \
    struct struct_member<BOOST_PP_SEQ_ELEM(1, names), i>                        \
    {                                                                           \
        typedef BOOST_PP_TUPLE_ELEM(2, 0, xy) type;                             \
        static type& call(BOOST_PP_SEQ_ELEM(1, names)& struct_)                 \
        {                                                                       \
            return struct_.s_.BOOST_PP_TUPLE_ELEM(2, 1, xy);                    \
        }                                                                       \
    };                                                                          \
    /***/

#endif

