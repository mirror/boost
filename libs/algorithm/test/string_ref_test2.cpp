/* 
   Copyright (c) Marshall Clow 2012-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    For more information, see http://www.boost.org
*/

#include <iostream>

#include <boost/algorithm/string_ref.hpp>

#include <boost/test/included/test_exec_monitor.hpp>

typedef boost::string_ref string_ref;

void ends_with ( const char *arg ) {
    string_ref sr ( arg );
    string_ref sr2 ( arg );
    const char *p = arg;

    while ( !*p ) {
        BOOST_CHECK ( sr.ends_with ( p ));
        ++p;
        }

    while ( !sr2.empty ()) {
        BOOST_CHECK ( sr.ends_with ( sr2 ));
        sr2.remove_prefix (1);
        }

    sr2 = arg;
    while ( !sr2.empty ()) {
        BOOST_CHECK ( sr.ends_with ( sr2 ));
        sr2.remove_prefix (1);
        }

    BOOST_CHECK ( sr.ends_with ( string_ref ()));
    }
    
void starts_with ( const char *arg ) {
    string_ref sr  ( arg );
    string_ref sr2 ( arg );
    const char *p = arg + std::strlen ( arg ) - 1;
    while ( p >= arg ) {
        std::string foo ( arg, p + 1 );
        BOOST_CHECK ( sr.starts_with ( foo ));
        --p;
        }

    while ( !sr2.empty ()) {
        BOOST_CHECK ( sr.starts_with ( sr2 ));
        sr2.remove_suffix (1);
        }

    BOOST_CHECK ( sr.starts_with ( string_ref ()));
    }

void reverse ( const char *arg ) {
//  Round trip
    string_ref sr1 ( arg );
    std::string string1 ( sr1.rbegin (), sr1.rend ());
    string_ref sr2 ( string1 );
    std::string string2 ( sr2.rbegin (), sr2.rend ());

    BOOST_CHECK ( std::equal ( sr2.rbegin (), sr2.rend (), arg ));
    BOOST_CHECK ( string2 == arg );
    BOOST_CHECK ( std::equal ( sr1.begin (), sr1.end (), string2.begin ()));
    }


void find ( const char *arg ) {
    string_ref sr1 ( arg );
    const char *p = arg;
    
//  Find everything at the start
    while ( !sr1.empty ()) {
        string_ref::size_type pos = sr1.find(*p);
        BOOST_CHECK ( pos == 0 );
        sr1.remove_prefix (1);
        ++p;
        }

//  Find everything at the end
    sr1  = arg;
    p    = arg + strlen ( arg ) - 1;
    while ( !sr1.empty ()) {
        string_ref::size_type pos = sr1.rfind(*p);
        BOOST_CHECK ( pos == sr1.size () - 1 );
        sr1.remove_suffix (1);
        --p;
        }
        
//  Find everything at the start
    sr1  = arg;
    p    = arg;
    while ( !sr1.empty ()) {
        string_ref::size_type pos = sr1.find_first_of(*p);
        BOOST_CHECK ( pos == 0 );
        sr1.remove_prefix (1);
        ++p;
        }


//  Find everything at the end
    sr1  = arg;
    p    = arg + strlen ( arg ) - 1;
    while ( !sr1.empty ()) {
        string_ref::size_type pos = sr1.find_last_of(*p);
        BOOST_CHECK ( pos == sr1.size () - 1 );
        sr1.remove_suffix (1);
        --p;
        }
    }

const char *test_strings [] = {
    "",
    "0",
    "abc",
    "adsfadadiaef;alkdg;aljt;j agl;sjrl;tjs;lga;lretj;srg[w349u5209dsfadfasdfasdfadsf",
    "abc\0asdfadsfasf",
    NULL
    };
    
int test_main( int , char* [] ) {
    const char **p = &test_strings[0];
    
    while ( *p != NULL ) {
        starts_with ( *p );
        ends_with ( *p );
        reverse ( *p );
        find ( *p );

        p++;
        }

    return 0;
    }
