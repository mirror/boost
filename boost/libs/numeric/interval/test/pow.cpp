#include <boost/numeric/interval.hpp>
#include <boost/test/test_tools.hpp>

bool test_pow(double al, double au, double bl, double bu, int p) {
  typedef boost::numeric::interval<double> I;
  I b = pow(I(al, au), p);
  return b.lower() == bl && b.upper() == bu;
}

int test_main(int, char *[]) {
  BOOST_TEST(test_pow(2, 3, 8, 27, 3));
  BOOST_TEST(test_pow(2, 3, 16, 81, 4));
  BOOST_TEST(test_pow(-3, 2, -27, 8, 3));
  BOOST_TEST(test_pow(-3, 2, 0, 81, 4));
  BOOST_TEST(test_pow(-3, -2, -27, -8, 3));
  BOOST_TEST(test_pow(-3, -2, 16, 81, 4));

  BOOST_TEST(test_pow(2, 4, 1./64, 1./8, -3));
  BOOST_TEST(test_pow(2, 4, 1./256, 1./16, -4));
  BOOST_TEST(test_pow(-4, -2, -1./8, -1./64, -3));
  BOOST_TEST(test_pow(-4, -2, 1./256, 1./16, -4));

  BOOST_TEST(test_pow(2, 3, 1, 1, 0));
  BOOST_TEST(test_pow(-3, 2, 1, 1, 0));
  BOOST_TEST(test_pow(-3, -2, 1, 1, 0));

  return 0;
}
