// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_CONCEPT_ADAPTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CONCEPT_ADAPTER_HPP_INCLUDED

#include <boost/iostreams/detail/disable_warnings.hpp>  // MSVC.

#include <boost/config.hpp>                             // SFINAE.
#include <boost/iostreams/concepts.hpp>
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/dispatch.hpp>
#include <boost/iostreams/detail/error.hpp>
#include <boost/iostreams/detail/ios_traits.hpp>
#include <boost/iostreams/device/null.hpp>
#include <boost/iostreams/io_traits.hpp>
#include <boost/iostreams/is_device.hpp>
#include <boost/iostreams/operations.hpp>
#include <boost/mpl/if.hpp>
#include <boost/static_assert.hpp>

namespace boost { namespace iostreams { namespace detail {

template<typename Category> struct device_wrapper_impl;
template<typename Category> struct flt_wrapper_impl;

template<typename T>
class concept_adapter {
private:
    typedef typename
            mpl::if_<
                is_std_io<T>, T&, T
            >::type                                    storage_type;
    typedef typename dispatch<T, input, output>::type  input_tag;
    typedef typename dispatch<T, output, input>::type  output_tag;
    typedef typename
            mpl::if_<
                is_device<T>,
                device_wrapper_impl<input_tag>,
                flt_wrapper_impl<input_tag>
            >::type                                    input_impl;
    typedef typename
            mpl::if_<
                is_device<T>,
                device_wrapper_impl<output_tag>,
                flt_wrapper_impl<output_tag>
            >::type                                    output_impl;
    typedef typename
            mpl::if_<
                is_device<T>,
                device_wrapper_impl<any_tag>,
                flt_wrapper_impl<any_tag>
            >::type                                    any_impl;
public:
    typedef BOOST_IOSTREAMS_CHAR_TYPE(T)               char_type;
    typedef BOOST_IOSTREAMS_CATEGORY(T)                category;

    concept_adapter(const reference_wrapper<T>& ref) : t_(ref.get())
    { BOOST_STATIC_ASSERT(is_std_io<T>::value); }
    concept_adapter(const T& t) : t_(t)
    { BOOST_STATIC_ASSERT(!is_std_io<T>::value); }

    T& operator*() { return t_; }
    T* operator->() { return &t_; }

    std::streamsize read(char_type* s, std::streamsize n)
    { return this->read(s, n, (basic_null_source<char_type>*) 0); }

    template<typename Source>
    std::streamsize read(char_type* s, std::streamsize n, Source* src)
    { return input_impl::read(t_, src, s, n); }

    void write(const char_type* s, std::streamsize n)
    { this->write(s, n, (basic_null_sink<char_type>*) 0); }

    template<typename Sink>
    void write(const char_type* s, std::streamsize n, Sink* snk)
    { output_impl::write(t_, snk, s, n); }

    std::streamoff seek( std::streamoff off, std::ios::seekdir way,
                         std::ios::openmode which )
    { 
        return this->seek( off, way, which, 
                           (basic_null_device<char_type, seekable>*) 0); 
    }

    template<typename Device>
    std::streamoff seek( std::streamoff off, std::ios::seekdir way,
                         std::ios::openmode which, Device* dev )
    { return any_impl::seek(t_, dev, off, way, which); }

    void flush(std::basic_streambuf<char_type>* sb)
    { if (sb) sb->pubsync(); }

    void close(std::ios::openmode which)
    { this->close(which, (basic_null_device<char_type, seekable>*) 0); }

    template<typename Device>
    void close(std::ios::openmode which, Device* dev)
    { any_impl::close(t_, dev, which); }

    template<typename Locale> // Avoid dependency on <locale>
    void imbue(const Locale& loc) { iostreams::imbue(t_, loc); }
public:
    storage_type t_;
};

//------------------Specializations of device_wrapper_impl--------------------//

template<>
struct device_wrapper_impl<any_tag> {
    template<typename Device, typename Dummy>
    static std::streamoff 
    seek( Device& dev, Dummy*, std::streamoff off, 
          std::ios::seekdir way, std::ios::openmode which )
    { 
        typedef BOOST_IOSTREAMS_CATEGORY(Device) category;
        return seek(dev, off, way, which, category()); 
    }

    template<typename Device>
    static std::streamoff 
    seek( Device&, std::streamoff, std::ios::seekdir, 
          std::ios::openmode, any_tag )
    { 
        throw cant_seek(); 
    }

