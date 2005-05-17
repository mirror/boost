// (C) Copyright Jonathan Turkanis 2004
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#include <string>
#include <boost/iostreams/compose.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/device/null.hpp>
#include <boost/iostreams/filter/newline.hpp>
#include <boost/iostreams/filter/test.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test.hpp>

namespace io = boost::iostreams;
using boost::unit_test::test_suite;

const std::string posix =
    "When I was one-and-twenty\n"
    "I heard a wise man say,\n"
    "'Give crowns and pounds and guineas\n"
    "But not your heart away;\n"
    "\n"
    "Give pearls away and rubies\n"
    "But keep your fancy free.'\n"
    "But I was one-and-twenty,\n"
    "No use to talk to me.\n"
    "\n"
    "When I was one-and-twenty\n"
    "I heard him say again,\n"
    "'The heart out of the bosom\n"
    "Was never given in vain;\n"
    "\n"
    "'Tis paid with sighs a plenty\n"
    "And sold for endless rue.'\n"
    "And I am two-and-twenty,\n"
    "And oh, 'tis true, 'tis true.\n";

const std::string windows =
    "When I was one-and-twenty\r\n"
    "I heard a wise man say,\r\n"
    "'Give crowns and pounds and guineas\r\n"
    "But not your heart away;\r\n"
    "\r\n"
    "Give pearls away and rubies\r\n"
    "But keep your fancy free.'\r\n"
    "But I was one-and-twenty,\r\n"
    "No use to talk to me.\r\n"
    "\r\n"
    "When I was one-and-twenty\r\n"
    "I heard him say again,\r\n"
    "'The heart out of the bosom\r\n"
    "Was never given in vain;\r\n"
    "\r\n"
    "'Tis paid with sighs a plenty\r\n"
    "And sold for endless rue.'\r\n"
    "And I am two-and-twenty,\r\n"
    "And oh, 'tis true, 'tis true.\r\n";

const std::string mac =
    "When I was one-and-twenty\r"
    "I heard a wise man say,\r"
    "'Give crowns and pounds and guineas\r"
    "But not your heart away;\r"
    "\r"
    "Give pearls away and rubies\r"
    "But keep your fancy free.'\r"
    "But I was one-and-twenty,\r"
    "No use to talk to me.\r"
    "\r"
    "When I was one-and-twenty\r"
    "I heard him say again,\r"
    "'The heart out of the bosom\r"
    "Was never given in vain;\r"
    "\r"
    "'Tis paid with sighs a plenty\r"
    "And sold for endless rue.'\r"
    "And I am two-and-twenty,\r"
    "And oh, 'tis true, 'tis true.\r";

const std::string no_final_newline =
    "When I was one-and-twenty\n"
    "I heard a wise man say,\n"
    "'Give crowns and pounds and guineas\n"
    "But not your heart away;\n"
    "\n"
    "Give pearls away and rubies\n"
    "But keep your fancy free.'\n"
    "But I was one-and-twenty,\n"
    "No use to talk to me.\n"
    "\n"
    "When I was one-and-twenty\n"
    "I heard him say again,\n"
    "'The heart out of the bosom\n"
    "Was never given in vain;\n"
    "\n"
    "'Tis paid with sighs a plenty\n"
    "And sold for endless rue.'\n"
    "And I am two-and-twenty,\n"
    "And oh, 'tis true, 'tis true.";

const std::string mixed =
    "When I was one-and-twenty\n"
    "I heard a wise man say,\r\n"
    "'Give crowns and pounds and guineas\r"
    "But not your heart away;\n"
    "\r\n"
    "Give pearls away and rubies\r"
    "But keep your fancy free.'\n"
    "But I was one-and-twenty,\r\n"
    "No use to talk to me.\r"
    "\r"
    "When I was one-and-twenty\r\n"
    "I heard him say again,\r"
    "'The heart out of the bosom\n"
    "Was never given in vain;\r\n"
    "\r"
    "'Tis paid with sighs a plenty\n"
    "And sold for endless rue.'\r\n"
    "And I am two-and-twenty,\r"
    "And oh, 'tis true, 'tis true.\n";

