/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_FOLD_S_HPP_INCLUDED)
#define BOOST_FUSION_FOLD_S_HPP_INCLUDED

#include <boost/fusion/algorithm/iteration/fold.hpp>
#include <boost/fusion/view/ext_/segmented_fold_until.hpp>

namespace boost { namespace fusion { namespace detail
{
    template<typename Fun>
    struct segmented_fold_fun
    {
        template<typename Sig>
        struct result;

        template<typename This, typename Range, typename State, typename Context>
        struct result<This(Range&, State&, Context&)>
        {
            typedef
                fusion::result<
                    typename result_of::fold<Range, State, Fun>::type,
                    continue_
                >
            type;
        };

        explicit segmented_fold_fun(Fun const& f)
          : fun(f)
        {}

        template<typename Range, typename State, typename Context>
        typename result<segmented_fold_fun(Range&, State const&, Context const&)>::type
        operator()(Range& rng, State const& state, Context const&) const
        {
            return fusion::fold(rng, state, fun);
        }

        Fun const& fun;
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
