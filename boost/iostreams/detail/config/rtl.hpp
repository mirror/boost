/*
 * Distributed under the Boost Software License, Version 1.0.(See accompanying 
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)
 * 
 * See http://www.boost.org/libs/iostreams for documentation.
 *
 * Defines preprocessor symbols expanding to the names of functions in the 
 * C runtime library used to access file descriptors and to the type used
 * to store file offsets for seeking.
 * 
 * File:        boost/iostreams/detail/config/rtl.hpp
 * Date:        Wed Dec 26 11:58:11 MST 2007
 * 
 * Copyright:   2007 CodeRage
 * Author:      Jonathan Turkanis
 */

#ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_RTL_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CONFIG_RTL_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/iostreams/detail/config/windows_posix.hpp>

// Handle open, close, read, and write
#if defined(__BORLANDC__)
# define BOOST_IOSTREAMS_RTL(x) BOOST_JOIN(_rtl_, x)
#else
# if defined(BOOST_IOSTREAMS_WINDOWS) && !defined(__CYGWIN__)
#  define BOOST_IOSTREAMS_RTL(x) BOOST_JOIN(_, x)
# else
#  define BOOST_IOSTREAMS_RTL(x) ::x
# endif
#endif
#define BOOST_IOSTREAMS_FD_OPEN   BOOST_IOSTREAMS_RTL(open)
#define BOOST_IOSTREAMS_FD_CLOSE  BOOST_IOSTREAMS_RTL(close)
#define BOOST_IOSTREAMS_FD_READ   BOOST_IOSTREAMS_RTL(read)
#define BOOST_IOSTREAMS_FD_WRITE  BOOST_IOSTREAMS_RTL(write)

// Handle lseek, ftruncate, stat, and off_t
#if defined(BOOST_IOSTREAMS_WINDOWS) && !defined(__CYGWIN__)
# if defined(BOOST_MSVC) || defined(__MSVCRT__) // MSVC, MinGW
#  define BOOST_IOSTREAMS_FD_SEEK    _lseeki64
#  define BOOST_IOSTREAMS_FD_OFFSET  __int64
# else                                          // Borland, Metrowerks, ...
#  define BOOST_IOSTREAMS_FD_SEEK    lseek  
#  define BOOST_IOSTREAMS_FD_OFFSET  long
# endif
#else // Non-windows
# if defined(_LARGEFILE64_SOURCE) && \
         (!defined(_FILE_OFFSET_BITS) || _FILE_OFFSET_BITS != 64) || \
     defined(BOOST_IOSTREAMS_HAS_LSEEK64) \
     /**/
#  define BOOST_IOSTREAMS_FD_SEEK      lseek64  // GCC for some 32-bit *nix
#  define BOOST_IOSTREAMS_FD_TRUNCATE  ftruncate64
#  define BOOST_IOSTREAMS_FD_STAT      stat64
#  define BOOST_IOSTREAMS_FD_OFFSET    off64_t
# else                                          // Cygwin, Darwin, ...
#  define BOOST_IOSTREAMS_FD_SEEK      lseek
#  define BOOST_IOSTREAMS_FD_TRUNCATE  ftruncate
#  define BOOST_IOSTREAMS_FD_STAT      stat
#  define BOOST_IOSTREAMS_FD_OFFSET    off_t
# endif
#endif

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_RTL_HPP_INCLUDED
