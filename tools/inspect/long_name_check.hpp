//  long_name_check header  --------------------------------------------------//
//  (main class renamed to: file_name_check) - gps

//  Copyright Beman Dawes 2002.
//  Copyright Gennaro Prota 2006.
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FILE_NAME_CHECK_HPP
#define BOOST_FILE_NAME_CHECK_HPP

#include "inspector.hpp"

namespace boost
{
  namespace inspect
  {
    class file_name_check : public inspector
    {
      long m_name_errors;

      // ISO 9660 Level 3
      //
      struct iso_9660_limits
      {
          enum { max_directory_depth = 8 };
          enum { max_dirname_length = 31 };
          enum { max_filename_length = 31 }; // > level 2!

          static const char name[];
      };

    public:

      typedef iso_9660_limits limits;

      file_name_check();
      virtual ~file_name_check();

      virtual const char * name() const { return "*N*"; }
      virtual const char * desc() const { return "file/directory names issues"; }

      virtual void inspect(
        const string & library_name,
        const path & full_path );

      virtual void inspect(
        const string &, // "filesystem"
        const path &,   // "c:/foo/boost/filesystem/path.hpp"
        const string &)
      { /* empty */ }



    };
  }
}

#endif // BOOST_FILE_NAME_CHECK_HPP
