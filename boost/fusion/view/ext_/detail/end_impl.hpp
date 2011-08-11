/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_END_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_END_IMPL_HPP_INCLUDED

#include <boost/mpl/assert.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/fusion/view/iterator_range.hpp>
#include <boost/fusion/container/list/cons.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/ext_/segments.hpp>
#include <boost/fusion/support/ext_/is_segmented.hpp>

namespace boost { namespace fusion { namespace detail
{
    //auto segmented_end_impl( rng, stack )
    //{
    //    assert(is_segmented(rng));
    //    auto it = end(segments(rng));
    //    return cons(iterator_range(it, it), stack);
    //}

    template<typename Range, typename Stack>
    struct segmented_end_impl
    {
        BOOST_MPL_ASSERT((traits::is_segmented<Range>));

        typedef
            typename result_of::end<
                typename remove_reference<
                    typename add_const<
                        typename result_of::segments<Range>::type
                    >::type
                >::type
            >::type
        end_type;

        typedef iterator_range<end_type, end_type>  pair_type;
        typedef cons<pair_type, Stack>              type;

        static type call(Range & rng, Stack stack)
        {
            end_type end = fusion::end(fusion::segments(rng));
            return type(pair_type(end, end), stack);
        }
    };

}}}

#endif
