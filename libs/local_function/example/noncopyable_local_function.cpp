
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#include <boost/local_function.hpp>
#include <boost/noncopyable.hpp>
#include <cassert>

//[noncopyable_local_function
struct n: boost::noncopyable {
    int i;
    n(int _i): i(_i) {}
};

int main() {
    n x(-1);

    void BOOST_LOCAL_FUNCTION(const bind& x) {  // OK: No copy
        assert( x.i == -1 );                    // and constant.
    } BOOST_LOCAL_FUNCTION_NAME(f)
    f();

    return 0;
}
//]

