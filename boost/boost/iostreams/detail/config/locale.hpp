// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Adapted from http://www.boost.org/more/separate_compilation.html, by
// John Maddock.

#ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_LOCALE_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CONFIG_LOCALE_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <cstddef>
#include <locale> 

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif         

//------------------Wide stream support---------------------------------------//

#ifndef BOOST_IOSTREAMS_NO_WIDE_STREAMS
# if defined (BOOST_NO_STD_WSTREAMBUF) && \
     ( !defined(__MSL_CPP__) || defined(_MSL_NO_WCHART_CPP_SUPPORT) ) \
     /**/
#  define BOOST_IOSTREAMS_NO_WIDE_STREAMS
# endif
#endif // #ifndef BOOST_IOSTREAMS_NO_WIDE_STREAMS   

//------------------Locale support--------------------------------------------//

#ifndef BOOST_IOSTREAMS_NO_LOCALE
# if defined(BOOST_NO_STD_LOCALE) || defined(__CYGWIN__)
#  define BOOST_IOSTREAMS_NO_LOCALE
# endif
#endif // #ifndef BOOST_IOSTREAMS_NO_LOCALE
                    
//------------------Put mbstate_t and codecvt in std--------------------------//

// From Robert Ramey's version of utf8_codecvt_facet.
namespace std { 

#if defined(__LIBCOMO__)
    using ::mbstate_t;
#elif defined(BOOST_DINKUMWARE_STDLIB)
    using ::mbstate_t;
#elif defined(__SGI_STL_PORT)
#elif defined(BOOST_NO_STDC_NAMESPACE)
    using ::codecvt;
    using ::mbstate_t;
#endif

} // End namespace std.

//------------------Normalize codecvt::length---------------------------------//

#if !defined(__MSL_CPP__) && !defined(__LIBCOMO__)
    #define BOOST_IOSTREAMS_CODECVT_CV_QUALIFIER const
#else
    #define BOOST_IOSTREAMS_CODECVT_CV_QUALIFIER
#endif

//------------------Support for codecvt with user-defined state types---------//

#if defined(__MSL_CPP__)
# define BOOST_NO_PRIMARY_CODECVT_DEFINITION
#endif

#if defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)
# define BOOST_EMPTY_PRIMARY_CODECVT_DEFINITION
#endif

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_LOCALE_HPP_INCLUDED
