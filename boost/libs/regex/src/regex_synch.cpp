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
  *   FILE:        regex_synch.cpp
  *   VERSION:     3.00
  *   DESCRIPTION: Thread synch helper functions, for regular
  *                expression library.
  */
#include <boost/re_detail/regex_synch.hpp>

namespace boost{
   namespace re_detail{

void BOOST_RE_CALL re_init_threads()
{
   BOOST_RE_GUARD_STACK
#ifdef BOOST_RE_THREADS
   if(p_re_lock == 0)
      p_re_lock = new critical_section();
   cs_guard g(*p_re_lock);
   ++re_lock_count;
#endif
}

void BOOST_RE_CALL re_free_threads()
{
   BOOST_RE_GUARD_STACK
#ifdef BOOST_RE_THREADS
   cs_guard g(*p_re_lock);
   --re_lock_count;
   if(re_lock_count == 0)
   {
      g.acquire(false);
      delete p_re_lock;
      p_re_lock = 0;
   }
#endif
}

#ifdef BOOST_RE_THREADS

BOOST_RE_IX_DECL critical_section* p_re_lock = 0;

BOOST_RE_IX_DECL unsigned int re_lock_count = 0;

#endif

   } // namespace re_detail
} // namespace boost

