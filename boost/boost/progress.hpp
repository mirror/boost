//  boost progress.hpp header file  ------------------------------------------//

//  (C) Copyright Beman Dawes 1994-99. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for most recent version including documentation.

//  Revision History
//  12 Jan 01  Change to inline implementation to allow use without library
//             builds. See docs for more rationale. (Beman Dawes) 
//  22 Jul 99  Name changed to .hpp
//  16 Jul 99  Second beta
//   6 Jul 99  Initial boost version

#ifndef BOOST_PROGRESS_HPP
#define BOOST_PROGRESS_HPP

#include <boost/timer.hpp>
#include <boost/utility.hpp>  // for noncopyable
#include <boost/cstdint.hpp>  // for uintmax_t
#include <iostream>

namespace boost {

//  progress_timer  ----------------------------------------------------------//

//  A progress_timer behaves like a timer except that the destructor displays
//  an elapsed time message at an appropriate place in an appropriate form.

class progress_timer : public timer, noncopyable
{
  
 public:
  explicit progress_timer( std::ostream & os = std::cout )
     : _os(os) {}  // os is hint; implementation may ignore
  ~progress_timer()
  {
  //  A) Throwing an exception from a destructor is a Bad Thing.
  //  B) The progress_timer destructor does output which may throw.
  //  C) A progress_timer is usually not critical to the application.
  //  Therefore, wrap the I/O in a try block, catch and ignore all exceptions.
    try
    {
      std::ios_base::fmtflags old_flags = _os.setf( std::ios_base::fixed,
                                                   std::ios_base::floatfield );
      std::streamsize old_prec = _os.precision( 2 );
      _os << elapsed() << " s\n" // "s" is System International d'Unités std
                       << std::endl;
      _os.flags( old_flags );
      _os.precision( old_prec );
    }

    catch (...) {} // eat any exceptions
  } // ~progress_timer

 private:
  std::ostream & _os;
};


//  progress_display  --------------------------------------------------------//

//  progress_display displays an appropriate indication of 
//  progress at an appropriate place in an appropriate form.

// NOTE: (Jan 12, 2001) Tried to change unsigned long to boost::uintmax_t, but
// found some compilers couldn't handle the required conversion to double.
// Reverted to unsigned long until the compilers catch up. 

class progress_display : noncopyable
{
 public:
  explicit progress_display( unsigned long expected_count,
                             std::ostream & os = std::cout )
   // os is hint; implementation may ignore
   : _os(os) { restart(expected_count); }

  void           restart( unsigned long expected_count )
  //  Effects: display appropriate scale
  //  Postconditions: count()==0, expected_count()==expected_count
  {
    _count = _next_tic_count = _tic = 0;
    _expected_count = expected_count;

    _os << "\n0%   10   20   30   40   50   60   70   80   90   100%\n"
             "|----|----|----|----|----|----|----|----|----|----|" << std::endl;
    if ( !_expected_count ) _expected_count = 1;  // prevent divide by zero
  } // restart

  unsigned long  operator+=( unsigned long increment )
  //  Effects: Display appropriate progress tic if needed.
  //  Postconditions: count()== original count() + increment
  //  Returns: count().
  {
    if ( (_count += increment) >= _next_tic_count ) { display_tic(); }
    return _count;
  }

  unsigned long  operator++()           { return operator+=( 1 ); }
  unsigned long  count() const          { return _count; }
  unsigned long  expected_count() const { return _expected_count; }

  private:
  std::ostream & _os; // may not be present in all imps
  unsigned long _count, _expected_count, _next_tic_count;
  unsigned int  _tic;
  void display_tic()
  {
    int tics_needed = (static_cast<double>(_count)/_expected_count)*50.0;
    do { _os << '*' << std::flush; } while ( ++_tic < tics_needed );
    _next_tic_count = (_tic/50.0)*_expected_count;  // use fp so large counts work
    if ( _count == _expected_count ) {
      if ( _tic < 51 ) _os << '*';
      _os << std::endl;
      }
  } // display_tic
};

} // namespace boost

#endif  // BOOST_PROGRESS_HPP
