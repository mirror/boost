//  boost progress.hpp header file  ------------------------------------------//

//  (C) Copyright Beman Dawes 1994-99. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for most recent version including documentation.

//  Revision History
//  22 Jul 99  Name changed to .hpp
//  16 Jul 99  Second beta
//   6 Jul 99  Initial boost version

#ifndef BOOST_PROGRESS_HPP
#define BOOST_PROGRESS_HPP

#include <boost/timer.hpp>
#include <boost/utility.hpp>
#include <iosfwd>

namespace boost {

//  progress_timer  ----------------------------------------------------------//

//  A progress_timer behaves like a timer except that the destructor displays
//  an elapsed time message at an appropriate place in an appropriate form.

class progress_timer : public timer, noncopyable  {
  
public:
   progress_timer() : _os(0) {}
   progress_timer( std::ostream& os ) // os is hint; implementation may ignore
     : _os(&os) {}
   ~progress_timer();

private:
   std::ostream* _os; // may be 0, also member may not be present in all imps
   }; // progress_display


//  progress_display  --------------------------------------------------------//

//  progress_display displays an appropriate indication of 
//  progress at an appropriate place in an appropriate form. 

class progress_display : noncopyable {

public:
   progress_display( unsigned long expected_count )
     : _os(0) { restart(expected_count); }
   progress_display( unsigned long expected_count,
                     std::ostream& os ) // os is hint; implementation may ignore
     : _os(&os) { restart(expected_count); }

   void           restart( unsigned long expected_count );
   //  Effects: display appropriate scale
   //  Postconditions: count()==0, expected_count()==expected_count

   unsigned long  operator+=( unsigned long increment ) {
     if ( (_count += increment) >= _next_tic_count ) { display_tic(); }
     return _count;
     } // operator+=
   //  Effects: Display appropriate progress tic if needed.
   //  Postconditions: count()== original count() + increment
   //  Returns: count().

   unsigned long  operator++()           { return operator+=( 1 ); }
   unsigned long  count() const          { return _count; }
   unsigned long  expected_count() const { return _expected_count; }

private:
   std::ostream* _os; // may be 0, also member may not be present in all imps
   unsigned long _count, _expected_count, _next_tic_count;
   unsigned int  _tic;
   void display_tic();
   }; // progress_display

} // namespace boost

#endif  // BOOST_PROGRESS_HPP
