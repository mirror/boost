// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_DIRECT_STREAMBUF_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_DIRECT_STREAMBUF_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif              

#include <boost/iostreams/detail/disable_warnings.hpp> // MSVC.

#include <cassert>
#include <cstddef>
#include <utility>                              // pair.
#include <boost/config.hpp>                     // BOOST_DEDUCED_TYPENAME.
#include <boost/iostreams/detail/streambuf/linked_streambuf.hpp>
#include <boost/iostreams/detail/error.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/optional.hpp>

namespace boost { namespace iostreams { namespace detail {

template< typename T, 
          typename Tr = std::char_traits<BOOST_IOSTREAMS_CHAR_TYPE(T)> >
class direct_streambuf 
    : public linked_streambuf<BOOST_IOSTREAMS_CHAR_TYPE(T), Tr> 
{
public:
    typedef BOOST_IOSTREAMS_CHAR_TYPE(T)                  char_type;
    BOOST_IOSTREAMS_STREAMBUF_TYPEDEFS(Tr)
private:
    typedef linked_streambuf<char_type, traits_type>      base_type;
    typedef std::basic_streambuf<char_type, traits_type>  streambuf_type;
    typedef BOOST_IOSTREAMS_CATEGORY(T)                   io_category;
public: // stream_facade needs access.
    void open( const T& t,
               std::streamsize,   // buffer size -- not used.
               std::streamsize ); // pback_size -- not used.
    bool is_open();
    void close();
protected:
    BOOST_IOSTREAMS_USING_PROTECTED_STREAMBUF_MEMBERS(base_type)
    direct_streambuf();

    //--------------Virtual functions-----------------------------------------//

    int_type underflow();
    int_type pbackfail(int_type c);
    int_type overflow(int_type c);
    pos_type seekoff( off_type off, std::ios::seekdir way,
                      std::ios::openmode which );
    pos_type seekpos(pos_type sp, std::ios::openmode which);
    void close(std::ios::openmode m);
private:
    pos_type seek_impl( off_type off, std::ios::seekdir way,
                        std::ios::openmode which );
    void init_input(any_tag) { }
    void init_input(input);
    void init_output(any_tag) { }
    void init_output(output);
    void init_get_area();
    void init_put_area();
    bool one_head() const;
    bool two_head() const;
    optional<T>  storage_;
    char_type   *ibeg_, *iend_, *obeg_, *oend_;
};
                    
//------------------Implementation of direct_streambuf------------------------//

template<typename T, typename Tr>
direct_streambuf<T, Tr>::direct_streambuf() 
    : ibeg_(0), iend_(0), obeg_(0), oend_(0) { }

template<typename T, typename Tr>
void direct_streambuf<T, Tr>::open(const T& t, std::streamsize, std::streamsize)
{
    storage_ = t;
    init_input(io_category());
    init_output(io_category());
    setg(0, 0, 0);
    setp(0, 0);
}

template<typename T, typename Tr>
bool direct_streambuf<T, Tr>::is_open() { return ibeg_ != 0 && !obeg_ != 0; }

template<typename T, typename Tr>
void direct_streambuf<T, Tr>::close() 
{ ibeg_ = iend_ = obeg_ = oend_ = 0; storage_.reset(); }

template<typename T, typename Tr>
typename direct_streambuf<T, Tr>::int_type 
direct_streambuf<T, Tr>::underflow()
{
    if (!ibeg_) 
        throw cant_read();
    if (!gptr()) 
        init_get_area();
    return gptr() != iend_ ? *gptr() : traits_type::eof();
}

template<typename T, typename Tr>
typename direct_streambuf<T, Tr>::int_type 
direct_streambuf<T, Tr>::pbackfail(int_type c)
{
    using namespace std;
    if (!ibeg_) 
        throw cant_read();
    if (gptr() != 0 && gptr() != ibeg_) {
        gbump(-1);
        if (!traits_type::eq_int_type(c, traits_type::eof()))
            *gptr() = traits_type::to_char_type(c);
        return traits_type::not_eof(c);
    }
    throw ios::failure("can't putback");
}

template<typename T, typename Tr>
typename direct_streambuf<T, Tr>::int_type 
direct_streambuf<T, Tr>::overflow(int_type c)
{
    using namespace std;
    if (!obeg_) throw ios::failure("no write access");
    if (!pptr()) init_put_area();
    if (!traits_type::eq_int_type(c, traits_type::eof())) {
        if (pptr() == oend_)
            throw ios::failure("write area exhausted");
        *pptr() = traits_type::to_char_type(c);
        pbump(1);
        return c;
    }
    return traits_type::not_eof(c);
}

template<typename T, typename Tr>
inline typename direct_streambuf<T, Tr>::pos_type
direct_streambuf<T, Tr>::seekoff
    (off_type off, std::ios::seekdir way, std::ios::openmode which)
{ return seek_impl(off, way, which); }

template<typename T, typename Tr>
inline typename direct_streambuf<T, Tr>::pos_type
direct_streambuf<T, Tr>::seekpos
    (pos_type sp, std::ios::openmode)
{ return seek_impl(sp, std::ios::beg, std::ios::in | std::ios::out); }

template<typename T, typename Tr>
void direct_streambuf<T, Tr>::close(std::ios::openmode) { close(); }

template<typename T, typename Tr>
typename direct_streambuf<T, Tr>::pos_type direct_streambuf<T, Tr>::seek_impl
    (off_type off, std::ios::seekdir way, std::ios::openmode which)
{
    using namespace std;
    ios::openmode both = ios::in | ios::out;
    if (two_head() && (which & both) == both)
        throw ios::failure("bad seek");
    off_type result = -1;
    bool one = one_head();
    if (one && (pptr() != 0 || gptr()== 0))
        init_get_area(); // Switch to input mode, for code reuse.
    if (one || (which & ios::in) != 0 && ibeg_ != 0) {
        if (!gptr()) setg(ibeg_, ibeg_, iend_);
        ptrdiff_t next = 0;
        switch (way) {
        case ios::beg: next = off; break;
        case ios::cur: next = (gptr() - ibeg_) + off; break;
        case ios::end: next = (iend_ - ibeg_) + off; break;
        default: assert(0);
        }
        if (next < 0 || next > (iend_ - ibeg_))
            throw ios::failure("bad seek");
        setg(ibeg_, ibeg_ + next, iend_);
        result = next;
    }
    if (!one && (which & ios::out) != 0 && obeg_ != 0) {
        if (!pptr()) setp(obeg_, oend_);
        ptrdiff_t next = 0;
        switch (way) {
        case ios::beg: next = off; break;
        case ios::cur: next = (pptr() - obeg_) + off; break;
        case ios::end: next = (oend_ - obeg_) + off; break;
        default: assert(0);
        }
        if (next < 0 || next > (oend_ - obeg_))
            throw ios::failure("bad seek");
        pbump(static_cast<int>(next - (pptr() - obeg_)));
        result = next;
    }
    return result;
}

template<typename T, typename Tr>
void direct_streambuf<T, Tr>::init_input(input)
{
    std::pair<char_type*, char_type*> p = input_sequence(*storage_);
    ibeg_ = p.first;
    iend_ = p.second;
}

template<typename T, typename Tr>
void direct_streambuf<T, Tr>::init_output(output)
{
    std::pair<char_type*, char_type*> p = output_sequence(*storage_);
    obeg_ = p.first;
    oend_ = p.second;
}

template<typename T, typename Tr>
void direct_streambuf<T, Tr>::init_get_area()
{
    setg(ibeg_, ibeg_, iend_);
    if (one_head() && pptr()) {
        gbump(static_cast<int>(pptr() - obeg_));
        setp(0, 0);
    }
}

template<typename T, typename Tr>
void direct_streambuf<T, Tr>::init_put_area()
{
    setp(obeg_, oend_);
    if (one_head() && gptr()) {
        pbump(static_cast<int>(gptr() - ibeg_));
        setg(0, 0, 0);
    }
}

template<typename T, typename Tr>
inline bool direct_streambuf<T, Tr>::one_head() const
{ return ibeg_ && obeg_ && ibeg_ == obeg_; }

template<typename T, typename Tr>
inline bool direct_streambuf<T, Tr>::two_head() const
{ return ibeg_ && obeg_ && ibeg_ != obeg_; }

//----------------------------------------------------------------------------//

} } } // End namespaces detail, iostreams, boost.

#include <boost/iostreams/detail/enable_warnings.hpp> // MSVC

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_DIRECT_STREAMBUF_HPP_INCLUDED
