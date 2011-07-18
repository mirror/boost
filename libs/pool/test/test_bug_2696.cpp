/* Copyright (C) 2011 John Maddock
* 
* Use, modification and distribution is subject to the 
* Boost Software License, Version 1.0. (See accompanying
* file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
*/

// Test of bug #2656 (https://svn.boost.org/trac/boost/ticket/2656)

#include <boost/pool/pool.hpp>
#include <boost/detail/lightweight_test.hpp>

struct limited_allocator_new_delete
{
   typedef std::size_t size_type; 
   typedef std::ptrdiff_t difference_type; 

   static char * malloc BOOST_PREVENT_MACRO_SUBSTITUTION(const size_type bytes)
   { 
#ifndef BOOST_POOL_VALGRIND
      static const unsigned max_size = 4 * 40 + sizeof(void*) + 2 * sizeof(std::size_t);
#else
      static const unsigned max_size = 4 * 40;
#endif
      if(bytes > max_size)
         return 0;
      return new (std::nothrow) char[bytes];
   }
   static void free BOOST_PREVENT_MACRO_SUBSTITUTION(char * const block)
   { 
      delete [] block;
   }
};

int main() 
{
   boost::pool<limited_allocator_new_delete> p1(4, 10, 40);
   for(int i = 1; i <= 40; ++i)
      BOOST_TEST((p1.ordered_malloc)(i));
   BOOST_TEST(p1.ordered_malloc(42) == 0);
   //
   // If the largest block is 40, and we start with 10, we get 10+20+40 elements before
   // we actually run out of memory:
   //
   boost::pool<limited_allocator_new_delete> p2(4, 10, 40);
   for(int i = 1; i <= 70; ++i)
      BOOST_TEST((p2.malloc)());
   boost::pool<limited_allocator_new_delete> p2b(4, 10, 40);
   for(int i = 1; i <= 100; ++i)
      BOOST_TEST((p2b.ordered_malloc)());
   //
   // Try again with no explicit upper limit:
   //
   boost::pool<limited_allocator_new_delete> p3(4);
   for(int i = 1; i <= 40; ++i)
      BOOST_TEST((p3.ordered_malloc)(i));
   BOOST_TEST(p3.ordered_malloc(42) == 0);
   boost::pool<limited_allocator_new_delete> p4(4, 10);
   for(int i = 1; i <= 100; ++i)
      BOOST_TEST((p4.ordered_malloc)());
   boost::pool<limited_allocator_new_delete> p5(4, 10);
   for(int i = 1; i <= 100; ++i)
      BOOST_TEST((p5.malloc)());
   return boost::report_errors();
}
