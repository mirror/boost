#if defined(_MSC_VER) && !defined(__ICL) && !defined(__COMO__)
#pragma warning(disable: 4786)  // identifier truncated in debug info
#pragma warning(disable: 4710)  // function not inlined
#pragma warning(disable: 4711)  // function selected for automatic inline expansion
#pragma warning(disable: 4514)  // unreferenced inline removed
#pragma warning(disable: 4355)  // 'this' : used in base member initializer list
#endif

//
//  shared_ptr_test.cpp - a test for shared_ptr.hpp and weak_ptr.hpp
//
//  Copyright (c) 2001, 2002 Peter Dimov and Multi Media Ltd.
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//

#include <boost/detail/lightweight_test.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#include <map>
#include <vector>

//

namespace n_element_type
{

void f(int &)
{
}

void test()
{
    typedef boost::shared_ptr<int>::element_type T;
    T t;
    f(t);
}

} // namespace n_element_type

namespace n_constructors
{

class incomplete;

void default_constructor()
{
    {
        boost::shared_ptr<int> pi;
        BOOST_TEST(pi? false: true);
        BOOST_TEST(!pi);
        BOOST_TEST(pi.get() == 0);
    }

    {
        boost::shared_ptr<void> pv;
        BOOST_TEST(pv? false: true);
        BOOST_TEST(!pv);
        BOOST_TEST(pv.get() == 0);
    }

    {
        boost::shared_ptr<incomplete> px;
        BOOST_TEST(px? false: true);
        BOOST_TEST(!px);
        BOOST_TEST(px.get() == 0);
    }
}

struct A
{
    int dummy;
};

struct X
{
    static long instances;

    X()
    {
        ++instances;
    }

    ~X()
    {
        --instances;
    }

private:

    X(X const &);
    X & operator= (X const &);
};

long X::instances = 0;

struct Y: public A, public X
{
    static long instances;

    Y()
    {
        ++instances;
    }

    ~Y()
    {
        --instances;
    }

private:

