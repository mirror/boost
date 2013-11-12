/*=============================================================================
    Copyright (c) 2011,2013 Daniel James

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#if !defined(BOOST_QUICKBOOK_SYNTAX_HIGHLIGHT_HPP)
#define BOOST_QUICKBOOK_SYNTAX_HIGHLIGHT_HPP

#include "fwd.hpp"

namespace quickbook
{
    void syntax_highlight(
        parse_iterator first, parse_iterator last,
        quickbook::state& state,
        source_mode_type source_mode,
        bool is_block);
}

#endif
