#ifndef BOOST_DATE_TIME_LOCAL_TIME_IO_HPP__
#define BOOST_DATE_TIME_LOCAL_TIME_IO_HPP__

/* Copyright (c) 2003-2004 CrystalClear Software, Inc.
 * Subject to the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE-1.0 or http://www.boost.org/LICENSE-1.0)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include <iostream>
#include "boost/date_time/local_time/local_date_time.hpp"
#include "boost/date_time/time_facet.hpp"

namespace boost {
namespace local_time {
  //! operator<< for local_date_time - see local_time docs for formatting details
  template<class CharT, class TraitsT>
  inline
  std::basic_ostream<CharT, TraitsT>&
  operator<<(std::basic_ostream<CharT, TraitsT>& os, const local_date_time& ldt)
  {
    typedef local_date_time time_type;//::utc_time_type typename 
    typedef date_time::time_facet<time_type, CharT> custom_time_facet;
    typedef std::time_put<CharT> std_time_facet;
    std::ostreambuf_iterator<CharT> oitr(os);
    
    if(std::has_facet<custom_time_facet>(os.getloc())) {
      std::use_facet<custom_time_facet>(os.getloc()).put(oitr, 
                                                         os, 
                                                         os.fill(), 
                                                         ldt);
    }
    else {
      custom_time_facet* f = new custom_time_facet();
      std::locale l = std::locale(os.getloc(), f);
      os.imbue(l);
      f->put(oitr, os, os.fill(), ldt);
    }

    return os;
  }

  
} } // namespaces

#endif // BOOST_DATE_TIME_LOCAL_TIME_IO_HPP__
