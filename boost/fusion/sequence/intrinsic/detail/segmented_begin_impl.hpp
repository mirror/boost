/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_BEGIN_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_BEGIN_IMPL_HPP_INCLUDED

#include <boost/type_traits/remove_const.hpp>
#include <boost/fusion/container/list/cons_fwd.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/fusion/sequence/intrinsic/detail/segmented_end_impl.hpp>
#include <boost/fusion/support/detail/segmented_fold_until_impl.hpp>

namespace boost { namespace fusion
{
    template <typename First, typename Last>
    struct iterator_range;
}}

namespace boost { namespace fusion { namespace detail
{
    struct segmented_begin_fun
    {
        template <typename Sig>
        struct result;
    
        template <typename This, typename Sequence, typename State, typename Context>
        struct result<This(Sequence&, State&, Context&)>
        {
            typedef
                iterator_range<
                    typename fusion::result_of::begin<Sequence>::type
                  , typename fusion::result_of::end<Sequence>::type
                >
            range_type;

            typedef
                fusion::result<
                    cons<range_type, typename remove_const<Context>::type>
                  , fusion::break_
                >
            type;
        };

        template <typename Sequence, typename State, typename Context>
        typename result<segmented_begin_fun(Sequence&, State const&, Context const&)>::type
        operator()(Sequence& seq, State const&, Context const& context) const
        {
            typedef
                iterator_range<
                    typename fusion::result_of::begin<Sequence>::type
                  , typename fusion::result_of::end<Sequence>::type
                >
            range_type;

            return cons<range_type, Context>(range_type(fusion::begin(seq), fusion::end(seq)), context);
        }
    };

    template <typename Sequence, typename Stack, bool IsSegmented = traits::is_segmented<Sequence>::type::value>
    struct segmented_begin_impl_aux
    {
        typedef
            segmented_end_impl<Sequence, Stack>
        end_impl;

        typedef
            segmented_fold_until_impl<
                Sequence
              , result<typename end_impl::type, continue_>
              , Stack
              , segmented_begin_fun
            >
        fold_impl;

        typedef typename fold_impl::type::value_type type;

        static type call(Sequence& seq, Stack const& stack)
        {
            return fold_impl::call(seq, end_impl::call(seq, stack), stack, segmented_begin_fun()).value;
        }
    };

    template <typename Sequence, typename Stack>
    struct segmented_begin_impl_aux<Sequence, Stack, false>
    {
        typedef typename result_of::begin<Sequence>::type  begin_type;
        typedef typename result_of::end<Sequence>::type    end_type;
        typedef iterator_range<begin_type, end_type>    pair_type;
        typedef cons<pair_type, Stack>                  type;

        static type call(Sequence& seq, Stack stack)
        {
            return type(pair_type(fusion::begin(seq), fusion::end(seq)), stack);
        }
    };

    template <typename Sequence, typename Stack>
    struct segmented_begin_impl
      : segmented_begin_impl_aux<Sequence, Stack>
    {};

}}}

#endif
