#include "test.hpp"
#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

template<unsigned long int n> struct t{};

BOOST_TYPEOF_REGISTER_TEMPLATE(t,
                               (BOOST_TYPEOF_INTEGRAL(unsigned long int))
                               )

BOOST_STATIC_ASSERT((boost::type_of::test<t<5>()>::value));
