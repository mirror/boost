//  progress_display implementation  -----------------------------------------//

//  (C) Copyright Beman Dawes 1996-99. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

//  Revision History
//  16 Jul 99  Second beta
//   6 Jul 99  Initial boost version

#include <boost/progress.hpp>
#include <iostream>
#include <cassert>

namespace boost {

void progress_display::restart( unsigned long expected_count ) {

  _count = _next_tic_count = _tic = 0;
  _expected_count = expected_count;

  if ( _os == 0 ) { _os = &std::cout; }

  *_os << "\n0%   10   20   30   40   50   60   70   80   90   100%\n"
            "|----|----|----|----|----|----|----|----|----|----|" << std::endl;
  if ( !_expected_count ) _expected_count = 1;  // prevent divide by zero
  } // restart

void progress_display::display_tic() {

  assert( _os != 0 );
  int tics_needed = (static_cast<double>(_count)/_expected_count)*50.0;
  do { *_os << '*' << std::flush; } while ( ++_tic < tics_needed );
  _next_tic_count = (_tic/50.0)*_expected_count;  // use fp so large counts work
  if ( _count == _expected_count ) {
    if ( _tic < 51 ) *_os << '*';
    *_os << std::endl;
    }
  } // display_tic

} // namespace boost

