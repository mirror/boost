/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_CATEGORY_OF_IMPL_20060223_2037)
#define BOOST_FUSION_CATEGORY_OF_IMPL_20060223_2037

namespace boost { namespace fusion {

    struct random_access_traversal_tag;

    namespace extension
    {
        template<typename Tag>
        struct category_of_impl;

        template<>
        struct category_of_impl<example_sequence_tag>
        {
            template<typename Sequence>
            struct apply
            {
                typedef random_access_traversal_tag type;
            };
        };
    }
}}

#endif
