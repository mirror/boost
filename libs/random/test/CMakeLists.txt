#
# Copyright Troy D. Straszheim
#
# Distributed under the Boost Software License, Version 1.0.
# See http://www.boost.org/LICENSE_1_0.txt
#
boost_additional_test_dependencies(random BOOST_DEPENDS test)

foreach(test
    rand48
    minstd_rand0
    minstd_rand
    ecuyer1988
    kreutzer1986
    hellekalek1995
    mt11213b
    mt19937
    lagged_fibonacci
    lagged_fibonacci607
    ranlux3
    ranlux4
    ranlux3_01
    ranlux4_01
    ranlux64_3_01
    ranlux64_4_01
    taus88)
  boost_test_run(test_${test} 
    ../instantiate.cpp
    COMPILE_FLAGS -DBOOST_RANDOM_URNG_TEST=${test}
    )
endforeach()

boost_test_run(random_test ../random_test.cpp)
boost_test_run(random_demo ../random_demo.cpp)
