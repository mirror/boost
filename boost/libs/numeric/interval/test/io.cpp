#include <boost/numeric/interval.hpp>
#include <boost/numeric/interval/io.hpp>
#include <boost/test/test_tools.hpp>

#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace boost;
using namespace interval_lib;


namespace my_namespace {

template<class T>
bool test(int precision) {
  interval<T> pi_i( 3.1415926, 3.1415927 );
  // write pi_i to a string
  std::ostringstream oss;
  oss.precision(precision);
  oss << pi_i;
  std::string pi_string = oss.str();
#ifdef BOOST_NUMERIC_INTERVAL_IO_VERBOSE
  std::cerr << "FYI: printing [3.1415926,3.1415927] with precision "
            << precision << " as "
            << std::setprecision(precision) << pi_i << std::endl;
#endif
  // read pi_o from same string
  interval<T> pi_o;
  std::istringstream iss(pi_string);
  iss >> pi_o;
  // the result should be at least as imprecise 
#ifdef BOOST_NUMERIC_INTERVAL_IO_VERBOSE
  if (!subset(pi_i, pi_o))
    std::cerr << "Error: getting [3.1415926,3.1415927] with precision "
              << precision << " as " << std::setprecision(precision)
              << "[" << pi_o.lower() << std::setprecision(precision)
              << "," << pi_o.upper() << "]" << std::endl;
  else
    std::cerr << "Good: getting [3.1415926,3.1415927] with precision "
              << precision << " as " << std::setprecision(precision)
   	        << "[" << pi_o.lower() << std::setprecision(precision)
              << "," << pi_o.upper() << "]" << std::endl;
#endif
  return subset(pi_i, pi_o);
}

} // namespace my_namespace

int test_main(int, char *[]) {
  using my_namespace::test;
  BOOST_TEST(test<float>(0));
  BOOST_TEST(test<float>(1));
  BOOST_TEST(test<float>(2));
  BOOST_TEST(test<float>(3));
  BOOST_TEST(test<float>(4));
  BOOST_TEST(test<float>(5));
  BOOST_TEST(test<float>(6));
  BOOST_TEST(test<float>(7));
  BOOST_TEST(test<float>(8));
  BOOST_TEST(test<double>(0));
  BOOST_TEST(test<double>(1));
  BOOST_TEST(test<double>(2));
  BOOST_TEST(test<double>(3));
  BOOST_TEST(test<double>(4));
  BOOST_TEST(test<double>(5));
  BOOST_TEST(test<double>(6));
  BOOST_TEST(test<double>(7));
  BOOST_TEST(test<double>(8));
  BOOST_TEST(test<double>(9));
  BOOST_TEST(test<double>(10));
  BOOST_TEST(test<double>(11));
  BOOST_TEST(test<double>(12));
  BOOST_TEST(test<double>(13));
  BOOST_TEST(test<double>(14));
  BOOST_TEST(test<double>(15));
  BOOST_TEST(test<long double>(0));
  BOOST_TEST(test<long double>(1));
  BOOST_TEST(test<long double>(2));
  BOOST_TEST(test<long double>(3));
  BOOST_TEST(test<long double>(4));
  BOOST_TEST(test<long double>(5));
  BOOST_TEST(test<long double>(6));
  BOOST_TEST(test<long double>(7));
  BOOST_TEST(test<long double>(8));
  BOOST_TEST(test<long double>(9));
  BOOST_TEST(test<long double>(10));
  BOOST_TEST(test<long double>(11));
  BOOST_TEST(test<long double>(12));
  BOOST_TEST(test<long double>(13));
  BOOST_TEST(test<long double>(14));
  BOOST_TEST(test<long double>(15));
  return 0;
}
