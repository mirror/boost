/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_EMPTY_09162005_0335)
#define FUSION_EMPTY_09162005_0335

#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    struct fusion_sequence_tag;

    namespace extension
    {
        template <typename Tag>
        struct empty_impl
        {
            template <typename Sequence>
            struct apply 
                : mpl::bool_<(result_of::size<Sequence>::value == 0)>
            {};
        };
    }

    namespace result_of
    {
        template <typename Sequence>
        struct empty 
            : extension::empty_impl<typename detail::tag_of<Sequence>::type>::
                template apply<Sequence>
        {};
    }

    template <typename Sequence>
    inline typename result_of::empty<Sequence>::type
    empty(Sequence const&)
    {
        static typename result_of::empty<Sequence>::type result;
        return result;
    }
}}

#endif