    Y(Y const &);
    Y & operator= (Y const &);
};

long Y::instances = 0;

void pointer_constructor()
{
    {
        boost::shared_ptr<int> pi(static_cast<int*>(0));
        BOOST_TEST(pi? false: true);
        BOOST_TEST(!pi);
        BOOST_TEST(pi.get() == 0);
        BOOST_TEST(pi.use_count() == 1);
        BOOST_TEST(pi.unique());
    }

    {
        boost::shared_ptr<int const> pi(static_cast<int*>(0));
        BOOST_TEST(pi? false: true);
        BOOST_TEST(!pi);
        BOOST_TEST(pi.get() == 0);
        BOOST_TEST(pi.use_count() == 1);
        BOOST_TEST(pi.unique());
    }

    {
        boost::shared_ptr<void> pv(static_cast<int*>(0));
        BOOST_TEST(pv? false: true);
        BOOST_TEST(!pv);
        BOOST_TEST(pv.get() == 0);
        BOOST_TEST(pv.use_count() == 1);
        BOOST_TEST(pv.unique());
    }

    {
        boost::shared_ptr<void const> pv(static_cast<int*>(0));
        BOOST_TEST(pv? false: true);
        BOOST_TEST(!pv);
        BOOST_TEST(pv.get() == 0);
        BOOST_TEST(pv.use_count() == 1);
        BOOST_TEST(pv.unique());
    }

    {
        boost::shared_ptr<X> px(static_cast<X*>(0));
        BOOST_TEST(px? false: true);
        BOOST_TEST(!px);
        BOOST_TEST(px.get() == 0);
        BOOST_TEST(px.use_count() == 1);
        BOOST_TEST(px.unique());
    }

    {
        boost::shared_ptr<X const> px(static_cast<X*>(0));
        BOOST_TEST(px? false: true);
        BOOST_TEST(!px);
        BOOST_TEST(px.get() == 0);
        BOOST_TEST(px.use_count() == 1);
        BOOST_TEST(px.unique());
    }

    {
        boost::shared_ptr<X> px(static_cast<Y*>(0));
        BOOST_TEST(px? false: true);
        BOOST_TEST(!px);
        BOOST_TEST(px.get() == 0);
        BOOST_TEST(px.use_count() == 1);
        BOOST_TEST(px.unique());
    }

    {
        boost::shared_ptr<X const> px(static_cast<Y*>(0));
        BOOST_TEST(px? false: true);
        BOOST_TEST(!px);
        BOOST_TEST(px.get() == 0);
        BOOST_TEST(px.use_count() == 1);
        BOOST_TEST(px.unique());
    }

    {
        boost::shared_ptr<void> pv(static_cast<X*>(0));
        BOOST_TEST(pv? false: true);
        BOOST_TEST(!pv);
        BOOST_TEST(pv.get() == 0);
        BOOST_TEST(pv.use_count() == 1);
        BOOST_TEST(pv.unique());
    }

    {
        boost::shared_ptr<void const> pv(static_cast<X*>(0));
        BOOST_TEST(pv? false: true);
        BOOST_TEST(!pv);
        BOOST_TEST(pv.get() == 0);
        BOOST_TEST(pv.use_count() == 1);
        BOOST_TEST(pv.unique());
    }

    {
        int * p = new int(7);
        boost::shared_ptr<int> pi(p);
        BOOST_TEST(pi? true: false);
        BOOST_TEST(!!pi);
        BOOST_TEST(pi.get() == p);
        BOOST_TEST(pi.use_count() == 1);
        BOOST_TEST(pi.unique());
        BOOST_TEST(*pi == 7);
    }

    {
        int * p = new int(7);
        boost::shared_ptr<int const> pi(p);
        BOOST_TEST(pi? true: false);
        BOOST_TEST(!!pi);
        BOOST_TEST(pi.get() == p);
        BOOST_TEST(pi.use_count() == 1);
        BOOST_TEST(pi.unique());
        BOOST_TEST(*pi == 7);
    }

    {
        int * p = new int(7);
        boost::shared_ptr<void> pv(p);
        BOOST_TEST(pv? true: false);
        BOOST_TEST(!!pv);
        BOOST_TEST(pv.get() == p);
        BOOST_TEST(pv.use_count() == 1);
        BOOST_TEST(pv.unique());
    }

    {
        int * p = new int(7);
        boost::shared_ptr<void const> pv(p);
        BOOST_TEST(pv? true: false);
        BOOST_TEST(!!pv);
        BOOST_TEST(pv.get() == p);
        BOOST_TEST(pv.use_count() == 1);
        BOOST_TEST(pv.unique());
    }

    BOOST_TEST(X::instances == 0);

    {
        X * p = new X;
        boost::shared_ptr<X> px(p);
        BOOST_TEST(px? true: false);
        BOOST_TEST(!!px);
        BOOST_TEST(px.get() == p);
        BOOST_TEST(px.use_count() == 1);
        BOOST_TEST(px.unique());
        BOOST_TEST(X::instances == 1);
    }

    BOOST_TEST(X::instances == 0);

    {
        X * p = new X;
        boost::shared_ptr<X const> px(p);
        BOOST_TEST(px? true: false);
        BOOST_TEST(!!px);
        BOOST_TEST(px.get() == p);
        BOOST_TEST(px.use_count() == 1);
        BOOST_TEST(px.unique());
        BOOST_TEST(X::instances == 1);
    }

    BOOST_TEST(X::instances == 0);

    {
        X * p = new X;
        boost::shared_ptr<void> pv(p);
        BOOST_TEST(pv? true: false);
        BOOST_TEST(!!pv);
        BOOST_TEST(pv.get() == p);
        BOOST_TEST(pv.use_count() == 1);
        BOOST_TEST(pv.unique());
        BOOST_TEST(X::instances == 1);
    }

    BOOST_TEST(X::instances == 0);

    {
        X * p = new X;
        boost::shared_ptr<void const> pv(p);
        BOOST_TEST(pv? true: false);
        BOOST_TEST(!!pv);
        BOOST_TEST(pv.get() == p);
        BOOST_TEST(pv.use_count() == 1);
        BOOST_TEST(pv.unique());
        BOOST_TEST(X::instances == 1);
    }

    BOOST_TEST(X::instances == 0);
    BOOST_TEST(Y::instances == 0);

    {
        Y * p = new Y;
        boost::shared_ptr<X> px(p);
        BOOST_TEST(px? true: false);
        BOOST_TEST(!!px);
        BOOST_TEST(px.get() == p);
        BOOST_TEST(px.use_count() == 1);
        BOOST_TEST(px.unique());
        BOOST_TEST(X::instances == 1);
        BOOST_TEST(Y::instances == 1);
    }

    BOOST_TEST(X::instances == 0);
    BOOST_TEST(Y::instances == 0);

    {
        Y * p = new Y;
        boost::shared_ptr<X const> px(p);
        BOOST_TEST(px? true: false);
        BOOST_TEST(!!px);
        BOOST_TEST(px.get() == p);
        BOOST_TEST(px.use_count() == 1);
        BOOST_TEST(px.unique());
        BOOST_TEST(X::instances == 1);
        BOOST_TEST(Y::instances == 1);
    }

    BOOST_TEST(X::instances == 0);
    BOOST_TEST(Y::instances == 0);
}

int m = 0;

void deleter(int * p)
{
    BOOST_TEST(p == 0);
}

void deleter2(int * p)
{
    BOOST_TEST(p == &m);
    ++*p;
}

struct deleter3
{
	void operator()(incomplete * p)
	{
		BOOST_TEST(p == 0);
	}
};

// Borland C++ 5.5.1 fails on static_cast<incomplete*>(0)

incomplete * p0 = 0;

void deleter_constructor()
{
    {
        boost::shared_ptr<int> pi(static_cast<int*>(0), deleter);
        BOOST_TEST(pi? false: true);
        BOOST_TEST(!pi);
        BOOST_TEST(pi.get() == 0);
        BOOST_TEST(pi.use_count() == 1);
        BOOST_TEST(pi.unique());
    }

    {
        boost::shared_ptr<void> pv(static_cast<int*>(0), &deleter);
        BOOST_TEST(pv? false: true);
        BOOST_TEST(!pv);
        BOOST_TEST(pv.get() == 0);
        BOOST_TEST(pv.use_count() == 1);
        BOOST_TEST(pv.unique());
    }

    {
        boost::shared_ptr<void const> pv(static_cast<int*>(0), deleter);
        BOOST_TEST(pv? false: true);
        BOOST_TEST(!pv);
        BOOST_TEST(pv.get() == 0);
        BOOST_TEST(pv.use_count() == 1);
        BOOST_TEST(pv.unique());
    }

    {
        boost::shared_ptr<incomplete> px(p0, deleter3());
        BOOST_TEST(px? false: true);
        BOOST_TEST(!px);
        BOOST_TEST(px.get() == 0);
        BOOST_TEST(px.use_count() == 1);
        BOOST_TEST(px.unique());
    }

    {
        boost::shared_ptr<void> pv(p0, deleter3());
        BOOST_TEST(pv? false: true);
        BOOST_TEST(!pv);
        BOOST_TEST(pv.get() == 0);
        BOOST_TEST(pv.use_count() == 1);
        BOOST_TEST(pv.unique());
    }

    {
        boost::shared_ptr<void const> pv(p0, deleter3());
        BOOST_TEST(pv? false: true);
        BOOST_TEST(!pv);
        BOOST_TEST(pv.get() == 0);
        BOOST_TEST(pv.use_count() == 1);
        BOOST_TEST(pv.unique());
    }

    BOOST_TEST(m == 0);

    {
        boost::shared_ptr<int> pi(&m, deleter2);
        BOOST_TEST(pi? true: false);
        BOOST_TEST(!!pi);
        BOOST_TEST(pi.get() == &m);
        BOOST_TEST(pi.use_count() == 1);
        BOOST_TEST(pi.unique());
    }

    BOOST_TEST(m == 1);

    {
        boost::shared_ptr<int const> pi(&m, &deleter2);
        BOOST_TEST(pi? true: false);
        BOOST_TEST(!!pi);
        BOOST_TEST(pi.get() == &m);
        BOOST_TEST(pi.use_count() == 1);
        BOOST_TEST(pi.unique());
    }

    BOOST_TEST(m == 2);

    {
        boost::shared_ptr<void> pv(&m, deleter2);
        BOOST_TEST(pv? true: false);
        BOOST_TEST(!!pv);
        BOOST_TEST(pv.get() == &m);
        BOOST_TEST(pv.use_count() == 1);
        BOOST_TEST(pv.unique());
    }

    BOOST_TEST(m == 3);

    {
        boost::shared_ptr<void const> pv(&m, &deleter2);
        BOOST_TEST(pv? true: false);
        BOOST_TEST(!!pv);
        BOOST_TEST(pv.get() == &m);
        BOOST_TEST(pv.use_count() == 1);
        BOOST_TEST(pv.unique());
    }

    BOOST_TEST(m == 4);
}

void copy_constructor()
{
    {
        boost::shared_ptr<int> pi;

        boost::shared_ptr<int> pi2(pi);
        BOOST_TEST(pi2 == pi);
        BOOST_TEST(pi2? false: true);
        BOOST_TEST(!pi2);
        BOOST_TEST(pi2.get() == 0);

        boost::shared_ptr<void> pi3(pi);
        BOOST_TEST(pi3 == pi);
        BOOST_TEST(pi3? false: true);
        BOOST_TEST(!pi3);
        BOOST_TEST(pi3.get() == 0);

        boost::shared_ptr<void> pi4(pi3);
        BOOST_TEST(pi4 == pi3);
        BOOST_TEST(pi4? false: true);
        BOOST_TEST(!pi4);
        BOOST_TEST(pi4.get() == 0);
    }

    {
        boost::shared_ptr<void> pv;

        boost::shared_ptr<void> pv2(pv);
        BOOST_TEST(pv2 == pv);
        BOOST_TEST(pv2? false: true);
        BOOST_TEST(!pv2);
        BOOST_TEST(pv2.get() == 0);
    }

    {
        boost::shared_ptr<incomplete> px;

        boost::shared_ptr<incomplete> px2(px);
        BOOST_TEST(px2 == px);
        BOOST_TEST(px2? false: true);
        BOOST_TEST(!px2);
        BOOST_TEST(px2.get() == 0);

        boost::shared_ptr<void> px3(px);
        BOOST_TEST(px3 == px);
        BOOST_TEST(px3? false: true);
        BOOST_TEST(!px3);
        BOOST_TEST(px3.get() == 0);
    }

    {
        boost::shared_ptr<int> pi(static_cast<int*>(0));

        boost::shared_ptr<int> pi2(pi);
        BOOST_TEST(pi2 == pi);
        BOOST_TEST(pi2? false: true);
        BOOST_TEST(!pi2);
        BOOST_TEST(pi2.get() == 0);
        BOOST_TEST(pi2.use_count() == 2);
        BOOST_TEST(!pi2.unique());

        BOOST_TEST(pi.use_count() == pi2.use_count());
        BOOST_TEST(!(pi < pi2 || pi2 < pi)); // shared ownership test

        boost::shared_ptr<void> pi3(pi);
        BOOST_TEST(pi3 == pi);
        BOOST_TEST(pi3? false: true);
        BOOST_TEST(!pi3);
        BOOST_TEST(pi3.get() == 0);
        BOOST_TEST(pi3.use_count() == 3);
        BOOST_TEST(!pi3.unique());

        boost::shared_ptr<void> pi4(pi2);
        BOOST_TEST(pi4 == pi2);
        BOOST_TEST(pi4? false: true);
        BOOST_TEST(!pi4);
        BOOST_TEST(pi4.get() == 0);
        BOOST_TEST(pi4.use_count() == 4);
        BOOST_TEST(!pi4.unique());

        BOOST_TEST(pi3.use_count() == pi4.use_count());
        BOOST_TEST(!(pi3 < pi4 || pi4 < pi3)); // shared ownership test
    }

    {
        boost::shared_ptr<X> px(static_cast<X*>(0));

        boost::shared_ptr<X> px2(px);
        BOOST_TEST(px2 == px);
        BOOST_TEST(px2? false: true);
        BOOST_TEST(!px2);
        BOOST_TEST(px2.get() == 0);
        BOOST_TEST(px2.use_count() == 2);
        BOOST_TEST(!px2.unique());

        BOOST_TEST(px.use_count() == px2.use_count());
        BOOST_TEST(!(px < px2 || px2 < px)); // shared ownership test

        boost::shared_ptr<void> px3(px);
        BOOST_TEST(px3 == px);
        BOOST_TEST(px3? false: true);
        BOOST_TEST(!px3);
        BOOST_TEST(px3.get() == 0);
        BOOST_TEST(px3.use_count() == 3);
        BOOST_TEST(!px3.unique());

        boost::shared_ptr<void> px4(px2);
        BOOST_TEST(px4 == px2);
        BOOST_TEST(px4? false: true);
        BOOST_TEST(!px4);
        BOOST_TEST(px4.get() == 0);
        BOOST_TEST(px4.use_count() == 4);
        BOOST_TEST(!px4.unique());

        BOOST_TEST(px3.use_count() == px4.use_count());
        BOOST_TEST(!(px3 < px4 || px4 < px3)); // shared ownership test
    }

    {
        int * p = new int(7);
        boost::shared_ptr<int> pi(p);

        boost::shared_ptr<int> pi2(pi);
        BOOST_TEST(pi2 == pi);
        BOOST_TEST(pi2? true: false);
        BOOST_TEST(!!pi2);
        BOOST_TEST(pi2.get() == p);
        BOOST_TEST(pi2.use_count() == 2);
        BOOST_TEST(!pi2.unique());
        BOOST_TEST(*pi2 == 7);

        BOOST_TEST(pi.use_count() == pi2.use_count());
        BOOST_TEST(!(pi < pi2 || pi2 < pi)); // shared ownership test
    }

    {
        int * p = new int(7);
        boost::shared_ptr<void> pv(p);
        BOOST_TEST(pv.get() == p);

        boost::shared_ptr<void> pv2(pv);
        BOOST_TEST(pv2 == pv);
        BOOST_TEST(pv2? true: false);
        BOOST_TEST(!!pv2);
        BOOST_TEST(pv2.get() == p);
        BOOST_TEST(pv2.use_count() == 2);
        BOOST_TEST(!pv2.unique());

        BOOST_TEST(pv.use_count() == pv2.use_count());
        BOOST_TEST(!(pv < pv2 || pv2 < pv)); // shared ownership test
    }

    BOOST_TEST(X::instances == 0);

    {
        X * p = new X;
        boost::shared_ptr<X> px(p);
        BOOST_TEST(px.get() == p);

        boost::shared_ptr<X> px2(px);
        BOOST_TEST(px2 == px);
        BOOST_TEST(px2? true: false);
        BOOST_TEST(!!px2);
        BOOST_TEST(px2.get() == p);
        BOOST_TEST(px2.use_count() == 2);
        BOOST_TEST(!px2.unique());

        BOOST_TEST(X::instances == 1);

        BOOST_TEST(px.use_count() == px2.use_count());
        BOOST_TEST(!(px < px2 || px2 < px)); // shared ownership test

        boost::shared_ptr<void> px3(px);
        BOOST_TEST(px3 == px);
        BOOST_TEST(px3? true: false);
        BOOST_TEST(!!px3);
        BOOST_TEST(px3.get() == p);
        BOOST_TEST(px3.use_count() == 3);
        BOOST_TEST(!px3.unique());

        boost::shared_ptr<void> px4(px2);
        BOOST_TEST(px4 == px2);
        BOOST_TEST(px4? true: false);
        BOOST_TEST(!!px4);
        BOOST_TEST(px4.get() == p);
        BOOST_TEST(px4.use_count() == 4);
        BOOST_TEST(!px4.unique());

        BOOST_TEST(px3.use_count() == px4.use_count());
        BOOST_TEST(!(px3 < px4 || px4 < px3)); // shared ownership test
    }

    BOOST_TEST(X::instances == 0);
    BOOST_TEST(Y::instances == 0);

    {
        Y * p = new Y;
        boost::shared_ptr<Y> py(p);
        BOOST_TEST(py.get() == p);

        boost::shared_ptr<X> px(py);
        BOOST_TEST(px == py);
        BOOST_TEST(px? true: false);
        BOOST_TEST(!!px);
        BOOST_TEST(px.get() == p);
        BOOST_TEST(px.use_count() == 2);
        BOOST_TEST(!px.unique());

        BOOST_TEST(X::instances == 1);
        BOOST_TEST(Y::instances == 1);

        boost::shared_ptr<void const> pv(px);
        BOOST_TEST(pv == px);
        BOOST_TEST(pv? true: false);
        BOOST_TEST(!!pv);
        BOOST_TEST(pv.get() == px.get());
        BOOST_TEST(pv.use_count() == 3);
        BOOST_TEST(!pv.unique());

        boost::shared_ptr<void const> pv2(py);
        BOOST_TEST(pv2 == py);
        BOOST_TEST(pv2? true: false);
        BOOST_TEST(!!pv2);
        BOOST_TEST(pv2.get() == py.get());
        BOOST_TEST(pv2.use_count() == 4);
        BOOST_TEST(!pv2.unique());

        BOOST_TEST(pv.use_count() == pv2.use_count());
        BOOST_TEST(!(pv < pv2 || pv2 < pv)); // shared ownership test
    }

    BOOST_TEST(X::instances == 0);
    BOOST_TEST(Y::instances == 0);
}

void weak_ptr_constructor()
{
    boost::shared_ptr<Y> p(new Y);

    boost::weak_ptr<Y> wp(p);

    {
        boost::shared_ptr<Y> p2(wp);
        BOOST_TEST(p2? true: false);
        BOOST_TEST(!!p2);
        BOOST_TEST(p2.get() == p.get());
        BOOST_TEST(p2.use_count() == 2);
        BOOST_TEST(!p2.unique());

        BOOST_TEST(p.use_count() == p2.use_count());
        BOOST_TEST(!(p < p2 || p2 < p)); // shared ownership test

        boost::shared_ptr<X> p3(wp);
        BOOST_TEST(p3? true: false);
        BOOST_TEST(!!p3);
        BOOST_TEST(p3.get() == p.get());
        BOOST_TEST(p3.use_count() == 3);
        BOOST_TEST(!p3.unique());

        BOOST_TEST(p.use_count() == p3.use_count());
    }

    p.reset();

    try
    {
        boost::shared_ptr<Y> p2(wp);
        BOOST_ERROR("shared_ptr<Y> p2(wp) failed to throw");
    }
    catch(boost::bad_weak_ptr)
    {
    }

    try
    {
        boost::shared_ptr<X> p3(wp);
        BOOST_ERROR("shared_ptr<X> p3(wp) failed to throw");
    }
    catch(boost::bad_weak_ptr)
    {
    }
}

void auto_ptr_constructor()
{
    {
        std::auto_ptr<int> p;
        boost::shared_ptr<int> pi(p);
        BOOST_TEST(pi? false: true);
        BOOST_TEST(!pi);
        BOOST_TEST(pi.get() == 0);
        BOOST_TEST(pi.use_count() == 1);
        BOOST_TEST(pi.unique());
        BOOST_TEST(p.get() == 0);
    }

    {
        std::auto_ptr<int> p;
        boost::shared_ptr<int const> pi(p);
        BOOST_TEST(pi? false: true);
        BOOST_TEST(!pi);
        BOOST_TEST(pi.get() == 0);
        BOOST_TEST(pi.use_count() == 1);
        BOOST_TEST(pi.unique());
        BOOST_TEST(p.get() == 0);
    }

    {
        std::auto_ptr<int> p;
        boost::shared_ptr<void> pv(p);
        BOOST_TEST(pv? false: true);
        BOOST_TEST(!pv);
        BOOST_TEST(pv.get() == 0);
        BOOST_TEST(pv.use_count() == 1);
        BOOST_TEST(pv.unique());
        BOOST_TEST(p.get() == 0);
    }

    {
        std::auto_ptr<int> p;
        boost::shared_ptr<void const> pv(p);
        BOOST_TEST(pv? false: true);
        BOOST_TEST(!pv);
        BOOST_TEST(pv.get() == 0);
        BOOST_TEST(pv.use_count() == 1);
        BOOST_TEST(pv.unique());
        BOOST_TEST(p.get() == 0);
    }

    {
        std::auto_ptr<X> p;
        boost::shared_ptr<X> px(p);
        BOOST_TEST(px? false: true);
        BOOST_TEST(!px);
        BOOST_TEST(px.get() == 0);
        BOOST_TEST(px.use_count() == 1);
        BOOST_TEST(px.unique());
        BOOST_TEST(p.get() == 0);
    }

    {
        std::auto_ptr<X> p;
        boost::shared_ptr<X const> px(p);
        BOOST_TEST(px? false: true);
        BOOST_TEST(!px);
        BOOST_TEST(px.get() == 0);
        BOOST_TEST(px.use_count() == 1);
        BOOST_TEST(px.unique());
        BOOST_TEST(p.get() == 0);
    }

    {
        std::auto_ptr<Y> p;
        boost::shared_ptr<X> px(p);
        BOOST_TEST(px? false: true);
        BOOST_TEST(!px);
        BOOST_TEST(px.get() == 0);
        BOOST_TEST(px.use_count() == 1);
        BOOST_TEST(px.unique());
        BOOST_TEST(p.get() == 0);
    }

    {
        std::auto_ptr<Y> p;
        boost::shared_ptr<X const> px(p);
        BOOST_TEST(px? false: true);
        BOOST_TEST(!px);
        BOOST_TEST(px.get() == 0);
        BOOST_TEST(px.use_count() == 1);
        BOOST_TEST(px.unique());
        BOOST_TEST(p.get() == 0);
    }

    {
        std::auto_ptr<Y> p;
        boost::shared_ptr<void> pv(p);
        BOOST_TEST(pv? false: true);
        BOOST_TEST(!pv);
        BOOST_TEST(pv.get() == 0);
        BOOST_TEST(pv.use_count() == 1);
        BOOST_TEST(pv.unique());
        BOOST_TEST(p.get() == 0);
    }

    {
        std::auto_ptr<Y> p;
        boost::shared_ptr<void const> pv(p);
        BOOST_TEST(pv? false: true);
        BOOST_TEST(!pv);
        BOOST_TEST(pv.get() == 0);
        BOOST_TEST(pv.use_count() == 1);
        BOOST_TEST(pv.unique());
        BOOST_TEST(p.get() == 0);
    }

    {
        std::auto_ptr<int> p(new int(7));
        int * q = p.get();
        boost::shared_ptr<int> pi(p);
        BOOST_TEST(pi? true: false);
        BOOST_TEST(!!pi);
        BOOST_TEST(pi.get() == q);
        BOOST_TEST(pi.use_count() == 1);
        BOOST_TEST(pi.unique());
        BOOST_TEST(*pi == 7);

#if !defined(BOOST_MSVC) || (BOOST_MSVC >= 1300)
        BOOST_TEST(p.get() == 0);
#endif
    }

    {
        std::auto_ptr<int> p(new int(7));
        int * q = p.get();
        boost::shared_ptr<int const> pi(p);
        BOOST_TEST(pi? true: false);
        BOOST_TEST(!!pi);
        BOOST_TEST(pi.get() == q);
        BOOST_TEST(pi.use_count() == 1);
        BOOST_TEST(pi.unique());
        BOOST_TEST(*pi == 7);

#if !defined(BOOST_MSVC) || (BOOST_MSVC >= 1300)
        BOOST_TEST(p.get() == 0);
#endif
    }

    {
        std::auto_ptr<int> p(new int(7));
        int * q = p.get();
        boost::shared_ptr<void> pv(p);
        BOOST_TEST(pv? true: false);
        BOOST_TEST(!!pv);
        BOOST_TEST(pv.get() == q);
        BOOST_TEST(pv.use_count() == 1);
        BOOST_TEST(pv.unique());

#if !defined(BOOST_MSVC) || (BOOST_MSVC >= 1300)
        BOOST_TEST(p.get() == 0);
#endif
    }

    {
        std::auto_ptr<int> p(new int(7));
        int * q = p.get();
        boost::shared_ptr<void const> pv(p);
        BOOST_TEST(pv? true: false);
        BOOST_TEST(!!pv);
        BOOST_TEST(pv.get() == q);
        BOOST_TEST(pv.use_count() == 1);
        BOOST_TEST(pv.unique());

#if !defined(BOOST_MSVC) || (BOOST_MSVC >= 1300)
        BOOST_TEST(p.get() == 0);
#endif
    }

    BOOST_TEST(X::instances == 0);

    {
        std::auto_ptr<X> p(new X);
        X * q = p.get();
        boost::shared_ptr<X> px(p);
        BOOST_TEST(px? true: false);
        BOOST_TEST(!!px);
        BOOST_TEST(px.get() == q);
        BOOST_TEST(px.use_count() == 1);
        BOOST_TEST(px.unique());
        BOOST_TEST(X::instances == 1);

#if !defined(BOOST_MSVC) || (BOOST_MSVC >= 1300)
        BOOST_TEST(p.get() == 0);
#endif
    }

    BOOST_TEST(X::instances == 0);

    {
        std::auto_ptr<X> p(new X);
        X * q = p.get();
        boost::shared_ptr<X const> px(p);
        BOOST_TEST(px? true: false);
        BOOST_TEST(!!px);
        BOOST_TEST(px.get() == q);
        BOOST_TEST(px.use_count() == 1);
        BOOST_TEST(px.unique());
        BOOST_TEST(X::instances == 1);

#if !defined(BOOST_MSVC) || (BOOST_MSVC >= 1300)
        BOOST_TEST(p.get() == 0);
#endif
    }

    BOOST_TEST(X::instances == 0);

    {
        std::auto_ptr<X> p(new X);
        X * q = p.get();
        boost::shared_ptr<void> pv(p);
        BOOST_TEST(pv? true: false);
        BOOST_TEST(!!pv);
        BOOST_TEST(pv.get() == q);
        BOOST_TEST(pv.use_count() == 1);
        BOOST_TEST(pv.unique());
        BOOST_TEST(X::instances == 1);

#if !defined(BOOST_MSVC) || (BOOST_MSVC >= 1300)
        BOOST_TEST(p.get() == 0);
#endif
    }

    BOOST_TEST(X::instances == 0);

    {
        std::auto_ptr<X> p(new X);
        X * q = p.get();
        boost::shared_ptr<void const> pv(p);
        BOOST_TEST(pv? true: false);
        BOOST_TEST(!!pv);
        BOOST_TEST(pv.get() == q);
        BOOST_TEST(pv.use_count() == 1);
        BOOST_TEST(pv.unique());
        BOOST_TEST(X::instances == 1);

#if !defined(BOOST_MSVC) || (BOOST_MSVC >= 1300)
        BOOST_TEST(p.get() == 0);
#endif
    }

    BOOST_TEST(X::instances == 0);
    BOOST_TEST(Y::instances == 0);

    {
        std::auto_ptr<Y> p(new Y);
        Y * q = p.get();
        boost::shared_ptr<X> px(p);
        BOOST_TEST(px? true: false);
        BOOST_TEST(!!px);
        BOOST_TEST(px.get() == q);
        BOOST_TEST(px.use_count() == 1);
        BOOST_TEST(px.unique());
        BOOST_TEST(X::instances == 1);
        BOOST_TEST(Y::instances == 1);

#if !defined(BOOST_MSVC) || (BOOST_MSVC >= 1300)
        BOOST_TEST(p.get() == 0);
#endif
    }

    BOOST_TEST(X::instances == 0);
    BOOST_TEST(Y::instances == 0);

    {
        std::auto_ptr<Y> p(new Y);
        Y * q = p.get();
        boost::shared_ptr<X const> px(p);
        BOOST_TEST(px? true: false);
        BOOST_TEST(!!px);
        BOOST_TEST(px.get() == q);
        BOOST_TEST(px.use_count() == 1);
        BOOST_TEST(px.unique());
        BOOST_TEST(X::instances == 1);
        BOOST_TEST(Y::instances == 1);

#if !defined(BOOST_MSVC) || (BOOST_MSVC >= 1300)
        BOOST_TEST(p.get() == 0);
#endif
    }

    BOOST_TEST(X::instances == 0);
    BOOST_TEST(Y::instances == 0);
}

void test()
{
    default_constructor();
    pointer_constructor();
    deleter_constructor();
    copy_constructor();
    weak_ptr_constructor();
    auto_ptr_constructor();
}

} // namespace n_constructors

