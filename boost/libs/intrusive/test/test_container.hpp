//////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006 Matias Capeletto
// Copyright (c) 2007 Ion Gaztañaga
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_TEST_TEST_CONTAINER_HPP
#define BOOST_INTRUSIVE_TEST_TEST_CONTAINER_HPP

// std
#include <cassert>
#include <algorithm>
#include <vector>
// Boost.Test
//#include "boost/test/included/test_exec_monitor.hpp"

namespace boost{
namespace intrusive{
namespace test {

const int NumElem = 5;

/*
Beginning of range  a.begin()     iterator if a is mutable, const_iterator otherwise [4] [7]  
End of range  a.end()     iterator if a is mutable, const_iterator otherwise [4]  
Size  a.size()     size_type  
Maximum size  a.max_size()     size_type  
Empty container  a.empty()     Convertible to bool  
Swap  a.swap(b)     void  

Expression semantics
Semantics of an expression is defined only where it differs from, or is not defined in, Assignable, Equality Comparable, or LessThan Comparable Name  Expression  Precondition  Semantics  Postcondition  
Move constructor  X(a)        X().size() == a.size(). X() contains a copy of each of a's elements.  
Move constructor  X b(a);        b.size() == a.size(). b contains a copy of each of a's elements.  
Move Assignment operator  b = a        b.size() == a.size(). b contains a copy of each of a's elements.  
Destructor  a.~X()     Each of a's elements is destroyed, and memory allocated for them (if any) is deallocated.     
Beginning of range  a.begin()     Returns an iterator pointing to the first element in the container. [7]  a.begin() is either dereferenceable or past-the-end. It is past-the-end if and only if a.size() == 0.  
End of range  a.end()     Returns an iterator pointing one past the last element in the container.  a.end() is past-the-end.  
Size  a.size()     Returns the size of the container, that is, its number of elements. [8]  a.size() >= 0 && a.size() <= max_size()  
Maximum size  a.max_size()     Returns the largest size that this container can ever have. [8]  a.max_size() >= 0 && a.max_size() >= a.size()  
Empty container  a.empty()     Equivalent to a.size() == 0. (But possibly faster.)     
Swap  a.swap(b)     Equivalent to swap(a,b) [9]     
*/

/*
expression     return type       operational       assertion/note       complexity
                                 semantics      pre/post-condition


X::value_type  T                 T is
                           CopyConstructible
compile time
X::reference lvalue of T compile time
X::const_-
reference
const lvalue of T compile time
X::iterator iterator type
whose value
type is T
any iterator category
except output iterator.
convertible to
X::const_iterator.
compile time
X::const_-
iterator
constant iterator
type whose
value type is T
any iterator category
except output iterator
compile time
X::difference_
type
signed integral
type
is identical to the
difference type of
X::iterator and
X::const_iterator
compile time
X::size_type unsigned
integral type
size_type can
represent any
non-negative value of
compile time






X u;     post: u.size() == 0        constant
X();     X().size() == 0            constant
X(a);    a == X(a). linear
X u(a); post: u == a linear
X u = a; Equivalent to: X u; u
= a;
(&a)->X(); void note: the destructor is
applied to every
element of a; all the
memory is deallocated.
linear
a.begin(); iterator;
const_-
iterator for
constant a
constant
*/

template< class Container >
void test_container( Container & c )
{
   typedef typename Container::value_type       value_type;
   typedef typename Container::iterator         iterator;
   typedef typename Container::const_iterator   const_iterator;
   typedef typename Container::reference        reference;
   typedef typename Container::const_reference  const_reference;
   typedef typename Container::pointer          pointer;
   typedef typename Container::const_pointer    const_pointer;
   typedef typename Container::difference_type  difference_type;
   typedef typename Container::size_type        size_type;

   const size_type num_elem = c.size();
   BOOST_CHECK( c.empty() == (num_elem == 0) );
   {
      iterator it(c.begin()), itend(c.end());
      size_type i;
      for(i = 0; i < num_elem; ++i){
         ++it;
      }
      BOOST_CHECK( it == c.end() );
      BOOST_CHECK( c.size() == i );
   }
   //Check iterator conversion
   BOOST_CHECK( const_iterator(c.begin()) == c.cbegin() );
   {
      const_iterator it(c.cbegin()), itend(c.cend());
      size_type i;
      for(i = 0; i < num_elem; ++i){
         ++it;
      }
      BOOST_CHECK( it == c.cend() );
      BOOST_CHECK( c.size() == i );
   }
}
/*
template< class Container >
void test_container
   ( Container & c, typename Container::size_type num_elem
   , Container & c2, typename Container::size_type num_elem2)
{
   typedef typename Container::value_type       value_type;
   typedef typename Container::iterator         iterator;
   typedef typename Container::const_iterator   const_iterator;
   typedef typename Container::reference        reference;
   typedef typename Container::const_reference  const_reference;
   typedef typename Container::pointer          pointer;
   typedef typename Container::const_pointer    const_pointer;
   typedef typename Container::difference_type  difference_type;
   typedef typename Container::size_type        size_type;

   //For the future:
   //
   //move-copy constructor
   //move-assignment

   test_container_helper(c, num_elem);
   test_container_helper(c2, num_elem2);

   //Test swap and test again
   c.swap(c2);
   test_container_helper(c, num_elem2);
   test_container_helper(c2, num_elem);
}*/

template< class Sequence >
void test_sequence( Sequence & seq )
{
   //First the container requirements  
   test_container(seq);
   typedef Sequence::value_type  value_type;
   typedef Sequence::iterator    iterator;

   Sequence::size_type old_size(seq.size());

   //Now test sequence requirements
   //insert(p, t)
   Sequence::value_type one(1);
   iterator one_pos = seq.insert(seq.begin(), one);
   BOOST_CHECK( &*seq.begin() == &one );
   BOOST_CHECK( seq.size() == (old_size + 1) );

   //insert(p, i, j)
   value_type range[2] = { value_type(2), value_type(3) };
   iterator range_it = one_pos;  ++range_it;
   seq.insert(range_it, &range[0], &range[2]);
   BOOST_CHECK( seq.size() == (old_size + 3) );
   range_it = ++seq.begin();
   BOOST_CHECK( &*range_it  == &range[0] );
   ++range_it;
   BOOST_CHECK( &*range_it  == &range[1] );

   //erase(q)
   iterator it_from_erase = seq.erase(seq.begin());
   BOOST_CHECK( seq.size() == (old_size + 2) );
   BOOST_CHECK( &*it_from_erase == &range[0] );

   //erase(q1, q2)
   iterator q1(it_from_erase), q2(it_from_erase);
   ++++q2;
   it_from_erase = seq.erase(q1, q2);
   BOOST_CHECK( seq.size() == old_size );
   //clear(), assign()???
}

}  // namespace test{
}  // namespace intrusive{
}  // namespace boost{

#endif // BOOST_INTRUSIVE_TEST_TEST_CONTAINER_HPP
