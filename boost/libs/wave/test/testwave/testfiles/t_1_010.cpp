/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library
    http://www.boost.org/

    Copyright (c) 2001-2006 Hartmut Kaiser. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

// Test, if wrongly placed '##' operators are detected

#define TEST1() A ## B
#define TEST2() A ##

//R #line 17 "t_1_010.cpp"
//R AB
TEST1()
//E t_1_010.cpp(19): error: ill formed preprocessing operator: concat ('##')
TEST2()    // error
