/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library
    http://www.boost.org/

    Copyright (c) 2001-2006 Hartmut Kaiser. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

// Tests, whether #if works when the expression is surrounded by paranthesis

#define WINVER 0x0500

//R #line 17 "t_2_015.cpp"
//R true
#if(WINVER >= 0x0500)
true
#endif
