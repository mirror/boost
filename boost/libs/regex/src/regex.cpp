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
  *   FILE:        regex.cpp
  *   VERSION:     see <boost/version.hpp>
  *   DESCRIPTION: Misc boost::regbase member funnctions.
  */


#define BOOST_REGEX_SOURCE

#include <new>
#include <boost/regex.hpp>
#include <boost/throw_exception.hpp>

#if defined(BOOST_REGEX_HAS_MS_STACK_GUARD) && defined(_MSC_VER) && (_MSC_VER >= 1300)
#  include <malloc.h>
#endif

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


namespace re_detail{

#ifdef BOOST_REGEX_HAS_MS_STACK_GUARD

BOOST_REGEX_DECL void BOOST_REGEX_CALL reset_stack_guard_page()
{
#if defined(BOOST_REGEX_HAS_MS_STACK_GUARD) && defined(_MSC_VER) && (_MSC_VER >= 1300)
   _resetstkoflw();
#else
   //
   // We need to locate the current page being used by the stack,
   // move to the page below it and then deallocate and protect
   // that page.  Note that ideally we would protect only the lowest
   // stack page that has been allocated: in practice there
   // seems to be no easy way to locate this page, in any case as
   // long as the next page is protected, then Windows will figure
   // the rest out for us...
   //
   SYSTEM_INFO si;
   GetSystemInfo(&si);
   MEMORY_BASIC_INFORMATION mi;
   DWORD previous_protection_status;
   //
   // this is an address in our stack space:
   //
   LPBYTE page = (LPBYTE)&page;
   //
   // Get the current memory page in use:
   //
   VirtualQuery(page, &mi, sizeof(mi));
   //
   // Go to the page one below this:
   //
   page = (LPBYTE)(mi.BaseAddress)-si.dwPageSize;
   //
   // Free and protect everything from the start of the
   // allocation range, to the end of the page below the
   // one in use:
   //
   if (!VirtualFree(mi.AllocationBase, (LPBYTE)page - (LPBYTE)mi.AllocationBase, MEM_DECOMMIT)
      || !VirtualProtect(page, si.dwPageSize, PAGE_GUARD | PAGE_READWRITE, &previous_protection_status))
   {
      throw std::bad_exception();
   }
#endif
}
#endif

BOOST_REGEX_DECL void BOOST_REGEX_CALL raise_regex_exception(const std::string& msg)
{
   bad_expression e(msg);
   throw_exception(e);
}

#if defined(BOOST_REGEX_NON_RECURSIVE) && !defined(BOOST_REGEX_V3)

mem_block_cache block_cache = { 0, };

#endif

} // namespace re_detail



} // namespace boost

#if defined(BOOST_RE_USE_VCL) && defined(BOOST_REGEX_BUILD_DLL)

int WINAPI DllEntryPoint(HINSTANCE , unsigned long , void*)
{
   return 1;
}
#endif







