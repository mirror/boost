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
  *   FILE         regex_kmp.hpp
  *   VERSION      3.03
  *   DESCRIPTION: Provides Knuth Morris Pratt search operations.
  *                Note this is an internal header file included
  *                by regex.hpp, do not include on its own.
  */

#ifndef BOOST_REGEX_KMP_HPP
#define BOOST_REGEX_KMP_HPP

#ifdef BOOST_REGEX_CONFIG_HPP
#include <boost/re_detail/regex_config.hpp>
#endif


namespace boost{
   namespace re_detail{

#ifdef __BORLANDC__
   #if __BORLANDC__ == 0x530
    #pragma option push -a4 -b -Ve
   #elif __BORLANDC__ > 0x530
    #pragma option push -a8 -b -Ve
   #endif
#endif

template <class charT>
struct kmp_info
{
   unsigned int size;
   unsigned int len;
   const charT* pstr;
   int kmp_next[1];
};

template <class charT, class Allocator>
void kmp_free(kmp_info<charT>* pinfo, Allocator a)
{
   typedef BOOST_RE_MAYBE_TYPENAME REBIND_TYPE(char, Allocator) atype;
   atype(a).deallocate((char*)pinfo, pinfo->size);
}

template <class iterator, class charT, class Trans, class Allocator>
kmp_info<charT>* kmp_compile(iterator first, iterator last, charT, Trans translate, Allocator a) 
{    
   typedef BOOST_RE_MAYBE_TYPENAME REBIND_TYPE(char, Allocator) atype;
   int i, j, m;
   i = 0;
   BOOST_RE_DISTANCE(first, last, m);
   ++m;
   unsigned int size = sizeof(kmp_info<charT>) + sizeof(int)*m + sizeof(charT)*m;
   --m;
   //
   // allocate struct and fill it in:
   //
   kmp_info<charT>* pinfo = (kmp_info<charT>*)atype(a).allocate(size);
   pinfo->size = size;
   pinfo->len = m;
   charT* p = (charT*)((char*)pinfo + sizeof(kmp_info<charT>) + sizeof(int)*(m+1));
   pinfo->pstr = p;
   while(first != last)
   {
      *p = translate(*first);
      ++first;
      ++p;
   }
   *p = 0;
   //
   // finally do regular kmp compile:
   //
   j = pinfo->kmp_next[0] = -1;
   while (i < m) 
   {
      while ((j > -1) && (pinfo->pstr[i] != pinfo->pstr[j])) 
         j = pinfo->kmp_next[j];
      ++i;
      ++j;
      if (pinfo->pstr[i] == pinfo->pstr[j]) 
         pinfo->kmp_next[i] = pinfo->kmp_next[j];
      else 
         pinfo->kmp_next[i] = j;
   }

   return pinfo;
}

#ifdef __BORLANDC__
 #if __BORLANDC__ > 0x520
  #pragma option pop
 #endif
#endif

   } // namepsace re_detail
} // namespace boost

#endif   // BOOST_REGEX_KMP_HPP





