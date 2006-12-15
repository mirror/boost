//  system_error_test.cpp  ---------------------------------------------------//

//  Copyright Beman Dawes 2006

//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/system

//----------------------------------------------------------------------------// 

//  VC++ 8.0 warns on usage of certain Standard Library and API functions that
//  can be cause buffer overruns or other possible security issues if misused.
//  See http://msdn.microsoft.com/msdnmag/issues/05/05/SafeCandC/default.aspx
//  But the wording of the warning is misleading and unsettling, there are no
//  portable alternative functions, and VC++ 8.0's own libraries use the
//  functions in question. So turn off the warnings.
#define _CRT_SECURE_NO_DEPRECATE
#define _SCL_SECURE_NO_DEPRECATE

#include <boost/test/minimal.hpp>
#include <boost/system/system_error.hpp>
#include <iostream>

#ifdef BOOST_WINDOWS_API
# include <winerror.h>
#endif

using boost::system::system_error;
using boost::system::error_code;
using boost::system::errno_ecat;
using boost::system::no_message;

#define TEST(x,v,w) test(#x,x,v,w)

namespace
{
  void test( const char * desc, const system_error & ex,
    error_code::value_type v, const char * str )
  {
    std::cout << "test " << desc << "\n what() returns \"" << ex.what() << "\"\n";
    BOOST_CHECK( ex.code().value() == v );
    BOOST_CHECK( ex.code().category() == errno_ecat );
# ifdef BOOST_WINDOWS_API
    BOOST_CHECK( std::string( ex.what() ) == str );
    if ( std::string( ex.what() ) != str )
      std::cout << "expected \"" << str << "\", but what() returned \""
        << ex.what() << "\"\n";
# endif
  }

  const boost::uint_least32_t uvalue = 1u;
}

int test_main( int, char *[] )
{
  // all combinations of constructors:

  system_error se_0( error_code(0, errno_ecat) ); 
  system_error se_1( 1, errno_ecat ); 
  system_error se_0_m( error_code(0, errno_ecat), "se_0_m" ); 
  system_error se_1_m( 1, errno_ecat, "se_1_m" ); 
  system_error se_0_nm( error_code(0, errno_ecat), "" ); 
  system_error se_1_nm( 1, errno_ecat, "" ); 
  system_error se_0_m_im( error_code(0, errno_ecat), "se_0_m_im", no_message ); 
  system_error se_1_m_im( 1, errno_ecat, "se_1_m_im", no_message ); 
  system_error se_0_nm_im( error_code(0, errno_ecat), "", no_message ); 
  system_error se_1_nm_im( 1, errno_ecat, "", no_message );
  system_error se_1u_m( uvalue, errno_ecat, "se_1u_m" ); 

  TEST( se_0, 0, "" );
  TEST( se_1, 1, "Operation not permitted" );
  TEST( se_0_m, 0, "se_0_m" );
  TEST( se_1_m, 1, "se_1_m: Operation not permitted" );
  TEST( se_0_nm, 0, "" );
  TEST( se_1_nm, 1, "Operation not permitted" );
  TEST( se_0_m_im, 0, "se_0_m_im" );
  TEST( se_1_m_im, 1, "se_1_m_im" );
  TEST( se_0_nm_im, 0, "" );
  TEST( se_1_nm_im, 1, "" );
  TEST( se_1u_m, 1, "se_1u_m: Operation not permitted" );

  return 0;
}


