/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library
    http://www.boost.org/

    Copyright (c) 2001-2006 Hartmut Kaiser. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

// Tests #line functionality with macro expansion required

#define LINE_NO 5
#define FILE_NAME "a_nonexisting_file.cpp"
#line LINE_NO FILE_NAME 

//R
//E a_nonexisting_file.cpp(8): fatal error: encountered #error directive or #pragma wave stop(): This error should occur at line 8 of "a_nonexisting_file.cpp"
#error This error should occur at line 8 of "a_nonexisting_file.cpp"
