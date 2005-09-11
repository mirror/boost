#include "test.hpp"

BOOST_STATIC_ASSERT(boost::type_of::test<void(&)()>::value);
BOOST_STATIC_ASSERT(boost::type_of::test<int(&)(int, short)>::value);
