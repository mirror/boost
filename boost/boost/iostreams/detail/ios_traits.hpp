// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_IOS_TRAITS_HPP_INCLUDED
#define BOOST_IOSTREAMS_IOS_TRAITS_HPP_INCLUDED       
 
#include <iterator>                            // back_insert_iterator.    
#include <iosfwd>
#include <boost/config.hpp>                    // static const.    
#include <boost/mpl/aux_/lambda_support.hpp>   
#include <boost/mpl/and.hpp>               
#include <boost/mpl/bool.hpp>               
#include <boost/mpl/or.hpp>               
#include <boost/preprocessor/cat.hpp>          
#include <boost/preprocessor/repetition/enum_params.hpp>        
#include <boost/type_traits/is_base_and_derived.hpp>            
#include <boost/type_traits/is_same.hpp>             
#include <boost/type_traits/detail/yes_no_type.hpp>     

//----------------------------------------------------------------------------//

// 
// Macro name: BOOST_IOSTREAMS_BOOL_TRAIT_DEF
// Description: Used to generate the traits classes is_istream, is_ostream,
//      etc.
//
#define BOOST_IOSTREAMS_BOOL_TRAIT_DEF(trait, type, arity) \
    namespace boost { namespace iostreams { namespace detail { \
      template<BOOST_PP_ENUM_PARAMS(arity, typename T)> \
      type_traits::yes_type BOOST_PP_CAT(trait, _helper) \
          (const volatile type<BOOST_PP_ENUM_PARAMS(arity, T)>*); \
      type_traits::no_type BOOST_PP_CAT(trait, _helper)(...); \
      template<typename T> \
      struct BOOST_PP_CAT(trait, _impl) { \
           BOOST_STATIC_CONSTANT(bool, value = \
               (sizeof(BOOST_PP_CAT(trait, _helper)(static_cast<T*>(0))) == \
                sizeof(type_traits::yes_type))); \
      }; \
    } \
    template<typename T> \
    struct trait \
        : mpl::bool_<detail::BOOST_PP_CAT(trait, _impl)<T>::value> \
    { BOOST_MPL_AUX_LAMBDA_SUPPORT(1, trait, (T)) }; \
    } } \
    /**/

// 
// Macro name: BOOST_IOSTREAMS_IOS_TRAIT_DEF
// Description: Used to generate the traits classes is_istream, is_ostream
//      is_iostream and is_streambuf on compilers which support 
//      has_xxx.
//
#define BOOST_IOSTREAMS_IOS_TRAIT_DEF(trait, base) \
    namespace boost { namespace iostreams { namespace detail { \
      template<typename T> \
      struct BOOST_PP_CAT(trait, _impl) { \
          template<typename U> \
          struct derived_from_base { \
              typedef typename U::char_type                    char_type; \
              typedef typename U::traits_type                  traits_type; \
              typedef mpl::or_< \
                          is_same< \
                              base<char_type, traits_type>, U \
                          >, \
                          is_base_and_derived< \
                              base<char_type, traits_type>, U \
                          > \
                      >                                        type; \
              BOOST_STATIC_CONSTANT(bool, value = type::value); \
          }; \
          typedef mpl::and_< \
                       mpl::bool_<has_char_type<T>::value>, \
                       mpl::bool_<has_traits_type<T>::value>, \
                       derived_from_base<T> \
                  >                                            type; \
          BOOST_STATIC_CONSTANT(bool, value = type::value); \
      }; \
    } \
    template<typename T> \
    struct trait \
        : mpl::bool_<detail::BOOST_PP_CAT(trait, _impl)<T>::value> \
    { BOOST_MPL_AUX_LAMBDA_SUPPORT(1, trait, (T)) }; \
    } } \
    /**/

BOOST_IOSTREAMS_BOOL_TRAIT_DEF(is_back_inserter, std::back_insert_iterator, 1)
BOOST_IOSTREAMS_BOOL_TRAIT_DEF(is_istream, std::basic_istream, 2)
BOOST_IOSTREAMS_BOOL_TRAIT_DEF(is_ostream, std::basic_ostream, 2)
BOOST_IOSTREAMS_BOOL_TRAIT_DEF(is_iostream, std::basic_iostream, 2)
BOOST_IOSTREAMS_BOOL_TRAIT_DEF(is_streambuf, std::basic_streambuf, 2)
BOOST_IOSTREAMS_BOOL_TRAIT_DEF(is_stringstream, std::basic_stringstream, 3)
BOOST_IOSTREAMS_BOOL_TRAIT_DEF(is_stringbuf, std::basic_stringbuf, 3)

namespace boost { namespace iostreams { 

//
// Template name: is_stream.
// Description: Type traits template returning true if T is the same as or
//      derived from a specialization of std::basic_istream, std::basic_ostream
//      or std::basic_streambuf. Ignores cv-qualifiers.
// Note: If T derives non-publicly from a speicialization of basic_streambuf,
//      the expression is_streambuf<T>::type will cause a compiler error. Since
//      it is common for streams to derive privately from basic_streambuf,
//      is_streambuf must come last in the disjunction below.
//
template<typename T>
struct is_std_io
    : mpl::or_< is_istream<T>, is_ostream<T>, is_streambuf<T> >
    { };

} } // End namespace iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_IOS_TRAITS_HPP_INCLUDED
