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
 * This file implements the following:
 *    void bcp_implementation::scan_cvs_path(const fs::path& p)
 */



#include "bcp_imp.hpp"
#include "fileview.hpp"
#include <boost/regex.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/detail/workaround.hpp>

void bcp_implementation::scan_cvs_path(const fs::path& p)
{
   //
   // scan through the cvs admin files to build a list
   // of all the files under cvs version control
   // and whether they are text or binary:
   //
   fs::path entries(m_boost_path / p / "CVS/Entries");
   if(fs::exists(entries))
   {
      static const boost::regex file_expression("^/([^/\\n]+)/[^/\\n]*/[^/\\n]*/[^k/\\n]*(kb[^/\\n]*)?/[^/\\n]*");
      static const boost::regex dir_expression("^D/([^/\\n]+)/");
      static const int file_subs[] = {1,2,};
      fileview view(entries);
      boost::regex_token_iterator<const char*> i(view.begin(), view.end(), dir_expression, 1);
      boost::regex_token_iterator<const char*> j;
      while(i != j)
      {
         fs::path recursion_dir(p / *i);
         scan_cvs_path(recursion_dir);
         ++i;
      }
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300) || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x570))
     std::vector<int> v(file_subs, file_subs + 2);
      i = boost::regex_token_iterator<const char*>(view.begin(), view.end(), file_expression, v);
#else
      i = boost::regex_token_iterator<const char*>(view.begin(), view.end(), file_expression, file_subs);
#endif
      while(i != j)
      {
         fs::path file(p / *i);
         ++i;
         bool binary = !(i->empty());
         ++i;
         m_cvs_paths[file] = binary;
      }

   }
}
