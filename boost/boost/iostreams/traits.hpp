// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// 
// Contains metafunctions io_char, io_category and io_mode used for deducing 
// the i/o category and i/o mode of a model of Filter or Device.
//
// Also contains several utility metafunctions, functions and macros.
//

#ifndef BOOST_IOSTREAMS_IO_TRAITS_HPP_INCLUDED
#define BOOST_IOSTREAMS_IO_TRAITS_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif              

#include <iosfwd>                           // streamsize.
#include <string>                           // char_traits. 
#include <boost/config.hpp>                 // partial spec, deduced typename.
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/select.hpp>        
#include <boost/iostreams/detail/ios_traits.hpp>     
#include <boost/iostreams/detail/is_iterator_range.hpp>        
#include <boost/iostreams/detail/wrap_unwrap.hpp> 
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>      
#include <boost/mpl/int.hpp>  
#include <boost/range/iterator_range.hpp>
#include <boost/range/value_type.hpp>
#include <boost/type_traits/is_convertible.hpp>     
#define BOOST_SELECT_BY_SIZE_MAX_CASE 9     
#include <boost/iostreams/detail/select_by_size.hpp>                     

namespace boost { namespace iostreams {          

//------------------Definitions of io_char------------------------------------//

namespace detail {

template<typename T>
struct get_char_type { typedef typename T::char_type type; };

} // End namespace detail.

#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION //---------------------------//

template<typename T>
struct io_char 
    : detail::get_char_type<
          typename detail::unwrapped_type<T>::type
      > 
    { };

template<typename Iter>
struct io_char< iterator_range<Iter> > {
    typedef typename iterator_value<Iter>::type type;
};

#else // #ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION //------------------//

template<typename T>
struct io_char {
    template<typename U>
    struct get_value_type {
        typedef typename range_value<U>::type type;
    };
    typedef typename 
            mpl::eval_if<
                is_iterator_range<T>,
                get_value_type<T>,
                detail::get_char_type<
                    BOOST_DEDUCED_TYPENAME detail::unwrapped_type<T>::type
                >
            >::type type;
};

#endif // #ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION //-----------------//

//------------------Definitions of io_char, io_category-----------------------//

namespace detail {

template<typename T>
struct member_io_category { typedef typename T::io_category type; };

} // End namespace detail.

#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION //---------------------------//

template<typename T>
struct io_category {
    typedef typename  
            select<
                is_iostream<T>,      iostream_tag, 
                is_istream<T>,       istream_tag, 
                is_ostream<T>,       ostream_tag,
                is_streambuf<T>,     streambuf_tag,
                is_stringstream<T>,  stringstream_tag,
                is_stringbuf<T>,     stringbuf_tag,
                mpl::true_,          lazy< detail::member_io_category<T> >
            >::type type;     
};
template<typename T>
struct io_category< boost::reference_wrapper<T> > 
    : io_category<T> 
    { };
template<typename T>
struct io_category< const boost::reference_wrapper<T> > 
    : io_category<T> 
    { };

#else // #ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION //------------------//

template<typename T>
struct io_category {
    typedef typename detail::unwrapped_type<T>::type U;
    typedef typename  
            select<
                is_iostream<U>,       iostream_tag, 
                is_istream<U>,        istream_tag, 
                is_ostream<U>,        ostream_tag,
                is_streambuf<U>,      streambuf_tag,
                is_stringstream<U>,   stringstream_tag,
                is_stringbuf<U>,      stringbuf_tag,
                mpl::true_,           lazy< detail::member_io_category<U> >
            >::type type;     
};

#endif // #ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION //-----------------//

//------------------Definition of get_category--------------------------------//

// 
// Returns an object of type io_category<T>::type.
// 
template<typename T>
inline typename io_category<T>::type get_category(const T&) 
{ typedef typename io_category<T>::type category; return category(); }

//----------Definition of io_int----------------------------------------------//

template<typename T>
struct io_int { 
    typedef std::char_traits<
                BOOST_DEDUCED_TYPENAME io_char<T>::type
            > traits_type; 
    typedef typename traits_type::int_type type; 
};

//------------------Definition of mode----------------------------------------//

namespace detail {

template<int N> struct io_mode_impl;

#define BOOST_IOSTREAMS_MODE_IMPL_SPEC(tag_, id_) \
    case_<id_> io_mode_impl_helper(tag_); \
    template<> struct io_mode_impl<id_> { typedef tag_ type; }; \
    /**/
BOOST_IOSTREAMS_MODE_IMPL_SPEC(input, 1)
BOOST_IOSTREAMS_MODE_IMPL_SPEC(output, 2)
BOOST_IOSTREAMS_MODE_IMPL_SPEC(bidirectional, 3)
BOOST_IOSTREAMS_MODE_IMPL_SPEC(input_seekable, 4)
BOOST_IOSTREAMS_MODE_IMPL_SPEC(output_seekable, 5)
BOOST_IOSTREAMS_MODE_IMPL_SPEC(seekable, 6)
BOOST_IOSTREAMS_MODE_IMPL_SPEC(dual_seekable, 7)
BOOST_IOSTREAMS_MODE_IMPL_SPEC(bidirectional_seekable, 8)
BOOST_IOSTREAMS_MODE_IMPL_SPEC(dual_use, 9)
#undef BOOST_IOSTREAMS_MODE_IMPL_SPEC

template<typename T>
struct io_mode_id {
    typedef typename io_category<T>::type category;
    BOOST_SELECT_BY_SIZE(int, value, detail::io_mode_impl_helper(category()));
};

} // End namespace detail.

template<typename T> // Borland 5.6.4 requires this circumlocution.
struct io_mode : detail::io_mode_impl< detail::io_mode_id<T>::value > { };
                
//----------Definition of convenience metafunctions---------------------------//

namespace detail {

template<typename T>
struct is_smart
    : is_convertible<T, detail::smart_tag>
    { };

} // End namespace detail.

//----------Definition of macros----------------------------------------------//

#define BOOST_IOSTREAMS_CHAR_TYPE(T) typename boost::iostreams::io_char<T>::type
#define BOOST_IOSTREAMS_CATEGORY(T) \
    typename boost::iostreams::io_category<T>::type \
    /**/
#define BOOST_IOSTREAMS_INT_TYPE(T) typename io_int<T>::type
#define BOOST_IOSTREAMS_STREAMBUF_TYPEDEFS(Tr) \
    typedef Tr traits_type; \
    typedef typename traits_type::int_type int_type; \
    typedef typename traits_type::off_type off_type; \
    typedef typename traits_type::pos_type pos_type; \
    /**/

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_IO_TRAITS_HPP_INCLUDED
