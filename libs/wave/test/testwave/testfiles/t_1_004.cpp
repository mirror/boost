/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library
    http://www.boost.org/

    Copyright (c) 2001-2006 Hartmut Kaiser. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

//O --variadics

// Tests macro expansion order in conjunction with the need to skip expansion 
// of the same macro as it is currently expanded.

#define CONCAT(a, b) a ## b
#define CONCAT_INDIRECT() CONCAT

//R #line 20 "t_1_004.cpp"
//R CONCAT(1, 2)
CONCAT(CON, CAT)(1, 2)
//R #line 23 "t_1_004.cpp"
//R CONCAT(1, 2)
CONCAT(CON, CAT(1, 2))
//R #line 26 "t_1_004.cpp"
//R 12
CONCAT(CONCAT_, INDIRECT)()(1, 2)
//R #line 29 "t_1_004.cpp"
//R CONCAT(1, 2)
CONCAT(CONCAT_, INDIRECT())(1, 2)
//R #line 32 "t_1_004.cpp"
//R 1 CONCAT(2, 3)
CONCAT(1, CONCAT(2, 3))