namespace n_assignment
{

class incomplete;

struct A
{
    int dummy;
};

struct X
{
    static long instances;

    X()
    {
        ++instances;
    }

    ~X()
    {
        --instances;
    }

private:

    X(X const &);
    X & operator= (X const &);
};

long X::instances = 0;

struct Y: public A, public X
{
    static long instances;

    Y()
    {
        ++instances;
    }

    ~Y()
    {
        --instances;
    }

private:

    Y(Y const &);
    Y & operator= (Y const &);
};

long Y::instances = 0;

void copy_assignment()
{
	{
		boost::shared_ptr<incomplete> p1;

		p1 = p1;

        BOOST_TEST(p1 == p1);
        BOOST_TEST(p1? false: true);
        BOOST_TEST(!p1);
        BOOST_TEST(p1.get() == 0);

		boost::shared_ptr<incomplete> p2;

		p1 = p2;

        BOOST_TEST(p1 == p2);
        BOOST_TEST(p1? false: true);
        BOOST_TEST(!p1);
        BOOST_TEST(p1.get() == 0);

		boost::shared_ptr<incomplete> p3(p1);

		p1 = p3;

        BOOST_TEST(p1 == p3);
        BOOST_TEST(p1? false: true);
        BOOST_TEST(!p1);
        BOOST_TEST(p1.get() == 0);
	}

	{
		boost::shared_ptr<void> p1;

		p1 = p1;

        BOOST_TEST(p1 == p1);
        BOOST_TEST(p1? false: true);
        BOOST_TEST(!p1);
        BOOST_TEST(p1.get() == 0);

		boost::shared_ptr<void> p2;

		p1 = p2;

        BOOST_TEST(p1 == p2);
        BOOST_TEST(p1? false: true);
        BOOST_TEST(!p1);
        BOOST_TEST(p1.get() == 0);

		boost::shared_ptr<void> p3(p1);

		p1 = p3;

        BOOST_TEST(p1 == p3);
        BOOST_TEST(p1? false: true);
        BOOST_TEST(!p1);
        BOOST_TEST(p1.get() == 0);

		boost::shared_ptr<void> p4(new int);
		BOOST_TEST(p4.use_count() == 1);

		p1 = p4;

        BOOST_TEST(p1 == p4);
        BOOST_TEST(!(p1 < p4 || p4 < p1));
		BOOST_TEST(p1.use_count() == 2);
		BOOST_TEST(p4.use_count() == 2);

		p1 = p3;

        BOOST_TEST(p1 == p3);
		BOOST_TEST(p4.use_count() == 1);
	}

	{
		boost::shared_ptr<X> p1;

		p1 = p1;

        BOOST_TEST(p1 == p1);
        BOOST_TEST(p1? false: true);
        BOOST_TEST(!p1);
        BOOST_TEST(p1.get() == 0);

		boost::shared_ptr<X> p2;

		p1 = p2;

        BOOST_TEST(p1 == p2);
        BOOST_TEST(p1? false: true);
        BOOST_TEST(!p1);
        BOOST_TEST(p1.get() == 0);

		boost::shared_ptr<X> p3(p1);

		p1 = p3;

        BOOST_TEST(p1 == p3);
        BOOST_TEST(p1? false: true);
        BOOST_TEST(!p1);
        BOOST_TEST(p1.get() == 0);

		BOOST_TEST(X::instances == 0);

		boost::shared_ptr<X> p4(new X);

		BOOST_TEST(X::instances == 1);

		p1 = p4;

		BOOST_TEST(X::instances == 1);

        BOOST_TEST(p1 == p4);
        BOOST_TEST(!(p1 < p4 || p4 < p1));

		BOOST_TEST(p1.use_count() == 2);

		p1 = p2;

        BOOST_TEST(p1 == p2);
		BOOST_TEST(X::instances == 1);

		p4 = p3;

        BOOST_TEST(p4 == p3);
		BOOST_TEST(X::instances == 0);
	}
}

void conversion_assignment()
{
	{
		boost::shared_ptr<void> p1;

		boost::shared_ptr<incomplete> p2;

		p1 = p2;

        BOOST_TEST(p1 == p2);
        BOOST_TEST(p1? false: true);
        BOOST_TEST(!p1);
        BOOST_TEST(p1.get() == 0);

		boost::shared_ptr<int> p4(new int);
		BOOST_TEST(p4.use_count() == 1);

		boost::shared_ptr<void> p5(p4);
		BOOST_TEST(p4.use_count() == 2);

		p1 = p4;

        BOOST_TEST(p1 == p4);
        BOOST_TEST(!(p1 < p5 || p5 < p1));
		BOOST_TEST(p1.use_count() == 3);
		BOOST_TEST(p4.use_count() == 3);

		p1 = p2;

        BOOST_TEST(p1 == p2);
		BOOST_TEST(p4.use_count() == 2);
	}

	{
		boost::shared_ptr<X> p1;

		boost::shared_ptr<Y> p2;

		p1 = p2;

        BOOST_TEST(p1 == p2);
        BOOST_TEST(p1? false: true);
        BOOST_TEST(!p1);
        BOOST_TEST(p1.get() == 0);

		BOOST_TEST(X::instances == 0);
		BOOST_TEST(Y::instances == 0);

		boost::shared_ptr<Y> p4(new Y);

		BOOST_TEST(X::instances == 1);
		BOOST_TEST(Y::instances == 1);
		BOOST_TEST(p4.use_count() == 1);

		boost::shared_ptr<X> p5(p4);
		BOOST_TEST(p4.use_count() == 2);

		p1 = p4;

		BOOST_TEST(X::instances == 1);
		BOOST_TEST(Y::instances == 1);

        BOOST_TEST(p1 == p4);
        BOOST_TEST(!(p1 < p5 || p5 < p1));

		BOOST_TEST(p1.use_count() == 3);
		BOOST_TEST(p4.use_count() == 3);

		p1 = p2;

        BOOST_TEST(p1 == p2);
		BOOST_TEST(X::instances == 1);
		BOOST_TEST(Y::instances == 1);
		BOOST_TEST(p4.use_count() == 2);

		p4 = p2;
		p5 = p2;

        BOOST_TEST(p4 == p2);
		BOOST_TEST(X::instances == 0);
		BOOST_TEST(Y::instances == 0);
	}
}

void auto_ptr_assignment()
{
	{
		boost::shared_ptr<int> p1;

		std::auto_ptr<int> p2;

		p1 = p2;
        BOOST_TEST(p1? false: true);
        BOOST_TEST(!p1);
        BOOST_TEST(p1.get() == 0);
		BOOST_TEST(p1.use_count() == 1);

		int * p = new int;
		std::auto_ptr<int> p3(p);

		p1 = p3;
		BOOST_TEST(p1.get() == p);
		BOOST_TEST(p1.use_count() == 1);

#if !defined(BOOST_MSVC) || (BOOST_MSVC >= 1300)
        BOOST_TEST(p3.get() == 0);
#endif

		p1 = p2;
        BOOST_TEST(p1? false: true);
        BOOST_TEST(!p1);
        BOOST_TEST(p1.get() == 0);
		BOOST_TEST(p1.use_count() == 1);
	}

	{
		boost::shared_ptr<void> p1;

		std::auto_ptr<int> p2;

		p1 = p2;
        BOOST_TEST(p1? false: true);
        BOOST_TEST(!p1);
        BOOST_TEST(p1.get() == 0);
		BOOST_TEST(p1.use_count() == 1);

		int * p = new int;
		std::auto_ptr<int> p3(p);

		p1 = p3;
		BOOST_TEST(p1.get() == p);
		BOOST_TEST(p1.use_count() == 1);

#if !defined(BOOST_MSVC) || (BOOST_MSVC >= 1300)
        BOOST_TEST(p3.get() == 0);
#endif

		p1 = p2;
        BOOST_TEST(p1? false: true);
        BOOST_TEST(!p1);
        BOOST_TEST(p1.get() == 0);
		BOOST_TEST(p1.use_count() == 1);
	}


	{
		boost::shared_ptr<X> p1;

		std::auto_ptr<Y> p2;

		p1 = p2;
        BOOST_TEST(p1? false: true);
        BOOST_TEST(!p1);
        BOOST_TEST(p1.get() == 0);
		BOOST_TEST(p1.use_count() == 1);
		BOOST_TEST(X::instances == 0);
		BOOST_TEST(Y::instances == 0);

		Y * p = new Y;
		std::auto_ptr<Y> p3(p);

		BOOST_TEST(X::instances == 1);
		BOOST_TEST(Y::instances == 1);

		p1 = p3;
		BOOST_TEST(p1.get() == p);
		BOOST_TEST(p1.use_count() == 1);
		BOOST_TEST(X::instances == 1);
		BOOST_TEST(Y::instances == 1);

#if !defined(BOOST_MSVC) || (BOOST_MSVC >= 1300)
        BOOST_TEST(p3.get() == 0);
#endif

		p1 = p2;
        BOOST_TEST(p1? false: true);
        BOOST_TEST(!p1);
        BOOST_TEST(p1.get() == 0);
		BOOST_TEST(p1.use_count() == 1);
		BOOST_TEST(X::instances == 0);
		BOOST_TEST(Y::instances == 0);
	}
}

void test()
{
	copy_assignment();
	conversion_assignment();
	auto_ptr_assignment();
}

} // namespace n_assignment

