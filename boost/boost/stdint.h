 //  boost stdint.h header file  ---------------------------------------------//

//  (C) Copyright boost.org 1999. Permission to copy, use, modify, sell
//  and distribute this software is granted provided this copyright
//  notice appears in all copies. This software is provided "as is" without
//  express or implied warranty, and with no claim as to its suitability for
//  any purpose.

//  See http://www.boost.org for most recent version including documentation.

//  NOTE WELL: C++ programs are advised to use <boost/cstdint.hpp> rather than
//  this header.

//  Revision History
//   22 Sep 00  64-bit support for Borland & Microsoft compilers (John Maddock)
//    8 Aug 99  Initial version (Beman Dawes)

#ifndef BOOST_STDINT_H
#define BOOST_STDINT_H

#include <boost/config.hpp>

#ifdef BOOST_SYSTEM_HAS_STDINT_H
#include <stdint.h>

#else

//  This is not a complete implementation of the 1999 C Standard stdint.h
//  header; it doesn't supply various macros which are not advisable for use in
//  C++ programs.

#include <limits.h> // implementation artifact; not part of interface

//  These are fairly safe guesses for some 16-bit, and most 32-bit and 64-bit
//  platforms.  For other systems, they will have to be hand tailored.
//  Because the fast types are assumed to be the same as the undecorated types,
//  it may be possible to hand tailor a more efficient implementation.

//  8-bit types  -------------------------------------------------------------//

# if UCHAR_MAX == 0xff
     typedef signed char     int8_t;
     typedef signed char     int_least8_t;
     typedef signed char     int_fast8_t;
     typedef unsigned char   uint8_t;
     typedef unsigned char   uint_least8_t;
     typedef unsigned char   uint_fast8_t;
# else
#    error defaults not correct; you must hand modify boost/stdint.hpp
# endif

//  16-bit types  ------------------------------------------------------------//

# if USHRT_MAX == 0xffff
     typedef short           int16_t;
     typedef short           int_least16_t;
     typedef short           int_fast16_t;
     typedef unsigned short  uint16_t;
     typedef unsigned short  uint_least16_t;
     typedef unsigned short  uint_fast16_t;
# else
#    error defaults not correct; you must hand modify boost/stdint.hpp
# endif

//  32-bit types  ------------------------------------------------------------//

# if UINT_MAX == 0xffffffff
     typedef int             int32_t;
     typedef int             int_least32_t;
     typedef int             int_fast32_t;
     typedef unsigned int    uint32_t;
     typedef unsigned int    uint_least32_t;
     typedef unsigned int    uint_fast32_t;
# elif ULONG_MAX == 0xffffffff
     typedef long            int32_t;
     typedef long            int_least32_t;
     typedef long            int_fast32_t;
     typedef unsigned long   uint32_t;
     typedef unsigned long   uint_least32_t;
     typedef unsigned long   uint_fast32_t;
# else
#    error defaults not correct; you must hand modify boost/stdint.hpp
# endif

//  64-bit types + intmax_t and uintmax_t  -----------------------------------//

# if defined(ULLONG_MAX) || defined(ULONG_LONG_MAX)
#    if (defined(ULLONG_MAX) && ULLONG_MAX == 18446744073709551615) ||  \
        (defined(ULONG_LONG_MAX) && ULONG_LONG_MAX == 18446744073709551615)
                                                                 // 2**64 - 1
     typedef long long            intmax_t;
     typedef unsigned long long   uintmax_t;
     typedef long long            int64_t;
     typedef long long            int_least64_t;
     typedef long long            int_fast64_t;
     typedef unsigned long long   uint64_t;
     typedef unsigned long long   uint_least64_t;
     typedef unsigned long long   uint_fast64_t;
#    else
#       error defaults not correct; you must hand modify boost/stdint.hpp
#    endif
# elif ULONG_MAX != 0xffffffff

#    if ULONG_MAX == 18446744073709551615 // 2**64 - 1
     typedef long                 intmax_t;
     typedef unsigned long        uintmax_t;
     typedef long                 int64_t;
     typedef long                 int_least64_t;
     typedef long                 int_fast64_t;
     typedef unsigned long        uint64_t;
     typedef unsigned long        uint_least64_t;
     typedef unsigned long        uint_fast64_t;
#    else
#       error defaults not correct; you must hand modify boost/stdint.hpp
#    endif
# elif (defined(BOOST_MSVC) && (BOOST_MSVC >= 1100)) || (defined(__BORLANDC__) && (__BORLANDC__ >= 0x520))
     //
     // we have Borland/Microsoft __int64:
     //
     typedef __int64             intmax_t;
     typedef unsigned __int64    uintmax_t;
     typedef __int64             int64_t;
     typedef __int64             int_least64_t;
     typedef __int64             int_fast64_t;
     typedef unsigned __int64    uint64_t;
     typedef unsigned __int64    uint_least64_t;
     typedef unsigned __int64    uint_fast64_t;
# else // assume no 64-bit integers
#define BOOST_NO_INT64_T
     typedef int32_t              intmax_t;
     typedef uint32_t             uintmax_t;
# endif

#endif  // BOOST_SYSTEM_HAS_STDINT_H not defined
#endif  // BOOST_STDINT_H
