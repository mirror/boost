/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library
    http://www.boost.org/

    Copyright (c) 2001-2006 Hartmut Kaiser. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

// Tests #line functionality with out a given file name

#line 5 

//R
//E t_2_003.cpp(8): fatal error: encountered #error directive or #pragma wave stop(): This error should occur at line 8 of "t_2_003.cpp"
#error This error should occur at line 8 of "t_2_003.cpp"
