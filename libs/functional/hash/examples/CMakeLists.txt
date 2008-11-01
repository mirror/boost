#-------------------------------------------------------------------------
#-- Needed include directories for the tests
boost_test_add_dependent_includes("utility;detail;config")
#-------------------------------------------------------------------------
boost_test_run(books)
boost_test_run(point)
boost_test_run(portable)


