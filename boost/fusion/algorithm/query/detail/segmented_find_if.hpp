/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_FIND_IF_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_FIND_IF_HPP_INCLUDED

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/fusion/algorithm/query/find_if_fwd.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/support/segmented_fold_until.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Pred>
    struct segmented_find_if_fun
    {
        template <typename Sig>
        struct result;

        template <typename This, typename Sequence, typename State, typename Context>
        struct result<This(Sequence&, State&, Context&)>
        {
            typedef
                typename result_of::find_if<Sequence, Pred>::type
            iterator_type;

            typedef
                typename result_of::make_segmented_iterator<
                    iterator_type
                  , typename remove_const<Context>::type
                >::type
            segmented_iterator_type;

            typedef
                typename mpl::if_<
                    result_of::equal_to<
                        iterator_type
                      , typename result_of::end<Sequence>::type
                    >
                  , fusion::result<typename remove_const<State>::type, continue_>, // NOT FOUND
                    fusion::result<segmented_iterator_type, break_>                // FOUND
                >::type
            type;
        };

        template <typename Sequence, typename State, typename Context>
        typename result<segmented_find_if_fun(Sequence&, State const&, Context const&)>::type
        operator()(Sequence& seq, State const& state, Context const& context) const
        {
            typedef
                typename result_of::equal_to<
                    typename result_of::find_if<Sequence, Pred>::type
                  , typename result_of::end<Sequence>::type
                >::type
            not_found;

            return call(seq, state, context, not_found());
        }

    private:
        template <typename Sequence, typename State, typename Context>
        typename result<segmented_find_if_fun(Sequence&, State const&, Context const&)>::type
        call(Sequence&, State const& state, Context const&, mpl::true_) const
        {
            return state;
        }

        template <typename Sequence, typename State, typename Context>
        typename result<segmented_find_if_fun(Sequence&, State const&, Context const&)>::type
        call(Sequence& seq, State const&, Context const& context, mpl::false_) const
        {
            return fusion::make_segmented_iterator(fusion::find_if<Pred>(seq), context);
        }
    };

    template <typename Sequence, typename Pred>
    struct result_of_segmented_find_if
    {
        struct filter
        {
            typedef
                typename result_of::segmented_fold_until<
                    Sequence
                  , typename result_of::end<Sequence>::type
                  , segmented_find_if_fun<Pred>
                >::type
            type;

            static type call(Sequence& seq)
            {
                return fusion::segmented_fold_until(
                    seq
                  , fusion::end(seq)
                  , segmented_find_if_fun<Pred>());
            }
        };

        typedef typename filter::type type;
    };
}}}

#endif
