/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_EXAMPLE_STRUCT_ITERATOR)
#define BOOST_FUSION_EXAMPLE_STRUCT_ITERATOR

#include <boost/fusion/support/iterator_base.hpp>
#include <boost/mpl/int.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/static_assert.hpp>

#include "./detail/next_impl.hpp"
#include "./detail/prior_impl.hpp"
#include "./detail/deref_impl.hpp"
#include "./detail/advance_impl.hpp"
#include "./detail/distance_impl.hpp"
#include "./detail/value_of_impl.hpp"
#include "./detail/equal_to_impl.hpp"

namespace boost { namespace fusion {
    
    struct example_struct_iterator_tag;
    struct random_access_traversal_tag;

    template<typename Struct, int Pos>
    struct example_struct_iterator
        : iterator_base<example_struct_iterator<Struct, Pos> >
    {
        BOOST_STATIC_ASSERT(Pos >=0 && Pos < 3);
        typedef Struct struct_type;
        typedef mpl::int_<Pos> index;
        typedef example_struct_iterator_tag fusion_tag;
        typedef random_access_traversal_tag category;

        example_struct_iterator(Struct& str)
            : struct_(str) {}

        Struct& struct_;
    };
}}

#endif
