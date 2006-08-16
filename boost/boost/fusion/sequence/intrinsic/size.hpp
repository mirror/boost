/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SIZE_05052005_0214)
#define FUSION_SIZE_05052005_0214

#include <boost/mpl/int.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    struct fusion_sequence_tag;

    namespace extension
    {
        template <typename Tag>
        struct size_impl
        {
            template <typename Sequence>
            struct apply : Sequence::size {};
        };
    }

    namespace result_of
    {
        template <typename Sequence>
        struct size
            : extension::size_impl<typename detail::tag_of<Sequence>::type>::
                template apply<Sequence>
        {};
    }

    template <typename Sequence>
    inline typename result_of::size<Sequence>::type
    size(Sequence const&)
    {
        static typename result_of::size<Sequence>::type result;
        return result;
    }
}}

#endif
