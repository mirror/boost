//
// Boost.Pointer Container
//
//  Copyright Thorsten Ottosen 2003-2005. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/ptr_container/
//

#include <boost/test/unit_test.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/ptr_container/ptr_deque.hpp>
#include <boost/ptr_container/ptr_list.hpp>
#include <boost/ptr_container/ptr_array.hpp>
#include <boost/ptr_container/ptr_set.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/string.hpp>
#include <fstream>
#include <string>

//
// serialization helper: we can't save a non-const object
// 
template< class T >
inline T const& as_const( T const& r )
{
    return r;
}

//
// class hierarchy
// 
struct Base
{
    friend class boost::serialization::access;

    int i;

    
    template< class Archive >
    void serialize( Archive& ar, const unsigned int version )
    {
        ar & i;
    }

    Base() : i(42)
    { }
    
    Base( int i ) : i(i)
    { }
    
    virtual ~Base()
    { }
};

inline bool operator<( const Base& l, const Base& r )
{
    return l.i < r.i;
}

struct Derived : Base
{
    int i2;

    template< class Archive >
    void serialize( Archive& ar, const unsigned int version )
    {
        ar & boost::serialization::base_object<Base>( *this );
        ar & i2;
    }

    Derived() : Base(42), i2(42)
    { }
    
    explicit Derived( int i2 ) : Base(0), i2(i2)
    { }
};

BOOST_CLASS_EXPORT_GUID( Derived, "Derived" )

//
// test of containers
// 
// 

template< class C, class T >
void add( C& c, T* r, unsigned n )
{
    c.insert( c.end(), r ); 
}

template< class U, class T >
void add( boost::ptr_array<U,2>& c, T* r, unsigned n )
{
    c.replace( n, r );
}

template< class Cont >
void test_serialization_helper()
{
    Cont vec;
    add( vec, new Base( -1 ), 0u );
    add( vec, new Derived( 1 ), 1u );

    std::ofstream ofs("filename");
    boost::archive::text_oarchive oa(ofs);
    oa << as_const(vec);
    ofs.close();

    
    
    std::ifstream ifs("filename", std::ios::binary);
    boost::archive::text_iarchive ia(ifs);
    Cont vec2;
    ia >> vec2;
    ifs.close();

    BOOST_CHECK_EQUAL( vec.size(), vec2.size() );
    BOOST_CHECK_EQUAL( (*vec2.begin()).i, -1 );
    BOOST_CHECK_EQUAL( (*--vec2.end()).i, 0 );
    typename Cont::iterator i = vec2.end();
    --i;
    Derived* d = dynamic_cast<Derived*>( &*i ); 
    BOOST_CHECK_EQUAL( d->i2, 1 );
}

template< class Map >
void test_serialization_map_helper()
{
    Map m;
    std::string key1("key1"), key2("key2");
    m.insert( key1, new Base( -1 ) );
    m.insert( key2, new Derived( 1 ) );
    BOOST_CHECK_EQUAL( m.size(), 2u );

    std::ofstream ofs("filename");
    boost::archive::text_oarchive oa(ofs);
    oa << as_const(m);
    ofs.close();


    
    std::ifstream ifs("filename", std::ios::binary);
    boost::archive::text_iarchive ia(ifs);
    Map m2;
    ia >> m2;
    ifs.close();

    BOOST_CHECK_EQUAL( m.size(), m2.size() );
    BOOST_CHECK_EQUAL( m2.find(key1)->second->i, -1 );
    BOOST_CHECK_EQUAL( m2.find(key2)->second->i, 0 );
    typename Map::iterator i = m2.find(key2);
    Derived* d = dynamic_cast<Derived*>( i->second ); 
    BOOST_CHECK_EQUAL( d->i2, 1 );
    
}

//
// basic test of hierarchy
// 
void test_hierarchy()
{
    Base* p = new Derived();
    std::ofstream ofs("filename");
    boost::archive::text_oarchive oa(ofs);
    oa << as_const(p);
    ofs.close();

    
    Base* d = 0; 
    std::ifstream ifs("filename", std::ios::binary);
    boost::archive::text_iarchive ia(ifs);
    ia >> d;
    ifs.close();
    
    BOOST_CHECK_EQUAL( p->i, d->i );
    BOOST_CHECK( p != d );
    BOOST_CHECK( dynamic_cast<Derived*>( d ) );
    delete p;
    delete d;
} 

//
// test initializer
// 
void test_serialization()
{
    test_hierarchy();
    test_serialization_helper< boost::ptr_deque<Base> >();
    test_serialization_helper< boost::ptr_list<Base> >();
    test_serialization_helper< boost::ptr_vector<Base> >();
    test_serialization_helper< boost::ptr_array<Base,2> >();
  
    test_serialization_helper< boost::ptr_set<Base> >();
    test_serialization_helper< boost::ptr_multiset<Base> >();

    test_serialization_map_helper< boost::ptr_map<std::string,Base> >();

//
// GCC hangs when calling find() on a multimap!
//      
//#if !BOOST_WORKAROUND(BOOST_MPL_CFG_GCC, BOOST_TESTED_AT(0x0300))

    test_serialization_map_helper< boost::ptr_multimap<std::string,Base> >();
    
//#endif

}


using boost::unit_test::test_suite;

test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    test_suite* test = BOOST_TEST_SUITE( "Pointer Container Test Suite" );

    test->add( BOOST_TEST_CASE( &test_serialization ) );

    return test;
}


