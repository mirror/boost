/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// pointer_iserializer.ipp: 

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <utility>
#include <cassert>
#include <cstddef>
#include <boost/config.hpp> // msvc 6.0 needs this for warning suppression
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{ 
    using ::size_t; 
} // namespace std
#endif

#include <boost/serialization/singleton.hpp>
#include <boost/archive/detail/basic_serializer_map.hpp>
#include <boost/archive/detail/archive_pointer_iserializer.hpp>

namespace boost { 
namespace archive {
namespace detail {

template<class Archive>
basic_serializer_map archive_pointer_iserializer<Archive>::m_map;

template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(BOOST_PP_EMPTY())
archive_pointer_iserializer<Archive>::archive_pointer_iserializer(
    const boost::serialization::extended_type_info & eti
) :
    basic_pointer_iserializer(eti)
{
    // only insert the first one.  Assumes that DLLS are unloaded in
    // the reverse sequence
    // std::pair<
    //    BOOST_DEDUCED_TYPENAME basic_serializer_map<Archive>::iterator, 
    //    bool
    // > result =
    m_map.insert(this);
}

template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(const basic_pointer_iserializer *) 
archive_pointer_iserializer<Archive>::find(
    const boost::serialization::extended_type_info & eti
){
    const basic_serializer_arg bs(eti);
    basic_serializer_map::const_iterator it;
    it = m_map.find(& bs);
    assert(it != m_map.end());
    return static_cast<const basic_pointer_iserializer *>(*it);
}

template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(BOOST_PP_EMPTY())
archive_pointer_iserializer<Archive>::~archive_pointer_iserializer(){
    basic_serializer_map::iterator it;
    it = m_map.find(this);
    assert(it != m_map.end());
    if(*it == static_cast<const basic_serializer *>(this))
        m_map.erase(it);
}

} // namespace detail
} // namespace archive
} // namespace boost
