//-----------------------------------------------------------------------------
// boost mpl/test/lambda_args.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2001-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/lambda.hpp"
#include "boost/mpl/apply.hpp"
#include "boost/type_traits/is_same.hpp"
#include "boost/static_assert.hpp"

using namespace boost;
using namespace mpl;

class C {};
class incomplete;

typedef int C::* mem_ptr;
typedef int (C::* mem_fun_ptr)();

#define AUX_LAMBDA_TEST(T) \
    {BOOST_STATIC_ASSERT((apply1<lambda< is_same<_,T> >::type, T>::type::value));} \
    {BOOST_STATIC_ASSERT((apply1<lambda< is_same<T,_> >::type, T>::type::value));} \
    {BOOST_STATIC_ASSERT((apply2<lambda< is_same<_,_> >::type, T, T>::type::value));} \
/**/

int main()
{
    AUX_LAMBDA_TEST(C);
#if !defined(BOOST_MSVC) || BOOST_MSVC > 1300
    AUX_LAMBDA_TEST(incomplete);
#endif
    AUX_LAMBDA_TEST(int);
    AUX_LAMBDA_TEST(void);
    AUX_LAMBDA_TEST(double);
    AUX_LAMBDA_TEST(int&);
    AUX_LAMBDA_TEST(int*);
//    AUX_LAMBDA_TEST(int[]);
    AUX_LAMBDA_TEST(int[10]);
    AUX_LAMBDA_TEST(int (*)())
    AUX_LAMBDA_TEST(mem_ptr);
    AUX_LAMBDA_TEST(mem_fun_ptr);

    return 0;
}
