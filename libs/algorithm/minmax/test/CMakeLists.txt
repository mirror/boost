#-------------------------------------------------------------------------
#-- Needed include directories for the tests
boost_test_add_dependent_includes("utility;detail;config;test;mpl;bind;type_traits;static_assert;preprocessor;array;iterator;timer;tuple;range")
#-------------------------------------------------------------------------


boost_test_run(minmax_element_test)
boost_test_run(minmax_test)
