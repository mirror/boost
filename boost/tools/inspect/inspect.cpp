//  inspect program  ---------------------------------------------------------//

//  (C) Copyright Beman Dawes 2002
//  See accompanying license for terms and conditions of use.

//  This program recurses through sub-directories looking for various problems.
//  It contains some Boost specific features, like ignoring "CVS" and "bin",
//  and the code that identifies library names assumes the Boost directory
//  structure.

//  See http://www.boost.org/tools/inspect for more information.

#include <boost/shared_ptr.hpp>
#include <boost/filesystem/exception.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>

#include <iostream>
#include <cassert>
#include <vector>
#include <list>
#include <utility>
#include <algorithm>

#include "inspector.hpp" // includes <string>, <boost/filesystem/path.hpp>,
                         // <iostream>, <set>
                         // and gives using for string and path.
#include "copyright_check.hpp"
#include "crlf_check.hpp"
#include "link_check.hpp"
#include "long_name_check.hpp"
#include "tab_check.hpp"
#include "cvs_iterator.hpp"

namespace fs = boost::filesystem;

namespace
{
  typedef boost::shared_ptr< boost::inspect::inspector > inspector_ptr;

  struct inspector_element
  {
    inspector_ptr  inspector;

    inspector_element( boost::inspect::inspector * p ) : inspector(p) {}
  };

  typedef std::list< inspector_element > inspector_list;

  long file_count;
  long directory_count;
  long error_count;

  boost::inspect::string_set content_signatures;

  hack::cvs_iterator end_itr;

  struct error_msg
  {
    string library;
    string rel_path;
    string msg;

    bool operator<( const error_msg & rhs ) const
    {
      if ( library < rhs.library ) return true;
      if ( library > rhs.library ) return false;
      if ( rel_path < rhs.rel_path ) return true;
      if ( rel_path > rhs.rel_path ) return false;
      return msg < rhs.msg;
    }
  };

  typedef std::vector< error_msg > error_msg_vector;
  error_msg_vector msgs;

//  visit_predicate (determines which directories are visited)  --------------//

  typedef bool(*pred_type)(const path&);

  bool visit_predicate( const path & pth )
  {
    string leaf( pth.leaf() );
    return
      leaf != "CVS"
      && leaf != "bin"
      && leaf != "jam_src" // this really out of our hands
      && leaf != "status"  // too many issues with generated HTML files
      ;
  }

//  library_from_content  ----------------------------------------------------//

  string library_from_content( const string & content )
  {
    string::size_type pos( content.find( "www.boost.org/libs/" ) );

    if ( pos == string::npos ) return "unknown";

    string lib;
    pos += 19;
    while ( content[pos] != ' '
      && content[pos] != '/'
      && content[pos] != '\n'
      && content[pos] != '\r'
      && content[pos] != '\t' ) lib += content[pos++];
    return lib;
  }

//  find_signature  ----------------------------------------------------------//

  bool find_signature( const path & file_path,
    const boost::inspect::string_set & signatures )
  {
    string name( file_path.leaf() );
    if ( signatures.find( name ) == signatures.end() )
    {
      string::size_type pos( name.rfind( '.' ) );
      if ( pos == string::npos
        || signatures.find( name.substr( pos ) )
          == signatures.end() ) return false;
    }
    return true;
  }

//  load_content  ------------------------------------------------------------//

  void load_content( const path & file_path, string & target )
  {
    target = "";

    if ( !find_signature( file_path, content_signatures ) ) return;

    fs::ifstream fin( file_path );
    if ( !fin )
      throw string( "could not open input file: " ) + file_path.string();
    std::getline( fin, target, '\0' ); // read the whole file
  }

//  check  -------------------------------------------------------------------//

  void check( const string & lib,
    const path & pth, const string & content, const inspector_list & insp_list )
  {
    // invoke each inspector
    for ( inspector_list::const_iterator itr = insp_list.begin();
      itr != insp_list.end(); ++itr )
    {
      itr->inspector->inspect( lib, pth ); // always call two-argument form
      if ( find_signature( pth, itr->inspector->signatures() ) )
      {
          itr->inspector->inspect( lib, pth, content );
      }
    }
  }

//  visit_all  ---------------------------------------------------------------//

  void visit_all( const string & lib,
    const path & dir_path, const inspector_list & insps )
  {
    ++directory_count;

    for ( hack::cvs_iterator itr( dir_path ); itr != end_itr; ++itr )
    {

      if ( fs::is_directory( *itr ) )
      {
        if ( visit_predicate( *itr ) )
        {
          string cur_lib( boost::inspect::impute_library( *itr ) );
          check( cur_lib, *itr, "", insps );
          visit_all( cur_lib, *itr, insps );
        }
      }
      else
      {
        ++file_count;
        string content;
        load_content( *itr, content );
        check( lib == "unknown"
          ? library_from_content( content ) : lib, *itr, content, insps );
      }
    }
  }

//  display_summary_helper  --------------------------------------------------//

  void display_summary_helper( const string & current_library, int err_count )
  {
    std::cout << "  <tr><td><a href=\"#" 
              << current_library
              << "\">" << current_library
              << "</a></td><td align=\"center\">"
              << err_count << "</td></tr>\n";
  }
  
//  display_summary  ---------------------------------------------------------//

