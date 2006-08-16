/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_04052005_1141)
#define FUSION_END_04052005_1141

#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    struct fusion_sequence_tag;

    namespace extension
    {
        template <typename Tag>
        struct end_impl
        {
            template <typename Sequence>
            struct apply;
        };
    }

    namespace result_of
    {
        template <typename Sequence>
        struct end
            : extension::end_impl<typename detail::tag_of<Sequence>::type>::
                template apply<Sequence>
        {};
    }

    template <typename Sequence>
    inline typename result_of::end<Sequence>::type
    end(Sequence& seq)
    {
        return result_of::end<Sequence>::call(seq);
    }

    template <typename Sequence>
    inline typename result_of::end<Sequence const>::type
    end(Sequence const& seq)
    {
        return result_of::end<Sequence const>::call(seq);
    }
}}

#endif
