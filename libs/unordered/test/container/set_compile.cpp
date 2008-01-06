
// Copyright 2006-2007 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This test creates the containers with members that meet their minimum
// requirements. Makes sure everything compiles and is defined correctly.

#include <boost/unordered_set.hpp>

#include <iostream>
#include <boost/detail/lightweight_test.hpp>
#include "../objects/minimal.hpp"
#include "./compile_tests.hpp"

int main()
{
    test::minimal::assignable assignable = test::minimal::assignable::create();

    std::cout<<"Test unordered_set.\n";
    boost::unordered_set<
        test::minimal::assignable,
        test::minimal::hash<test::minimal::assignable>,
        test::minimal::equal_to<test::minimal::assignable>,
        test::minimal::allocator<test::minimal::assignable> > set;

    container_test(set, assignable);

    std::cout<<"Test unordered_multiset.\n";
    boost::unordered_multiset<
        test::minimal::assignable,
        test::minimal::hash<test::minimal::assignable>,
        test::minimal::equal_to<test::minimal::assignable>,
        test::minimal::allocator<test::minimal::assignable> > multiset;

    container_test(multiset, assignable);

    return boost::report_errors();
}
