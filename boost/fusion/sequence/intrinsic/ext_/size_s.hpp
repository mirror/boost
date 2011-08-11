/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SIZE_S_08112006_1141)
#define BOOST_FUSION_SIZE_S_08112006_1141

#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/fusion/mpl.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/sequence/intrinsic/ext_/segments.hpp>
#include <boost/fusion/support/ext_/is_segmented.hpp>

namespace boost { namespace fusion
{
    ///////////////////////////////////////////////////////////////////////////
    // calculates the size of any segmented data structure.
    template<typename Sequence>
    struct segmented_size;

    namespace detail
    {
        ///////////////////////////////////////////////////////////////////////////
        template<typename Sequence, bool IsSegmented = traits::is_segmented<Sequence>::value>
        struct segmented_size_impl
          : mpl::fold<
                typename remove_reference<
                    typename add_const<
                        typename result_of::segments<Sequence>::type
                    >::type
                >::type,
                mpl::size_t<0>,
                mpl::plus<mpl::_1, segmented_size<mpl::_2> >
            >::type
        {};

        template<typename Sequence>
        struct segmented_size_impl<Sequence, false>
          : result_of::size<Sequence>::type
        {};
    }

    template<typename Sequence>
    struct segmented_size
      : detail::segmented_size_impl<Sequence>
    {};

}}

#endif
