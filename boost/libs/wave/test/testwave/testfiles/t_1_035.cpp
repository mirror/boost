/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library
    http://www.boost.org/

    Copyright (c) 2001-2006 Hartmut Kaiser. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

// Tests token pasting with empty empty arguments

//O --variadics

#define PASTE1(a, b, c, d) a ## b ## c ## d
#define PASTE2(a, b, c, d) a##b##c##d

//R #line 18 "t_1_035.cpp"
PASTE1(1, ,3,4)   //R 134 
PASTE1(1,,3,4)    //R 134 
PASTE1(1, , , 4)  //R 14 
//R
PASTE2(1, ,3,4)   //R 134 
PASTE2(1,,3,4)    //R 134 
PASTE2(1, , , 4)  //R 14 
