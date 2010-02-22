/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_DETAIL_CLASS_SIZE_IMPL_HPP
#define BOOST_FUSION_ADAPTED_DETAIL_CLASS_SIZE_IMPL_HPP

#include <boost/fusion/adapted/struct/detail/size_impl.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct size_impl;

    template <>
    struct size_impl<class_tag>
      : size_impl<struct_tag>
    {};

    template <>
    struct size_impl<assoc_class_tag>
      : size_impl<assoc_struct_tag>
    {};
}}}

#endif
