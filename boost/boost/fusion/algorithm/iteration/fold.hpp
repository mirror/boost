/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_FOLD_05052005_1214)
#define FUSION_FOLD_05052005_1214

#include <boost/fusion/algorithm/iteration/detail/fold.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/static_assert.hpp>

namespace boost { namespace fusion
{
    struct void_;

    namespace result_of
    {
        template <typename Sequence, typename State, typename F>
        struct fold
        {
            typedef typename
                detail::static_fold<
                    typename result_of::begin<Sequence>::type
                  , typename result_of::end<Sequence>::type
                  , State
                  , F
                >::type
            type;
        };
    }

    template <typename Sequence, typename State, typename F>
    inline typename result_of::fold<Sequence, State, F>::type
    fold(Sequence& seq, State const& state, F const& f)
    {
        return detail::fold(
            fusion::begin(seq)
          , fusion::end(seq)
          , state
          , f
          , result_of::equal_to<
                typename result_of::begin<Sequence>::type
              , typename result_of::end<Sequence>::type>()
        );
    }

    template <typename Sequence, typename State, typename F>
    inline typename result_of::fold<Sequence const, State, F>::type
    fold(Sequence const& seq, State const& state, F const& f)
    {
        return detail::fold(
            fusion::begin(seq)
          , fusion::end(seq)
          , state
          , f
          , result_of::equal_to<
                typename result_of::begin<Sequence const>::type
              , typename result_of::end<Sequence const>::type>()
        );
    }
}}

#endif

