/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_EQUAL_TO_IMPL_27122005_1020)
#define BOOST_FUSION_EQUAL_TO_IMPL_27122005_1020

#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/and.hpp>

namespace boost { namespace fusion
{
    struct array_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct equal_to_impl;

        template <>
        struct equal_to_impl<array_iterator_tag>
        {
            template <typename I1, typename I2>
            struct apply             
                : is_same<
                    typename I1::identity
                  , typename I2::identity
                >
            {};
        };
    }
}}

#endif

