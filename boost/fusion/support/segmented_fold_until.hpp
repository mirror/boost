/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_FOLD_UNTIL_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_FOLD_UNTIL_HPP_INCLUDED

#include <boost/fusion/support/detail/segmented_fold_until_impl.hpp>
#include <boost/fusion/view/iterator_range.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/empty.hpp>
#include <boost/fusion/container/list/cons.hpp>

namespace boost { namespace fusion
{
    //auto segmented_fold_until(rng, state, fun)
    //{
    //  return first(segmented_fold_until_impl(rng, state, nil, fun));
    //}

    namespace result_of
    {
        template <typename Range, typename State, typename Fun>
        struct segmented_fold_until
        {
            typedef
                detail::segmented_fold_until_impl<
                    Range,
                    result<State, continue_>,
                    fusion::nil,
                    Fun
                >
            impl;

            typedef
                typename impl::type::value_type
            type;
        };
    }

    template <typename Range, typename State, typename Fun>
    typename result_of::segmented_fold_until<Range, State, Fun>::type
    segmented_fold_until(Range& rng, State const& state, Fun const& fun)
    {
        typedef typename result_of::segmented_fold_until<Range, State, Fun>::impl impl;
        return impl::call(rng, state, fusion::nil(), fun).value;
    }

    template <typename Range, typename State, typename Fun>
    typename result_of::segmented_fold_until<Range const, State, Fun>::type
    segmented_fold_until(Range const& rng, State const& state, Fun const& fun)
    {
        typedef typename result_of::segmented_fold_until<Range const, State, Fun>::impl impl;
        return impl::call(rng, state, fusion::nil(), fun).value;
    }
}}
#endif