namespace n_reset
{

void plain_reset()
{
}

void pointer_reset()
{
}

void deleter_reset()
{
}

void test()
{
	plain_reset();
	pointer_reset();
	deleter_reset();
}

} // namespace n_reset

namespace n_access
{

struct X
{
};

void test()
{
    {
        boost::shared_ptr<X> px;
        BOOST_TEST(px.get() == 0);
        BOOST_TEST(px? false: true);
        BOOST_TEST(!px);

#if defined(BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP)
        using boost::get_pointer;
#endif

        BOOST_TEST(get_pointer(px) == px.get());
    }

    {
        boost::shared_ptr<X> px(static_cast<X*>(0));
        BOOST_TEST(px.get() == 0);
        BOOST_TEST(px? false: true);
        BOOST_TEST(!px);

#if defined(BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP)
        using boost::get_pointer;
#endif

        BOOST_TEST(get_pointer(px) == px.get());
    }

    {
        boost::shared_ptr<X> px(static_cast<X*>(0), boost::checked_deleter<X>());
        BOOST_TEST(px.get() == 0);
        BOOST_TEST(px? false: true);
        BOOST_TEST(!px);

#if defined(BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP)
        using boost::get_pointer;
#endif

        BOOST_TEST(get_pointer(px) == px.get());
    }

    {
        X * p = new X;
        boost::shared_ptr<X> px(p);
        BOOST_TEST(px.get() == p);
        BOOST_TEST(px? true: false);
        BOOST_TEST(!!px);
        BOOST_TEST(&*px == px.get());
        BOOST_TEST(px.operator ->() == px.get());

#if defined(BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP)
        using boost::get_pointer;
#endif

        BOOST_TEST(get_pointer(px) == px.get());
    }

    {
        X * p = new X;
        boost::shared_ptr<X> px(p, boost::checked_deleter<X>());
        BOOST_TEST(px.get() == p);
        BOOST_TEST(px? true: false);
        BOOST_TEST(!!px);
        BOOST_TEST(&*px == px.get());
        BOOST_TEST(px.operator ->() == px.get());

#if defined(BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP)
        using boost::get_pointer;
#endif

        BOOST_TEST(get_pointer(px) == px.get());
    }
}

} // namespace n_access

