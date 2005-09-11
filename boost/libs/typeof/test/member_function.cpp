#include "test.hpp"

BOOST_STATIC_ASSERT(boost::type_of::test<double(*)()>::value);
BOOST_STATIC_ASSERT(boost::type_of::test<double(*)(int, double, short, char*, bool, char, float, long, unsigned short)>::value);
BOOST_STATIC_ASSERT(boost::type_of::test<void(*)()>::value);
BOOST_STATIC_ASSERT(boost::type_of::test<void(*)(int, double, short, char*, bool, char, float, long, unsigned short)>::value);
