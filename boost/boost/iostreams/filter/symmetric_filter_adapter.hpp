// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Contains the definitions of the class templates symmetric_filter_adapter,
// which models DualUseFilter based on a model of the Symmetric Filter.

//
// Roughly, a Symmetric Filter is a class type with the following interface:
//
//   struct symmetric_filter {
//       typedef xxx char_type;
//
//       bool filter( const char*& begin_in, const char* end_in,
//                    char*& begin_out, char* end_out, bool flush )
//       {
//          // Consume as many characters as possible from the interval
//          // [begin_in, end_in), without exhausting the output range
//          // [begin_out, end_out). If flush is true, write as mush output
//          // as possible. 
//          // A return value of true indicates that filter should be called 
//          // again. More precisely, if flush is false, a return value of 
//          // false indicates that the natural end of stream has been reached
//          // and that all filtered data has been forwarded; if flush is
//          // true, a return value of false indicates that all filtered data 
//          // has been forwarded.
//       }
//       void close() { /* Reset filter's state. */ }
//   };
//
// Symmetric Filter filters need not be CopyConstructable.
//

#ifndef BOOST_IOSTREAMS_SYMMETRIC_FILTER_ADAPTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_SYMMETRIC_FILTER_ADAPTER_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <cassert>
#include <memory>                               // allocator, auto_ptr.
#include <boost/config.hpp>                     // BOOST_DEDUCED_TYPENAME.
#include <boost/iostreams/char_traits.hpp>
#include <boost/iostreams/constants.hpp>        // buffer size.
#include <boost/iostreams/detail/buffer.hpp>
#include <boost/iostreams/detail/char_traits.hpp>
#include <boost/iostreams/detail/closer.hpp>
#include <boost/iostreams/detail/config/limits.hpp>
#include <boost/iostreams/detail/template_params.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/iostreams/operations.hpp>       // read, write.
#include <boost/iostreams/pipeline.hpp>
#include <boost/preprocessor/iteration/local.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/shared_ptr.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>  // MSVC.

namespace boost { namespace iostreams {

template< typename SymmetricFilter,
          typename Alloc =
              std::allocator<
                  BOOST_DEDUCED_TYPENAME char_type_of<SymmetricFilter>::type
              > >
class symmetric_filter_adapter {
public:
    typedef typename char_type_of<SymmetricFilter>::type  char_type;
    typedef std::basic_string<char_type>                  string_type;
    struct category
        : dual_use,
          filter_tag,
          multichar_tag,
          closable_tag
        { };

    // BEGIN DEBUG
    explicit symmetric_filter_adapter(int buffer_size)
        : pimpl_(new impl(buffer_size))
        { }

    template<typename T0>
    symmetric_filter_adapter(int buffer_size, const T0& t0)
        : pimpl_(new impl(buffer_size, t0))
        { }

    template<typename T0, typename T1>
    symmetric_filter_adapter(int buffer_size, const T0& t0, const T1& t1)
        : pimpl_(new impl(buffer_size, t0, t1))
        { }

    template<typename T0, typename T1, typename T2>
    symmetric_filter_adapter( int buffer_size, const T0& t0,
                              const T1& t1, const T2& t2 )
        : pimpl_(new impl(buffer_size, t0, t1, t2))
        { }
    // END DEBUG

    // Expands to a sequence of ctors which forward to impl.
    #define BOOST_PP_LOCAL_MACRO(n) \
        BOOST_IOSTREAMS_TEMPLATE_PARAMS(n, T) \
        explicit symmetric_filter_adapter( \
              int buffer_size BOOST_PP_COMMA_IF(n) \
              BOOST_PP_ENUM_BINARY_PARAMS(n, const T, &t) ) \
            : pimpl_(new impl(buffer_size BOOST_PP_COMMA_IF(n) \
                     BOOST_PP_ENUM_PARAMS(n, t))) \
            { } \
        /**/
    //#define BOOST_PP_LOCAL_LIMITS (0, BOOST_IOSTREAMS_MAX_FORWARDING_ARITY)
    //#include BOOST_PP_LOCAL_ITERATE()
    #undef BOOST_PP_LOCAL_MACRO

