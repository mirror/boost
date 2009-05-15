# Boost.Flyweight tests Jamfile
#
# Copyright 2006-2008 Joaquín M López Muñoz.
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)
#
# See http://www.boost.org/libs/flyweight for library home page.

boost_add_library(intermod_holder_dll 
  intermod_holder_dll.cpp
  COMPILE_FLAGS "-DBOOST_FLYWEIGHT_TEST_INTERMOD_HOLDER_DLL_SOURCE=1"
  NO_SINGLE_THREADED
  NO_STATIC
  NO_INSTALL
  )

boost_test_run(test_assoc_cont_factory test_assoc_cont_factory.cpp test_assoc_cont_fact_main.cpp)
boost_test_run(test_basic test_basic.cpp              test_basic_main.cpp)
boost_test_run(test_custom_factory test_custom_factory.cpp     test_custom_factory_main.cpp)
boost_test_run(test_init test_init.cpp               test_init_main.cpp)

boost_test_run(test_intermod_holder test_intermod_holder.cpp    test_intermod_holder_main.cpp
  DEPENDS intermod_holder_dll)

boost_test_run(test_multictor test_multictor.cpp          test_multictor_main.cpp)
boost_test_run(test_no_locking test_no_locking.cpp         test_no_locking_main.cpp)
boost_test_run(test_no_tracking test_no_tracking.cpp        test_no_tracking_main.cpp)
boost_test_run(test_set_factory test_set_factory.cpp        test_set_factory_main.cpp)
