#include "test.hpp"

BOOST_STATIC_ASSERT(boost::type_of::test<void(&)()>::value);
BOOST_STATIC_ASSERT(boost::type_of::test<int(&)(int, short)>::value);

// check that function values/refs can be bound

int foo(double);
typedef int(&FREF)(double);
FREF fref = *foo;

BOOST_STATIC_ASSERT((boost::is_same<BOOST_TYPEOF(fref), int(double)>::value));
