/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_POP_BACK_09172005_1038)
#define FUSION_POP_BACK_09172005_1038

#include <boost/fusion/view/iterator_range/iterator_range.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/iterator/iterator_facade.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace fusion
{
    template <typename Iterator_>
    struct pop_back_iterator
        : iterator_facade<
            pop_back_iterator<Iterator_>
          , typename Iterator_::category>
    {
        typedef Iterator_ base_type;
        base_type base;

        pop_back_iterator(base_type const& base)
            : base(base) {}

        template <typename I1, typename I2>
        struct equal_to
            : is_same<
                typename result_of::next<
                    typename I1::base_type>::type
              , typename I2::base_type
            >
        {};

        template <typename Iterator, typename N>
        struct advance
            : pop_back_iterator<
                typename result_of::advance<
                    typename Iterator::base_type, N>::type
            >
        {
        };

        template <typename First, typename Last>
        struct distance
            : mpl::minus<
                typename result_of::distance<
                    typename First::base_type
                  , typename Last::base_type
                >::type
              , mpl::int_<1>
            >::type
        {};

        template <typename Iterator>
        struct value_of
            : result_of::value_of<typename Iterator::base_type> {};

        template <typename Iterator>
        struct deref
        {
            typedef typename
                result_of::deref<typename Iterator::base_type>::type
            type;

            static type
            call(Iterator const& it)
            {
                return fusion::deref(it.base);
            }
        };

        template <typename Iterator>
        struct next
        {
            typedef pop_back_iterator<
                typename result_of::next<
                    typename Iterator::base_type
                >::type>
            type;

            static type
            call(Iterator const& i)
            {
                return fusion::next(i.base);
            }
        };

        template <typename Iterator>
        struct prior
        {
            typedef pop_back_iterator<
                typename result_of::prior<
                    typename Iterator::base_type
                >::type>
            type;

            static type
            call(Iterator const& i)
            {
                return fusion::prior(i.base);
            }
        };
    };

    namespace result_of
    {
        template <typename Sequence>
        struct pop_back
        {
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

