/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library
    http://www.boost.org/

    Copyright (c) 2001-2005 Hartmut Kaiser. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

// Tests, whether invalid expression errors get ignored for 'passive' #elif 
// expressions
#define USHRT_MAX 0xffffU

// The number of bytes in a short.
# if !defined (SIZEOF_SHORT)
#   if (USHRT_MAX) == 255U
#     define SIZEOF_SHORT 1
#   elif (USHRT_MAX) == 65535U
#     define SIZEOF_SHORT 2
#   elif (USHRT_MAX) == 4294967295U
#     define SIZEOF_SHORT 4
#   elif (USHRT_MAX) == 18446744073709551615U  
#     define SIZEOF_SHORT 8
#   else
#     error: unsupported short size, must be updated for this platform!
#   endif /* USHRT_MAX */
# endif /* !defined (SIZEOF_SHORT) */

//R #line 32 "t_4_004.cpp"
//R true
#if SIZEOF_SHORT == 2
true
#else
false
#endif
