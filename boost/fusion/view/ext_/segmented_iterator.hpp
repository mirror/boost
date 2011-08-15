/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_ITERATOR_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_ITERATOR_HPP_INCLUDED

#include <boost/mpl/equal.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/fusion/mpl/begin.hpp>
#include <boost/fusion/mpl/end.hpp>
#include <boost/fusion/mpl/clear.hpp>
#include <boost/fusion/mpl/push_front.hpp>
#include <boost/fusion/iterator/iterator_facade.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/view/ext_/detail/next_impl.hpp>
#include <boost/fusion/view/ext_/segmented_begin.hpp>
#include <boost/fusion/view/ext_/segmented_end.hpp>
#include <boost/fusion/container/vector/convert.hpp>

namespace boost { namespace fusion
{
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
            : mpl::equal<
                typename mpl::reverse_transform<
                    typename result_of::as_vector<typename It1::context_type>::type,
                    result_of::begin<mpl::_1>
                >::type,
                typename mpl::reverse_transform<
                    typename result_of::as_vector<typename It2::context_type>::type,
                    result_of::begin<mpl::_1>
                >::type,
                result_of::equal_to<mpl::_1, mpl::_2>
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
