 /*
 * Copyright (c) 2002
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
  *   FILE         mem_block_cache.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: memory block cache used by the non-recursive matcher.
  */

#ifndef BOOST_REGEX_V4_MEM_BLOCK_CACHE_HPP
#define BOOST_REGEX_V4_MEM_BLOCK_CACHE_HPP

#include <new>
#include <boost/regex/v4/regex_synch.hpp>

#ifdef __BORLANDC__
#  pragma option push -a8 -b -Vx -Ve -pc -w-8027
#endif

namespace boost{
namespace re_detail{

struct mem_block_node
{
   mem_block_node* next;
};

struct mem_block_cache
{
   // this member has to be statically initialsed:
   mem_block_node* next;
   unsigned cached_blocks;

   ~mem_block_cache()
   {
      while(next)
      {
         mem_block_node* old = next;
         next = next->next;
         ::operator delete(old);
      }
   }
   void* get()
   {
#ifdef BOOST_HAS_THREADS
      re_detail::cs_guard g(*re_detail::p_re_lock);
#endif
     if(next)
      {
         mem_block_node* result = next;
         next = next->next;
         --cached_blocks;
         return result;
      }
      return ::operator new(BOOST_REGEX_BLOCKSIZE);
   }
   void put(void* p)
   {
#ifdef BOOST_HAS_THREADS
      re_detail::cs_guard g(*re_detail::p_re_lock);
#endif
      if(cached_blocks >= BOOST_REGEX_MAX_CACHE_BLOCKS)
      {
         ::operator delete(p);
      }
      else
      {
         mem_block_node* old = static_cast<mem_block_node*>(p);
         old->next = next;
         next = old;
         ++cached_blocks;
      }
   }
};

extern mem_block_cache block_cache;

}
} // namespace boost

#ifdef __BORLANDC__
#  pragma option pop
#endif

#endif
