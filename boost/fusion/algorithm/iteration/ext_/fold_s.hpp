/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_FOLD_S_HPP_INCLUDED)
#define BOOST_FUSION_FOLD_S_HPP_INCLUDED

#include <boost/fusion/algorithm/iteration/fold.hpp>
#include <boost/fusion/support/segmented_fold_until.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Fun>
    struct segmented_fold_fun
    {
        explicit segmented_fold_fun(Fun const& f)
          : fun(f)
        {}

        Fun const& fun;

        template <typename Sequence, typename State, typename Context>
        struct apply
        {
            typedef typename result_of::fold<Sequence, State, Fun>::type type;
            typedef mpl::true_ continue_type;

            static type call(Sequence& seq, State const& state, Context const&, segmented_fold_fun const& fun)
            {
                return fusion::fold(seq, state, fun.fun);
            }
        };
    };
}}}

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename State, typename F>
        struct fold_s
          : result_of::segmented_fold_until<
                Sequence,
                State,
                detail::segmented_fold_fun<F>
            >
        {};
    }

    template <typename Sequence, typename State, typename F>
    typename result_of::fold_s<Sequence, State, F>::type
    fold_s(Sequence& seq, State const& state, F const& f)
    {
        return fusion::segmented_fold_until(seq, state, detail::segmented_fold_fun<F>(f));
    }

    template <typename Sequence, typename State, typename F>
    typename result_of::fold_s<Sequence const, State, F>::type
    fold_s(Sequence const& seq, State const& state, F const& f)
    {
        return fusion::segmented_fold_until(seq, state, detail::segmented_fold_fun<F>(f));
    }
}}

#endif
