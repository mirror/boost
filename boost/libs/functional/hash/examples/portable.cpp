
//  Copyright Daniel James 2005. Use, modification, and distribution are
//  subject to the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/functional/hash.hpp>
#include <cassert>

// This example illustrates how to customise boost::hash portably, so that
// it'll work on both compilers that don't implement argument dependent lookup
// and compilers that implement strict two-phase template instantiation.

namespace foo
{
    struct custom_type
    {
        int value;

        custom_type(int x) : value(x) {}

#ifndef BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
        friend inline std::size_t hash_value(custom_type x)
        {
            boost::hash<int> hasher;
            return hasher(x.value);
        }
#else
        std::size_t hash() const
        {
            boost::hash<int> hasher;
            return hasher(value);
        }
#endif
    };
}

#ifdef BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
namespace boost
{
    std::size_t hash_value(foo::custom_type x)
    {
        return x.hash();
    }
}
#endif

int main()
{
    foo::custom_type x(1), y(2), z(1);

    boost::hash<foo::custom_type> hasher;

    assert(hasher(x) == hasher(x));
    assert(hasher(x) != hasher(y));
    assert(hasher(x) == hasher(z));
}
