/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_AT_KEY_05052005_0229)
#define FUSION_VALUE_AT_KEY_05052005_0229

#include <boost/mpl/int.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    namespace extension
    {
        template <typename Tag>
        struct value_at_key_impl
        {
            template <typename Sequence, typename N>
            struct apply;
        };
    }
    
    namespace result_of
    {
        template <typename Sequence, typename N>
        struct value_at_key
            : extension::value_at_key_impl<typename detail::tag_of<Sequence>::type>::
                template apply<Sequence, N>
        {};
    }
}}

#endif

