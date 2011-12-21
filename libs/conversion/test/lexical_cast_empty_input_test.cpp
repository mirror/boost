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
#include <boost/test/unit_test.hpp>
#include <boost/range/iterator_range.hpp>

using namespace boost;

void test_empty_iterator_range()
{
    boost::iterator_range<const char*> v;
    BOOST_CHECK_THROW(lexical_cast<int>(v), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<float>(v), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<double>(v), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<long double>(v), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<unsigned int>(v), bad_lexical_cast);
    BOOST_CHECK_EQUAL(lexical_cast<std::string>(v), std::string());
    BOOST_CHECK_THROW(lexical_cast<unsigned short>(v), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<char>(v), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<unsigned char>(v), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<signed char>(v), bad_lexical_cast);
}

void test_empty_string()
{
    std::string v;
    BOOST_CHECK_THROW(lexical_cast<int>(v), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<float>(v), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<double>(v), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<long double>(v), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<unsigned int>(v), bad_lexical_cast);
    BOOST_CHECK_EQUAL(lexical_cast<std::string>(v), std::string());
    BOOST_CHECK_THROW(lexical_cast<unsigned short>(v), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<char>(v), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<unsigned char>(v), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<signed char>(v), bad_lexical_cast);
}

struct Escape
{
    Escape(const std::string& s)
        : str_(s)
    {}

    std::string str_;
};

inline std::ostream& operator<< (std::ostream& o, const Escape& rhs)
{
    return o << rhs.str_;
}

void test_empty_user_class()
{
    Escape v("");
    BOOST_CHECK_THROW(lexical_cast<int>(v), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<float>(v), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<double>(v), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<long double>(v), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<unsigned int>(v), bad_lexical_cast);
    BOOST_CHECK_EQUAL(lexical_cast<std::string>(v), std::string());
    BOOST_CHECK_THROW(lexical_cast<unsigned short>(v), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<char>(v), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<unsigned char>(v), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<signed char>(v), bad_lexical_cast);
}

namespace std {
inline std::ostream & operator<<(std::ostream & out, const std::vector<long> & v)
{
    std::ostream_iterator<long> it(out);
    std::copy(v.begin(), v.end(), it);
    assert(out);
    return out;
}
}

void test_empty_vector()
{
    std::vector<long> v;
    BOOST_CHECK_THROW(lexical_cast<int>(v), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<float>(v), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<double>(v), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<long double>(v), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<unsigned int>(v), bad_lexical_cast);
    BOOST_CHECK_EQUAL(lexical_cast<std::string>(v), std::string());
    BOOST_CHECK_THROW(lexical_cast<unsigned short>(v), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<char>(v), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<unsigned char>(v), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<signed char>(v), bad_lexical_cast);
}

unit_test::test_suite *init_unit_test_suite(int, char *[])
{
    unit_test::test_suite *suite =
        BOOST_TEST_SUITE("lexical_cast. Empty input unit test");
    suite->add(BOOST_TEST_CASE(&test_empty_iterator_range));
    suite->add(BOOST_TEST_CASE(&test_empty_string));
    suite->add(BOOST_TEST_CASE(&test_empty_user_class));
    suite->add(BOOST_TEST_CASE(&test_empty_vector));

    return suite;
}