void read_newline_filter()
{
    using namespace io;

        // Test converting to posix format.

    BOOST_CHECK(test_input_filter(newline_filter(newline::posix), posix, posix));
    BOOST_CHECK(test_input_filter(newline_filter(newline::posix), windows, posix));
    BOOST_CHECK(test_input_filter(newline_filter(newline::posix), mac, posix));
    BOOST_CHECK(test_input_filter(newline_filter(newline::posix), mixed, posix));

        // Test converting to windows format.

    BOOST_CHECK(test_input_filter(newline_filter(newline::windows), posix, windows));
    BOOST_CHECK(test_input_filter(newline_filter(newline::windows), windows, windows));
    BOOST_CHECK(test_input_filter(newline_filter(newline::windows), mac, windows));
    BOOST_CHECK(test_input_filter(newline_filter(newline::windows), mixed, windows));

        // Test converting to mac format.

    BOOST_CHECK(test_input_filter(newline_filter(newline::mac), posix, mac));
    BOOST_CHECK(test_input_filter(newline_filter(newline::mac), windows, mac));
    BOOST_CHECK(test_input_filter(newline_filter(newline::mac), mac, mac));
    BOOST_CHECK(test_input_filter(newline_filter(newline::mac), mixed, mac));
}

void write_newline_filter()
{
    using namespace io;

        // Test converting to posix format.

    BOOST_CHECK(test_output_filter(newline_filter(newline::posix), posix, posix));
    BOOST_CHECK(test_output_filter(newline_filter(newline::posix), windows, posix));
    BOOST_CHECK(test_output_filter(newline_filter(newline::posix), mac, posix));
    BOOST_CHECK(test_output_filter(newline_filter(newline::posix), mixed, posix));

        // Test converting to windows format.

    BOOST_CHECK(test_output_filter(newline_filter(newline::windows), posix, windows));
    BOOST_CHECK(test_output_filter(newline_filter(newline::windows), windows, windows));
    BOOST_CHECK(test_output_filter(newline_filter(newline::windows), mac, windows));
    BOOST_CHECK(test_output_filter(newline_filter(newline::windows), mixed, windows));

        // Test converting to mac format.

    BOOST_CHECK(test_output_filter(newline_filter(newline::mac), posix, mac));
    BOOST_CHECK(test_output_filter(newline_filter(newline::mac), windows, mac));
    BOOST_CHECK(test_output_filter(newline_filter(newline::mac), mac, mac));
    BOOST_CHECK(test_output_filter(newline_filter(newline::mac), mixed, mac));
}

void test_input_against_flags(int flags, const std::string& input, bool read)
{
    if (read) {
        io::copy(
            io::compose(
                io::newline_checker(flags),
                io::array_source(input.c_str())
            ),
            io::null_sink()
        );
    } else {
        io::copy(
            io::array_source(input.c_str()),
            io::compose(io::newline_checker(flags), io::null_sink())
        );
    }
}

