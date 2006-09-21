/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_ARRAY_ITERATOR_26122005_2250)
#define BOOST_FUSION_ARRAY_ITERATOR_26122005_2250

#include <cstddef>

#include <boost/config.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/add_const.hpp>

#include <boost/fusion/support/iterator_base.hpp>
#include <boost/fusion/sequence/adapted/array/detail/next_impl.hpp>
#include <boost/fusion/sequence/adapted/array/detail/prior_impl.hpp>
#include <boost/fusion/sequence/adapted/array/detail/advance_impl.hpp>
#include <boost/fusion/sequence/adapted/array/detail/deref_impl.hpp>
#include <boost/fusion/sequence/adapted/array/detail/value_of_impl.hpp>
#include <boost/fusion/sequence/adapted/array/detail/distance_impl.hpp>
#include <boost/fusion/sequence/adapted/array/detail/equal_to_impl.hpp>

namespace boost { namespace fusion {

    struct array_iterator_tag;
    struct random_access_traversal_tag;

    template<typename Array, std::size_t Pos>
    struct array_iterator
        : iterator_base<array_iterator<Array, Pos> >
    {
        BOOST_MPL_ASSERT_RELATION(Pos,>=,0);
        BOOST_MPL_ASSERT_RELATION(Pos,<=,std::size_t(Array::static_size));

        typedef mpl::size_t<Pos> index;
        typedef array_iterator_tag fusion_tag;
        typedef random_access_traversal_tag category;
        typedef Array array_type;
        typedef array_iterator<
            typename add_const<Array>::type, Pos> identity;

        array_iterator(Array& a)
            : array(a) {}

        Array& array;
    private:
        array_iterator<Array, Pos> operator=(const array_iterator<Array, Pos>&);
    };
}}

#endif
