// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// This header is used only by block_oriented_streambuf, which is currently
// broken.

#ifndef BOOST_IOSTREAMS_DETAIL_STREAMBUF_BASE_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_STREAMBUF_BASE_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif              

#include <boost/iostreams/detail/disable_warnings.hpp>  // MSVC, Borland 5.x.

#include <exception>
#include <boost/bind.hpp>                        // Used w/ scope_guard.
#include <boost/ref.hpp>                         // Used w/ scope_guard.
#include <boost/iostreams/detail/adapter/concept_adapter.hpp>
#include <boost/iostreams/detail/buffer.hpp>
#include <boost/iostreams/detail/double_object.hpp>
#include <boost/iostreams/detail/scope_guard.hpp>
#include <boost/iostreams/detail/streambuf/linked_streambuf.hpp>
#include <boost/iostreams/detail/workaround.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/iostreams/is_device.hpp>
#include <boost/iostreams/operations.hpp>
#include <boost/mpl/if.hpp>
#include <boost/optional.hpp>
#include <boost/detail/none.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost { namespace iostreams { namespace detail {

template<typename Ch, typename Alloc, typename Mode>
struct double_buffer
    : double_object< 
          basic_buffer<Ch, Alloc>, 
          is_convertible<Mode, two_sequence> 
      >
{
    basic_buffer<Ch, Alloc>& in() { return this->first(); }
    basic_buffer<Ch, Alloc>& out() { return this->second(); }
};

//
// Description: The implementation of basic_streambuf used by chains.
//
template<typename T, typename Tr, typename Alloc, typename Mode>
class streambuf_base
    : public linked_streambuf<BOOST_IOSTREAMS_CHAR_TYPE(T), Tr>, 
      public double_buffer<BOOST_IOSTREAMS_CHAR_TYPE(T), Alloc, Mode>
{
public:
    typedef BOOST_IOSTREAMS_CHAR_TYPE(T)                      char_type;
    BOOST_IOSTREAMS_STREAMBUF_TYPEDEFS( Tr)
private:
    typedef BOOST_IOSTREAMS_CATEGORY(T)                       io_category;
    typedef concept_adapter<T>                                wrapper;
protected:
    typedef basic_buffer<char_type, Alloc>                    buffer_type;
    typedef linked_streambuf<char_type, traits_type>          base_type;
    typedef typename base_type::link                          link;
    BOOST_IOSTREAMS_USING_PROTECTED_STREAMBUF_MEMBERS(base_type)
public:
    streambuf_base();
    ~streambuf_base();

    void open(const T& t BOOST_IOSTREAMS_PUSH_PARAMS());
    bool is_open();
    void close();

    //----------Direct filter or device access--------------------------------//

    T& operator*() { return *obj(); }
    T* operator->() { return &**obj(); }
protected:
    using double_buffer<char_type, Alloc, Mode>::in;
    using double_buffer<char_type, Alloc, Mode>::out;

    //----------Accessor functions--------------------------------------------//

    wrapper& obj() { return *storage_; }
    link* next() const { return next_; }
    bool can_read() const { return is_convertible<Mode, input>::value; }
    bool can_write() const { return is_convertible<Mode, output>::value; }
    bool output_buffered() const { return (flags_ & output_buffered) != 0; }
    bool shared_buffer() const { return is_convertible<Mode, seekable>::value; }
    void set_flags(int f) { flags_ = f; }

    //----------Utility function----------------------------------------------//

    void sync_impl();
    void close_impl(std::ios::openmode);

    //----------Virtual functions---------------------------------------------//

    void imbue(const std::locale& loc);    // Declared in basic_streambuf.
    void close(std::ios::openmode m); // Declared in linked_streambuf.
    void set_next(link* next);             // Declared in linked_streambuf.
    virtual void init_get_area();
    virtual void init_put_area();
private:

    enum {

        // state flags, valid for all modes.
        f_open             = 1,
        f_input_closed     = f_open << 1,
        f_output_closed    = f_input_closed << 1,
        f_output_buffered  = f_output_closed
    };

    optional<wrapper>  storage_;
    link*              next_;
    char_type*         oldptr_;
    char_type          peek_;
    int                flags_;
};

//--------------Implementation of streambuf_base--------------------------//

template<typename T, typename Tr, typename Alloc, typename Mode>
streambuf_base<T, Tr, Alloc, Mode>::streambuf_base()
    : next_(0), oldptr_(0), peek_(), flags_(0) { }

template<typename T, typename Tr, typename Alloc, typename Mode>
streambuf_base<T, Tr, Alloc, Mode>::~streambuf_base() 
{ if (is_open()) try { close(); } catch (std::exception&) { } }

