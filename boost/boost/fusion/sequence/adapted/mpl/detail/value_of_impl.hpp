/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_OF_TRAITS_05052005_0734)
#define FUSION_VALUE_OF_TRAITS_05052005_0734

#include <boost/mpl/deref.hpp>

namespace boost { namespace fusion
{
    struct mpl_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        template <>
        struct value_of_impl<mpl_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename mpl::deref<
                    typename Iterator::iterator_type>::type
                type;
            };
        };
    }
}}

#endif


