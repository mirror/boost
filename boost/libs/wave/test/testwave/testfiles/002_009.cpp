/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library
    http://www.boost.org/

    Copyright (c) 2001-2005 Hartmut Kaiser. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

// The result of macro expansion must be
// retokenized to find header-name tokens
// of either <file> or "file"

//O -S.

#if !defined(FILE_002_009_CPP)    // avoid #include recursion
#define FILE_002_009_CPP

#define SYSTEM_HEADER <002_009.cpp>
#define USER_HEADER   "002_009.cpp"

//R #line 24 "002_009.cpp"
//R including <002 _009.cpp>
including <002_009.cpp>
#include SYSTEM_HEADER

//R #line 29 "002_009.cpp"
//R including "002_009.cpp"
including "002_009.cpp"
#include USER_HEADER

#endif // FILE_002_009_CPP
