//  error_code_user_test.cpp  ------------------------------------------------//

//  Copyright Beman Dawes 2006

//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/system

//  ------------------------------------------------------------------------  //
//  This code demonstrates creation and use of a new category of error codes.

//  The motivation was a Boost posting by Christopher Kohlhoff on June 28, 2006.

#include <boost/system/error_code.hpp>
#include <boost/cerrno.hpp>

//  ------------------------------------------------------------------------  //

//  header asio.hpp

#define BOO_BOO 12345  // this could also be a constant; a macro is used for
                       // illustration because many older API's define errors
                       // via macro.
namespace boost
{
  namespace asio
  {
    // asio declares have its own error_category:
    extern system::error_category asio_error;
    
    namespace error
    {
      extern boost::system::error_code boo_boo;
    }

    void boo_boo( boost::system::error_code & ec );
  }
}

//  ------------------------------------------------------------------------  //

//  implementation file asio.cpp:

namespace boost
{
  namespace asio
  {

    system::error_category asio_error = system::error_code::new_category();

    namespace error
    {
      boost::system::error_code boo_boo( BOO_BOO, asio_error );
    }

    //  function sets ec arg to boo_boo
    void boo_boo( boost::system::error_code & ec )
    {
      ec = error::boo_boo;
    }
  }
}

//  ------------------------------------------------------------------------  //

//  a user program:


// #include <asio.hpp>
#include <boost/test/minimal.hpp>

int test_main( int, char *[] )
{
  boost::system::error_code ec;
  boost::asio::boo_boo( ec );

  BOOST_CHECK( ec );
  BOOST_CHECK( ec == boost::asio::error::boo_boo );
  BOOST_CHECK( ec.value() == BOO_BOO );
  BOOST_CHECK( ec.category() == boost::asio::asio_error );

  // a real user can't rely on the value of an error_category object's value,
  // but in this test program that value is known, so test for it.
  BOOST_CHECK( ec.category().value() == boost::system::native_ecat.value()+1 );

  // asio did not supply decoders, so test the defaults
  BOOST_CHECK( ec.to_errno() == EOTHER );
  BOOST_CHECK( ec.message() == "API error" );
  BOOST_CHECK( ec.wmessage() == L"API error" );
  return 0;
}
