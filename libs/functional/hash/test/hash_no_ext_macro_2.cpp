
// Copyright 2006-2009 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#define HASH_NAMESPACE boost

// Include header with BOOST_HASH_NO_EXTENSIONS defined
#if !defined(BOOST_HASH_NO_EXTENSIONS)
#define BOOST_HASH_NO_EXTENSIONS
#endif
#include <boost/functional/hash.hpp>

// Include header without BOOST_HASH_NO_EXTENSIONS defined
#undef BOOST_HASH_NO_EXTENSIONS
#include <boost/functional/hash.hpp>

#include <boost/detail/lightweight_test.hpp>
#include <map>

int main()
{
    std::map<int, int> x;

    x.insert(std::map<int, int>::value_type(53, -42));
    x.insert(std::map<int, int>::value_type(14, -75));

    HASH_NAMESPACE::hash<std::map<int, int> > hasher;
    BOOST_TEST(hasher(x) == HASH_NAMESPACE::hash_value(x));
    
    return boost::report_errors();
}
