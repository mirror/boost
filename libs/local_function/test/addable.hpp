
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef ADDABLE_HPP_
#define ADDABLE_HPP_

#include <boost/concept_check.hpp>

template<typename T>
struct Addable { // User-defined concept.
    BOOST_CONCEPT_USAGE(Addable) {
        return_type(x + y); // Check addition `T operator+(T x, T y)`.
    }
private:
    T x;
    T y;
    void return_type(T const&); // Used to check addition returns type `T`.
};

#endif // #include guard

