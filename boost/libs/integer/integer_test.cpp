//  boost integer.hpp test program  ------------------------------------------//

//  (C) Copyright Beman Dawes 1999. Permission to copy, use, modify, sell
//  and distribute this software is granted provided this copyright
//  notice appears in all copies. This software is provided "as is" without
//  express or implied warranty, and with no claim as to its suitability for
//  any purpose.

//  See http://www.boost.org for most recent version including documentation.

//  Revision History
//   10 Mar 01  Boost Test Library now used for tests (Beman Dawes)
//   31 Aug 99  Initial version

#include <iostream>
#include <boost/integer.hpp>

#define BOOST_INCLUDE_MAIN
#include <boost/test/test_tools.hpp>

namespace
{
    void test( long ) { std::cout << "long\n"; }
    void test( int ) { std::cout << "int\n"; }
    void test( short ) { std::cout << "short\n"; }
    void test( signed char ) { std::cout << "signed char\n"; }
    void test( unsigned long ) { std::cout << "unsigned long\n"; }
    void test( unsigned int ) { std::cout << "unsigned int\n"; }
    void test( unsigned short ) { std::cout << "unsigned short\n"; }
    void test( unsigned char ) { std::cout << "unsigned char\n"; }
} // unnamed namespace

// just to prove it works, specialize int_fast_t<short> to yield long
namespace boost
{
    template<> struct int_fast_t<short> { typedef long fast; };
}

