// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Contains machinery for performing code conversion.

#ifndef BOOST_IOSTREAMS_CODE_CONVERTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_CODE_CONVERTER_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/iostreams/detail/config/wide_streams.hpp>
#if defined(BOOST_IOSTREAMS_NO_WIDE_STREAMS) || \
    defined(BOOST_IOSTREAMS_NO_LOCALE) \
    /**/
# error code conversion not supported on this platform
#endif

#include <algorithm>                       // max.
#include <cstring>                         // memcpy.
#include <exception>
#include <boost/config.hpp>                // DEDUCED_TYPENAME.
#include <boost/iostreams/char_traits.hpp>
#include <boost/iostreams/constants.hpp>   // default_filter_buffer_size.
#include <boost/iostreams/detail/adapter/concept_adapter.hpp>
#include <boost/iostreams/detail/adapter/direct_adapter.hpp>
#include <boost/iostreams/detail/buffer.hpp>
#include <boost/iostreams/detail/call_traits.hpp>
#include <boost/iostreams/detail/codecvt_holder.hpp>
#include <boost/iostreams/detail/codecvt_helper.hpp>
#include <boost/iostreams/detail/double_object.hpp>
#include <boost/iostreams/detail/forward.hpp>
#include <boost/iostreams/detail/ios.hpp> // failure, openmode, int types.
#include <boost/iostreams/detail/select.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/iostreams/operations.hpp>
#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_same.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp> // Borland 5.x

namespace boost { namespace iostreams {

struct code_conversion_error : BOOST_IOSTREAMS_FAILURE {
    code_conversion_error() 
        : BOOST_IOSTREAMS_FAILURE("code conversion error")
        { }
};

namespace detail {

//--------------Definition of conversion_buffer-------------------------------//

// Buffer and conversion state for reading.
template<typename Codecvt, typename Alloc>
class conversion_buffer 
    : public buffer<
                 BOOST_DEDUCED_TYPENAME detail::codecvt_extern<Codecvt>::type,
                 Alloc
             > 
{
public:
    typedef typename Codecvt::state_type state_type;
    conversion_buffer() 
        : buffer<
              BOOST_DEDUCED_TYPENAME detail::codecvt_extern<Codecvt>::type,
              Alloc
          >(0) 
    { 
        reset(); 
    }
    state_type& state() { return state_; }
    void reset() 
    { 
        if (this->size()) 
            this->set(0, 0);
        state_ = state_type(); 
    }
private:
    state_type state_;
};

//--------------Definition of converter_impl----------------------------------//

// Contains member data, open/is_open/close and buffer management functions.
template<typename Device, typename Codecvt, typename Alloc>
struct code_converter_impl {
    typedef typename codecvt_extern<Codecvt>::type          extern_type;
    typedef typename io_category<Device>::type              device_category;
    typedef is_convertible<device_category, input>          can_read;
    typedef is_convertible<device_category, output>         can_write;
    typedef is_convertible<device_category, bidirectional>  is_bidir;
    typedef typename 
            select<  // Disambiguation for Tru64
                is_bidir, bidirectional,
                can_read, input,
                can_write, output
            >::type                                         mode;      
    typedef typename
            mpl::if_<
                is_direct<Device>,
                direct_adapter<Device>,
                Device
            >::type                                         policy_type;
    typedef optional< concept_adapter<policy_type> >        storage_type;
    typedef is_convertible<device_category, two_sequence>   is_double;
    typedef conversion_buffer<Codecvt, Alloc>               buffer_type;

    code_converter_impl() : cvt_(), flags_(0) { }

    ~code_converter_impl()
    { 
        try { 
            if (flags_ & f_open) close(); 
        } catch (std::exception&) { /* */ } 
    }

    void open(const Device& dev, int buffer_size)
    {
        if (flags_ & f_open)
            throw BOOST_IOSTREAMS_FAILURE("already open");
        if (buffer_size == -1)
            buffer_size = default_filter_buffer_size;
        int max_length = cvt_.get().max_length();
        buffer_size = (std::max)(buffer_size, 2 * max_length);
        if (can_read::value) {
            buf_.first().resize(buffer_size);
            buf_.first().set(0, 0);
        }
        if (can_write::value && !is_double::value) {
            buf_.second().resize(buffer_size);
            buf_.second().set(0, buffer_size);
        }
        dev_.reset(concept_adapter<policy_type>(dev));
        flags_ |= f_open;
    }

    void close(BOOST_IOS::openmode which = BOOST_IOS::in | BOOST_IOS::out)
    {
        if (which & BOOST_IOS::in) {
            iostreams::close(**dev_, BOOST_IOS::in);
            flags_ |= f_input_closed;
        }
        if (which & BOOST_IOS::out) {
            flush();
            iostreams::close(**dev_, BOOST_IOS::out);
            flags_ |= f_output_closed;
        }
        if ( !is_double::value || 
             (flags_ & f_input_closed) != 0 && 
             (flags_ & f_output_closed) != 0 )
        {
            dev_.reset();
            buf_.first().reset();
            buf_.second().reset();
            flags_ = 0;
        }
    }
    bool is_open() const { return (flags_ & f_open) != 0;}

