// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)
// See http://www.boost.org/libs/iostreams for documentation.

// This material is heavily indebted to the discussion and code samples in
// A. Langer and K. Kreft, "Standard C++ IOStreams and Locales",
// Addison-Wesley, 2000, pp. 228-43.

#ifndef BOOST_IOSTREAMS_DETAIL_INDIRECT_STREAMBUF_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_INDIRECT_STREAMBUF_HPP_INCLUDED

#include <algorithm>                             // min, max.
#include <cassert>
#include <exception>
#include <boost/config.hpp>                      // Member template friends.
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/constants.hpp>
#include <boost/iostreams/detail/adapter/concept_adapter.hpp>
#include <boost/iostreams/detail/buffer.hpp>
#include <boost/iostreams/detail/config/wide_streams.hpp>
#include <boost/iostreams/detail/double_object.hpp>
#include <boost/iostreams/detail/ios.hpp>
#include <boost/iostreams/detail/push.hpp>
#include <boost/iostreams/detail/streambuf/linked_streambuf.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/iostreams/operations.hpp>
#include <boost/mpl/if.hpp>
#include <boost/optional.hpp>
#include <boost/type_traits/is_convertible.hpp>

#include <boost/iostreams/detail/config/disable_warnings.hpp>  // MSVC, Borland 5.x

