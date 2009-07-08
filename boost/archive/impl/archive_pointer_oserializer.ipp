/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// archive_pointer_oserializer.ipp: 

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <utility>
#include <cassert>

#include <boost/config.hpp> // msvc 6.0 needs this for warning suppression

#include <boost/archive/detail/archive_pointer_oserializer.hpp>
#include <boost/archive/detail/basic_serializer_map.hpp>
#include <boost/serialization/singleton.hpp>

namespace boost { 
namespace archive {
namespace detail {

template<class Archive>
basic_serializer_map archive_pointer_oserializer<Archive>::m_map;

template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(BOOST_PP_EMPTY())
archive_pointer_oserializer<Archive>::archive_pointer_oserializer(
    const boost::serialization::extended_type_info & eti
) :
    basic_pointer_oserializer(eti)
{
    // only insert the first one.  Assumes that DLLS are unloaded in
    // the reverse sequence
    //std::pair<
    //    BOOST_DEDUCED_TYPENAME  oserializer_map<Archive>::iterator, 
    //    bool
    // > result =
    m_map.insert(this);
}

template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(const basic_pointer_oserializer *) 
archive_pointer_oserializer<Archive>::find(
    const boost::serialization::extended_type_info & eti
){
    const basic_serializer_arg bs(eti);
    basic_serializer_map::const_iterator it;
    it =  m_map.find(& bs);
    assert(it != m_map.end());
    return static_cast<const basic_pointer_oserializer *>(*it);
}

template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(BOOST_PP_EMPTY())
archive_pointer_oserializer<Archive>::~archive_pointer_oserializer(){
    basic_serializer_map::iterator it;
    it = m_map.find(this);
    assert(it != m_map.end());
    if(*it == static_cast<const basic_serializer *>(this))
        m_map.erase(it);
}

} // namespace detail
} // namespace archive
} // namespace boost
