/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NONE_07062005_1128)
#define FUSION_NONE_07062005_1128

#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/algorithm/query/detail/none.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename F>
        struct none
        {
            typedef bool type;
        };
    }

    template <typename Sequence, typename F>
    inline bool
    none(Sequence const& seq, F f)
    {
        return detail::none(
                fusion::begin(seq)
              , fusion::end(seq)
              , f
              , result_of::equal_to<
                    typename result_of::begin<Sequence>::type
                  , typename result_of::end<Sequence>::type>());
    }
}}

#endif

