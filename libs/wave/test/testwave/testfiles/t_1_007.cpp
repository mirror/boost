/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library
    http://www.boost.org/

    Copyright (c) 2001-2006 Hartmut Kaiser. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

//O --variadics

// Tests the correctness of parameter replacement, if the parameter is
// adjacent to an operator '##'.

#define CONCAT(a, b) PRIMITIVE_CONCAT(a, b)
#define PRIMITIVE_CONCAT(a, b) a ## b

//R #line 20 "t_1_007.cpp"
//R 123
CONCAT(1, PRIMITIVE_CONCAT(2, 3))
//R #line 23 "t_1_007.cpp"
//R 123
CONCAT(1, CONCAT(2, 3))
//R #line 26 "t_1_007.cpp"
//R 1 CONCAT(2, 3)
PRIMITIVE_CONCAT(1, CONCAT(2, 3))
