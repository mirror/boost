// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_DIRECT_ADAPTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_DIRECT_ADAPTER_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif              

#include <boost/config.hpp>       // SFINAE, MSVC, put ptrdiff_t in std.
#include <algorithm>              // copy, min.
#include <cstddef>                // ptrdiff_t.
#include <iosfwd>                 // streamsize.
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/config/limits.hpp>       // forwarding.
#include <boost/iostreams/detail/double_object.hpp>
#include <boost/iostreams/detail/error.hpp>
#include <boost/iostreams/traits.hpp>                     // io_mode, is_direct.
#include <boost/iostreams/operations.hpp>
#include <boost/mpl/bool.hpp> 
#include <boost/mpl/or.hpp> 
#include <boost/preprocessor/iteration/local.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost { namespace iostreams { namespace detail {
                    
//------------------Definition of direct_adapter_base-------------------------//

// Put all initialization in base class to faciliate forwarding.
template<typename Direct>
class direct_adapter_base {
public:
    typedef typename io_char<Direct>::type char_type;
    struct io_category 
        : io_mode<Direct>::type,
          device_tag,
          closable_tag,
          localizable_tag
        { };
protected:
    direct_adapter_base(const Direct& d);
    typedef is_convertible<io_category, two_sequence> is_double;
    struct pointers {
        char_type *beg, *ptr, *end;
    };
    void init_input(mpl::true_);
    void init_input(mpl::false_) { }
    void init_output(mpl::true_);
    void init_output(mpl::false_) { }
    double_object<pointers, is_double>  ptrs_;
    Direct                              d_;
};

template<typename Direct>
class direct_adapter : private direct_adapter_base<Direct> {
private:
    typedef direct_adapter_base<Direct>      base_type;
    typedef typename base_type::pointers     pointers;
    typedef typename base_type::is_double    is_double;
    using base_type::ptrs_;
    using base_type::d_;
public:
    typedef typename base_type::char_type    char_type;
    typedef typename base_type::io_category  io_category;

        // Constructors

#if !BOOST_WORKAROUND(BOOST_MSVC, <= 1310)
    direct_adapter(const Direct& d) : base_type(d) { }   
    direct_adapter(const direct_adapter& d) : base_type(d) { }
# define BOOST_PP_LOCAL_LIMITS (1, BOOST_IOSTREAMS_MAX_FORWARDING_ARITY)
#else
    template<typename U>
    struct is_direct
        : mpl::or_< 
              is_same<U, direct_adapter<Direct> >, 
              is_same<U, Direct> 
          >
        { };
    template<typename U>
    direct_adapter(const U& u) 
        : base_type(forward(u, is_direct<U>()))
        { }
# define BOOST_PP_LOCAL_LIMITS (2, BOOST_IOSTREAMS_MAX_FORWARDING_ARITY)
#endif

#define BOOST_PP_LOCAL_MACRO(n) \
    template<BOOST_PP_ENUM_PARAMS(n, typename P)> \
    direct_adapter(BOOST_PP_ENUM_BINARY_PARAMS(n, const P, &p)) \
        : base_type(Direct(BOOST_PP_ENUM_PARAMS(n, p))) \
        { } \
    /**/
#include BOOST_PP_LOCAL_ITERATE()
#undef BOOST_PP_LOCAL_MACRO

        // Device interface.

    std::streamsize read(char_type* s, std::streamsize n);
    void write(const char_type* s, std::streamsize n);
    std::streamoff seek( std::streamoff, std::ios::seekdir,
                         std::ios::openmode = std::ios::in | std::ios::out );
    void close();
    void close(std::ios_base::openmode which);
    void imbue(const std::locale&);

        // Direct device access.

    Direct& operator*() { return d_; }
    Direct* operator->() { return &d_; }
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1310)
private:
    template<typename U>
    static Direct forward(const U& u, mpl::true_) { return u; }
    template<typename U>
    static Direct forward(const U& u, mpl::false_) { return Direct(u); }
#endif
};

//--------------Definition of wrap_direct and unwrap_direct-------------------//

