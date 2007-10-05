/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library
    http://www.boost.org/

    Copyright (c) 2001-2006 Hartmut Kaiser. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

// Tests, whether alternative tokens are interpreted inside of conditional 
// expressions

//R #line 16 "t_2_014.cpp"
//R true
#if compl 1
true
#else
false
#endif

//R #line 26 "t_2_014.cpp"
//R true
#if not 1
false
#else
true
#endif

//R #line 32 "t_2_014.cpp"
//R true
#if 1 or 2
true
#else
false
#endif

//R #line 40 "t_2_014.cpp"
//R true
#if 1 and 2
true
#else
false
#endif

//R #line 50 "t_2_014.cpp"
//R true
#if not 1
false
#else
true
#endif

//R #line 56 "t_2_014.cpp"
//R true
#if 1 xor 2
true
#else
false
#endif

//R #line 66 "t_2_014.cpp"
//R true
#if 1 bitand 2
false
#else
true
#endif

//R #line 72 "t_2_014.cpp"
//R true
#if 1 bitor 2
true
#else
false
#endif

//R #line 80 "t_2_014.cpp"
//R true
#if 1 not_eq 2
true
#else
false
#endif
