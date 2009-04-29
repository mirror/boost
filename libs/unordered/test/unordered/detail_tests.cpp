
// Copyright 2009 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Test some of the library's implementation details.

#include <boost/unordered_set.hpp>
#include <boost/unordered_map.hpp>

#include <boost/detail/lightweight_test.hpp>
#include <boost/range.hpp>

int main() {
    
    // Test that the prime list has the right length.
    // 
    // It would have been better to automatically set the length in the header
    // but that doesn't work on some compilers. It's okay that this isn't tested
    // on all compilers, as it really only needs to be checked on one.

#if !defined(BOOST_MSVC)

    BOOST_TEST_EQ(
        boost::end(boost::unordered_detail::prime_list::value) -
        boost::begin(boost::unordered_detail::prime_list::value),
        boost::unordered_detail::prime_list::length);
        
#endif

    return boost::report_errors();
}