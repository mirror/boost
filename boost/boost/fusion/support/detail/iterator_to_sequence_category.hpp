/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ITERATOR_TO_SEQUENCE_CATEGORY_07212005_0726)
#define FUSION_ITERATOR_TO_SEQUENCE_CATEGORY_07212005_0726

namespace boost { namespace fusion
{
    struct incrementable_traversal_tag;
    struct single_pass_traversal_tag;
    struct forward_traversal_tag;
    struct bidirectional_traversal_tag;
    struct random_access_traversal_tag;

    struct incrementable_sequence_tag;
    struct single_pass_sequence_tag;
    struct forward_sequence_tag;
    struct bidirectional_sequence_tag;
    struct random_access_sequence_tag;
}}
    
namespace boost { namespace fusion { namespace detail
{
    template <typename Category>
    struct iterator_to_sequence_category;
    
    template <>
    struct iterator_to_sequence_category<incrementable_traversal_tag>
    {
        typedef incrementable_sequence_tag type;
    };

    template <>
    struct iterator_to_sequence_category<single_pass_traversal_tag>
    {
        typedef single_pass_sequence_tag type;
    };

    template <>
    struct iterator_to_sequence_category<forward_traversal_tag>
    {
        typedef forward_sequence_tag type;
    };

    template <>
    struct iterator_to_sequence_category<bidirectional_traversal_tag>
    {
        typedef bidirectional_sequence_tag type;
    };

    template <>
    struct iterator_to_sequence_category<random_access_traversal_tag>
    {
        typedef random_access_sequence_tag type;
    };
}}}

#endif
