#ifndef BOOST_SERIALIZATION_BASIC_HELPER_HPP
#define BOOST_SERIALIZATION_BASIC_HELPER_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_helper.hpp: base class of function objects attached to archives

// (C) Copyright 2004 Robert Ramey and Martin Ecker
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

namespace boost {
namespace serialization{

class basic_helper {
public:
    virtual ~basic_helper(){}
};

} // namespace serialization
} // namespace boost

#endif // BOOST_SERIALIZATION_BASIC_HELPER_HPP
