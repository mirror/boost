#if defined(_MSC_VER) && !defined(__ICL)
#pragma warning(disable: 4786)  // identifier truncated in debug info
#pragma warning(disable: 4710)  // function not inlined
#pragma warning(disable: 4711)  // function selected for automatic inline expansion
#pragma warning(disable: 4514)  // unreferenced inline removed
#endif

//
//  shared_ptr_test.cpp - a test for shared_ptr.hpp and weak_ptr.hpp
//
//  Copyright (c) 2001 Peter Dimov and Multi Media Ltd.
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//

#define BOOST_INCLUDE_MAIN
#include <boost/test/test_tools.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

bool boost_error(char const *, char const *, char const *, long)
{
    return true;
}

namespace
{
    int cnt = 0;
}

struct X
{
    X()
    {
        ++cnt;
        std::cout << "X(" << this << ")::X()\n";
    }

    virtual ~X()
    {
        --cnt;
        std::cout << "X(" << this << ")::~X()\n";
    }

private:

    X(X const &);
    X & operator= (X const &);
};

struct Y: public X
{
    Y()
    {
        ++cnt;
        std::cout << "Y(" << this << ")::Y()\n";
    }

    ~Y()
    {
        --cnt;
        std::cout << "Y(" << this << ")::~Y()\n";
    }

private:

    Y(Y const &);
    Y & operator= (Y const &);
};

int * get_object()
{
    ++cnt;
    std::cout << "get_object()\n";
    return &cnt;
}

void release_object(int * p)
{
    BOOST_TEST(p == &cnt);
    --cnt;
    std::cout << "release_object()\n";
}

int test_main(int, char * [])
{
    using namespace boost;

    {
        shared_ptr<X> p(new Y);
        shared_ptr<X> p2(new X);

        shared_ptr<Y> p3 = shared_dynamic_cast<Y>(p);
        shared_ptr<Y> p4 = shared_dynamic_cast<Y>(p2);

        BOOST_TEST(p.use_count() == 2);
        BOOST_TEST(p2.use_count() == 1);
        BOOST_TEST(p3.use_count() == 2);
        BOOST_TEST(p4.use_count() == 1);

        shared_ptr<void> p5(p);

        std::cout << "--\n";

        p.reset();
        p2.reset();
        p3.reset();
        p4.reset();

        std::cout << "--\n";

        BOOST_TEST(p5.use_count() == 1);

        weak_ptr<X> wp1;

        BOOST_TEST(wp1.use_count() == 0);
        BOOST_TEST(wp1.get() == 0);

        weak_ptr<X> wp2 = shared_static_cast<X>(p5);

        BOOST_TEST(wp2.use_count() == 1);
        BOOST_TEST(wp2.get() != 0);

        weak_ptr<Y> wp3 = shared_dynamic_cast<Y>(wp2);

        BOOST_TEST(wp3.use_count() == 1);
        BOOST_TEST(wp3.get() != 0);
        BOOST_TEST(wp2 == wp3);

        weak_ptr<X> wp4(wp3);

        wp1 = p2;
        wp1 = p4;
        wp1 = wp3;
        wp1 = wp2;

        BOOST_TEST(wp1.use_count() == 1);
        BOOST_TEST(wp1.get() != 0);
        BOOST_TEST(wp1 == wp2);

        p5.reset();

        BOOST_TEST(wp1.use_count() == 0);
        BOOST_TEST(wp1.get() == 0);

        BOOST_TEST(wp2.use_count() == 0);
        BOOST_TEST(wp2.get() == 0);

        BOOST_TEST(wp3.use_count() == 0);
        BOOST_TEST(wp3.get() == 0);

        shared_ptr<int> p6(get_object(), release_object);
    }

    BOOST_TEST(cnt == 0);

    return 0;
}
