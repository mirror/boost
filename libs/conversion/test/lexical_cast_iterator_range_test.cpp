//  Unit test for boost::lexical_cast.
//
//  See http://www.boost.org for most recent version, including documentation.
//
//  Copyright Antony Polukhin, 2012.
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

#include <boost/test/unit_test.hpp>
#include <boost/range/iterator_range.hpp>

using namespace boost;

#if defined(BOOST_NO_STRINGSTREAM) || defined(BOOST_NO_STD_WSTRING)
#define BOOST_LCAST_NO_WCHAR_T
#endif

struct class_with_user_defined_sream_operators {
    int i;

    operator int() const {
        return i;
    }
};

template <class CharT>
inline std::basic_istream<CharT>& operator >> (std::basic_istream<CharT>& istr, class_with_user_defined_sream_operators& rhs)
{
    return istr >> rhs.i;
}


template <class RngT>
void do_test_iterator_range(const RngT& rng)
{
    BOOST_CHECK_EQUAL(lexical_cast<int>(rng), 1);
    BOOST_CHECK_EQUAL(lexical_cast<unsigned int>(rng), 1u);
    BOOST_CHECK_EQUAL(lexical_cast<short>(rng), 1);
    BOOST_CHECK_EQUAL(lexical_cast<unsigned short>(rng), 1u);
    BOOST_CHECK_EQUAL(lexical_cast<long int>(rng), 1);
    BOOST_CHECK_EQUAL(lexical_cast<unsigned long int>(rng), 1u);
    BOOST_CHECK_EQUAL(lexical_cast<float>(rng), 1.0f);
    BOOST_CHECK_EQUAL(lexical_cast<double>(rng), 1.0);
    BOOST_CHECK_EQUAL(lexical_cast<long double>(rng), 1.0L);
    BOOST_CHECK_EQUAL(lexical_cast<class_with_user_defined_sream_operators>(rng), 1);

#if defined(BOOST_HAS_LONG_LONG)
    BOOST_CHECK_EQUAL(lexical_cast<boost::ulong_long_type>(rng), 1u);
    BOOST_CHECK_EQUAL(lexical_cast<boost::long_long_type>(rng), 1);
#elif defined(BOOST_HAS_MS_INT64)
    BOOST_CHECK_EQUAL(lexical_cast<unsigned __int64>(rng), 1u);
    BOOST_CHECK_EQUAL(lexical_cast<__int64>(rng), 1);
#endif

#ifndef BOOST_LCAST_NO_WCHAR_T
    BOOST_CHECK(lexical_cast<std::wstring>(rng) == L"1");
#endif
}

void test_char_iterator_ranges() 
{
    typedef char test_char_type;

    // Zero terminated
    test_char_type data1[] = "1";
    iterator_range<test_char_type*> rng1(data1, data1 + 1);
    do_test_iterator_range(rng1);
    BOOST_CHECK_EQUAL(lexical_cast<std::string>(rng1), "1");

    const test_char_type cdata1[] = "1";
    iterator_range<const test_char_type*> crng1(cdata1, cdata1 + 1);
    do_test_iterator_range(crng1);
    BOOST_CHECK_EQUAL(lexical_cast<std::string>(crng1), "1");

    // Non zero terminated
    test_char_type data2[] = "11";
    iterator_range<test_char_type*> rng2(data2, data2 + 1);
    do_test_iterator_range(rng2);
    BOOST_CHECK_EQUAL(lexical_cast<std::string>(rng2), "1");

    const test_char_type cdata2[] = "11";
    iterator_range<const test_char_type*> crng2(cdata2, cdata2 + 1);
    do_test_iterator_range(crng2);
    BOOST_CHECK_EQUAL(lexical_cast<std::string>(crng2), "1");
}

void test_unsigned_char_iterator_ranges() 
{
    typedef unsigned char test_char_type;

    // Zero terminated
    test_char_type data1[] = "1";
    iterator_range<test_char_type*> rng1(data1, data1 + 1);
    do_test_iterator_range(rng1);
    BOOST_CHECK_EQUAL(lexical_cast<std::string>(rng1), "1");

    const test_char_type cdata1[] = "1";
    iterator_range<const test_char_type*> crng1(cdata1, cdata1 + 1);
    do_test_iterator_range(crng1);
    BOOST_CHECK_EQUAL(lexical_cast<std::string>(crng1), "1");

    // Non zero terminated
    test_char_type data2[] = "11";
    iterator_range<test_char_type*> rng2(data2, data2 + 1);
    do_test_iterator_range(rng2);
    BOOST_CHECK_EQUAL(lexical_cast<std::string>(rng2), "1");

    const test_char_type cdata2[] = "11";
    iterator_range<const test_char_type*> crng2(cdata2, cdata2 + 1);
    do_test_iterator_range(crng2);
    BOOST_CHECK_EQUAL(lexical_cast<std::string>(crng2), "1");
}

void test_signed_char_iterator_ranges() 
{
    typedef signed char test_char_type;

    // Zero terminated
    test_char_type data1[] = "1";
    iterator_range<test_char_type*> rng1(data1, data1 + 1);
    do_test_iterator_range(rng1);
    BOOST_CHECK_EQUAL(lexical_cast<std::string>(rng1), "1");

    const test_char_type cdata1[] = "1";
    iterator_range<const test_char_type*> crng1(cdata1, cdata1 + 1);
    do_test_iterator_range(crng1);
    BOOST_CHECK_EQUAL(lexical_cast<std::string>(crng1), "1");

    // Non zero terminated
    test_char_type data2[] = "11";
    iterator_range<test_char_type*> rng2(data2, data2 + 1);
    do_test_iterator_range(rng2);
    BOOST_CHECK_EQUAL(lexical_cast<std::string>(rng2), "1");

    const test_char_type cdata2[] = "11";
    iterator_range<const test_char_type*> crng2(cdata2, cdata2 + 1);
    do_test_iterator_range(crng2);
    BOOST_CHECK_EQUAL(lexical_cast<std::string>(crng2), "1");
}

void test_wide_char_iterator_ranges() 
{
#ifndef BOOST_LCAST_NO_WCHAR_T
    typedef wchar_t test_char_type;

    // Zero terminated
    test_char_type data1[] = L"1";
    iterator_range<test_char_type*> rng1(data1, data1 + 1);
    do_test_iterator_range(rng1);

    const test_char_type cdata1[] = L"1";
    iterator_range<const test_char_type*> crng1(cdata1, cdata1 + 1);
    do_test_iterator_range(crng1);

    // Non zero terminated
    test_char_type data2[] = L"11";
    iterator_range<test_char_type*> rng2(data2, data2 + 1);
    do_test_iterator_range(rng2);

    const test_char_type cdata2[] = L"11";
    iterator_range<const test_char_type*> crng2(cdata2, cdata2 + 1);
    do_test_iterator_range(crng2);
#endif

    BOOST_CHECK(true);
}

unit_test::test_suite *init_unit_test_suite(int, char *[])
{
    unit_test::test_suite *suite = BOOST_TEST_SUITE("lexical_cast. Testing conversions using iterator_range<>");
    suite->add(BOOST_TEST_CASE(&test_char_iterator_ranges));
    suite->add(BOOST_TEST_CASE(&test_unsigned_char_iterator_ranges));
    suite->add(BOOST_TEST_CASE(&test_signed_char_iterator_ranges));
    suite->add(BOOST_TEST_CASE(&test_wide_char_iterator_ranges));

    return suite;
}