namespace n_use_count
{

struct X
{
};

void test()
{
    {
        boost::shared_ptr<X> px(static_cast<X*>(0));
        BOOST_TEST(px.use_count() == 1);
        BOOST_TEST(px.unique());

        boost::shared_ptr<X> px2(px);
        BOOST_TEST(px2.use_count() == 2);
        BOOST_TEST(!px2.unique());
        BOOST_TEST(px.use_count() == 2);
        BOOST_TEST(!px.unique());
    }

    {
        boost::shared_ptr<X> px(new X);
        BOOST_TEST(px.use_count() == 1);
        BOOST_TEST(px.unique());

        boost::shared_ptr<X> px2(px);
        BOOST_TEST(px2.use_count() == 2);
        BOOST_TEST(!px2.unique());
        BOOST_TEST(px.use_count() == 2);
        BOOST_TEST(!px.unique());
    }

    {
        boost::shared_ptr<X> px(new X, boost::checked_deleter<X>());
        BOOST_TEST(px.use_count() == 1);
        BOOST_TEST(px.unique());

        boost::shared_ptr<X> px2(px);
        BOOST_TEST(px2.use_count() == 2);
        BOOST_TEST(!px2.unique());
        BOOST_TEST(px.use_count() == 2);
        BOOST_TEST(!px.unique());
    }
}

} // namespace n_use_count

