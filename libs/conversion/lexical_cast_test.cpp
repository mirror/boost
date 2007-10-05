//  Unit test for boost::lexical_cast.
//
//  See http://www.boost.org for most recent version, including documentation.
//
//  Copyright Terje Slettebø and Kevlin Henney, 2005.
//
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt).
//
// Note: The unit test no longer compile on MSVC 6, but lexical_cast itself works for it.

#include <boost/config.hpp>

#if defined(__INTEL_COMPILER)
#pragma warning(disable: 193 383 488 981 1418 1419)
#elif defined(BOOST_MSVC)
#pragma warning(disable: 4097 4100 4121 4127 4146 4244 4245 4511 4512 4701 4800)
#endif

#include <boost/lexical_cast.hpp>

#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#if defined(BOOST_NO_STRINGSTREAM) || \
    defined(BOOST_NO_STD_WSTRING) || \
    defined(BOOST_NO_STD_LOCALE)
#define DISABLE_WIDE_CHAR_SUPPORT
#endif

using namespace boost;

void test_conversion_to_char();
void test_conversion_to_int();
void test_conversion_to_double();
void test_conversion_to_bool();
void test_conversion_to_string();
void test_conversion_from_to_wchar_t_alias();
void test_conversion_to_pointer();
void test_conversion_from_wchar_t();
void test_conversion_to_wchar_t();
void test_conversion_from_wstring();
void test_conversion_to_wstring();
void test_bad_lexical_cast();
void test_no_whitespace_stripping();

unit_test::test_suite *init_unit_test_suite(int, char *[])
{
    unit_test_framework::test_suite *suite =
        BOOST_TEST_SUITE("lexical_cast unit test");
    suite->add(BOOST_TEST_CASE(test_conversion_to_char));
    suite->add(BOOST_TEST_CASE(test_conversion_to_int));
    suite->add(BOOST_TEST_CASE(test_conversion_to_double));
    suite->add(BOOST_TEST_CASE(test_conversion_to_bool));
    suite->add(BOOST_TEST_CASE(test_conversion_from_to_wchar_t_alias));
    suite->add(BOOST_TEST_CASE(test_conversion_to_pointer));
    suite->add(BOOST_TEST_CASE(test_conversion_to_string));
    #ifndef DISABLE_WIDE_CHAR_SUPPORT
    suite->add(BOOST_TEST_CASE(test_conversion_from_wchar_t));
    suite->add(BOOST_TEST_CASE(test_conversion_to_wchar_t));
    suite->add(BOOST_TEST_CASE(test_conversion_from_wstring));
    suite->add(BOOST_TEST_CASE(test_conversion_to_wstring));
    #endif
    suite->add(BOOST_TEST_CASE(test_bad_lexical_cast));
    suite->add(BOOST_TEST_CASE(test_no_whitespace_stripping));
    return suite;
}

void test_conversion_to_char()
{
    BOOST_CHECK_EQUAL('A', lexical_cast<char>('A'));
    BOOST_CHECK_EQUAL(' ', lexical_cast<char>(' '));
    BOOST_CHECK_EQUAL('1', lexical_cast<char>(1));
    BOOST_CHECK_EQUAL('0', lexical_cast<char>(0));
    BOOST_CHECK_THROW(lexical_cast<char>(123), bad_lexical_cast);
    BOOST_CHECK_EQUAL('1', lexical_cast<char>(1.0));
    BOOST_CHECK_EQUAL('1', lexical_cast<char>(true));
    BOOST_CHECK_EQUAL('0', lexical_cast<char>(false));
    BOOST_CHECK_EQUAL('A', lexical_cast<char>("A"));
    BOOST_CHECK_EQUAL(' ', lexical_cast<char>(" "));
    BOOST_CHECK_THROW(lexical_cast<char>(""), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<char>("Test"), bad_lexical_cast);
    BOOST_CHECK_EQUAL('A', lexical_cast<char>(std::string("A")));
    BOOST_CHECK_EQUAL(' ', lexical_cast<char>(std::string(" ")));
    BOOST_CHECK_THROW(
        lexical_cast<char>(std::string("")), bad_lexical_cast);
    BOOST_CHECK_THROW(
        lexical_cast<char>(std::string("Test")), bad_lexical_cast);
}