namespace boost { namespace iostreams { namespace detail {

//
// Description: The implementation of basic_streambuf used by chains.
//
template<typename T, typename Tr, typename Alloc, typename Mode>
class indirect_streambuf
    : public linked_streambuf<BOOST_DEDUCED_TYPENAME io_char<T>::type, Tr>
{
public:
    typedef typename io_char<T>::type                         char_type;
    BOOST_IOSTREAMS_STREAMBUF_TYPEDEFS(Tr)
private:
    typedef typename io_category<T>::type                     io_category;
    typedef concept_adapter<T>                                wrapper;
    typedef detail::basic_buffer<char_type, Alloc>            buffer_type;
    typedef indirect_streambuf<T, Tr, Alloc, Mode>            my_type;
    typedef detail::linked_streambuf<char_type, traits_type>  base_type;
#ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES
    typedef std::basic_streambuf<char_type, traits_type>      streambuf_type;
#else
    typedef std::streambuf                                    streambuf_type;
#endif
public:
    indirect_streambuf();

    void open(const T& t BOOST_IOSTREAMS_PUSH_PARAMS());
    bool is_open();
    void close();
    bool auto_close() const;
    void set_auto_close(bool close);

    //----------Direct filter or device access--------------------------------//

    T& operator*() { return *obj(); }
    T* operator->() { return &*obj(); }
protected:
#if !BOOST_WORKAROUND(__GNUC__, == 2)
    BOOST_IOSTREAMS_USING_PROTECTED_STREAMBUF_MEMBERS(base_type)
#endif

    //----------virtual functions---------------------------------------------//

#ifndef BOOST_IOSTREAMS_NO_LOCALE
    void imbue(const std::locale& loc);
#endif
    int_type underflow();
    int_type pbackfail(int_type c);
    std::streamsize xsgetn(char_type* s, std::streamsize n);
    int_type overflow(int_type c);
    std::streamsize xsputn(const char_type* s, std::streamsize n);
    int sync();
    pos_type seekoff( off_type off, BOOST_IOS::seekdir way,
                      BOOST_IOS::openmode which );
    pos_type seekpos(pos_type sp, BOOST_IOS::openmode which);
    void close(BOOST_IOS::openmode m); // Declared in linked_streambuf.
    void set_next(streambuf_type* next); // Declared in linked_streambuf.
private:

    //----------Accessor functions--------------------------------------------//

    wrapper& obj() { return *storage_; }
    streambuf_type* next() const { return next_; }
    buffer_type& in() { return buffer_.first(); }
    buffer_type& out() { return buffer_.second(); }
    bool can_read() const { return is_convertible<Mode, input>::value; }
    bool can_write() const { return is_convertible<Mode, output>::value; }
    bool output_buffered() const { return (flags_ & f_output_buffered) != 0; }
    bool shared_buffer() const { return is_convertible<Mode, seekable>::value; }
    void set_flags(int f) { flags_ = f; }

    //----------State changing functions--------------------------------------//
    virtual void init_get_area();
    virtual void init_put_area();

    //----------Utility function----------------------------------------------//

    pos_type seek_impl( off_type off, BOOST_IOS::seekdir way,
                        BOOST_IOS::openmode which );
    void sync_impl();
    void close_impl(BOOST_IOS::openmode);

    enum {
        f_open             = 1,
        f_input_closed     = f_open << 1,
        f_output_closed    = f_input_closed << 1,
        f_output_buffered  = f_output_closed << 1,
        f_auto_close       = f_output_buffered << 1
    };

    optional<wrapper>           storage_;
    streambuf_type*             next_;
    double_object<
        buffer_type,
        is_convertible<
            Mode,
            two_sequence
        >
    >                           buffer_;
    std::streamsize             pback_size_;
    int                         flags_;
};

//--------------Implementation of indirect_streambuf--------------------------//

template<typename T, typename Tr, typename Alloc, typename Mode>
indirect_streambuf<T, Tr, Alloc, Mode>::indirect_streambuf()
    : next_(0), pback_size_(0), flags_(f_auto_close) { }

//--------------Implementation of open, is_open and close---------------------//

template<typename T, typename Tr, typename Alloc, typename Mode>
void indirect_streambuf<T, Tr, Alloc, Mode>::open
    (const T& t, int buffer_size, int pback_size)
{
    using namespace std;

    // Normalize buffer sizes.
    buffer_size =
        (buffer_size != -1) ?
        buffer_size :
        is_filter<T>::value ?
            default_filter_buffer_size :
            default_buffer_size;
    pback_size =
        (pback_size != -1) ?
        pback_size :
        default_pback_buffer_size;

    // Construct input buffer.
    if (can_read()) {
        pback_size_ = (std::max)(2, pback_size); // STLPort needs 2.
        streamsize size =
            pback_size_ +
            ( buffer_size ? buffer_size: 1 );
        in().resize(size);
        if (!shared_buffer())
            init_get_area();
    }

    // Construct output buffer.
    if (can_write() && !shared_buffer()) {
        if (buffer_size != 0)
            out().resize(buffer_size);
        init_put_area();
    }

    storage_ = wrapper(t);
    flags_ |= f_open;
    if (can_write() && buffer_size)
        flags_ |= f_output_buffered;
}

template<typename T, typename Tr, typename Alloc, typename Mode>
inline bool indirect_streambuf<T, Tr, Alloc, Mode>::is_open()
{ return (flags_ & f_open) != 0; }

template<typename T, typename Tr, typename Alloc, typename Mode>
void indirect_streambuf<T, Tr, Alloc, Mode>::close()
{
    using namespace std;
    if ((flags_ & f_input_closed) == 0)
        try { close(BOOST_IOS::in); } catch (std::exception&) { }
    if ((flags_ & f_output_closed) == 0)
        try { close(BOOST_IOS::out); } catch (std::exception&) { }
    storage_.reset();
    flags_ = 0;
}

template<typename T, typename Tr, typename Alloc, typename Mode>
bool indirect_streambuf<T, Tr, Alloc, Mode>::auto_close() const
{ return (flags_ & f_auto_close) != 0; }

template<typename T, typename Tr, typename Alloc, typename Mode>
void indirect_streambuf<T, Tr, Alloc, Mode>::set_auto_close(bool close)
{ flags_ = (flags_ & ~f_auto_close) | (close ? f_auto_close : 0); }

//--------------Implementation virtual functions------------------------------//

#ifndef BOOST_IOSTREAMS_NO_LOCALE
template<typename T, typename Tr, typename Alloc, typename Mode>
void indirect_streambuf<T, Tr, Alloc, Mode>::imbue(const std::locale& loc)
{
    if (is_open()) {
        obj().imbue(loc);
        if (next_)
            next_->pubimbue(loc);
    }
}
#endif

template<typename T, typename Tr, typename Alloc, typename Mode>
typename indirect_streambuf<T, Tr, Alloc, Mode>::int_type
indirect_streambuf<T, Tr, Alloc, Mode>::underflow()
{
    using namespace std;
    if (!gptr()) init_get_area();
    buffer_type& buf = in();
    if (gptr() < egptr()) return traits_type::to_int_type(*gptr());

    // Fill putback buffer.
    streamsize keep = (std::min)( static_cast<streamsize>(gptr() - eback()),
                                  pback_size_ );
    if (keep)
        traits_type::move( buf.data() + (pback_size_ - keep),
                           gptr() - keep, keep );

    // Set pointers to reasonable values in case read throws.
    setg( buf.data() + pback_size_ - keep,
          buf.data() + pback_size_,
          buf.data() + pback_size_ );

    // Read from source.
    streamsize chars =
        obj().read(buf.data() + pback_size_, buf.size() - pback_size_, next_);
    setg(eback(), gptr(), buf.data() + pback_size_ + chars);
    return chars != 0 ?
        traits_type::to_int_type(*gptr()) :
        traits_type::eof();
}

template<typename T, typename Tr, typename Alloc, typename Mode>
std::streamsize indirect_streambuf<T, Tr, Alloc, Mode>::xsgetn
    (char_type* s, std::streamsize n)
{
    using namespace std;
    if (!gptr()) init_get_area();
    buffer_type& buf = in();
    streamsize avail =
        (std::min)(n, static_cast<streamsize>(egptr() - gptr()));

    // Fill request from buffer.
    if (avail) {
        traits_type::copy(s, gptr(), avail);
        gbump((int) avail);
        if (avail == n) return avail;
    }

    // Read from source.
    streamsize amt = obj().read(s + avail, n - avail, next_);

    // Fill putback buffer:
    streamsize keep = (std::min)(avail + amt, pback_size_);
    streamsize overflow = (std::max)((streamsize) 0, keep - amt);
    if (overflow > 0)
        traits_type::move( buf.data() + pback_size_ - keep,
                           gptr() - overflow, overflow );
    if (keep)
        traits_type::copy( buf.data() + pback_size_ - keep + overflow,
                           s + avail + amt - keep + overflow,
                           (keep - overflow) );
    setg( buf.data() + pback_size_ - keep,
          buf.data() + pback_size_,
          buf.data() + pback_size_ );
    return avail + amt;
}

template<typename T, typename Tr, typename Alloc, typename Mode>
typename indirect_streambuf<T, Tr, Alloc, Mode>::int_type
indirect_streambuf<T, Tr, Alloc, Mode>::pbackfail(int_type c)
{
    if (gptr() != eback()) {
        gbump(-1);
        if (!traits_type::eq_int_type(c, traits_type::eof()))
            *gptr() = traits_type::to_char_type(c);
        return traits_type::not_eof(c);
    } else {
        throw bad_putback();
    }
}

template<typename T, typename Tr, typename Alloc, typename Mode>
typename indirect_streambuf<T, Tr, Alloc, Mode>::int_type
indirect_streambuf<T, Tr, Alloc, Mode>::overflow(int_type c)
{
    if ( output_buffered() && pptr() == 0 ||
         shared_buffer() && gptr() != 0 )
    {
        init_put_area();
    }
    if (!traits_type::eq_int_type(c, traits_type::eof())) {
        if (output_buffered()) {
            if (pptr() == epptr())
                sync_impl();
            *pptr() = traits_type::to_char_type(c);
            pbump(1);
        } else {
            char_type d = traits_type::to_char_type(c);
            obj().write(&d, 1, next_);
            return c;
        }
    }
    return traits_type::not_eof(c);
}

template<typename T, typename Tr, typename Alloc, typename Mode>
std::streamsize indirect_streambuf<T, Tr, Alloc, Mode>::xsputn
    (const char_type* s, std::streamsize n)
{
    if ( output_buffered() && pptr() == 0 ||
         shared_buffer() && gptr() != 0 )
    {
        init_put_area();
    }
    if (output_buffered()) {
        if (n < epptr() - pptr()) {
            traits_type::copy(pptr(), s, n);
            pbump((int) n);
        } else {
            sync_impl();
            obj().write(s, n, next_);
        }
    } else {
        obj().write(s, n, next_);
    }
    return n;
}

template<typename T, typename Tr, typename Alloc, typename Mode>
int indirect_streambuf<T, Tr, Alloc, Mode>::sync()
{
    try { // sync() is no-throw.
        sync_impl();
        obj().flush(next_);
        return 0;
    } catch (std::exception&) { return -1; }
}

template<typename T, typename Tr, typename Alloc, typename Mode>
inline typename indirect_streambuf<T, Tr, Alloc, Mode>::pos_type
indirect_streambuf<T, Tr, Alloc, Mode>::seekoff
    (off_type off, BOOST_IOS::seekdir way, BOOST_IOS::openmode which)
{ return seek_impl(off, way, which); }

template<typename T, typename Tr, typename Alloc, typename Mode>
inline typename indirect_streambuf<T, Tr, Alloc, Mode>::pos_type
indirect_streambuf<T, Tr, Alloc, Mode>::seekpos
    (pos_type sp, BOOST_IOS::openmode)
{ return seek_impl(sp, BOOST_IOS::beg, BOOST_IOS::in | BOOST_IOS::out); }

template<typename T, typename Tr, typename Alloc, typename Mode>
typename indirect_streambuf<T, Tr, Alloc, Mode>::pos_type
indirect_streambuf<T, Tr, Alloc, Mode>::seek_impl
    (off_type off, BOOST_IOS::seekdir way, BOOST_IOS::openmode which)
{
    if (pptr() != 0) sync();
    if (way == BOOST_IOS::cur && gptr())
        off -= static_cast<off_type>(egptr() - gptr());
    setg(0, 0, 0);
    setp(0, 0);
    return obj().seek(off, way, which, next_);
}

template<typename T, typename Tr, typename Alloc, typename Mode>
inline void indirect_streambuf<T, Tr, Alloc, Mode>::set_next
    (streambuf_type* next)
{ next_ = next; }

template<typename T, typename Tr, typename Alloc, typename Mode>
inline void indirect_streambuf<T, Tr, Alloc, Mode>::close
    (BOOST_IOS::openmode which)
{
    close_impl(which);
    try { obj().close(which, next_); } catch (std::exception&) { }
}

//----------State changing functions------------------------------------------//

template<typename T, typename Tr, typename Alloc, typename Mode>
inline void indirect_streambuf<T, Tr, Alloc, Mode>::close_impl
    (BOOST_IOS::openmode which)
{
    if (which & BOOST_IOS::in) {
        setg(0, 0, 0);
        flags_ |= f_input_closed;
    }
    if (which & BOOST_IOS::out) {
        sync();
        setp(0, 0);
        flags_ |= f_output_closed;
    }
}

template<typename T, typename Tr, typename Alloc, typename Mode>
void indirect_streambuf<T, Tr, Alloc, Mode>::sync_impl()
{
    std::streamsize amt;
    if ((amt = static_cast<std::streamsize>(pptr() - pbase())) > 0) {
        obj().write(pbase(), amt, next());
        setp(out().begin(), out().end());
    }
}

template<typename T, typename Tr, typename Alloc, typename Mode>
void indirect_streambuf<T, Tr, Alloc, Mode>::init_get_area()
{
    if (shared_buffer() && pptr() != 0) {
        sync_impl();
        setp(0, 0);
    }
    setg(in().begin(), in().begin(), in().begin());
}

template<typename T, typename Tr, typename Alloc, typename Mode>
void indirect_streambuf<T, Tr, Alloc, Mode>::init_put_area()
{
    using namespace std;
    if (shared_buffer() && gptr() != 0)
        setg(0, 0, 0);
    if (output_buffered())
        setp(out().begin(), out().end());
    else
        setp(0, 0);
}

//----------------------------------------------------------------------------//

} } } // End namespaces detail, iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp> // MSVC, Borland 5.x

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_INDIRECT_STREAMBUF_HPP_INCLUDED
