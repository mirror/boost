#-------------------------------------------------------------------------
#-- Needed include directories for the tests
boost_test_add_dependent_includes("utility;detail;config;test;mpl;preprocessor;type_traits;timer;smart_ptr;iterator;exception;static_assert;io;bind;integer")
#-------------------------------------------------------------------------

boost_test_run(bounds_test)
boost_test_run(traits_test)
boost_test_run(converter_test)
boost_test_run(udt_support_test)
boost_test_run(numeric_conv_cast_test numeric_cast_test.cpp)
boost_test_run(udt_example_0)
