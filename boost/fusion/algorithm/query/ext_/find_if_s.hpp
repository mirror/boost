/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_FIND_IF_S_HPP_INCLUDED)
#define BOOST_FUSION_FIND_IF_S_HPP_INCLUDED

#include <boost/type_traits/remove_const.hpp>
#include <boost/fusion/algorithm/query/find_if.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/view/ext_/segmented_fold_until.hpp>

namespace boost { namespace fusion { namespace detail
{
    template<typename Pred>
    struct segmented_find_if_fun
    {
        template<typename Sig>
        struct result;

        template<typename This, typename Range, typename State, typename Context>
        struct result<This(Range&, State&, Context&)>
        {
            typedef
                typename result_of::find_if<Range, Pred>::type
            iterator_type;

            typedef
                typename result_of::make_segmented_iterator<
                    iterator_type,
                    typename remove_const<Context>::type
                >::type
            segmented_iterator_type;

            typedef
                typename mpl::if_<
                    result_of::equal_to<
                        iterator_type,
                        typename result_of::end<Range>::type
                    >,
                    fusion::result<typename remove_const<State>::type, continue_>, // NOT FOUND
                    fusion::result<segmented_iterator_type, break_>     // FOUND
                >::type
            type;
        };

        template<typename Range, typename State, typename Context>
        typename result<segmented_find_if_fun(Range&, State const&, Context const&)>::type
        operator()(Range& rng, State const& state, Context const& context) const
        {
            typedef
                typename result_of::equal_to<
                    typename result_of::find_if<Range, Pred>::type,
                    typename result_of::end<Range>::type
                >::type
            not_found;

            return call(rng, state, context, not_found());
        }

    private:
        template<typename Range, typename State, typename Context>
        typename result<segmented_find_if_fun(Range&, State const&, Context const&)>::type
        call(Range&, State const& state, Context const&, mpl::true_) const
        {
            return state;
        }

        template<typename Range, typename State, typename Context>
        typename result<segmented_find_if_fun(Range&, State const&, Context const&)>::type
        call(Range& rng, State const&, Context const& context, mpl::false_) const
        {
            return fusion::make_segmented_iterator(fusion::find_if<Pred>(rng), context);
        }
    };

}}}

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename Pred>
        struct find_if_s
          : result_of::segmented_fold_until<
                Sequence,
                typename result_of::end<Sequence>::type,
                detail::segmented_find_if_fun<Pred> >
        {};
    }

    template <typename Pred, typename Sequence>
    typename result_of::find_if_s<Sequence, Pred>::type
    find_if_s(Sequence& seq)
    {
        return fusion::segmented_fold_until(
            seq,
            fusion::end(seq),
            detail::segmented_find_if_fun<Pred>());
    }

    template <typename Pred, typename Sequence>
    typename result_of::find_if_s<Sequence const, Pred>::type
    find_if_s(Sequence const& seq)
    {
        return fusion::segmented_fold_until(
            seq, fusion::end(seq),
            detail::segmented_find_if_fun<Pred>());
    }
}}

#endif
