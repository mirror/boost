/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library
    http://www.boost.org/

    Copyright (c) 2001-2008 Hartmut Kaiser. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

// make sure newlines inside of macro invocations get accounted for correctly

#define BAZ(T, E) T E

struct foo
{
  BAZ
  (bool, 
   value = true
   );
};

struct bar {};

//R #line 14 "t_1_038.cpp"
//R struct foo
//R {
//R bool value = true;
//R #line 20 "t_1_038.cpp"
//R };
//R
//R struct bar {};

