/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2007
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_POINTER_PLUS_BIT_HPP
#define BOOST_INTRUSIVE_POINTER_PLUS_BIT_HPP

#include<boost/type_traits/alignment_of.hpp>
#include<boost/static_assert.hpp>

namespace boost {
namespace intrusive {

//!This trait class is used to know if a pointer
//!can embed an extra bit of information if
//!it's going to be used to point to objects
//!with an alignment of "Alignment" bytes.
template<class Pointer>
struct has_pointer_plus_bit
{
   enum  {  value = false  };
};

//!This is an specialization for raw pointers.
//!Raw pointers can embed an extra bit in the lower bit
//!if the alignment is multiple of 2.

template<class T>
struct has_pointer_plus_bit<T*>
{
   enum  {  value = (boost::alignment_of<T>::value % 2u) == 0  };
};

//!This is class that is supposed to have static methods
//!to embed an extra bit of information in a pointer.
//!This is a declaration and there is no default implementation,
//!because operations to embed the bit change with every pointer type.
//!
//!An implementation that detects that a pointer type whose
//!has_pointer_plus_bit<>::value is non-zero can make use of these
//!operations to embed the bit in the pointer.
template<class Pointer>
struct pointer_plus_bit;

//!This is the specialization to embed an extra bit of information
//!in a raw pointer. The extra bit is stored in the lower bit of the pointer.
template<class T>
struct pointer_plus_bit<T*>
{
   typedef T*        pointer;

   //Check that the pointer can embed the bit
   BOOST_STATIC_ASSERT((has_pointer_plus_bit<T*>::value));

   static pointer get_pointer(pointer n)
   {  return pointer(std::size_t(n) & std::size_t(~1u));  }

   static void set_pointer(pointer &n, pointer p)
   {
      assert(0 == (std::size_t(p) & std::size_t(1u)));
      n = pointer(std::size_t(p) | (std::size_t(n) & std::size_t(1u))); 
   }

   static bool get_bit(pointer n)
   {  return (std::size_t(n) & std::size_t(1u)) != 0;  }

   static void set_bit(pointer &n, bool c)
   {  n = pointer(std::size_t(get_pointer(n)) | std::size_t(c));  }
};

} //namespace intrusive 
} //namespace boost 

#endif //BOOST_INTRUSIVE_POINTER_PLUS_BIT_HPP
