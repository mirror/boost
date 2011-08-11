/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_POP_BACK_09172005_1038)
#define FUSION_POP_BACK_09172005_1038

#include <boost/fusion/view/iterator_range/iterator_range.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/empty.hpp>
#include <boost/fusion/iterator/iterator_adapter.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace fusion
{
    template <typename Iterator_>
    struct pop_back_iterator
        : iterator_adapter<
            pop_back_iterator<Iterator_>
          , Iterator_>
    {
        typedef iterator_adapter<
            pop_back_iterator<Iterator_>
          , Iterator_>
        base_type;

        pop_back_iterator(Iterator_ const& iterator_base)
            : base_type(iterator_base) {}

        template <typename BaseIterator>
        struct make
        {
            typedef pop_back_iterator<BaseIterator> type;

            static type
            call(BaseIterator const& i)
            {
                return type(i);
            }
        };

        template <typename I1, typename I2>
        struct equal_to
            : result_of::equal_to<
                typename result_of::next<
                    typename I1::iterator_base_type>::type
              , typename I2::iterator_base_type
            >
        {};

        template <typename First, typename Last>
        struct distance
            : mpl::minus<
                typename result_of::distance<
                    typename First::iterator_base_type
                  , typename Last::iterator_base_type
                >::type
              , mpl::int_<1>
            >::type
        {};
    };

    namespace result_of
    {
        template <typename Sequence>
        struct pop_back
        {
            BOOST_MPL_ASSERT_NOT((result_of::empty<Sequence>));

            typedef pop_back_iterator<
                typename begin<Sequence>::type>
            begin_type;

            typedef pop_back_iterator<
                typename end<Sequence>::type>
            end_type;

            typedef
                iterator_range<begin_type, end_type>
            type;
        };
    }

    template <typename Sequence>
    inline typename result_of::pop_back<Sequence const>::type
    pop_back(Sequence const& seq)
    {
        typedef result_of::pop_back<Sequence const> comp;
        typedef typename comp::begin_type begin_type;
        typedef typename comp::end_type end_type;
        typedef typename comp::type result;

        return result(
            begin_type(fusion::begin(seq))
          , end_type(fusion::end(seq))
        );
    }
}}

#endif

