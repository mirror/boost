//  boost cstdint.hpp test program  ------------------------------------------//

//  (C) Copyright Beman Dawes 2000. Permission to copy, use, modify, sell
//  and distribute this software is granted provided this copyright
//  notice appears in all copies. This software is provided "as is" without
//  express or implied warranty, and with no claim as to its suitability for
//  any purpose.

//  See http://www.boost.org for most recent version including documentation.

//  Revision History
//   28 Jun 00  Initial version

#include <boost/cstdint.hpp>
#include <cassert>
#include <iostream>

#ifdef NDEBUG
#error This test makes no sense with NDEBUG defined
#endif

int main()
{
  boost::int8_t          int8          = -127;        
  boost::int_least8_t    int_least8    = -127;    
  boost::int_fast8_t     int_fast8     = -127;

  boost::uint8_t         uint8         = 255;       
  boost::uint_least8_t   uint_least8   = 255; 
  boost::uint_fast8_t    uint_fast8    = 255;
  
  boost::int16_t         int16         = -32767;       
  boost::int_least16_t   int_least16   = -32767; 
  boost::int_fast16_t    int_fast16    = -32767;
  
  boost::uint16_t        uint16         = 65535;       
  boost::uint_least16_t  uint_least16   = 65535; 
  boost::uint_fast16_t   uint_fast16    = 65535;
  
  boost::int32_t         int32         = -2147483647;       
  boost::int_least32_t   int_least32   = -2147483647; 
  boost::int_fast32_t    int_fast32    = -2147483647;
  
  boost::uint32_t        uint32        = 4294967295;      
  boost::uint_least32_t  uint_least32  = 4294967295;
  boost::uint_fast32_t   uint_fast32   = 4294967295; 

  boost::intmax_t        intmax        = -2147483647; 
  boost::uintmax_t       uintmax       = 4294967295;

  assert( int8 == -127 );
  assert( int_least8 == -127 );
  assert( int_fast8 == -127 );
  assert( uint8 == 255 );
  assert( uint_least8 == 255 );
  assert( uint_fast8 == 255 );
  assert( int16 == -32767 );
  assert( int_least16 == -32767 );
  assert( int_fast16 == -32767 );
  assert( uint16 == 65535 );
  assert( uint_least16 == 65535 );
  assert( uint_fast16 == 65535 );
  assert( int32 == -2147483647 );
  assert( int_least32 == -2147483647 );
  assert( int_fast32 == -2147483647 );
  assert( uint32 == 4294967295 );
  assert( uint_least32 == 4294967295 );
  assert( uint_fast32 == 4294967295 );
  assert( intmax == -2147483647 );
  assert( uintmax == 4294967295 );

  std::cout << "OK\n";
  return 0;
}