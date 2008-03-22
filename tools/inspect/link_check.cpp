//  link_check implementation  -----------------------------------------------//

//  Copyright Beman Dawes 2002.
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include "link_check.hpp"
#include "boost/regex.hpp"
#include "boost/filesystem/operations.hpp"
#include <cstdlib>

namespace fs = boost::filesystem;

namespace
{
  boost::regex url_regex(
    "<\\s*[^>]*\\s+(?:HREF|SRC)" // HREF or SRC
    "\\s*=\\s*(['\"])(.*?)\\1",
    boost::regbase::normal | boost::regbase::icase);

  // Decode percent encoded characters and html escapsed ampersands,
  // returns an empty string if there's an error.
  // The urls should really be fully HTML decoded at the beginning.
  std::string decode_url(std::string const& path) {
    std::string::size_type pos = 0, next;
    std::string result;
    result.reserve(path.length());

    while((next = path.find_first_of("&%", pos)) != std::string::npos) {
      result.append(path, pos, next - pos);
      pos = next;
      switch(path[pos]) {
        case '%': {
          if(path.length() - next < 3) return "";
          char hex[3] = { path[next + 1], path[next + 2], '\0' };
          char* end_ptr;
          result += (char) std::strtol(hex, &end_ptr, 16);
          if(*end_ptr) return "";
          pos = next + 3;
          break;
        }
        case '&': {
          if(path.substr(pos, 5) == "&amp;") {
            result += '&'; pos += 5;
          }
          else {
            result += '&'; pos += 1;
          }
          break;
        }
      }
    }

    result.append(path, pos, path.length());

    return result;
  }

} // unnamed namespace

namespace boost
{
  namespace inspect
  {

//  link_check constructor  --------------------------------------------------//

   link_check::link_check()
     : m_broken_errors(0), m_unlinked_errors(0), m_invalid_errors(0),
       m_bookmark_errors(0)
   {
   }

//  inspect (all)  -----------------------------------------------------------//

   void link_check::inspect(
      const string & /*library_name*/,
      const path & full_path )
    {
      // keep track of paths already encountered to reduce disk activity
      if ( !fs::is_directory( full_path ) )
        m_paths[ relative_to( full_path, fs::initial_path() ) ] |= m_present;
    }

//  inspect ( .htm, .html )  -------------------------------------------------//

   void link_check::inspect(
      const string & library_name,
      const path & full_path,   // example: c:/foo/boost/filesystem/path.hpp
      const string & contents )     // contents of file to be inspected
    {
      if (contents.find( "boostinspect:" "nounlinked" ) != string::npos)
          m_paths[ relative_to( full_path, fs::initial_path() ) ] |= m_nounlinked_errors;

      bool no_link_errors =
          (contents.find( "boostinspect:" "nolink" ) != string::npos);

      string::const_iterator start( contents.begin() );
      string::const_iterator end( contents.end() );
      boost::match_results< string::const_iterator > what;
      boost::match_flag_type flags = boost::match_default;

      while( boost::regex_search( start, end, what, url_regex, flags) )
      {
        // what[0] contains the whole string iterators.
        // what[2] contains the URL iterators.
        do_url( string( what[2].first, what[2].second ),
          library_name, full_path, no_link_errors );

        start = what[0].second; // update search position
        flags |= boost::match_prev_avail; // update flags
        flags |= boost::match_not_bob;
      }
    }

//  do_url  ------------------------------------------------------------------//

    void link_check::do_url( const string & url, const string & library_name,
      const path & source_path, bool no_link_errors )
        // precondition: source_path.is_complete()
    {
      if ( url[0] == '#'
        || url.find( "mailto:" ) == 0
        || url.find( "http:" ) == 0
        || url.find( "https:" ) == 0
        || url.find( "ftp:" ) == 0
        || url.find( "news:" ) == 0
        || url.find( "javascript:" ) == 0
        ) return;

      if ( url.find( "file:" ) == 0 )
      {
        if(!no_link_errors) {
          ++m_invalid_errors;
          error( library_name, source_path, string(name()) + " invalid URL (hardwired file): " + url );
        }
        return;
      }

      // detect characters banned by RFC2396:
      if ( !no_link_errors && url.find_first_of( " <>\"{}|\\^[]'" ) != string::npos )
      {
        ++m_invalid_errors;
        error( library_name, source_path, string(name()) + " invalid character in URL: " + url );
      }

      // strip url of bookmarks
      string plain_url( url );
      string::size_type pos( plain_url.find( '#' ) );
      if ( pos != string::npos )
      {
        plain_url.erase( pos );
        // detect characters banned by RFC2396 in bookmark:
        if ( !no_link_errors && url.find( '#', pos+1 ) != string::npos )
        {
          ++m_bookmark_errors;
          error( library_name, source_path, string(name()) + " invalid bookmark: " + url );
        }
      }

      string decoded_url = decode_url(plain_url);
      if(decoded_url.empty()) {
        if(!no_link_errors) {
          ++m_invalid_errors;
          error( library_name, source_path, string(name()) + " invalid URL: " + url );
        }
        return;
      }

      // strip url of references to current dir
      if ( decoded_url[0]=='.' && decoded_url[1]=='/' ) decoded_url.erase( 0, 2 );

      // url is relative source_path.branch()
      // convert to target_path, which is_complete()
      path target_path;
      try { target_path = source_path.branch_path() /= path( decoded_url, fs::no_check ); }
      catch ( const fs::filesystem_error & )
      {
        if(!no_link_errors) {
          ++m_invalid_errors;
          error( library_name, source_path, string(name()) + " invalid URL: " + url );
        }
        return;
      }

      // create a m_paths entry if necessary
      std::pair< const string, int > entry(
        relative_to( target_path, fs::initial_path() ), 0 );
      m_path_map::iterator itr( m_paths.find( entry.first ) );
      if ( itr == m_paths.end() )
      {
        if ( fs::exists( target_path ) ) entry.second = m_present;
        itr = m_paths.insert( entry ).first;
      }

      // itr now points to the m_paths entry
      itr->second |= m_linked_to;

      // if target isn't present, the link is broken
      if ( !no_link_errors && (itr->second & m_present) == 0 )
      {
        ++m_broken_errors;
        error( library_name, source_path, string(name()) + " broken link: " + url );
      }
    }

//  close  -------------------------------------------------------------------//

   void link_check::close()
   {
     for ( m_path_map::const_iterator itr = m_paths.begin();
       itr != m_paths.end(); ++itr )
     {
// std::clog << itr->first << " " << itr->second << "\n";
       if ( (itr->second & m_linked_to) != m_linked_to
         && (itr->second & m_nounlinked_errors) != m_nounlinked_errors
         && (itr->first.rfind( ".html" ) == itr->first.size()-5
          || itr->first.rfind( ".htm" ) == itr->first.size()-4)
         // because they may be redirectors, it is OK if these are unlinked:
         && itr->first.rfind( "index.html" ) == string::npos
         && itr->first.rfind( "index.htm" ) == string::npos )
       {
         ++m_unlinked_errors;
         path full_path( fs::initial_path() / path(itr->first, fs::no_check) );
         error( impute_library( full_path ), full_path, string(name()) + " unlinked file" );
       }
     }
   }

  } // namespace inspect
} // namespace boost

