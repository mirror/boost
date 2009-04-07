
#ifndef BOOST_MPL_STRING_HPP_INCLUDED
#define BOOST_MPL_STRING_HPP_INCLUDED

// Copyright Eric Niebler 2009
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id: string.hpp 49239 2009-04-01 09:10:26Z eric_niebler $
// $Date: 2009-04-01 02:10:26 -0700 (Wed, 1 Apr 2009) $
// $Revision: 49239 $

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/mpl/char.hpp>
#include <boost/mpl/long.hpp>
#include <boost/mpl/back.hpp>
#include <boost/mpl/copy.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/joint_view.hpp>
#include <boost/mpl/insert_range.hpp>
#include <boost/mpl/back_inserter.hpp>
#include <boost/mpl/iterator_range.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>
#include <boost/preprocessor/arithmetic/div.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>

namespace boost { namespace mpl
{
    #ifndef BOOST_MPL_STRING_MAX_LENGTH
    # define BOOST_MPL_STRING_MAX_LENGTH 32
    #endif
    
    #define BOOST_MPL_STRING_MAX_PARAMS BOOST_PP_DIV(BOOST_PP_ADD(BOOST_MPL_STRING_MAX_LENGTH, 3), 4)

    #define BOOST_MPL_MULTICHAR_LENGTH(c)   (std::size_t)((c>0xffffff)+(c>0xffff)+(c>0xff)+1)
    #define BOOST_MPL_MULTICHAR_AT(c,i)     (char)(0xff&(c>>(8*(BOOST_MPL_MULTICHAR_LENGTH(c)-(std::size_t)(i)-1))))

    struct string_tag;
    struct string_iterator_tag;

    template<BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(BOOST_MPL_STRING_MAX_PARAMS, unsigned int C, 0)>
    struct string;

    template<typename Sequence, unsigned long N>
    struct string_iterator;

    template<typename Sequence>
    struct sequence_tag;

    template<typename Tag>
    struct size_impl;

    template<>
    struct size_impl<string_tag>
    {
        template<typename Sequence>
        struct apply
          : mpl::size_t<Sequence::size>
        {};
    };

    template<typename Tag>
    struct at_impl;

    template<>
    struct at_impl<string_tag>
    {
        template<typename Sequence, typename N>
        struct apply
          : Sequence::template at<N::value>
        {};
    };

    template<typename Tag>
    struct begin_impl;

    template<>
    struct begin_impl<string_tag>
    {
        template<typename Sequence>
        struct apply
        {
            typedef string_iterator<Sequence, 0> type;
        };
    };

    template<typename Tag>
    struct end_impl;

    template<>
    struct end_impl<string_tag>
    {
        template<typename Sequence>
        struct apply
        {
            typedef string_iterator<Sequence, Sequence::size> type;
        };
    };

    template<typename Tag>
    struct push_back_impl;

    template<>
    struct push_back_impl<string_tag>
    {
        template<typename Sequence, typename Value, bool B = (4==BOOST_MPL_MULTICHAR_LENGTH(Sequence::back_))>
        struct apply
        {
            BOOST_MPL_ASSERT_MSG(false, PUSH_BACK_FAILED_MPL_STRING_IS_FULL, (Sequence));
            typedef void type;
        };

        template<typename Value>
        struct apply<string<>, Value, false>
        {
            typedef string<(char)Value::value> type;
        };

        #define M0(z,n,data)                                                                        \
        template<BOOST_PP_ENUM_PARAMS_Z(z, n, unsigned int C), typename Value>                      \
        struct apply<string<BOOST_PP_ENUM_PARAMS_Z(z, n, C)>, Value, false>                         \
        {                                                                                           \
            typedef string<                                                                         \
                BOOST_PP_ENUM_PARAMS_Z(z, BOOST_PP_DEC(n), C)                                       \
                BOOST_PP_COMMA_IF(BOOST_PP_DEC(n))                                                  \
                (BOOST_PP_CAT(C,BOOST_PP_DEC(n))>0xffffff)                                          \
                ?BOOST_PP_CAT(C,BOOST_PP_DEC(n))                                                    \
                :(BOOST_PP_CAT(C,BOOST_PP_DEC(n))<<8)|(unsigned char)Value::value                   \
              , (BOOST_PP_CAT(C,BOOST_PP_DEC(n))>0xffffff)                                          \
                ?(char)Value::value                                                                 \
                :0                                                                                  \
            > type;                                                                                 \
        };

