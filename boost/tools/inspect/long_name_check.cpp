//  long_name_check implementation  ------------------------------------------//

//  Copyright Beman Dawes 2002.
//  See accompanying license for terms and conditions of use.

#include "long_name_check.hpp"

namespace boost
{
  namespace inspect
  {
    long_name_check::long_name_check() : m_long_name_errors(0) {}
     
    void long_name_check::inspect(
      const string & library_name,
      const path & full_path )
    {
      string leaf( full_path.leaf() );

      if ( leaf.size() > 31 )
      {
        ++m_long_name_errors;
        error( library_name, full_path, "filename > 31 chars" );
      }
    }

    long_name_check::~long_name_check()
    {
      std::cout << "  " << m_long_name_errors << " " << desc() << '\n';
    }


  } // namespace inspect
} // namespace boost
