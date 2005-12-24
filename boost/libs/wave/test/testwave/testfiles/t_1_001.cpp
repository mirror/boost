/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library
    http://www.boost.org/

    Copyright (c) 2001-2006 Hartmut Kaiser. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

// Test macro expansion order
#define A(x, y) x, y
#define B(x, y) [x][y]
#define C(x) B(x)

//R #line 16 "t_1_001.cpp"
C( A(2, 3) )      //R [2][3] 
