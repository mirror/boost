//  boost cstdint.hpp header file  -------------------------------------------//

//  (C) Copyright boost.org 1999. Permission to copy, use, modify, sell
//  and distribute this software is granted provided this copyright
//  notice appears in all copies. This software is provided "as is" without
//  express or implied warranty, and with no claim as to its suitability for
//  any purpose.

//  See http://www.boost.org for most recent version including documentation.

//  Revision History
//   22 Sep 00  Better 64-bit support (John Maddock)
//   29 Jun 00  Reimplement to avoid including stdint.h within namespace boost
//    8 Aug 99  Initial version (Beman Dawes)

#ifndef BOOST_CSTDINT_HPP
#define BOOST_CSTDINT_HPP

#include <limits.h> // implementation artifact; not part of interface

#include <boost/stdint.h>

namespace boost
{

  using ::int8_t;             
  using ::int_least8_t;       
  using ::int_fast8_t;        
  using ::uint8_t;            
  using ::uint_least8_t;      
  using ::uint_fast8_t;       
                     
  using ::int16_t;            
  using ::int_least16_t;      
  using ::int_fast16_t;       
  using ::uint16_t;           
  using ::uint_least16_t;     
  using ::uint_fast16_t;      
                     
  using ::int32_t;            
  using ::int_least32_t;      
  using ::int_fast32_t;       
  using ::uint32_t;           
  using ::uint_least32_t;     
  using ::uint_fast32_t;      
                     
#ifndef BOOST_NO_INT64_T

  using ::int64_t;            
  using ::int_least64_t;      
  using ::int_fast64_t;       
  using ::uint64_t;           
  using ::uint_least64_t;     
  using ::uint_fast64_t;      
                     
#endif

  using ::intmax_t;      
  using ::uintmax_t;     

} // namespace boost

#endif
