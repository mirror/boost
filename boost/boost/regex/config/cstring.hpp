/*
 *
 * Copyright (c) 1998-2002
 * Dr John Maddock
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Dr John Maddock makes no representations
 * about the suitability of this software for any purpose.  
 * It is provided "as is" without express or implied warranty.
 *
 */
 
 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         boost/regex/config/cstring.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: regex narrow character string fixes.
  */

#ifndef BOOST_REGEX_CONFIG_CSTRING_HPP
#define BOOST_REGEX_CONFIG_CSTRING_HPP

#include <cstring>
#include <cctype>
#include <boost/config.hpp>

namespace std{

#ifndef BOOST_NO_STDC_NAMESPACE
extern "C"{
#endif

// Any function that is a macro is converted into an inline function:
#ifdef memcmp
inline int (memcmp)(const void * p1, const void * p2, size_t s)
{ return memcmp(p1, p2, s); }
#undef memcmp
#elif defined(BOOST_NO_STDC_NAMESPACE)
using ::memcmp;
#endif

#ifdef memcpy
inline void *(memcpy)(void * p1, const void *p2, size_t s)
{ return memcpy(p1, p2, s); }
#undef memcpy
#elif defined(BOOST_NO_STDC_NAMESPACE)
using ::memcpy;
#endif

#ifdef memmove
inline void *(memmove)(void *, const void *, size_t)
{ return memmove(p1,p2,s); }
#undef memmove
#elif defined(BOOST_NO_STDC_NAMESPACE)
using ::memmove;
#endif

#ifdef memset
inline void *(memset)(void *p, int a, size_t b)
{ return memset(p,a,b); }
#undef memset
#elif defined(BOOST_NO_STDC_NAMESPACE)
using ::memset;
#endif

#ifdef strcat
inline char *(strcat)(char *p1, const char *p2)
{ return strcat(p1,p2); }
#undef strcat
#elif defined(BOOST_NO_STDC_NAMESPACE)
using ::strcat;
#endif

#ifdef strcmp
inline int (strcmp)(const char *p1, const char *p2)
{ return strcmp(p1,p2); }
#undef strcmp
#elif defined(BOOST_NO_STDC_NAMESPACE)
using ::strcmp;
#endif

#ifdef strcoll
inline int (strcoll)(const char *p1, const char *p2)
{ return strcoll(p1,p2); }
#undef strcoll
#elif defined(BOOST_NO_STDC_NAMESPACE)
using ::strcoll;
#endif

#ifdef strcpy
inline char *(strcpy)(char *p1, const char *p2)
{ return strcpy(p1,p2); }
#undef strcpy
#elif defined(BOOST_NO_STDC_NAMESPACE)
using ::strcpy;
#endif

#ifdef strlen
inline size_t (strlen)(const char *p)
{ return strlen(p); }
#undef strlen
#elif defined(BOOST_NO_STDC_NAMESPACE)
using ::strlen;
#endif

#ifdef strxfrm
inline size_t (strxfrm)(char *p1, const char *p2, size_t s)
{ return strxfrm(p1,p2,s); }
#undef strxfrm
#elif defined(BOOST_NO_STDC_NAMESPACE)
using ::strxfrm;
#endif

#ifdef isalnum
inline int (isalnum)(int i)
{ return isalnum(i); }
#undef isalnum
#elif defined(BOOST_NO_STDC_NAMESPACE)
using ::isalnum;
#endif

#ifdef isalpha
inline int (isalpha)(int i)
{ return isalpha(i); }
#undef isalpha
#elif defined(BOOST_NO_STDC_NAMESPACE)
using ::isalpha;
#endif

#ifdef iscntrl
inline int (iscntrl)(int i)
{ return iscntrl(i); }
#undef iscntrl
#elif defined(BOOST_NO_STDC_NAMESPACE)
using ::iscntrl;
#endif

#ifdef isdigit
inline int (isdigit)(int i)
{ return isdigit(i); }
#undef isdigit
#elif defined(BOOST_NO_STDC_NAMESPACE)
using ::isdigit;
#endif

#ifdef isgraph
inline int (isgraph)(int i)
{ return isgraph(i); }
#undef isgraph
#elif defined(BOOST_NO_STDC_NAMESPACE)
using ::isgraph;
#endif

#ifdef islower
inline int (islower)(int i)
{ return islower(i); }
#undef islower
#elif defined(BOOST_NO_STDC_NAMESPACE)
using ::islower;
#endif

#ifdef isprint
inline int (isprint)(int i)
{ return isprint(i); }
#undef isprint
#elif defined(BOOST_NO_STDC_NAMESPACE)
using ::isprint;
#endif

#ifdef ispunct
inline int (ispunct)(int i)
{ return ispunct(i); }
#undef ispunct
#elif defined(BOOST_NO_STDC_NAMESPACE)
using ::ispunct;
#endif

#ifdef isspace
inline int (isspace)(int i)
{ return isspace(i); }
#elif defined(BOOST_NO_STDC_NAMESPACE)
using ::isspace;
#endif

#ifdef isupper
inline int (isupper)(int i)
{ return isupper(i); }
#undef isupper
#elif defined(BOOST_NO_STDC_NAMESPACE)
using ::isupper;
#endif

#ifdef isxdigit
inline int (isxdigit)(int i)
{ return isxdigit(i); }
#undef isxdigit
#elif defined(BOOST_NO_STDC_NAMESPACE)
using ::isxdigit;
#endif

#ifdef tolower
inline int (tolower)(int i)
{ return tolower(i); }
#undef tolower
#elif defined(BOOST_NO_STDC_NAMESPACE)
using ::tolower;
#endif

#ifdef toupper
inline int (toupper)(int i)
{ return toupper(i); }
#undef toupper
#elif defined(BOOST_NO_STDC_NAMESPACE)
using ::toupper;
#endif

#ifndef BOOST_NO_STDC_NAMESPACE
} // extern "C"
#endif

} // namespace std

#endif
