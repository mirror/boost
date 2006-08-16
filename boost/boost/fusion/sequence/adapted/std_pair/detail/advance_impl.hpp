/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ADVANCE_IMPL_09302005_1847)
#define FUSION_ADVANCE_IMPL_09302005_1847

#include <boost/static_assert.hpp>

namespace boost { namespace fusion
{
    struct std_pair_iterator_tag;

    template <typename Vector, int N>
    struct std_pair_iterator;

    namespace extension
    {
        template <typename Tag>
        struct advance_impl;
    
        template <>
        struct advance_impl<std_pair_iterator_tag>
        {
            template <typename Iterator, typename N>
            struct apply
            {
                typedef typename Iterator::index index;
                typedef typename Iterator::pair_type pair_type;
                typedef std_pair_iterator<pair_type, index::value+N::value> type;
                BOOST_STATIC_ASSERT(
                    (index::value+N::value) >= 0 &&(index::value+N::value) < 2);
    
                static type
                call(Iterator const& i)
                {
                    return type(i.vec);
                }
            };
        };
    }
}}

#endif