template<typename Device>
struct wrap_direct_traits 
    : mpl::if_<
        is_direct<Device>,
        direct_adapter<Device>,
        Device
        >
    { };

template<typename Device>
typename wrap_direct_traits<Device>::type
inline wrap_direct(Device dev) 
{ 
    typedef typename wrap_direct_traits<Device>::type type;
    return type(dev); 
}

template<typename Device>
static Device& unwrap_direct(Device& d) { return d; }  

template<typename Device>
static Device& unwrap_direct(direct_adapter<Device>& d) { return *d; }  

//--------------Implementation of direct_adapter_base-------------------------//

template<typename Direct>
direct_adapter_base<Direct>::direct_adapter_base(const Direct& d) : d_(d)
{
    init_input(is_convertible<io_category, input>());
    init_output(is_convertible<io_category, output>());
}

template<typename Direct>
void direct_adapter_base<Direct>::init_input(mpl::true_) 
{
    std::pair<char_type*, char_type*> seq = iostreams::input_sequence(d_);
    ptrs_.first().beg = seq.first;
    ptrs_.first().ptr = seq.first;
    ptrs_.first().end = seq.second;
}

template<typename Direct>
void direct_adapter_base<Direct>::init_output(mpl::true_) 
{
    std::pair<char_type*, char_type*> seq = iostreams::output_sequence(d_);
    ptrs_.second().beg = seq.first;
    ptrs_.second().ptr = seq.first;
    ptrs_.second().end = seq.second;
}

//--------------Implementation of direct_adapter------------------------------//

template<typename Direct>
inline std::streamsize direct_adapter<Direct>::read
    (char_type* s, std::streamsize n)
{
    using namespace std;
    pointers& get = ptrs_.first();
    streamsize avail = 
        static_cast<streamsize>(get.end - get.ptr);
    streamsize result = std::min(n, avail);
    std::copy(get.ptr, get.ptr + result, s);
    get.ptr += result;
    return result;
}

template<typename Direct>
inline void direct_adapter<Direct>::write
    (const char_type* s, std::streamsize n)
{
    using namespace std;
    pointers& put = ptrs_.second();
    streamsize capacity = 
        static_cast<streamsize>(put.end - put.ptr);
    streamsize amt = std::min(n, capacity);
    std::copy(s, s + amt, put.ptr);
    put.ptr += amt;
}

template<typename Direct>
inline std::streamoff direct_adapter<Direct>::seek
    ( std::streamoff off, std::ios::seekdir way, 
      std::ios::openmode which )
{
    using namespace std;
    pointers& get = ptrs_.first();
    pointers& put = ptrs_.second();
    if (way == ios::cur && get.ptr != put.ptr)
       bad_seek();
    ptrdiff_t next = 0;
    if ((which & ios::in) || !is_double::value) {
        if (way == ios::beg)
            next = off; 
        else if (way == ios::cur)
            next = get.ptr - get.beg + off; 
        else
            next = get.end - get.beg + off; 
        if (next >= 0 && next < get.end - get.beg)
            get.ptr = get.beg + next;
        else
            bad_seek();
    }
    if ((which & ios::out) && is_double::value) {
        if (way == ios::beg)
            next = off; 
        else if (way == ios::cur)
            next = put.ptr - put.beg + off; 
        else
            next = put.end - put.beg + off; 
        if (next >= 0 && next < put.end - put.beg)
            put.ptr = put.beg + next;
        else
            bad_seek();
    }
    return static_cast<std::streamoff>(next);
}

template<typename Direct>
void direct_adapter<Direct>::close() 
{ 
    BOOST_STATIC_ASSERT((!is_convertible<io_category, two_sequence>::value));
    boost::iostreams::close(d_, std::ios::in | std::ios::out);
}

template<typename Direct>
void direct_adapter<Direct>::close(std::ios_base::openmode which) 
{ 
    BOOST_STATIC_ASSERT((is_convertible<io_category, two_sequence>::value));
    boost::iostreams::close(d_, which);
}

template<typename Direct>
void direct_adapter<Direct>::imbue(const std::locale& loc) 
{ boost::iostreams::imbue(d_, loc); }

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_DIRECT_ADAPTER_HPP_INCLUDED
