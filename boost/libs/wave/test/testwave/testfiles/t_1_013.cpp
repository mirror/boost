/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library
    http://www.boost.org/

    Copyright (c) 2001-2006 Hartmut Kaiser. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

// This sample is taken from the C++ standard 16.3.5.6 [cpp.scope] and was 
// slightly modified (removed the '#include' directive)

#define str(s) # s
#define xstr(s) str(s)
#define debug(s, t) printf("x" # s "= %d, x" # t "= %s", \
x ## s, x ## t)
#define INCFILE(n) vers ## n /* from previous #include example */
#define glue(a, b) a ## b
#define xglue(a, b) glue(a, b)
#define HIGHLOW "hello"
#define LOW LOW ", world"
debug(1, 2);
fputs(str(strncmp("abc\0d?", "abc", '\4', "\u1234") /* this goes away */
== 0) str(: @\n), s);
/*#include*/ xstr(INCFILE(2).hpp)
glue(HIGH, LOW);
xglue(HIGH, LOW)

// should expand to 
//R #line 22 "t_1_013.cpp"
//R printf("x" "1" "= %d, x" "2" "= %s", x1, x2);
//R fputs("strncmp(\"abc\\0d\?\", \"abc\", '\\4', \"\\u1234\") == 0" ": @\n", s);
//R "vers2.hpp"
//R "hello";
//R "hello" ", world"
