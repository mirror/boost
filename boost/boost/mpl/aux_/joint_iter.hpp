
#ifndef BOOST_MPL_AUX_JOINT_ITER_HPP_INCLUDED
#define BOOST_MPL_AUX_JOINT_ITER_HPP_INCLUDED

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

#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/aux_/lambda_spec.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

namespace aux {

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template<
      typename Iterator1
    , typename LastIterator1
    , typename Iterator2
    >
struct joint_iter
{
    typedef Iterator1 base;
    typedef forward_iterator_tag category;
    typedef joint_iter<
          typename next<base>::type
        , LastIterator1
        , Iterator2
        > next;

    typedef typename deref<base>::type type;
};

template<
      typename LastIterator1
    , typename Iterator2
    >
struct joint_iter<LastIterator1,LastIterator1,Iterator2>
{
    typedef Iterator2 base;
    typedef forward_iterator_tag category;
    typedef joint_iter<
          LastIterator1
        , LastIterator1
        , typename next<base>::type
        > next;

    typedef typename deref<base>::type type;
};


#else

// forward decl. for 'joint_iter_impl'
template<
      typename Iterator1
    , typename LastIterator1
    , typename Iterator2
    >
struct joint_iter;

template< bool > struct joint_iter_impl
{
    template< 
          typename Iterator1
        , typename LastIterator1
        , typename Iterator2
        >
    struct result_
    {
        typedef Iterator1 base;
        typedef forward_iterator_tag category;
        typedef joint_iter<
              typename next<Iterator1>::type
            , LastIterator1
            , Iterator2
            > next;

        typedef typename deref<Iterator1>::type type;
    };
};

template<> struct joint_iter_impl<true>
{
    template< 
          typename Iterator1
        , typename LastIterator1
        , typename Iterator2
        >
    struct result_
    {
        typedef Iterator2 base;
        typedef forward_iterator_tag category;
        typedef joint_iter<
              LastIterator1
            , LastIterator1
            , typename next<Iterator2>::type
            > next;

        typedef typename deref<Iterator2>::type type;
    };
};


template<
      typename Iterator1
    , typename LastIterator1
    , typename Iterator2
    >
struct joint_iter
    : joint_iter_impl< is_same<Iterator1,LastIterator1>::value >
        ::template result_<Iterator1,LastIterator1,Iterator2>
{
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

} // namespace aux

BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(3, aux::joint_iter)

}}

#endif // BOOST_MPL_AUX_JOINT_ITER_HPP_INCLUDED
