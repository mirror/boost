#include "test.hpp"
#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

struct x;
BOOST_TYPEOF_REGISTER_TYPE(x)

BOOST_STATIC_ASSERT(boost::type_of::test<double x::*>::value);
