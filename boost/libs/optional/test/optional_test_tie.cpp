// (C) 2003, Fernando Luis Cacciola Carballal.
//
// This material is provided "as is", with absolutely no warranty expressed
// or implied. Any use is at your own risk.
//
// Permission to use or copy this software for any purpose is hereby granted
// without fee, provided the above notices are retained on all copies.
// Permission to modify the code and to distribute modified code is granted,
// provided the above notices are retained, and a notice that the code was
// modified is included with the above copyright notice.
//
// You are welcome to contact the author at:
//  fernando_cacciola@hotmail.com
//
#include<iostream>
#include<stdexcept>
#include<string>

#define BOOST_ENABLE_ASSERT_HANDLER

#include "boost/optional.hpp"
#include "boost/tuple/tuple.hpp"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#include "boost/test/minimal.hpp"

#include "optional_test_common.cpp"

// Test boost::tie() interoperabiliy.
int test_main( int, char* [] )
{
  typedef X T ;
          
  try
  {
    TRACE( std::endl << BOOST_CURRENT_FUNCTION  );
  
    T z(0);
    T a(1);
    T b(2);
  
    optional<T> oa, ob ;
  
    // T::T( T const& x ) is used
    set_pending_dtor( ARG(T) ) ;
    set_pending_copy( ARG(T) ) ;
    boost::tie(oa,ob) = std::make_pair(a,b) ;
    check_is_not_pending_dtor( ARG(T) ) ;
    check_is_not_pending_copy( ARG(T) ) ;
    check_initialized(oa);
    check_initialized(ob);
    check_value(oa,a,z);
    check_value(ob,b,z);
    
  }
  catch ( ... )
  {
    BOOST_ERROR("Unexpected Exception caught!");
  }

  return 0;
}


