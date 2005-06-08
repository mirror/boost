/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// pointer_iserializer.ipp: 

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp> // msvc 6.0 needs this for warning suppression

#include <boost/archive/detail/basic_serializer_map.hpp>
#include <boost/archive/detail/archive_pointer_iserializer.hpp>

namespace boost { 
namespace archive {
namespace detail {

template<class Archive>
basic_serializer_map & iserializer_map(){
    static basic_serializer_map map;
    return map;
}

template<class Archive>
#if !defined(__BORLANDC__)
BOOST_DECL_ARCHIVE_OR_WARCHIVE
#endif
archive_pointer_iserializer<Archive>::archive_pointer_iserializer(
    const boost::serialization::extended_type_info & type
) :
    basic_pointer_iserializer(type)
{
    iserializer_map<Archive>().insert(this);
}

template<class Archive>
#if !defined(__BORLANDC__)
    #if defined(BOOST_MSVC) || defined(BOOST_INTEL_WIN) || defined(__MWERKS__)
        BOOST_DECL_ARCHIVE_OR_WARCHIVE
        const basic_pointer_iserializer * 
    #else
        const basic_pointer_iserializer * 
        BOOST_DECL_ARCHIVE_OR_WARCHIVE
    #endif
#else
    const basic_pointer_iserializer * 
#endif
archive_pointer_iserializer<Archive>::find(
    const boost::serialization::extended_type_info & type
){
    return static_cast<const basic_pointer_iserializer *>(
        iserializer_map<Archive>().tfind(type)
    );
}

} // namespace detail
} // namespace archive
} // namespace boost
