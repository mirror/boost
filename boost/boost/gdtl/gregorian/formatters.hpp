#ifndef GREGORIAN_FORMATTERS_HPP___
#define GREGORIAN_FORMATTERS_HPP___
/* Copyright (c) 2002 CrystalClear Software, Inc.
 * Disclaimer & Full Copyright at end of file
 * Author: Jeff Garland 
 */

#include "boost/gdtl/gregorian/gregorian_types.hpp"
#include "boost/gdtl/gregorian/greg_facet.hpp"
#include "boost/gdtl/date_formatting.hpp"
#include "boost/gdtl/iso_format.hpp"
#include "boost/gdtl/date_format_simple.hpp"

namespace boost {
namespace gregorian {



  //! To YYYY-mmm-DD string where mmm 3 char month name. Example:  2002-Jan-01
  /*!\ingroup date_format
   */
  inline std::string to_simple_string(const date& d) {
    return gdtl::date_formatter<date,gdtl::simple_format>::date_to_string(d);
  }

  //! Convert date period to simple string. Example: [2002-Jan-01/2002-Jan-02]
  /*!\ingroup date_format
   */
  inline std::string to_simple_string(const date_period& d) {
    std::string s("[");
    std::string d1(gdtl::date_formatter<date,gdtl::simple_format>::date_to_string(d.begin()));
    std::string d2(gdtl::date_formatter<date,gdtl::simple_format>::date_to_string(d.last()));
    return std::string("[" + d1 + "/" + d2 + "]");
  }

  //! Date period to iso standard format CCYYMMDD/CCYYMMDD. Example: 20021225/20021231
  /*!\ingroup date_format
   */
  inline std::string to_iso_string(const date_period& d) {
    std::string s(gdtl::date_formatter<date,gdtl::iso_format>::date_to_string(d.begin()));
    return s + "/" + gdtl::date_formatter<date,gdtl::iso_format>::date_to_string(d.last());
  }


  //! Convert to iso extended format string CCYY-MM-DD. Example 2002-12-31
  /*!\ingroup date_format
   */
  inline std::string to_iso_extended_string(const date& d) {
    return gdtl::date_formatter<date,gdtl::iso_extended_format>::date_to_string(d);
  }

  //! Convert to iso standard string YYYYMMDD. Example: 20021231
  /*!\ingroup date_format
   */
  inline std::string to_iso_string(const date& d) {
    return gdtl::date_formatter<date,gdtl::iso_format>::date_to_string(d);
  }
  
  

  inline std::string to_sql_string(const date& d) 
  {
    date::ymd_type ymd = d.year_month_day();
    std::ostringstream ss;
    ss << ymd.year << "-"
       << std::setw(2) << std::setfill('0') 
       << ymd.month 
       << "-"
       << std::setw(2) << std::setfill('0') 
       << ymd.day;
    return ss.str();
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

