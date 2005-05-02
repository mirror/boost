// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_BUFFERS_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_BUFFERS_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif              

#include <algorithm>                           // swap.
#include <memory>                              // allocator.
#include <boost/config.hpp>                    // member templates.
#include <boost/iostreams/detail/ios.hpp>      // streamsize.     
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>     
#include <boost/utility.hpp>                   // noncopyable.

namespace boost { namespace iostreams { namespace detail {

//----------------Buffers-----------------------------------------------------//

//
// Template name: buffer
// Description: Character buffer.
// Template paramters:
//     Ch - The character type.
//     Alloc - The Allocator type.
//
template< typename Ch,
          typename Alloc = std::allocator<Ch> >
class basic_buffer : private noncopyable {
private:
#ifndef BOOST_NO_STD_ALLOCATOR
    typedef typename Alloc::template rebind<Ch>::other allocator_type;
#else
    typedef std::allocator<Ch> allocator_type;
#endif
public:
    basic_buffer();
    basic_buffer(int buffer_size);
    ~basic_buffer();
    void resize(int buffer_size);
    Ch* begin() const { return buf_; }
    Ch* end() const { return buf_ + size_; }
    Ch* data() const { return buf_; }
    std::streamsize size() const { return size_; }
    void swap(basic_buffer& rhs);
private:
    Ch*              buf_;
    std::streamsize  size_;
};

template<typename Ch, typename Alloc>
void swap(basic_buffer<Ch, Alloc>& lhs, basic_buffer<Ch, Alloc>& rhs)
{ lhs.swap(rhs); }

//
// Template name: buffer
// Description: Character buffer with two pointers accessible via ptr() and
//      eptr().
// Template paramters:
//     Ch - A character type.
//
template< typename Ch,
          typename Alloc = std::allocator<Ch> >
class buffer : public basic_buffer<Ch, Alloc> {
private:
    typedef basic_buffer<Ch, Alloc> base;
public:
    using base::resize; 
    using base::data; 
    using base::size;
    typedef Ch* const const_pointer;
    buffer(int buffer_size);
    Ch* & ptr() { return ptr_; }
    const_pointer& ptr() const { return ptr_; }
    Ch* & eptr() { return eptr_; }
    const_pointer& eptr() const { return eptr_; }
    void set(std::streamsize ptr, std::streamsize end);
    void swap(buffer& rhs);
private:
    Ch *ptr_, *eptr_;
};

template<typename Ch, typename Alloc>
void swap(buffer<Ch, Alloc>& lhs, buffer<Ch, Alloc>& rhs)
{ lhs.swap(rhs); }

//--------------Implementation of basic_buffer--------------------------------//

template<typename Ch, typename Alloc>
basic_buffer<Ch, Alloc>::basic_buffer() : buf_(0), size_(0) { }

template<typename Ch, typename Alloc>
basic_buffer<Ch, Alloc>::basic_buffer(int buffer_size)
    : buf_(static_cast<Ch*>(allocator_type().allocate(buffer_size, 0))), 
      size_(buffer_size) // Cast for SunPro 5.3.
    { }

template<typename Ch, typename Alloc>
inline basic_buffer<Ch, Alloc>::~basic_buffer()
{ if (buf_) allocator_type().deallocate(buf_, size_); }

template<typename Ch, typename Alloc>
inline void basic_buffer<Ch, Alloc>::resize(int buffer_size)
{
    if (size_ != buffer_size) {
        basic_buffer<Ch, Alloc> temp(buffer_size);
        std::swap(size_, temp.size_);
        std::swap(buf_, temp.buf_);
    }
}

template<typename Ch, typename Alloc>
void basic_buffer<Ch, Alloc>::swap(basic_buffer& rhs) 
{ 
    std::swap(buf_, rhs.buf_); 
    std::swap(size_, rhs.size_); 
}

//--------------Implementation of buffer--------------------------------------//

template<typename Ch, typename Alloc>
buffer<Ch, Alloc>::buffer(int buffer_size)
    : basic_buffer<Ch, Alloc>(buffer_size) { }

template<typename Ch, typename Alloc>
inline void buffer<Ch, Alloc>::set(std::streamsize ptr, std::streamsize end)
{ 
    ptr_ = data() + ptr; 
    eptr_ = data() + end; 
}

template<typename Ch, typename Alloc>
inline void buffer<Ch, Alloc>::swap(buffer& rhs) 
{ 
    base::swap(rhs); 
    std::swap(ptr_, rhs.ptr_); 
    std::swap(eptr_, rhs.eptr_); 
}

//----------------------------------------------------------------------------//

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_BUFFERS_HPP_INCLUDED
