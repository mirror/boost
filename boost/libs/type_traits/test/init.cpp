
#include "test.hpp"

boost::unit_test_framework::test_suite* get_master_unit(const char* name)
{
   static boost::unit_test_framework::test_suite* ptest_suite = 0;
   if(0 == ptest_suite)
      ptest_suite = BOOST_TEST_SUITE( name ? name : "" );
   return ptest_suite;
}

boost::unit_test_framework::test_suite* init_unit_test_suite ( int , char* [] )
{
   return get_master_unit();
}