void test_conversion_to_int()
{
    BOOST_CHECK_EQUAL(1, lexical_cast<int>('1'));
    BOOST_CHECK_EQUAL(0, lexical_cast<int>('0'));
    BOOST_CHECK_THROW(lexical_cast<int>('A'), bad_lexical_cast);
    BOOST_CHECK_EQUAL(1, lexical_cast<int>(1));
    BOOST_CHECK_EQUAL(
        (std::numeric_limits<int>::max)(),
        lexical_cast<int>((std::numeric_limits<int>::max)()));
    BOOST_CHECK_EQUAL(1, lexical_cast<int>(1.0));

    BOOST_CHECK_THROW(lexical_cast<int>(1.23), bad_lexical_cast);

    BOOST_CHECK_THROW(lexical_cast<int>(1e20), bad_lexical_cast);
    BOOST_CHECK_EQUAL(1, lexical_cast<int>(true));
    BOOST_CHECK_EQUAL(0, lexical_cast<int>(false));
    BOOST_CHECK_EQUAL(123, lexical_cast<int>("123"));
    BOOST_CHECK_THROW(
        lexical_cast<int>(" 123"), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<int>(""), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<int>("Test"), bad_lexical_cast);
    BOOST_CHECK_EQUAL(123, lexical_cast<int>("123"));
    BOOST_CHECK_EQUAL(123, lexical_cast<int>(std::string("123")));
    BOOST_CHECK_THROW(
        lexical_cast<int>(std::string(" 123")), bad_lexical_cast);
    BOOST_CHECK_THROW(
        lexical_cast<int>(std::string("")), bad_lexical_cast);
    BOOST_CHECK_THROW(
        lexical_cast<int>(std::string("Test")), bad_lexical_cast);
}

void test_conversion_to_double()
{
    BOOST_CHECK_CLOSE(1.0, lexical_cast<double>('1'), (std::numeric_limits<double>::epsilon()));
    BOOST_CHECK_THROW(lexical_cast<double>('A'), bad_lexical_cast);
    BOOST_CHECK_CLOSE(1.0, lexical_cast<double>(1), (std::numeric_limits<double>::epsilon()));
    BOOST_CHECK_CLOSE(1.23, lexical_cast<double>(1.23), (std::numeric_limits<double>::epsilon()));
    BOOST_CHECK_CLOSE(1.234567890, 1.234567890, std::numeric_limits<double>::epsilon());
    BOOST_CHECK_CLOSE(1.0, lexical_cast<double>(true), (std::numeric_limits<double>::epsilon()));
    BOOST_CHECK_CLOSE(0.0, lexical_cast<double>(false), (std::numeric_limits<double>::epsilon()));
    BOOST_CHECK_CLOSE(1.23, lexical_cast<double>("1.23"), (std::numeric_limits<double>::epsilon()));
    BOOST_CHECK_THROW(lexical_cast<double>(""), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<double>("Test"), bad_lexical_cast);
    BOOST_CHECK_CLOSE(1.23, lexical_cast<double>(std::string("1.23")), (std::numeric_limits<double>::epsilon()));
    BOOST_CHECK_THROW(
        lexical_cast<double>(std::string("")), bad_lexical_cast);
    BOOST_CHECK_THROW(
        lexical_cast<double>(std::string("Test")), bad_lexical_cast);
}

void test_conversion_to_bool()
{
    BOOST_CHECK_EQUAL(true, lexical_cast<bool>('1'));
    BOOST_CHECK_EQUAL(false, lexical_cast<bool>('0'));
    BOOST_CHECK_THROW(lexical_cast<bool>('A'), bad_lexical_cast);
    BOOST_CHECK_EQUAL(true, lexical_cast<bool>(1));
    BOOST_CHECK_EQUAL(false, lexical_cast<bool>(0));
    BOOST_CHECK_THROW(lexical_cast<bool>(123), bad_lexical_cast);
    BOOST_CHECK_EQUAL(true, lexical_cast<bool>(1.0));
    BOOST_CHECK_EQUAL(false, lexical_cast<bool>(0.0));
    BOOST_CHECK_EQUAL(true, lexical_cast<bool>(true));
    BOOST_CHECK_EQUAL(false, lexical_cast<bool>(false));
    BOOST_CHECK_EQUAL(true, lexical_cast<bool>("1"));
    BOOST_CHECK_EQUAL(false, lexical_cast<bool>("0"));
    BOOST_CHECK_THROW(lexical_cast<bool>(""), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<bool>("Test"), bad_lexical_cast);
    BOOST_CHECK_EQUAL(true, lexical_cast<bool>("1"));
    BOOST_CHECK_EQUAL(false, lexical_cast<bool>("0"));
    BOOST_CHECK_EQUAL(true, lexical_cast<bool>(std::string("1")));
    BOOST_CHECK_EQUAL(false, lexical_cast<bool>(std::string("0")));
    BOOST_CHECK_THROW(
        lexical_cast<bool>(std::string("")), bad_lexical_cast);
    BOOST_CHECK_THROW(
        lexical_cast<bool>(std::string("Test")), bad_lexical_cast);
}