namespace n_swap
{

struct X
{
};

void test()
{
    {
        boost::shared_ptr<X> px;
        boost::shared_ptr<X> px2;

        px.swap(px2);

        BOOST_TEST(px.get() == 0);
        BOOST_TEST(px2.get() == 0);

        using std::swap;
        swap(px, px2);

        BOOST_TEST(px.get() == 0);
        BOOST_TEST(px2.get() == 0);
    }

    {
        X * p = new X;
        boost::shared_ptr<X> px;
        boost::shared_ptr<X> px2(p);
        boost::shared_ptr<X> px3(px2);

        px.swap(px2);

        BOOST_TEST(px.get() == p);
        BOOST_TEST(px.use_count() == 2);
        BOOST_TEST(px2.get() == 0);
        BOOST_TEST(px3.get() == p);
        BOOST_TEST(px3.use_count() == 2);

        using std::swap;
        swap(px, px2);

        BOOST_TEST(px.get() == 0);
        BOOST_TEST(px2.get() == p);
        BOOST_TEST(px2.use_count() == 2);
        BOOST_TEST(px3.get() == p);
        BOOST_TEST(px3.use_count() == 2);
    }

    {
        X * p1 = new X;
        X * p2 = new X;
        boost::shared_ptr<X> px(p1);
        boost::shared_ptr<X> px2(p2);
        boost::shared_ptr<X> px3(px2);

        px.swap(px2);

        BOOST_TEST(px.get() == p2);
        BOOST_TEST(px.use_count() == 2);
        BOOST_TEST(px2.get() == p1);
        BOOST_TEST(px2.use_count() == 1);
        BOOST_TEST(px3.get() == p2);
        BOOST_TEST(px3.use_count() == 2);

        using std::swap;
        swap(px, px2);

        BOOST_TEST(px.get() == p1);
        BOOST_TEST(px.use_count() == 1);
        BOOST_TEST(px2.get() == p2);
        BOOST_TEST(px2.use_count() == 2);
        BOOST_TEST(px3.get() == p2);
        BOOST_TEST(px3.use_count() == 2);
    }
}

} // namespace n_swap

namespace n_comparison
{

struct X
{
    int dummy;
};

struct Y
{
    int dummy2;
};

struct Z: public X, public Y
{
};

void test()
{
    {
        boost::shared_ptr<X> px;
        BOOST_TEST(px == px);
        BOOST_TEST(!(px != px));
        BOOST_TEST(!(px < px));

		boost::shared_ptr<X> px2;

        BOOST_TEST(px.get() == px2.get());
        BOOST_TEST(px == px2);
        BOOST_TEST(!(px != px2));
        BOOST_TEST(!(px < px2 && px2 < px));
    }

    {
        boost::shared_ptr<X> px;
        boost::shared_ptr<X> px2(px);

		BOOST_TEST(px2 == px2);
        BOOST_TEST(!(px2 != px2));
        BOOST_TEST(!(px2 < px2));

        BOOST_TEST(px.get() == px2.get());
        BOOST_TEST(px == px2);
        BOOST_TEST(!(px != px2));
        BOOST_TEST(!(px < px2 && px2 < px));
    }

    {
        boost::shared_ptr<X> px;
        boost::shared_ptr<X> px2(new X);

		BOOST_TEST(px2 == px2);
        BOOST_TEST(!(px2 != px2));
        BOOST_TEST(!(px2 < px2));

        BOOST_TEST(px.get() != px2.get());
        BOOST_TEST(px != px2);
        BOOST_TEST(!(px == px2));
        BOOST_TEST(px < px2 || px2 < px);
        BOOST_TEST(!(px < px2 && px2 < px));
    }

    {
        boost::shared_ptr<X> px(new X);
        boost::shared_ptr<X> px2(new X);

        BOOST_TEST(px.get() != px2.get());
        BOOST_TEST(px != px2);
        BOOST_TEST(!(px == px2));
        BOOST_TEST(px < px2 || px2 < px);
        BOOST_TEST(!(px < px2 && px2 < px));
    }

    {
        boost::shared_ptr<X> px(new X);
        boost::shared_ptr<X> px2(px);

		BOOST_TEST(px2 == px2);
        BOOST_TEST(!(px2 != px2));
        BOOST_TEST(!(px2 < px2));

        BOOST_TEST(px.get() == px2.get());
        BOOST_TEST(px == px2);
        BOOST_TEST(!(px != px2));
        BOOST_TEST(!(px < px2 || px2 < px));
    }

    {
        boost::shared_ptr<X> px(new X);
        boost::shared_ptr<Y> py(new Y);
        boost::shared_ptr<Z> pz(new Z);

        BOOST_TEST(px.get() != pz.get());
        BOOST_TEST(px != pz);
        BOOST_TEST(!(px == pz));

        BOOST_TEST(py.get() != pz.get());
        BOOST_TEST(py != pz);
        BOOST_TEST(!(py == pz));

        boost::shared_ptr<void> pvx(px);

		BOOST_TEST(pvx == pvx);
        BOOST_TEST(!(pvx != pvx));
        BOOST_TEST(!(pvx < pvx));

        boost::shared_ptr<void> pvy(py);
        boost::shared_ptr<void> pvz(pz);

        BOOST_TEST(pvx < pvy || pvy < pvx);
        BOOST_TEST(pvx < pvz || pvz < pvx);
        BOOST_TEST(pvy < pvz || pvz < pvy);

		BOOST_TEST(!(pvx < pvy && pvy < pvx));
		BOOST_TEST(!(pvx < pvz && pvz < pvx));
		BOOST_TEST(!(pvy < pvz && pvz < pvy));
    }

    {
        boost::shared_ptr<Z> pz(new Z);
        boost::shared_ptr<X> px(pz);

		BOOST_TEST(px == px);
        BOOST_TEST(!(px != px));
        BOOST_TEST(!(px < px));

        boost::shared_ptr<Y> py(pz);

        BOOST_TEST(px.get() == pz.get());
        BOOST_TEST(px == pz);
        BOOST_TEST(!(px != pz));

        BOOST_TEST(py.get() == pz.get());
        BOOST_TEST(py == pz);
        BOOST_TEST(!(py != pz));

        boost::shared_ptr<void> pvx(px);
        boost::shared_ptr<void> pvy(py);
        boost::shared_ptr<void> pvz(pz);

        // pvx and pvy aren't equal...
        BOOST_TEST(pvx.get() != pvy.get());
        BOOST_TEST(pvx != pvy);
        BOOST_TEST(!(pvx == pvy));

        // ... but they share ownership ...
        BOOST_TEST(!(pvx < pvy || pvy < pvx));

        // ... with pvz
        BOOST_TEST(!(pvx < pvz || pvz < pvx));
        BOOST_TEST(!(pvy < pvz || pvz < pvy));
    }
}

} // namespace n_comparison

namespace n_static_cast
{

struct X
{
};

struct Y: public X
{
};

void test()
{
    {
        boost::shared_ptr<void> pv;

        boost::shared_ptr<int> pi = boost::static_pointer_cast<int>(pv);
        BOOST_TEST(pi.get() == 0);

        boost::shared_ptr<X> px = boost::static_pointer_cast<X>(pv);
        BOOST_TEST(px.get() == 0);
    }

    {
        boost::shared_ptr<int> pi(new int);
        boost::shared_ptr<void> pv(pi);

        boost::shared_ptr<int> pi2 = boost::static_pointer_cast<int>(pv);
        BOOST_TEST(pi.get() == pi2.get());
        BOOST_TEST(!(pi < pi2 || pi2 < pi));
        BOOST_TEST(pi.use_count() == 3);
        BOOST_TEST(pv.use_count() == 3);
        BOOST_TEST(pi2.use_count() == 3);
    }

    {
        boost::shared_ptr<X> px(new X);
        boost::shared_ptr<void> pv(px);

        boost::shared_ptr<X> px2 = boost::static_pointer_cast<X>(pv);
        BOOST_TEST(px.get() == px2.get());
        BOOST_TEST(!(px < px2 || px2 < px));
        BOOST_TEST(px.use_count() == 3);
        BOOST_TEST(pv.use_count() == 3);
        BOOST_TEST(px2.use_count() == 3);
    }

    {
        boost::shared_ptr<X> px(new Y);

        boost::shared_ptr<Y> py = boost::static_pointer_cast<Y>(px);
        BOOST_TEST(px.get() == py.get());
        BOOST_TEST(px.use_count() == 2);
        BOOST_TEST(py.use_count() == 2);

        boost::shared_ptr<X> px2(py);
        BOOST_TEST(!(px < px2 || px2 < px));
    }
}

} // namespace n_static_cast

