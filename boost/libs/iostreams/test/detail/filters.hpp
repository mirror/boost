// (C) Copyright Jonathan Turkanis 2004
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Contains the definitions of several constants used by the test program.

#ifndef BOOST_IOSTREAMS_TEST_FILTERS_HPP_INCLUDED
#define BOOST_IOSTREAMS_TEST_FILTERS_HPP_INCLUDED

#include <boost/config.hpp>                 
#include <algorithm>                            // min.
#include <cctype>                               // to_upper, to_lower.
#include <cstdlib>                              // to_upper, to_lower (VC6).
#include <cstddef>                              // ptrdiff_t.
#include <boost/iostreams/concepts.hpp>
#include <boost/iostreams/constants.hpp>
#include <boost/iostreams/detail/buffer.hpp>
#include <boost/iostreams/detail/char_traits.hpp>
#include <boost/iostreams/detail/iostream.hpp>  // seekdir, streamsize.
#include <boost/iostreams/detail/streambuf.hpp>
#include <boost/iostreams/pipable.hpp>
#include <boost/type_traits/is_convertible.hpp>
#ifdef BOOST_NO_STDC_NAMESPACE
namespace std { using ::toupper; using ::tolower; }
#endif

namespace boost { namespace iostreams { namespace test {

struct toupper_filter : public input_filter {
    template<typename Source>
    int get(Source& s) { return std::toupper(boost::iostreams::get(s)); }
};
BOOST_IOSTREAMS_PIPABLE(toupper_filter, 0)

struct tolower_filter : public output_filter {
    template<typename Sink>
    void put(Sink& s, char c) { boost::iostreams::put(s, (char) std::tolower(c)); }
};
BOOST_IOSTREAMS_PIPABLE(tolower_filter, 0)

struct toupper_multichar_filter : public multichar_input_filter {
    template<typename Source>
    std::streamsize read(Source& s, char* buf, std::streamsize n)
        {
            std::streamsize result = boost::iostreams::read(s, buf, n);
            for (int z = 0; z < result; ++z)
                buf[z] = (char) std::toupper(buf[z]);
            return result;
        }
};
BOOST_IOSTREAMS_PIPABLE(toupper_multichar_filter, 0)

struct tolower_multichar_filter : public multichar_output_filter {
    template<typename Sink>
    void write(Sink& s, const char* buf, std::streamsize n)
        {
            for (std::streamsize z = 0; z < n; ++z)
                boost::iostreams::put(s, (char) std::tolower(buf[z]));
        }
};
BOOST_IOSTREAMS_PIPABLE(tolower_multichar_filter, 0)

// Note: The filter is given an internal buffer, unnecessary in this simple
// case, to test symmetric_filter_adapter.
struct toupper_symmetric_filter {
    typedef char char_type;
    toupper_symmetric_filter() : buf_(default_filter_buffer_size) 
    { 
        buf_.set(0, 0);
    }
    bool filter( const char*& src_begin, const char* src_end,
                 char*& dest_begin, char* dest_end, bool /* flush */ )
    {
        while ( can_read(src_begin, src_end) || 
                can_write(dest_begin, dest_end) ) 
        {
            if (can_read(src_begin, src_end)) read(src_begin, src_end);
            if (can_write(dest_begin, dest_end)) 
                write(dest_begin, dest_end);
        }
        return buf_.ptr() != buf_.eptr();
    }
    void close() { buf_.set(0, 0); }
    void read(const char*& src_begin, const char* src_end)
    {
        std::ptrdiff_t count =
            std::min<std::ptrdiff_t>( src_end - src_begin,
                                      buf_.size() - 
                                          (buf_.eptr() - buf_.data()) );
        while (count-- > 0)
            *buf_.eptr()++ = std::toupper(*src_begin++);
    }
    void write(char*& dest_begin, char* dest_end)
    {
        std::ptrdiff_t count =
            std::min<std::ptrdiff_t>( dest_end - dest_begin,
                                      buf_.eptr() - buf_.ptr() );
        while (count-- > 0)
            *dest_begin++ = *buf_.ptr()++;
        if (buf_.ptr() == buf_.eptr())
            buf_.set(0, 0);
    }
    bool can_read(const char*& src_begin, const char* src_end)
    { return src_begin != src_end && buf_.eptr() != buf_.end(); }
    bool can_write(char*& dest_begin, char* dest_end)
    { return dest_begin != dest_end && buf_.ptr() != buf_.eptr(); }
    iostreams::detail::buffer<char> buf_;
};
BOOST_IOSTREAMS_PIPABLE(toupper_symmetric_filter, 0)

struct identity_seekable_filter : filter<seekable> {
    template<typename Source>
    int get(Source& s) { return boost::iostreams::get(s); }

    template<typename Sink>
    void put(Sink& s, char c) { boost::iostreams::put(s, c); }

    template<typename Device>
    std::streamoff seek(Device& d, std::streamoff off, BOOST_IOS::seekdir way)
    { return boost::iostreams::seek(d, off, way); }
};
BOOST_IOSTREAMS_PIPABLE(identity_seekable_filter, 0)

struct identity_seekable_multichar_filter : multichar_filter<seekable> {
    template<typename Source>
    std::streamsize read(Source& s, char* buf, std::streamsize n)
    { return boost::iostreams::read(s, buf, n); }
    template<typename Sink>
    void write(Sink& s, const char* buf, std::streamsize n)
    { boost::iostreams::write(s, buf, n); }
    template<typename Device>
    std::streamoff seek(Device& d, std::streamoff off, BOOST_IOS::seekdir way)
    { return boost::iostreams::seek(d, off, way); }
};
BOOST_IOSTREAMS_PIPABLE(identity_seekable_multichar_filter, 0)

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_TEST_FILTERS_HPP_INCLUDED
