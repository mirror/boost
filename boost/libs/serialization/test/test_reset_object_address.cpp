/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// test_reset_object_address.cpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <sstream>
#include <cassert>
#include <cstdlib> // for rand()
#include <cstddef> // size_t

#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{
    using ::rand; 
    using ::size_t;
}
#endif

#include <boost/test/test_tools.hpp>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <boost/serialization/access.hpp>


// Someday, maybe all tests will be converted to the unit test framework.
// but for now use the text execution monitor to be consistent with all
// the other tests.

// simple test of untracked value
#include "A.hpp"

void test1(){
    std::stringstream ss;
    const A a;
    {
        boost::archive::text_oarchive oa(ss);
        oa << a;
    }
    A a1;
    {
        boost::archive::text_iarchive ia(ss);
        // load to temporary
        A a2;
        ia >> a2;
        BOOST_CHECK_EQUAL(a, a2);
        // move to final destination
        a1 = a2;
        ia.reset_object_address(& a1, & a2);
    }
    BOOST_CHECK_EQUAL(a, a1);
}

// simple test of tracked value
class B {
    friend class boost::serialization::access;
    int m_i;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int file_version){
        ar & m_i;
    }
public:
    bool operator==(const B & rhs) const {
        return m_i == rhs.m_i;
    }
    B() :
        m_i(std::rand())
    {}
};

BOOST_TEST_DONT_PRINT_LOG_VALUE( B )

void test2(){
    std::stringstream ss;
    B const b;
    B const * const b_ptr = & b;
    BOOST_CHECK_EQUAL(& b, b_ptr);
    {
        boost::archive::text_oarchive oa(ss);
        oa << b;
        oa << b_ptr;
    }
    B b1;
    B * b1_ptr;
    {
        boost::archive::text_iarchive ia(ss);
        // load to temporary
        B b2;
        ia >> b2;
        BOOST_CHECK_EQUAL(b, b2);
        // move to final destination
        b1 = b2;
        ia.reset_object_address(& b1, & b2);
        ia >> b1_ptr;
    }
    BOOST_CHECK_EQUAL(b, b1);
    BOOST_CHECK_EQUAL(& b1, b1_ptr);
}

// check that nested member values are properly moved
class D {
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int file_version){
        ar & m_b;
    }
public:
    B m_b;
    bool operator==(const D & rhs) const {
        return m_b == rhs.m_b;
    }
};

BOOST_TEST_DONT_PRINT_LOG_VALUE( D )

void test3(){
    std::stringstream ss;
    D const d;
    B const * const b_ptr = & d.m_b;
    {
        boost::archive::text_oarchive oa(ss);
        oa << d;
        oa << b_ptr;
    }
    D d1;
    B * b1_ptr;
    {
        boost::archive::text_iarchive ia(ss);
        D d2;
        ia >> d2;
        d1 = d2;
        ia.reset_object_address(& d1, & d2);
        ia >> b1_ptr;
    }
    BOOST_CHECK_EQUAL(d, d1);
    BOOST_CHECK_EQUAL(* b_ptr, * b1_ptr);
}

// check that data pointed to by pointer members is NOT moved
class E {
    int m_i;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int file_version){
        ar & m_i;
    }
public:
    bool operator==(const E &rhs) const {
        return m_i == rhs.m_i;
    }
    E() :
        m_i(std::rand())
    {}
    E(const E & rhs) :
        m_i(rhs.m_i)
    {}
};
BOOST_TEST_DONT_PRINT_LOG_VALUE( E )

// check that moves don't move stuff pointed too
class F {
    friend class boost::serialization::access;
    E * m_eptr;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int file_version){
        ar & m_eptr;
    }
public:
    bool operator==(const F &rhs) const {
        return *m_eptr == *rhs.m_eptr;
    }
    F & operator=(const F & rhs) {
        * m_eptr = * rhs.m_eptr;
        return *this;
    }
    F(){
        m_eptr = new E;
    }
    F(const F & rhs){
        *this = rhs;
    }
    ~F(){
        delete m_eptr;
    }
};

BOOST_TEST_DONT_PRINT_LOG_VALUE( F )

void test4(){
    std::stringstream ss;
    const F f;
    {
        boost::archive::text_oarchive oa(ss);
        oa << f;
    }
    F f1;
    {
        boost::archive::text_iarchive ia(ss);
        F f2;
        ia >> f2;
        f1 = f2;
        ia.reset_object_address(& f1, & f2);
    }
    BOOST_CHECK_EQUAL(f, f1);
}

int test_main(int /* argc */, char * /* argv */[])
{
    test1();
    test2();
    test3();
    test4();
    return EXIT_SUCCESS;
}
