// -*-C++-*- boost.h
// <!!----------------------------------------------------------------------> 
// <!! Copyright (C) 1998 Dietmar Kuehl, Claas Solutions GmbH > 
// <!!> 
// <!! Permission to use, copy, modify, distribute and sell this > 
// <!! software for any purpose is hereby granted without fee, provided > 
// <!! that the above copyright notice appears in all copies and that > 
// <!! both that copyright notice and this permission notice appear in > 
// <!! supporting documentation. Dietmar Kuehl and Claas Solutions make no > 
// <!! representations about the suitability of this software for any > 
// <!! purpose. It is provided "as is" without express or implied warranty. > 
// <!!----------------------------------------------------------------------> 

// Author: Dietmar Kuehl dietmar.kuehl@claas-solutions.de 
// Title:  A file used to declare the stuff necessary for WinNT dlls

// -------------------------------------------------------------------------- 

#if !defined(BOOST_H)
#define BOOST_H 1

// --------------------------------------------------------------------------

#if defined(unix) || defined(__unix) || defined(__unix__)
#  define BOOST_DECL
#else
#  ifdef BOOST_EXPORTS
#    define BOOST_DECL __declspec(dllexport)
#  else
#    define BOOST_DECL __declspec(dllimport)
#  endif
#endif

// --------------------------------------------------------------------------

#endif /* BOOST_H */
