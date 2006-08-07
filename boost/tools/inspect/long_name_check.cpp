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

bool starts_with_nonalpha( path const & p )
{
  const string & x = p.string();
  assert(!x.empty());

  const string::value_type first = x[0];

  return !std::isalpha( first, std::locale::classic() )
      && first != '_'
      && x != ".cvsignore"
      ;
}

bool contains_dot( path const & p)
{
    return p.string().find( '.' ) != std::string::npos;
}

// ISO 9660
path::iterator::difference_type depth( path const & p)
{
    return std::distance( p.begin(), p.end() );
}

}}


namespace boost
{
  namespace inspect
  {
    const char file_name_check::limits::name[] = "ISO 9660 Level 3";

    file_name_check::file_name_check() : m_name_errors(0) {}

    void file_name_check::inspect(
      const string & library_name,
      const path & full_path )
    {
      std::string const leaf( full_path.leaf() );

      // checks on the leaf name ----------------------------------//
      {
          const unsigned m = filesystem::is_directory(full_path)
              ? limits::max_dirname_length
              : limits::max_filename_length;

          if ( leaf.size() > m )
          {
              ++m_name_errors;
              error( library_name, full_path, string(name())
                  + " name exceeds "
                  + boost::lexical_cast<string>(m)
                  + " characters" );
          }
      }

      if ( std::count( leaf.begin(), leaf.end(), '.' ) > 1 )
      {
        ++m_name_errors;
        error( library_name, full_path, string(name())
            + " name contains more than one dot character ('.')" );
      }

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

      if( aux::starts_with_nonalpha( path(leaf)) )
      {
        ++m_name_errors;
        error( library_name, full_path, string(name())
            + " leading character of \""
            + leaf + "\""
            + " is not alphabetic" );
      }

      if ( filesystem::is_directory( full_path )
          && aux::contains_dot( relative_path ) )
      {
        ++m_name_errors;
        error( library_name, full_path, string(name())
            + " directory name contains the dot character ('.')" );
      }

      {
          const int m = limits::max_directory_depth;
          if ( filesystem::is_directory( full_path ) 
              && aux::depth( relative_path) > m )
          {
              ++m_name_errors;
              error( library_name, full_path, string(name())
                  + " directory depth exceeds "
                  + boost::lexical_cast<string>(m)
                  + " (maximum for " + limits::name + " (CD-ROMs))" );
          }
      }

      const unsigned max_relative_path = 100; // [gps] Explain this
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
            + generic_root )
            ;
      }

      if (relative_path.leaf() != ".cvsignore")
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
      std::cout << "  " << m_name_errors << " " << desc() << '\n';
    }


  } // namespace inspect
} // namespace boost
