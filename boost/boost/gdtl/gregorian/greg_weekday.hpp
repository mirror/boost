#ifndef GREG_WEEKDAY_HPP___
#define GREG_WEEKDAY_HPP___
/* Copyright (c) 2000 CrystalClear Software, Inc.
 * Disclaimer & Full Copyright at end of file
 * Author: Jeff Garland
 */

#include "boost/gdtl/constrained_value.hpp"
#include "boost/gdtl/date_defs.hpp"
#include <stdexcept>

namespace boost {
namespace gregorian {

  //bring enum values into the namespace
  using gdtl::Sunday;
  using gdtl::Monday;
  using gdtl::Tuesday;
  using gdtl::Wednesday;
  using gdtl::Thursday;
  using gdtl::Friday;
  using gdtl::Saturday;


  //! Exception that flags that a weekday number is incorrect
  struct bad_weekday : public std::out_of_range
  {
    bad_weekday() : std::out_of_range("Weekday os out of range 0..6") {}
  };
  typedef CV::simple_exception_policy<unsigned short, 0, 6, bad_weekday> greg_weekday_policies;
  typedef CV::constrained_value<greg_weekday_policies> greg_weekday_rep;


  //! Represent a day within a week (range 0==Sun to 6==Sat)
  class greg_weekday : public greg_weekday_rep {
  public:
    greg_weekday(unsigned short day_of_week_num) :
      greg_weekday_rep(day_of_week_num)
    {}

    unsigned short as_number() const {return value_;}
    const char* as_short_string() const;
    const char* as_long_string()  const;

  };



} } //namespace gregorian

/* Copyright (c) 2000
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