    bool flush() { return flush(is_convertible<device_category, output>()); }
    bool flush(mpl::false_) { return true; }
    bool flush(mpl::true_)
    {
        buffer_type& out = buf_.second();
        std::streamsize amt =
            static_cast<std::streamsize>(out.ptr() - out.data());
        std::streamsize result = dev_->write(out.data(), amt);
        if (result < amt) {
            char_traits<extern_type>::move( out.data(),
                                            out.data() + result, 
                                            amt - result );
        }
        out.set(amt - result, out.size() - amt + result);
        return result != 0;
    }

    int fill() // Returns an int as a status code.
    {
        using std::streamsize;
        buffer_type& in = buf_.first();
        streamsize off = static_cast<streamsize>(in.eptr() - in.ptr());
        if (off)
            char_traits<extern_type>::move(in.data(), in.ptr(), off);
        in.set(0, off);
        streamsize amt =
            dev_->read(in.data() + off, in.size() - off);
        if (amt != -1)
            in.set(0, off + amt);
        return amt == in.size() - off ?
            '\n' :
            amt == -1 ?
                EOF :
                WOULD_BLOCK;
    }

    policy_type& get() { return *dev_.get(); }
    const policy_type& get() const { return *dev_.get(); }

    enum {
        f_open             = 1,
        f_input_closed     = f_open << 1,
        f_output_closed    = f_input_closed << 1
    };

