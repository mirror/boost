/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library
    http://www.boost.org/

    Copyright (c) 2001-2006 Hartmut Kaiser. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

// Tests concatination of more than two parameters

#define CAT3_1(a, b, c) a##b##c
#define CAT3_2(a, b, c) a ## b ## c

#define CAT4_1(a, b, c, d) a##b##c##d
#define CAT4_2(a, b, c, d) a ## b ## c ## d

//R #line 19 "t_1_029.cpp"
CAT3_1(1, 0, 0)       //R 100 
CAT3_2(1, 0, 0)       //R 100 
//R
CAT4_1(1, 0, 0, 2)    //R 1002 
CAT4_2(1, 0, 0, 2)    //R 1002 
