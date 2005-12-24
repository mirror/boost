/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library
    http://www.boost.org/

    Copyright (c) 2001-2006 Hartmut Kaiser. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

// Tests continuing scanning into the underlying input stream after expanding
// a macro, if this is appropriate

#define A Token1 B
#define B() Token2

//R #line 18 "t_1_016.cpp"
//R Token1 Token2
A()