namespace n_dynamic_cast
{

struct V
{
    virtual ~V() {}
};

struct W: public V
{
};

void test()
{
    {
        boost::shared_ptr<V> pv;
        boost::shared_ptr<W> pw = boost::dynamic_pointer_cast<W>(pv);
        BOOST_TEST(pw.get() == 0);
    }

    {
        boost::shared_ptr<V> pv(static_cast<V*>(0));

        boost::shared_ptr<W> pw = boost::dynamic_pointer_cast<W>(pv);
        BOOST_TEST(pw.get() == 0);

        boost::shared_ptr<V> pv2(pw);
        BOOST_TEST(pv < pv2 || pv2 < pv);
    }

    {
        boost::shared_ptr<V> pv(static_cast<W*>(0));

        boost::shared_ptr<W> pw = boost::dynamic_pointer_cast<W>(pv);
        BOOST_TEST(pw.get() == 0);

        boost::shared_ptr<V> pv2(pw);
        BOOST_TEST(pv < pv2 || pv2 < pv);
    }

    {
        boost::shared_ptr<V> pv(new V);

        boost::shared_ptr<W> pw = boost::dynamic_pointer_cast<W>(pv);
        BOOST_TEST(pw.get() == 0);

        boost::shared_ptr<V> pv2(pw);
        BOOST_TEST(pv < pv2 || pv2 < pv);
    }

    {
        boost::shared_ptr<V> pv(new W);

        boost::shared_ptr<W> pw = boost::dynamic_pointer_cast<W>(pv);
        BOOST_TEST(pw.get() == pv.get());
        BOOST_TEST(pv.use_count() == 2);
        BOOST_TEST(pw.use_count() == 2);

        boost::shared_ptr<V> pv2(pw);
        BOOST_TEST(!(pv < pv2 || pv2 < pv));
    }
}

} // namespace n_dynamic_cast

namespace n_map
{

struct X
{
};

void test()
{
    std::vector< boost::shared_ptr<int> > vi;

    {
        boost::shared_ptr<int> pi1(new int);
        boost::shared_ptr<int> pi2(new int);
        boost::shared_ptr<int> pi3(new int);

        vi.push_back(pi1);
        vi.push_back(pi1);
        vi.push_back(pi1);
        vi.push_back(pi2);
        vi.push_back(pi1);
        vi.push_back(pi2);
        vi.push_back(pi1);
        vi.push_back(pi3);
        vi.push_back(pi3);
        vi.push_back(pi2);
        vi.push_back(pi1);
    }

    std::vector< boost::shared_ptr<X> > vx;

    {
        boost::shared_ptr<X> px1(new X);
        boost::shared_ptr<X> px2(new X);
        boost::shared_ptr<X> px3(new X);

        vx.push_back(px2);
        vx.push_back(px2);
        vx.push_back(px1);
        vx.push_back(px2);
        vx.push_back(px1);
        vx.push_back(px1);
        vx.push_back(px1);
        vx.push_back(px2);
        vx.push_back(px1);
        vx.push_back(px3);
        vx.push_back(px2);
    }

    std::map< boost::shared_ptr<void>, long > m;

    {
        for(std::vector< boost::shared_ptr<int> >::iterator i = vi.begin(); i != vi.end(); ++i)
        {
            ++m[*i];
        }
    }

    {
        for(std::vector< boost::shared_ptr<X> >::iterator i = vx.begin(); i != vx.end(); ++i)
        {
            ++m[*i];
        }
    }

    {
        for(std::map< boost::shared_ptr<void>, long >::iterator i = m.begin(); i != m.end(); ++i)
        {
            BOOST_TEST(i->first.use_count() == i->second + 1);
        }
    }
}

} // namespace n_map

namespace n_transitive
{

struct X
{
    X(): next() {}
    boost::shared_ptr<X> next;
};

void test()
{
    boost::shared_ptr<X> p(new X);
    p->next = boost::shared_ptr<X>(new X);
    BOOST_TEST(!p->next->next);
    p = p->next;
    BOOST_TEST(!p->next);
}

} // namespace n_transitive

namespace n_report_1
{

class foo
{ 
public: 

    foo(): m_self(this)
    {
    } 

    void suicide()
    {
        m_self.reset();
    }

private:

    boost::shared_ptr<foo> m_self;
}; 

void test()
{
    foo * foo_ptr = new foo;
    foo_ptr->suicide();
} 

} // namespace n_report_1

// Test case by Per Kristensen
namespace n_report_2
{

class foo
{
public:

    void setWeak(boost::shared_ptr<foo> s)
    {
        w = s;
    }

private:

    boost::weak_ptr<foo> w;
};
 
class deleter
{
public:

    deleter(): lock(0)
    {
    }

    ~deleter()
    {
        BOOST_TEST(lock == 0);
    }

    void operator() (foo * p)
    {
        ++lock;
        delete p;
        --lock;
    }
 
private:

    int lock;
};
 
void test()
{
    boost::shared_ptr<foo> s(new foo, deleter());
    s->setWeak(s);
    s.reset();
}

} // namespace n_report_2

namespace n_old
{

int cnt = 0;

struct X
{
    X()
    {
        ++cnt;
    }

    ~X() // virtual destructor deliberately omitted
    {
        --cnt;
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
    }

    ~Y()
    {
        --cnt;
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
    return &cnt;
}

void release_object(int * p)
{
    BOOST_TEST(p == &cnt);
    --cnt;
}

template<class T> void test_is_X(boost::shared_ptr<T> const & p)
{
    BOOST_TEST(p->id() == 1);
    BOOST_TEST((*p).id() == 1);
}

template<class T> void test_is_X(boost::weak_ptr<T> const & p)
{
    BOOST_TEST(p.get() != 0);
    BOOST_TEST(p.get()->id() == 1);
}

template<class T> void test_is_Y(boost::shared_ptr<T> const & p)
{
    BOOST_TEST(p->id() == 2);
    BOOST_TEST((*p).id() == 2);
}

template<class T> void test_is_Y(boost::weak_ptr<T> const & p)
{
    boost::shared_ptr<T> q = boost::make_shared(p);
    BOOST_TEST(q.get() != 0);
    BOOST_TEST(q->id() == 2);
}

template<class T> void test_eq(T const & a, T const & b)
{
    BOOST_TEST(a == b);
    BOOST_TEST(!(a != b));
    BOOST_TEST(!(a < b));
    BOOST_TEST(!(b < a));
}

template<class T> void test_ne(T const & a, T const & b)
{
    BOOST_TEST(!(a == b));
    BOOST_TEST(a != b);
    BOOST_TEST(a < b || b < a);
    BOOST_TEST(!(a < b && b < a));
}

void test_shared(boost::weak_ptr<void> const & a, boost::weak_ptr<void> const & b)
{
    BOOST_TEST(!(a < b));
    BOOST_TEST(!(b < a));
}

void test_nonshared(boost::weak_ptr<void> const & a, boost::weak_ptr<void> const & b)
{
    BOOST_TEST(a < b || b < a);
    BOOST_TEST(!(a < b && b < a));
}

template<class T, class U> void test_eq2(T const & a, U const & b)
{
    BOOST_TEST(a == b);
    BOOST_TEST(!(a != b));
}

template<class T, class U> void test_ne2(T const & a, U const & b)
{
    BOOST_TEST(!(a == b));
    BOOST_TEST(a != b);
}

template<class T> void test_is_zero(boost::shared_ptr<T> const & p)
{
    BOOST_TEST(!p);
    BOOST_TEST(p.get() == 0);
}

template<class T> void test_is_nonzero(boost::shared_ptr<T> const & p)
{
    // p? true: false is used to test p in a boolean context.
    // BOOST_TEST(p) is not guaranteed to test the conversion,
    // as the macro might test !!p instead.
    BOOST_TEST(p? true: false);
    BOOST_TEST(p.get() != 0);
}

void test()
{
    using namespace boost;

    {
        shared_ptr<X> p(new Y);
        shared_ptr<X> p2(new X);

        test_is_nonzero(p);
        test_is_nonzero(p2);
        test_is_Y(p);
        test_is_X(p2);
        test_ne(p, p2);

        {
            shared_ptr<X> q(p);
            test_eq(p, q);
        }

        shared_ptr<Y> p3 = dynamic_pointer_cast<Y>(p);
        shared_ptr<Y> p4 = dynamic_pointer_cast<Y>(p2);

        test_is_nonzero(p3);
        test_is_zero(p4);

        BOOST_TEST(p.use_count() == 2);
        BOOST_TEST(p2.use_count() == 1);
        BOOST_TEST(p3.use_count() == 2);

        test_is_Y(p3);
        test_eq2(p, p3);
        test_ne2(p2, p4);

        shared_ptr<void> p5(p);

        test_is_nonzero(p5);
        test_eq2(p, p5);

        weak_ptr<X> wp1(p2);

        BOOST_TEST(!wp1.expired());
        BOOST_TEST(wp1.use_count() != 0);

        p.reset();
        p2.reset();
        p3.reset();
        p4.reset();

        test_is_zero(p);
        test_is_zero(p2);
        test_is_zero(p3);
        test_is_zero(p4);

        BOOST_TEST(p5.use_count() == 1);

        BOOST_TEST(wp1.expired());
        BOOST_TEST(wp1.use_count() == 0);

        try
        {
            shared_ptr<X> sp1(wp1);
            BOOST_ERROR("shared_ptr<X> sp1(wp1) failed to throw");
        }
        catch(boost::bad_weak_ptr const &)
        {
        }

        test_is_zero(boost::make_shared(wp1));

        weak_ptr<X> wp2 = static_pointer_cast<X>(p5);

        BOOST_TEST(wp2.use_count() == 1);
        test_is_Y(wp2);
        test_nonshared(wp1, wp2);

        // Scoped to not affect the subsequent use_count() tests.
        {
            shared_ptr<X> sp2(wp2);
            test_is_nonzero(boost::make_shared(wp2));
        }

        weak_ptr<Y> wp3 = dynamic_pointer_cast<Y>(boost::make_shared(wp2));

        BOOST_TEST(wp3.use_count() == 1);
        test_shared(wp2, wp3);

        weak_ptr<X> wp4(wp3);

        BOOST_TEST(wp4.use_count() == 1);
        test_shared(wp2, wp4);

        wp1 = p2;
        test_is_zero(boost::make_shared(wp1));

        wp1 = p4;
        wp1 = wp3;
        wp1 = wp2;

        BOOST_TEST(wp1.use_count() == 1);
        test_shared(wp1, wp2);

        weak_ptr<X> wp5;

        bool b1 = wp1 < wp5;
        bool b2 = wp5 < wp1;

        p5.reset();

        BOOST_TEST(wp1.use_count() == 0);
        BOOST_TEST(wp2.use_count() == 0);
        BOOST_TEST(wp3.use_count() == 0);

        // Test operator< stability for std::set< weak_ptr<> >
        // Thanks to Joe Gottman for pointing this out

        BOOST_TEST(b1 == (wp1 < wp5));
        BOOST_TEST(b2 == (wp5 < wp1));

        {
            // note that both get_object and release_object deal with int*
            shared_ptr<void> p6(get_object(), release_object);
        }
    }

    BOOST_TEST(cnt == 0);
}

} // namespace n_old

namespace n_spt_incomplete
{

class file;

boost::shared_ptr<file> fopen(char const * name, char const * mode);
void fread(boost::shared_ptr<file> f, void * data, long size);

int file_instances = 0;

void test()
{
    BOOST_TEST(file_instances == 0);

    {
        boost::shared_ptr<file> pf = fopen("name", "mode");
        BOOST_TEST(file_instances == 1);
        fread(pf, 0, 17041);
    }

    BOOST_TEST(file_instances == 0);
}

} // namespace n_spt_incomplete

namespace n_spt_pimpl
{

class file
{
private:

