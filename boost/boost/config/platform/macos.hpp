//  (C) Copyright Boost.org 2001. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for most recent version.

//  Mac OS specific config options:

#define BOOST_PLATFORM "Mac OS"

// If __MACH__, we're using the BSD standard C library, not the MSL:
#if defined(__MACH__)

#  define BOOST_NO_CTYPE_FUNCTIONS
#  define BOOST_NO_CWCHAR
#  ifndef BOOST_HAS_UNISTD_H
#    define BOOST_HAS_UNISTD_H
#  endif
#  ifndef BOOST_HAS_STDINT_H
#     define BOOST_HAS_STDINT_H
#  endif

#  ifndef __APPLE_CC__

// GCC strange "ignore std" mode works better if you pretend everything
// is in the std namespace, for the most part.

#    define BOOST_NO_STDC_NAMESPACE
#  endif

#endif
