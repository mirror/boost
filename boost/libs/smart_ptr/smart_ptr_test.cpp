//  smart pointer test program  ----------------------------------------------//

//  (C) Copyright Beman Dawes 1998, 1999. Permission to copy, use, modify, sell
//  and distribute this software is granted provided this copyright notice
//  appears in all copies. This software is provided "as is" without express or
//  implied warranty, and with no claim as to its suitability for any purpose.

//  Revision History
//  29 Nov 99  added std::swap and associative container tests (Darin Adler)
//  25 Sep 99  added swap tests
//  20 Jul 99  header name changed to .hpp
//  20 Apr 99  additional error tests added.

#include <boost/smart_ptr.hpp>
#include <cassert>
#include <cstring>
#include <iostream>
#include <set>

#ifdef NDEBUG
#error This test program makes no sense if NDEBUG is defined
#endif

using namespace std;
using boost::scoped_ptr;
using boost::scoped_array;
using boost::shared_ptr;
using boost::shared_array;

template<typename T>
void ck( const T* v1, T v2 ) { assert( *v1 == v2 ); }

namespace {
  int UDT_use_count;  // independent of pointer maintained counts
  }

//  user defined type  -------------------------------------------------------//

class UDT {
  long value_;
 public:
  explicit UDT( long value=0 ) : value_(value) { ++UDT_use_count; }
  ~UDT() {
    --UDT_use_count;
    cout << "UDT with value " << value_ << " being destroyed" << endl;
    }
  long value() const { return value_; }
  void value( long v ) { value_ = v;; }
  };  // UDT

//  main  --------------------------------------------------------------------//

//  This isn't a very systematic test; it just hits some of the basics.

