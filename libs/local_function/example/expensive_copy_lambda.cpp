
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#include <boost/config.hpp>
#ifndef BOOST_NO_LAMBDAS

#include <iostream>
#include <cassert>

//[expensive_copy_lambda
struct n {
    int i;
    n(int _i): i(_i) {}
    n(n const& x): i(x.i) { // Some time consuming copy.
        for (unsigned i = 0; i < 10000; ++i) std::cout << '.';
    }
};

int main(void) {
    n x(-1);

    auto f = [x]() {        // Problem: Expensive copy, but if bind
        assert( x.i == -1); // by `&x` then `x` is not constant.
    };
    f();

    return 0;
}
//]

#else // NO_LAMBDAS

int main(void) { return 0; } // Trivial program.

#endif // NO_LAMBDAS

