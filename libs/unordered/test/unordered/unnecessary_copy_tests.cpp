
// Copyright 2006-2007 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/unordered_set.hpp>
#include <boost/unordered_map.hpp>
#include <boost/detail/lightweight_test.hpp>

struct count_copies
{
    static int count;
    count_copies() { ++count; }
    count_copies(count_copies const&) { ++count; }
private:
    count_copies& operator=(count_copies const&);
};

#if defined(BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP)
namespace boost {
#endif

std::size_t hash_value(count_copies const&) {
    return 0;
}

#if defined(BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP)
}
#endif

bool operator==(count_copies const&, count_copies const&) {
    return true;
}

int count_copies::count;

template <class T>
void unnecessary_copy_test(T*)
{
    count_copies::count = 0;
    T x;
    typename T::value_type a;
    BOOST_TEST(count_copies::count == 1);
    x.insert(a);
    BOOST_TEST(count_copies::count == 2);
}


int main()
{
    unnecessary_copy_test((boost::unordered_set<count_copies>*) 0);
    unnecessary_copy_test((boost::unordered_multiset<count_copies>*) 0);
    unnecessary_copy_test((boost::unordered_map<int, count_copies>*) 0);
    unnecessary_copy_test((boost::unordered_multimap<int, count_copies>*) 0);

    return boost::report_errors();
}
