//  (C) Copyright Boost.org 2001. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for most recent version.

//  Mac OS specific config options:

#define BOOST_PLATFORM "Mac OS"

// if __MACH__, we're using the BSD standard C library, not the MSL
#if defined(__MACH__)
#  define BOOST_HAS_UNISTD_H
#  define BOOST_NO_CWCHAR
#  define BOOST_NO_STDC_NAMESPACE
#  ifndef BOOST_HAS_STDINT_H
#     define BOOST_HAS_STDINT_H
#  endif
#endif






