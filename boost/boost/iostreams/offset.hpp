// (C) Copyright Jonathan Turkanis 2005.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_OFFSET_HPP_INCLUDED
#define BOOST_IOSTREAMS_OFFSET_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <algorithm>          // min.
#include <utility>            // pair.
#include <boost/cstdint.hpp>  // intmax_t.
#include <boost/config.hpp>   // DEDUCED_TYPENAME.
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/char_traits.hpp>
#include <boost/iostreams/detail/adapter/basic_adapter.hpp>
#include <boost/iostreams/detail/call_traits.hpp>
#include <boost/iostreams/detail/enable_if_stream.hpp>
#include <boost/iostreams/detail/error.hpp>
#include <boost/iostreams/detail/ios.hpp>     // failure.
#include <boost/iostreams/detail/select.hpp>
#include <boost/iostreams/operations.hpp>
#include <boost/iostreams/skip.hpp>
#include <boost/iostreams/traits.hpp>         // io_mode, is_direct.
#include <boost/mpl/bool.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_convertible.hpp>

#include <boost/iostreams/detail/config/disable_warnings.hpp> // VC7.1 C4244.

namespace boost { namespace iostreams {

namespace detail {

//
// Template name: offset_indirect_device.
// Description: Provides an offset view of an indirect Device.
// Template paramters:
//      Device - An indirect model of Device that models either Source or
//          SeekableDevice.
//
template<typename Device>
class offset_indirect_device : public basic_adapter<Device> {
private:
    typedef typename detail::param_type<Device>::type  param_type;
public:
    typedef typename io_char<Device>::type             char_type;
    struct io_category
        : io_mode<Device>::type,
          device_tag,
          closable_tag,
          flushable_tag,
          localizable_tag,
          optimally_buffered_tag
        { };
    offset_indirect_device( param_type dev, stream_offset off,
                            stream_offset len );
    std::streamsize read(char_type* s, std::streamsize n);
    std::streamsize write(const char_type* s, std::streamsize n);
    stream_offset seek(stream_offset off, BOOST_IOS::seekdir way);
private:
    stream_offset beg_, pos_, end_;
};

//
// Template name: offset_direct_device.
// Description: Provides an offset view of a Direct Device.
// Template paramters:
//      Device - A model of Direct and Device.
//
template<typename Device>
class offset_direct_device : public basic_adapter<Device> {
public:
    typedef typename io_char<Device>::type     char_type;
    typedef std::pair<char_type*, char_type*>  pair_type;
    struct io_category
        : io_mode<Device>::type,
          device_tag,
          direct_tag,
          closable_tag,
          localizable_tag
        { };
    offset_direct_device( const Device& dev, stream_offset off,
                          stream_offset len );
    pair_type input_sequence();
    pair_type output_sequence();
private:
    pair_type sequence(mpl::true_);
    pair_type sequence(mpl::false_);
    char_type *beg_, *end_;
};

//
// Template name: offset_filter.
// Description: Provides an offset view of a Filter.
// Template paramters:
//      Filter - An indirect model of Filter.
//
template<typename Filter>
class offset_filter : public basic_adapter<Filter> {
public:
    typedef typename io_char<Filter>::type char_type;
    struct io_category
        : io_mode<Filter>::type,
          filter_tag,
          multichar_tag,
          closable_tag,
          localizable_tag,
          optimally_buffered_tag
        { };
    offset_filter(const Filter& flt, stream_offset off, stream_offset len);

    template<typename Source>
    std::streamsize read(Source& src, char_type* s, std::streamsize n)
    {
        using namespace std;
        if (!open_)
            open(src);
        streamsize amt =
            (std::min) (n, static_cast<streamsize>(end_ - pos_));
        streamsize result = iostreams::read(this->component(), src, s, amt);
        if (result != -1)
            pos_ += result;
        return result;
    }

    template<typename Sink>
    std::streamsize write(Sink& snk, const char_type* s, std::streamsize n)
    {
        if (!open_)
            open(snk);
        if (pos_ + n >= end_)
            bad_write();
        std::streamsize result = 
            iostreams::write(this->component(), snk, s, n);
        pos_ += result;
        return result;
    }

