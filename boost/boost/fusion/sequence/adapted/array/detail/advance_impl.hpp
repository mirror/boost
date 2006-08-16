/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_ADVANCE_IMPL_27122005_0938)
#define BOOST_FUSION_ADVANCE_IMPL_27122005_0938

namespace boost { namespace fusion {

    struct array_iterator_tag;

    template<typename Array, std::size_t Pos>
    struct array_iterator;

    namespace extension
    {
        template<typename Tag>
        struct advance_impl;

        template<>
        struct advance_impl<array_iterator_tag>
        {
            template<typename Iterator, typename N>
            struct apply
            {
                typedef typename Iterator::index index;
                typedef typename Iterator::array_type array_type;
                typedef array_iterator<array_type, index::value + N::value> type;

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
