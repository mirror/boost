/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library
    http://www.boost.org/

    Copyright (c) 2001-2006 Hartmut Kaiser. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

// The follwoing is a parametized partially expanding concatenation macro.
// It is a extremly good test of expansion order and the order of operations 
// during macro expansion in general. 

#define CAT(a, b) a ## b

#define PARTIAL_CAT(i) CAT(PARTIAL_CAT_, i)

#define PARTIAL_CAT_0(a, b) CAT(a, b)
#define PARTIAL_CAT_1(a, b) CAT(PARTIAL ## a, b)
#define PARTIAL_CAT_2(a, b) CAT(a, b ## PARTIAL)
#define PARTIAL_CAT_3(a, b) CAT(PARTIAL ## a, b ## PARTIAL)

#define PARTIAL
#define PARTIALPARTIAL

#define X Token1
#define Y Token2

//R #line 31 "t_1_008.cpp"
//R Token1Token2
PARTIAL_CAT(0)( PARTIAL X, Y PARTIAL )
//R #line 34 "t_1_008.cpp"
//R XToken2
PARTIAL_CAT(1)( PARTIAL X, Y PARTIAL )
//R #line 37 "t_1_008.cpp"
//R Token1Y
PARTIAL_CAT(2)( PARTIAL X, Y PARTIAL )
//R #line 40 "t_1_008.cpp"
//R XY
PARTIAL_CAT(3)( PARTIAL X, Y PARTIAL )
