// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_PUSH_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_PUSH_HPP_INCLUDED 

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif                    
 
#include <boost/iostreams/adapt.hpp>
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/adapter/range_adapter.hpp>
#include <boost/iostreams/detail/enable_if_stream.hpp>   
#include <boost/iostreams/pipable.hpp>   
#include <boost/iostreams/detail/push_params.hpp>   
#include <boost/iostreams/detail/resolve.hpp>   
#include <boost/preprocessor/control/expr_if.hpp> 
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_convertible.hpp>
                
//------Macros for defining 'push constructors' and overloads of push---------//
          
#define BOOST_IOSTREAMS_ADAPT_STREAM(helper, has_return, arg) \
    BOOST_PP_EXPR_IF(has_return, return) \
    this->helper(boost::iostreams::detail::wrap(arg) BOOST_IOSTREAMS_PUSH_ARGS()); \
    /**/

#define BOOST_IOSTREAMS_DEFINE_PUSH_IMPL1(mode, ch, name, helper, result, has_return ) \
    template<typename IteratorType> \
    BOOST_PP_EXPR_IF(has_return, result) \
    name(IteratorType first, IteratorType last BOOST_IOSTREAMS_PUSH_PARAMS()) \
    { BOOST_PP_EXPR_IF(has_return, return) \
      this->helper( boost::iostreams::detail::range_adapter<mode, IteratorType> \
                    (first, last) BOOST_IOSTREAMS_PUSH_ARGS() ); } \
    template<typename Piper, typename Concept> \
    BOOST_PP_EXPR_IF(has_return, result) \
    name( const boost::iostreams::detail::piper<Piper, Concept>& p \
          BOOST_IOSTREAMS_PUSH_PARAMS() ) \
    { p.push(*this); } \
    /**/

#ifndef BOOST_NO_SFINAE
# define BOOST_IOSTREAMS_DEFINE_PUSH_IMPL2(mode, ch, name, helper, result, has_return ) \
    template<typename T> \
    BOOST_PP_EXPR_IF(has_return, result) \
    name(const T& t BOOST_IOSTREAMS_PUSH_PARAMS() BOOST_IOSTREAMS_DISABLE_IF_STREAM(T)) \
    { BOOST_PP_EXPR_IF(has_return, return) \
      this->helper( boost::iostreams::detail::resolve<mode, ch>(t) \
                    BOOST_IOSTREAMS_PUSH_ARGS() ); } \
    template<typename T> \
    BOOST_PP_EXPR_IF(has_return, result) \
    name( T& t BOOST_IOSTREAMS_PUSH_PARAMS() \
          BOOST_IOSTREAMS_ENABLE_IF_STREAM(T)) \
    { BOOST_IOSTREAMS_ADAPT_STREAM(helper, has_return, t) } \
    /**/
#else // #ifndef BOOST_NO_SFINAE
# define BOOST_IOSTREAMS_DEFINE_PUSH_IMPL2(mode, ch, name, helper, result, has_return )  \
    template<typename T> \
    BOOST_PP_EXPR_IF(has_return, result) \
    name(const T& t BOOST_IOSTREAMS_PUSH_PARAMS()) \
    { BOOST_PP_EXPR_IF(has_return, return) \
      this->helper( boost::iostreams::detail::resolve<mode, ch>(t) \
                    BOOST_IOSTREAMS_PUSH_ARGS() ); } \
    template<typename CharType, typename TraitsType> \
    BOOST_PP_EXPR_IF(has_return, result) \
    name(std::basic_streambuf<CharType, TraitsType>& sb BOOST_IOSTREAMS_PUSH_PARAMS()) \
    { BOOST_IOSTREAMS_ADAPT_STREAM(helper, has_return, sb); } \
    template<typename CharType, typename TraitsType> \
    BOOST_PP_EXPR_IF(has_return, result) \
    name(std::basic_istream<CharType, TraitsType>& is BOOST_IOSTREAMS_PUSH_PARAMS()) \
    { BOOST_STATIC_ASSERT((boost::is_convertible<input_seekable, mode>::value)); \
      BOOST_IOSTREAMS_ADAPT_STREAM(helper, has_return, is); } \
    template<typename CharType, typename TraitsType> \
    BOOST_PP_EXPR_IF(has_return, result) \
    name(std::basic_ostream<CharType, TraitsType>& os BOOST_IOSTREAMS_PUSH_PARAMS()) \
    { BOOST_STATIC_ASSERT((boost::is_convertible<output_seekable, mode>::value)); \
      BOOST_IOSTREAMS_ADAPT_STREAM(helper, has_return, os); } \
    template<typename CharType, typename TraitsType> \
    BOOST_PP_EXPR_IF(has_return, result) \
    name(std::basic_iostream<CharType, TraitsType>& io BOOST_IOSTREAMS_PUSH_PARAMS()) \
    { BOOST_STATIC_ASSERT((boost::is_convertible<seekable, mode>::value)); \
      BOOST_IOSTREAMS_ADAPT_STREAM(helper, has_return, io); } \
    /**/
#endif // #ifndef BOOST_NO_SFINAE

#define BOOST_IOSTREAMS_DEFINE_PUSH_IMPL(mode, ch, name, helper, result, has_return) \
    BOOST_IOSTREAMS_DEFINE_PUSH_IMPL1(mode, ch, name, helper, result, has_return) \
    BOOST_IOSTREAMS_DEFINE_PUSH_IMPL2(mode, ch, name, helper, result, has_return) \
    /**/

//
// Macro: BOOST_IOSTREAMS_DEFINE_PUSH_CONSTRUCTOR(mode, name, helper).
// Description: Defines overloads with name 'name' which forward to a function
//      'helper' which takes a filter or devide by const reference.
//
#define BOOST_IOSTREAMS_DEFINE_PUSH_CONSTRUCTOR(mode, ch, name, helper)  \
    BOOST_IOSTREAMS_DEFINE_PUSH_IMPL(mode, ch, name, helper, _, 0)       \
    /**/

//
// Macro: BOOST_IOSTREAMS_DEFINE_PUSH_CONSTRUCTOR(mode, name, helper).
// Description: Defines constructors which forward to a function
//      'helper' which takes a filter or device by const reference.
//
#define BOOST_IOSTREAMS_DEFINE_PUSH(mode, ch, name, helper)            \
    BOOST_IOSTREAMS_DEFINE_PUSH_IMPL(mode, ch, name, helper, void, 1)  \
    /**/

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_PUSH_HPP_INCLUDED
