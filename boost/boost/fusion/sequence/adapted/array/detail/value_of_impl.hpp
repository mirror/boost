/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_VALUE_OF_IMPL_27122005_1011)
#define BOOST_FUSION_VALUE_OF_IMPL_27122005_1011

namespace boost { namespace fusion
{
    struct array_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        template <>
        struct value_of_impl<array_iterator_tag>
        {
            template <typename Iterator>
            struct apply 
            {
                typedef typename Iterator::array_type array_type;
                typedef typename array_type::value_type type;
            };
        };
    }
}}

#endif
