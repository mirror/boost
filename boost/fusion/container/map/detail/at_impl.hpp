/*=============================================================================
    Copyright (c) 2001-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_MAP_DETAIL_AT_IMPL_02042013_0821)
#define BOOST_FUSION_MAP_DETAIL_AT_IMPL_02042013_0821

#include <boost/fusion/support/detail/access.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    namespace extension
    {
        template <typename Tag>
        struct at_impl;

        template <>
        struct at_impl<map_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef
                    decltype(std::declval<Sequence>().get(N()))
                type;

                static type
                call(Sequence& m)
                {
                    return m.get(N());
                }
            };

            template <typename Sequence, typename N>
            struct apply<Sequence const, N>
            {
                typedef
                    decltype(std::declval<Sequence const>().get(N()))
                type;

                static type
                call(Sequence const& m)
                {
                    return m.get(N());
                }
            };
        };
    }
}}

#endif
