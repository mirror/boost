#if defined(_MSC_VER) && !defined(__ICL)
#pragma warning(disable: 4786)  // identifier truncated in debug info
#pragma warning(disable: 4710)  // function not inlined
#pragma warning(disable: 4711)  // function selected for automatic inline expansion
#pragma warning(disable: 4514)  // unreferenced inline removed
#endif

//
//  assert_test.cpp - a test for boost/assert.hpp
//
//  Copyright (c) 2002 Peter Dimov and Multi Media Ltd.
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//

#define BOOST_DEBUG 1

#include <boost/assert.hpp>
#include <cstdio>

bool boost_error(char const * expr, char const * func, char const * file, long line)
{
    std::printf("%s(%ld): Assertion '%s' failed in function '%s'\n", file, line, expr, func);
    return true; // fail w/ standard assert()
}

int main()
{
    BOOST_ASSERT(0 == 1);
}
