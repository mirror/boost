#if defined(_MSC_VER) && !defined(__ICL)
#pragma warning(disable: 4786)  // identifier truncated in debug info
#pragma warning(disable: 4710)  // function not inlined
#pragma warning(disable: 4711)  // function selected for automatic inline expansion
#pragma warning(disable: 4514)  // unreferenced inline removed
#endif

//
//  bind_test_2.cpp - tests bind.hpp with function objects
//
//  Version 1.00.0005 (2001-07-13)
//
//  Copyright (c) 2001 Peter Dimov and Multi Media Ltd.
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//

#include <boost/bind.hpp>
#include <boost/ref.hpp>
#include <iostream>

struct X
{
    short operator()(short & r) const { return ++r; }
    int operator()(int a, int b) const { return a + 10 * b; }
    long operator() (long a, long b, long c) const { return a + 10 * b + 100 * c; }
};

unsigned long hash = 0;

template<class F> void test(F f, int const i)
{
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
    using namespace boost;

    short i(6);

    test(bind<short>(X(), ref(i)), 1);
    test(bind<short>(X(), ref(i)), 2);
    test(bind<int>(X(), i, _1), 3);
    test(bind<long>(X(), i, _1, 9), 4);

    return detect_errors(hash == 24857);
}
