/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztañaga  2007
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTRUSIVE_PARENT_FROM_MEMBER_HPP
#define BOOST_INTRUSIVE_PARENT_FROM_MEMBER_HPP

namespace boost {
namespace intrusive {
namespace detail {

template<class Parent, class Member>
std::size_t offset_from_pointer_to_member(const Member Parent::* ptr_to_member)
{
   //This works with gcc and msvc
   return *(const std::size_t*)(const void*)&ptr_to_member;
   //Other compilers might need other transformation, depending how a
   //pointer to data member is implemented.
}

template<class Parent, class Member>
Parent *parent_from_member(Member *member, const Member Parent::* ptr_to_member)
{
   return (Parent*)((char*)member - 
      offset_from_pointer_to_member(ptr_to_member));
}

template<class Parent, class Member>
const Parent *parent_from_member(const Member *member, const Member Parent::* ptr_to_member)
{
   return (const Parent*)((const char*)member - 
      offset_from_pointer_to_member(ptr_to_member));
}

}  //namespace detail {
}  //namespace intrusive {
}  //namespace boost {

#endif   //#ifndef BOOST_INTRUSIVE_PARENT_FROM_MEMBER_HPP
