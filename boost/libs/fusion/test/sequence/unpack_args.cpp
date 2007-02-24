//
//  Copyright (c) 2006 João Abecasis
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/fusion/sequence/utility/unpack_args.hpp>

#include <boost/fusion/sequence/container/vector.hpp>
#include <boost/fusion/sequence/container/list.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/mpl/int.hpp>
#include <boost/noncopyable.hpp>
#include <boost/detail/lightweight_test.hpp>

namespace fusion = boost::fusion;

////////////////////////////////////////////////////////////////////////////////
//
// Helper stuff
//

struct object {};
struct nc_object : boost::noncopyable {};

template <class T>
inline T const & const_(T const & t)
{
    return t;
}

////////////////////////////////////////////////////////////////////////////////
//
// Test functoids
//

// polymorphic functors
struct foo
{
    typedef int result_type;

    int operator()()       { return 0; }
    int operator()() const { return 1; }

    int operator()(int i)       { return 2 + i; }
    int operator()(int i) const { return 3 + i; }

    int operator()(int i, object &)             { return 4 + i; }
    int operator()(int i, object &) const       { return 5 + i; }
    int operator()(int i, object const &)       { return 6 + i; }
    int operator()(int i, object const &) const { return 7 + i; }

    int operator()(int i, object &, nc_object &)       { return 10 + i; }
    int operator()(int i, object &, nc_object &) const { return 11 + i; }
};

struct nc_foo
    : boost::noncopyable
{
    typedef int result_type;

    int operator()()       { return 0; }
    int operator()() const { return 1; }

    int operator()(int i)       { return 2 + i; }
    int operator()(int i) const { return 3 + i; }
};

// nullary function
int bar() { return 20; }

// unary function
int square(int i) { return i * i; }

// binary functions
int baz1(int i, object &) { return 30 + i; }
int baz2(int i, object const &) { return 70 + i; }

// cv-qualified unary function pointers
typedef int (*                   func_ptr)(int);
typedef int (* const           c_func_ptr)(int);
typedef int (* volatile        v_func_ptr)(int);
typedef int (* const volatile cv_func_ptr)(int);

   func_ptr func_ptr1 = &square;
 c_func_ptr func_ptr2 = &square;
 v_func_ptr func_ptr3 = &square;
cv_func_ptr func_ptr4 = &square;

////////////////////////////////////////////////////////////////////////////////
//
//  Test data
//

typedef int         element1_type;
typedef object      element2_type;
typedef nc_object & element3_type;

int         element1 = 100;
object      element2 = object();
nc_object   element3;

////////////////////////////////////////////////////////////////////////////////
//
//  Tests (by sequence size)
//

template <class Sequence>
void test_sequence_n(Sequence & seq, boost::mpl::int_<0>)
{
    {
        foo f;

        BOOST_TEST(       f () == fusion::unpack_args(       f ,        seq ));
        BOOST_TEST(const_(f)() == fusion::unpack_args(const_(f),        seq ));
        BOOST_TEST(       f () == fusion::unpack_args(       f , const_(seq)));
        BOOST_TEST(const_(f)() == fusion::unpack_args(const_(f), const_(seq)));
    }

    {
        nc_foo nc_f;

        BOOST_TEST(       nc_f () == fusion::unpack_args(       nc_f ,        seq ));
        BOOST_TEST(const_(nc_f)() == fusion::unpack_args(const_(nc_f),        seq ));
        BOOST_TEST(       nc_f () == fusion::unpack_args(       nc_f , const_(seq)));
        BOOST_TEST(const_(nc_f)() == fusion::unpack_args(const_(nc_f), const_(seq)));
    }

    BOOST_TEST(bar() == fusion::unpack_args(bar, seq));
}

template <class Sequence>
void test_sequence_n(Sequence & seq, boost::mpl::int_<1>)
{
    {
        foo f;

        BOOST_TEST(       f (element1) == fusion::unpack_args(       f ,        seq ));
        BOOST_TEST(const_(f)(element1) == fusion::unpack_args(const_(f),        seq ));
        BOOST_TEST(       f (element1) == fusion::unpack_args(       f , const_(seq)));
        BOOST_TEST(const_(f)(element1) == fusion::unpack_args(const_(f), const_(seq)));
    }

    {
        nc_foo nc_f;

        BOOST_TEST(       nc_f (element1) == fusion::unpack_args(       nc_f ,        seq ));
        BOOST_TEST(const_(nc_f)(element1) == fusion::unpack_args(const_(nc_f),        seq ));
        BOOST_TEST(       nc_f (element1) == fusion::unpack_args(       nc_f , const_(seq)));
        BOOST_TEST(const_(nc_f)(element1) == fusion::unpack_args(const_(nc_f), const_(seq)));
    }

    BOOST_TEST(square(element1) == fusion::unpack_args(square, seq));

    BOOST_TEST(func_ptr1(element1) == fusion::unpack_args(func_ptr1, seq));
    BOOST_TEST(func_ptr2(element1) == fusion::unpack_args(func_ptr2, seq));
    BOOST_TEST(func_ptr3(element1) == fusion::unpack_args(func_ptr3, seq));
    BOOST_TEST(func_ptr4(element1) == fusion::unpack_args(func_ptr4, seq));
}

template <class Sequence>
void test_sequence_n(Sequence & seq, boost::mpl::int_<2>)
{
    {
        foo f;

        BOOST_TEST(       f (element1, element2) == fusion::unpack_args(       f , seq));
        BOOST_TEST(const_(f)(element1, element2) == fusion::unpack_args(const_(f), seq));
        
        BOOST_TEST(       f (element1, const_(element2)) == fusion::unpack_args(       f , const_(seq)));
        BOOST_TEST(const_(f)(element1, const_(element2)) == fusion::unpack_args(const_(f), const_(seq)));
    }

    BOOST_TEST(baz1(element1, element2) == fusion::unpack_args(baz1, seq));
    BOOST_TEST(baz2(element1, element2) == fusion::unpack_args(baz2, seq));
}

template <class Sequence>
void test_sequence_n(Sequence & seq, boost::mpl::int_<3>)
{
    foo f;

    BOOST_TEST(       f (element1, element2, element3) == fusion::unpack_args(       f , seq));
    BOOST_TEST(const_(f)(element1, element2, element3) == fusion::unpack_args(const_(f), seq));
}

////////////////////////////////////////////////////////////////////////////////
template <class Sequence>
void test_sequence(Sequence & seq)
{
    test_sequence_n(seq, fusion::size(seq));
}

////////////////////////////////////////////////////////////////////////////////
int main()
{
    typedef fusion::vector<> vector0;
    typedef fusion::vector<element1_type> vector1;
    typedef fusion::vector<element1_type, element2_type> vector2;
    typedef fusion::vector<element1_type, element2_type, element3_type> vector3;

    vector0 v0;
    vector1 v1(element1);
    vector2 v2(element1, element2);
    vector3 v3(element1, element2, element3);

    test_sequence(v0);
    test_sequence(v1);
    test_sequence(v2);
    test_sequence(v3);

    typedef fusion::list<> list0;
    typedef fusion::list<element1_type> list1;
    typedef fusion::list<element1_type, element2_type> list2;
    typedef fusion::list<element1_type, element2_type, element3_type> list3;

    list0 l0;
    list1 l1(element1);
    list2 l2(element1, element2);
    list3 l3(element1, element2, element3);

    test_sequence(l0);
    test_sequence(l1);
    test_sequence(l2);
    test_sequence(l3);
    return boost::report_errors();
}
