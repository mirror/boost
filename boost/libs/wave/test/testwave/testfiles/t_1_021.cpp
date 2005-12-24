/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library
    http://www.boost.org/

    Copyright (c) 2001-2006 Hartmut Kaiser. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

// Tests continuing scanning into the underlying input stream after expanding
// a macro, if this is appropriate

#define MACRO() X + Y NEXT
#define X 1
#define Y 2
#define NEXT() ...

//R #line 20 "t_1_021.cpp"
//R 1 + 2 ...
MACRO()()