        BOOST_PP_REPEAT_FROM_TO(1, BOOST_PP_DEC(BOOST_MPL_STRING_MAX_PARAMS), M0, ~)
        #undef M0

        template<BOOST_PP_ENUM_PARAMS(BOOST_MPL_STRING_MAX_PARAMS, unsigned int C), typename Value>
        struct apply<string<BOOST_PP_ENUM_PARAMS(BOOST_MPL_STRING_MAX_PARAMS, C)>, Value, false>
        {
            typedef string<
                BOOST_PP_ENUM_PARAMS(BOOST_PP_DEC(BOOST_MPL_STRING_MAX_PARAMS), C)
              , (BOOST_PP_CAT(C,BOOST_PP_DEC(BOOST_MPL_STRING_MAX_PARAMS))<<8)|(unsigned char)Value::value
            > type;
        };
    };

    template<typename Tag>
    struct push_front_impl;

    template<>
    struct push_front_impl<string_tag>
    {
        template<typename Sequence, typename Value, bool B = (4==BOOST_MPL_MULTICHAR_LENGTH(Sequence::front_))>
        struct apply
        {
            BOOST_MPL_ASSERT_MSG(false, PUSH_FRONT_FAILED_MPL_STRING_IS_FULL, (Sequence));
            typedef void type;
        };

        template<typename Value>
        struct apply<string<>, Value, false>
        {
            typedef string<(char)Value::value> type;
        };

        #define M0(z,n,data)                                                                        \
        template<BOOST_PP_ENUM_PARAMS_Z(z, n, unsigned int C), typename Value>                      \
        struct apply<string<BOOST_PP_ENUM_PARAMS_Z(z, n, C)>, Value, true>                          \
        {                                                                                           \
            typedef string<                                                                         \
                (char)Value::value                                                                  \
                BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, C)                                            \
            > type;                                                                                 \
        };

        BOOST_PP_REPEAT_FROM_TO(1, BOOST_PP_DEC(BOOST_MPL_STRING_MAX_PARAMS), M0, ~)
        #undef M0

