/*=============================================================================
    Copyright (c) 2011 Daniel James

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#if !defined(BOOST_SPIRIT_QUICKBOOK_TABLE_TAGS_HPP)
#define BOOST_SPIRIT_QUICKBOOK_TABLE_TAGS_HPP

#include "value_tags.hpp"

namespace quickbook
{
    QUICKBOOK_VALUE_TAGS(table_tags, 0x200,
        (title)(row)(cell)
    )

    QUICKBOOK_VALUE_TAGS(general_tags, 0x300,
        (element_id)
    )

}

#endif