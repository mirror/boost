
#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/testfrmwk.hpp"
#include <iostream>

int
main() 
{

  using namespace boost::gregorian;

  partial_date pd(1,1);
  date d = pd.get_date(2000);
  check("Partial date getdate",     date(2000,1,1) == d);
  d = pd.get_date(2001);
  check("Partial date getdate",     date(2001,1,1) == d);

  typedef boost::date_time::last_kday_of_month<date> lastkday;

  //Find last Sunday in Feb
  lastkday lsif(Sunday, Feb);
  std::cout << to_simple_string(lsif.get_date(2002)) << std::endl; //24th
  check("Last kday",     date(2002,Feb,24) == lsif.get_date(2002));
  lastkday ltif(Thursday, Feb);
  check("Last kday",     date(2002,Feb,28) == ltif.get_date(2002));
  lastkday lfif(Friday, Feb);
  check("Last kday",     date(2002,Feb,22) == lfif.get_date(2002));

  typedef boost::date_time::first_kday_of_month<date> firstkday;

  firstkday fsif(Sunday, Feb);
  std::cout << to_simple_string(fsif.get_date(2002)) << std::endl; //24th
  check("First kday",     date(2002,Feb,3) == fsif.get_date(2002));
  firstkday ftif(Thursday, Feb);
  check("First kday",     date(2002,Feb,7) == ftif.get_date(2002));
  firstkday ffif(Friday, Feb);
  check("First kday",     date(2002,Feb,1) == ffif.get_date(2002));
  
  typedef boost::date_time::first_kday_after<date> firstkdayafter;
  firstkdayafter fkaf(Monday);
  std::cout << to_simple_string(fkaf.get_date(date(2002,Feb,1)))
            << std::endl; //feb 4
  check("kday after",date(2002,Feb,4) == fkaf.get_date(date(2002,Feb,1)));
  firstkdayafter fkaf2(Thursday);
  check("kday after",date(2002,Feb,7) == fkaf2.get_date(date(2002,Feb,1)));
  check("kday after",date(2002,Feb,28)== fkaf2.get_date(date(2002,Feb,21)));

  typedef boost::date_time::first_kday_before<date> firstkdaybefore;
  firstkdaybefore fkbf(Monday);
  std::cout << to_simple_string(fkaf.get_date(date(2002,Feb,10)))
            << std::endl; //feb 4
  check("kday before",date(2002,Feb,4) == fkbf.get_date(date(2002,Feb,10)));
  firstkdaybefore fkbf2(Thursday);
  check("kday before",date(2002,Jan,31) == fkbf2.get_date(date(2002,Feb,1)));
  check("kday before",date(2002,Feb,7)== fkbf2.get_date(date(2002,Feb,14)));
  
  return printTestStats();

};
