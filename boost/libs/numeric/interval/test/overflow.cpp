#include <boost/numeric/interval.hpp>
#include <boost/test/minimal.hpp>

template<class I>
void test_one(typename I::base_type x, typename I::base_type f) {
  I y = x;
  typename I::base_type g = 1 / f;
  const int nb = 10000;
  for(int i = 0; i < nb; i++) y *= f;
  for(int i = 0; i < nb; i++) y *= g;
  BOOST_TEST(in(x, y));
}

template<class I>
void test() {
  test_one<I>(1., 25.);
  test_one<I>(1., 0.04);
  test_one<I>(-1., 25.);
  test_one<I>(-1., 0.04);
}

int test_main(int, char *[]) {
  test<boost::numeric::interval<float> >();
  test<boost::numeric::interval<double> >();
  test<boost::numeric::interval<long double> >();
  return 0;
}
