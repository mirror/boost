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
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/export.hpp>
#include <fstream>


struct Base
{
	int i;

	template< class Archive >
	void serialize( Archive& ar, unsigned int version )
	{
		ar & i;
	}

	Base() : i(42)
	{ }
	
	explicit Base( int i ) : i(i)
	{ }
	
	virtual ~Base()
	{ }
};

struct Derived : Base
{
	int i2;

	template< class Archive >
	void serialize( Archive& ar, unsigned int version )
	{
		ar & boost::serialization::base_object<Base>( *this );
		ar & i2;
	}

	Derived() : Base(42), i2(42)
	{ }
	
	explicit Derived( int i2 ) : Base(0), i2(i2)
	{ }
};

BOOST_CLASS_EXPORT_GUID( Derived, "Derived")


namespace boost
{
	
	template< class Archive, class T, class CA, class A >
	inline void save( Archive& ar, ptr_vector<T,CA,A>& t, unsigned int )
	{
		boost::serialization::stl::save_collection< Archive, ptr_vector<T,CA,A> >( ar, t );
	}
	
	template< class Archive, class T, class CA, class A >
	inline void load( Archive& ar, ptr_vector<T,CA,A>& t, unsigned int )
	{
		namespace ser = boost::serialization::stl; 
		ser::load_collection< Archive, 
			                  ptr_vector<T,CA,A>,
			                  ser::archive_input_seq<Archive, ptr_vector<T,CA,A> >,
			                  ser::reserve_imp< ptr_vector<T,CA,A> > >( ar, t );
	}
	

	template< class Archive, class T, class CA, class A >
	inline void serialize( Archive& ar, ptr_vector<T,CA,A>& t, unsigned int version )
	{
		boost::serialization::split_free( ar, t, version );
	}
	
}



void test_serialization()
{
	boost::ptr_vector<Base> vec;
	vec.push_back( new Base( 2 ) );
	vec.push_back( new Derived( 1 ) );

    std::ofstream ofs("filename");
    boost::archive::text_oarchive oa(ofs);
	oa << vec;
	ofs.close();

	std::ifstream ifs("filename", std::ios::binary);
    boost::archive::text_iarchive ia(ifs);
	boost::ptr_vector<Base> vec2;
	ia >> vec2;
	ifs.close();

	BOOST_CHECK_EQUAL( vec.size(), vec2.size() );
}



using boost::unit_test::test_suite;

test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    test_suite* test = BOOST_TEST_SUITE( "Pointer Container Test Suite" );

    test->add( BOOST_TEST_CASE( &test_serialization ) );

    return test;
}


