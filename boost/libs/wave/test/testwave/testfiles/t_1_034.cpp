/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library
    http://www.boost.org/

    Copyright (c) 2001-2006 Hartmut Kaiser. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

// Tests empty __VA_ARGS__ expansion

//O --variadics

#define MACRO1(x, ...)  x -> __VA_ARGS__
#define MACRO2(...)     __VA_ARGS__
#define STR(...)        #__VA_ARGS__

//R #line 19 "t_1_034.cpp"
MACRO1(1,)    //R 1 -> 
MACRO2(1, 2)  //R 1,2 
STR()         //R "" 
