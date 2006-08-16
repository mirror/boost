/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_FIND_IF_05052005_1107)
#define FUSION_FIND_IF_05052005_1107

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Iterator, typename Pred>
    struct apply_filter
    {
        typedef typename
            mpl::apply1<
                Pred
              , typename result_of::value_of<Iterator>::type
            >::type
        type;
    };

    template <typename First, typename Last, typename Pred>
    struct main_find_if;

    template <typename First, typename Last, typename Pred>
    struct recursive_find_if
    {
        typedef typename
            main_find_if<
                typename result_of::next<First>::type, Last, Pred
            >::type
        type;
    };

    template <typename First, typename Last, typename Pred>
    struct main_find_if
    {
        typedef mpl::or_<
            result_of::equal_to<First, Last>
          , apply_filter<First, Pred> >
        filter;

        typedef typename
            mpl::eval_if<
                filter
              , mpl::identity<First>
              , recursive_find_if<First, Last, Pred>
            >::type
        type;
    };

    template <typename First, typename Last, typename Pred>
    struct static_find_if
    {
        typedef typename
            main_find_if<
                First
              , Last
              , typename mpl::lambda<Pred>::type
            >::type
        type;

        template <typename Iterator>
        static type
        call(Iterator const& iter, mpl::true_)
        {
            return iter;
        }

        template <typename Iterator>
        static type
        call(Iterator const& iter, mpl::false_)
        {
            return call(fusion::next(iter));
        }

        template <typename Iterator>
        static type
        call(Iterator const& iter)
        {
            typedef result_of::equal_to<Iterator, type> found;
            return call(iter, found());
        }
    };

    template <typename First, typename Last, typename Pred>
    struct static_seq_find_if : static_find_if<First, Last, Pred>
    {
        typedef typename static_find_if<First, Last, Pred>::type type;

        template <typename Sequence>
        static type
        call(Sequence const& seq)
        {
            return static_find_if<First, Last, Pred>::call(fusion::begin(seq));
        }

        template <typename Sequence>
        static type
        call(Sequence& seq)
        {
            return static_find_if<First, Last, Pred>::call(fusion::begin(seq));
        }
    };
}}}

#endif