int main() {

  assert( UDT_use_count == 0 );  // reality check

  //  test scoped_ptr with a built-in type
  long * lp = new long;
  scoped_ptr<long> sp ( lp );
  assert( sp.get() == lp );
  assert( lp == sp.get() );
  assert( &*sp == lp );

  *sp = 1234568901L;
  assert( *sp == 1234568901L );
  assert( *lp == 1234568901L );
  ck( static_cast<long*>(sp.get()), 1234568901L );
  ck( lp, *sp );

  sp.reset();
  assert( sp.get() == 0 );

  //  test scoped_ptr with a user defined type
  scoped_ptr<UDT> udt_sp ( new UDT( 999888777 ) );
  assert( udt_sp->value() == 999888777 );
  udt_sp.reset();
  udt_sp.reset( new UDT( 111222333 ) );
  assert( udt_sp->value() == 111222333 );
  udt_sp.reset( new UDT( 333222111 ) );
  assert( udt_sp->value() == 333222111 );

  //  test scoped_array with a build-in type
  char * sap = new char [ 100 ];
  scoped_array<char> sa ( sap );
  assert( sa.get() == sap );
  assert( sap == sa.get() );

  strcpy( sa.get(), "Hot Dog with mustard and relish" );
  assert( strcmp( sa.get(), "Hot Dog with mustard and relish" ) == 0 );
  assert( strcmp( sap, "Hot Dog with mustard and relish" ) == 0 );

  assert( sa[0] == 'H' );
  assert( sa[30] == 'h' );

  sa[0] = 'N';
  sa[4] = 'd';
  assert( strcmp( sap, "Not dog with mustard and relish" ) == 0 );

  sa.reset();
  assert( sa.get() == 0 );

  //  test shared_ptr with a built-in type
  int * ip = new int;
  shared_ptr<int> cp ( ip );
  assert( ip == cp.get() );
  assert( cp.use_count() == 1 );

  *cp = 54321;
  assert( *cp == 54321 );
  assert( *ip == 54321 );
  ck( static_cast<int*>(cp.get()), 54321 );
  ck( static_cast<int*>(ip), *cp );

  shared_ptr<int> cp2 ( cp );
  assert( ip == cp2.get() );
  assert( cp.use_count() == 2 );
  assert( cp2.use_count() == 2 );

  assert( *cp == 54321 );
  assert( *cp2 == 54321 );
  ck( static_cast<int*>(cp2.get()), 54321 );
  ck( static_cast<int*>(ip), *cp2 );
  
  shared_ptr<int> cp3 ( cp );
  assert( cp.use_count() == 3 );
  assert( cp2.use_count() == 3 );
  assert( cp3.use_count() == 3 );
  cp.reset();
  assert( cp2.use_count() == 2 );
  assert( cp3.use_count() == 2 );
  assert( cp.use_count() == 1 );
  cp.reset( new int );
  *cp =  98765;
  assert( *cp == 98765 );
  *cp3 = 87654;
  assert( *cp3 == 87654 );
  assert( *cp2 == 87654 );
  cp.swap( cp3 );
  assert( *cp == 87654 );
  assert( *cp2 == 87654 );
  assert( *cp3 == 98765 );
  cp.swap( cp3 );
  assert( *cp == 98765 );
  assert( *cp2 == 87654 );
  assert( *cp3 == 87654 );
  cp2 = cp2;
  assert( cp2.use_count() == 2 );
  assert( *cp2 == 87654 );
  cp = cp2;
  assert( cp2.use_count() == 3 );
  assert( *cp2 == 87654 );
  assert( cp.use_count() == 3 );
  assert( *cp == 87654 );
  
  shared_ptr<int> cp4;
  swap( cp2, cp4 );
  assert( cp4.use_count() == 3 );
  assert( *cp4 == 87654 );
  assert( cp2.get() == 0 );
  
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
  set< shared_ptr<int> > scp;
  scp.insert(cp4);
  assert( scp.find(cp4) != scp.end() );
  assert( scp.find(cp4) == scp.find( shared_ptr<int>(cp4) ) );
#endif

  //  test shared_array with a built-in type
  char * cap = new char [ 100 ];
  shared_array<char> ca ( cap );
  assert( ca.get() == cap );
  assert( cap == ca.get() );
  assert( &ca[0] == cap );

  strcpy( ca.get(), "Hot Dog with mustard and relish" );
  assert( strcmp( ca.get(), "Hot Dog with mustard and relish" ) == 0 );
  assert( strcmp( cap, "Hot Dog with mustard and relish" ) == 0 );

  assert( ca[0] == 'H' );
  assert( ca[30] == 'h' );
  
  shared_array<char> ca2 ( ca );
  shared_array<char> ca3 ( ca2 );

  ca[0] = 'N';
  ca[4] = 'd';
  assert( strcmp( ca.get(), "Not dog with mustard and relish" ) == 0 );
  assert( strcmp( ca2.get(), "Not dog with mustard and relish" ) == 0 );
  assert( strcmp( ca3.get(), "Not dog with mustard and relish" ) == 0 );
  assert( ca.use_count() == 3 );
  assert( ca2.use_count() == 3 );
  assert( ca3.use_count() == 3 );
  ca2.reset();
  assert( ca.use_count() == 2 );
  assert( ca3.use_count() == 2 );
  assert( ca2.use_count() == 1 );

  ca.reset();
  assert( ca.get() == 0 );

  shared_array<char> ca4;
  swap( ca3, ca4 );
  assert( ca4.use_count() == 1 );
  assert( strcmp( ca4.get(), "Not dog with mustard and relish" ) == 0 );
  assert( ca3.get() == 0 );
  
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
  set< shared_array<char> > sca;
  sca.insert(ca4);
  assert( sca.find(ca4) != sca.end() );
  assert( sca.find(ca4) == sca.find( shared_array<char>(ca4) ) );
#endif

  //  test shared_array with user defined type
  shared_array<UDT> udta ( new UDT[3] );

  udta[0].value( 111 );
  udta[1].value( 222 );
  udta[2].value( 333 );
  shared_array<UDT> udta2 ( udta );

  assert( udta[0].value() == 111 );
  assert( udta[1].value() == 222 );
  assert( udta[2].value() == 333 );
  assert( udta2[0].value() == 111 );
  assert( udta2[1].value() == 222 );
  assert( udta2[2].value() == 333 );
  udta2.reset();
  assert( udta2.get() == 0 );
  assert( udta.use_count() == 1 );
  assert( udta2.use_count() == 1 );

  assert( UDT_use_count == 4 );  // reality check

  //  test shared_ptr with a user defined type
  UDT * up = new UDT;
  shared_ptr<UDT> sup ( up );
  assert( up == sup.get() );
  assert( sup.use_count() == 1 );

  sup->value( 54321 ) ;
  assert( sup->value() == 54321 );
  assert( up->value() == 54321 );

  shared_ptr<UDT> sup2;
  sup2 = sup;
  assert( sup2->value() == 54321 );
  assert( sup.use_count() == 2 );
  assert( sup2.use_count() == 2 );
  sup2 = sup2;
  assert( sup2->value() == 54321 );
  assert( sup.use_count() == 2 );
  assert( sup2.use_count() == 2 );

  cout << "OK" << endl;

  new char[12345]; // deliberate memory leak to verify leaks detected

  return 0;
  } // main

