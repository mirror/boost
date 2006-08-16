/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_STD_PAIR_ITERATOR_09262005_0934)
#define FUSION_STD_PAIR_ITERATOR_09262005_0934

#include <boost/fusion/support/iterator_base.hpp>
#include <boost/fusion/sequence/adapted/std_pair/detail/advance_impl.hpp>
#include <boost/fusion/sequence/adapted/std_pair/detail/deref_impl.hpp>
#include <boost/fusion/sequence/adapted/std_pair/detail/distance_impl.hpp>
#include <boost/fusion/sequence/adapted/std_pair/detail/equal_to_impl.hpp>
#include <boost/fusion/sequence/adapted/std_pair/detail/next_impl.hpp>
#include <boost/fusion/sequence/adapted/std_pair/detail/prior_impl.hpp>
#include <boost/fusion/sequence/adapted/std_pair/detail/value_of_impl.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace fusion
{
    struct std_pair_iterator_tag;
    struct random_access_traversal_tag;

    template <typename Pair, int N>
    struct std_pair_iterator_identity;

    template <typename Pair, int N>
    struct std_pair_iterator
        : iterator_base<std_pair_iterator<Pair, N> >
    {
        typedef mpl::int_<N> index;
        typedef std_pair_iterator_tag ftag;
        typedef random_access_traversal_tag category;
        typedef std_pair_iterator_identity<
            typename add_const<Pair>::type, N> identity;
        typedef Pair pair_type;

        std_pair_iterator(Pair& pair)
            : pair(pair) {}
        Pair& pair;
    };
}}

#endif


