/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_BEGIN_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_BEGIN_IMPL_HPP_INCLUDED

#include <boost/type_traits/remove_const.hpp>
#include <boost/fusion/view/iterator_range.hpp>
#include <boost/fusion/container/list/cons.hpp>
#include <boost/fusion/container/generation/make_cons.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/support/ext_/is_segmented.hpp>
#include <boost/fusion/view/ext_/detail/end_impl.hpp>
#include <boost/fusion/view/ext_/segmented_fold_until.hpp>

namespace boost { namespace fusion { namespace detail
{
    struct segmented_begin_fun
    {
        template<typename Sig>
        struct result;
    
        template<typename This, typename Range, typename State, typename Context>
        struct result<This(Range&, State&, Context&)>
        {
            typedef
                iterator_range<
                    typename fusion::result_of::begin<Range>::type,
                    typename fusion::result_of::end<Range>::type
                >
            range_type;

            typedef
                fusion::result<
                    cons<range_type, typename remove_const<Context>::type>,
                    fusion::break_
                >
            type;
        };

        template<typename Range, typename State, typename Context>
        typename result<segmented_begin_fun(Range&, State const&, Context const&)>::type
        operator()(Range& rng, State const&, Context const& context) const
        {
            typedef
                iterator_range<
                    typename fusion::result_of::begin<Range>::type,
                    typename fusion::result_of::end<Range>::type
                >
            range_type;

            return fusion::make_cons(range_type(fusion::begin(rng), fusion::end(rng)), context);
        }
    };

    template<typename Range, typename Stack, bool IsSegmented = traits::is_segmented<Range>::type::value>
    struct segmented_begin_impl
    {
        typedef
            segmented_end_impl<Range, Stack>
        end_impl;

        typedef
            segmented_fold_until_impl<
                Range,
                result<typename end_impl::type, continue_>,
                Stack,
                segmented_begin_fun
            >
        fold_impl;

        typedef typename fold_impl::type::value_type type;

        static type call(Range& rng, Stack const& stack)
        {
            return fold_impl::call(rng, end_impl::call(rng, stack), stack, segmented_begin_fun()).value;
        }
    };

    template<typename Range, typename Stack>
    struct segmented_begin_impl<Range, Stack, false>
    {
        typedef typename result_of::begin<Range>::type  begin_type;
        typedef typename result_of::end<Range>::type    end_type;
        typedef iterator_range<begin_type, end_type>    pair_type;
        typedef cons<pair_type, Stack>                  type;

        static type call(Range& rng, Stack stack)
        {
            return type(pair_type(fusion::begin(rng), fusion::end(rng)), stack);
        }
    };

}}}

#endif
