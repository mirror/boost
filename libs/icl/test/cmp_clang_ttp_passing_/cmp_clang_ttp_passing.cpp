/*-----------------------------------------------------------------------------+    
Copyright (c) 2011-2011: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#define BOOST_TEST_MODULE icl::cmp_clang_ttp_passing unit test
#include <libs/icl/test/disable_test_warnings.hpp>
#include <boost/config.hpp>
#include "../unit_test_unwarned.hpp"


namespace sep
{

template<class T>class less{};

template
<
    class T, 
    template<class>class less_T = sep::less
>
class cont
{
public:
    boost test()const { return true; }
};

template
<
    class T, 
    template<class T2, 
             template<class>class less_T2 = sep::less>
    class Cont
>
bool func()
{
    typedef Cont<T> cont_type; 
    cont_type x;
    return x.test();
}

}//namespace sep


BOOST_AUTO_TEST_CASE(dummy)
{
    bool executed = sep::func<int, sep::cont>();
    BOOST_CHECK( executed );
}

