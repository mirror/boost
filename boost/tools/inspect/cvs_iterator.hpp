//  cvs_iterator  ------------------------------------------------------------//

//  (C) Copyright Beman Dawes 2003. Permission to copy,
//  use, modify, sell and distribute this software is granted provided this
//  copyright notice appears in all copies. This software is provided "as is"
//  without express or implied warranty, and with no claim as to its
//  suitability for any purpose.

//  WARNING: This is just a quick hack. It doesn't conform to C++ Standard
//  Library iterator requirements.

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/exception.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/noncopyable.hpp>
#include <string>
#include <cassert>

namespace hack
{
  class cvs_iterator : boost::noncopyable
  {
    boost::filesystem::ifstream  entries_file;
    boost::filesystem::path      dir_path;
    boost::filesystem::path      value_path;
  public:

    cvs_iterator(){} // end iterator

    ~cvs_iterator() { if ( !!entries_file ) entries_file.close(); }

    cvs_iterator( const boost::filesystem::path & dir_path ) : dir_path(dir_path)
    {
      boost::filesystem::path entries_file_path( dir_path / "CVS/Entries" ); 
      entries_file.open( entries_file_path );
      if ( !entries_file )
        throw std::string( "could not open: " ) + entries_file_path.string();
      ++*this;
    }

    const boost::filesystem::path & operator*() const { return value_path; }

    cvs_iterator & operator++()
    {
      assert( !!entries_file );
      std::string contents;
      do
      {
        do
        {
          std::getline( entries_file, contents );
          if ( entries_file.eof() )
          { 
            entries_file.close(); 
            value_path = "";
            return *this;
          }
        } while ( contents == "D" );
        if ( contents[0] == 'D' ) contents.erase( 0, 1 );
        value_path = dir_path
          / boost::filesystem::path( contents.substr( 1, contents.find( '/', 1 ) ), boost::filesystem::no_check );

      // in case entries file is mistaken, do until value_path actually found
      } while ( !boost::filesystem::exists( value_path ) );  
      return *this;
    }

    bool operator==( const cvs_iterator & rhs )
      { return value_path.string() == rhs.value_path.string(); }

    bool operator!=( const cvs_iterator & rhs )
      { return value_path.string() != rhs.value_path.string(); }

  };
}
