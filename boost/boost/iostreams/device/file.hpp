// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

//
// Contains wrappers for standard file buffers, together
// with convenience typedefs:
//      - basic_file_source
//      - basic_file_sink
//      - basic_file
//

#ifndef BOOST_IOSTREAMS_FILE_HPP_INCLUDED
#define BOOST_IOSTREAMS_FILE_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif              

#include <boost/iostreams/detail/disable_warnings.hpp>  // MSVC.

#include <fstream>
#include <locale>
#include <string>                                // pathnames, char_traits.
#include <boost/iostreams/categories.hpp>               
#include <boost/shared_ptr.hpp>

namespace boost { namespace iostreams {

template<typename Ch>
class basic_file {
public:
    typedef Ch char_type;
    struct category
        : public seekable_device_tag,
          public closable_tag,
          public localizable_tag
        { };
    basic_file( const std::string& path,
                std::ios::openmode mode =
                    std::ios::in | std::ios::out,
                std::ios::openmode base_mode =
                    std::ios::in | std::ios::out );
    std::streamsize read(char_type* s, std::streamsize n);
    void write(const char_type* s, std::streamsize n);
    std::streamoff seek( std::streamoff off, std::ios::seekdir way, 
                         std::ios::openmode mode = 
                             std::ios::in | std::ios::out );
    void close();
    void imbue(const std::locale& loc) { pimpl_->file_.pubimbue(loc);  }
private:
    struct impl {
        impl(const std::string& path, std::ios::openmode mode)
            { file_.open(path.c_str(), mode); }
        ~impl() { if (file_.is_open()) file_.close(); }
        std::basic_filebuf<Ch> file_;
    };
    shared_ptr<impl> pimpl_;
};

typedef basic_file<char>     file;
typedef basic_file<wchar_t>  wfile;

template<typename Ch>
struct basic_file_source : private basic_file<Ch> {
    typedef Ch char_type;
    struct category
        : public source_tag,
          public closable_tag
        { };
    using basic_file<Ch>::read;
    using basic_file<Ch>::close;
    basic_file_source( const std::string& path,
                       std::ios::openmode mode = std::ios::in )
        : basic_file<Ch>(path, mode & ~std::ios::out, std::ios::in) 
        { }
};

typedef basic_file_source<char>     file_source;
typedef basic_file_source<wchar_t>  wfile_source;

template<typename Ch>
struct basic_file_sink : private basic_file<Ch> {
    typedef Ch char_type;
    struct category
        : public sink_tag,
          public closable_tag
        { };
    using basic_file<Ch>::write;
    using basic_file<Ch>::close;
    basic_file_sink( const std::string& path,
                     std::ios::openmode mode = std::ios::out )
        : basic_file<Ch>(path, mode & ~std::ios::in, std::ios::out) 
        { }
};

typedef basic_file_sink<char>     file_sink;
typedef basic_file_sink<wchar_t>  wfile_sink;
                                 
//------------------Implementation of basic_file------------------------------//

template<typename Ch>
basic_file<Ch>::basic_file
    ( const std::string& path, std::ios::openmode mode, 
      std::ios::openmode base_mode )
    : pimpl_(new impl(path, mode | base_mode)) { }

template<typename Ch>
inline std::streamsize basic_file<Ch>::read
    (char_type* s, std::streamsize n)
{ return pimpl_->file_.sgetn(s, n); }

template<typename Ch>
inline void basic_file<Ch>::write
    (const char_type* s, std::streamsize n)
{ pimpl_->file_.sputn(s, n); }

template<typename Ch>
std::streamoff basic_file<Ch>::seek
    ( std::streamoff off, std::ios::seekdir way, 
      std::ios::openmode )
{ return pimpl_->file_.pubseekoff(off, way); }

template<typename Ch>
void basic_file<Ch>::close() { pimpl_->file_.close(); }

//----------------------------------------------------------------------------//

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/enable_warnings.hpp> // MSVC

#endif // #ifndef BOOST_IOSTREAMS_FILE_HPP_INCLUDED