    codecvt_holder<Codecvt>  cvt_;
    storage_type             dev_;
    double_object<
        buffer_type, 
        is_double
    >                        buf_;
    int                      flags_;
};

} // End namespace detail.

//--------------Definition of converter---------------------------------------//

#define BOOST_IOSTREAMS_CONVERTER_PARAMS() , int buffer_size = -1
#define BOOST_IOSTREAMS_CONVERTER_ARGS() , buffer_size

template<typename Device, typename Codecvt, typename Alloc>
struct code_converter_base {
    typedef detail::code_converter_impl<
                Device, Codecvt, Alloc
            > impl_type;
    code_converter_base() : pimpl_(new impl_type) { }
    shared_ptr<impl_type> pimpl_;
};

template< typename Device, 
          typename Codecvt = detail::default_codecvt, 
          typename Alloc = std::allocator<char> >
class code_converter 
    : protected code_converter_base<Device, Codecvt, Alloc>
{
private:
    typedef detail::code_converter_impl<
                Device, Codecvt, Alloc
            >                                                       impl_type;
    typedef typename impl_type::policy_type                         policy_type;
    typedef typename impl_type::buffer_type                         buffer_type;
    typedef typename detail::codecvt_holder<Codecvt>::codecvt_type  codecvt_type;
    typedef typename detail::codecvt_intern<Codecvt>::type          intern_type;
    typedef typename detail::codecvt_extern<Codecvt>::type          extern_type;
    typedef typename detail::codecvt_state<Codecvt>::type           state_type;
public:
    typedef intern_type                                             char_type;    
    struct io_category 
        : impl_type::mode, device_tag, closable_tag, localizable_tag
        { };
    BOOST_STATIC_ASSERT((
        is_same<
            extern_type, 
            BOOST_DEDUCED_TYPENAME io_char<Device>::type
        >::value
    ));
public:
    code_converter() { }
    // BEGIN DEBUG
    explicit code_converter( typename detail::param_type<Device>::type t, 
                             int buffer_size = -1 ) 
    {
        this->open_impl(detail::wrap(t), buffer_size);
    }
    explicit code_converter( const reference_wrapper<Device>& ref, 
                             int buffer_size = -1 ) 
    {
        this->open_impl(ref , buffer_size);
    }
    void open( typename detail::param_type<Device>::type t, 
               int buffer_size = -1 ) 
    {
        this->open_impl(detail::wrap(t), buffer_size);
    }
    void open( const reference_wrapper<Device>& ref, 
               int buffer_size = -1 ) 
    {
        this->open_impl(ref, buffer_size);
    }
    template< typename U0> 
    code_converter(const U0& u0) 
    {
        this->open_impl(Device(u0));
    }
    template<typename U0, typename U1> 
    code_converter(const U0& u0, const U1& u1) 
    {
        this->open_impl(Device(u0, u1));
    }
    template<typename U0, typename U1, typename U2> 
    code_converter(const U0& u0, const U1&u1, const U2& u2) 
    {
        this->open_impl(Device(u0, u1, u2));
    }
    template<typename U0> 
    void open(const U0& u0) 
    {
        this->open_impl(Device(u0));
    }
    template<typename U0, typename U1> 
    void open(const U0& u0, const U1& u1) 
    {
        this->open_impl(Device(u0, u1));
    }
    template<typename U0, typename U1, typename U2> 
    void open(const U0& u0, const U1& u1, const U2& u2) 
    {
        this->open_impl(Device(u0, u1, u2));
    }
    // BEGIN END
    //BOOST_IOSTREAMS_FORWARD( code_converter, open_impl, Device,
    //                         BOOST_IOSTREAMS_CONVERTER_PARAMS, 
    //                         BOOST_IOSTREAMS_CONVERTER_ARGS )

        // fstream-like interface.

    bool is_open() const { return impl().is_open(); }
    void close(BOOST_IOS::openmode which = BOOST_IOS::in | BOOST_IOS::out )
    { impl().close(which); }

        // Device interface.

    std::streamsize read(char_type*, std::streamsize);
    std::streamsize write(const char_type*, std::streamsize);
    void imbue(const std::locale& loc) { impl().cvt_.imbue(loc); }

        // Direct device access.

    Device& operator*() { return detail::unwrap_direct(dev()); }
    Device* operator->() { return &detail::unwrap_direct(dev()); }
private:
    template<typename T> // Used for forwarding.
    void open_impl(const T& t BOOST_IOSTREAMS_CONVERTER_PARAMS()) 
    { 
        impl().open(t BOOST_IOSTREAMS_CONVERTER_ARGS()); 
    }
    int fill() { return impl().fill(); }
    bool flush() { return impl().flush(); }

    const codecvt_type& cvt() { return impl().cvt_.get(); }
    policy_type& dev() { return impl().get(); }
    buffer_type& in() { return impl().buf_.first(); }
    buffer_type& out() { return impl().buf_.second(); }
    impl_type& impl() { return *this->pimpl_; }
};

//--------------Implementation of converter-----------------------------------//

// Implementation note: if end of stream contains a partial character,
// it is ignored.
template<typename Device, typename Codevt, typename Alloc>
std::streamsize code_converter<Device, Codevt, Alloc>::read
    (char_type* s, std::streamsize n)
{
    using namespace std;
    const extern_type*   next;        // Next external char.
    intern_type*         nint;        // Next internal char.
    streamsize           total = 0;   // Characters read.
    int                  status;
    bool                 partial = false;
    buffer_type&         buf = in();

    do {

        // Fill buffer.
        if (buf.ptr() == buf.eptr() || partial) {
            status = fill();
            if (buf.ptr() == buf.eptr())
                break;
            partial = false;
        }

        // Convert.
        codecvt_base::result result =
            cvt().in( buf.state(),
                      buf.ptr(), buf.eptr(), next,
                      s + total, s + n, nint );
        buf.ptr() += next - buf.ptr();
        total = static_cast<streamsize>(nint - s);

        switch (result) {
        case codecvt_base::partial:
            partial = true;
            break;
        case codecvt_base::ok:
            break;
        case codecvt_base::error:
            buf.state() = state_type();
            throw code_conversion_error();
        case codecvt_base::noconv:
        default:
            buf.state() = state_type();
            intern_type c = intern_type();
            memcpy(&c, (const void*) buf.ptr(), sizeof(extern_type));
            s[total++] = c;
            break;
        }

    } while (total < n && status != EOF && status != WOULD_BLOCK);

    return total == 0 && status == EOF ? -1 : total;
}

template<typename Device, typename Codevt, typename Alloc>
std::streamsize code_converter<Device, Codevt, Alloc>::write
    (const char_type* s, std::streamsize n)
{
    using namespace std;
    buffer_type&        buf = out();
    extern_type*        next;              // Next external char.
    const intern_type*  nint;              // Next internal char.
    streamsize          total = 0;         // Characters written.
    bool                partial = false;

    while (total < n) {

        // Empty buffer.
        if (buf.ptr() == buf.eptr() || partial) {
            if (!flush())
                break;
            partial = false;
        }
       
        // Convert.
        codecvt_base::result result =
            cvt().out( buf.state(),
                       s + total, s + n, nint,
                       buf.ptr(), buf.eptr(), next );
        int progress = (int) (next - buf.ptr());
        buf.ptr() += progress;

        switch (result) {
        case codecvt_base::partial:
            partial = true; // Fall through.
        case codecvt_base::ok:
            total = static_cast<streamsize>(nint - s);
            break;
        case codecvt_base::error:
            buf.state() = state_type();
            throw code_conversion_error();
        case codecvt_base::noconv:
            {
                // This can be shortened to two memcpy's.
                const char* c = (const char*) (s + total);
                for ( std::size_t index = 0; 
                      index < sizeof(intern_type); 
                      index += sizeof(extern_type), 
                      ++buf.ptr() ) 
                {
                    memcpy(buf.ptr(), c + index, sizeof(extern_type));
                    if (buf.ptr() == buf.end())
                        flush();
                }
                ++total;
            }
        }
    }
    return total;
}

//----------------------------------------------------------------------------//

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp> // Borland 5.x

#endif // #ifndef BOOST_IOSTREAMS_CODE_CONVERTER_HPP_INCLUDED
