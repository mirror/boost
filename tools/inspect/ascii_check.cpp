//  ascii_check implementation  ------------------------------------------------//

//  Copyright Marshall Clow 2007.
//	Based on the tab-check checker by Beman Dawes
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//	√ -- this is a test.

#include "ascii_check.hpp"
#include <functional>

namespace boost
{
  namespace inspect
  {

	static const string gPunct ( "$_{}[]#()<>%:;.?*+-/ˆ&|~!=,\\\"'@^`" );
	
   // Legal characters for a source file are defined in section 2.2 of the standard
   // I have added '@', '^', and '`' to the "legal" chars because they are commonly
   //    used in comments, and they are strictly ASCII.
   struct non_ascii : public std::unary_function<char, bool> {
   public:
      non_ascii () {}
      ~non_ascii () {}
      bool operator () ( char c ) const
      {
         if ( c == ' ' ) return false;
         if ( c >= 'a' && c <= 'z' ) return false;
         if ( c >= 'A' && c <= 'Z' ) return false;
         if ( c >= '0' && c <= '9' ) return false;
      // Horizontal/Vertical tab, newline, and form feed
         if ( c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f' ) return false;
         return gPunct.find ( c ) == string::npos;
      }
   };


   ascii_check::ascii_check() : m_files_with_errors(0)
   {
     register_signature( ".c" );
     register_signature( ".cpp" );
     register_signature( ".cxx" );
     register_signature( ".h" );
     register_signature( ".hpp" );
     register_signature( ".hxx" );
     register_signature( ".ipp" );
   }

   void ascii_check::inspect(
      const string & library_name,
      const path & full_path,   // example: c:/foo/boost/filesystem/path.hpp
      const string & contents )     // contents of file to be inspected
    {
      if (contents.find( "boostinspect:" "noascii" ) != string::npos) return;

      if ( std::find_if ( contents.begin (), contents.end (), non_ascii ()) != contents.end ())
      {
        ++m_files_with_errors;
        error( library_name, full_path, name() );
      }
    }
  } // namespace inspect
} // namespace boost


