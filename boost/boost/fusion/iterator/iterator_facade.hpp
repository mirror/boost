/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ITERATOR_FACADE_09252006_1011)
#define FUSION_ITERATOR_FACADE_09252006_1011

#include <boost/fusion/support/iterator_base.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace fusion
{
    struct iterator_facade_tag;

    template <typename Derived, typename Category>
    struct iterator_facade : iterator_base<Derived>
    {
        typedef iterator_facade_tag fusion_tag;
        typedef Derived derived_type;
        typedef Category category;

        template <typename I1, typename I2>
        struct equal_to // default implementation
            : is_same<
                typename I1::derived_type
              , typename I2::derived_type
            >
        {};
    };
}}

#endif
