#ifndef POSIX_TIME_DURATION_HPP___
#define POSIX_TIME_DURATION_HPP___
/* Copyright (c) 2002 CrystalClear Software, Inc.
 * Disclaimer & Full Copyright at end of file
 * Author: Jeff Garland
 */

#include "boost/date_time/posix_time/posix_time_config.hpp"

namespace boost {
namespace posix_time {

  //! Allows expression of durations as an hour count
  /*! \ingroup time_basics
   */
  class hours : public time_duration
  {
  public:
    explicit hours(long h) :
      time_duration(h,0,0)
    {}
  };

  //! Allows expression of durations as a minute count
  /*! \ingroup time_basics
   */
  class minutes : public time_duration
  {
  public:
    explicit minutes(long m) :
      time_duration(0,m,0)
    {}
  };

  //! Allows expression of durations as a seconds count
  /*! \ingroup time_basics
   */
  class seconds : public time_duration
  {
  public:
    explicit seconds(long s) :
      time_duration(0,0,s)
    {}
  };



#if defined(BOOST_DATE_TIME_HAS_NANOSECONDS)

  //! Allows expression of durations as milli seconds
  /*! \ingroup time_basics
   */
  typedef date_time::subsecond_duration<time_duration, 1000000> millisec;

  //! Allows expression of durations as micro seconds
  /*! \ingroup time_basics
   */
  typedef date_time::subsecond_duration<time_duration, 1000> microsec;

  //! Allows expression of durations as nano seconds
  /*! \ingroup time_basics
   */
  typedef date_time::subsecond_duration<time_duration, 1> nanosec;


#endif

#if defined(BOOST_DATE_TIME_HAS_MICROSECONDS) && (!defined(BOOST_DATE_TIME_HAS_NANOSECONDS))

  //! Allows expression of durations as milli seconds
  /*! \ingroup time_basics
   */
  typedef date_time::subsecond_duration<time_duration, 1000> millisec;

  //! Allows expression of durations as micro seconds
  /*! \ingroup time_basics
   */
  typedef date_time::subsecond_duration<time_duration, 1>    microsec;

#endif



} }//namespace posix_time

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
 *
 */

#endif

