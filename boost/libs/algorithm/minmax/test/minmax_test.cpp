#include <utility>
#include <functional>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <vector>
#include <list>
#include <set>
#include <iostream>

#include <boost/algorithm/minmax.hpp>
#include <boost/test/included/test_exec_monitor.hpp>

class custom {
  int _M_x;
  friend bool operator<(custom const& x, custom const& y);
  friend std::ostream& operator<<(std::ostream& str, custom const& x);
public:
  explicit custom(int x = 0) : _M_x(x) {}
  custom(custom const& y) : _M_x(y._M_x) {}
  custom operator+(custom const& y) const { return custom(_M_x+y._M_x); }
  custom& operator+=(custom const& y) { _M_x += y._M_x; return *this; }
};

bool operator< (custom const& x, custom const& y)
{
  return x._M_x < y._M_x;
}

template <class Value>
struct less_count : std::less<Value> {
  typedef std::less<Value> Base;
  less_count(less_count<Value> const& lc) : _M_counter(lc._M_counter) {}
  less_count(int& counter) : _M_counter(counter) {}
  bool operator()(Value const& a, Value const& b) const {
    ++_M_counter;
    return Base::operator()(a,b);
  }
  void reset() {
    _M_counter = 0;
  }
private:
  int& _M_counter;
};

template <class Value>
void test(int n, char* name)
{
  using namespace boost;

  // Test functionality
  tuple<Value const&, Value const&> result = minmax(0, 1);
  BOOST_CHECK_EQUAL( result.get<0>(), 0 );
  BOOST_CHECK_EQUAL( result.get<1>(), 1 );

  result = minmax(1, 0);
  BOOST_CHECK_EQUAL( result.get<0>(), 0 );
  BOOST_CHECK_EQUAL( result.get<1>(), 1 );
  
  // Test functionality and number of comparisons
  int counter = 0;
  BOOST_CHECK_EQUAL( result.get<0>(), 0 );
  BOOST_CHECK_EQUAL( result.get<1>(), 1 );
  BOOST_CHECK_EQUAL( counter, 1 );

  result = minmax(1, 0, less_count<Value>(counter) );
  BOOST_CHECK_EQUAL( result.get<0>(), 0 );
  BOOST_CHECK_EQUAL( result.get<1>(), 1 );
  BOOST_CHECK_EQUAL( counter, 2);
}

int test_main( int argc, char* argv[] )
{
  test<int>(n, "builtin");
  test<custom>(n, "custom ");

  return 0;
}
