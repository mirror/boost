/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_archive.cpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

//////////////////////////////////////////////////////////////////////
//
//  objects are stored as
//
//      class_id*   // -1 for a null pointer
//      if a new class id
//      [
//          exported key - class name*
//          tracking level - always/never
//          file version
//      ]
//
//      if tracking
//      [
//          object_id
//      ]
//          
//      [   // if a new object id
//          data...
//      ]
//
//  * required only for pointers - optional for objects

#define BOOST_ARCHIVE_SOURCE
#include <boost/archive/basic_archive.hpp>

namespace boost {
namespace archive {

///////////////////////////////////////////////////////////////////////
// constants used in archive signature
//This should never ever change. note that is not an std::string
// string.
#if defined(BOOST_MSVC)
    BOOST_DECL_ARCHIVE 
    const char * 
#else
    const char * 
    BOOST_DECL_ARCHIVE 
#endif
ARCHIVE_SIGNATURE(){
    return "serialization::archive";
}

// this should change if the capabilities are added to the library
// such that archives can be created which can't be read by previous
// versions of this library
// 1 - initial version
// 2 - made address tracking optional
// 3 - numerous changes - can't guarentee compatibility with previous versions
unsigned char 
BOOST_DECL_ARCHIVE 
ARCHIVE_VERSION(){
    return 3;
}

} // namespace archive
} // namespace boost
