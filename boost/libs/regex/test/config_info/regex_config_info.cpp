/*
 *
 * Copyright (c) 2003
 * Dr John Maddock
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Dr John Maddock makes no representations
 * about the suitability of this software for any purpose.  
 * It is provided "as is" without express or implied warranty.
 *
 */

//
// This program extends config_info to print out regex library
// configuration information.  We do this by redfining the main
// provided by config_info, our real main will call it later:
//
#ifndef OLD_MAIN
#  define OLD_MAIN info_main
#endif

#define main OLD_MAIN
#include <libs/config/test/config_info.cpp>
#undef main
#ifndef NEW_MAIN
#  define NEW_MAIN main
#endif
#include <boost/regex.hpp>

int NEW_MAIN()
{
   OLD_MAIN();

   print_separator();
   PRINT_MACRO(BOOST_REGEX_USER_CONFIG);
   PRINT_MACRO(BOOST_REGEX_USE_C_LOCALE);
   PRINT_MACRO(BOOST_REGEX_USE_CPP_LOCALE);
   PRINT_MACRO(BOOST_REGEX_HAS_DLL_RUNTIME);
   PRINT_MACRO(BOOST_REGEX_DYN_LINK);
   PRINT_MACRO(BOOST_REGEX_NO_LIB);
   PRINT_MACRO(BOOST_REGEX_NO_TEMPLATE_SWITCH_MERGE);
   PRINT_MACRO(BOOST_REGEX_NO_W32);
   PRINT_MACRO(BOOST_REGEX_NO_BOOL);
   PRINT_MACRO(BOOST_REGEX_NO_EXTERNAL_TEMPLATES);
   PRINT_MACRO(BOOST_REGEX_NO_FWD);
   PRINT_MACRO(BOOST_REGEX_V3);
   PRINT_MACRO(BOOST_REGEX_HAS_MS_STACK_GUARD);
   PRINT_MACRO(BOOST_REGEX_RECURSIVE);
   PRINT_MACRO(BOOST_REGEX_NON_RECURSIVE);
   PRINT_MACRO(BOOST_REGEX_BLOCKSIZE);
   PRINT_MACRO(BOOST_REGEX_MAX_BLOCKS);
   PRINT_MACRO(BOOST_REGEX_MAX_CACHE_BLOCKS);
   PRINT_MACRO(BOOST_NO_WREGEX);
   PRINT_MACRO(BOOST_REGEX_NO_FILEITER);
   PRINT_MACRO(BOOST_REGEX_STATIC_LINK);
   PRINT_MACRO(BOOST_REGEX_DYN_LINK);
   PRINT_MACRO(BOOST_REGEX_DECL);
   PRINT_MACRO(BOOST_REGEX_CALL);
   PRINT_MACRO(BOOST_REGEX_CCALL);
   PRINT_MACRO(BOOST_REGEX_MAX_STATE_COUNT);

#if defined(BOOST_REGEX_CONFIG_INFO) && !defined(NO_RECURSE)
   print_regex_library_info();
#endif

   return 0;
}


