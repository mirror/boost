// Copyright Vladimir Prus 2002-2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)


#include <boost/program_options/options_description.hpp>
using namespace boost::program_options;

#include <boost/function.hpp>
using namespace boost;

#define BOOST_INCLUDE_MAIN  // for testing, include rather than link
#include <boost/test/test_tools.hpp>

#include <utility>
#include <string>
using namespace std;

void test_type()
{
    options_description desc;
    desc.add_options()
        ("foo", value<int>(), "")
        ("bar", value<std::string>(), "")
        ;
    
    const typed_value_base* b = dynamic_cast<const typed_value_base*>
        (desc.find("foo", false).semantic().get());
    BOOST_CHECK(b);
    BOOST_CHECK(b->value_type() == typeid(int));

    const typed_value_base* b2 = dynamic_cast<const typed_value_base*>
        (desc.find("bar", false).semantic().get());
    BOOST_CHECK(b2);
    BOOST_CHECK(b2->value_type() == typeid(std::string));
}

void test_approximation()
{
    options_description desc;
    desc.add_options()
    ("foo", new untyped_value())
    ("fee", new untyped_value())
    ("baz", new untyped_value());

    BOOST_CHECK_EQUAL(desc.find("fo", true).long_name(), "foo");
//    BOOST_CHECK(desc.count_approx("foo") == 1);
//    set<string> a = desc.approximations("f");
//    BOOST_CHECK(a.size() == 2);
//    BOOST_CHECK(*a.begin() == "fee");
//    BOOST_CHECK(*(++a.begin()) == "foo");
}

int test_main(int, char* [])
{
    test_type();
    test_approximation();
    return 0;
}
