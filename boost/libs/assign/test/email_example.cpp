// Boost.Assign library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/assign/
//


#include <boost/config.hpp>

#if BOOST_WORAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
#  pragma warn -8091 // supress warning in Boost.Test
#  pragma warn -8057 // unused argument argc/argv in Boost.Test
#endif

#include <boost/assign/list_inserter.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <vector>
#include <map>

namespace ba = boost::assign;

class email
{
public:
    enum address_option
    {
        check_addr_book,
        dont_check_addr_book
    };
    
    typedef std::pair<std::string,address_option> bcc_type;
        
private:

    mutable std::map<std::string,address_option> cc_list;
    mutable std::map<std::string,address_option> to_list;
    std::vector< bcc_type >                      bcc_list;
        
    void add_cc_impl( const std::string& name, address_option ao )
    {
        cc_list[ name ] = ao;
    }
    
    void add_to_impl( const std::string& name )
    {
        to_list[ name ] = check_addr_book;
    }
    
    void add_bcc_impl( const bcc_type& bcc )
    {
        bcc_list.push_back( bcc ); 
    }
     
public:
    
    ba::list_inserter< boost::function2< void, std::string, address_option > >
    add_cc( std::string name, address_option ao )
    {
        add_cc_impl( name, ao );
        return ba::make_list_inserter( boost::bind( &email::add_cc_impl, this, _1, _2 ) );
    }

    ba::list_inserter< boost::function1< void, std::string > >
    add_to( const std::string& name )
    {
        add_to_impl( name );
        return ba::make_list_inserter( boost::bind( &email::add_to_impl, this, _1 ) );
    }
    
    ba::list_inserter< boost::function1< void, bcc_type >, bcc_type >
    add_bcc( const bcc_type& bcc )
    {
        add_bcc_impl( bcc );
        return ba::make_list_inserter( boost::bind( &email::add_bcc_impl, this, _1 ) );     
    }
    
    address_option
    cc_at( const std::string& name ) const
    {
        return cc_list[ name ];
    }
    
    address_option 
    to_at( const std::string& name ) const
    {
        return to_list[ name ];
    }
    
    address_option
    bcc_at( unsigned index ) const
    {
        return bcc_list.at( index ).second;
    }
};



void check_list_inserter()
{
    using namespace boost::assign;

    email e;
    e.add_cc( "franz", email::dont_check_addr_book )
            ( "hanz", email::check_addr_book )
            ( "betty", email::dont_check_addr_book );
    BOOST_CHECK_EQUAL( e.cc_at( "franz" ), email::dont_check_addr_book );
    BOOST_CHECK_EQUAL( e.cc_at( "hanz" ), email::check_addr_book );
    BOOST_CHECK_EQUAL( e.cc_at( "betty" ), email::dont_check_addr_book );

    e.add_to( "betsy" )( "peter" );
    BOOST_CHECK_EQUAL( e.cc_at( "betsy" ), email::check_addr_book );
    BOOST_CHECK_EQUAL( e.cc_at( "peter" ), email::check_addr_book );
    
    e.add_bcc( email::bcc_type( "Mr. Foo", email::check_addr_book ) )
             ( "Mr. Bar", email::dont_check_addr_book );
    BOOST_CHECK_EQUAL( e.bcc_at( 0 ), email::check_addr_book );
    BOOST_CHECK_EQUAL( e.bcc_at( 1 ), email::dont_check_addr_book );
    
}



#include <boost/test/included/unit_test_framework.hpp> 

using boost::unit_test_framework::test_suite;

test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    test_suite* test = BOOST_TEST_SUITE( "List Test Suite" );

    test->add( BOOST_TEST_CASE( &check_list_inserter ) );

    return test;
}

