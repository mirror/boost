// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// This implementation is currently broken and is not used.

#ifndef BOOST_IOSTREAMS_DETAIL_BLOCK_ORIENTED_STREAMBUF_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_BLOCK_ORIENTED_STREAMBUF_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif              

#include <boost/iostreams/detail/disable_warnings.hpp> // MSVC.

#include <algorithm> // min, max.
#include <exception>
#include <boost/iostreams/detail/error.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/iostreams/streambuf/streambuf_base.hpp>

namespace boost { namespace iostreams { namespace detail {

//
// Description: The implementation of basic_streambuf used by chains.
//
template<typename T, typename Tr, typename Alloc, typename Mode>
class block_oriented_streambuf : public streambuf_base<T, Tr, Alloc, Mode> {
public:
    typedef BOOST_IOSTREAMS_CHAR_TYPE(T)               char_type;
    BOOST_IOSTREAMS_STREAMBUF_TYPEDEFS( Tr)
public:
    block_oriented_streambuf() : oldptr_(0), peek_() { }
private:
    typedef streambuf_base<T, Tr, Alloc, Mode>  base_type;
protected:
    typedef typename base_type::buffer_type     buffer_type;
    typedef typename base_type::link            link;
    BOOST_IOSTREAMS_USING_PROTECTED_STREAMBUF_MEMBERS(base_type)
    int_type underflow();
    int_type pbackfail(int_type c);
    std::streamsize xsgetn(char_type* s, std::streamsize n);
    int_type overflow(int_type c);
    std::streamsize xsputn(const char_type* s, std::streamsize n);
    int sync();
    pos_type seekoff( off_type off, std::ios::seekdir way,
                      std::ios::openmode which );
    pos_type seekpos(pos_type sp, std::ios::openmode which);
private:
    std::streamsize next_block();
    char_type*  oldptr_;
    char_type   peek_;
};

//--------------Implementation of block_oriented_streambuf--------------------//

//--------------Implementation virtual functions------------------------------//

template<typename T, typename Tr, typename Alloc, typename Mode>
std::streamsize block_oriented_streambuf<T, Tr, Alloc, Mode>::next_block()
{
    using namespace std;
    char_type* data = this->in().data();
    streamsize size = this->in().size();
    peek_ = data[size - 1];
    streamsize amt = this->obj().read(data, size, this->next());
    setg(data, data, data + amt);
    return amt;
}

template<typename T, typename Tr, typename Alloc, typename Mode>
typename block_oriented_streambuf<T, Tr, Alloc, Mode>::int_type
block_oriented_streambuf<T, Tr, Alloc, Mode>::underflow()
{
    using namespace std;
    if (!gptr()) this->init_get_area();
    if (eback() == &peek_) { // Restore saved buffer state.
        setg(this->in().begin(), this->in().begin(), oldptr_); 
        return traits_type::to_int_type(*gptr());
    }
    return next_block() ?
           traits_type::to_int_type(*gptr()) :
           traits_type::eof();
}

template<typename T, typename Tr, typename Alloc, typename Mode>
typename block_oriented_streambuf<T, Tr, Alloc, Mode>::int_type
block_oriented_streambuf<T, Tr, Alloc, Mode>::pbackfail(int_type c)
{
    if (eback() == &peek_)
        throw bad_putback();
    if (eback() < gptr()) {
        gbump(-1);
    } else {
        oldptr_ = egptr();                 // Save main buffer state.
        setg(&peek_, &peek_, &peek_ + 1);  // Switch to small buffer.
    }
    if (!traits_type::eq_int_type(c, traits_type::eof()))
        *gptr() = traits_type::to_char_type(c); 
    return traits_type::not_eof(c);
}

template<typename T, typename Tr, typename Alloc, typename Mode>
std::streamsize block_oriented_streambuf<T, Tr, Alloc, Mode>::xsgetn
    (char_type* s, std::streamsize n)
{
    using namespace std;
    if (!gptr()) this->init_get_area();

    char_type* data = this->in().data();
    streamsize size = this->in().size();
    std::streamsize result = 0;

    // Copy contents of putback buffer to [s, s + n)
    if (eback() == &peek_) {
        *s = peek_;
        ++result;
        setg(data, data, oldptr_);
    }

    // Copy contents of main buffer to [s, s + n).
    streamsize amt;
    if (amt = min(static_cast<streamsize>(egptr() - gptr()), n - result)) {
        traits_type::copy(s + result, gptr(), amt);
        gbump(amt);
        result += amt;
        if (result == n || egptr() != data + size)
            return result;
    }

    // Calculate number of blocks to read directly into [s, s + n).
    streamsize remaining = n - result;
    int skip = (remaining % size) ? 
        remaining / size : 
        (remaining / size ) - 1;

    // Read skip blocks into [s, s + n).
    streamsize blocks;
    if (blocks = skip * size) {
        amt = this->obj().read(s + result, blocks, this->next());
        result += amt;
        if (amt < blocks) {
            setg(data, data, data);
            return result;
        }
    }

    // Read last (partial) block into main buffer.
    peek_ = s[result - 1];
    amt = this->obj().read(data, remaining - blocks, this->next());
    setg(data, data, data + amt);

    // Copy contents of main buffer to [s, s + n).
    traits_type::copy(s + result, data, amt);
    gbump(amt);
    result += amt;

    return result;
}

template<typename T, typename Tr, typename Alloc, typename Mode>
typename block_oriented_streambuf<T, Tr, Alloc, Mode>::int_type
block_oriented_streambuf<T, Tr, Alloc, Mode>::overflow(int_type c)
{
    using namespace std;
    if (pptr() == 0) this->init_put_area();
    if (!traits_type::eq_int_type(c, traits_type::eof())) {
        this->sync_impl();
        setp(this->out().begin(), this->out().end());
        *pptr() = traits_type::to_int_type(c);
        pbump(1);
    }
    return traits_type::not_eof(c);
}

template<typename T, typename Tr, typename Alloc, typename Mode>
std::streamsize block_oriented_streambuf<T, Tr, Alloc, Mode>::xsputn
    (const char_type* s, std::streamsize n)
{
    using namespace std;
    if (!pptr()) this->init_put_area();

    char_type* data = this->out().data();
    streamsize size = this->out().size();
    streamsize result = 0;

    // Copy initial segment of [s, s + n) to main buffer.
    streamsize amt = min(static_cast<streamsize>(epptr() - pptr()), n);
    traits_type::copy(pptr(), s, amt);
    pbump(amt);
    result += amt;
    if (result == n)
        return result;

    // Flush buffer.
    this->sync_impl();

    // Calculate number of blocks to write directly from [s, s + n).
    streamsize remaining = n - result;
    int skip = remaining / size;   

    // Write skip blocks from [s, s + n).
    streamsize blocks;
    if (blocks = skip * size)
        this->obj().write(s + result, blocks, this->next());
    result += blocks;

    if ((remaining % size)== 0) {
        setp(data, data + size);
        return result;
    }

    // Write last (partial) block to main buffer.
    traits_type::copy(data, s + result, n - result);
    setp(data, data + size);
    pbump(n - result);
    
    return n;
}

template<typename T, typename Tr, typename Alloc, typename Mode>
int block_oriented_streambuf<T, Tr, Alloc, Mode>::sync()
{
    try { // sync() is no-throw.
        this->sync_impl();
        this->obj().flush(this->next());
        return 0;
    } catch (std::exception&) { return -1; }
}

template<typename T, typename Tr, typename Alloc, typename Mode>
typename block_oriented_streambuf<T, Tr, Alloc, Mode>::pos_type
block_oriented_streambuf<T, Tr, Alloc, Mode>::seekoff
    (off_type off, std::ios::seekdir way, std::ios::openmode which)
{
    using namespace std;

    if (this->shared_buffer())
        which = ios::in | ios::out;
    if ((which & ios::out) && pptr())
        this->sync_impl();

    bool seek_input = // Is read head being repositioned?
            this->shared_buffer() ? 
                gptr() != 0 : 
                (which & ios::in) != 0;
    buffer_type& buf = seek_input ? this->in() : this->out();
    char_type* ptr = seek_input ? gptr() : pptr();
    streamsize size = buf.size();

    // Caluculate offset adjustment, so buffer will be aligned 
    // on block boundary.
    off_type adj = 0; 
    switch (way) {
    case ios::beg:
        adj = off % size;
        break;
    case ios::cur:
        if (off > 0) { 
            adj = off + static_cast<off_type>(ptr - buf.begin());
            adj %= size;
        } else if (off < 0) {
            adj = -off + static_cast<off_type>(buf.end() - ptr);
            adj %= size;
            adj = (size - adj) % size;
        }
        if (gptr() && (which & ios::in)) // Unconsumed input.
            adj += static_cast<off_type>(egptr() - gptr());
        break;
    case ios::end: // Seek to end to calculate length.
        adj = (this->obj().seek(0, way, which, this->next()) + off) % size;
        break;
    }
    if (seek_input) 
        off -= adj;

    // Forward adjusted seek request.
    off_type result = this->obj().seek(off - adj, way, which, this->next());

    // initialize buffers.
    if (seek_input) 
        setg(buf.begin(), buf.begin() + adj, buf.begin() + adj);
    if ((which & ios::end) && (!this->shared_buffer() || !gptr())) 
        setp(buf.begin() + adj, buf.end());

    return result + adj;
}

template<typename T, typename Tr, typename Alloc, typename Mode>
typename block_oriented_streambuf<T, Tr, Alloc, Mode>::pos_type
block_oriented_streambuf<T, Tr, Alloc, Mode>::seekpos
    (pos_type sp, std::ios::openmode which)
{ 
    typedef std::basic_streambuf<char_type, traits_type> sbuf;
    return sbuf::seekoff(sp, std::ios::beg, which); 
} 

//----------------------------------------------------------------------------//

} } } // End namespaces detail, iostreams, boost.

#include <boost/iostreams/detail/enable_warnings.hpp> // MSVC

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_BLOCK_ORIENTED_STREAMBUF_HPP_INCLUDED
