/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DISTANCE_IMPL_09302005_1846)
#define FUSION_DISTANCE_IMPL_09302005_1846

#include <boost/mpl/minus.hpp>

namespace boost { namespace fusion
{
    struct std_pair_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct distance_impl;

        template <>
        struct distance_impl<std_pair_iterator_tag>
        {
            template <typename First, typename Last>
            struct apply : mpl::minus<typename Last::index, typename First::index>
            {    
                static typename mpl::minus<
                    typename Last::index, typename First::index>::type
                call(First const&, Last const&)
                {
                    typedef typename mpl::minus<
                        typename Last::index, typename First::index>::type 
                    result;
                    return result();
                }
            };
        };
    }
}}

#endif
