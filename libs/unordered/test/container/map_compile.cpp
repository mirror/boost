
// Copyright 2006-2007 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This test creates the containers with members that meet their minimum
// requirements. Makes sure everything compiles and is defined correctly.

#include <boost/unordered_map.hpp>

#include <iostream>
#include <boost/detail/lightweight_test.hpp>
#include "../objects/minimal.hpp"
#include "./compile_tests.hpp"

int main()
{
    typedef std::pair<test::minimal::assignable const,
            test::minimal::copy_constructible> value_type;
    value_type value(
            test::minimal::assignable::create(),
            test::minimal::copy_constructible::create());

    std::cout<<"Test unordered_map.\n";
    boost::unordered_map<
        test::minimal::assignable,
        test::minimal::copy_constructible,
        test::minimal::hash<test::minimal::assignable>,
        test::minimal::equal_to<test::minimal::assignable>,
        test::minimal::allocator<value_type> > map;

    container_test(map, value);

    std::cout<<"Test unordered_multimap.\n";
    boost::unordered_multimap<
        test::minimal::assignable,
        test::minimal::copy_constructible,
        test::minimal::hash<test::minimal::assignable>,
        test::minimal::equal_to<test::minimal::assignable>,
        test::minimal::allocator<value_type> > multimap;

    container_test(multimap, value);

    return boost::report_errors();
}
