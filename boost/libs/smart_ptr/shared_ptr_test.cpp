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

    virtual int id() const
    {
        return 1;
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

    virtual int id() const
    {
        return 2;
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

template<class T> void test_is_X(T const & p)
{
    BOOST_TEST(p->id() == 1);
    BOOST_TEST((*p).id() == 1);
}

template<class T> void test_is_Y(T const & p)
{
    BOOST_TEST(p->id() == 2);
    BOOST_TEST((*p).id() == 2);
}

// std::rel_ops::operator!= breaks x != y when defined in the global namespace

#if defined(__STL_BEGIN_RELOPS_NAMESPACE) && !defined(__STL_USE_NAMESPACE_FOR_RELOPS)
#  define BOOST_BROKEN_INEQUALITY
#endif

template<class T> void test_eq(T const & a, T const & b)
{
    BOOST_TEST(a == b);

#ifndef BOOST_BROKEN_INEQUALITY

    BOOST_TEST(!(a != b));

#endif

    BOOST_TEST(!(a < b));
    BOOST_TEST(!(b < a));
}

template<class T> void test_ne(T const & a, T const & b)
{
    BOOST_TEST(!(a == b));

#ifndef BOOST_BROKEN_INEQUALITY

    BOOST_TEST(a != b);

#endif

    BOOST_TEST(a < b || b < a);
    BOOST_TEST(!(a < b && b < a));
}

template<class T, class U> void test_eq2(T const & a, U const & b)
{
    BOOST_TEST(a == b);

#ifndef BOOST_BROKEN_INEQUALITY

    BOOST_TEST(!(a != b));

#endif

}

template<class T, class U> void test_ne2(T const & a, U const & b)
{
    BOOST_TEST(!(a == b));

#ifndef BOOST_BROKEN_INEQUALITY

    BOOST_TEST(a != b);

#endif

}

int test_main(int, char * [])
{
    using namespace boost;

    {
        shared_ptr<X> p(new Y);
        shared_ptr<X> p2(new X);

        test_is_Y(p);
        test_is_X(p2);
        test_ne(p, p2);

        {
            shared_ptr<X> q(p);
            test_eq(p, q);
        }

        shared_ptr<Y> p3 = shared_dynamic_cast<Y>(p);
        shared_ptr<Y> p4 = shared_dynamic_cast<Y>(p2);

        BOOST_TEST(p.use_count() == 2);
        BOOST_TEST(p2.use_count() == 1);
        BOOST_TEST(p3.use_count() == 2);
        BOOST_TEST(p4.use_count() == 1);

        test_is_Y(p3);
        test_eq2(p, p3);
        test_ne2(p2, p4);

        shared_ptr<void> p5(p);

        test_eq2(p, p5);

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

        test_is_Y(wp2);
        test_ne(wp1, wp2);

        weak_ptr<Y> wp3 = shared_dynamic_cast<Y>(wp2);

        BOOST_TEST(wp3.use_count() == 1);
        BOOST_TEST(wp3.get() != 0);

        test_eq2(wp2, wp3);

        weak_ptr<X> wp4(wp3);

        test_eq(wp2, wp4);

        wp1 = p2;
        wp1 = p4;
        wp1 = wp3;
        wp1 = wp2;

        BOOST_TEST(wp1.use_count() == 1);
        BOOST_TEST(wp1.get() != 0);

        test_eq(wp1, wp2);

        weak_ptr<X> wp5;

        bool b1 = wp1 < wp5;
        bool b2 = wp5 < wp1;

        p5.reset();

        BOOST_TEST(wp1.use_count() == 0);
        BOOST_TEST(wp1.get() == 0);

        BOOST_TEST(wp2.use_count() == 0);
        BOOST_TEST(wp2.get() == 0);

        BOOST_TEST(wp3.use_count() == 0);
        BOOST_TEST(wp3.get() == 0);

        // Test operator< stability for std::set< weak_ptr<> >
        // Thanks to Joe Gottman for pointing this out

        BOOST_TEST(b1 == (wp1 < wp5));
        BOOST_TEST(b2 == (wp5 < wp1));

        shared_ptr<int> p6(get_object(), release_object);
    }

    BOOST_TEST(cnt == 0);

    return 0;
}
