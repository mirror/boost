/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_MPL_ITERATOR_05052005_0731)
#define FUSION_MPL_ITERATOR_05052005_0731

#include <boost/fusion/support/iterator_base.hpp>
#include <boost/fusion/support/detail/mpl_iterator_category.hpp>
#include <boost/fusion/sequence/adapted/mpl/detail/deref_impl.hpp>
#include <boost/fusion/sequence/adapted/mpl/detail/next_impl.hpp>
#include <boost/fusion/sequence/adapted/mpl/detail/prior_impl.hpp>
#include <boost/fusion/sequence/adapted/mpl/detail/value_of_impl.hpp>
#include <boost/fusion/sequence/adapted/mpl/detail/equal_to_impl.hpp>
#include <boost/fusion/sequence/adapted/mpl/detail/distance_impl.hpp>
#include <boost/fusion/sequence/adapted/mpl/detail/advance_impl.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace fusion
{
    struct mpl_iterator_tag;

    template <typename Iterator>
    struct mpl_iterator
        : iterator_base<mpl_iterator<Iterator> >
    {
        typedef mpl_iterator_tag fusion_tag;
        typedef typename detail::mpl_iterator_category<
            typename Iterator::category>::type 
        category;
        typedef typename remove_const<Iterator>::type iterator_type;
    };
}}

#endif


