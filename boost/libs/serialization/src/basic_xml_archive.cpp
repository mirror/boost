/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// xml_archive.cpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#define BOOST_ARCHIVE_SOURCE
#include <boost/archive/basic_xml_archive.hpp>

namespace boost {
namespace archive {

#if defined(BOOST_MSVC) || defined(BOOST_INTEL_WIN) || defined(__MWERKS__)
BOOST_DECL_ARCHIVE 
const char *
#else
const char *
BOOST_DECL_ARCHIVE 
#endif
OBJECT_ID(){
    return "object_id";
}
#if defined(BOOST_MSVC) || defined(BOOST_INTEL_WIN) || defined(__MWERKS__)
BOOST_DECL_ARCHIVE 
const char *
#else
const char *
BOOST_DECL_ARCHIVE 
#endif
OBJECT_REFERENCE(){
    return "object_id_reference";
}
#if defined(BOOST_MSVC) || defined(BOOST_INTEL_WIN) || defined(__MWERKS__)
BOOST_DECL_ARCHIVE 
const char *
#else
const char *
BOOST_DECL_ARCHIVE 
#endif
CLASS_ID(){
    return "class_id";
}
#if defined(BOOST_MSVC) || defined(BOOST_INTEL_WIN) || defined(__MWERKS__)
BOOST_DECL_ARCHIVE 
const char *
#else
const char *
BOOST_DECL_ARCHIVE 
#endif
CLASS_ID_REFERENCE(){
    return "class_id_reference";
}
#if defined(BOOST_MSVC) || defined(BOOST_INTEL_WIN) || defined(__MWERKS__)
BOOST_DECL_ARCHIVE 
const char *
#else
const char *
BOOST_DECL_ARCHIVE 
#endif
CLASS_NAME(){
    return "class_name";
}
#if defined(BOOST_MSVC) || defined(BOOST_INTEL_WIN) || defined(__MWERKS__)
BOOST_DECL_ARCHIVE 
const char *
#else
const char *
BOOST_DECL_ARCHIVE 
#endif
TRACKING(){
    return "tracking_level";
}
#if defined(BOOST_MSVC) || defined(BOOST_INTEL_WIN) || defined(__MWERKS__)
BOOST_DECL_ARCHIVE 
const char *
#else
const char *
BOOST_DECL_ARCHIVE 
#endif
VERSION(){
    return "version";
}
#if defined(BOOST_MSVC) || defined(BOOST_INTEL_WIN) || defined(__MWERKS__)
BOOST_DECL_ARCHIVE 
const char *
#else
const char *
BOOST_DECL_ARCHIVE 
#endif
SIGNATURE(){
    return "signature";
}

}// namespace archive
}// namespace boost
