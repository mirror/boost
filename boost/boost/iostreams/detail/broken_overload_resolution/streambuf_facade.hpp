// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// No include guards -- file included by boost/iostreams/streambuf_facade.hpp
// within include guards.

#include <boost/iostreams/detail/disable_warnings.hpp>  // MSVC.

#include <memory>                                       // allocator.       
#include <boost/iostreams/detail/broken_overload_resolution/forward.hpp>
#include <boost/iostreams/detail/forward.hpp>
#include <boost/iostreams/detail/param_type.hpp>
#include <boost/iostreams/traits.hpp>

namespace boost { namespace iostreams {

template< typename T, 
          typename Tr = 
              std::char_traits<
                  BOOST_DEDUCED_TYPENAME io_char<T>::type 
              >,
          typename Alloc = std::allocator<BOOST_IOSTREAMS_CHAR_TYPE(T)>,
          typename Mode = BOOST_DEDUCED_TYPENAME io_mode<T>::type >
class streambuf_facade
    : public detail::streambuf_facade_traits<T, Tr, Alloc, Mode>::type
{
private:
    BOOST_STATIC_ASSERT((is_convertible<BOOST_IOSTREAMS_CATEGORY(T), Mode>::value));
    typedef typename 
            detail::streambuf_facade_traits<
                T, Tr, Alloc, Mode
            >::type                               base_type;
    typedef T                                     policy_type;
public:
    typedef BOOST_IOSTREAMS_CHAR_TYPE(T)          char_type;
    BOOST_IOSTREAMS_STREAMBUF_TYPEDEFS(Tr)
    streambuf_facade() { }
    template<typename U0>
    streambuf_facade(const U0& u0)
    {
        open_impl(detail::forward<T, U0>(), u0);
    }
    template<typename U0, typename U1>
    streambuf_facade(const U0& u0, const U1& u1)
    {
        open_impl(detail::forward<T, U0>(), u0, u1);
    }
    template<typename U0, typename U1, typename U2>
    streambuf_facade(const U0& u0, const U1& u1, const U2& u2)
    {
        open_impl(detail::forward<T, U0>(), u0, u1, u2);
    }
    template<typename U0>
    streambuf_facade(U0& u0)
    {
        open_impl(detail::forward<T, U0>(), u0);
    }
    template<typename U0, typename U1>
    streambuf_facade(U0& u0, const U1& u1)
    {
        open_impl(detail::forward<T, U0>(), u0, u1);
    }
    template<typename U0, typename U1, typename U2>
    streambuf_facade(U0& u0, const U1& u1, const U2& u2)
    {
        open_impl(detail::forward<T, U0>(), u0, u1, u2);
    }
    template<typename U0>
    void open(const U0& u0)
    {
        open_impl(detail::forward<T, U0>(), u0);
    }
    template<typename U0, typename U1>
    void open(const U0& u0, const U1& u1)
    {
        open_impl(detail::forward<T, U0>(), u0, u1);
    }
    template<typename U0, typename U1, typename U2>
    void open(const U0& u0, const U1& u1, const U2& u2)
    {
        open_impl(detail::forward<T, U0>(), u0, u1, u2);
    }
    template<typename U0>
    void open(U0& u0)
    {
        open_impl(detail::forward<T, U0>(), u0);
    }
    template<typename U0, typename U1>
    void open(U0& u0, const U1& u1)
    {
        open_impl(detail::forward<T, U0>(), u0, u1);
    }
    template<typename U0, typename U1, typename U2>
    void open(U0& u0, const U1& u1, const U2& u2)
    {
        open_impl(detail::forward<T, U0>(), u0, u1, u2);
    }
private:
    template<typename U0>
    void open_impl(mpl::false_, const U0& u0)
    {
        base_type::open(u0, -1, -1);
    }
    template<typename U0>
    void open_impl(mpl::false_, U0& u0)
    {
        base_type::open(detail::wrap(u0), -1, -1);
    }
    template<typename U0>
    void open_impl(mpl::true_, const U0& u0)
    {
        base_type::open(Device(u0), -1, -1);
    }
    template<typename U0, typename U1>
    void open_impl(mpl::false_, const U0& u0, const U1& u1)
    {
        base_type::open(u0, u1, -1);
    }
    template<typename U0, typename U1>
    void open_impl(mpl::false_, U0& u0, const U1& u1)
    {
        base_type::open(detail::wrap(u0), u1, -1);
    }
    template<typename U0, typename U1>
    void open_impl(mpl::true_, const U0& u0, const U1& u1)
    {
        base_type::open(Device(u0, u1), -1, -1);
    }
    template<typename U0, typename U1, typename U2>
    void open_impl(mpl::false_, const U0& u0, const U1& u1, const U2& u2)
    {
        base_type::open(u0, u1, u2);
    }
    template<typename U0, typename U1, typename U2>
    void open_impl(mpl::false_, U0& u0, const U1& u1, const U2& u2)
    {
        base_type::open(detail::wrap(u0), u1, u2);
    }
    template<typename U0, typename U1, typename U2>
    void open_impl(mpl::true_, const U0& u0, const U1& u1, const U2& u2)
    {
        base_type::open(Device(u0, u1, u2), -1, -1);
    }
    void check_open()
    {
        if (this->is_open()) 
            throw std::ios_base::failure("already open");
    }
};

} } // End namespaces iostreams, boost.
