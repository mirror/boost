//  copyright_check implementation  ------------------------------------------------//

//  Copyright Beman Dawes 2002.
//  See accompanying license for terms and conditions of use.

#include "copyright_check.hpp"

namespace boost
{
  namespace inspect
  {
   copyright_check::copyright_check() : m_files_with_errors(0)
   {
     register_signature( ".c" );
     register_signature( ".cpp" );
     register_signature( ".cxx" );
     register_signature( ".h" );
     register_signature( ".hpp" );
     register_signature( ".hxx" );
     register_signature( ".ipp" );
     register_signature( "Jamfile" );
     register_signature( ".jam" );
   }
     
   void copyright_check::inspect(
      const string & library_name,
      const path & full_path,   // example: c:/foo/boost/filesystem/path.hpp
      const string & contents )     // contents of file to be inspected
    {
      if ( contents.find( "Copyright" ) == string::npos
        && contents.find( "copyright" ) == string::npos )
      {
        ++m_files_with_errors;
        error( library_name, full_path, desc() );
      }
    }
  } // namespace inspect
} // namespace boost


