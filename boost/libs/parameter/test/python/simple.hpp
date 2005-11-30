// Copyright Daniel Wallin 2005. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_SIMPLE_051130_HPP
# define BOOST_PARAMETER_SIMPLE_051130_HPP

# include <boost/parameter/python/function.hpp>
# include <boost/parameter/python/make_function.hpp>

ZKB_KEYWORD(tag, x)
ZKB_KEYWORD(tag, y)
ZKB_KEYWORD(tag, z)
ZKB_KEYWORD(tag, u)

ZKB_FUNCTION(int, add, add_meta, tag,
    (required
        (x, int)
        (y, int)
    )
    (optional
        (z, int, 0)
        (u, int, 0)
    )
);

ZKB_KEYWORD(tag, value)
ZKB_KEYWORD(tag, name)
ZKB_KEYWORD(tag, scale)

ZKB_FUNCTION(void, print, print_meta, tag,
    (required
        (value, int)
    )
    (optional
        (name, char const*, "unnamed")
        (scale, float, 1.f)
    )
);

#endif // BOOST_PARAMETER_SIMPLE_051130_HPP

