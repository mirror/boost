
// Copyright Eric Niebler 2009
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id: string.cpp 49240 2009-04-01 09:21:07Z eric_niebler $
// $Date: 2009-04-01 02:21:07 -0700 (Wed, 1 Apr 2009) $
// $Revision: 49240 $

#include <string>
#include <cstring>
#include <iostream>

#include <boost/mpl/string.hpp>

#include <boost/mpl/at.hpp>
#include <boost/mpl/long.hpp>
#include <boost/mpl/back.hpp>
#include <boost/mpl/copy.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/mpl/erase.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/joint_view.hpp>
#include <boost/mpl/insert_range.hpp>
#include <boost/mpl/back_inserter.hpp>
#include <boost/mpl/iterator_range.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/detail/lightweight_test.hpp>
namespace mpl = boost::mpl;

// Accept a string as a template parameter!
template<char const *sz>
struct greeting
{
    std::string say_hello() const
    {
        return sz;
    }
};

struct push_char
{
    push_char(std::string &str)
      : str_(&str)
    {}

    void operator()(char ch) const
    {
        this->str_->push_back(ch);
    }

    std::string *str_;
};

void test1()
{
    BOOST_TEST(0 == std::strcmp(mpl::string<'Hell','o wo','rld!'>::c_str, "Hello world!"));
    BOOST_TEST((12 == mpl::size<mpl::string<'Hell','o wo','rld!'> >::type::value));
    BOOST_TEST(('w' == mpl::at_c<mpl::string<'Hell','o wo','rld!'>, 6>::type::value));

    // test using a string as a template parameter
    greeting<mpl::string<'Hell','o wo','rld!'>::c_str> g;
    BOOST_TEST("Hello world!" == g.say_hello());

    BOOST_TEST(0 == std::strcmp("", mpl::string<>::c_str));

    std::string result;
    mpl::for_each<mpl::string<'Hell','o wo','rld!'> >(push_char(result));
    BOOST_TEST("Hello world!" == result);

    BOOST_MPL_ASSERT((mpl::empty<mpl::string<> >));
    BOOST_MPL_ASSERT_NOT((mpl::empty<mpl::string<'hi!'> >));

    BOOST_TEST(('h' == mpl::front<mpl::string<'hi!'> >::type()));
    BOOST_TEST(('!' == mpl::back<mpl::string<'hi!'> >::type()));
}

// testing push_back
void test2()
{
    typedef mpl::push_back<mpl::string<>, mpl::char_<'a'> >::type t1;
    BOOST_TEST(0 == std::strcmp("a", t1::c_str));

    typedef mpl::push_back<t1, mpl::char_<'b'> >::type t2;
    BOOST_TEST(0 == std::strcmp("ab", t2::c_str));

    typedef mpl::push_back<t2, mpl::char_<'c'> >::type t3;
    BOOST_TEST(0 == std::strcmp("abc", t3::c_str));
    BOOST_MPL_ASSERT((boost::is_same<t3, mpl::string<'abc'> >));

    typedef mpl::push_back<t3, mpl::char_<'d'> >::type t4;
    BOOST_TEST(0 == std::strcmp("abcd", t4::c_str));

    typedef mpl::push_back<t4, mpl::char_<'e'> >::type t5;
    BOOST_TEST(0 == std::strcmp("abcde", t5::c_str));
    BOOST_MPL_ASSERT((boost::is_same<t5, mpl::string<'abcd','e'> >));

    typedef mpl::string<'aaaa','aaaa','aaaa','aaaa','aaaa','aaaa','aaaa','aaa'> almost_full;
    BOOST_TEST(0 == std::strcmp("aaaa" "aaaa" "aaaa" "aaaa" "aaaa" "aaaa" "aaaa" "aaa", almost_full::c_str));

    typedef mpl::push_back<almost_full, mpl::char_<'X'> >::type t6;
    BOOST_TEST(0 == std::strcmp("aaaa" "aaaa" "aaaa" "aaaa" "aaaa" "aaaa" "aaaa" "aaaX", t6::c_str));
}

// testing push_front
void test3()
{
    typedef mpl::push_front<mpl::string<>, mpl::char_<'a'> >::type t1;
    BOOST_TEST(0 == std::strcmp("a", t1::c_str));

    typedef mpl::push_front<t1, mpl::char_<'b'> >::type t2;
    BOOST_TEST(0 == std::strcmp("ba", t2::c_str));

    typedef mpl::push_front<t2, mpl::char_<'c'> >::type t3;
    BOOST_TEST(0 == std::strcmp("cba", t3::c_str));

    typedef mpl::push_front<t3, mpl::char_<'d'> >::type t4;
    BOOST_TEST(0 == std::strcmp("dcba", t4::c_str));

    typedef mpl::push_front<t4, mpl::char_<'e'> >::type t5;
    BOOST_TEST(0 == std::strcmp("edcba", t5::c_str));

    typedef mpl::string<'aaa','aaaa','aaaa','aaaa','aaaa','aaaa','aaaa','aaaa'> almost_full;
    BOOST_TEST(0 == std::strcmp("aaa" "aaaa" "aaaa" "aaaa" "aaaa" "aaaa" "aaaa" "aaaa", almost_full::c_str));

    typedef mpl::push_front<almost_full, mpl::char_<'X'> >::type t6;
    BOOST_TEST(0 == std::strcmp("Xaaa" "aaaa" "aaaa" "aaaa" "aaaa" "aaaa" "aaaa" "aaaa", t6::c_str));
}

void test4()
{
    // back-inserter with copy
    typedef mpl::vector_c<char, 'a','b','c','d','e'> rgc;
    typedef mpl::copy<rgc, mpl::back_inserter<mpl::string<> > >::type str;
    BOOST_TEST(0 == std::strcmp("abcde", str::c_str));
}

// test insert_range and erase
void test5()
{
    typedef mpl::string<'Hell','o wo','rld!'> hello;
    typedef mpl::advance_c<mpl::begin<hello>::type, 5>::type where;
    typedef mpl::string<' cru','el'> cruel;
    typedef mpl::insert_range<hello, where, cruel>::type hello_cruel;
    BOOST_TEST(0 == std::strcmp("Hello cruel world!", hello_cruel::c_str));

    typedef mpl::erase<hello, mpl::begin<hello>::type, where>::type erased1;
    BOOST_TEST(0 == std::strcmp(" world!", erased1::c_str));
}


int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();

    return boost::report_errors();
}
