//  minmax_check implementation  -----------------------------------------------//

//  Copyright Beman Dawes 2002.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include "minmax_check.hpp"
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>

namespace
{
  boost::regex minmax_regex(
    "\\b(min|max)\\b" // match min or max, whole word
    "\\s*\\(",        // followed by 0 or more spaces and an opening paren
    boost::regex::normal);

} // unnamed namespace

namespace boost
{
  namespace inspect
  {

    //  minmax_check constructor  --------------------------------------------------//

    minmax_check::minmax_check()
      : m_errors(0)
    {
      // C/C++ source code...
      register_signature( ".c" );
      register_signature( ".cpp" );
      register_signature( ".cxx" );
      register_signature( ".h" );
      register_signature( ".hpp" );
      register_signature( ".hxx" );
      register_signature( ".inc" );
      register_signature( ".ipp" );
    }

    //  inspect ( C++ source files )  ----------------------------------------------//

    void minmax_check::inspect(
      const string & library_name,
      const path & full_path,      // example: c:/foo/boost/filesystem/path.hpp
      const string & contents)     // contents of file to be inspected
    {
      boost::sregex_iterator cur(contents.begin(), contents.end(), minmax_regex), end;

      for( ; cur != end; ++cur, ++m_errors )
      {
        std::string linenbr = boost::lexical_cast<string>(
          std::count( contents.begin(), (*cur)[0].first, '\n' ) + 1);

        error( library_name, full_path, "violation of Boost min/max guidelines on line " + linenbr );
      } 
    }

  } // namespace inspect
} // namespace boost

