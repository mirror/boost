/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_OF_IMPL_09302005_1847)
#define FUSION_VALUE_OF_IMPL_09302005_1847

#include <boost/static_assert.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace fusion
{
    struct std_pair_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        template <>
        struct value_of_impl<std_pair_iterator_tag>
        {
            template <typename Iterator>
            struct apply 
            {
                typedef typename Iterator::pair_type pair_type;
                typedef typename Iterator::index index;
                static int const index_value = index::value;

                BOOST_STATIC_ASSERT(index_value >= 0 && index_value <= 2);
                typedef typename
                    mpl::if_c<
                        (index_value == 0)
                      , typename pair_type::first_type
                      , typename pair_type::second_type
                    >::type
                type;
            };
        };
    }
}}

#endif
