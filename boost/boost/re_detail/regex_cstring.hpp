/*
 *
 * Copyright (c) 1998-2000
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
  *   FILE         regex_cstring.hpp
  *   VERSION      3.04
  *   DESCRIPTION: This is an internal header file, do not include directly.
  *                String support and helper functions, for regular
  *                expression library.
  */

#ifndef BOOST_REGEX_CSTRING_HPP
#define BOOST_REGEX_CSTRING_HPP

#ifndef BOOST_REGEX_CONFIG_HPP
#include <boost/re_detail/regex_config.hpp>
#endif

#include <cstring>

namespace boost{
   namespace re_detail{

#ifdef __BORLANDC__
   #if __BORLANDC__ == 0x530
    #pragma option push -a4 -b -Ve
   #elif __BORLANDC__ > 0x530
    #pragma option push -a8 -b -Ve
   #endif
#endif

//
// start by defining some template function aliases for C API functions:
//

template <class charT>
std::size_t BOOST_RE_CALL re_strlen(const charT *s)
{
   std::size_t len = 0;
   while(*s)
   {
      ++s;
      ++len;
   }
   return len;
}

inline std::size_t BOOST_RE_CALL re_strlen(const char *s)
{
   return std::strlen(s);
}

#ifndef BOOST_RE_NO_WCSTRING

inline std::size_t BOOST_RE_CALL re_strlen(const wchar_t *s)
{
   return std::wcslen(s);
}

#endif

#ifndef BOOST_RE_NO_WCSTRING
BOOST_RE_IX_DECL void BOOST_RE_CALL re_transform(std::basic_string<wchar_t>& out, const std::basic_string<wchar_t>& in);
#endif
BOOST_RE_IX_DECL void BOOST_RE_CALL re_transform(std::string& out, const std::string& in);

template <class charT>
void BOOST_RE_CALL re_trunc_primary(std::basic_string<charT>& s)
{
   for(unsigned int i = 0; i < s.size(); ++i)
   {
      if(s[i] <= 1)
      {
         s.erase(i);
         break;
      }
   }
}

inline char* BOOST_RE_CALL re_strcpy(char *s1, const char *s2)
{
   #if defined(__BORLANDC__) && defined(strcpy)
   return ::strcpy(s1, s2);
   #else
   return std::strcpy(s1, s2);
   #endif
}

#ifndef BOOST_RE_NO_WCSTRING

inline wchar_t* BOOST_RE_CALL re_strcpy(wchar_t *s1, const wchar_t *s2)
{
   return std::wcscpy(s1, s2);
}

#endif


template <class charT>
charT* BOOST_RE_CALL re_strdup(const charT* p)
{
   charT* buf = new charT[re_strlen(p) + 1];
   re_strcpy(buf, p);
   return buf;
}

template <class charT>
inline void BOOST_RE_CALL re_strfree(charT* p)
{
   delete[] p;
}

#ifdef __BORLANDC__
 #if __BORLANDC__ > 0x520
  #pragma option pop
 #endif
#endif

} // namespace re_detail
} // namespace boost

#endif  // BOOST_REGEX_CSTRING_HPP




