
//  (C) Copyright Daniel James 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#define HASH_NAMESPACE boost

// Simple test to make sure BOOST_HASH_NO_EXTENSIONS does disable extensions
// (or at least one of them).
#define BOOST_HASH_NO_EXTENSIONS

#include <boost/functional/hash.hpp>
#include <boost/functional/hash.hpp>
#include <set>

int main()
{
    HASH_NAMESPACE::hash< std::set<int> > hasher;
    return 0;
}
