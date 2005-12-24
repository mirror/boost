/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library
    http://www.boost.org/

    Copyright (c) 2001-2006 Hartmut Kaiser. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

// Tests for a problem wrt preprocessing tokens (preprocessing numbers)

#define X() X_ ## 0R()
#define X_0R() ...

//R #line 16 "t_9_009.cpp"
X() //R ... 
