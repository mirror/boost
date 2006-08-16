/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_IS_ASSOCIATIVE_IMPL_20060304_2219)
#define BOOST_FUSION_IS_ASSOCIATIVE_IMPL_20060304_2219

#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion { 

    struct set_tag;

    namespace extension {
        template<typename Tag>
        struct is_associative_impl;

        template<>
        struct is_associative_impl<fusion::set_tag>
        {
            template<typename Seq>
            struct apply
                : mpl::true_
            {};
        };
    }
}}

#endif
