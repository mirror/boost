/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_FOLD_05052005_1211)
#define FUSION_FOLD_05052005_1211

#include <boost/mpl/bool.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/next.hpp>

namespace boost { namespace fusion { namespace detail
{
    // Unary arguments version

    template <typename F>
    struct apply_fold_result
    {
        template <typename Value, typename State>
        struct apply
        {
            typedef typename F::template result<Value, State>::type type;
        };
    };

    template <typename Iterator, typename State, typename F>
    struct fold_apply
        : mpl::apply<apply_fold_result<F>, typename result_of::value_of<Iterator>::type, State>
    {};

    template <typename First, typename Last, typename State, typename F>
    struct static_fold;

    template <typename First, typename Last, typename State, typename F>
    struct next_result_of_fold
    {
        typedef typename
            static_fold<
                typename result_of::next<First>::type
              , Last
              , typename fold_apply<First, State, F>::type
              , F
            >::type
        type;
    };

    template <typename First, typename Last, typename State, typename F>
    struct static_fold
    {
        typedef typename
            mpl::if_<
                result_of::equal_to<First, Last>
              , mpl::identity<State>
              , next_result_of_fold<First, Last, State, F>
            >::type
        result;

        typedef typename result::type type;
    };

    // terminal case
    template <typename First, typename Last, typename State, typename F>
    inline State const&
    fold(First const&, Last const&, State const& state, F const&, mpl::true_)
    {
        return state;
    }

    // non-terminal case
    template <typename First, typename Last, typename State, typename F>
    inline typename static_fold<First, Last, State, F>::type
    fold(
        First const& first
      , Last const& last
      , State const& state
      , F const& f
      , mpl::false_)
    {
        return detail::fold(
            fusion::next(first)
          , last
          , f(*first, state)
          , f
          , result_of::equal_to<typename result_of::next<First>::type, Last>()
        );
    }
}}}

#endif