    template<typename Device>
    stream_offset seek(Device& dev, stream_offset off, BOOST_IOS::seekdir way)
    {
        stream_offset next;
        if (way == BOOST_IOS::beg) {
            next = beg_ + off;
        } else if (way == BOOST_IOS::cur) {
            next = pos_ + off;
        } else {
            next = end_ + off;
        }
        if (next < beg_ || next >= end_)
            bad_seek();
        pos_ = this->component().seek(dev, next, BOOST_IOS::cur);
        return pos_ - beg_;
    }
private:
    template<typename Device>
    void open(Device& dev)
    {
        open_ = true;
        iostreams::skip(this->component(), dev, beg_);
    }
    stream_offset  beg_, pos_, end_;
    bool           open_;
};

template<typename T>
struct offset_traits
    : select<
          is_filter<T>,  offset_filter<T>,
          is_direct<T>,  offset_direct_device<T>,
          else_,         offset_indirect_device<T>
      >
    { };

} // End namespace detail.

template<typename T>
struct offset_view : public detail::offset_traits<T>::type {
    typedef typename detail::param_type<T>::type param_type;
    offset_view(param_type t, stream_offset off, stream_offset len)
        : detail::offset_traits<T>::type(t, off, len)
        { }
};

//--------------Implementation of offset--------------------------------------//

// Note: The following workarounds are patterned after resolve.hpp. It has not
// yet been confirmed that they are necessary.

#ifndef BOOST_IOSTREAMS_BROKEN_OVERLOAD_RESOLUTION //-------------------------//
# ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES //-------------------------------//

template<typename T>
offset_view<T> offset( const T& t, stream_offset off, stream_offset len
                       BOOST_IOSTREAMS_DISABLE_IF_STREAM(T) )
{ return offset_view<T>(t, off, len); }

template<typename Ch, typename Tr>
offset_view< std::basic_streambuf<Ch, Tr> >
offset(std::basic_streambuf<Ch, Tr>& sb)
{ return offset_view< std::basic_streambuf<Ch, Tr> >(sb); }

template<typename Ch, typename Tr>
offset_view< std::basic_istream<Ch, Tr> >
offset(std::basic_istream<Ch, Tr>& is)
{ return offset_view< std::basic_istream<Ch, Tr> >(is); }

template<typename Ch, typename Tr>
offset_view< std::basic_ostream<Ch, Tr> >
offset(std::basic_ostream<Ch, Tr>& os)
{ return offset_view< std::basic_ostream<Ch, Tr> >(os); }

template<typename Ch, typename Tr>
offset_view< std::basic_iostream<Ch, Tr> >
offset(std::basic_iostream<Ch, Tr>& io)
{ return offset_view< std::basic_iostream<Ch, Tr> >(io); }

# else // # ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES //---------------------//

template<typename T>
offset_view<T> offset( const T& t, stream_offset off, stream_offset len
                       BOOST_IOSTREAMS_DISABLE_IF_STREAM(T) )
{ return offset_view<T>(t, off, len); }

offset_view<std::streambuf> offset(std::streambuf& sb)
{ return offset_view<std::streambuf>(sb); }

offset_view<std::istream> offset(std::istream<Ch, Tr>& is)
{ return offset_view<std::istream>(is); }

offset_view<std::ostream> offset(std::ostream<Ch, Tr>& os)
{ return offset_view<std::ostream>(os); }

offset_view<std::iostream> offset(std::iostream<Ch, Tr>& io)
{ return offset_view<std::iostream>(io); }

# endif // # ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES //--------------------//
#else // #ifndef BOOST_IOSTREAMS_BROKEN_OVERLOAD_RESOLUTION //----------------//

template<typename T>
offset_view<T> offset(const T& t, mpl::true_)
{   // Bad overload resolution.
    return offset_view<T>(const_cast<T&>(t));
}

template<typename Mode, typename Ch, typename T>
offset_view<T> offset(const T& t, mpl::false_)
{ return offset_view<T>(t); }

template<typename T>
offset_view<T> offset(const T& t BOOST_IOSTREAMS_DISABLE_IF_STREAM(T))
{ return offset(t, is_std_io<T>()); }

# if !BOOST_WORKAROUND(__BORLANDC__, < 0x600) && \
     !BOOST_WORKAROUND(BOOST_MSVC, <= 1300) && \
     !defined(__GNUC__) // ---------------------------------------------------//

template<typename T>
offset_view<T> offset(T& t) { return offset_view<T>(t); }

# endif // Borland 5.x, VC6-7.0 or GCC 2.9x //--------------------------------//
#endif // #ifndef BOOST_IOSTREAMS_BROKEN_OVERLOAD_RESOLUTION //---------------//
//----------------------------------------------------------------------------//

namespace detail {

//--------------Implementation of offset_indirect_device----------------------//

template<typename Device>
offset_indirect_device<Device>::offset_indirect_device
    (param_type dev, stream_offset off, stream_offset len)
    : basic_adapter<Device>(dev), beg_(off), pos_(off), end_(off + len)
{
    if (len < 0 || off < 0)
        throw BOOST_IOSTREAMS_FAILURE("bad offset");
    iostreams::skip(this->component(), off);
}

template<typename Device>
inline std::streamsize offset_indirect_device<Device>::read
    (char_type* s, std::streamsize n)
{
    using namespace std;
    streamsize amt =
        (std::min) (n, static_cast<streamsize>(end_ - pos_));
    streamsize result = iostreams::read(this->component(), s, amt);
    if (result != -1)
        pos_ += result;
    return result;
}

template<typename Device>
inline std::streamsize offset_indirect_device<Device>::write
    (const char_type* s, std::streamsize n)
{
    if (pos_ + n >= end_)
        bad_write();
    streamsize result = iostreams::write(this->component(), s, n);
    pos_ += result;
    return result;
}

template<typename Device>
stream_offset offset_indirect_device<Device>::seek
    (stream_offset off, BOOST_IOS::seekdir way)
{
    stream_offset next;
    if (way == BOOST_IOS::beg) {
        next = beg_ + off;
    } else if (way == BOOST_IOS::cur) {
        next = pos_ + off;
    } else {
        next = end_ + off;
    }
    if (next < beg_ || next >= end_)
        bad_seek();
    pos_ = iostreams::seek(this->component(), next - pos_, BOOST_IOS::cur);
    return pos_ - beg_;
}

//--------------Implementation of offset_direct_device------------------------//

template<typename Device>
offset_direct_device<Device>::offset_direct_device
    (const Device& dev, stream_offset off, stream_offset len)
    : basic_adapter<Device>(dev), beg_(0), end_(0)
{
    std::pair<char_type*, char_type*> seq =
        sequence(is_convertible<io_category, input>());
    if (off < 0 || len < 0 || off + len > seq.second - seq.first)
        throw BOOST_IOSTREAMS_FAILURE("bad offset");
    beg_ = seq.first + off;
    end_ = seq.first + off + len;
}

template<typename Device>
typename offset_direct_device<Device>::pair_type
offset_direct_device<Device>::input_sequence()
{
    BOOST_STATIC_ASSERT((is_convertible<io_category, input>::value));
    return std::make_pair(beg_, end_);
}

template<typename Device>
typename offset_direct_device<Device>::pair_type
offset_direct_device<Device>::output_sequence()
{
    BOOST_STATIC_ASSERT((is_convertible<io_category, output>::value));
    return std::make_pair(beg_, end_);
}

template<typename Device>
typename offset_direct_device<Device>::pair_type
offset_direct_device<Device>::sequence(mpl::true_)
{ return iostreams::input_sequence(this->component()); }

template<typename Device>
typename offset_direct_device<Device>::pair_type
offset_direct_device<Device>::sequence(mpl::false_)
{ return iostreams::output_sequence(this->component()); }

//--------------Implementation of offset_filter-------------------------------//

template<typename Filter>
offset_filter<Filter>::offset_filter
    (const Filter& flt, stream_offset off, stream_offset len)
    : basic_adapter<Filter>(flt), beg_(off),
      pos_(off), end_(off + len), open_(false)
{
    if (len < 0 || off < 0)
        throw BOOST_IOSTREAMS_FAILURE("bad offset");
}

} // End namespace detail.

} } // End namespaces iostreams, boost.


#endif // #ifndef BOOST_IOSTREAMS_OFFSET_HPP_INCLUDED