void read_newline_checker()
{
    io::filtering_istream in;
    io::newline_checker* checker = 0;

        // Verify properties of ::posix.

    in.push(io::newline_checker(io::newline::posix));
    in.push(io::array_source(::posix.c_str()));
    BOOST_CHECK_NO_THROW(io::copy(in, io::null_sink()));
    in.pop(); // pop source.
    checker = BOOST_IOSTREAMS_COMPONENT(in, 0, io::newline_checker);
    BOOST_CHECK(checker->is_posix());
    BOOST_CHECK(!checker->is_windows());
    BOOST_CHECK(!checker->is_mac());
    BOOST_CHECK(!checker->is_mixed());
    BOOST_CHECK(checker->has_final_newline());
    in.pop(); // pop checker.

        // Verify properties of ::windows.

    in.push(io::newline_checker(io::newline::windows));
    in.push(io::array_source(::windows.c_str()));
    try {
        io::copy(in, io::null_sink());
    } catch (io::newline_error&) {
        BOOST_CHECK_MESSAGE(
            false, "failed checking for windows line endings"
        );
    }
    in.pop(); // pop source.
    checker = BOOST_IOSTREAMS_COMPONENT(in, 0, io::newline_checker);
    BOOST_CHECK(!checker->is_posix());
    BOOST_CHECK(checker->is_windows());
    BOOST_CHECK(!checker->is_mac());
    BOOST_CHECK(!checker->is_mixed());
    BOOST_CHECK(checker->has_final_newline());
    in.pop(); // pop checker.

        // Verify properties of ::mac.

    in.push(io::newline_checker(io::newline::mac));
    in.push(io::array_source(::mac.c_str()));
    BOOST_CHECK_NO_THROW(io::copy(in, io::null_sink()));
    in.pop(); // pop source.
    checker = BOOST_IOSTREAMS_COMPONENT(in, 0, io::newline_checker);
    BOOST_CHECK(!checker->is_posix());
    BOOST_CHECK(!checker->is_windows());
    BOOST_CHECK(checker->is_mac());
    BOOST_CHECK(!checker->is_mixed());
    BOOST_CHECK(checker->has_final_newline());
    in.pop(); // pop checker.

        // Verify properties of no_final_newline.

    in.push(io::newline_checker(io::newline::posix));
    in.push(io::array_source(::no_final_newline.c_str()));
    BOOST_CHECK_NO_THROW(io::copy(in, io::null_sink()));
    in.pop(); // pop source.
    checker = BOOST_IOSTREAMS_COMPONENT(in, 0, io::newline_checker);
    BOOST_CHECK(checker->is_posix());
    BOOST_CHECK(!checker->is_windows());
    BOOST_CHECK(!checker->is_mac());
    BOOST_CHECK(!checker->is_mixed());
    BOOST_CHECK(!checker->has_final_newline());
    in.pop(); // pop checker.

        // Verify properties of mixed.

    in.push(io::newline_checker());
    in.push(io::array_source(::mixed.c_str()));
    BOOST_CHECK_NO_THROW(io::copy(in, io::null_sink()));
    in.pop(); // pop source.
    checker = BOOST_IOSTREAMS_COMPONENT(in, 0, io::newline_checker);
    BOOST_CHECK(!checker->is_posix());
    BOOST_CHECK(!checker->is_windows());
    BOOST_CHECK(!checker->is_mac());
    BOOST_CHECK(checker->is_mixed_posix());
    BOOST_CHECK(checker->is_mixed_windows());
    BOOST_CHECK(checker->is_mixed_mac());
    BOOST_CHECK(checker->is_mixed());
    BOOST_CHECK(checker->has_final_newline());
    in.pop(); // pop checker.

        // Verify exceptions when input does not satisfy target conditions.

    BOOST_CHECK_THROW(
        test_input_against_flags(io::newline::windows, ::posix, true),
        io::newline_error
    )
    BOOST_CHECK_THROW(
        test_input_against_flags(io::newline::mac, ::posix, true),
        io::newline_error
    )
    BOOST_CHECK_THROW(
        test_input_against_flags(io::newline::posix, ::windows, true),
        io::newline_error
    )
    BOOST_CHECK_THROW(
        test_input_against_flags(io::newline::mac, ::windows, true),
        io::newline_error
    )
    BOOST_CHECK_THROW(
        test_input_against_flags(io::newline::posix, ::mac, true),
        io::newline_error
    )
    BOOST_CHECK_THROW(
        test_input_against_flags(io::newline::windows, ::mac, true),
        io::newline_error
    )
    BOOST_CHECK_THROW(
        test_input_against_flags(io::newline::final_newline, ::no_final_newline, true),
        io::newline_error
    )
    BOOST_CHECK_THROW(
        test_input_against_flags(io::newline::posix, ::mixed, true),
        io::newline_error
    )
    BOOST_CHECK_THROW(
        test_input_against_flags(io::newline::windows, ::mixed, true),
        io::newline_error
    )
    BOOST_CHECK_THROW(
        test_input_against_flags(io::newline::mac, ::mixed, true),
        io::newline_error
    )
}

