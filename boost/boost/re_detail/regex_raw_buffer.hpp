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
  *   FILE         regex_raw_buffer.hpp
  *   VERSION      3.01
  *   DESCRIPTION: Raw character buffer for regex code.
  *                Note this is an internal header file included
  *                by regex.hpp, do not include on its own.
  */

#ifndef BOOST_REGEX_RAW_BUFFER_HPP
#define BOOST_REGEX_RAW_BUFFER_HPP

#ifndef BOOST_REGEX_CONFIG_HPP
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

struct empty_padding{};

union padding
{
   void* p;
   unsigned int i;
};

template <int N>
struct padding3
{
   enum{
      padding_size = 8,
      padding_mask = 7
   };
};

template<>
struct padding3<2>
{
   enum{
      padding_size = 2,
      padding_mask = 1
   };
};

template<>
struct padding3<4>
{
   enum{
      padding_size = 4,
      padding_mask = 3
   };
};

template<>
struct padding3<8>
{
   enum{
      padding_size = 8,
      padding_mask = 7
   };
};

template<>
struct padding3<16>
{
   enum{
      padding_size = 16,
      padding_mask = 15
   };
};

enum{
   padding_size = padding3<sizeof(padding)>::padding_size,
   padding_mask = padding3<sizeof(padding)>::padding_mask
};

//
// class raw_storage
// basically this is a simplified vector<unsigned char>
// this is used by reg_expression for expression storage
//

template <class Allocator>
class raw_storage
{
public:
   typedef Allocator allocator_type;
   typedef typename REBIND_TYPE(unsigned char, allocator_type)::size_type size_type;
   typedef BOOST_RE_MAYBE_TYPENAME REBIND_TYPE(unsigned char, allocator_type) alloc_inst_type;
   typedef typename REBIND_TYPE(unsigned char, allocator_type)::pointer pointer;
private:
   //
   // empty member optimisation:
   struct alloc_data : public alloc_inst_type
   {
      typename alloc_inst_type::pointer last;
      alloc_data(const Allocator& a) : alloc_inst_type(a){}
   } alloc_inst;
   raw_storage<Allocator>::pointer start, end;
public:

   raw_storage(const Allocator& a = Allocator());
   raw_storage(size_type n, const Allocator& a = Allocator());

   ~raw_storage()
   {
      alloc_inst.deallocate(start, (alloc_inst.last - start));
   }

   void BOOST_RE_CALL resize(size_type n);
   
   void* BOOST_RE_CALL extend(size_type n)
   {
      if(size_type(alloc_inst.last - end) < n)
         resize(n + (end - start));
      register void* result = end;
      end += n;
      return result;
   }

   void* BOOST_RE_CALL insert(size_type pos, size_type n);

   size_type BOOST_RE_CALL size()
   {
      return end - start;
   }

   size_type BOOST_RE_CALL capacity()
   {
      return alloc_inst.last - start;
   }

   void* BOOST_RE_CALL data()const
   {
      return start;
   }

   size_type BOOST_RE_CALL index(void* ptr)
   {
      return (unsigned char*)ptr - (unsigned char*)data();
   }

   void BOOST_RE_CALL clear()
   {
      end = start;
   }

   void BOOST_RE_CALL align()
   {
      // move end up to a boundary:
      end = (unsigned char*)start + ((((unsigned char*)end - (unsigned char*)start) + padding_mask) & ~padding_mask);
   }

   Allocator BOOST_RE_CALL allocator()const;
};

template <class Allocator>
CONSTRUCTOR_INLINE raw_storage<Allocator>::raw_storage(const Allocator& a)
  : alloc_inst(a)
{
  start = end = alloc_inst.allocate(1024);
  alloc_inst.last = start + 1024;
}

template <class Allocator>
CONSTRUCTOR_INLINE raw_storage<Allocator>::raw_storage(size_type n, const Allocator& a)
  : alloc_inst(a)
{
  start = end = alloc_inst.allocate(n);
  alloc_inst.last = start + n;
}

template <class Allocator>
Allocator BOOST_RE_CALL raw_storage<Allocator>::allocator()const
{
  return alloc_inst;
}

template <class Allocator>
void BOOST_RE_CALL raw_storage<Allocator>::resize(size_type n)
{
   register size_type newsize = (alloc_inst.last - start) * 2;
   register size_type datasize = end - start;
   if(newsize < n)
      newsize = n;
   // extend newsize to WORD/DWORD boundary:
   newsize = (newsize + padding_mask) & ~(padding_mask);

   // allocate and copy data:
   register unsigned char* ptr = alloc_inst.allocate(newsize);
   std::memcpy(ptr, start, datasize);

   // get rid of old buffer:
   alloc_inst.deallocate(start, (alloc_inst.last - start));

   // and set up pointers:
   start = ptr;
   end = ptr + datasize;
   alloc_inst.last = ptr + newsize;
}

template <class Allocator>
void* BOOST_RE_CALL raw_storage<Allocator>::insert(size_type pos, size_type n)
{
   jm_assert(pos <= size_type(end - start));
   if(size_type(alloc_inst.last - end) < n)
      resize(n + (end - start));
   register void* result = start + pos;
   std::memmove(start + pos + n, start + pos, (end - start) - pos);
   end += n;
   return result;
}

#ifdef __BORLANDC__
 #if __BORLANDC__ > 0x520
  #pragma option pop
 #endif
#endif

} // namespace re_detail
} // namespace boost

#endif




