#ifndef BOOST_ARCHIVE_DETAIL_DECL_HPP
#define BOOST_ARCHIVE_DETAIL_DECL_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
//  decl.hpp
//
//  © Copyright Robert Ramey 2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/serialization

//----------------------------------------------------------------------------// 

// This header implements separate compilation features as described in
// http://www.boost.org/more/separate_compilation.html

#include <boost/config.hpp>

#if defined(BOOST_HAS_DECLSPEC) \
&& (defined(BOOST_ALL_DYN_LINK) || defined(BOOST_SERIALIZATION_DYN_LINK))

#if defined(BOOST_ARCHIVE)
    #define BOOST_DECL_ARCHIVE __declspec(dllexport)
    #pragma message( "BOOST_DECL_ARCHIVE __declspec(dllexport)" )
    #define BOOST_DECL_ARCHIVE_OR_WARCHIVE __declspec(dllexport)
    #pragma message( "BOOST_DECL_ARCHIVE_OR_WARCHIVE __declspec(dllexport)" )
#elif defined(BOOST_WARCHIVE)
    #define BOOST_DECL_WARCHIVE __declspec(dllexport)
    #pragma message( "BOOST_DECL_WARCHIVE __declspec(dllexport)" )
    #define BOOST_DECL_ARCHIVE_OR_WARCHIVE __declspec(dllexport)
    #pragma message( "BOOST_DECL_ARCHIVE_OR_WARCHIVE __declspec(dllexport)" )
#endif

#if !defined(BOOST_DECL_ARCHIVE)
    #define BOOST_DECL_ARCHIVE __declspec(dllimport)
    #pragma message( "BOOST_DECL_ARCHIVE __declspec(dllimport)" )
#endif
#if !defined(BOOST_DECL_WARCHIVE)
    #define BOOST_DECL_WARCHIVE __declspec(dllimport)
    #pragma message( "BOOST_DECL_WARCHIVE __declspec(dllimport)" )
#endif
#if !defined(BOOST_DECL_ARCHIVE_OR_WARCHIVE)
    #define BOOST_DECL_ARCHIVE_OR_WARCHIVE __declspec(dllimport)
    #pragma message( "BOOST_DECL_WARCHIVE_OR_WARCHIVE __declspec(dllimport)" )
#endif
// and reinitialize include guard so in case another archive header is
// included.
#if defined(BOOST_ARCHIVE_DETAIL_UNDECL_HPP)
    #undef BOOST_ARCHIVE_DETAIL_UNDECL_HPP
#endif

#else // BOOST_HAS_DECLSPEC && ...

    #define BOOST_DECL_ARCHIVE 
    #define BOOST_DECL_WARCHIVE 
    #define BOOST_DECL_ARCHIVE_OR_WARCHIVE 

#endif // BOOST_HAS_DECLSPEC


#endif // BOOST_ARCHIVE_DETAIL_DECL_HPP