void write_newline_checker()
{
    io::filtering_ostream out;
    io::newline_checker* checker = 0;

        // Verify properties of ::posix.

    out.push(io::newline_checker(io::newline::posix));
    out.push(io::null_sink());
    BOOST_CHECK_NO_THROW(io::copy(io::array_source(::posix.c_str()), out))
    out.pop(); // pop source.
    checker = BOOST_IOSTREAMS_COMPONENT(out, 0, io::newline_checker);
    BOOST_CHECK(checker->is_posix());
    BOOST_CHECK(!checker->is_windows());
    BOOST_CHECK(!checker->is_mac());
    BOOST_CHECK(!checker->is_mixed());
    BOOST_CHECK(checker->has_final_newline());
    out.pop(); // pop checker.

        // Verify properties of ::windows.

    out.push(io::newline_checker(io::newline::windows));
    out.push(io::null_sink());
    BOOST_CHECK_NO_THROW(io::copy(io::array_source(::windows.c_str()), out))
    out.pop(); // pop source.
    checker = BOOST_IOSTREAMS_COMPONENT(out, 0, io::newline_checker);
    BOOST_CHECK(!checker->is_posix());
    BOOST_CHECK(checker->is_windows());
    BOOST_CHECK(!checker->is_mac());
    BOOST_CHECK(!checker->is_mixed());
    BOOST_CHECK(checker->has_final_newline());
    out.pop(); // pop checker.

        // Verify properties of ::mac.

    out.push(io::newline_checker(io::newline::mac));
    out.push(io::null_sink());
    BOOST_CHECK_NO_THROW(io::copy(io::array_source(::mac.c_str()), out))
    out.pop(); // pop source.
    checker = BOOST_IOSTREAMS_COMPONENT(out, 0, io::newline_checker);
    BOOST_CHECK(!checker->is_posix());
    BOOST_CHECK(!checker->is_windows());
    BOOST_CHECK(checker->is_mac());
    BOOST_CHECK(!checker->is_mixed());
    BOOST_CHECK(checker->has_final_newline());
    out.pop(); // pop checker.

        // Verify properties of no_final_newline.

    out.push(io::newline_checker(io::newline::posix));
    out.push(io::null_sink());
    BOOST_CHECK_NO_THROW(io::copy(io::array_source(::no_final_newline.c_str()), out))
    out.pop(); // pop source.
    checker = BOOST_IOSTREAMS_COMPONENT(out, 0, io::newline_checker);
    BOOST_CHECK(checker->is_posix());
    BOOST_CHECK(!checker->is_windows());
    BOOST_CHECK(!checker->is_mac());
    BOOST_CHECK(!checker->is_mixed());
    BOOST_CHECK(!checker->has_final_newline());
    out.pop(); // pop checker.

        // Verify properties of mixed.

    out.push(io::newline_checker());
    out.push(io::null_sink());
    BOOST_CHECK_NO_THROW(io::copy(io::array_source(::mixed.c_str()), out))
    out.pop(); // pop source.
    checker = BOOST_IOSTREAMS_COMPONENT(out, 0, io::newline_checker);
    BOOST_CHECK(!checker->is_posix());
    BOOST_CHECK(!checker->is_windows());
    BOOST_CHECK(!checker->is_mac());
    BOOST_CHECK(checker->is_mixed_posix());
    BOOST_CHECK(checker->is_mixed_windows());
    BOOST_CHECK(checker->is_mixed_mac());
    BOOST_CHECK(checker->is_mixed());
    BOOST_CHECK(checker->has_final_newline());
    out.pop(); // pop checker.

        // Verify exceptions when input does not satisfy target conditions.

    BOOST_CHECK_THROW(
        test_input_against_flags(io::newline::windows, ::posix, false),
        io::newline_error
    )
    BOOST_CHECK_THROW(
        test_input_against_flags(io::newline::mac, ::posix, false),
        io::newline_error
    )
    BOOST_CHECK_THROW(
        test_input_against_flags(io::newline::posix, ::windows, false),
        io::newline_error
    )
    BOOST_CHECK_THROW(
        test_input_against_flags(io::newline::mac, ::windows, false),
        io::newline_error
    )
    BOOST_CHECK_THROW(
        test_input_against_flags(io::newline::posix, ::mac, false),
        io::newline_error
    )
    BOOST_CHECK_THROW(
        test_input_against_flags(io::newline::windows, ::mac, false),
        io::newline_error
    )
    BOOST_CHECK_THROW(
        test_input_against_flags(io::newline::final_newline, ::no_final_newline, false),
        io::newline_error
    )
    BOOST_CHECK_THROW(
        test_input_against_flags(io::newline::posix, ::mixed, false),
        io::newline_error
    )
    BOOST_CHECK_THROW(
        test_input_against_flags(io::newline::windows, ::mixed, false),
        io::newline_error
    )
    BOOST_CHECK_THROW(
        test_input_against_flags(io::newline::mac, ::mixed, false),
        io::newline_error
    )
}

test_suite* init_unit_test_suite(int, char* [])
{
    test_suite* test = BOOST_TEST_SUITE("newline_filter test");
    test->add(BOOST_TEST_CASE(&read_newline_filter));
    test->add(BOOST_TEST_CASE(&write_newline_filter));
    test->add(BOOST_TEST_CASE(&read_newline_checker));
    test->add(BOOST_TEST_CASE(&write_newline_checker));
    return test;
}