void test_conversion_to_string()
{
    BOOST_CHECK_EQUAL("A", lexical_cast<std::string>('A'));
    BOOST_CHECK_EQUAL(" ", lexical_cast<std::string>(' '));
    BOOST_CHECK_EQUAL("123", lexical_cast<std::string>(123));
    BOOST_CHECK_EQUAL("1.23", lexical_cast<std::string>(1.23));
    BOOST_CHECK_EQUAL("1.111111111", lexical_cast<std::string>(1.111111111));
    BOOST_CHECK_EQUAL("1", lexical_cast<std::string>(true));
    BOOST_CHECK_EQUAL("0", lexical_cast<std::string>(false));
    BOOST_CHECK_EQUAL("Test", lexical_cast<std::string>("Test"));
    BOOST_CHECK_EQUAL(" ", lexical_cast<std::string>(" "));
    BOOST_CHECK_EQUAL("", lexical_cast<std::string>(""));
    BOOST_CHECK_EQUAL("Test", lexical_cast<std::string>(std::string("Test")));
    BOOST_CHECK_EQUAL(" ", lexical_cast<std::string>(std::string(" ")));
    BOOST_CHECK_EQUAL("", lexical_cast<std::string>(std::string("")));
}

void test_conversion_from_to_wchar_t_alias()
{
    BOOST_CHECK_EQUAL(123u, lexical_cast<unsigned short>("123"));
    BOOST_CHECK_EQUAL(123u, lexical_cast<unsigned int>("123"));
    BOOST_CHECK_EQUAL(123u, lexical_cast<unsigned long>("123"));
    BOOST_CHECK_EQUAL(std::string("123"),
        lexical_cast<std::string>(static_cast<unsigned short>(123)));
    BOOST_CHECK_EQUAL(std::string("123"), lexical_cast<std::string>(123u));
    BOOST_CHECK_EQUAL(std::string("123"), lexical_cast<std::string>(123ul));
}

void test_conversion_to_pointer()
{
    BOOST_CHECK_THROW(lexical_cast<char *>("Test"), bad_lexical_cast);
    #ifndef DISABLE_WIDE_CHAR_SUPPORT
    BOOST_CHECK_THROW(lexical_cast<wchar_t *>("Test"), bad_lexical_cast);
    #endif
}

void test_conversion_from_wchar_t()
{
#ifndef DISABLE_WIDE_CHAR_SUPPORT
#if !defined(BOOST_NO_INTRINSIC_WCHAR_T)
    BOOST_CHECK_EQUAL(1, lexical_cast<int>(L'1'));
    BOOST_CHECK_THROW(lexical_cast<int>(L'A'), bad_lexical_cast);
#endif

    BOOST_CHECK_EQUAL(123, lexical_cast<int>(L"123"));
    BOOST_CHECK_THROW(lexical_cast<int>(L""), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<int>(L"Test"), bad_lexical_cast);

#if !defined(BOOST_NO_INTRINSIC_WCHAR_T)
    BOOST_CHECK_EQUAL(1.0, lexical_cast<double>(L'1'));
    BOOST_CHECK_THROW(lexical_cast<double>(L'A'), bad_lexical_cast);
#endif

    BOOST_CHECK_EQUAL(1.23, lexical_cast<double>(L"1.23"));
    BOOST_CHECK_THROW(lexical_cast<double>(L""), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<double>(L"Test"), bad_lexical_cast);

#if !defined(BOOST_NO_INTRINSIC_WCHAR_T)
    BOOST_CHECK_EQUAL(true, lexical_cast<bool>(L'1'));
    BOOST_CHECK_EQUAL(false, lexical_cast<bool>(L'0'));
    BOOST_CHECK_THROW(lexical_cast<bool>(L'A'), bad_lexical_cast);
#endif
    BOOST_CHECK_EQUAL(true, lexical_cast<bool>(L"1"));
    BOOST_CHECK_EQUAL(false, lexical_cast<bool>(L"0"));
    BOOST_CHECK_THROW(lexical_cast<bool>(L""), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<bool>(L"Test"), bad_lexical_cast);
#endif
}

