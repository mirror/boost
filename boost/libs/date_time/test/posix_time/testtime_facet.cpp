
/* Copyright (c) 2004 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE-1.0 or http://www.boost.org/LICENSE-1.0)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include "boost/date_time/posix_time/posix_time.hpp"
//#include "boost/date_time/time_facet.hpp"
#include "boost/date_time/testfrmwk.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

template<class temporal_type, typename charT>
inline
void 
teststreaming(std::string testname, 
              temporal_type value,
              std::basic_string<charT> expected_result,
              const std::locale& locale = std::locale::classic())
{
  std::basic_stringstream<charT> ss;
  ss.imbue(locale);
  ss << value;
  check(testname, ss.str() == expected_result);
}



#if !defined(BOOST_NO_STD_WSTRING) 
static const wchar_t* long_month_names[] =
  {L"Januar",L"Februar",L"Marz",L"April",L"Mai",L"Juni",L"Juli",L"August",
   L"September",L"Oktober",L"November",L"Dezember"};
static const wchar_t* short_month_names[]=
  {L"Jan",L"Feb",L"Mar",L"Apr",L"Mai",L"Jun",L"Jul",L"Aug",
   L"Sep",L"Okt",L"Nov",L"Dez"};

std::vector<std::basic_string<wchar_t> > de_short_month_names;
std::vector<std::basic_string<wchar_t> > de_long_month_names;
#endif // 

int main() {
  using namespace boost::gregorian;
  using namespace boost::posix_time;

  try {
    date d(2004,Oct,13);
    date min_date(min_date_time);
    date max_date(max_date_time);

    date_period dp(d, d + date_duration(7));
    ptime t(d, time_duration(18,01,56));
    ptime tf = t + microseconds(3);
    time_period tp(t, tf + days(7) + time_duration(1,1,1));
    time_duration td = hours(3) + minutes(2) + seconds(1) + milliseconds(9);
    {
      std::stringstream ss;
      ss << t;
      check("Stream and to_string formats match (ptime)", 
          to_simple_string(t) == ss.str());
      std::cout << t << ' ' << td << std::endl;
      ss.str("");
      ss << tf;
      check("Stream and to_string formats match (ptime w/ fracsec)", 
          to_simple_string(tf) == ss.str());
      ss.str("");
      ss << tp;
      check("Stream and to_string formats match (time_period)", 
          to_simple_string(tp) == ss.str());
      ss.str("");
      ss << td;
      check("Stream and to_string formats match (time_duration)", 
          to_simple_string(td) == ss.str());
      std::cout << ss.str() << std::endl;

      time_facet* f = new time_facet();
      ss.imbue(std::locale(ss.getloc(), f));
      ss.str("");

      f->format("%Y-%b-%d %H:%M:%S %%d");
      f->time_duration_format("%H:%M:%S %%S");
      ss << t;
      check("Literal '%' in format", ss.str() == std::string("2004-Oct-13 18:01:56 %d"));
      ss.str("");
      ss << td;
      check("Literal '%' in time_duration format", ss.str() == std::string("03:02:01 %S"));
      ss.str("");
      f->format("%Y-%b-%d %H:%M:%S %%%d");
      f->time_duration_format("%H:%M:%S %%%S");
      ss << t;
      check("Multiple literal '%'s in format", ss.str() == std::string("2004-Oct-13 18:01:56 %13"));
      ss.str("");
      ss << td;
      check("Multiple literal '%'s in time_duration format", ss.str() == std::string("03:02:01 %01"));
      ss.str("");
    }
#if !defined(BOOST_NO_STD_WSTRING) 
    std::copy(&short_month_names[0], 
              &short_month_names[12],
              std::back_inserter(de_short_month_names));
    
    std::copy(&long_month_names[0], 
              &long_month_names[12],
              std::back_inserter(de_long_month_names));
    

    {
      wtime_facet *timefacet = new wtime_facet(wtime_facet::standard_format);
      teststreaming("widestream default classic time", t, 
                    //std::wstring(L"Wed Oct 13 18:01:56 2004"),
                    std::wstring(L"10/13/04 18:01:56"),
                    std::locale(std::locale::classic(), timefacet));
    }
    {
      wtime_facet *timefacet = new wtime_facet(wtime_facet::standard_format);
      teststreaming("widestream default classic time with fractional seconds truncated", t, 
                    //std::wstring(L"Wed Oct 13 18:01:56 2004"),
                    std::wstring(L"10/13/04 18:01:56"),
                    std::locale(std::locale::classic(), timefacet));
    }
    {
      wtime_facet *timefacet = new wtime_facet(wtime_facet::standard_format);
      teststreaming("widestream default time period with fractional seconds truncated", tp, 
                    //std::wstring(L"[Wed Oct 13 18:01:56 2004/Wed Oct 20 19:02:57 2004]"),
                    std::wstring(L"[10/13/04 18:01:56/10/20/04 19:02:57]"),
                    std::locale(std::locale::classic(), timefacet));
    }
    {
      wtime_facet *timefacet = new wtime_facet(L"%Y-%b-%d %I:%M:%S %p");
      teststreaming("widestream time in 12 hours format w/ (AM/PM)", tp.begin(), 
                    std::wstring(L"2004-Oct-13 06:01:56 PM"),
                    std::locale(std::locale::classic(), timefacet));
    }
    {
      wtime_facet *timefacet = new wtime_facet(wtime_facet::standard_format);
#ifdef BOOST_DATE_TIME_HAS_NANOSECONDS
      teststreaming("widestream time duration", td, 
                    std::wstring(L"03:02:01.009000000"),
                    std::locale(std::locale::classic(), timefacet));
#else
      teststreaming("widestream time duration", td, 
                    std::wstring(L"03:02:01.009000"),
                    std::locale(std::locale::classic(), timefacet));
#endif // BOOST_DATE_TIME_HAS_NANOSECONDS
    }

#ifdef BOOST_DATE_TIME_HAS_NANOSECONDS
    teststreaming("widestream time duration", td, 
                  std::wstring(L"03:02:01.009000000"));
#else
    teststreaming("widestream time duration", td, 
                  std::wstring(L"03:02:01.009000"));
#endif // BOOST_DATE_TIME_HAS_NANOSECONDS

    //wtime_facet *timefacet = new wtime_facet();
    //std::locale cloc = std::locale(std::locale::classic(), timefacet);
    //ss.imbue(cloc);
//     ss << L"classic date:               " << d << std::endl;
//     ss << L"classic dateperiod:         " << dp << std::endl;
    //ss << L"classic time:               " << t << std::endl;
    //ss << L"classic timefrac:           " << tf << std::endl;
    //ss << L"classic timeperiod:         " << tp << std::endl;

    {
      wtime_facet* wtimefacet = new wtime_facet(L"day: %j date: %Y-%b-%d weekday: %A time: %H:%M:%s");
#ifdef BOOST_DATE_TIME_HAS_NANOSECONDS
      teststreaming("widestream custom time facet narly format", t, 
                    std::wstring(L"day: 287 date: 2004-Oct-13 weekday: Wednesday time: 18:01:56.000000000"), 
                    std::locale(std::locale::classic(), wtimefacet));
#else
      teststreaming("widestream custom time facet narly format", t, 
                    std::wstring(L"day: 287 date: 2004-Oct-13 weekday: Wednesday time: 18:01:56.000000"), 
                    std::locale(std::locale::classic(), wtimefacet));
#endif
    }
    {
      wtime_facet* wtimefacet = new wtime_facet(L"%Y-%b-%d %H:%M:%S,%f");
#ifdef BOOST_DATE_TIME_HAS_NANOSECONDS
      teststreaming("widestream custom time fractional seconds: %Y-%b-%d %H:%M:%S,%f", t, 
                    std::wstring(L"2004-Oct-13 18:01:56,000000000"), 
                    std::locale(std::locale::classic(), wtimefacet));
#else
      teststreaming("widestream custom time fractional seconds: %Y-%b-%d %H:%M:%S,%f", t, 
                    std::wstring(L"2004-Oct-13 18:01:56,000000"), 
                    std::locale(std::locale::classic(), wtimefacet));
#endif
    }

    {
      wtime_facet* wtimefacet = new wtime_facet(L"%Y-%b-%d %H:%M:%S");
      teststreaming("widestream custom time no frac seconds: %Y-%b-%d %H:%M:%S", t, 
                    std::wstring(L"2004-Oct-13 18:01:56"), 
                    std::locale(std::locale::classic(), wtimefacet));
    }

    {
      wtime_facet* wtimefacet = new wtime_facet(L"%Y-%b-%d %H:%M:%S");
      wtimefacet->short_month_names(de_short_month_names);
      teststreaming("widestream custom time no frac seconds, german months: %Y-%b-%d %H:%M:%S", t, 
                    std::wstring(L"2004-Okt-13 18:01:56"), 
                    std::locale(std::locale::classic(), wtimefacet));
    }

    {
      wtime_facet* wtimefacet = new wtime_facet();
      wtimefacet->format(L"%B %b %Y");
      wtimefacet->short_month_names(de_short_month_names);
      wtimefacet->long_month_names(de_long_month_names);
      teststreaming("widestream custom time no frac seconds, german months: %B %b %Y", t, 
                    std::wstring(L"Oktober Okt 2004"), 
                    std::locale(std::locale::classic(), wtimefacet));
    }

    {
      wtime_facet* wtimefacet = new wtime_facet(L"%Y-%b-%d %H:%M:%S%F");
      teststreaming("widestream custom time no frac seconds %F operator: %Y-%b-%d %H:%M:%S%F", t, 
                    std::wstring(L"2004-Oct-13 18:01:56"), 
                    std::locale(std::locale::classic(), wtimefacet));
    }

    {
      wtime_facet* wtimefacet = new wtime_facet(L"%Y-%b-%d %H:%M:%S%F");
#ifdef BOOST_DATE_TIME_HAS_NANOSECONDS
      teststreaming("widestream custom time with frac seconds %F operator: %Y-%b-%d %H:%M:%S%F", tf, 
                    std::wstring(L"2004-Oct-13 18:01:56.000003000"), 
                    std::locale(std::locale::classic(), wtimefacet));
#else
      teststreaming("widestream custom time with frac seconds %F operator: %Y-%b-%d %H:%M:%S%F", tf, 
                    std::wstring(L"2004-Oct-13 18:01:56.000003"), 
                    std::locale(std::locale::classic(), wtimefacet));
#endif // BOOST_DATE_TIME_HAS_NANOSECONDS
    }
    {
      wtime_facet* wtimefacet = new wtime_facet();
      wtimefacet->set_iso_format();
#ifdef BOOST_DATE_TIME_HAS_NANOSECONDS
      teststreaming("widestream custom time iso format", tf, 
                    std::wstring(L"20041013T180156.000003000"), 
                    std::locale(std::locale::classic(), wtimefacet));
#else
      teststreaming("widestream custom time iso format", tf, 
                    std::wstring(L"20041013T180156.000003"), 
                    std::locale(std::locale::classic(), wtimefacet));
#endif // BOOST_DATE_TIME_HAS_NANOSECONDS
    }
    {
      wtime_facet* wtimefacet = new wtime_facet();
      wtimefacet->set_iso_extended_format();
#ifdef BOOST_DATE_TIME_HAS_NANOSECONDS
      teststreaming("widestream custom time iso extended format", tf, 
                    std::wstring(L"2004-10-13 18:01:56.000003000"), 
                    std::locale(std::locale::classic(), wtimefacet));
#else
      teststreaming("widestream custom time iso extended format", tf, 
                    std::wstring(L"2004-10-13 18:01:56.000003"), 
                    std::locale(std::locale::classic(), wtimefacet));
#endif // BOOST_DATE_TIME_HAS_NANOSECONDS
    }


    {
      wtime_facet* wtimefacet = new wtime_facet(L"%Y-%b-%d %H:%M:%S%F");
#ifdef BOOST_DATE_TIME_HAS_NANOSECONDS
      teststreaming("widestream time period frac seconds %F operator: %Y-%b-%d %H:%M:%S%F", tp, 
                    std::wstring(L"[2004-Oct-13 18:01:56/2004-Oct-20 19:02:57.000002999]"), 
                    std::locale(std::locale::classic(), wtimefacet));
#else
      teststreaming("widestream time period frac seconds %F operator: %Y-%b-%d %H:%M:%S%F", tp, 
                    std::wstring(L"[2004-Oct-13 18:01:56/2004-Oct-20 19:02:57.000002]"), 
                    std::locale(std::locale::classic(), wtimefacet));
#endif // BOOST_DATE_TIME_HAS_NANOSECONDS
    }

    {
      wtime_facet* wtimefacet = new wtime_facet(L"%Y-%b-%d %H:%M:%s");
      wperiod_formatter pf(wperiod_formatter::AS_OPEN_RANGE, L" / ", L"[ ", L" )", L" ]");
      wtimefacet->period_formatter(pf);

#ifdef BOOST_DATE_TIME_HAS_NANOSECONDS
      teststreaming("widestream custom time : %Y-%b-%d %H:%M:%s", tp, 
                    std::wstring(L"[ 2004-Oct-13 18:01:56.000000000 / 2004-Oct-20 19:02:57.000003000 )"), 
                    std::locale(std::locale::classic(), wtimefacet));
#else
      teststreaming("widestream custom time : %Y-%b-%d %H:%M:%s", tp, 
                    std::wstring(L"[ 2004-Oct-13 18:01:56.000000 / 2004-Oct-20 19:02:57.000003 )"), 
                    std::locale(std::locale::classic(), wtimefacet));
#endif // BOOST_DATE_TIME_HAS_NANOSECONDS
    }


    {
      ptime nt(not_a_date_time);
      teststreaming("widestream custom time : not a datetime", nt,
                    std::wstring(L"not-a-date-time"));
    }




//     //Denmark English has iso extended default format...
//     std::locale gloc("en_DK"); 
//     ss.imbue(gloc);
//     ss << L"default english-denmark date:        " << d << std::endl;
//     ss << L"default english-denmark dateperiod:  " << dp << std::endl;
//     ss << L"default english-denmark time:        " << t << std::endl;
//     ss << L"default english-denmark timefrac:    " << tf << std::endl;
//     ss << L"default english-denmark timeperiod:  " << tp << std::endl;



#endif 
  }
  catch(std::exception& e) {
    std::cout << "Caught std::exception: " << e.what() << std::endl;
  }
  catch(...) {
    std::cout << "bad exception" << std::endl;
  }

  return printTestStats();
}

