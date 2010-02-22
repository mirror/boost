/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_DETAIL_CLASS_EXTENSION_HPP
#define BOOST_FUSION_ADAPTED_DETAIL_CLASS_EXTENSION_HPP

#include <boost/fusion/adapted/struct/detail/extension.hpp>

namespace boost { namespace fusion
{
    struct class_tag;
    struct class_iterator_tag;
    struct assoc_class_tag;
    struct assoc_class_iterator_tag;

    typedef assoc_struct_category assoc_class_category;
}}

#endif
