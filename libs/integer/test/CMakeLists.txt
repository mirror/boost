boost_test_run(cstdint_test cstdint_test.cpp)
boost_test_run(integer_mask_test integer_mask_test.cpp)
boost_test_run(integer_test integer_test.cpp)
boost_test_run(integer_traits_test integer_traits_test.cpp
               DEPENDS boost_test_exec_monitor)
boost_test_run(issue_2134 issue_2134.cpp)
boost_test_run(static_log2_test static_log2_test.cpp)
boost_test_run(static_min_max_test static_min_max_test.cpp)
