
#include "boost/gdtl/gregorian/gregorian.hpp"
#include "boost/gdtl/testfrmwk.hpp"
#include <iostream>
#include <string>
 

int
main() 
{


// Examples from 8601
// Full date
// Extended CCYY-MM-DD
  std::string s("2001-10-5");

  //This one aborts gcc2.95.3 on mandrake 8.1 linux with
  //bad lexical cast?
  try {
    boost::gregorian::date d(boost::gregorian::from_string(s));
    std::cout << "here" << std::endl;
    check("check year",  d.year()  == 2001);
    check("check month", d.month() == 10);
    check("check day",   d.day()   == 5);
  }
  catch(std::exception& e) {
    check("parse 2001-10-5",  false);
    std::cout << "Fail: " << e.what() << std::endl;
  }

  try {
    std::string s2("2001-12-41"); //oops should be 31
    boost::gregorian::date bad_day(boost::gregorian::from_string(s2)); //won't construct
    check("check bad day", false);
    //The line below won't execute, but make the compiler think
    //we are using bad day....
    std::cout << "Oh oh, this shouldn't be reached: "
	      << boost::gregorian::to_iso_string(bad_day) << std::endl;

  }
  catch(boost::gregorian::bad_day_of_month) { //expected
    check("check bad day", true);
  }
  catch(std::exception& e) {
    //oops wrong exception
    check("check bad day",  false);
    std::cout << "Fail: " << e.what() << std::endl;
  }

  try {
    std::string s2("2001-14-1"); //oops should be <= 12
    boost::gregorian::date bad_month(boost::gdtl::parse_date<boost::gregorian::date>(s2));
    check("check bad month", false); //fail the test
    //The line below won't execute, but make the compiler think
    //we are using bad day....
    std::cout << "Oh oh, this shouldn't be reached: "
	      << boost::gregorian::to_iso_string(bad_month) << std::endl;

  }
  catch(boost::gregorian::bad_month) { //expected
    check("check bad month", true);
  }
  catch(std::exception& e) {
    //oops wrong exception
    check("check bad month",  false);
    std::cout << "Fail: " << e.what() << std::endl;
  }

  //This one aborts gcc2.95.3 on mandrake 8.1 linux with
  //bad lexical cast?
  try {
    //Example of ISO Standard -- CCYYMMDD
    using namespace boost::gregorian;
    std::string ud("20011009"); //2001-Oct-09
    date d1(boost::gregorian::from_undelimited_string(ud));
    //  std::cout << to_string(d1) << std::endl;
    check("undelimited date string", d1 == date(2001,Oct,9));
    
  
    std::string ad("2001/10/09");
    date d2(boost::gdtl::parse_date<date>(ad));
    check("check american date",  d2  == date(2001,Oct,9));
  }
  catch(std::exception& e) {
    check("more parsing",  false);
    std::cout << "Fail: " << e.what() << std::endl;
  }

//   std::string s1("2001-Oct-5");
//   gregorian::date d1(parse_date<gregorian::date>(s1));
//    check("check month", d1.month() == 10);
  




//Calendar Week + Day Number
// CCYYWwwDThhmmss
// 1986W105T
// week == 10 day=5
// see page 5


//Duration rep
//CCYYMMDDThhmmss/PnYnMnDTnHnMnS

  printTestStats();

  return 0;
}
