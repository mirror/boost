/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_EQUAL_TO_IMPL_05232005_0621)
#define FUSION_EQUAL_TO_IMPL_05232005_0621

#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/and.hpp>

namespace boost { namespace fusion
{
    struct mpl_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct equal_to_impl;

        template <>
        struct equal_to_impl<mpl_iterator_tag>
        {
            template <typename I1, typename I2>
            struct apply             
                : is_same<
                    typename remove_const<typename I1::iterator_type>::type
                  , typename remove_const<typename I2::iterator_type>::type
                >
            {
            };
        };
    }
}}

#endif

