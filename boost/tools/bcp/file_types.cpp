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
 *    void bcp_implementation::is_source_file(const fs::path& p)
 *    void bcp_implementation::is_html_file(const fs::path& p)
 *    void bcp_implementation::is_binary_file(const fs::path& p)
 */

#include "bcp_imp.hpp"
#include <boost/regex.hpp>

bool bcp_implementation::is_source_file(const fs::path& p)
{
   static const boost::regex e(
      ".*\\."
      "(?:"
         "c|cxx|cpp|h|hxx|hpp|inc"
      ")"
      );
   return boost::regex_match(p.string(), e);
}

bool bcp_implementation::is_html_file(const fs::path& p)
{
   static const boost::regex e(
      ".*\\."
      "(?:"
         "html?|css"
      ")"
      );
   return boost::regex_match(p.string(), e);
}

bool bcp_implementation::is_binary_file(const fs::path& p)
{
   if(m_cvs_mode)
   {
      std::map<fs::path, bool, path_less>::iterator pos = m_cvs_paths.find(p);
      if(pos != m_cvs_paths.end()) return pos->second;
   }
   static const boost::regex e(
      "(.*\\."
      "(?:"
         "c|cxx|cpp|h|hxx|hpp|inc|html?|css|mak|in"
      ")"
      "|"
      "(Jamfile|makefile|configure)",
      boost::regex::perl | boost::regex::icase);
   return !boost::regex_match(p.leaf(), e);

}
