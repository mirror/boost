/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library
    http://www.boost.org/

    Copyright (c) 2001-2006 Hartmut Kaiser. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

// Test, if additional whitespace is inserted at appropriate places.

#define STRINGIZE(x) STRINGIZE_D(x)
#define STRINGIZE_D(x) #x

#define X() 1
#define PLUS() +
#define MINUS() -
#define DOT() .

//R #line 21 "t_9_003.cpp"
X()2                          //R 1 2 
STRINGIZE( X()2 )             //R "12" 
//R 
X() 2                         //R 1 2 
STRINGIZE( X() 2 )            //R "1 2" 
//R 
PLUS()MINUS()                 //R + - 
STRINGIZE( PLUS()MINUS() )    //R "+-" 
//R 
PLUS()PLUS()                  //R + + 
STRINGIZE( PLUS()PLUS() )     //R "++" 
//R 
MINUS()MINUS()                //R - - 
STRINGIZE( MINUS()MINUS() )   //R "--" 
//R 
DOT()DOT()DOT()               //R .. . 
STRINGIZE( DOT()DOT()DOT() )  //R "..." 
