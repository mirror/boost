#ifndef BOOST_ARCHIVE_TMPDIR_HPP
#define BOOST_ARCHIVE_TMPDIR_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// codecvt_null.hpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

namespace boost {
namespace archive {

const char * tmpdir(){
    char *dirname;
    dirname = getenv("TMP");
    if(NULL == dirname)
        dirname = getenv("TMPDIR");
    if(NULL == dirname)
        dirname = getenv("TEMP");
    if(NULL == dirname)
        dirname = "/tmp";
	return dirname;
}

} // archive
} // boost

#endif // BOOST_ARCHIVE_TMPDIR_HPP
