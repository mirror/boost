/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NEXT_IMPL_09302005_1847)
#define FUSION_NEXT_IMPL_09302005_1847

#include <boost/static_assert.hpp>

namespace boost { namespace fusion
{
    struct std_pair_iterator_tag;
    template <typename Vector, int N>
    struct std_pair_iterator;

    namespace extension
    {
        template <typename Tag>
        struct next_impl;

        template <>
        struct next_impl<std_pair_iterator_tag>
        {
            template <typename Iterator>
            struct apply 
            {
                typedef typename Iterator::pair_type pair_type;
                typedef typename Iterator::index index;
                static int const index_val = index::value;
                typedef std_pair_iterator<pair_type, index_val+1> type;
                BOOST_STATIC_ASSERT((index_val+1) >= 0 &&(index_val+1) <= 2);

                static type
                call(Iterator const& i)
                {
                    return type(i.pair);
                }
            };
        };
    }
}}

#endif