int test_main(int,char**)
{
     using boost::int_t;
     using boost::uint_t;

#ifdef BOOST_SHOW_TYPES
     std::cout << 32 << ' '; test( int_t<32>::least() ); 
     std::cout << 31 << ' '; test( int_t<31>::least() ); 
     std::cout << 30 << ' '; test( int_t<30>::least() ); 
     std::cout << 29 << ' '; test( int_t<29>::least() ); 
     std::cout << 28 << ' '; test( int_t<28>::least() ); 
     std::cout << 27 << ' '; test( int_t<27>::least() ); 
     std::cout << 26 << ' '; test( int_t<26>::least() ); 
     std::cout << 25 << ' '; test( int_t<25>::least() ); 
     std::cout << 24 << ' '; test( int_t<24>::least() ); 
     std::cout << 23 << ' '; test( int_t<23>::least() ); 
     std::cout << 22 << ' '; test( int_t<22>::least() ); 
     std::cout << 21 << ' '; test( int_t<21>::least() ); 
     std::cout << 20 << ' '; test( int_t<20>::least() ); 
     std::cout << 19 << ' '; test( int_t<19>::least() ); 
     std::cout << 18 << ' '; test( int_t<18>::least() ); 
     std::cout << 17 << ' '; test( int_t<17>::least() ); 
     std::cout << 16 << ' '; test( int_t<16>::least() ); 
     std::cout << 15 << ' '; test( int_t<15>::least() ); 
     std::cout << 14 << ' '; test( int_t<14>::least() ); 
     std::cout << 13 << ' '; test( int_t<13>::least() ); 
     std::cout << 12 << ' '; test( int_t<12>::least() ); 
     std::cout << 11 << ' '; test( int_t<11>::least() ); 
     std::cout << 10 << ' '; test( int_t<10>::least() ); 
     std::cout << 9 << ' '; test( int_t<9>::least() ); 
     std::cout << 8 << ' '; test( int_t<8>::least() ); 
     std::cout << 7 << ' '; test( int_t<7>::least() ); 
     std::cout << 6 << ' '; test( int_t<6>::least() ); 
     std::cout << 5 << ' '; test( int_t<5>::least() ); 
     std::cout << 4 << ' '; test( int_t<4>::least() ); 
     std::cout << 3 << ' '; test( int_t<3>::least() ); 
     std::cout << 2 << ' '; test( int_t<2>::least() ); 
     std::cout << 1 << ' '; test( int_t<1>::least() ); 
     std::cout << 0 << ' '; test( int_t<0>::least() ); 
     std::cout << 32 << ' '; test( int_t<32>::fast() ); 
     std::cout << 31 << ' '; test( int_t<31>::fast() ); 
     std::cout << 30 << ' '; test( int_t<30>::fast() ); 
     std::cout << 29 << ' '; test( int_t<29>::fast() ); 
     std::cout << 28 << ' '; test( int_t<28>::fast() ); 
     std::cout << 27 << ' '; test( int_t<27>::fast() ); 
     std::cout << 26 << ' '; test( int_t<26>::fast() ); 
     std::cout << 25 << ' '; test( int_t<25>::fast() ); 
     std::cout << 24 << ' '; test( int_t<24>::fast() ); 
     std::cout << 23 << ' '; test( int_t<23>::fast() ); 
     std::cout << 22 << ' '; test( int_t<22>::fast() ); 
     std::cout << 21 << ' '; test( int_t<21>::fast() ); 
     std::cout << 20 << ' '; test( int_t<20>::fast() ); 
     std::cout << 19 << ' '; test( int_t<19>::fast() ); 
     std::cout << 18 << ' '; test( int_t<18>::fast() ); 
     std::cout << 17 << ' '; test( int_t<17>::fast() ); 
     std::cout << 16 << ' '; test( int_t<16>::fast() ); 
     std::cout << 15 << ' '; test( int_t<15>::fast() ); 
     std::cout << 14 << ' '; test( int_t<14>::fast() ); 
     std::cout << 13 << ' '; test( int_t<13>::fast() ); 
     std::cout << 12 << ' '; test( int_t<12>::fast() ); 
     std::cout << 11 << ' '; test( int_t<11>::fast() ); 
     std::cout << 10 << ' '; test( int_t<10>::fast() ); 
     std::cout << 9 << ' '; test( int_t<9>::fast() ); 
     std::cout << 8 << ' '; test( int_t<8>::fast() ); 
     std::cout << 7 << ' '; test( int_t<7>::fast() ); 
     std::cout << 6 << ' '; test( int_t<6>::fast() ); 
     std::cout << 5 << ' '; test( int_t<5>::fast() ); 
     std::cout << 4 << ' '; test( int_t<4>::fast() ); 
     std::cout << 3 << ' '; test( int_t<3>::fast() ); 
     std::cout << 2 << ' '; test( int_t<2>::fast() ); 
     std::cout << 1 << ' '; test( int_t<1>::fast() ); 
     std::cout << 0 << ' '; test( int_t<0>::fast() ); 
     std::cout << 32 << ' '; test( uint_t<32>::least() ); 
     std::cout << 31 << ' '; test( uint_t<31>::least() ); 
     std::cout << 30 << ' '; test( uint_t<30>::least() ); 
     std::cout << 29 << ' '; test( uint_t<29>::least() ); 
     std::cout << 28 << ' '; test( uint_t<28>::least() ); 
     std::cout << 27 << ' '; test( uint_t<27>::least() ); 
     std::cout << 26 << ' '; test( uint_t<26>::least() ); 
     std::cout << 25 << ' '; test( uint_t<25>::least() ); 
     std::cout << 24 << ' '; test( uint_t<24>::least() ); 
     std::cout << 23 << ' '; test( uint_t<23>::least() ); 
     std::cout << 22 << ' '; test( uint_t<22>::least() ); 
     std::cout << 21 << ' '; test( uint_t<21>::least() ); 
     std::cout << 20 << ' '; test( uint_t<20>::least() ); 
     std::cout << 19 << ' '; test( uint_t<19>::least() ); 
     std::cout << 18 << ' '; test( uint_t<18>::least() ); 
     std::cout << 17 << ' '; test( uint_t<17>::least() ); 
     std::cout << 16 << ' '; test( uint_t<16>::least() ); 
     std::cout << 15 << ' '; test( uint_t<15>::least() ); 
     std::cout << 14 << ' '; test( uint_t<14>::least() ); 
     std::cout << 13 << ' '; test( uint_t<13>::least() ); 
     std::cout << 12 << ' '; test( uint_t<12>::least() ); 
     std::cout << 11 << ' '; test( uint_t<11>::least() ); 
     std::cout << 10 << ' '; test( uint_t<10>::least() ); 
     std::cout << 9 << ' '; test( uint_t<9>::least() ); 
     std::cout << 8 << ' '; test( uint_t<8>::least() ); 
     std::cout << 7 << ' '; test( uint_t<7>::least() ); 
     std::cout << 6 << ' '; test( uint_t<6>::least() ); 
     std::cout << 5 << ' '; test( uint_t<5>::least() ); 
     std::cout << 4 << ' '; test( uint_t<4>::least() ); 
     std::cout << 3 << ' '; test( uint_t<3>::least() ); 
     std::cout << 2 << ' '; test( uint_t<2>::least() ); 
     std::cout << 1 << ' '; test( uint_t<1>::least() ); 
     std::cout << 0 << ' '; test( uint_t<0>::least() ); 
     std::cout << 32 << ' '; test( uint_t<32>::fast() ); 
     std::cout << 31 << ' '; test( uint_t<31>::fast() ); 
     std::cout << 30 << ' '; test( uint_t<30>::fast() ); 
     std::cout << 29 << ' '; test( uint_t<29>::fast() ); 
     std::cout << 28 << ' '; test( uint_t<28>::fast() ); 
     std::cout << 27 << ' '; test( uint_t<27>::fast() ); 
     std::cout << 26 << ' '; test( uint_t<26>::fast() ); 
     std::cout << 25 << ' '; test( uint_t<25>::fast() ); 
     std::cout << 24 << ' '; test( uint_t<24>::fast() ); 
     std::cout << 23 << ' '; test( uint_t<23>::fast() ); 
     std::cout << 22 << ' '; test( uint_t<22>::fast() ); 
     std::cout << 21 << ' '; test( uint_t<21>::fast() ); 
     std::cout << 20 << ' '; test( uint_t<20>::fast() ); 
     std::cout << 19 << ' '; test( uint_t<19>::fast() ); 
     std::cout << 18 << ' '; test( uint_t<18>::fast() ); 
     std::cout << 17 << ' '; test( uint_t<17>::fast() ); 
     std::cout << 16 << ' '; test( uint_t<16>::fast() ); 
     std::cout << 15 << ' '; test( uint_t<15>::fast() ); 
     std::cout << 14 << ' '; test( uint_t<14>::fast() ); 
     std::cout << 13 << ' '; test( uint_t<13>::fast() ); 
     std::cout << 12 << ' '; test( uint_t<12>::fast() ); 
     std::cout << 11 << ' '; test( uint_t<11>::fast() ); 
     std::cout << 10 << ' '; test( uint_t<10>::fast() ); 
     std::cout << 9 << ' '; test( uint_t<9>::fast() ); 
     std::cout << 8 << ' '; test( uint_t<8>::fast() ); 
     std::cout << 7 << ' '; test( uint_t<7>::fast() ); 
     std::cout << 6 << ' '; test( uint_t<6>::fast() ); 
     std::cout << 5 << ' '; test( uint_t<5>::fast() ); 
     std::cout << 4 << ' '; test( uint_t<4>::fast() ); 
     std::cout << 3 << ' '; test( uint_t<3>::fast() ); 
     std::cout << 2 << ' '; test( uint_t<2>::fast() ); 
     std::cout << 1 << ' '; test( uint_t<1>::fast() ); 
     std::cout << 0 << ' '; test( uint_t<0>::fast() );
#endif
     
    long v = 0x7FFFFFFF;
    BOOST_TEST( int_t<32>::least(v) == v );    v >>= 1;
    BOOST_TEST( int_t<31>::least(v) == v );    v >>= 1;
    BOOST_TEST( int_t<30>::least(v) == v );    v >>= 1;
    BOOST_TEST( int_t<29>::least(v) == v );    v >>= 1;
    BOOST_TEST( int_t<28>::least(v) == v );    v >>= 1;
    BOOST_TEST( int_t<27>::least(v) == v );    v >>= 1;
    BOOST_TEST( int_t<26>::least(v) == v );    v >>= 1;
    BOOST_TEST( int_t<25>::least(v) == v );    v >>= 1;
    BOOST_TEST( int_t<24>::least(v) == v );    v >>= 1;
    BOOST_TEST( int_t<23>::least(v) == v );    v >>= 1;
    BOOST_TEST( int_t<22>::least(v) == v );    v >>= 1;
    BOOST_TEST( int_t<21>::least(v) == v );    v >>= 1;
    BOOST_TEST( int_t<20>::least(v) == v );    v >>= 1;
    BOOST_TEST( int_t<19>::least(v) == v );    v >>= 1;
    BOOST_TEST( int_t<18>::least(v) == v );    v >>= 1;
    BOOST_TEST( int_t<17>::least(v) == v );    v >>= 1;
    BOOST_TEST( int_t<16>::least(v) == v );    v >>= 1;
    BOOST_TEST( int_t<15>::least(v) == v );    v >>= 1;
    BOOST_TEST( int_t<14>::least(v) == v );    v >>= 1;
    BOOST_TEST( int_t<13>::least(v) == v );    v >>= 1;
    BOOST_TEST( int_t<12>::least(v) == v );    v >>= 1;
    BOOST_TEST( int_t<11>::least(v) == v );    v >>= 1;
    BOOST_TEST( int_t<10>::least(v) == v );    v >>= 1;
    BOOST_TEST( int_t<9>::least(v) == v );     v >>= 1;
    BOOST_TEST( int_t<8>::least(v) == v );     v >>= 1;
    BOOST_TEST( int_t<7>::least(v) == v );     v >>= 1;
    BOOST_TEST( int_t<6>::least(v) == v );     v >>= 1;
    BOOST_TEST( int_t<5>::least(v) == v );     v >>= 1;
    BOOST_TEST( int_t<4>::least(v) == v );     v >>= 1;
    BOOST_TEST( int_t<3>::least(v) == v );     v >>= 1;
    BOOST_TEST( int_t<2>::least(v) == v );     v >>= 1;
    BOOST_TEST( int_t<1>::least(v) == v );     v >>= 1;
    BOOST_TEST( int_t<0>::least(v) == v );
    v = 0x7FFFFFFF;
    BOOST_TEST( int_t<32>::fast(v) == v );    v >>= 1;
    BOOST_TEST( int_t<31>::fast(v) == v );    v >>= 1;
    BOOST_TEST( int_t<30>::fast(v) == v );    v >>= 1;
    BOOST_TEST( int_t<29>::fast(v) == v );    v >>= 1;
    BOOST_TEST( int_t<28>::fast(v) == v );    v >>= 1;
    BOOST_TEST( int_t<27>::fast(v) == v );    v >>= 1;
    BOOST_TEST( int_t<26>::fast(v) == v );    v >>= 1;
    BOOST_TEST( int_t<25>::fast(v) == v );    v >>= 1;
    BOOST_TEST( int_t<24>::fast(v) == v );    v >>= 1;
    BOOST_TEST( int_t<23>::fast(v) == v );    v >>= 1;
    BOOST_TEST( int_t<22>::fast(v) == v );    v >>= 1;
    BOOST_TEST( int_t<21>::fast(v) == v );    v >>= 1;
    BOOST_TEST( int_t<20>::fast(v) == v );    v >>= 1;
    BOOST_TEST( int_t<19>::fast(v) == v );    v >>= 1;
    BOOST_TEST( int_t<18>::fast(v) == v );    v >>= 1;
    BOOST_TEST( int_t<17>::fast(v) == v );    v >>= 1;
    BOOST_TEST( int_t<16>::fast(v) == v );    v >>= 1;
    BOOST_TEST( int_t<15>::fast(v) == v );    v >>= 1;
    BOOST_TEST( int_t<14>::fast(v) == v );    v >>= 1;
    BOOST_TEST( int_t<13>::fast(v) == v );    v >>= 1;
    BOOST_TEST( int_t<12>::fast(v) == v );    v >>= 1;
    BOOST_TEST( int_t<11>::fast(v) == v );    v >>= 1;
    BOOST_TEST( int_t<10>::fast(v) == v );    v >>= 1;
    BOOST_TEST( int_t<9>::fast(v) == v );     v >>= 1;
    BOOST_TEST( int_t<8>::fast(v) == v );     v >>= 1;
    BOOST_TEST( int_t<7>::fast(v) == v );     v >>= 1;
    BOOST_TEST( int_t<6>::fast(v) == v );     v >>= 1;
    BOOST_TEST( int_t<5>::fast(v) == v );     v >>= 1;
    BOOST_TEST( int_t<4>::fast(v) == v );     v >>= 1;
    BOOST_TEST( int_t<3>::fast(v) == v );     v >>= 1;
    BOOST_TEST( int_t<2>::fast(v) == v );     v >>= 1;
    BOOST_TEST( int_t<1>::fast(v) == v );     v >>= 1;
    BOOST_TEST( int_t<0>::fast(v) == v );
    unsigned long u = 0xFFFFFFFF;
    BOOST_TEST( uint_t<32>::least(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<31>::least(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<30>::least(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<29>::least(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<28>::least(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<27>::least(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<26>::least(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<25>::least(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<24>::least(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<23>::least(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<22>::least(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<21>::least(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<20>::least(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<19>::least(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<18>::least(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<17>::least(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<16>::least(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<15>::least(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<14>::least(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<13>::least(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<11>::least(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<12>::least(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<10>::least(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<9>::least(u) == u );     u >>= 1;
    BOOST_TEST( uint_t<8>::least(u) == u );     u >>= 1;
    BOOST_TEST( uint_t<7>::least(u) == u );     u >>= 1;
    BOOST_TEST( uint_t<6>::least(u) == u );     u >>= 1;
    BOOST_TEST( uint_t<5>::least(u) == u );     u >>= 1;
    BOOST_TEST( uint_t<4>::least(u) == u );     u >>= 1;
    BOOST_TEST( uint_t<3>::least(u) == u );     u >>= 1;
    BOOST_TEST( uint_t<2>::least(u) == u );     u >>= 1;
    BOOST_TEST( uint_t<1>::least(u) == u );     u >>= 1;
    BOOST_TEST( uint_t<0>::least(u) == u );
    u = 0xFFFFFFFF;
    BOOST_TEST( uint_t<32>::fast(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<31>::fast(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<30>::fast(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<29>::fast(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<28>::fast(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<27>::fast(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<26>::fast(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<25>::fast(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<24>::fast(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<23>::fast(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<22>::fast(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<21>::fast(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<20>::fast(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<19>::fast(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<18>::fast(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<17>::fast(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<16>::fast(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<15>::fast(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<14>::fast(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<13>::fast(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<12>::fast(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<11>::fast(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<10>::fast(u) == u );    u >>= 1;
    BOOST_TEST( uint_t<9>::fast(u) == u );     u >>= 1;
    BOOST_TEST( uint_t<8>::fast(u) == u );     u >>= 1;
    BOOST_TEST( uint_t<7>::fast(u) == u );     u >>= 1;
    BOOST_TEST( uint_t<6>::fast(u) == u );     u >>= 1;
    BOOST_TEST( uint_t<5>::fast(u) == u );     u >>= 1;
    BOOST_TEST( uint_t<4>::fast(u) == u );     u >>= 1;
    BOOST_TEST( uint_t<3>::fast(u) == u );     u >>= 1;
    BOOST_TEST( uint_t<2>::fast(u) == u );     u >>= 1;
    BOOST_TEST( uint_t<1>::fast(u) == u );     u >>= 1;
    BOOST_TEST( uint_t<0>::fast(u) == u );
        
    return 0;
}
