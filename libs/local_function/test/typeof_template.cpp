
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#include "addable.hpp"
#include <boost/local_function.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/concept_check.hpp>
#define BOOST_TEST_MODULE TestTypeofTemplate
#include <boost/test/unit_test.hpp>
#include <algorithm>

//[typeof_template
template<typename T>
T calculate(const T& factor) {
    T sum = 0;

    void BOOST_LOCAL_FUNCTION_TPL(const bind factor, bind& sum, T num) {
        // Local function `TYPEOF` does not need `typename`.
        BOOST_CONCEPT_ASSERT((Addable<typename boost::remove_reference<
                BOOST_LOCAL_FUNCTION_TYPEOF(sum)>::type>));
        sum += factor * num;
    } BOOST_LOCAL_FUNCTION_NAME(add)

    add(6);
    return sum;
}
//]

BOOST_AUTO_TEST_CASE( test_typeof_template ) {
    BOOST_CHECK( calculate(10) == 60 );
}

