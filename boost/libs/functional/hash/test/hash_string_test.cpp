//  (C) Copyright Daniel James 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/functional/hash/hash.hpp>

#define BOOST_AUTO_TEST_MAIN
#include <boost/test/auto_unit_test.hpp>

#include <boost/limits.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>

#include "./compile_time.hpp"

BOOST_AUTO_UNIT_TEST(string_tests)
{
    BOOST_CHECK(compile_time_tests<std::string>::success);

    boost::hash<std::string> x1;
    boost::hash<std::string> x2;

    BOOST_CHECK(x1("Hello") == x2(std::string("Hel") + "lo"));
    BOOST_CHECK(x1("") == x2(std::string()));
}

#if !defined(BOOST_NO_STD_WSTRING)
BOOST_AUTO_UNIT_TEST(wstring_tests)
{
    BOOST_CHECK(compile_time_tests<std::wstring>::success);

    boost::hash<std::wstring> x1;
    boost::hash<std::wstring> x2;

    BOOST_CHECK(x1(L"Hello") == x2(std::wstring(L"Hel") + L"lo"));
    BOOST_CHECK(x1(L"") == x2(std::wstring()));
}
#endif
