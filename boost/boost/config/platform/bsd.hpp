//  (C) Copyright Boost.org 2001. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for most recent version.

//  generic BSD config options:

#if !defined(__FreeBSD__) && !defined(__NetBSD__) && !defined(__OpenBSD__)
#error "This platform is not BSD"
#endif

#ifdef __FreeBSD__
#define BOOST_PLATFORM "FreeBSD " BOOST_STRINGIZE(__FreeBSD__)
#elif defined(__NetBSD__)
#define BOOST_PLATFORM "NetBSD " BOOST_STRINGIZE(__NetBSD__)
#elif defined(__OpenBSD__)
#define BOOST_PLATFORM "OpenBSD " BOOST_STRINGIZE(__OpenBSD__)
#endif

//
// is this the correct version check?
// FreeBSD has <nl_type.h> but does not
// advertise the fact in <unistd.h>:
//
#if defined(__FreeBSD__) && (__FreeBSD__ >= 4)
#  define BOOST_HAS_NL_TYPES_H
#endif

//
// No wide character support in the BSD header files:
//
#define BOOST_NO_CWCHAR

//
// The BSD <ctype.h> has macros only, no functions:
//
#define BOOST_NO_CTYPE_FUNCTIONS
