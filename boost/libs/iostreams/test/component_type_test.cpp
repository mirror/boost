// (C) Copyright Jonathan Turkanis 2004
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#include <stdexcept>
#include <typeinfo>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test.hpp>
#include "detail/constants.hpp"
#include "detail/filters.hpp"
#include "detail/temp_file.hpp"
#include "detail/verification.hpp"
using boost::unit_test::test_suite;

#define COMPARE_TYPE_ID(x, y) BOOST_IOSTREAMS_COMPARE_TYPE_ID(x, y)

void component_type_test()
{
    using namespace std;
    using namespace boost::iostreams;
    using namespace boost::iostreams::test;

    temp_file       dest;
    lowercase_file  lower;

    filtering_ostream out;
    out.push(tolower_filter());
    out.push(tolower_multichar_filter());
    out.push(file_sink(dest.name(), out_mode));

    // Check component types.

    BOOST_CHECK(COMPARE_TYPE_ID(
        BOOST_IOSTREAMS_COMPONENT_TYPE(out, 0), 
        typeid(tolower_filter)
    ));
    BOOST_CHECK(COMPARE_TYPE_ID(
        BOOST_IOSTREAMS_COMPONENT_TYPE(out, 1), 
        typeid(tolower_multichar_filter)
    ));
    BOOST_CHECK(COMPARE_TYPE_ID(
        BOOST_IOSTREAMS_COMPONENT_TYPE(out, 2), 
        typeid(file_sink)
    ));
    BOOST_CHECK_THROW(
        BOOST_IOSTREAMS_COMPONENT_TYPE(out, 3),
        std::out_of_range
    );

    // Check components.

    filtering_ostream out2;
    out2.push(*(BOOST_IOSTREAMS_COMPONENT(out, 0, tolower_filter)));
    out2.push(*(BOOST_IOSTREAMS_COMPONENT(out, 1, tolower_multichar_filter)));
    out2.push(*(BOOST_IOSTREAMS_COMPONENT(out, 2, file_sink)));
    write_data_in_chunks(out);
    out.reset();
    BOOST_CHECK_MESSAGE(
        compare_files(dest.name(), lower.name()),
        "failed accessing components of chain"
    );
}

test_suite* init_unit_test_suite(int, char* []) 
{
    test_suite* test = BOOST_TEST_SUITE("component_type test");
    test->add(BOOST_TEST_CASE(&component_type_test));
    return test;
}
