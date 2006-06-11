#include <boost/typeof/typeof.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/static_assert.hpp>

int foo(double);
typedef int(&FREF)(double);
FREF fref = *foo;

BOOST_STATIC_ASSERT((boost::is_same<BOOST_TYPEOF(fref), int(double)>::value));
