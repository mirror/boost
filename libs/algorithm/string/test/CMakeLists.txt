#-------------------------------------------------------------------------
#-- Needed include directories for the tests
boost_test_add_dependent_includes("utility;detail;config;test;mpl;bind;type_traits;static_assert;preprocessor;array;iterator;exception;range;timer")
#-------------------------------------------------------------------------


boost_test_run(trim_test)

boost_test_run(conv_test)
boost_test_run(predicate_test)
boost_test_run(find_test)
boost_test_run(split_test)
boost_test_run(join_test)
boost_test_run(replace_test)
boost_test_run(regex_test DEPENDS boost_regex SHARED)