    template<typename Device>
    static std::streamoff 
    seek( Device& dev, std::streamoff off, 
          std::ios::seekdir way, std::ios::openmode which, 
          random_access )
    { 
        return iostreams::seek(dev, off, way, which); 
    }

    template<typename Device, typename Dummy>
    static void close(Device& dev, Dummy*, std::ios::openmode which)
    { iostreams::close(dev, which); }
};


template<>
struct device_wrapper_impl<input> : device_wrapper_impl<any_tag>  {
    template<typename Device, typename Dummy>
    static std::streamsize
    read( Device& dev, Dummy*, BOOST_IOSTREAMS_CHAR_TYPE(Device)* s,
          std::streamsize n )
    { return iostreams::read(dev, s, n); }

    template<typename Device, typename Dummy>
    static void write( Device&, Dummy*, const BOOST_IOSTREAMS_CHAR_TYPE(Device)*,
                       std::streamsize )
    { throw cant_write(); }
};

template<>
struct device_wrapper_impl<output> {
    template<typename Device, typename Dummy>
    static std::streamsize
    read(Device&, Dummy*, BOOST_IOSTREAMS_CHAR_TYPE(Device)*, std::streamsize)
    { throw cant_read(); }

    template<typename Device, typename Dummy>
    static void write( Device& dev, Dummy*,
                       const BOOST_IOSTREAMS_CHAR_TYPE(Device)* s,
                       std::streamsize n )
    { iostreams::write(dev, s, n); }
};

//------------------Specializations of flt_wrapper_impl--------------------//

template<>
struct flt_wrapper_impl<any_tag> {
    template<typename Filter, typename Device>
    static std::streamoff
    seek( Filter& f, Device* dev, std::streamoff off,
          std::ios::seekdir way, std::ios::openmode which )
    {
        typedef BOOST_IOSTREAMS_CATEGORY(Filter) category;
        return seek(f, dev, off, way, which, category());
    }

    template<typename Filter, typename Device>
    static std::streamoff
    seek( Filter&, Device*, std::streamoff,
          std::ios::seekdir, std::ios::openmode, any_tag )
    { throw cant_seek(); }

    template<typename Filter, typename Device>
    static std::streamoff
    seek( Filter& f, Device* dev, std::streamoff off,
          std::ios::seekdir way, std::ios::openmode which,
          random_access tag )
    {
        typedef BOOST_IOSTREAMS_CATEGORY(Filter) category;
        return seek(f, dev, off, way, which, tag, category());
    }

    template<typename Filter, typename Device>
    static std::streamoff
    seek( Filter& f, Device* dev, std::streamoff off,
          std::ios::seekdir way, std::ios::openmode which,
          random_access, any_tag )
    { return f.seek(*dev, off, way); }

    template<typename Filter, typename Device>
    static std::streamoff
    seek( Filter& f, Device* dev, std::streamoff off,
          std::ios::seekdir way, std::ios::openmode which,
          random_access, two_sequence )
    { return f.seek(*dev, off, way);  }

    template<typename Filter, typename Device>
    static void close(Filter& f, Device* dev, std::ios::openmode which)
    { iostreams::close(f, *dev, which); }
};

template<>
struct flt_wrapper_impl<input> {
    template<typename Filter, typename Source>
    static std::streamsize
    read( Filter& f, Source* src, BOOST_IOSTREAMS_CHAR_TYPE(Filter)* s,
          std::streamsize n )
    { return iostreams::read(f, *src, s, n); }

    template<typename Filter, typename Sink>
    static void write( Filter&, Sink*, const BOOST_IOSTREAMS_CHAR_TYPE(Filter)*,
                       std::streamsize)
    { throw cant_write(); }
};

template<>
struct flt_wrapper_impl<output> {
    template<typename Filter, typename Source>
    static std::streamsize
    read(Filter&, Source*, BOOST_IOSTREAMS_CHAR_TYPE(Filter)*,std::streamsize)
    { throw cant_read(); }

    template<typename Filter, typename Sink>
    static void write( Filter& f, Sink* snk,
                       const BOOST_IOSTREAMS_CHAR_TYPE(Filter)* s,
                       std::streamsize n )
    { iostreams::write(f, *snk, s, n); }
};

//----------------------------------------------------------------------------//

} } } // End namespaces detail, iostreams, boost.

#include <boost/iostreams/detail/enable_warnings.hpp>  // MSVC.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CONCEPT_ADAPTER_HPP_INCLUDED
