#include "test.hpp"
#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

enum E{ONE, TWO, THREE};
template<E e> struct t{};

BOOST_TYPEOF_REGISTER_TEMPLATE(t, 
                               (BOOST_TYPEOF_INTEGRAL(E))
                               )

BOOST_STATIC_ASSERT(boost::type_of::test<t<TWO>()>::value);
