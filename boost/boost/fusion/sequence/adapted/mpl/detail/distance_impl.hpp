/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DISTANCE_IMPL_09232005_2303)
#define FUSION_DISTANCE_IMPL_09232005_2303

#include <boost/mpl/minus.hpp>
#include <boost/mpl/distance.hpp>

namespace boost { namespace fusion
{
    struct mpl_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct distance_impl;

        template <>
        struct distance_impl<mpl_iterator_tag>
        {
            template <typename First, typename Last>
            struct apply 
                : mpl::distance<
                    typename First::iterator_type
                  , typename Last::iterator_type>
            {    
                static typename mpl::distance<
                    typename First::iterator_type
                  , typename Last::iterator_type>::type
                call(First const&, Last const&)
                {
                    typedef typename mpl::distance<
                        typename First::iterator_type
                      , typename Last::iterator_type>::type
                    result;
                    return result();
                }
            };
        };
    }
}}

#endif
