// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Inspired by fdstream.hpp, (C) Copyright Nicolai M. Josuttis 2001,
// available at http://www.josuttis.com/cppcode/fdstream.html.

#ifndef BOOST_IOSTREAMS_FILE_DESCRIPTOR_HPP_INCLUDED
#define BOOST_IOSTREAMS_FILE_DESCRIPTOR_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif              

#include <ios>                                        // openmodes.
#include <string>                                     // file pathnames.
#include <boost/iostreams/categories.hpp>             // tags.
#include <boost/iostreams/detail/config/auto_link.hpp>
#include <boost/iostreams/detail/config/dyn_link.hpp>

// Must be the last header.
#include <boost/config/abi_prefix.hpp>     

namespace boost { namespace iostreams {

class BOOST_IOSTREAMS_DECL file_descriptor {
public:
    typedef char char_type;
    struct io_category : public seekable_device_tag, closable_tag { };
    file_descriptor() : fd_(-1), close_(false) { }
    explicit file_descriptor(int fd, bool close = false) 
        : fd_(fd), close_(close) { }
    explicit file_descriptor( const std::string& path, 
                              std::ios::openmode mode =
                                  std::ios::in | std::ios::out,
                              std::ios::openmode base_mode =
                                  std::ios::in | std::ios::out )
    { open(path, mode, base_mode); }
    void open( const std::string& path, 
               std::ios::openmode =
                   std::ios::in | std::ios::out,
               std::ios::openmode base_mode =
                   std::ios::in | std::ios::out );
    std::streamsize read(char_type* s, std::streamsize n);
    void write(const char_type* s, std::streamsize n);
    std::streamoff seek(std::streamoff off, std::ios::seekdir way);
    void close();
private:
    int   fd_;
    bool  close_;
};

struct file_descriptor_source : private file_descriptor {
    typedef char char_type;
    struct io_category : public source_tag, closable_tag { };
    using file_descriptor::read;
    using file_descriptor::open;
    using file_descriptor::close;
    file_descriptor_source() { } 
    explicit file_descriptor_source(int fd, bool close = false) 
        : file_descriptor(fd, close) { }
    explicit file_descriptor_source( const std::string& path, 
                                     std::ios::openmode m = std::ios::in )
        : file_descriptor(path, m & ~std::ios::out, std::ios::in) 
        { }
};

struct file_descriptor_sink : private file_descriptor {
    typedef char char_type;
    struct io_category : public sink_tag, closable_tag { };
    using file_descriptor::write;
    using file_descriptor::open;
    using file_descriptor::close;
    file_descriptor_sink() { } 
    explicit file_descriptor_sink(int fd, bool close = false) 
        : file_descriptor(fd, close) { }
    explicit file_descriptor_sink( const std::string& path, 
                                   std::ios::openmode m = std::ios::out )
        : file_descriptor(path, m & ~std::ios::in, std::ios::out) 
        { }
};

} } // End namespaces iostreams, boost.

#include <boost/config/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // #ifndef BOOST_IOSTREAMS_FILE_DESCRIPTOR_HPP_INCLUDED
