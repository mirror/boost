/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_ITERATOR_EQUAL_TO_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_ITERATOR_EQUAL_TO_HPP_INCLUDED

#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/iterator/equal_to.hpp>

namespace boost { namespace fusion
{
    struct nil;

    namespace detail
    {
        template <typename Stack1, typename Stack2>
        struct segmented_equal_to
          : mpl::and_<
                result_of::equal_to<
                    typename Stack1::car_type::begin_type,
                    typename Stack2::car_type::begin_type
                >,
                segmented_equal_to<
                    typename Stack1::cdr_type,
                    typename Stack2::cdr_type
                >
            >
        {};

        template <typename Stack1>
        struct segmented_equal_to<Stack1, fusion::nil>
          : mpl::false_
        {};

        template <typename Stack2>
        struct segmented_equal_to<fusion::nil, Stack2>
          : mpl::false_
        {};

        template <>
        struct segmented_equal_to<fusion::nil, fusion::nil>
          : mpl::true_
        {};
    }
}}

#endif
