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
//          // as possible. Return true to indicate that filter() must be
//          // called again.
//       }
//       void close() { /* Reset filter's state. */ }
//   };
//
// Symmetric Filter filters need not be CopyConstructable or Assignable.
//

#ifndef BOOST_IOSTREAMS_SYMMETRIC_FILTER_ADAPTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_SYMMETRIC_FILTER_ADAPTER_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif              

#include <boost/iostreams/detail/disable_warnings.hpp>  // MSVC.

#include <cassert>
#include <memory>                               // allocator
#include <boost/config.hpp>                     // BOOST_DEDUCED_TYPENAME.
#include <boost/iostreams/constants.hpp>        // buffer size.
#include <boost/iostreams/detail/buffer.hpp>
#include <boost/iostreams/detail/closer.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/iostreams/operations.hpp>       // read, write.
#include <boost/shared_ptr.hpp>

namespace boost { namespace iostreams {

namespace detail {

template<typename SymmetricFilter, typename Alloc>
class symmetric_filter_adapter_impl {
public:
    typedef typename io_char<SymmetricFilter>::type           char_type;
    typedef std::char_traits<char_type>                       traits_type;
    typedef std::basic_string<char_type, traits_type, Alloc>  string_type;
    struct category
        : dual_use,
          filter_tag,
          multichar_tag,
          closable_tag
        { };
    symmetric_filter_adapter_impl( SymmetricFilter* filter,  
                                   std::streamsize buffer_size );
    ~symmetric_filter_adapter_impl() { delete filter_; }

    template<typename Source>
    std::streamsize read(Source& src, char_type* s, std::streamsize n)
    {
        using namespace std;
        if (!(state_ & f_read))
            begin_read();
        char_type *next_s = s, *end_s = s + n;
        while (true) {

            // Invoke filter if there are unconsumed characters or if
            // filter must be flushed:
            bool eof = (state_ & f_eof) != 0;
            if (buf_.ptr() != buf_.eptr() || eof) {
                bool done =
                    !filter_->filter( 
                        const_cast<const char_type*&>(buf_.ptr()),
                        buf_.eptr(), next_s, end_s, eof 
                    ) && eof;
                if (next_s == end_s || done)
                    return static_cast<streamsize>(next_s - s);
            }

            // Fill buffer, unless eof has already been reached.
            if (!eof) {
                assert(buf_.ptr() == buf_.eptr());
                streamsize amt = 
                    boost::iostreams::read(src, buf_.data(), buf_.size());
                if (amt < buf_.size())
                    state_ |= f_eof;
                buf_.set(0, amt);
            }
        }
    }

    template<typename Sink>
    void write(Sink& snk, const char_type* s, std::streamsize n)
    {
        using namespace std;
        if (!(state_ & f_write))
            begin_write();
        const char_type *next_s = s, *end_s = s + n;
        while (next_s != end_s) {
            if (buf_.ptr() == buf_.eptr()) {
                boost::iostreams::write(
                    snk, buf_.data(),
                    static_cast<streamsize>(buf_.ptr() - buf_.data()) 
                );
                buf_.set(0, buf_.size());
            }
            filter_->filter(next_s, end_s, buf_.ptr(), buf_.eptr(), false);
        }
    }

    typedef symmetric_filter_adapter_impl<SymmetricFilter, Alloc> self;
    friend struct closer<self>;
    template<typename Sink>
    void close(Sink& snk, std::ios::openmode which)
    {
        using namespace std;
        if ((state_ & f_read) && (which & ios::in))
            close();
        if ((state_ & f_write) && (which & ios::out)) {
            closer<self> closer(*this);
            char e; // Dummy.
            const char* end = &e;
            bool done = false;
            flush(snk);
            while (!done) {
                done = !filter_->filter(
                            end, end, buf_.ptr(), buf_.eptr(), true
                        );
                flush(snk);
            }
        }
    }

    SymmetricFilter& filter() { return *filter_; }
    string_type unconsumed_input() const;
private:
    void begin_read();
    void begin_write();

    template<typename Sink> 
    void flush(Sink& snk)
    {
        boost::iostreams::write(
            snk, buf_.data(),
            static_cast<std::streamsize>(buf_.ptr() - buf_.data()) 
        );
        buf_.set(0, buf_.size());
    }

    void close();

    enum {
        f_read   = 1,
        f_write  = f_read << 1,
        f_eof    = f_write << 1
    };

    SymmetricFilter*          filter_;
    buffer<char_type, Alloc>  buf_;
    int                       state_;
};

} // End namespace detail.

template< typename SymmetricFilter,
          typename Alloc = 
              std::allocator<
                  BOOST_DEDUCED_TYPENAME
                  io_char<SymmetricFilter>::type
              > >
class symmetric_filter_adapter {
private:
    typedef detail::symmetric_filter_adapter_impl<
                SymmetricFilter, Alloc
            >                                       impl_type;
public:
    typedef typename impl_type::char_type           char_type;
    typedef typename impl_type::category            io_category;
    symmetric_filter_adapter( SymmetricFilter* filter,     // Takes ownership.
                              std::streamsize buffer_size =
                                  default_buffer_size )    // Use large buffer.
        : pimpl_(new impl_type(filter, buffer_size)) { }

    template<typename Source>
    std::streamsize read(Source& src, char_type* s, std::streamsize n)
    { return pimpl_->read(src, s, n); }

    template<typename Sink>
    void write(Sink& snk, const char_type* s, std::streamsize n)
    { pimpl_->write(snk, s, n); }

    template<typename Sink>
    void close(Sink& snk, std::ios::openmode which)
    { pimpl_->close(snk, which); }
protected:
    typedef typename impl_type::string_type         string_type;
    SymmetricFilter& filter() { return pimpl_->filter(); }
    string_type unconsumed_input() const 
    { return pimpl_->unconsumed_input(); }
private:
    shared_ptr<impl_type> pimpl_;
};

//----------------------------------------------------------------------------//

namespace detail {

template<typename SymmetricFilter, typename Alloc>
symmetric_filter_adapter_impl<SymmetricFilter, Alloc>::
    symmetric_filter_adapter_impl
        (SymmetricFilter* filter, std::streamsize buffer_size)
    : filter_(filter), buf_(buffer_size), state_(0) 
    { }

template<typename SymmetricFilter, typename Alloc>
void symmetric_filter_adapter_impl<SymmetricFilter, Alloc>::begin_read()
{
    assert(!(state_ & f_write));
    state_ |= f_read;
    buf_.set(0, 0);
}

template<typename SymmetricFilter, typename Alloc>
void symmetric_filter_adapter_impl<SymmetricFilter, Alloc>::begin_write()
{
    assert(!(state_ & f_read));
    state_ |= f_write;
    buf_.set(0, 0);
}

template<typename SymmetricFilter, typename Alloc>
void symmetric_filter_adapter_impl<SymmetricFilter, Alloc>::close()
{
    state_ = 0;
    buf_.set(0, 0);
    filter_->close();
}

template<typename SymmetricFilter, typename Alloc>
typename symmetric_filter_adapter_impl<SymmetricFilter, Alloc>::string_type
symmetric_filter_adapter_impl<SymmetricFilter, Alloc>::unconsumed_input() const
{ return string_type(buf_.ptr(), buf_.eptr()); }

} // End namespace detail.

//----------------------------------------------------------------------------//

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/enable_warnings.hpp>  // MSVC.

#endif // #ifndef BOOST_IOSTREAMS_SYMMETRIC_FILTER_ADAPTER_HPP_INCLUDED
