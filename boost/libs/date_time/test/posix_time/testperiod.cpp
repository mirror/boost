#include <iostream>
#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/date_time/posix_time/time_period.hpp"
#include "boost/date_time/testfrmwk.hpp"

int main() 
{
  using namespace boost::gregorian;
  using namespace boost::posix_time;
  date d1(2001,Jan, 1);
  ptime t1 (d1,hours(2));//2001-Jan-1 02:00:00
  ptime t2 (d1,hours(3));//2001-Jan-1 03:00:00
  time_period p1(t1,t2); //2001-Jan-1 02:59:59
  time_period p2(p1);
  check("copy construct & ==", p1 == p2);
  time_period p3 = p2;
  check("assignment", p3 == p2);
  time_period p4(t1,hours(1));
  std::cout << to_simple_string(t1) << std::endl;
  std::cout << to_simple_string(p4) << std::endl;
  std::cout << to_simple_string(p1) << std::endl;
  check("construction and ==", p1 == p4);
  check("begin", p1.begin() == t1);
  check("last",  p1.end()   == t2);
  check("end",   p1.last()  == t2-time_duration::unit());
  
  std::cout << to_simple_string(p1) << std::endl;
  //  check("last",  p1.()  == t2);
  check("contains begin", p1.contains(t1));
  check("contains end-not", !p1.contains(t2));
  check("contains last",  p1.contains(t2-seconds(1)));
  ptime t3(date(2001,Jan,1),hours(4));
  time_period p5(t2,t3);
  check("check contains", !p1.contains(p5.begin()));
  check("check contains", !p5.contains(p1.begin()));
  check("operator== not equal case", !(p1 == p5));
  check("less than order", p1 < p5);
  check("greater than order", p5 > p1);
  check("not equal", p5 != p1);
  check("intersects with myself", p1.intersects(p1));
  check("not intersects", !(p1.intersects(p5)));
  check("not intersects", !(p5.intersects(p1)));

  time_period p6(p5);
  p6.shift(minutes(30));
  std::cout << to_simple_string(p5) << std::endl;
  std::cout << to_simple_string(p6) << std::endl;
  check("shifted intersects",    p5.intersects(p6));
  check("shifted intersects",    p6.intersects(p5));
  check("contains begin",        p5.contains(p6.begin()));
  p6.shift(minutes(30));
  std::cout << to_simple_string(p5) << std::endl;
  std::cout << to_simple_string(p6) << std::endl;
  check("shifted !intersects",    !p5.intersects(p6));
  check("shifted !intersects",    !p6.intersects(p5));
  p6.shift(minutes(-30));
  std::cout << to_simple_string(p5) << std::endl;
  std::cout << to_simple_string(p6) << std::endl;
  time_period p7 = p5.intersection(p6);
  std::cout << to_simple_string(p7) << std::endl;
  check("shifted intersection",    
	p7 == time_period(ptime(d1,time_duration(3,30,0)),
			  ptime(d1,time_duration(4,0,0))));
//   date_period p4(date(1999,Dec,1), d2);
//   check("intersects", p1.intersects(p4));
//   check("intersects", p4.intersects(p1));
//   date_period p5(date(1999,Dec,1), date(2000,Dec,31));
//   check("intersects", p1.intersects(p5));
//   check("intersects", p5.intersects(p1));
//   date_period p6(date(2000,Jan,1),date(2000,Dec,31));
//   check("contains period", p5.contains(p6));
//   check("contains period equal", p6.contains(p6));
//   check("not contains period", !p6.contains(p5));
  
//   //shift test
//   p1.shift(fourDays); //from 2000-Jan-01--2000-Jan-04
//   date_period shifted(date(2000,Jan,5),date(2000,Jan,8));
//   //   std::cout << to_string(p1.begin()) <<"--" 
//   // 	    << to_string(p1.last()) << std::endl;
//   check("shift", p1 == shifted);
  

//   //intersection tests
//   date_period i1(date(2000,Jan,5), date(2000,Jan,10));
//   date_period i2(date(2000,Jan,1), date(2000,Jan,7));
//   date_period r1(date(2000,Jan,5), date(2000,Jan,7));
//   //case 1    [5 -10) intersect [1-7) ->  [5-7)
//   check("intersect case1", i1.intersection(i2) == r1);
//   check("intersect case1", i2.intersection(i1) == r1);
//   //case 2    [5 -10) intersect [1-15) -> [5-10)
//   date_period i3(date(2000,Jan,1), date(2000,Jan,15));
//   check("intersect case2", i1.intersection(i3) == i1);
//   check("intersect case2", i3.intersection(i1) == i1);
//   //case 3    [5-10) intersect [7-15)  -> [7-10)
//   date_period i4(date(2000,Jan,7), date(2000,Jan,10));
//   date_period r2(date(2000,Jan,7), date(2000,Jan,10));
//   check("intersect case3", i1.intersection(i4) == r2);
//   check("intersect case3", i4.intersection(i1) == r2);
//   //case 4    [5-10) interset [6-9)  -> [6-9)
//   date_period i5(date(2000,Jan,6), date(2000,Jan,9));
//   check("intersect case4", i1.intersection(i5) == i5);
//   check("intersect case4", i5.intersection(i1) == i5);
//   //case 5 no intersection [1-7) intersect [7-10)
//   check("no intersection", i2.intersection(i4).is_null());

//   //case 1    [5 -10) merge [1-7) ->  [1-10)
//   date_period r3(date(2000,Jan,1), date(2000,Jan,10));
//   //  std::cout << to_iso_string(i1.merge(i2).begin()) << "/" << to_iso_string(i1.merge(i2).last()) << std::endl;
//   check("[5 -10) merge [1-7) ->  [1-10)", i1.merge(i2) == r3);
//   check("[1 -7)  merge [7-10) ->  null", i2.merge(i4).is_null());
//   date_period r4(date(2000,Jan,5), date(2000,Jan,10));
//   check("[5 -10) merge [6-9)  -> [5-10)", i1.merge(i5) == r4);
  
  
  printTestStats();

  return 0;
}
