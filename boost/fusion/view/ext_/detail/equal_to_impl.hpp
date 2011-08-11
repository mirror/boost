/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_ITERATOR_EQUAL_TO_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_ITERATOR_EQUAL_TO_HPP_INCLUDED

#include <boost/mpl/equal.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/fusion/mpl.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/container/vector/convert.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>

namespace boost { namespace fusion
{
    struct segmented_iterator_tag;

    namespace extension
    {
        template<typename Tag>
        struct equal_to_impl;

        template<>
        struct equal_to_impl<segmented_iterator_tag>
        {
            // Compare all the segment iterators in each stack, starting with
            // the bottom-most.
            template<typename It1, typename It2>
            struct apply
              : mpl::equal<
                    typename mpl::reverse_transform<
                        typename result_of::as_vector<typename It1::nodes_type>::type,
                        result_of::begin<mpl::_1>
                    >::type,
                    typename mpl::reverse_transform<
                        typename result_of::as_vector<typename It2::nodes_type>::type,
                        result_of::begin<mpl::_1>
                    >::type,
                    result_of::equal_to<mpl::_1, mpl::_2>
                >
            {};
        };

    }
}}

#endif
