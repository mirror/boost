//  assert_macro_check implementation  ------------------------------------------------//

//  Copyright Eric Niebler 2010.
//  Based on the assert_macro_check checker by Marshall Clow
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include "deprecated_macro_check.hpp"
#include <functional>
#include "boost/regex.hpp"
#include "boost/lexical_cast.hpp"
#include "boost/filesystem/operations.hpp"

namespace fs = boost::filesystem;

namespace
{
  const char * boost150macros [] = {
	"BOOST_NO_0X_HDR_ARRAY",
	"BOOST_NO_0X_HDR_CHRONO",
	"BOOST_NO_0X_HDR_CODECVT",
	"BOOST_NO_0X_HDR_CONDITION_VARIABLE",
	"BOOST_NO_0X_HDR_FORWARD_LIST",
	"BOOST_NO_0X_HDR_FUTURE",
	"BOOST_NO_0X_HDR_INITIALIZER_LIST",
	"BOOST_NO_INITIALIZER_LISTS",
	"BOOST_NO_0X_HDR_MUTEX",
	"BOOST_NO_0X_HDR_RANDOM",
	"BOOST_NO_0X_HDR_RATIO",
	"BOOST_NO_0X_HDR_REGEX",
	"BOOST_NO_0X_HDR_SYSTEM_ERROR",
	"BOOST_NO_0X_HDR_THREAD",
	"BOOST_NO_0X_HDR_TUPLE",
	"BOOST_NO_0X_HDR_TYPE_TRAITS",
	"BOOST_NO_0X_HDR_TYPEINDEX",
	"BOOST_NO_0X_HDR_UNORDERED_SET",
	"BOOST_NO_0X_HDR_UNORDERED_MAP",
	"BOOST_NO_STD_UNORDERED",
	NULL
	};
	
  const char * boost151macros [] = {
    NULL
    };
} // unnamed namespace


namespace boost
{
  namespace inspect
  {
   deprecated_macro_check::deprecated_macro_check()
     : m_files_with_errors(0)
     , m_from_boost_root(
         fs::exists(fs::initial_path() / "boost") &&
         fs::exists(fs::initial_path() / "libs"))
   {
     register_signature( ".c" );
     register_signature( ".cpp" );
     register_signature( ".cxx" );
     register_signature( ".h" );
     register_signature( ".hpp" );
     register_signature( ".hxx" );
     register_signature( ".ipp" );
   }

   void deprecated_macro_check::inspect(
      const string & library_name,
      const path & full_path,   // example: c:/foo/boost/filesystem/path.hpp
      const string & contents )     // contents of file to be inspected
    {
      if (contents.find( "boostinspect:" "ndprecated_macros" ) != string::npos)
        return;

      // Check files iff (a) they are in the boost directory, or (b) they
      // are in the src directory under libs.
      if (m_from_boost_root) {
        path relative( relative_to( full_path, fs::initial_path() ) );
        path::const_iterator pbeg = relative.begin(), pend = relative.end();
        if (pbeg != std::find(pbeg, pend, "boost") &&
          !(pbeg == std::find(pbeg, pend, "libs") && pend != std::find(pbeg, pend, "src")))
          return;
      }

      const char **ptr;
      long errors = 0;
      for ( ptr = boost150macros; *ptr != NULL; ++ptr )
      {
		if ( contents.find( *ptr ) != string::npos ) {
          ++errors;
          error( library_name, full_path, string ( "Deprecated Boost macro " ) + *ptr );
          }
      }

      for ( ptr = boost151macros; *ptr != NULL; ++ptr )
      {
		if ( contents.find( *ptr ) != string::npos ) {
          ++errors;
          error( library_name, full_path, string ( "Deprecated Boost macro " ) + *ptr );
          }
      }

      if(errors > 0)
        ++m_files_with_errors;
    }
  } // namespace inspect
} // namespace boost


