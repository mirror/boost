//  Unit test for boost::lexical_cast.
//
//  See http://www.boost.org for most recent version, including documentation.
//
//  Copyright Antony Polukhin, 2011.
//
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt).

#include <boost/config.hpp>

#if defined(__INTEL_COMPILER)
#pragma warning(disable: 193 383 488 981 1418 1419)
#elif defined(BOOST_MSVC)
#pragma warning(disable: 4097 4100 4121 4127 4146 4244 4245 4511 4512 4701 4800)
#endif

#include <boost/lexical_cast.hpp>

#include <boost/cstdint.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#if defined(BOOST_NO_STRINGSTREAM) || defined(BOOST_NO_STD_WSTRING)
#define BOOST_LCAST_NO_WCHAR_T
#endif

using namespace boost;

template <class T>
void test_inf_nan_templated()
{
    typedef T test_t;

    BOOST_CHECK(lexical_cast<test_t>("inf") > (std::numeric_limits<test_t >::max)() );
    BOOST_CHECK(lexical_cast<test_t>("INF") > (std::numeric_limits<test_t >::max)() );

    BOOST_CHECK(lexical_cast<test_t>("-inf") < -(std::numeric_limits<test_t >::max)() );
    BOOST_CHECK(lexical_cast<test_t>("-INF") < -(std::numeric_limits<test_t >::max)() );

    BOOST_CHECK(lexical_cast<test_t>("+inf") > (std::numeric_limits<test_t >::max)() );
    BOOST_CHECK(lexical_cast<test_t>("+INF") > (std::numeric_limits<test_t >::max)() );

    BOOST_CHECK(lexical_cast<test_t>("infinity") > (std::numeric_limits<test_t >::max)() );
    BOOST_CHECK(lexical_cast<test_t>("INFINITY") > (std::numeric_limits<test_t >::max)() );

    BOOST_CHECK(lexical_cast<test_t>("-infinity") < -(std::numeric_limits<test_t >::max)() );
    BOOST_CHECK(lexical_cast<test_t>("-INFINITY") < -(std::numeric_limits<test_t >::max)() );

    BOOST_CHECK(lexical_cast<test_t>("+infinity") > (std::numeric_limits<test_t >::max)() );
    BOOST_CHECK(lexical_cast<test_t>("+INFINITY") > (std::numeric_limits<test_t >::max)() );

    BOOST_CHECK( lexical_cast<test_t>("nan") != lexical_cast<test_t>("nan") );
    BOOST_CHECK( lexical_cast<test_t>("NAN") != lexical_cast<test_t>("NAN") );

    BOOST_CHECK( lexical_cast<test_t>("-nan") != lexical_cast<test_t>("-nan") );
    BOOST_CHECK( lexical_cast<test_t>("-NAN") != lexical_cast<test_t>("-NAN") );

    BOOST_CHECK( lexical_cast<test_t>("+nan") != lexical_cast<test_t>("+nan") );
    BOOST_CHECK( lexical_cast<test_t>("+NAN") != lexical_cast<test_t>("+NAN") );

    BOOST_CHECK( lexical_cast<test_t>("nan()") != lexical_cast<test_t>("nan()") );
    BOOST_CHECK( lexical_cast<test_t>("NAN(some string)") != lexical_cast<test_t>("NAN(some string)") );
    BOOST_CHECK_THROW( lexical_cast<test_t>("NAN(some string"), bad_lexical_cast );

    BOOST_CHECK(lexical_cast<std::string>( -std::numeric_limits<test_t >::infinity()) == "-inf" );
    BOOST_CHECK(lexical_cast<std::string>( std::numeric_limits<test_t >::infinity()) == "inf" );
    BOOST_CHECK(lexical_cast<std::string>( std::numeric_limits<test_t >::quiet_NaN()) == "nan" );

#ifndef  BOOST_LCAST_NO_WCHAR_T
    BOOST_CHECK(lexical_cast<test_t>(L"inf") > (std::numeric_limits<test_t >::max)() );
    BOOST_CHECK(lexical_cast<test_t>(L"INF") > (std::numeric_limits<test_t >::max)() );

    BOOST_CHECK( lexical_cast<test_t>(L"nan") != lexical_cast<test_t>(L"nan") );
    BOOST_CHECK( lexical_cast<test_t>(L"NAN") != lexical_cast<test_t>(L"NAN") );

    BOOST_CHECK(lexical_cast<std::wstring>( -std::numeric_limits<test_t >::infinity()) == L"-inf" );
    BOOST_CHECK(lexical_cast<std::wstring>( std::numeric_limits<test_t >::infinity()) == L"inf" );
    BOOST_CHECK(lexical_cast<std::wstring>( std::numeric_limits<test_t >::quiet_NaN()) == L"nan" );

#endif
}

void test_inf_nan_float()
{
    test_inf_nan_templated<float >();
}

void test_inf_nan_double()
{
    test_inf_nan_templated<double >();
}

void test_inf_nan_long_double()
{
    test_inf_nan_templated<long double >();
}

unit_test::test_suite *init_unit_test_suite(int, char *[])
{
    unit_test_framework::test_suite *suite =
        BOOST_TEST_SUITE("lexical_cast inf anf nan parsing unit test");
    suite->add(BOOST_TEST_CASE(&test_inf_nan_float));
    suite->add(BOOST_TEST_CASE(&test_inf_nan_double));
    suite->add(BOOST_TEST_CASE(&test_inf_nan_long_double));

    return suite;
}
