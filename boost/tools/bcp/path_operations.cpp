/*
 *
 * Copyright (c) 2003
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
 * This file implements path comparisons
 */


#include "bcp_imp.hpp"
#include <cctype>

#ifdef BOOST_NO_STDC_NAMESPACE
namespace std{
   using ::tolower;
}
#endif


int compare_paths(const fs::path& a, const fs::path& b)
{
   const std::string& as = a.string();
   const std::string& bs = b.string();
   std::string::const_iterator i, j, k, l;
   i = as.begin();
   j = as.end();
   k = bs.begin();
   l = bs.end();
   while(i != j)
   {
      if(k == l)
         return -1;
      int r = std::tolower(*i) - std::tolower(*k);
      if(r) return r;
      ++i;
      ++k;
   }
   return (k == l) ? 0 : 1;
}
