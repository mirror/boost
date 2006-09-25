/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_STD_PAIR_ITERATOR_09262005_0934)
#define FUSION_STD_PAIR_ITERATOR_09262005_0934

//~ #include <boost/fusion/support/iterator_base.hpp>
//~ #include <boost/fusion/sequence/adapted/std_pair/detail/advance_impl.hpp>
//~ #include <boost/fusion/sequence/adapted/std_pair/detail/deref_impl.hpp>
//~ #include <boost/fusion/sequence/adapted/std_pair/detail/distance_impl.hpp>
//~ #include <boost/fusion/sequence/adapted/std_pair/detail/equal_to_impl.hpp>
//~ #include <boost/fusion/sequence/adapted/std_pair/detail/next_impl.hpp>
//~ #include <boost/fusion/sequence/adapted/std_pair/detail/prior_impl.hpp>
//~ #include <boost/fusion/sequence/adapted/std_pair/detail/value_of_impl.hpp>
//~ #include <boost/type_traits/add_const.hpp>



#include <boost/fusion/iterator/iterator_facade.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/minus.hpp>
#include <utility>

namespace boost { namespace fusion
{
    struct random_access_traversal_tag;

    template <typename Pair, int N>
    struct std_pair_iterator
        : iterator_facade<std_pair_iterator<Pair, N>, random_access_traversal_tag>
    {
        BOOST_MPL_ASSERT_RELATION(N, >=, 0);
        BOOST_MPL_ASSERT_RELATION(N, <=, 2);

        typedef mpl::int_<N> index;
        typedef Pair pair_type;

        std_pair_iterator(Pair& pair)
            : pair(pair) {}
        Pair& pair;

        template <typename Iterator>
        struct value_of;

        template <typename Pair_>
        struct value_of<std_pair_iterator<Pair_, 0> >
            : mpl::identity<typename Pair_::first_type> {};

        template <typename Pair_>
        struct value_of<std_pair_iterator<Pair_, 1> >
            : mpl::identity<typename Pair_::second_type> {};

        template <typename Iterator>
        struct deref;

        template <typename Pair_>
        struct deref<std_pair_iterator<Pair_, 0> >
        {
            typedef typename
                mpl::if_<
                    is_const<Pair_>
                  , typename Pair_::first_type const&
                  , typename Pair_::first_type&
                >::type
            type;

            static type
            call(std_pair_iterator<Pair_, 0> const& iter)
            {
                return iter.pair.first;
            }
        };

        template <typename Pair_>
        struct deref<std_pair_iterator<Pair_, 1> >
        {
            typedef typename
                mpl::if_<
                    is_const<Pair_>
                  , typename Pair_::second_type const&
                  , typename Pair_::second_type&
                >::type
            type;

            static type
            call(std_pair_iterator<Pair_, 1> const& iter)
            {
                return iter.pair.second;
            }
        };

        template <typename Iterator, typename N>
        struct advance
        {
            typedef typename Iterator::index index;
            typedef typename Iterator::pair_type pair_type;
            typedef std_pair_iterator<pair_type, index::value + N::value> type;

            static type
            call(Iterator const& iter)
            {
                return type(iter.pair);
            }
        };

        template <typename Iterator>
        struct next : advance<Iterator, mpl::int_<1> > {};

        template <typename Iterator>
        struct prior : advance<Iterator, mpl::int_<-1> > {};

        template <typename I1, typename I2>
        struct distance : mpl::minus<typename I2::index, typename I1::index>
        {
            typedef typename
                mpl::minus<
                    typename I2::index, typename I1::index
                >::type 
            type;

            static type
            call(I1 const&, I2 const&)
            {
                return type();
            }
        };
    };
}}

#endif


