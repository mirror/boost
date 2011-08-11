/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_ITERATOR_DEREF_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_ITERATOR_DEREF_HPP_INCLUDED

#include <boost/fusion/iterator/deref.hpp>

namespace boost { namespace fusion
{
    struct segmented_iterator_tag;

    namespace extension
    {
        template<typename Tag>
        struct deref_impl;

        //auto deref(it)
        //{
        //  return deref(begin(car(it.nodes)))
        //}
        template<>
        struct deref_impl<segmented_iterator_tag>
        {
            template<typename It>
            struct apply
            {
                typedef
                    typename result_of::deref<
                        typename It::nodes_type::car_type::begin_type
                    >::type
                type;

                static type call(It const& it)
                {
                    return *it.nodes.car.first;
                }
            };
        };

    }
}}

#endif
