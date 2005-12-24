/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library
    http://www.boost.org/

    Copyright (c) 2001-2006 Hartmut Kaiser. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

// Tests, if macro expansion eats up follow up tokens under certain conditions
// (which it shouldn't).

#define SCAN(x) x

#define BUG BUG_2
#define BUG_2

//R #line 19 "t_1_025.cpp"
SCAN(BUG) 1 2 3 4 5   //R 1 2 3 4 5 

