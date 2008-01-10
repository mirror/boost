
// Copyright 2006-2007 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "./containers.hpp"

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/test/exception_safety.hpp>
#include "../helpers/random_values.hpp"
#include "../helpers/invariants.hpp"

test::seed_t seed(9387);

template <class T>
struct self_swap_base : public test::exception_base
{
    test::random_values<T> values;
    self_swap_base(int count = 0) : values(count) {}

    typedef T data_type;
    T init() const { return T(values.begin(), values.end()); }
    void run(T& x) const { x.swap(x); }
    void check(T const& x) const {
        std::string scope(test::scope);

#if BOOST_UNORDERED_SWAP_METHOD != 2
        HASH_CHECK(
                scope == "hash::operator(hash)" ||
                scope == "hash::operator=(hash)" ||
                scope == "equal_to::operator(equal_to)" ||
                scope == "equal_to::operator=(equal_to)");
#endif

        test::check_equivalent_keys(x);
    }
};

template <class T>
struct self_swap_test1 : self_swap_base<T> {};

template <class T>
struct self_swap_test2 : self_swap_base<T>
{
    self_swap_test2() : self_swap_base<T>(100) {}
};

template <class T>
struct swap_base : public test::exception_base
{
    const test::random_values<T> x_values, y_values;
    const T initial_x, initial_y;

    swap_base(unsigned int count1, unsigned int count2, int tag1, int tag2)
        : x_values(count1), y_values(count2),
        initial_x(x_values.begin(), x_values.end(), 0, BOOST_DEDUCED_TYPENAME T::hasher(tag1),
                BOOST_DEDUCED_TYPENAME T::key_equal(tag1), BOOST_DEDUCED_TYPENAME T::allocator_type(tag1)),
        initial_y(y_values.begin(), y_values.end(), 0, BOOST_DEDUCED_TYPENAME T::hasher(tag2),
                BOOST_DEDUCED_TYPENAME T::key_equal(tag2), BOOST_DEDUCED_TYPENAME T::allocator_type(tag2))
    {}

    struct data_type {
        data_type(T const& x, T const& y)
            : x(x), y(y) {}

        T x, y;
    };

    data_type init() const { return data_type(initial_x, initial_y); }
    void run(data_type& d) const {
        try {
            d.x.swap(d.y);
        } catch (std::runtime_error) {}
    }
    void check(data_type const& d) const {
        std::string scope(test::scope);

#if BOOST_UNORDERED_SWAP_METHOD != 2
        HASH_CHECK(
                scope == "hash::operator(hash)" ||
                scope == "hash::operator=(hash)" ||
                scope == "equal_to::operator(equal_to)" ||
                scope == "equal_to::operator=(equal_to)");
#endif
        
        test::check_equivalent_keys(d.x);
        test::check_equivalent_keys(d.y);
    }
};

template <class T>
struct swap_test1 : swap_base<T>
{
    swap_test1() : swap_base<T>(0, 0, 0, 0) {}
};

template <class T>
struct swap_test2 : swap_base<T>
{
    swap_test2() : swap_base<T>(60, 0, 0, 0) {}    
};

template <class T>
struct swap_test3 : swap_base<T>
{
    swap_test3() : swap_base<T>(0, 60, 0, 0) {}    
};

template <class T>
struct swap_test4 : swap_base<T>
{
    swap_test4() : swap_base<T>(10, 10, 1, 2) {}
};

RUN_EXCEPTION_TESTS(
    (self_swap_test1)(self_swap_test2)
    (swap_test1)(swap_test2)(swap_test3)(swap_test4),
    CONTAINER_SEQ)
