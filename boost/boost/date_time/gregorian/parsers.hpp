#ifndef GREGORIAN_PARSERS_HPP___
#define GREGORIAN_PARSERS_HPP___
/* Copyright (c) 2002 CrystalClear Software, Inc.
 * Disclaimer & Full Copyright at end of file
 * Author: Jeff Garland, Bart Garst
 */

#include "boost/date_time/gregorian/gregorian_types.hpp"
#include "boost/date_time/date_parsing.hpp"
#include "boost/date_time/compiler_config.hpp"
#include <string>
#include <sstream>

namespace boost {
namespace gregorian {

  //! Deprecated: Use from_simple_string
  inline date from_string(std::string s) {
    return date_time::parse_date<date>(s);
  }

  //! From delimited date string where with order year-month-day eg: 2002-1-25 or 2003-Jan-25
  inline date from_simple_string(std::string s) {
    return date_time::parse_date<date>(s);
  }
  
#if !(defined(BOOST_NO_STD_ITERATOR_TRAITS))
  //! Stream should hold a date in the form of: 2002-1-25. Month number, abbrev, or name are accepted
  /* Arguments passed in by-value for convertability of char[] 
   * to iterator_type. Calls to from_stream_type are by-reference 
   * since conversion is already done */
  template<class iterator_type>
  inline date from_stream(iterator_type beg, iterator_type end) {
    if(beg == end)
    {
      return date(not_a_date_time);
    }
    std::string s = date_time::from_stream_type(beg, end, 
	std::iterator_traits<iterator_type>::value_type());
    return date_time::parse_date<date>(s);
  }
#endif //BOOST_NO_STD_ITERATOR_TRAITS

  //! From iso type date string where with order year-month-day eg: 20020125
  inline date from_undelimited_string(std::string s) {
    return date_time::parse_undelimited_date<date>(s);
  }

} } //namespace gregorian

  
    
    




















/* Copyright (c) 2002
 * CrystalClear Software, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  CrystalClear Software makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 */
#endif

