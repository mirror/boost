//  timer class implementation  ----------------------------------------------//

//  (C) Copyright Beman Dawes 1994-98. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

///  Portability warning: this implementation depends on std::clock() returning
///  elapsed time, and CLOCKS_PER_SEC being reasonably large. Those
///  requirements are not met by all operating systems. 

//  Revision History
//  25 Sep 99  elapsed_max() and elapsed_min() added (John_Maddock)
//  16 Jul 99  Second beta
//   6 Jul 99  Initial boost version

#include <boost/timer.hpp>
#include <ctime>
#include <limits>

namespace std {}      /// cope with implementations which do not yet
using namespace std;  /// place the <ctime> functions in namespace std
                      /// Yes, this is ugly, but it is also the real world

namespace boost {

class timer::_timer { public: clock_t start_time; };

timer::timer() : _imp( new _timer ) { _imp->start_time = clock(); }

timer::timer( const timer& src ) : _imp( new _timer )
                                    { _imp->start_time = src._imp->start_time; }
timer::~timer(){}
 
void timer::restart()               { _imp->start_time = clock(); }

timer& timer::operator=( const timer& src )
  { _imp->start_time = src._imp->start_time; return * this; }
    
double timer::elapsed() const 
  { return  double(clock() - _imp->start_time) / CLOCKS_PER_SEC; }

double timer::elapsed_max() const {
    return (double(numeric_limits<clock_t>::max())
       - double(_imp->start_time)) / double(CLOCKS_PER_SEC); 
}

double timer::elapsed_min() const   { return double(1)/double(CLOCKS_PER_SEC); }


              
} // namespace boost