  void display_summary()
  {
    string current_library( msgs.begin()->library ); 
    int err_count = 0;
    for ( error_msg_vector::iterator itr ( msgs.begin() );
      itr != msgs.end(); ++itr )
    {
      if ( current_library != itr->library )
      {
        display_summary_helper( current_library, err_count );
        current_library = itr->library;
        err_count = 0;
      }
      ++err_count;
    }
    display_summary_helper( current_library, err_count );
  }


//  display_details  ---------------------------------------------------------//

  void display_details()
  {

    // display error messages with group indication
    error_msg current;
    string sep;
    bool first = true;
    for ( error_msg_vector::iterator itr ( msgs.begin() );
      itr != msgs.end(); ++itr )
    {
      if ( current.library != itr->library )
      {
        if ( !first ) std::cout << "</pre>\n";
        std::cout << "\n<h3><a name=\"" << itr->library
                  << "\">" << itr->library << "</a></h3>\n<pre>";
      }
      if ( current.library != itr->library
        || current.rel_path != itr->rel_path )
      {
        std::cout << "\n";
        std::cout << itr->rel_path;
        sep = ": ";
      }
      if ( current.library != itr->library
        || current.rel_path != itr->rel_path
        || current.msg != itr->msg )
      {
        std::cout << sep << itr->msg;
        sep = ", ";
      }
      current.library = itr->library;
      current.rel_path = itr->rel_path;
      current.msg = itr->msg;
      first = false;
   }
   std::cout << "</pre>\n";
  }

} // unnamed namespace

namespace boost
{
  namespace inspect
  {

//  register_signature  ------------------------------------------------------//

    void inspector::register_signature( const string & signature )
    {
      m_signatures.insert( signature );
      content_signatures.insert( signature );
    }

//  error  -------------------------------------------------------------------//

    void inspector::error( const string & library_name,
      const path & full_path, const string & msg )
    {
      ++error_count;
      error_msg err_msg;
      err_msg.library = library_name;
      err_msg.rel_path = relative_to( full_path, fs::initial_path() );
      err_msg.msg = msg;
      msgs.push_back( err_msg );

//     std::cout << library_name << ": "
//        << full_path.string() << ": "
//        << msg << '\n';

    }

//  impute_library  ----------------------------------------------------------//

    string impute_library( const path & full_dir_path )
    {
      path relative( relative_to( full_dir_path, fs::initial_path() ) );
      if ( relative.empty() ) return "boost-root";
      string first( *relative.begin() );
      string second =  // borland 5.61 requires op=  
        ++relative.begin() == relative.end()
          ? string() : *++relative.begin();

      if ( first == "boost" )
        return second.empty() ? string( "unknown" ) : second;

      return (( first == "libs" || first == "tools" ) && !second.empty())
        ? second : first;
    }

  } // namespace inspect
} // namespace boost

//  cpp_main()  --------------------------------------------------------------//

int cpp_main( int argc, char * argv[] )
{
  fs::initial_path();

  inspector_list inspectors;

  inspectors.push_back( inspector_element( new boost::inspect::copyright_check ) );
  inspectors.push_back( inspector_element( new boost::inspect::crlf_check ) );
  inspectors.push_back( inspector_element( new boost::inspect::link_check ) );
  inspectors.push_back( inspector_element( new boost::inspect::long_name_check ) );
  inspectors.push_back( inspector_element( new boost::inspect::tab_check ) );

  visit_all( "boost-root", fs::initial_path(), inspectors );

  // close
  for ( inspector_list::iterator itr = inspectors.begin();
        itr != inspectors.end(); ++itr )
  {
    itr->inspector->close();
  }

  char run_date[128];
  std::time_t tod;
  std::time( &tod );
  std::strftime( run_date, sizeof(run_date),
    "%X UTC, %A %d %B %Y", std::gmtime( &tod ) );

  std::cout << "<html>\n"
          "<head>\n"
          "<title>Boost Inspection Report</title>\n"
          "</head>\n"
          "<body bgcolor=\"#ffffff\" text=\"#000000\">\n"
          "<table border=\"0\">\n"
          "<tr>\n"
          "<td><img border=\"0\" src=\"../c++boost.gif\" width=\"277\" "
          "height=\"86\"></td>\n"
          "<td align=\"center\">\n"
          "<h1>Boost Inspection Report</h1>\n"
          "<b>Run Date:</b> " << run_date  << "\n"
          "</td>\n"
          "</table>\n"
          "<p>An <a href=\"http://www.boost.org/tools/inspect/index.html\">inspection\n" 
          "program</a> checks each file in the current Boost CVS for various problems,\n" 
          "generating this web page as output. Problems detected include tabs in files,\n" 
          "missing copyrights, broken URL's, and similar misdemeanors.</p>\n"
          ;

  std::cout << "<h2>Totals</h2>\n<pre>"
            << file_count << " files scanned\n"
            << directory_count << " directories scanned\n"
            << error_count << " problems reported\n"
            << "\nproblem counts:\n";

  for ( inspector_list::iterator itr = inspectors.begin();
        itr != inspectors.end(); ++itr )
  {
    itr->inspector.reset();
  }

  std::cout << "</pre>\n"
          "<h2>Summary</h2>\n"
          "<table border=\"1\" cellpadding=\"5\" cellspacing=\"0\">\n"
          "  <tr>\n"
          "    <td><b>Library</b></td>\n"
          "    <td><b>Problems</b></td>\n"
          "  </tr>\n"
          ;

  std::sort( msgs.begin(), msgs.end() );

  display_summary();

  std::cout << "</table>\n"
               "<h2>Details</h2>\n";

  display_details();

  std::cout << "</body>\n"
               "</html>\n";
  return 0;
}