    template<typename Source>
    std::streamsize read(Source& src, char_type* s, std::streamsize n)
    {
        using namespace std;
        if (!(state() & f_read))
            begin_read();

        buffer_type&  buf = pimpl_->buf_;
        int           status = (state() & f_eof) != 0 ? f_eof : f_good;
        char_type    *next_s = s,
                     *end_s = s + n;
        while (true)
        {
            // Invoke filter if there are unconsumed characters in buffer or if
            // filter must be flushed.
            bool flush = status == f_eof;
            if (buf.ptr() != buf.eptr() || flush) {
                const char_type* next = buf.ptr();
                bool done =
                    !filter().filter(next, buf.eptr(), next_s, end_s, flush);
                buf.ptr() = buf.data() + (next - buf.data());
                if (done)
                    return detail::check_eof(static_cast<streamsize>(next_s - s));
            }

            // If no more characters are available without blocking, or
            // if read request has been satisfied, return.
            if ( status == f_would_block && buf.ptr() == buf.eptr() ||
                 next_s == end_s )
            {
                return static_cast<streamsize>(next_s - s);
            }

            // Fill buffer.
            if (status == f_good)
                status = fill(src);
        }
    }

    template<typename Sink>
    std::streamsize write(Sink& snk, const char_type* s, std::streamsize n)
    {
        if (!(state() & f_write))
            begin_write();

        buffer_type&     buf = pimpl_->buf_;
        const char_type *next_s, *end_s;
        for (next_s = s, end_s = s + n; next_s != end_s; ) {
            if (buf.ptr() == buf.eptr() && !flush(snk))
                break;
            filter().filter(next_s, end_s, buf.ptr(), buf.eptr(), false);
        }
        return static_cast<std::streamsize>(next_s - s);
    }

    // Give detail::closer<> permission to call close().
    typedef symmetric_filter_adapter<SymmetricFilter, Alloc> self;
    friend struct detail::closer<self>;

    template<typename Sink>
    void close(Sink& snk, BOOST_IOS::openmode which)
    {
        using namespace std;
        if ((state() & f_read) && (which & BOOST_IOS::in))
            close();
        if ((state() & f_write) && (which & BOOST_IOS::out)) {

            // Repeatedly invoke filter() with no input.
            detail::closer<self>  closer(*this);
            buffer_type&          buf = pimpl_->buf_;
            char                  dummy;
            const char*           end = &dummy;
            bool                  again = true;
            while (again) {
                if (buf.ptr() != buf.eptr())
                    again = filter().filter(end, end, buf.ptr(), buf.eptr(), true);
                flush(snk);
            }
        }
    }
    SymmetricFilter& filter() { return *pimpl_; }
    string_type unconsumed_input() const;
private:
    typedef detail::buffer<char_type, Alloc> buffer_type;

    buffer_type& buf() { return pimpl_->buf_; }
    const buffer_type& buf() const { return pimpl_->buf_; }
    int& state() { return pimpl_->state_; }
    void begin_read();
    void begin_write();

    template<typename Source>
    int fill(Source& src)
    {
        std::streamsize amt = iostreams::read(src, buf().data(), buf().size());
        if (amt == -1) {
            state() |= f_eof;
            return f_eof;
        }
        buf().set(0, amt);
        return amt == buf().size() ? f_good : f_would_block;
    }

    // Attempts to write the contents of the buffer the given Sink.
    // Returns true if at least on character was written.
    template<typename Sink>
    bool flush(Sink& snk)
    {
        typedef typename iostreams::category_of<Sink>::type  category;
        typedef is_convertible<category, output>             can_write;
        return flush(snk, can_write());
    }

