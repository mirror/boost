// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_FILTER_STREAMBUF_HPP_INCLUDED
#define BOOST_IOSTREAMS_FILTER_STREAMBUF_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif              

#include <exception>
#include <memory>                               // allocator.
#include <boost/iostreams/detail/chain.hpp>
#include <boost/iostreams/detail/access_control.hpp>
#include <boost/iostreams/detail/push.hpp>
#include <boost/iostreams/detail/streambuf/chainbuf.hpp>
#include <boost/mpl/if.hpp>                    

namespace boost { namespace iostreams {

// BEGIN DEBUG
template< typename Mode, 
          typename Ch = char, 
          typename Tr = std::char_traits<Ch>, 
          typename Alloc = std::allocator<Ch>, 
          typename Access = public_ > 
class filtering_streambuf 
    : public boost::iostreams::detail::chainbuf< 
                 boost::iostreams::detail::chain<Mode, Ch, Tr, Alloc>, 
                 Mode, 
                 Access 
             > 
{
public: 
    typedef Ch char_type; 
    typedef Tr traits_type; 
    typedef typename traits_type::int_type int_type;
    typedef typename traits_type::off_type off_type; 
    typedef typename traits_type::pos_type pos_type; 
    typedef Mode mode; 
    typedef boost::iostreams::detail::chain<Mode, Ch, Tr, Alloc> chain_type; 
    filtering_streambuf() { }
    template<typename IteratorType> 
    filtering_streambuf( IteratorType first, IteratorType last, 
                         std::streamsize buffer_size = -1, 
                         std::streamsize pback_size = -1 ) 
    {
        this->push_impl( boost::iostreams::detail::range_adapter<mode, IteratorType>(first, last), 
                         buffer_size, pback_size );
    }
    template<typename Piper, typename Concept> 
    filtering_streambuf( const boost::iostreams::detail::piper<Piper, Concept>& p , 
                         std::streamsize buffer_size = -1 , 
                         std::streamsize pback_size = -1 ) 
    {
        p.push(*this);
    }
#ifndef BOOST_NO_SFINAE
    template<typename T> 
    filtering_streambuf( const T& t, std::streamsize buffer_size = -1 , 
                         std::streamsize pback_size = -1, 
                         typename boost::disable_if< 
                              boost::iostreams::is_std_io<T> 
                         >::type* = 0) 
    {
        this->push_impl( boost::iostreams::detail::resolve<mode, Ch>(t), 
                         buffer_size, pback_size );
    }
    template<typename T> 
    filtering_streambuf( T& t, 
                         std::streamsize buffer_size = -1, 
                         std::streamsize pback_size = -1, 
                         typename boost::enable_if< 
                             boost::iostreams::is_std_io<T> 
                         >::type* = 0) 
    {
        this->push_impl(boost::iostreams::detail::wrap(t) , buffer_size, pback_size);
    }
#else 
    template<typename T> 
    filtering_streambuf( const T& t, std::streamsize buffer_size = -1 , 
                         std::streamsize pback_size = -1 ) 
    {
        this->push_impl( boost::iostreams::detail::resolve<mode, Ch>(t), 
                         buffer_size, pback_size );
    }
    template<typename Ch, typename Tr> 
    filtering_streambuf( std::basic_istream<Ch, Tr>& t, 
                         std::streamsize buffer_size = -1, 
                         std::streamsize pback_size = -1 ) 
    {
        this->push_impl(boost::iostreams::detail::wrap(t) , buffer_size, pback_size);
    }
    template<typename Ch, typename Tr> 
    filtering_streambuf( std::basic_ostream<Ch, Tr>& t, 
                         std::streamsize buffer_size = -1, 
                         std::streamsize pback_size = -1 ) 
    {
        this->push_impl(boost::iostreams::detail::wrap(t) , buffer_size, pback_size);
    }
    template<typename Ch, typename Tr> 
    filtering_streambuf( std::basic_iostream<Ch, Tr>& t, 
                         std::streamsize buffer_size = -1, 
                         std::streamsize pback_size = -1 ) 
    {
        this->push_impl(boost::iostreams::detail::wrap(t) , buffer_size, pback_size);
    }
    template<typename Ch, typename Tr> 
    filtering_streambuf( std::basic_streambuf<Ch, Tr>& t, 
                         std::streamsize buffer_size = -1, 
                         std::streamsize pback_size = -1 ) 
    {
        this->push_impl(boost::iostreams::detail::wrap(t) , buffer_size, pback_size);
    }
#endif // BOOST_NO_SFINAE
    ~filtering_streambuf() 
    {
        if (this->is_complete()) 
            this->pubsync();
    }
};
// END DEBUG

//
// Macro: BOOST_IOSTREAMS_DEFINE_FILTERBUF(name_, chain_type_, default_char_)
// Description: Defines a template derived from std::basic_streambuf which uses
//      a chain to perform i/o. The template has the following parameters:
//      Ch - The character type.
//      Tr - The character traits type.
//      Alloc - The allocator type.
//      Access - Indicates accessibility of the chain interface; must be either
//          public_ or protected_; defaults to public_.
//
#define BOOST_IOSTREAMS_DEFINE_FILTER_STREAMBUF(name_, chain_type_, default_char_) \
    template< typename Mode, typename Ch = default_char_, \
              typename Tr = std::char_traits<Ch>, \
              typename Alloc = std::allocator<Ch>, typename Access = public_ > \
    class name_ : public boost::iostreams::detail::chainbuf< \
                             chain_type_<Mode, Ch, Tr, Alloc>, Mode, Access \
                         > \
    { \
    public: \
        typedef Ch                                             char_type; \
        BOOST_IOSTREAMS_STREAMBUF_TYPEDEFS(Tr) \
        typedef Mode                                           mode; \
        typedef chain_type_<Mode, Ch, Tr, Alloc>               chain_type; \
        name_() { } \
        BOOST_IOSTREAMS_DEFINE_PUSH_CONSTRUCTOR(mode, Ch, name_, push_impl) \
        ~name_() { if (this->is_complete()) this->pubsync(); } \
    }; \
    /**/ 
//BOOST_IOSTREAMS_DEFINE_FILTER_STREAMBUF(filtering_streambuf, boost::iostreams::detail::chain, char)
BOOST_IOSTREAMS_DEFINE_FILTER_STREAMBUF(filtering_wstreambuf, boost::iostreams::detail::chain, wchar_t)

typedef filtering_streambuf<input>    filtering_istreambuf;
typedef filtering_streambuf<output>   filtering_ostreambuf;
typedef filtering_wstreambuf<input>   filtering_wistreambuf;
typedef filtering_wstreambuf<output>  filtering_wostreambuf;

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_FILTER_STREAMBUF_HPP_INCLUDED
