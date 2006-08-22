/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SIZE_IMPL_20060223_2033)
#define BOOST_FUSION_SIZE_IMPL_20060223_2033

#include <boost/mpl/int.hpp>

namespace boost { namespace fusion {

    struct example_sequence_tag;

    namespace extension
    {
        template<typename Tag>
        struct size_impl;

        template<>
        struct size_impl<example_sequence_tag>
        {
            template<typename Sequence>
            struct apply
                : mpl::int_<2>
            {};
        };
    }
}}

#endif