    template<typename Sink>
    bool flush(Sink& snk, mpl::true_)
    {
        using std::streamsize;
        typedef char_traits<char_type> traits_type;
        streamsize amt =
            static_cast<streamsize>(buf().ptr() - buf().data());
        streamsize result =
            boost::iostreams::write(snk, buf().data(), amt);
        if (result < amt && result > 0)
            traits_type::move(buf().data(), buf().data() + result, amt - result);
        buf().set(amt - result, buf().size());
        return result != 0;
    }

    template<typename Sink>
    bool flush(Sink& snk, mpl::false_) { return true;}

    void close();

    enum {
        f_read   = 1,
        f_write  = f_read << 1,
        f_eof    = f_write << 1,
        f_good,
        f_would_block
    };

    struct impl : SymmetricFilter {

        // BEGIN DEBUG
        //explicit impl(int buffer_size)
        //    : SymmetricFilter(), buf_(buffer_size), state_(0) { }

        //template<typename T0>
        //impl(int buffer_size, const T0 &t0)
        //    : SymmetricFilter(t0), buf_(buffer_size), state_(0)
        //    { }

        //template<typename T0, typename T1>
        //impl(int buffer_size, const T0 &t0, const T1 &t1)
        //    : SymmetricFilter(t0, t1), buf_(buffer_size), state_(0)
        //    { }

        //template<typename T0, typename T1, typename T2>
        //impl(int buffer_size, const T0 &t0, const T1 &t1, const T2& t2)
        //    : SymmetricFilter(t0, t1, t2), buf_(buffer_size), state_(0)
        //    { }
        // END DEBUG

    // Expands to a sequence of ctors which forward to SymmetricFilter.
    #define BOOST_PP_LOCAL_MACRO(n) \
        BOOST_IOSTREAMS_TEMPLATE_PARAMS(n, T) \
        impl( int buffer_size BOOST_PP_COMMA_IF(n) \
              BOOST_PP_ENUM_BINARY_PARAMS(n, const T, &t) ) \
            : SymmetricFilter(BOOST_PP_ENUM_PARAMS(n, t)), \
              buf_(buffer_size), state_(0) \
            { } \
        /**/
    #define BOOST_PP_LOCAL_LIMITS (0, BOOST_IOSTREAMS_MAX_FORWARDING_ARITY)
    #include BOOST_PP_LOCAL_ITERATE()
    #undef BOOST_PP_LOCAL_MACRO

        buffer_type  buf_;
        int          state_;
    };

    shared_ptr<impl> pimpl_;
};
BOOST_IOSTREAMS_PIPABLE(symmetric_filter_adapter, 2)

//------------------Implementation of symmetric_filter_adapter----------------//

template<typename SymmetricFilter, typename Alloc>
void symmetric_filter_adapter<SymmetricFilter, Alloc>::begin_read()
{
    assert(!(state() & f_write));
    state() |= f_read;
    buf().set(0, 0);
}

template<typename SymmetricFilter, typename Alloc>
void symmetric_filter_adapter<SymmetricFilter, Alloc>::begin_write()
{
    assert(!(state() & f_read));
    state() |= f_write;
    buf().set(0, buf().size());
}

template<typename SymmetricFilter, typename Alloc>
void symmetric_filter_adapter<SymmetricFilter, Alloc>::close()
{
    state() = 0;
    buf().set(0, 0);
    filter().close();
}

template<typename SymmetricFilter, typename Alloc>
typename symmetric_filter_adapter<SymmetricFilter, Alloc>::string_type
symmetric_filter_adapter<SymmetricFilter, Alloc>::unconsumed_input() const
{ return string_type(buf().ptr(), buf().eptr()); }

//----------------------------------------------------------------------------//

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>  // MSVC.

#endif // #ifndef BOOST_IOSTREAMS_SYMMETRIC_FILTER_ADAPTER_HPP_INCLUDED
