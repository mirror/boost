// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// No include guards -- file included by boost/iostreams/stream_facade.hpp
// within include guards.

#include <boost/config.hpp>                     // BOOST_STATIC_CONSANT.
#include <boost/iostreams/constants.hpp>
#include <boost/iostreams/detail/forward.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace iostreams {

template< typename Device,
          typename Tr =
              std::char_traits<
                  BOOST_DEDUCED_TYPENAME io_char<Device>::type
              >,
          typename Alloc =
              std::allocator<
                  BOOST_DEDUCED_TYPENAME io_char<Device>::type
              > >
struct stream_facade : detail::stream_facade_base<Device, Tr, Alloc> {
public:
    typedef BOOST_IOSTREAMS_CHAR_TYPE(Device)        char_type;
    BOOST_IOSTREAMS_STREAMBUF_TYPEDEFS(Tr)
private:
    typedef typename
            detail::stream_facade_traits<
                Device, Tr
            >::stream_type                           stream_type;
    typedef Device                                   policy_type;
    template<typename U>
    struct forward_impl {
        BOOST_STATIC_CONSTANT(bool, value = 
            ( !is_same< 
                   const U&,
                   typename detail::param_type<Device>::type
              >::value &&
              !is_same< 
                  const U&,
                  const reference_wrapper<Device>
              >::value ));
    };
    template<typename U>
    struct forward : mpl::bool_<forward_impl<U>::value> { };
public:
    stream_facade() { }

    template<typename U0>
    stream_facade(const U0& u0)
    {
        open_impl(forward<U0>(), u0);
    }
    template<typename U0, typename U1>
    stream_facade(const U0& u0, const U1& u1)
    {
        open_impl(forward<U0>(), u0, u1);
    }
    template<typename U0, typename U1, typename U2>
    stream_facade(const U0& u0, const U1& u1, const U2& u2)
    {
        open_impl(forward<U0>(), u0, u1, u2);
    }
    template<typename U0>
    stream_facade(U0& u0)
    {
        open_impl(forward<U0>(), u0);
    }
    template<typename U0, typename U1>
    stream_facade(U0& u0, const U1& u1)
    {
        open_impl(forward<U0>(), u0, u1);
    }
    template<typename U0, typename U1, typename U2>
    stream_facade(U0& u0, const U1& u1, const U2& u2)
    {
        open_impl(forward<U0>(), u0, u1, u2);
    }
    template<typename U0>
    void open(const U0& u0)
    {
        open_impl(forward<U0>(), u0);
    }
    template<typename U0, typename U1>
    void open(const U0& u0, const U1& u1)
    {
        open_impl(forward<U0>(), u0, u1);
    }
    template<typename U0, typename U1, typename U2>
    void open(const U0& u0, const U1& u1, const U2& u2)
    {
        open_impl(forward<U0>(), u0, u1, u2);
    }
    template<typename U0>
    void open(U0& u0)
    {
        open_impl(forward<U0>(), u0);
    }
    template<typename U0, typename U1>
    void open(U0& u0, const U1& u1)
    {
        open_impl(forward<U0>(), u0, u1);
    }
    template<typename U0, typename U1, typename U2>
    void open(U0& u0, const U1& u1, const U2& u2)
    {
        open_impl(forward<U0>(), u0, u1, u2);
    }
    bool is_open() const { return this->member.is_open(); }
    void close() { this->member.close(); }
    void set_buffer_size(std::streamsize size)
    { this->member.set_buffer_size(size); }
    Device& operator*() { return *this->member; }
    Device* operator->() { return &*this->member; }
private:
    template<typename U0>
    void open_impl(mpl::false_, const U0& u0)
    {
        this->clear(); 
        this->member.open(u0);
    }
    template<typename U0>
    void open_impl(mpl::false_, U0& u0)
    {
        this->clear(); 
        this->member.open(detail::wrap(u0));
    }
    template<typename U0>
    void open_impl(mpl::true_, const U0& u0)
    {
        this->clear(); 
        this->member.open(Device(u0));
    }
    template<typename U0, typename U1>
    void open_impl(mpl::false_, const U0& u0, const U1& u1)
    {
        this->clear(); 
        this->member.open(u0, u1);
    }
    template<typename U0, typename U1>
    void open_impl(mpl::false_, U0& u0, const U1& u1)
    {
        this->clear(); 
        this->member.open(detail::wrap(u0), u1);
    }
    template<typename U0, typename U1>
    void open_impl(mpl::true_, const U0& u0, const U1& u1)
    {
        this->clear(); 
        this->member.open(Device(u0, u1));
    }
    template<typename U0, typename U1, typename U2>
    void open_impl(mpl::false_, const U0& u0, const U1& u1, const U2& u2)
    {
        this->clear(); 
        this->member.open(u0, u1, u2);
    }
    template<typename U0, typename U1, typename U2>
    void open_impl(mpl::false_, U0& u0, const U1& u1, const U2& u2)
    {
        this->clear(); 
        this->member.open(detail::wrap(u0), u1, u2);
    }
    template<typename U0, typename U1, typename U2>
    void open_impl(mpl::true_, const U0& u0, const U1& u1, const U2& u2)
    {
        this->clear(); 
        this->member.open(Device(u0, u1, u2));
    }
};

} } // End namespaces iostreams, boost.
