/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SEQUENCE_BASE_04182005_0737)
#define FUSION_SEQUENCE_BASE_04182005_0737

#include <boost/fusion/support/detail/compiler_config.hpp>

namespace boost { namespace fusion
{
    struct sequence_root {};

    template <typename Sequence>
    struct sequence_base : sequence_root
    {
        Sequence const&
        derived() const
        {
            return static_cast<Sequence const&>(*this);
        }

        Sequence&
        derived()
        {
            return static_cast<Sequence&>(*this);
        }
    };
}}

#endif
