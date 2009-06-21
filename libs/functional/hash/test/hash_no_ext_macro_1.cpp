
// Copyright 2006-2009 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#define HASH_NAMESPACE boost

// Include header without BOOST_HASH_NO_EXTENSIONS defined
#if defined(BOOST_HASH_NO_EXTENSIONS)
#undef BOOST_HASH_NO_EXTENSIONS
#endif
#include <boost/functional/hash.hpp>

// Include header with BOOST_HASH_NO_EXTENSIONS defined
#define BOOST_HASH_NO_EXTENSIONS
#include <boost/functional/hash.hpp>

#include <boost/detail/lightweight_test.hpp>
#include <deque>
#include <cassert>

int main()
{
    std::deque<int> x;

    x.push_back(1);
    x.push_back(2);

    HASH_NAMESPACE::hash<std::deque<int> > hasher;
    BOOST_TEST(hasher(x) == HASH_NAMESPACE::hash_value(x));

    return boost::report_errors();
}
