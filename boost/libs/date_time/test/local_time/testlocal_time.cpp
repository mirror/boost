/* Copyright (c) 2003-2004 CrystalClear Software, Inc.
 * Subject to the Boost Software License, Version 1.0. 
 * (See accompanying file LICENSE-1.0 or http://www.boost.org/LICENSE-1.0)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */


#include "boost/date_time/local_time/time_zone.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/date_time/local_time/local_time.hpp"
#include "boost/date_time/local_time/posix_time_zone.hpp"
#include "boost/date_time/testfrmwk.hpp"
#include <iostream>

int
main()
{

  using namespace boost::gregorian;
  using namespace boost::posix_time;
  using namespace boost::local_time;

  try {
    boost::shared_ptr<time_zone_base> az_tz(new posix_time_zone("MST-07"));
    date d(2003, 12, 20);
    hours h(12);
    ptime t(d,h);
    local_date_time az_time(t, az_tz);
    
    check("compare utc and az time", az_time == (t + hours(7)));
    // doesn't work? why the above line works    check("compare utc and az time", az_time > t );
    check("Zone abbreviation", az_time.zone()->std_zone_abbrev() == std::string("MST"));
    check("base offset", az_time.zone()->base_utc_offset() == hours(-7));
    check("base offset", az_time.zone()->has_dst() == false);
    check("check utc time is 7 hours ahead " + to_simple_string(az_time.utc_time()), 
          az_time.utc_time() == t+hours(7));
    check("is_dst check", az_time.is_dst() == false);
    check("to_string: " + az_time.to_string(), 
          az_time.to_string() == "2003-Dec-20 12:00:00 MST");
    
    std::cout << "Checking copy construction" << std::endl;
    local_date_time az_time2(az_time); //copy constructor
    // Now test the copy
    check("check utc time is 7 hours ahead " + to_simple_string(az_time2.utc_time()), 
          az_time2.utc_time() == t+hours(7));
    check("is_dst check", az_time2.is_dst() == false);
    check("to_string: " + az_time2.to_string(), 
          az_time2.to_string() == "2003-Dec-20 12:00:00 MST");
    
    //Now construct with a date and time
    std::cout << "Checking construct with date and time_duration" << std::endl;
    local_date_time az_time3(d, h, az_tz, false);
    check("Zone abbreviation", az_time3.zone()->std_zone_abbrev() == std::string("MST"));
    check("base offset", az_time3.zone()->base_utc_offset() == hours(-7));
    check("base offset", az_time3.zone()->has_dst() == false);
    check("check utc time is 7 hours ahead " + to_simple_string(az_time3.utc_time()), 
          az_time3.utc_time() == t+hours(7));
    check("is_dst check", az_time3.is_dst() == false);
    check("to_string: " + az_time3.to_string(), 
          az_time3.to_string() == "2003-Dec-20 12:00:00 MST");
    
    
    std::cout << "Test conversion of time zone from Arizona to New York" << std::endl;
    boost::shared_ptr<time_zone_base> ny_tz(new posix_time_zone("EST-05EDT,M4.1.0,M10.5.0"));
    local_date_time ny_time = az_time.local_time_in(ny_tz);
    //TODO fix    check("Check ny_time and az_time are equal", ny_time == az_time);
    check("Zone abbreviation", ny_time.zone()->std_zone_abbrev() == std::string("EST"));
    check("base offset", ny_time.zone()->base_utc_offset() == hours(-5));
    check("base offset", ny_time.zone()->has_dst() == true);
    check("to_string: " + ny_time.to_string(), 
          ny_time.to_string() == "2003-Dec-20 14:00:00 EST");
    ny_time += hours(3);
    check("to_string after add 3 hours: " + ny_time.to_string(), 
          ny_time.to_string() == "2003-Dec-20 17:00:00 EST");
    
    std::cout << ny_time.to_string() << std::endl;
  }
  catch(std::exception& e) {
    check(std::string("test failed due to exception: ") + e.what(), false);
  }

  return printTestStats();
}

