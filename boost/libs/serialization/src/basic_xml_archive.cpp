/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// xml_archive.cpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#define BOOST_ARCHIVE
#include <boost/archive/basic_xml_archive.hpp>

namespace boost {
namespace archive {

BOOST_DECL_ARCHIVE const char * OBJECT_ID(){
    return "object_id";
}
BOOST_DECL_ARCHIVE const char * OBJECT_REFERENCE(){
    return "object_id_reference";
}
BOOST_DECL_ARCHIVE const char * CLASS_ID(){
    return "class_id";
}
BOOST_DECL_ARCHIVE const char * CLASS_ID_REFERENCE(){
    return "class_id_reference";
}
BOOST_DECL_ARCHIVE const char * CLASS_NAME(){
    return "class_name";
}
BOOST_DECL_ARCHIVE const char * TRACKING(){
    return "tracking_level";
}
BOOST_DECL_ARCHIVE const char * VERSION(){
    return "version";
}
BOOST_DECL_ARCHIVE const char * SIGNATURE(){
    return "signature";
}

}// namespace archive
}// namespace boost
