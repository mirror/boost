#if defined(_MSC_VER) && !defined(__ICL)
#pragma warning(disable: 4786)  // identifier truncated in debug info
#pragma warning(disable: 4710)  // function not inlined
#pragma warning(disable: 4711)  // function selected for automatic inline expansion
#pragma warning(disable: 4514)  // unreferenced inline removed
#endif

//
//  bind_test_1.cpp - tests bind.hpp with function pointers
//
//  Version 1.00.0003 (2001-07-13)
//
//  Copyright (c) 2001 Peter Dimov and Multi Media Ltd.
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//

#include <boost/bind.hpp>
#include <iostream>

long f_1(long a)
{
    return a;
}

long f_2(long a, long b)
{
    return a + 10 * b;
}

long f_3(long a, long b, long c)
{
    return a + 10 * b + 100 * c;
}

long f_4(long a, long b, long c, long d)
{
    return a + 10 * b + 100 * c + 1000 * d;
}

long f_5(long a, long b, long c, long d, long e)
{
    return a + 10 * b + 100 * c + 1000 * d + 10000 * e;
}

long f_6(long a, long b, long c, long d, long e, long f)
{
    return a + 10 * b + 100 * c + 1000 * d + 10000 * e + 100000 * f;
}

long f_7(long a, long b, long c, long d, long e, long f, long g)
{
    return a + 10 * b + 100 * c + 1000 * d + 10000 * e + 100000 * f + 1000000 * g;
}

long f_8(long a, long b, long c, long d, long e, long f, long g, long h)
{
    return a + 10 * b + 100 * c + 1000 * d + 10000 * e + 100000 * f + 1000000 * g + 10000000 * h;
}

long f_9(long a, long b, long c, long d, long e, long f, long g, long h, long i)
{
    return a + 10 * b + 100 * c + 1000 * d + 10000 * e + 100000 * f + 1000000 * g + 10000000 * h + 100000000 * i;
}

unsigned long hash = 0;

template<class F> void test(F f)
{
    int const i = 1;
    hash = (hash * 17041 + f(i)) % 32768;
}

int detect_errors(bool x)
{
    if(x)
    {
        std::cerr << "no errors detected.\n";
        return 0;
    }
    else
    {
        std::cerr << "test failed.\n";
        return 1;
    }
}

int main()
{
    test(boost::bind(f_1, _1));
    test(boost::bind(f_2, _1, 2));
    test(boost::bind(f_3, _1, 2, 3));
    test(boost::bind(f_4, _1, 2, 3, 4));
    test(boost::bind(f_5, _1, 2, 3, 4, 5));
    test(boost::bind(f_6, _1, 2, 3, 4, 5, 6));
    test(boost::bind(f_7, _1, 2, 3, 4, 5, 6, 7));
    test(boost::bind(f_8, _1, 2, 3, 4, 5, 6, 7, 8));
    test(boost::bind(f_9, _1, 2, 3, 4, 5, 6, 7, 8, 9));

    return detect_errors(hash == 18797);
}
