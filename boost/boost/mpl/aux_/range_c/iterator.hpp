
#ifndef BOOST_MPL_AUX_RANGE_C_ITERATOR_HPP_INCLUDED
#define BOOST_MPL_AUX_RANGE_C_ITERATOR_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/aux_/iterator_names.hpp>

namespace boost { namespace mpl {

template< typename N >
struct rc_iter
{
    typedef aux::rc_iter_tag tag;
    typedef random_access_iterator_tag category;
    typedef N type;

    typedef rc_iter<typename next<N>::type> next;
    typedef rc_iter<typename prior<N>::type> prior;

    template< typename D >
    struct BOOST_MPL_AUX_ITERATOR_ADVANCE
    {
        typedef rc_iter<
              typename plus<N,D>::type
            > type;
    };

    template< typename U >
    struct BOOST_MPL_AUX_ITERATOR_DISTANCE
    {
        typedef typename minus<typename U::type,N>::type type;
    };
};

}}

#endif // BOOST_MPL_AUX_RANGE_C_ITERATOR_HPP_INCLUDED
