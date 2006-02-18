#include "test.hpp"
#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

struct A;
BOOST_TYPEOF_REGISTER_TYPE(A)

BOOST_STATIC_ASSERT(boost::type_of::test<A>::value);
