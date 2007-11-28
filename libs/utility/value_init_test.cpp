// Copyright 2002, Fernando Luis Cacciola Carballal.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Test program for "boost/utility/value_init.hpp"
//
// Initial: 21 Agu 2002

#include <iostream>
#include <string>

#include "boost/utility/value_init.hpp"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#include "boost/test/minimal.hpp"

//
// Sample POD type
//
struct POD
{
  POD () : c(0), i(0), f(0) {}

  POD ( char c_, int i_, float f_ ) : c(c_), i(i_), f(f_) {}

  friend std::ostream& operator << ( std::ostream& os, POD const& pod )
    { return os << '(' << pod.c << ',' << pod.i << ',' << pod.f << ')' ; }

  friend bool operator == ( POD const& lhs, POD const& rhs )
    { return lhs.f == rhs.f && lhs.c == rhs.c && lhs.i == rhs.i ; }

  float f;
  char  c;
  int   i;
} ;

//
// Sample non POD type
//
struct NonPODBase
{
  virtual ~NonPODBase() {}
} ;
struct NonPOD : NonPODBase
{
  NonPOD () : id() {}
  NonPOD ( std::string const& id_) : id(id_) {}

  friend std::ostream& operator << ( std::ostream& os, NonPOD const& npod )
    { return os << '(' << npod.id << ')' ; }

  friend bool operator == ( NonPOD const& lhs, NonPOD const& rhs )
    { return lhs.id == rhs.id ; }

  std::string id ;
} ;

//
// Sample aggregate POD struct type
//
struct AggregatePODStruct
{
  float f;
  char  c;
  int   i;
};

bool operator == ( AggregatePODStruct const& lhs, AggregatePODStruct const& rhs )
{ return lhs.f == rhs.f && lhs.c == rhs.c && lhs.i == rhs.i ; }

//
// An aggregate struct that contains an std::string and an int.
// Pavel Kuznetsov (MetaCommunications Engineering) used a struct like
// this to reproduce the Microsoft Visual C++ compiler bug, reported as
// Feedback ID 100744, "Value-initialization in new-expression"
// https://connect.microsoft.com/VisualStudio/feedback/ViewFeedback.aspx?FeedbackID=100744
//
struct StringAndInt
{
  std::string s;
  int i;
};

bool operator == ( StringAndInt const& lhs, StringAndInt const& rhs )
{ return lhs.s == rhs.s && lhs.i == rhs.i ; }


//
// A struct that has an explicit (user defined) destructor.
// Some compilers do not correctly value-initialize such a struct, for example:
// Microsoft Visual C++, Feedback ID 100744, "Value-initialization in new-expression"
// https://connect.microsoft.com/VisualStudio/feedback/ViewFeedback.aspx?FeedbackID=100744
//
struct StructWithDestructor
{
  int i;
  ~StructWithDestructor() {}
};

bool operator == ( StructWithDestructor const& lhs, StructWithDestructor const& rhs )
{ return lhs.i == rhs.i ; }


//
// A struct that has a virtual function.
// Some compilers do not correctly value-initialize such a struct either, for example:
// Microsoft Visual C++, Feedback ID 100744, "Value-initialization in new-expression"
// https://connect.microsoft.com/VisualStudio/feedback/ViewFeedback.aspx?FeedbackID=100744
//
struct StructWithVirtualFunction
{
  int i;
  virtual void VirtualFunction(); 
};

void StructWithVirtualFunction::VirtualFunction()
{
}

bool operator == ( StructWithVirtualFunction const& lhs, StructWithVirtualFunction const& rhs )
{ return lhs.i == rhs.i ; }


//
// This test function tests boost::value_initialized<T> for a specific type T.
// The first argument (y) is assumed have the value of a value-initialized object.
// Returns true on success.
//
template<class T>
bool test ( T const& y, T const& z )
{
  const boost::unit_test::counter_t counter_before_test = boost::minimal_test::errors_counter();
  boost::value_initialized<T> x ;
  BOOST_CHECK ( y == x ) ;
  BOOST_CHECK ( y == boost::get(x) ) ;
  static_cast<T&>(x) = z ;
  boost::get(x) = z ;
  BOOST_CHECK ( x == z ) ;

  boost::value_initialized<T> const x_c ;
  BOOST_CHECK ( y == x_c ) ;
  BOOST_CHECK ( y == boost::get(x_c) ) ;
  T& x_c_ref = x_c ;
  x_c_ref = z ;
  BOOST_CHECK ( x_c == z ) ;

#if !BOOST_WORKAROUND(BOOST_MSVC, < 1300)
  boost::value_initialized<T const> cx ;
  BOOST_CHECK ( y == cx ) ;
  BOOST_CHECK ( y == boost::get(cx) ) ;

  boost::value_initialized<T const> const cx_c ;
  BOOST_CHECK ( y == cx_c ) ;
  BOOST_CHECK ( y == boost::get(cx_c) ) ;
#endif
  return boost::minimal_test::errors_counter() == counter_before_test ;
}

int test_main(int, char **)
{
  BOOST_CHECK ( test( 0,1234 ) ) ;
  BOOST_CHECK ( test( 0.0,12.34 ) ) ;
  BOOST_CHECK ( test( POD(0,0,0.0), POD('a',1234,56.78) ) ) ;
  BOOST_CHECK ( test( NonPOD( std::string() ), NonPOD( std::string("something") ) ) ) ;

  NonPOD NonPOD_object( std::string("NonPOD_object") );
  BOOST_CHECK ( test<NonPOD *>( 0, &NonPOD_object ) ) ;

  AggregatePODStruct zeroInitializedAggregatePODStruct = { 0.0f, '\0', 0 };
  AggregatePODStruct nonZeroInitializedAggregatePODStruct = { 1.25f, 'a', -1 };
  BOOST_CHECK ( test(zeroInitializedAggregatePODStruct, nonZeroInitializedAggregatePODStruct) );

  StringAndInt stringAndInt0;
  StringAndInt stringAndInt1;
  stringAndInt0.i = 0;
  stringAndInt1.i = 1;
  stringAndInt1.s = std::string("1");
  BOOST_CHECK ( test(stringAndInt0, stringAndInt1) );

  StructWithDestructor structWithDestructor0;
  StructWithDestructor structWithDestructor1;
  structWithDestructor0.i = 0;
  structWithDestructor1.i = 1;
  BOOST_CHECK ( test(structWithDestructor0, structWithDestructor1) );

  StructWithVirtualFunction structWithVirtualFunction0;
  StructWithVirtualFunction structWithVirtualFunction1;
  structWithVirtualFunction0.i = 0;
  structWithVirtualFunction1.i = 1;
  BOOST_CHECK ( test(structWithVirtualFunction0, structWithVirtualFunction1) );

  return 0;
}


unsigned int expected_failures = 0;
