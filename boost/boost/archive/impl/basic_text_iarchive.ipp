/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_text_iarchive.ipp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . Permission to copy, 
// use, modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided "as is"
// without express or ied warranty, and with no claim as to its suitability
// for any purpose.

//  See http://www.boost.org for updates, documentation, and revision history.

#include <string>
#include <cassert>
#include <algorithm>
#include <cstring>

#include <boost/config.hpp> // for BOOST_DEDUCED_TYPENAME
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{ 
    using ::memcpy; 
}
#endif

#include <boost/archive/basic_text_iarchive.hpp>

namespace boost {
namespace archive {

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// implementation of text_text_archive
template<class Archive>
void basic_text_iarchive<Archive>::load_override(class_name_type & t, int){
    std::string cn;
    cn.reserve(BOOST_SERIALIZATION_MAX_KEY_SIZE);
    load_override(cn, 0);
    if(cn.size() > (BOOST_SERIALIZATION_MAX_KEY_SIZE - 1))
        boost::throw_exception(
            archive_exception(archive_exception::invalid_class_name)
        );
    std::memcpy(t, cn.data(), cn.size());
    // borland tweak
    t.t[cn.size()] = '\0';
}

} // namespace archive
} // namespace boost
