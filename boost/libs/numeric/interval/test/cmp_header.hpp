#include <boost/numeric/interval/interval.hpp>
#include <boost/numeric/interval/checking.hpp>
#include <boost/numeric/interval/compare.hpp>
#include <boost/numeric/interval/policies.hpp>
#include <boost/test/test_tools.hpp>

struct empty_class {};

typedef boost::numeric::interval_lib::policies
          <empty_class, boost::numeric::interval_lib::checking_base<int> >
  my_policies;

typedef boost::numeric::interval<int, my_policies> I;

#define BOOST_C_EXN(e) \
  BOOST_CHECK_THROW(e, boost::numeric::interval_lib::comparison_error)
