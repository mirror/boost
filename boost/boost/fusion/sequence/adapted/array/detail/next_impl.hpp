/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NEXT_IMPL_27122005_0927)
#define FUSION_NEXT_IMPL_27122005_0927

#include <cstddef>

namespace boost { namespace fusion {

    struct array_iterator_tag;

    template<typename Array, std::size_t Pos>
    struct array_iterator;

    namespace extension
    {
        template<typename Tag>
        struct next_impl;

        template<>
        struct next_impl<array_iterator_tag>
        {
            template<typename Iterator>
            struct apply
            {
                typedef typename Iterator::array_type array_type;
                typedef typename Iterator::index index;
                static int const index_val = index::value;
                typedef array_iterator<array_type, index_val + 1> type;

                static type
                call(Iterator const& i)
                {
                    return type(i.array);
                }
            };
        };
    }
}}

#endif
