//  license_check implementation  --------------------------------------------//

//  Copyright Beman Dawes 2002-2003.
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <boost/regex.hpp>
#include "license_check.hpp"

namespace
{
  boost::regex license_regex(
    "boost(\\s+|\\s+#\\s*|\\s+//\\s*)software(\\s+|\\s+#\\s*|\\s+//\\s*)license",
    boost::regbase::normal | boost::regbase::icase);

} // unnamed namespace

namespace boost
{
  namespace inspect
  {
   license_check::license_check() : m_files_with_errors(0)
   {
     register_signature( ".c" );
     register_signature( ".cpp" );
     register_signature( ".cxx" );
     register_signature( ".h" );
     register_signature( ".hpp" );
     register_signature( ".hxx" );
     register_signature( ".htm" );
     register_signature( ".html" );
     register_signature( ".ipp" );
     register_signature( "Jamfile" );
     register_signature( ".jam" );
   }
     
   void license_check::inspect(
      const string & library_name,
      const path & full_path,   // example: c:/foo/boost/filesystem/path.hpp
      const string & contents )     // contents of file to be inspected
    {
      if ( !boost::regex_search( contents, license_regex ) )
      {
        ++m_files_with_errors;
        error( library_name, full_path, desc() );
      }
    }
  } // namespace inspect
} // namespace boost