        template<BOOST_PP_ENUM_PARAMS(BOOST_MPL_STRING_MAX_PARAMS, unsigned int C), typename Value>
        struct apply<string<BOOST_PP_ENUM_PARAMS(BOOST_MPL_STRING_MAX_PARAMS, C)>, Value, false>
        {
            typedef string<
                ((((unsigned char)Value::value)<<(BOOST_MPL_MULTICHAR_LENGTH(C0)*8))|C0)
              , BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_MPL_STRING_MAX_PARAMS, C)
            > type;
        };
    };

    template<typename Tag>
    struct insert_range_impl;

    template<>
    struct insert_range_impl<string_tag>
    {
        template<typename Sequence, typename Pos, typename Range>
        struct apply
          : copy<
                joint_view<
                    iterator_range<
                        string_iterator<Sequence, 0>
                      , Pos
                    >
                  , joint_view<
                        Range
                      , iterator_range<
                            Pos
                          , string_iterator<Sequence, Sequence::size>
                        >
                    >
                >
              , back_inserter<string<> >
            >
        {};
    };

    template<typename Tag>
    struct insert_impl;

    template<>
    struct insert_impl<string_tag>
    {
        template<typename Sequence, typename Pos, typename Value>
        struct apply
          : insert_range<Sequence, Pos, string<(char)Value::value> >
        {};
    };

    template<typename Tag>
    struct erase_impl;

    template<>
    struct erase_impl<string_tag>
    {
        template<typename Sequence, typename First, typename Last>
        struct apply
          : copy<
                joint_view<
                    iterator_range<
                        string_iterator<Sequence, 0>
                      , First
                    >
                  , iterator_range<
                        typename if_na<Last, typename next<First>::type>::type
                      , string_iterator<Sequence, Sequence::size>
                    >
                >
              , back_inserter<string<> >
            >
        {};
    };

    template<typename Tag>
    struct clear_impl;

    template<>
    struct clear_impl<string_tag>
    {
        template<typename>
        struct apply
        {
            typedef string<> type;
        };
    };

    template<typename Tag>
    struct advance_impl;

    template<>
    struct advance_impl<string_iterator_tag>
    {
        template<typename Iterator, typename N>
        struct apply
        {
            typedef string_iterator<
                typename Iterator::string_type
              , Iterator::index + N::value
            > type;
        };
    };

    template<typename Tag>
    struct distance_impl;

    template<>
    struct distance_impl<string_iterator_tag>
    {
        template<typename First, typename Last>
        struct apply
        {
            typedef mpl::long_<(long)Last::index - (long)First::index> type;
        };
    };

    template<typename Sequence, unsigned long N>
    struct string_iterator
      : Sequence::template at<N>
    {
        typedef string_iterator_tag tag;
        typedef std::random_access_iterator_tag category;
        typedef Sequence string_type;
        static unsigned long const index = N;
        typedef string_iterator<Sequence, N+1> next;
        typedef string_iterator<Sequence, N-1> prior;
    };

    template<BOOST_PP_ENUM_PARAMS(BOOST_MPL_STRING_MAX_PARAMS, unsigned int C)>
    struct string
    {
        /// INTERNAL ONLY
        static unsigned int const front_ = C0;
        /// INTERNAL ONLY
        static unsigned int const back_ = BOOST_PP_CAT(C, BOOST_PP_DEC(BOOST_MPL_STRING_MAX_PARAMS));
        /// INTERNAL ONLY
        typedef string<BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_MPL_STRING_MAX_PARAMS, C)> rest_;

        typedef string type;

        typedef string_tag tag;

        static std::size_t const size = BOOST_MPL_MULTICHAR_LENGTH(C0) + rest_::size;

    #if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
    private:
        /// INTERNAL ONLY
        template<unsigned long Pos, bool B>
        struct at_impl
          : boost::mpl::char_<BOOST_MPL_MULTICHAR_AT(C0,Pos)>
        {};

        /// INTERNAL ONLY
        template<unsigned long Pos>
        struct at_impl<Pos, false>
          : rest_::template at<Pos-BOOST_MPL_MULTICHAR_LENGTH(C0)>
        {};

    public:
        template<unsigned long Pos>
        struct at
          : at_impl<Pos, (Pos < BOOST_MPL_MULTICHAR_LENGTH(C0))>
        {};
    #else
        template<unsigned long Pos, bool B = (Pos < BOOST_MPL_MULTICHAR_LENGTH(C0))>
        struct at
          : boost::mpl::char_<BOOST_MPL_MULTICHAR_AT(C0,Pos)>
        {};

        template<unsigned long Pos>
        struct at<Pos, false>
          : rest_::template at<Pos-BOOST_MPL_MULTICHAR_LENGTH(C0)>
        {};
    #endif

        static char const c_str[];
    };

    template<BOOST_PP_ENUM_PARAMS(BOOST_MPL_STRING_MAX_PARAMS, unsigned int C)>
    char const string<BOOST_PP_ENUM_PARAMS(BOOST_MPL_STRING_MAX_PARAMS, C)>::c_str[] =
    {
    #define M0(z, n, data) at<n>::value
        BOOST_PP_ENUM(BOOST_MPL_STRING_MAX_LENGTH, M0, ~)
    #undef M0
      , '\0' // to ensure the string is null-terminated
    };

    template<BOOST_PP_ENUM_PARAMS(BOOST_MPL_STRING_MAX_PARAMS, unsigned int C)>
    std::size_t const string<BOOST_PP_ENUM_PARAMS(BOOST_MPL_STRING_MAX_PARAMS, C)>::size;

    template<BOOST_PP_ENUM_PARAMS(BOOST_MPL_STRING_MAX_PARAMS, unsigned int C)>
    unsigned int const string<BOOST_PP_ENUM_PARAMS(BOOST_MPL_STRING_MAX_PARAMS, C)>::front_;

    template<BOOST_PP_ENUM_PARAMS(BOOST_MPL_STRING_MAX_PARAMS, unsigned int C)>
    unsigned int const string<BOOST_PP_ENUM_PARAMS(BOOST_MPL_STRING_MAX_PARAMS, C)>::back_;

    template<>
    struct string<>
    {
        /// INTERNAL ONLY
        static unsigned int const front_ = 0;
        /// INTERNAL ONLY
        static unsigned int const back_ = 0;
        /// INTERNAL ONLY
        typedef string rest_;

        typedef string type;

        typedef string_tag tag;

        static std::size_t const size = 0;

        template<unsigned long>
        struct at
          : boost::mpl::char_<'\0'>
        {};

        static char const c_str[];
    };

    char const string<>::c_str[] = {'\0'};
    std::size_t const string<>::size;
    unsigned int const string<>::front_;
    unsigned int const string<>::back_;

}} // namespace boost

#endif // BOOST_MPL_STRING_HPP_INCLUDED
