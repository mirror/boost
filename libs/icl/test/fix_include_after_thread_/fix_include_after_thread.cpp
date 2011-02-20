/*-----------------------------------------------------------------------------+    
Copyright (c) 2011-2011: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#define BOOST_TEST_MODULE icl::fix_include_after_thread unit test
#include <boost/config.hpp>
#include <boost/test/unit_test.hpp>

//Problem: If <boost/thread.hpp> is included before this
//example code, it influences compilation: Code that has
//compiled well, produces a syntax error error C2059 under 
//msvc-9/10. This can be fixed by enclosing subexpressions
//like some_attribute<Type>::value in parentheses
//  ->(some_attribute<Type>::value)
//The problem does not occur for gcc compilers.
#include <boost/thread.hpp>
//--- included code ---------------------------------------
template <class Type> struct some_attribute
{ 
    BOOST_STATIC_CONSTANT(int, value = 0); 
};

template <class Type> struct some_predicate
{ 
    BOOST_STATIC_CONSTANT(bool, 
    //  value = ((some_attribute<Type>::value) < 0) 
        value = ( some_attribute<Type>::value  < 0) 
                //error C2059: syntax error : ')' ONLY
                //IF <boost/thread.hpp> is included before
        ); 
};
//--- end of included code --------------------------------

BOOST_AUTO_TEST_CASE(dummy)
{
    BOOST_CHECK(true);
}

