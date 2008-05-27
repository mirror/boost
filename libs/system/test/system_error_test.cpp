//  system_error_test.cpp  ---------------------------------------------------//

//  Copyright Beman Dawes 2006

//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/system

//----------------------------------------------------------------------------// 

#include <boost/config/warning_disable.hpp>

#include <boost/test/minimal.hpp>
#include <boost/system/system_error.hpp>
#include <iostream>

#ifdef BOOST_WINDOWS_API
#include <windows.h>
#endif

using boost::system::system_error;
using boost::system::error_code;
using boost::system::system_category;

#define TEST(x,v,w) test(#x,x,v,w)

namespace
{
  void test( const char * desc, const system_error & ex,
    int v, const char * str )
  {
    std::cout << "test " << desc << "\n what() returns \"" << ex.what() << "\"\n";
    BOOST_CHECK( ex.code().value() == v );
    BOOST_CHECK( ex.code().category() == system_category );
# ifdef BOOST_WINDOWS_API
    LANGID language_id;
#   if !defined(__MINGW32__) && !defined(__CYGWIN__)
      language_id = ::GetUserDefaultUILanguage();
#   else
      language_id = 0x0409; // Assume US English
#   endif
    // std::cout << "GetUserDefaultUILanguage() returns " << language_id << '\n';
    if ( language_id == 0x0409 )  // English (United States)
    {
      BOOST_CHECK( std::string( ex.what() ) == str );
      if ( std::string( ex.what() ) != str )
        std::cout << "expected \"" << str << "\", but what() returned \""
          << ex.what() << "\"\n";
    }
# endif
  }

  const boost::uint_least32_t uvalue = 1u;
}

int test_main( int, char *[] )
{
  // all combinations of constructors:

  system_error se_0_m( error_code(0, system_category), "se_0_m" ); 
  system_error se_1_m( 1, system_category, "se_1_m" ); 
  system_error se_0_nm( error_code(0, system_category), "" ); 
  system_error se_1_nm( 1, system_category, "" ); 
  system_error se_0_nmx( error_code(0, system_category), "" ); 
  system_error se_1_nmx( 1, system_category, "" ); 
  system_error se_1u_m( uvalue, system_category, "se_1u_m" );

  TEST( se_0_m, 0, "se_0_m" );
  TEST( se_1_m, 1, "se_1_m: Incorrect function" );
  TEST( se_0_nm, 0, "" );
  TEST( se_1_nm, 1, "Incorrect function" );
  TEST( se_0_nmx, 0, "" );
  TEST( se_1_nmx, 1, "Incorrect function" );
  TEST( se_1u_m, 1, "se_1u_m: Incorrect function" );


  return 0;
}


