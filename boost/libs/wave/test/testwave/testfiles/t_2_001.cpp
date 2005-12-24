/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library
    http://www.boost.org/

    Copyright (c) 2001-2006 Hartmut Kaiser. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

// Tests the #warning directive (note: only available, if enabled during
// compilation, the macro expansion is available only, when enabled separately
// during the compilation too)

//R
//E t_2_001.cpp(18): warning: encountered #warning directive: This is a warning
#define WARNING1 This is a 
#define WARNING2 warning
#warning WARNING1 WARNING2
