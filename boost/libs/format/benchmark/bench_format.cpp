// -*- C++ -*-
//  Boost general library 'format'  ---------------------------
//  See http://www.boost.org for updates, documentation, and revision history.

//  (C) Samuel Krempp 2001
//                  krempp@crans.ens-cachan.fr
//  Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

// several suggestions from Jens Maurer

// ------------------------------------------------------------------------------
// bench_variants.cc :  do the same task, with snprintf, stream, and format
//                      and compare their times.

// This benchmark is provided purely for information.
// It might not even compile as-is, 
//   or not give any sensible results. 
//      (e.g., it expects sprintf to be POSIX compliant)

// ------------------------------------------------------------------------------


#include <iostream>
#include <iomanip>
#include <cstdio>  // sprintf
#include <cstring>
#include <fstream>
#include <cmath>   // floor
#include <boost/timer.hpp>

#include "boost/format.hpp"

//#define knelson

#ifdef knelson
namespace KNelson {
#include "boost/format3.hpp"
}
#endif




// portable /dev/null stream equivalent, by James Kanze, http://www.gabi-soft.de
class NulStreambuf : public std::streambuf
{
public:
  NulStreambuf() { 
      setp( dummyBuffer , dummyBuffer + 64 ) ;
  }
  virtual int  overflow( int c );
  virtual int  underflow(); 
private:
    char                dummyBuffer[ 64 ] ;
} ;

class NulStream : public std::basic_ostream<char, std::char_traits<char> > 
{
public:
  NulStream();
  virtual ~NulStream();
  NulStreambuf*    rdbuf() {
    return static_cast< NulStreambuf* >(
                   ((std::basic_ostream<char, std::char_traits<char> > *) this) -> rdbuf() ) ;
  }
} ;
 

//-------------------------------------------------------------------------------------
//   NulStream implementation

NulStream::NulStream()  : std::basic_ostream<char, std::char_traits<char> > (NULL) {
  init( new NulStreambuf ) ;
}

NulStream::~NulStream() {
    delete rdbuf() ;
}

int  NulStreambuf::underflow(){ return std::ios::traits_type::eof();    
}

int NulStreambuf::overflow( int c ){
    setp( dummyBuffer , dummyBuffer + 64 ) ;
    return (c == std::ios::traits_type::eof()) ? '\0' : c ;
}



// -------------------------------------------------------------------------------------

static int NTests = 300000;

//static std::stringstream nullStream;
static NulStream nullStream;
static double tstream, tpf;
static const std::string fstring="%3$#x %1$20.10E %2$g %3$d \n";//"point number %03d : x=%1$20.10E, v=%1$20.10E,  (%s) \n"
static const double     arg1=45.23;
static const double     arg2=12.34;
static const int        arg3=23;
static const std::string res = "0x17     4.5230000000E+01 12.34 23 \n";
//static const std::string res = "23.0000     4.5230000000E+01 12.34 23 \n";

void test_snprintf();
void test_nullstream();
void test_stored_format();
void test_format();

#ifdef knelson
void test_format3();
#endif

int main(){
    using namespace boost;
    using namespace std;

    test_snprintf();
    test_nullstream();
    test_stored_format();
    test_format();
#ifdef knelson
    //    test_format3();
#endif
    return 0;
}


void test_snprintf()
{
    using namespace std;

    // Check that snpintf is Unix98 compatible on the platform :
    char * buf = new char[4000];
    sprintf(buf, fstring.c_str(), arg1, arg2, arg3);
    if( strncmp( buf, res.c_str(), res.size()) != 0 ) {
      cerr << endl << buf;
    }
    // time the loop :
    boost::timer chrono;
    for(int i=0; i<NTests; ++i) {
      sprintf(buf, fstring.c_str(), arg1, arg2, arg3);
    }
    tpf=chrono.elapsed();
    cout  << left << setw(20) <<"printf time"<< right <<":" << tpf  << endl;
}

void test_nullstream()
{
    using namespace std;
    boost::timer chrono;
    stringstream oss;
    //static const std::string fstring="%3$#x %1$20.10E %2$g %3$d \n";

    std::ios_base::fmtflags f = std::ios_base::floatfield;
    oss << hex << showbase << arg3
         << dec << noshowbase << " " 
         << scientific << setw(20) << setprecision(10) << uppercase << arg1 
         << setprecision(0) << nouppercase ;
    oss.unsetf( f);
    oss << " " << arg2 << " " << arg3 << " \n" ;
    
    if(oss.str() != res ) {
      cerr << endl << oss.str() ;
    }


    for(int i=0; i<NTests; ++i) { 
      nullStream << hex << showbase << arg3
                 << dec << noshowbase << " " 
                 << scientific << setw(20) << setprecision(10) << uppercase <<  arg1 
                 << setprecision(6) << nouppercase;
      nullStream.unsetf( f);
      nullStream << " " << arg2 << " " << arg3 << " \n" ;

    }
    double t = chrono.elapsed();
    cout  << left << setw(20) <<"ostream time"<< right <<":" << setw(5) << t  
          << ",  = " << t / tpf << " * printf \n";
    tstream = t;
}

void test_stored_format()
{
    using namespace std;
    boost::format fmter = boost::format(fstring.c_str());

    stringstream oss;
    oss << fmter % arg1 % arg2 % arg3 ;
    if( oss.str() != res ) {
      cerr << endl << oss.str();
    }

    // not only is the format-string parsed once,
    // but also the buffer of the internal stringstream is already allocated.

    boost::timer chrono;        
    for(int i=0; i<NTests; ++i) {
      nullStream << fmter % arg1 % arg2 % arg3;
    }
    double t=chrono.elapsed();
    cout  << left << setw(20) <<"stored format time"<< right <<":" << setw(5) << t 
          << ",  = " << t / tstream << " * stream \n";
}

void test_format()
{
  using namespace std;
  stringstream oss;
  oss << boost::format(fstring.c_str()) % arg1 % arg2 % arg3;
  if(oss.str() != res ) {
    cerr << endl << oss.str();
  }

  boost::timer chrono;
  for(int i=0; i<NTests; ++i) {
    nullStream << boost::format(fstring.c_str()) % arg1 % arg2 % arg3;
  }
  double t = chrono.elapsed();
  cout  << left << setw(20) <<"format time"<< right <<":" << setw(5) << t
        << ",  = " << t / tstream << " * stream \n";
}
 
#ifdef knelson
void test_format3()
{
  using namespace std;
  stringstream oss;
  oss << KNelson::boost::format(fstring.c_str(), arg1, arg2, arg3);
  if(oss.str() != res ) {
    cerr << endl << oss.str();
  }

  boost::timer chrono;
  for(int i=0; i<NTests; ++i) {
    nullStream << KNelson::boost::format(fstring.c_str(), arg1, arg2, arg3);
  }
  double t = chrono.elapsed();
  cout  << left << setw(20) <<"format3 time"<< right <<":" << setw(5) << t
        << ",  = " << t / tstream << " * stream \n";
}
 
#endif
