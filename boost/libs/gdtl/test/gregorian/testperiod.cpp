#include "boost/gdtl/gregorian/gregorian.hpp"
#include "boost/gdtl/testfrmwk.hpp"
#include <iostream>

int main() 
{
  using namespace boost::gregorian;
  date d1(2000,Jan,1),d2(2000,Jan,4);
  date d3 = d2;
  check("assignment", d3 == d2);
  date_duration fourDays(4);
  date_period p1(d1,d2);
  date_period p2(d1,date_duration(3));
  check("construction and ==", p1 == p2);
  check("begin", p1.begin() == d1);
  check("last",  p1.last()  == d2-date_duration(1) );
  check("end",   p1.end()   == d2);
  check("contains begin", p1.contains(d1));
  check("contains last", !p1.contains(d2));
  date_period p3(date(2000,Jan,4),date(2000,Feb,1));
  check("operator== not equal case", !(p1 == p3));
  check("less than order", p1 < p3);
  check("greater than order", p3 > p1);
  check("not equal", p3 != p1);
  check("intersects with myself", p1.intersects(p1));
  check("not intersects", !(p1.intersects(p3)));
  check("not intersects", !(p3.intersects(p1)));
  date_period p4(date(1999,Dec,1), d2);
  check("intersects", p1.intersects(p4));
  check("intersects", p4.intersects(p1));
  date_period p5(date(1999,Dec,1), date(2000,Dec,31));
  check("intersects", p1.intersects(p5));
  check("intersects", p5.intersects(p1));
  date_period p6(date(2000,Jan,1),date(2000,Dec,31));
  check("contains period", p5.contains(p6));
  check("contains period equal", p6.contains(p6));
  check("not contains period", !p6.contains(p5));
  
  //shift test
  p1.shift(fourDays); //from 2000-Jan-01--2000-Jan-04
  date_period shifted(date(2000,Jan,5),date(2000,Jan,8));
  //   std::cout << to_string(p1.begin()) <<"--" 
  // 	    << to_string(p1.last()) << std::endl;
  check("shift", p1 == shifted);
  

  //intersection tests
  date_period i1(date(2000,Jan,5), date(2000,Jan,10));
  date_period i2(date(2000,Jan,1), date(2000,Jan,7));
  date_period r1(date(2000,Jan,5), date(2000,Jan,7));
  //case 1    [5 -10) intersect [1-7) ->  [5-7)
  std::cout << to_simple_string(i1.intersection(i2)) << std::endl;
  check("intersect case1", i1.intersection(i2) == r1);
  check("intersect case1", i2.intersection(i1) == r1);
  //case 2    [5 -10) intersect [1-15) -> [5-10)
  date_period i3(date(2000,Jan,1), date(2000,Jan,15));
  check("intersect case2", i1.intersection(i3) == i1);
  check("intersect case2", i3.intersection(i1) == i1);
  //case 3    [5-10) intersect [7-15)  -> [7-10)
  date_period i4(date(2000,Jan,7), date(2000,Jan,10));
  date_period r2(date(2000,Jan,7), date(2000,Jan,10));
  check("intersect case3", i1.intersection(i4) == r2);
  check("intersect case3", i4.intersection(i1) == r2);
  //case 4    [5-10) interset [6-9)  -> [6-9)
  date_period i5(date(2000,Jan,6), date(2000,Jan,9));
  check("intersect case4", i1.intersection(i5) == i5);
  check("intersect case4", i5.intersection(i1) == i5);
  //case 5 no intersection [1-7) intersect [7-10)
  check("no intersection", i2.intersection(i4).is_null());

  //case 1    [5 -10) merge [1-7) ->  [1-10)
  date_period r3(date(2000,Jan,1), date(2000,Jan,10));
  //  std::cout << to_iso_string(i1.merge(i2).begin()) << "/" << to_iso_string(i1.merge(i2).last()) << std::endl;
  check("[5 -10) merge [1-7)  -> [1-10)", i1.merge(i2) == r3);
  check("[1 -7)  merge [7-10) ->  null",  i2.merge(i4).is_null());
  date_period r4(date(2000,Jan,5), date(2000,Jan,10));
  check("[5 -10) merge [6-9)  -> [5-10)", i1.merge(i5) == r4);
  
  
  printTestStats();

  return 0;
}
