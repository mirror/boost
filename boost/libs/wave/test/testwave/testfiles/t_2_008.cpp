/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library
    http://www.boost.org/

    Copyright (c) 2001-2006 Hartmut Kaiser. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

// Tests #include statements with macros as argmuments

//R
//E t_2_008.cpp(15): error: could not find include file: some_include_file.h
#define INCLUDE_FILE "some_include_file.h"
#include INCLUDE_FILE
