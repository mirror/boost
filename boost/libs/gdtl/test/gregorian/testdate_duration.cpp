
#include "boost/gdtl/gregorian/gregorian.hpp"
#include "boost/gdtl/testfrmwk.hpp"
#include <iostream>


void test_date_duration()
{
  using namespace boost::gregorian;
  
  date_duration threeDays(3);
  date_duration twoDays(2);
  //date_duration zeroDays(0);
  check("Self equal case",       threeDays == threeDays);
  check("Not equal case",        !(threeDays == twoDays));
  check("Less case succeed",     twoDays < threeDays);
  check("Not less case",         !(threeDays < twoDays));
  check("Not less case - equal", !(threeDays < threeDays));
  check("Greater than ",         !(threeDays > threeDays));
  check("Greater equal ",        threeDays >= threeDays);
  check("Greater equal - false", !(twoDays >= threeDays));
  check("add", twoDays + threeDays == date_duration(5));
  date_duration derivedOneDay = threeDays - twoDays;
  check("Subtraction - neg result", twoDays - threeDays == date_duration(-1));
  date_duration oneDay(1);
  check("Subtraction",           oneDay == derivedOneDay);

//   date_duration dd(1);
//   dd++;
//   check("Increment",             dd == twoDays);

}

int main() {
  test_date_duration();
  printTestStats();
  return 0;
};
