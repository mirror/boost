//  boost timer.hpp header file  ---------------------------------------------//

//  (C) Copyright Beman Dawes 1994-99. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for most recent version including documentation.

//  Revision History
//  25 Sep 99  elapsed_max() and elapsed_min() added (John Maddock)
//  16 Jul 99  Second beta
//   6 Jul 99  Initial boost version

#ifndef BOOST_TIMER_HPP
#define BOOST_TIMER_HPP

#include <boost/smart_ptr.hpp>

namespace boost {

//  timer  -------------------------------------------------------------------//

//  A timer object measures elapsed time.

//  It is recommended that implementations measure wall clock rather than CPU
//  time since the intended use is performance measurement on systems where
//  total elapsed time is more important than just process or CPU time.

//  Warnings: The maximum measurable elapsed time may well be only 596.5+ hours
//  due to implementation limitations.  The accuracy of timings depends on the
//  accuracy of timing information provided by the underlying platform, and
//  this varies a great deal from platform to platform.

class timer {

public:
         timer();                        // postcondition: elapsed()==0
         timer( const timer& src );      // post: elapsed()==src.elapsed()
        ~timer();
  timer& operator=( const timer& src );  // post: elapsed()==src.elapsed()
  void   restart();                      // post: elapsed()==0
  double elapsed() const;                // return elapsed time in seconds

  double elapsed_max() const;  // return estimated maximum value for elapsed()
  // Portability warning: elapsed_max() may return too high a value on systems
  // where std::clock_t overflows or resets at surprising values.
  double elapsed_min() const;            // return minimum value for elapsed()

private:
  class _timer;
  scoped_ptr<_timer> _imp;               // hide implementation details
  }; // timer

} // namespace boost

#endif  // BOOST_TIMER_HPP
