/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_END_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_END_HPP_INCLUDED

#include <boost/fusion/container/list/cons.hpp>
#include <boost/fusion/view/ext_/detail/end_impl.hpp>

namespace boost { namespace fusion
{
    template<typename Nodes>
    struct segmented_iterator;

    //auto segmented_end( rng )
    //{
    //    return make_segmented_iterator( segmented_end_impl( rng ) );
    //}

    template<typename Range>
    struct segmented_end
    {
        typedef
            segmented_iterator<
                typename detail::segmented_end_impl<Range, fusion::nil>::type
            >
        type;

        static type call(Range & rng)
        {
            return type(
                detail::segmented_end_impl<Range, fusion::nil>::call(rng, fusion::nil()));
        }
    };

}}

#endif
