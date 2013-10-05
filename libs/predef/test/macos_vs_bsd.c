/*
Copyright Redshift Software Inc. 2013
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

/*
 * OSX can masquerade as BSD when sys/param.h is previously included.
 * So we test that we only detect OSX in this combination.
 */
#include <boost/predef/os/macos.h>

#if BOOST_OS_MACOS
#   include <sys/param.h>
#   include <boost/predef/os/bsd.h>
#   if BOOST_OS_BSD
#       error "Both BOOST_OS_MACOS and BOOST_OS_BSD defined."
#   endif
#endif
