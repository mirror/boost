/*
 *
 * Copyright (c) 1998-200
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
  *   FILE:        regex.cpp
  *   VERSION:     3.04
  *   DESCRIPTION: Misc boost::regbase member funnctions.
  */


#include <boost/regex.hpp>


namespace boost{


//
// fix: these are declared out of line here to ensure
// that dll builds contain the Virtual table for these
// types - this ensures that exceptions can be thrown
// from the dll and caught in an exe.
bad_pattern::~bad_pattern() throw() {}
bad_expression::~bad_expression() throw() {}

regbase::regbase()
   : _flags(regbase::failbit){}

regbase::regbase(const regbase& b)
   : _flags(b._flags){}

} // namespace boost

#if defined(BOOST_RE_USE_VCL) && defined(BOOST_RE_BUILD_DLL)

int WINAPI DllEntryPoint(HINSTANCE , unsigned long , void*)
{
   return 1;
}
#endif