//--------------Implementation of open, is_open and close---------------------//

template<typename T, typename Tr, typename Alloc, typename Mode>
void streambuf_base<T, Tr, Alloc, Mode>::open
    (const T& t, std::streamsize buffer_size, std::streamsize pback_size)
{
    if (buffer_size)
        flags_ |= f_output_buffered;

    // Normalize buffer sizes.
    buffer_size =
        buffer_size != -1 ?
        buffer_size :
        is_device<T>::value ?
            default_buffer_size :
            default_filter_buffer_size;

    // Construct input buffer.
    if (can_read()) {
        in().resize(buffer_size);
        if (!shared_buffer())
            init_get_area();
    }

    // Construct output buffer.
    if (can_write() && !shared_buffer()) {
        out().resize(buffer_size);
        init_put_area();
    }

    storage_ = wrapper(t);
    flags_ |= f_open;
}

template<typename T, typename Tr, typename Alloc, typename Mode>
inline bool streambuf_base<T, Tr, Alloc, Mode>::is_open()
{ return (flags_ & f_open) != 0; }

#include <boost/iostreams/detail/scope_guard_prefix.hpp> // CW workaround
template<typename T, typename Tr, typename Alloc, typename Mode>
void streambuf_base<T, Tr, Alloc, Mode>::close()
{   

    typedef streambuf_base<T, Tr, Alloc, Mode> my_type;
    void (my_type::*close)(ios::openmode) = &my_type::close;
    void (optional<wrapper>::*reset)() = &optional<wrapper>::reset;
    BOOST_SCOPE_GUARD(bind(&my_type::set_flags, ref(*this), 0));
    BOOST_SCOPE_GUARD(bind(reset, ref(storage_)));
    if ((flags_ & f_output_closed) == 0)
        close(std::ios::out);
    if ((flags_ & f_input_closed) == 0)
        close(std::ios::in);
}
#include <boost/iostreams/detail/scope_guard_suffix.hpp>

//--------------Implementation virtual functions------------------------------//

template<typename T, typename Tr, typename Alloc, typename Mode>
void streambuf_base<T, Tr, Alloc, Mode>::imbue(const std::locale& loc)
{ obj().imbue(loc); if (next_) next_->pubimbue(loc); }

template<typename T, typename Tr, typename Alloc, typename Mode>
inline void streambuf_base<T, Tr, Alloc, Mode>::set_next
    (link* next)
{ next_ = next; }

template<typename T, typename Tr, typename Alloc, typename Mode>
inline void streambuf_base<T, Tr, Alloc, Mode>::close(std::ios::openmode which)
{   
#if !defined(BOOST_IOSTREAMS_NO_SCOPE_GUARD) && \
    !BOOST_WORKAROUND(__BORLANDC__, < 0x600)
    BOOST_SCOPE_GUARD(bind(&my_type::close_impl, ref(*this), which));
    BOOST_SCOPE_GUARD(bind(&wrapper::close, ref(obj()), which, next_));
#else
    try { obj().close(which, next_); } catch (std::exception&) { }
    close_impl(which);
#endif    
}

template<typename T, typename Tr, typename Alloc, typename Mode>
inline void streambuf_base<T, Tr, Alloc, Mode>::close_impl
    (std::ios::openmode which)
{       
    if (which & std::ios::in) {
        setg(0, 0, 0);
        flags_ |= f_input_closed; 
    }
    if (which & std::ios::out) {
        sync();
        setp(0, 0);
        flags_ |= f_output_closed;
    }
}

template<typename T, typename Tr, typename Alloc, typename Mode>
void streambuf_base<T, Tr, Alloc, Mode>::sync_impl()
{
    std::streamsize amt;
    if (amt = static_cast<std::streamsize>(pptr() - pbase())) {
        obj().write(pbase(), amt, next());
        setp(pptr(), epptr());
    }
}

template<typename T, typename Tr, typename Alloc, typename Mode>
void streambuf_base<T, Tr, Alloc, Mode>::init_get_area()
{ 
    if (shared_buffer() && pptr() != 0) {
        sync_impl();
        setp(0, 0);
    }
    setg(in().begin(), in().begin(), in().begin()); 
}

template<typename T, typename Tr, typename Alloc, typename Mode>
void streambuf_base<T, Tr, Alloc, Mode>::init_put_area()
{ 
    using namespace std;
    if (shared_buffer() && gptr() != 0) 
        setg(0, 0, 0);
    setp(out().begin(), out().end()); 
}

//----------------------------------------------------------------------------//

} } } // End namespaces detail, iostreams, boost.

#include <boost/iostreams/detail/enable_warnings.hpp> // MSVC, Borland 5.x.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_STREAMBUF_BASE_HPP_INCLUDED
