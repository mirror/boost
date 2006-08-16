/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_TAGS_07212005_1031)
#define FUSION_TAGS_07212005_1031

namespace boost { namespace fusion
{
//  Iterator Classification
    struct incrementable_traversal_tag {};

    struct single_pass_traversal_tag
        : incrementable_traversal_tag {};

    struct forward_traversal_tag
        : single_pass_traversal_tag {};

    struct bidirectional_traversal_tag
        : forward_traversal_tag {};

    struct random_access_traversal_tag
        : bidirectional_traversal_tag {};

//  Sequence Classification
    struct incrementable_sequence_tag {};

    struct single_pass_sequence_tag
        : incrementable_sequence_tag {};

    struct forward_sequence_tag
        : single_pass_sequence_tag {};

    struct bidirectional_sequence_tag
        : forward_sequence_tag {};

    struct random_access_sequence_tag
        : bidirectional_sequence_tag {};

    struct associative_sequence_tag // $$$ this is no longer true $$$ 
        : forward_sequence_tag {};
}}

#endif
