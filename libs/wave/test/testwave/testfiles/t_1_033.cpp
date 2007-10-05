/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library
    http://www.boost.org/

    Copyright (c) 2001-2006 Hartmut Kaiser. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

// Tests the stringize operator in conjunction with varidic macros

//O --variadics

#define STR(...) #__VA_ARGS__

//R #line 17 "t_1_033.cpp"
STR(1, 2, 3)            //R "1, 2, 3" 
STR(1,2,3)              //R "1,2,3" 
STR(1 , 2 , 3)          //R "1 , 2 , 3" 
STR( 1  ,   2  ,   3 )  //R "1 , 2 , 3" 
