boost_test_run(rational_example rational_example.cpp)
boost_test_run(rational_test 
  rational_test.cpp
  DEPENDS boost_unit_test_framework
  )
