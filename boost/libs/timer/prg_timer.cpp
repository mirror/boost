 //  progress_timer class implementation  ------------------------------------//

//  (C) Copyright Beman Dawes 1994-99. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

//  Revision History
//  16 Jul 99  Second beta
//   6 Jul 99  Initial boost version

#include <boost/progress.hpp>
#include <iostream>

namespace boost {

progress_timer::~progress_timer() {

//  Throwing an exception from a destructor is a Bad Thing.
//  The progress_timer destructor does output which may throw.
//  A progress_timer is usually not critical to the application.
//  Therefore, wrap the I/O in a try block, catch and ignore all exceptions.
  try {

    if( _os == 0 ) { _os = &std::cout; }

    std::ios_base::fmtflags old_flags = _os->setf( std::ios_base::fixed,
                                                   std::ios_base::floatfield );
    std::streamsize old_prec = _os->precision( 2 );
    *_os << elapsed() << " s\n" // "s" is System International d'Unités std
                      << std::endl;
    _os->flags( old_flags );
    _os->precision( old_prec );
    } // try block

  catch (...) {} // eat any exceptions

  } // ~progress_timer
  
} // namespace boost
