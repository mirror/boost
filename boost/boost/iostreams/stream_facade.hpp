// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_STREAM_FACADE_HPP_INCLUDED
#define BOOST_IOSTREAMS_STREAM_FACADE_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <istream>
#include <ostream>
#include <boost/iostreams/constants.hpp>
#include <boost/iostreams/detail/forward.hpp>
#include <boost/iostreams/detail/select.hpp>
#include <boost/iostreams/streambuf_facade.hpp>
#include <boost/mpl/and.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost { namespace iostreams {

namespace detail {

template<typename Device, typename Tr>
struct stream_facade_traits {
    typedef BOOST_IOSTREAMS_CHAR_TYPE(Device)                   char_type;
    typedef Tr                                                  traits_type;
    typedef BOOST_IOSTREAMS_CATEGORY(Device)                    mode;
    typedef typename
            select<
                mpl::and_<
                    is_convertible<mode, input>,
                    is_convertible<mode, output>
                >,
                std::basic_iostream<char_type, traits_type>,
                is_convertible<mode, input>,
                std::basic_istream<char_type, traits_type>,
                mpl::true_,
                std::basic_ostream<char_type, traits_type>
            >::type                                             stream_type;
};

// Hack to work around fact that streams don't have default constructors.
// Simplifies the definition of the macro BOOST_IOSTREAMS_DEFINE_FORWARDING_FUNCTIONS.
template< typename Device,
          typename Tr =
              std::char_traits<
                  BOOST_DEDUCED_TYPENAME char_type<Device>::type
              >,
          typename Alloc =
              std::allocator<
                  BOOST_DEDUCED_TYPENAME char_type<Device>::type
              >,
          typename Base = // VC6 Workaround.
              BOOST_DEDUCED_TYPENAME
              detail::stream_facade_traits<Device, Tr>::stream_type >
class stream_facade_base
    : protected base_from_member< streambuf_facade<Device, Tr, Alloc> >,
      public Base
{
private:
    typedef base_from_member< streambuf_facade<Device, Tr, Alloc> >  pbase_type;
    typedef typename stream_facade_traits<Device, Tr>::stream_type   stream_type;
protected:
    using pbase_type::member; // Avoid warning about 'this' in initializer list.
public:
    stream_facade_base() : pbase_type(), stream_type(&member) { }
};

} // End namespace detail.

//
// Template name: stream_facade.
// Description: A iostream which reads from and writes to an instance of a
//      designated device type.
// Template paramters:
//      Device - A device type.
//      Alloc - The allocator type.
//
template< typename Device,
          typename Tr =
              std::char_traits<
                  BOOST_DEDUCED_TYPENAME char_type<Device>::type
              >,
          typename Alloc =
              std::allocator<
                  BOOST_DEDUCED_TYPENAME char_type<Device>::type
              > >
struct stream_facade : detail::stream_facade_base<Device, Tr, Alloc> {
public:
    typedef BOOST_IOSTREAMS_CHAR_TYPE(Device)        char_type;
    BOOST_IOSTREAMS_STREAMBUF_TYPEDEFS(Tr)
private:
    typedef base_from_member<
                streambuf_facade<Device, Tr, Alloc>
            >                                        pbase_type;
    typedef typename
            detail::stream_facade_traits<
                Device, Tr
            >::stream_type                           stream_type;
    typedef Device                                   policy_type;
public:
    stream_facade() { }
    // BEGIN DEBUG
    stream_facade( typename detail::param_type<Device>::type t,
                   std::streamsize buffer_size = -1,
                   std::streamsize pback_size = -1 )
    { this->open_impl(detail::wrap(t), buffer_size, pback_size); }
    stream_facade( const reference_wrapper<Device>& ref,
                   std::streamsize buffer_size = -1,
                   std::streamsize pback_size = -1 )
    { this->open_impl(ref , buffer_size, pback_size); }
    void open( typename detail::param_type<Device>::type t,
               std::streamsize buffer_size = -1,
               std::streamsize pback_size = -1 )
    { this->open_impl(detail::wrap(t), buffer_size, pback_size); }
    void open( const reference_wrapper<Device>& ref ,
               std::streamsize buffer_size = -1,
               std::streamsize pback_size = -1 )
    { this->open_impl(ref , buffer_size, pback_size); }
    template<typename U0>
    stream_facade(U0 u0) { this->open_impl(Device(u0)); }
    template<typename U0, typename U1>
    stream_facade(U0 u0, U1 u1) { this->open_impl(Device(u0, u1)); }
    template<typename U0, typename U1, typename U2>
    stream_facade(U0 u0, U1 u1, U2 u2) { this->open_impl(Device(u0, u1, u2)); }
    template<typename U0>
    void open(U0 u0) { this->open_impl (Device(u0)); }
    template<typename U0, typename U1>
    void open(U0 u0, U1 u1) { this->open_impl (Device(u0, u1)); }
    template<typename U0, typename U1, typename U2>
    void open(U0 u0, U1 u1, U2 u2) { this->open_impl (Device(u0, u1, u2)); }
    // END DEBUG
    //BOOST_IOSTREAMS_FORWARD( streambuf_facade, open_impl, Device,
    //                         BOOST_IOSTREAMS_PUSH_PARAMS(),
    //                         BOOST_IOSTREAMS_PUSH_ARGS() )
    bool is_open() const { return this->member.is_open(); }
    void close() { this->member.close(); }
    void set_buffer_size(std::streamsize size)
    { this->member.set_buffer_size(size); }
    Device& operator*() { return *this->member; }
    Device* operator->() { return &*this->member; }
private:
    void open_impl(const Device& dev BOOST_IOSTREAMS_PUSH_PARAMS()) // For forwarding.
    { this->clear(); this->member.open(dev BOOST_IOSTREAMS_PUSH_ARGS()); }
};

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_STREAM_FACADE_HPP_INCLUDED
