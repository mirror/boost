/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library
    http://www.boost.org/

    Copyright (c) 2001-2006 Hartmut Kaiser. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

// The result of macro expansion must be
// retokenized to find header-name tokens
// of either <file> or "file"

//O -S.

#if !defined(FILE_002_009_CPP)    // avoid #include recursion
#define FILE_002_009_CPP

#define SYSTEM_HEADER <t_2_009.cpp>
#define USER_HEADER   "t_2_009.cpp"

//R #line 24 "t_2_009.cpp"
//R including <t_2_009.cpp>
including <t_2_009.cpp>
#include SYSTEM_HEADER

//R #line 29 "t_2_009.cpp"
//R including "t_2_009.cpp"
including "t_2_009.cpp"
#include USER_HEADER

#endif // FILE_002_009_CPP
