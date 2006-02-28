/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library
    http://www.boost.org/

    Copyright (c) 2001-2006 Hartmut Kaiser. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

// The result of macro expansion must be retokenized to find header-name tokens
// of either <file> or "file". Test inclusion using absolute names.

#if !defined(FILE_002_017_CPP)    // avoid #include recursion
#define FILE_002_017_CPP

#include __FILE__

#endif // FILE_002_017_CPP

//R #line 24 "t_2_017.cpp"
//R file t_2_017.cpp
//R #line 24 "t_2_017.cpp"
//R file t_2_017.cpp
file t_2_017.cpp
