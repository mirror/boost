// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_IOS_TRAITS_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_IOS_TRAITS_HPP_INCLUDED       
  
#include <iosfwd>
#include <boost/iostreams/detail/bool_trait_def.hpp>      
#include <boost/mpl/or.hpp>                         

namespace boost { namespace iostreams { 

BOOST_IOSTREAMS_BOOL_TRAIT_DEF(is_istream, std::basic_istream, 2)
BOOST_IOSTREAMS_BOOL_TRAIT_DEF(is_ostream, std::basic_ostream, 2)
BOOST_IOSTREAMS_BOOL_TRAIT_DEF(is_iostream, std::basic_iostream, 2)
BOOST_IOSTREAMS_BOOL_TRAIT_DEF(is_streambuf, std::basic_streambuf, 2)
BOOST_IOSTREAMS_BOOL_TRAIT_DEF(is_stringstream, std::basic_stringstream, 3)
BOOST_IOSTREAMS_BOOL_TRAIT_DEF(is_stringbuf, std::basic_stringbuf, 3)

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

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_IOS_TRAITS_HPP_INCLUDED
