
// + file: libs/mpl/aux_/test/test_case.cpp
// + last modified: 03/may/03

// Copyright (c) 2002-03
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

#include "boost/mpl/aux_/test.hpp"

CTT_test_case( false_positives, (S)(T) )
{
    CTT_assert_same( 2, (S, char) );
    CTT_assert_not_same( 2, (S, bool) );
    //T t;
}

CTT_test_case( empty_set, (T) )
    {
    CTT_for_each( 
          (T)(T const)
        , false_positives
        , (char)(_1)
        );
    }

int main()
{
    CTT_test( empty_set, (bool) );
    CTT_for_each( (int)(long), empty_set, (_1) );

    return 0;
}
