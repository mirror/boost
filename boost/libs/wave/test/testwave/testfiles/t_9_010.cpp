/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library
    http://www.boost.org/

    Copyright (c) 2001-2006 Hartmut Kaiser. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

// Tests, whether adjacent tokens are separated by whitespace if the adjacency
// is created by macro expansion

#define A(x) x

//R #line 16 "t_9_010.cpp"
A(1)1         //R 1 1 
A(1)X         //R 1 X 
A(X)1         //R X 1 
A(X)X         //R X X 

#define CAT(a, b) PRIMITIVE_CAT(a, b)
#define PRIMITIVE_CAT(a, b) a ## b

#define X() B
#define ABC 1

//R #line 28 "t_9_010.cpp"
CAT(A, X() C) //R AB C 
CAT(A, X()C)  //R AB C 
