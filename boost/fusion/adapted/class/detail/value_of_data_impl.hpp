/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_DETAIL_CLASS_VALUE_OF_DATA_IMPL_HPP
#define BOOST_FUSION_ADAPTED_DETAIL_CLASS_VALUE_OF_DATA_IMPL_HPP

#include <boost/fusion/adapted/struct/detail/value_of_data_impl.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_data_impl;

    template <>
    struct value_of_data_impl<assoc_class_iterator_tag>
      : value_of_data_impl<assoc_struct_iterator_tag>
    {};
}}}

#endif
