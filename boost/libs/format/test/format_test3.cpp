// -*- C++ -*-
//  Boost general library 'format'   ---------------------------
//  See http://www.boost.org for updates, documentation, and revision history.

//  (C) Samuel Krempp 2001
//                  krempp@crans.ens-cachan.fr
//  Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

#include "boost/format.hpp"

#include <iostream> 
#include <iomanip>

#define BOOST_INCLUDE_MAIN 
#include <boost/test/test_tools.hpp>

struct Rational {
  int n,d;
  Rational (int an, int ad) : n(an), d(ad) {}
};

std::ostream& operator<<( std::ostream& os, const Rational& r) {
  os << r.n << "/" << r.d;
  return os;
}


int test_main(int, char* [])
{
    using namespace std;
    using boost::format;
    using boost::io::group;
    using boost::io::str;

    Rational r(16,9);

    string s;
    // special paddings 
    s = str( format("[%=6s] [%+6s] [%+6s] [% 6s] [%+6s]\n") 
                      % 123
                      % group(internal, setfill('W'), 234)
                      % group(internal, setfill('X'), -345)
                      % group(setfill('Y'), 456)
                      % group(setfill('Z'), -10 ) );

    if(s != "[  123 ] [+WW234] [-XX345] [YY 456] [ZZZ-10]\n" ) {
      cerr << s ;
      BOOST_ERROR("formatting error. (with special paddings)");
    }

    // nesting formats :
    s = str( format("%2$014x [%1%] %|2$05|\n") % (format("%05s / %s") % -18 % 7)
             %group(showbase, -100)
             );
    if( s != "0x0000ffffff9c [-0018 / 7] -0100\n" ){
      cerr << s ;
      BOOST_ERROR("nesting did not work");
    }
    return 0;
}
