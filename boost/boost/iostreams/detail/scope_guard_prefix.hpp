// Copyright (C) 2003-2004 Joaquín M López Muñoz.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// From <boost/multi_index/ordered_index.hpp>.

#include <boost/detail/workaround.hpp>

// The "ISO C++ Template Parser" option in CW8.3 has a problem with the
// ifetime of const references bound to temporaries -- precisely what
// scopeguards are.
#if BOOST_WORKAROUND(__MWERKS__, <= 0x3003)
# pragma parse_func_templ off
# pragma parse_mfunc_templ off
#endif
