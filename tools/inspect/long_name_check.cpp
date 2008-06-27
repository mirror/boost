//  long_name_check implementation  ------------------------------------------//

//  Copyright Beman Dawes 2002.
//  Copyright Gennaro Prota 2006.
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include "long_name_check.hpp"

#include "boost/filesystem/operations.hpp"
#include "boost/lexical_cast.hpp"

#include <locale>
#include <algorithm>

namespace { namespace aux {

bool starts_with_nonalnum( path const & p )
{
  const string & x = p.string();
  assert(!x.empty());

  const string::value_type first = x[0];

  return !std::isalnum( first, std::locale::classic() )
      && first != '_'
      && x != ".cvsignore"
      && x != ".svn"
      ;
}

}}


namespace boost
{
  namespace inspect
  {
    const char file_name_check::limits::name[] = "ISO 9660:1999 Level 3";

    file_name_check::file_name_check() : m_name_errors(0) {}

    void file_name_check::inspect(
      const string & library_name,
      const path & full_path )
    {
      std::string const leaf( full_path.leaf() );

      if ( *leaf.rbegin() == '.' )
      {
        ++m_name_errors;
        error( library_name, full_path, string(name())
            + " filename ends with the dot character ('.')" );
      }

      path const relative_path(
          relative_to( full_path, filesystem::initial_path() )
          , &filesystem::no_check );


      // checks on the directory name --------------------------- //

      if( aux::starts_with_nonalnum( path(leaf)) )
      {
        ++m_name_errors;
        error( library_name, full_path, string(name())
            + " leading character of \""
            + leaf + "\""
            + " is not alphanumeric" );
      }

      const unsigned max_relative_path = 207; // ISO 9660:1999 sets this limit
      const string generic_root( "boost_X_XX_X/" );
      if ( relative_path.string().size() >
          ( max_relative_path - generic_root.size() ) )
      {
        ++m_name_errors;
        error( library_name, full_path,
            string(name())
            + " file path will exceed "
            + boost::lexical_cast<string>(max_relative_path)
            + " characters in a directory tree with a root of the form "
            + generic_root + ", and this exceeds ISO 9660:1999 limit of 207"  )
            ;
      }

      if (relative_path.leaf() != ".cvsignore" && relative_path.leaf() != ".svn")
      {
        try
        {
          path const check_portability( relative_path.string(), &filesystem::portable_name );
        }
        catch ( filesystem::filesystem_error const& )
        {
          ++m_name_errors;
          error( library_name, full_path, string(name()) + " nonportable path" );
        }
      }
    }

    file_name_check::~file_name_check()
    {
      std::cout << "  " << m_name_errors << " " << desc() << line_break();
    }


  } // namespace inspect
} // namespace boost