void test_conversion_to_wchar_t()
{
#if !defined(DISABLE_WIDE_CHAR_SUPPORT) && !defined(BOOST_NO_INTRINSIC_WCHAR_T)
    BOOST_CHECK_EQUAL(L'1', lexical_cast<wchar_t>(1));
    BOOST_CHECK_EQUAL(L'0', lexical_cast<wchar_t>(0));
    BOOST_CHECK_THROW(lexical_cast<wchar_t>(123), bad_lexical_cast);
    BOOST_CHECK_EQUAL(L'1', lexical_cast<wchar_t>(1.0));
    BOOST_CHECK_EQUAL(L'0', lexical_cast<wchar_t>(0.0));
    BOOST_CHECK_EQUAL(L'1', lexical_cast<wchar_t>(true));
    BOOST_CHECK_EQUAL(L'0', lexical_cast<wchar_t>(false));
    BOOST_CHECK_EQUAL(L'A', lexical_cast<wchar_t>(L'A'));
    BOOST_CHECK_EQUAL(L' ', lexical_cast<wchar_t>(L' '));
    BOOST_CHECK_EQUAL(L'A', lexical_cast<wchar_t>(L"A"));
    BOOST_CHECK_EQUAL(L' ', lexical_cast<wchar_t>(L" "));
    BOOST_CHECK_THROW(lexical_cast<wchar_t>(L""), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<wchar_t>(L"Test"), bad_lexical_cast);
    BOOST_CHECK_EQUAL(L'A', lexical_cast<wchar_t>(std::wstring(L"A")));
    BOOST_CHECK_EQUAL(L' ', lexical_cast<wchar_t>(std::wstring(L" ")));
    BOOST_CHECK_THROW(
        lexical_cast<wchar_t>(std::wstring(L"")), bad_lexical_cast);
    BOOST_CHECK_THROW(
        lexical_cast<wchar_t>(std::wstring(L"Test")), bad_lexical_cast);
    #endif
}

void test_conversion_from_wstring()
{
    #ifndef DISABLE_WIDE_CHAR_SUPPORT
    BOOST_CHECK_EQUAL(123, lexical_cast<int>(std::wstring(L"123")));
    BOOST_CHECK_THROW(
        lexical_cast<int>(std::wstring(L"")), bad_lexical_cast);
    BOOST_CHECK_THROW(
        lexical_cast<int>(std::wstring(L"Test")), bad_lexical_cast);

    BOOST_CHECK_EQUAL(true, lexical_cast<bool>(std::wstring(L"1")));
    BOOST_CHECK_EQUAL(false, lexical_cast<bool>(std::wstring(L"0")));
    BOOST_CHECK_THROW(
        lexical_cast<bool>(std::wstring(L"")), bad_lexical_cast);
    BOOST_CHECK_THROW(
        lexical_cast<bool>(std::wstring(L"Test")), bad_lexical_cast);
    #endif
}

void test_conversion_to_wstring()
{
    #ifndef DISABLE_WIDE_CHAR_SUPPORT
    BOOST_CHECK(L"123" == lexical_cast<std::wstring>(123));
    BOOST_CHECK(L"1.23" == lexical_cast<std::wstring>(1.23));
    BOOST_CHECK(L"1.111111111" == lexical_cast<std::wstring>(1.111111111));
    BOOST_CHECK(L"1" == lexical_cast<std::wstring>(true));
    BOOST_CHECK(L"0" == lexical_cast<std::wstring>(false));
#if !defined(BOOST_NO_INTRINSIC_WCHAR_T)
    BOOST_CHECK(L"A" == lexical_cast<std::wstring>(L'A'));
    BOOST_CHECK(L" " == lexical_cast<std::wstring>(L' '));
#endif
    BOOST_CHECK(L"Test" == lexical_cast<std::wstring>(L"Test"));
    BOOST_CHECK(L" " == lexical_cast<std::wstring>(L" "));
    BOOST_CHECK(L"" == lexical_cast<std::wstring>(L""));
    BOOST_CHECK(L"Test" == lexical_cast<std::wstring>(std::wstring(L"Test")));
    BOOST_CHECK(L" " == lexical_cast<std::wstring>(std::wstring(L" ")));
    BOOST_CHECK(L"" == lexical_cast<std::wstring>(std::wstring(L"")));
    #endif
}

void test_bad_lexical_cast()
{
    try
    {
        lexical_cast<int>(std::string("Test"));

        BOOST_CHECK(false); // Exception expected
    }
    catch(const bad_lexical_cast &e)
    {
        BOOST_CHECK(e.source_type() == typeid(std::string));
        BOOST_CHECK(e.target_type() == typeid(int));
    }
}

void test_no_whitespace_stripping()
{
    BOOST_CHECK_THROW(lexical_cast<int>(" 123"), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<int>("123 "), bad_lexical_cast);
}
