/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library
    http://www.boost.org/

    Copyright (c) 2001-2006 Hartmut Kaiser. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

// Tests the validity of whitespace handling during macro expansion

#define MACRO() 123

//R #line 16 "t_1_022.cpp"
//R 123
MACRO()
//R #line 19 "t_1_022.cpp"
//R 123
MACRO
()
//R #line 23 "t_1_022.cpp"
//R 123
MACRO(
)