    class impl;
    boost::shared_ptr<impl> pimpl_;

public:

    file(char const * name, char const * mode);

    // compiler generated members are fine and useful

    void read(void * data, long size);

    long total_size() const;
};

int file_instances = 0;

void test()
{
    BOOST_TEST(file_instances == 0);

    {
        file f("name", "mode");
        BOOST_TEST(file_instances == 1);
        f.read(0, 152);

        file f2(f);
        BOOST_TEST(file_instances == 1);
        f2.read(0, 894);

        BOOST_TEST(f.total_size() == 152+894);

        {
            file f3("name2", "mode2");
            BOOST_TEST(file_instances == 2);
        }

        BOOST_TEST(file_instances == 1);
    }

    BOOST_TEST(file_instances == 0);
}

} // namespace n_spt_pimpl

namespace n_spt_abstract
{

class X
{
public:

    virtual void f(int) = 0;
    virtual int g() = 0;

protected:

    ~X() {}
};

boost::shared_ptr<X> createX();

int X_instances = 0;

void test()
{
    BOOST_TEST(X_instances == 0);

    {
        boost::shared_ptr<X> px = createX();

        BOOST_TEST(X_instances == 1);

        px->f(18);
        px->f(152);

        BOOST_TEST(px->g() == 170);
    }

    BOOST_TEST(X_instances == 0);
}

} // namespace n_spt_abstract

namespace n_spt_preventing_delete
{

int X_instances = 0;

class X
{
private:

    X()
    {
        ++X_instances;
    }

    ~X()
    {
        --X_instances;
    }

    class deleter;
    friend class deleter;

    class deleter
    {
    public:

        void operator()(X * p) { delete p; }
    };

public:

    static boost::shared_ptr<X> create()
    {
        boost::shared_ptr<X> px(new X, X::deleter());
        return px;
    }
};

void test()
{
    BOOST_TEST(X_instances == 0);

    {
        boost::shared_ptr<X> px = X::create();
        BOOST_TEST(X_instances == 1);
    }

    BOOST_TEST(X_instances == 0);
}

} // namespace n_spt_preventing_delete

namespace n_spt_array
{

int X_instances = 0;

struct X
{
    X()
    {
        ++X_instances;
    }

    ~X()
    {
        --X_instances;
    }
};

void test()
{
    BOOST_TEST(X_instances == 0);

    {
        boost::shared_ptr<X> px(new X[4], boost::checked_array_deleter<X>());
        BOOST_TEST(X_instances == 4);
    }

    BOOST_TEST(X_instances == 0);
}

} // namespace n_spt_array

namespace n_spt_static
{

class X
{
public:

	X()
	{
	}

private:

    void operator delete(void *);
};

struct null_deleter
{
    void operator()(void const *) const
    {
    }
};

static X x;

void test()
{
    boost::shared_ptr<X> px(&x, null_deleter());
}

} // namespace n_spt_static

namespace n_spt_intrusive
{

void test()
{
}

} // namespace n_spt_intrusive

namespace n_spt_another_sp
{

void test()
{
}

} // namespace n_spt_another_sp

namespace n_spt_shared_from_this
{

class X
{
public:

    virtual void f() = 0;

protected:

    ~X() {}
};

class Y
{
public:

    virtual boost::shared_ptr<X> getX() = 0;

protected:

    ~Y() {}
};

class impl: public X, public Y
{
private:

    boost::weak_ptr<impl> weak_this;

    impl(impl const &);
    impl & operator=(impl const &);

    impl() {}

public:

    static boost::shared_ptr<impl> create()
    {
        boost::shared_ptr<impl> pi(new impl);
        pi->weak_this = pi;
        return pi;
    }

    virtual void f() {}

    virtual boost::shared_ptr<X> getX()
    {
        boost::shared_ptr<X> px = boost::make_shared(weak_this);
        return px;
    }
};

void test()
{
    boost::shared_ptr<Y> py = impl::create();
    BOOST_TEST(py.get() != 0);
    BOOST_TEST(py.use_count() == 1);

    boost::shared_ptr<X> px = py->getX();
    BOOST_TEST(px.get() != 0);
    BOOST_TEST(py.use_count() == 2);

    boost::shared_ptr<Y> py2 = boost::dynamic_pointer_cast<Y>(px);
    BOOST_TEST(py.get() == py2.get());
    BOOST_TEST(!(py < py2 || py2 < py));
    BOOST_TEST(py.use_count() == 3);
}

} // namespace n_spt_shared_from_this

namespace n_spt_wrap
{

void test()
{
}

} // namespace n_spt_wrap

int main()
{
    n_element_type::test();
    n_constructors::test();
    n_assignment::test();
    n_reset::test();
    n_access::test();
    n_use_count::test();
    n_swap::test();
    n_comparison::test();
    n_static_cast::test();
    n_dynamic_cast::test();

    n_map::test();

    n_transitive::test();
    n_report_1::test();
    n_report_2::test();

    n_old::test();

    n_spt_incomplete::test();
    n_spt_pimpl::test();
    n_spt_abstract::test();
    n_spt_preventing_delete::test();
    n_spt_array::test();
    n_spt_static::test();
    n_spt_intrusive::test();
    n_spt_another_sp::test();
    n_spt_shared_from_this::test();
//  n_spt_post_constructors::test();
    n_spt_wrap::test();

    return boost::report_errors();
}

namespace n_spt_incomplete
{

class file
{
public:

    file(): fread_called(false)
    {
        ++file_instances;
    }

    ~file()
    {
        BOOST_TEST(fread_called);
        --file_instances;
    }

    bool fread_called;
};

boost::shared_ptr<file> fopen(char const *, char const *)
{
    boost::shared_ptr<file> pf(new file);
    return pf;
}

void fread(boost::shared_ptr<file> pf, void *, long)
{
    pf->fread_called = true;
}

} // namespace n_spt_incomplete

namespace n_spt_pimpl
{

class file::impl
{
private:

    impl(impl const &);
    impl & operator=(impl const &);

    long total_size_;

public:

    impl(char const *, char const *): total_size_(0)
    {
        ++file_instances;
    }

    ~impl()
    {
        --file_instances;
    }

    void read(void *, long size)
    {
        total_size_ += size;
    }

    long total_size() const
    {
        return total_size_;
    }
};

file::file(char const * name, char const * mode): pimpl_(new impl(name, mode))
{
}

void file::read(void * data, long size)
{
    pimpl_->read(data, size);
}

long file::total_size() const
{
    return pimpl_->total_size();
}

} // namespace n_spt_pimpl

namespace n_spt_abstract
{

class X_impl: public X
{
private:

    X_impl(X_impl const &);
    X_impl & operator=(X_impl const &);

    int n_;

public:

    X_impl(): n_(0)
    {
        ++X_instances;
    }

    ~X_impl()
    {
        --X_instances;
    }

    virtual void f(int n)
    {
        n_ += n;
    }

    virtual int g()
    {
        return n_;
    }
};

boost::shared_ptr<X> createX()
{
    boost::shared_ptr<X> px(new X_impl);
    return px;
}

} // namespace n_spt_abstract
