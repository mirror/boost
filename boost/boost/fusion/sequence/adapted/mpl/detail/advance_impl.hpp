/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ADVANCE_IMPL_09232005_2324)
#define FUSION_ADVANCE_IMPL_09232005_2324

#include <boost/mpl/advance.hpp>

namespace boost { namespace fusion
{
    struct mpl_iterator_tag;

    template <typename Iterator>
    struct mpl_iterator;

    namespace extension
    {
        template <typename Tag>
        struct advance_impl;
    
        template <>
        struct advance_impl<mpl_iterator_tag>
        {
            template <typename Iterator, typename N>
            struct apply
            {
                typedef mpl_iterator<
                    typename mpl::advance<typename Iterator::iterator_type, N>::type> 
                type;
    
                static type
                call(Iterator const& i)
                {
                    static type result; 
                    return result;
                }
            };
        };
    }
}}

#endif
