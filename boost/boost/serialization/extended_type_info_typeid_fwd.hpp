#ifndef BOOST_SERIALIZATION_EXTENDED_TYPE_INFO_TYPEID_FWD_HPP
#define BOOST_SERIALIZATION_EXTENDED_TYPE_INFO_TYPEID_FWD_HPP
/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

// extended_type_info_typeid.hpp: implementation for version that depends
// on runtime typing (rtti - typeid) but uses a user specified string
// as the portable class identifier.

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

namespace boost {
namespace serialization {

///////////////////////////////////////////////////////////////////////////////
template<class T>
class extended_type_info_typeid;

} // namespace serialization
} // namespace boost

///////////////////////////////////////////////////////////////////////////////
// If no other implementation has been designated as default, 
// use this one.  To use this implementation as the default, specify it
// before any of the other headers.

#ifndef BOOST_SERIALIZATION_DEFAULT_TYPE_INFO
#define BOOST_SERIALIZATION_DEFAULT_TYPE_INFO(T) \
    extended_type_info_typeid<const T>
/**/
#endif

#endif // BOOST_SERIALIZATION_EXTENDED_TYPE_INFO_TYPEID_FWD_HPP
