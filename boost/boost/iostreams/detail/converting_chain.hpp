// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// NOTE: This implementation has not been tested.

#ifndef BOOST_IOSTREAMS_DETAIL_CONVERTING_CHAIN_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CONVERTING_CHAIN_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif              

#include <memory>                               // allocator.
#include <boost/iostreams/converter.hpp>
#include <boost/iostreams/detail/chain.hpp>
#include <boost/iostreams/detail/push.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace iostreams { namespace detail {

template< typename Mode, 
          typename Ch = wchar_t, 
          typename Tr = std::char_traits<wchar_t>,
          typename Alloc = std::allocator<Ch> >
class converting_chain {
private:
    typedef chain<Mode, char, std::char_traits<char>, Alloc>  external_chain;
    typedef chain<Mode, Ch, Tr, Alloc>                        internal_chain;
    typedef converter<external_chain, Alloc, Ch, Tr>          converter_type; 
public:
    typedef Ch                                     char_type;
    BOOST_IOSTREAMS_STREAMBUF_TYPEDEFS(Tr)
    typedef Alloc                                  allocator_type;
    typedef Mode                                   mode;
    struct category
        : Mode,
          device_tag,
          closable_tag 
        { };
    typedef chain_client<converting_chain>         client_type;
    friend class chain_client<converting_chain;

    converting_chain();

    //----------Buffer sizing-------------------------------------------------//

    void set_buffer_size(std::streamsize n)
        { 
            chain_.set_buffer_size(n);
            cvt_->set_buffer_size(n);
        }
    void set_filter_buffer_size(std::streamsize n)
        { 
            chain_.set_filter_buffer_size(n);
            cvt_->set_filter_buffer_size(n);
        }
    void set_pback_size(std::streamsize n)
        { 
            chain_.set_pback_size(n);
            cvt_->set_pback_size(n);
        }

    //----------Device interface----------------------------------------------//

    std::streamsize read(char_type* s, std::streamsize n);
    void write(const char_type* s, std::streamsize n);
    off_type seek(off_type off, std::ios::seekdir way);
    void flush() { list().front()->pubsync(); }

    //----------Container interface-------------------------------------------//

    BOOST_IOSTREAMS_DEFINE_PUSH(mode, char_type, push, push_impl)
    void pop() 
        {
            if (!cvt_->empty()) {
                cvt_->pop();
                if (cvt_->empty())
                    chain_.pop();   // Pop cvt_ from chain_.
            } else {
                chain_.pop();
            }
        }
    bool empty() const { return chain_.empty() && cvt_->empty(); }
    size_type size() const { return chain_.size() + cvt_->size(); }
    void reset() { chain_.reset(); cvt_->reset(); }
    bool is_complete() const 
    { return chain_.is_complete() && cvt_->is_complete(); }

    //----------Direct stream buffer access-----------------------------------//

    streambuf_type& operator*() { return *chain_; }
    streambuf_type* operator->() { return &*chain_; }
protected:
    void register_client(client_type* client);
    void notify();
private:
    template<typename T>
    void push_impl( const T& t,
                    std::streamsize buffer_size = -1,
                    std::streamsize pback_size = -1 )
        {
            
        }
private:
    internal_chain  chain_;
    converter_type  cvt_;
};
            
} } } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CONVERTING_CHAIN_HPP_INCLUDED
