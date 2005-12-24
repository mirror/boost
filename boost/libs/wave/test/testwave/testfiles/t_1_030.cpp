/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library
    http://www.boost.org/

    Copyright (c) 2001-2006 Hartmut Kaiser. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

// Tests, whether an empty macro prevents another macro from expansion

#define EMPTY()
#define SCAN(x) x
#define MACRO(x) (x)

//R #line 17 "t_1_030.cpp"
SCAN( MACRO EMPTY() )(1)    //R (1) 
