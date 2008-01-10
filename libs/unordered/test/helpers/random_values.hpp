
// Copyright 2005-2007 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_UNORDERED_TEST_HELPERS_RANDOM_VALUES_HEADER)
#define BOOST_UNORDERED_TEST_HELPERS_RANDOM_VALUES_HEADER

#include <list>
#include <algorithm>
#include "./generators.hpp"

namespace test
{
    template <class X>
    struct random_values
        : public std::list<BOOST_DEDUCED_TYPENAME X::value_type>
    {
        random_values(int count) {
            typedef BOOST_DEDUCED_TYPENAME X::value_type value_type;
            static test::generator<value_type> gen;
            std::generate_n(std::back_inserter(*this), count, gen);
        }
    };
}

#endif
