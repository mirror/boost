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
  *   FILE         pattern_except.cpp
  *   VERSION      3.01
  *   DESCRIPTION: Declares pattern-matching exception classes.
  */

#ifndef BOOST_RE_PAT_EXCEPT_HPP
#define BOOST_RE_PAT_EXCEPT_HPP

#include <stdexcept>

namespace boost{

#ifdef __BORLANDC__
   #if __BORLANDC__ == 0x530
    #pragma option push -a4 -b -Ve
   #elif __BORLANDC__ > 0x530
    #pragma option push -a8 -b -Ve
   #endif
#endif

class BOOST_RE_IX_DECL bad_pattern : public std::runtime_error
{
public:
   explicit bad_pattern(const std::string& s) : std::runtime_error(s){};
   ~bad_pattern();
};

class BOOST_RE_IX_DECL bad_expression : public bad_pattern
{
public:
   explicit bad_expression(const std::string& s) : bad_pattern(s) {}
   ~bad_expression();
};


#ifdef __BORLANDC__
 #if __BORLANDC__ > 0x520
  #pragma option pop
 #endif
#endif

} // namespace boost

#endif
