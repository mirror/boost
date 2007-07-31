// Boost.Range library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#define _MSL_USING_NAMESPACE 1

#include <boost/detail/workaround.hpp>

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
#  pragma warn -8091 // supress warning in Boost.Test
#  pragma warn -8057 // unused argument argc/argv in Boost.Test
#endif

#define BOOST_RANGE_ENABLE_MFC
#define BOOST_RANGE_ENABLE_MCF_CARRAY

/*
#define WIN32
#define _WINDOWS
#define _MBCS
#define _AFXDLL
#define _ATL_DLL
*/

///Od /D "WIN32" /D "_WINDOWS" /D "_DEBUG" /D "_MBCS" /D "_AFXDLL" /D "_ATL_DLL" /Gm /EHsc /RTC1 
// /MDd /Zc:wchar_t /Yu"stdafx.h" /Fp"Debug/Foo.pch" /Fo"Debug/" /Fd"Debug/vc70.pdb" /W3 /nologo /c /Wp64 /ZI /TP

#include <boost/range.hpp>
#include <boost/range/detail/mfc/carray.hpp>
#include <boost/range/detail/mfc/cstring.hpp>

#include <boost/test/test_tools.hpp>
#include <boost/config.hpp>


void check_mfc()
{
    CString s = "hello world";
    BOOST_CHECK( boost::begin( s ) + boost::size( s ) == boost::end( s ) );
    BOOST_CHECK( boost::size( s ) == boost::size( "hello world" ) );
    BOOST_CHECK( !boost::empty( s ) );
    const CString cs( s );
    BOOST_CHECK( boost::begin( cs ) + boost::size( cs ) == boost::end( cs ) );
    BOOST_CHECK( boost::size( cs ) == boost::size( "hello world" ) );
    BOOST_CHECK( !boost::empty( cs ) );
    
    CArray<int,int> a;
    BOOST_CHECK( boost::empty( a ) );
    a.Add( 5 );
    a.Add( 10 );
    BOOST_CHECK( boost::begin( a ) + boost::size( a ) == boost::end( a ) );
    BOOST_CHECK( boost::size( a ) == 2 );
    BOOST_CHECK( !boost::empty( a ) );
    const CArray<int,int>& ca = a;
    BOOST_CHECK( boost::begin( ca ) + boost::size( ca ) == boost::end( ca ) );
    BOOST_CHECK( boost::size( ca ) == 2 );
    BOOST_CHECK( !boost::empty( ca ) );
    
}



#include <boost/test/unit_test.hpp>
using boost::unit_test::test_suite;


test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    test_suite* test = BOOST_TEST_SUITE( "Range Test Suite" );

    test->add( BOOST_TEST_CASE( &check_mfc ) );

    return test;
}






