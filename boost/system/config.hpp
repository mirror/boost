//  boost/system/config.hpp  -----------------------------------------------------------//

//  Copyright Beman Dawes 2003, 2006

//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/system for documentation.

#ifndef BOOST_SYSTEM_CONFIG_HPP                  
#define BOOST_SYSTEM_CONFIG_HPP

#include <boost/config.hpp>

//  BOOST_POSIX_API or BOOST_WINDOWS_API specify which API to use.
//  If not specified, a sensible default will be applied.

# if defined( BOOST_WINDOWS_API ) && defined( BOOST_POSIX_API )
#   error both BOOST_WINDOWS_API and BOOST_POSIX_API are defined
# elif !defined( BOOST_WINDOWS_API ) && !defined( BOOST_POSIX_API )
#   if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
      // All Win32 development environments, including 64-bit Windows and MinGW, define 
      // _WIN32 or one of its variant spellings. Note that Cygwin is a POSIX environment,
      // so does not define _WIN32 or its variants.
#     define BOOST_WINDOWS_API
#   else
#     define BOOST_POSIX_API 
#   endif
# endif

//  enable dynamic or static linking as requested --------------------------------------//

#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_SYSTEM_DYN_LINK)
# if defined(BOOST_SYSTEM_SOURCE)
#   define BOOST_SYSTEM_DECL BOOST_SYMBOL_EXPORT
# else 
#   define BOOST_SYSTEM_DECL BOOST_SYMBOL_IMPORT
# endif
#else
# define BOOST_SYSTEM_DECL
#endif

//  enable automatic library variant selection  ----------------------------------------// 

#if !defined(BOOST_SYSTEM_SOURCE) && !defined(BOOST_ALL_NO_LIB) && !defined(BOOST_SYSTEM_NO_LIB)
//
// Set the name of our library, this will get undef'ed by auto_link.hpp
// once it's done with it:
//
#define BOOST_LIB_NAME boost_system
//
// If we're importing code from a dll, then tell auto_link.hpp about it:
//
#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_SYSTEM_DYN_LINK)
#  define BOOST_DYN_LINK
#endif
//
// And include the header that does the work:
//
#include <boost/config/auto_link.hpp>
#endif  // auto-linking disabled

#endif // BOOST_SYSTEM_CONFIG_HPP

