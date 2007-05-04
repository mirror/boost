/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztañaga  2006-2007
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_TEST_COMMON_FUNCTORS_HPP
#define BOOST_INTRUSIVE_TEST_COMMON_FUNCTORS_HPP

namespace boost      {
namespace intrusive  {
namespace test       {

class delete_destroyer
{
public:
   template <class Pointer>
      void operator()(Pointer p)
   {
      using boost::get_pointer;
      delete get_pointer(p); 
   }
};

class new_cloner
{
public:
   template<class Type>
      Type *operator()(const Type &t)
   {  return new Type(t); }
};

}  //namespace test       {
}  //namespace intrusive  {
}  //namespace boost      {

#endif
