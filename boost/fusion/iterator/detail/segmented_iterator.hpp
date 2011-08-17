/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_ITERATOR_SEGMENTED_ITERATOR_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_ITERATOR_SEGMENTED_ITERATOR_HPP_INCLUDED

#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/iterator/iterator_facade.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/detail/segmented_equal_to.hpp>
#include <boost/fusion/container/list/detail/reverse_cons.hpp>

namespace boost { namespace fusion
{
    struct nil;

    namespace detail
    {
        template <typename Stack>
        struct segmented_next_impl;
    }

    // A segmented iterator wraps a "context", which is a cons list
    // of ranges, the frontmost is range over values and the rest
    // are ranges over internal segments.
    template<typename Context>
    struct segmented_iterator
      : iterator_facade<segmented_iterator<Context>, forward_traversal_tag>
    {
        explicit segmented_iterator(Context const& ctx)
          : context(ctx)
        {}

        //auto deref(it)
        //{
        //  return deref(begin(car(it.context)))
        //}
        template<typename It>
        struct deref
        {
            typedef
                typename result_of::deref<
                    typename It::context_type::car_type::begin_type
                >::type
            type;

            static type call(It const& it)
            {
                return *it.context.car.first;
            }
        };

        // Compare all the segment iterators in each stack, starting with
        // the bottom-most.
        template<typename It1, typename It2>
        struct equal_to
          : detail::segmented_equal_to<
                typename detail::reverse_cons<typename It1::context_type>::type,
                typename detail::reverse_cons<typename It2::context_type>::type
            >
        {};

        template<typename It>
        struct next
        {
            typedef detail::segmented_next_impl<typename It::context_type> impl;
            typedef segmented_iterator<typename impl::type> type;

            static type call(It const& it)
            {
                return type(impl::call(it.context));
            }
        };

        typedef Context context_type;
        context_type context;
    };

}}

#endif
