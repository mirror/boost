/* Copyright (c) 2002,2003,2004 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE-1.0 or http://www.boost.org/LICENSE-1.0)
 * Author: Jeff Garland, Bart Garst
 */
 
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/time_serialize.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/date_time/testfrmwk.hpp>
#include <fstream>

using namespace boost;
using namespace posix_time;
using namespace gregorian;

int main(){
  // originals
  date d(2002, Feb, 14);
#if defined(BOOST_DATE_TIME_POSIX_TIME_STD_CONFIG)
  time_duration td(12,13,52,123456789);
#else
  time_duration td(12,13,52,123456);
#endif
  ptime pt(d, td);
  time_period tp(pt, ptime(date(2002, Oct, 31), hours(19)));

  // for loading in from archive
  date d2(not_a_date_time);
  time_duration td2(1,0,0);
  ptime pt2(d2, td2);
  time_period tp2(pt2, hours(1));
  
  std::ofstream ofs("tmp_file");
  archive::text_oarchive oa(ofs);

  try{
    oa << pt;
    oa << tp;
    oa << td;
  }catch(archive::archive_exception ae){
    std::string s(ae.what());
    check("Error writing to archive: " + s, false);
    ofs.close();
    return printTestStats();
  }

  ofs.close();

  std::ifstream ifs("tmp_file");
  archive::text_iarchive ia(ifs);

  try{
    ia >> pt2;
    ia >> tp2;
    ia >> td2;
  }catch(archive::archive_exception ae){
    std::string s(ae.what());
    check("Error readng from archive: " + s, false);
    ifs.close();
    return printTestStats();
  }

  ifs.close();
 
  check("ptime", pt == pt2);
  check("time_period", tp == tp2);
  check("time_duration", td == td2);

  return printTestStats();
}
