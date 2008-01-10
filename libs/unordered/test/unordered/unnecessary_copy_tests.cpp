
// Copyright 2006-2007 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/unordered_set.hpp>
#include <boost/unordered_map.hpp>
#include <boost/detail/lightweight_test.hpp>

namespace test {
    struct count_copies
    {
        static int count;
        count_copies() { ++count; }
        count_copies(count_copies const&) { ++count; }
    private:
       count_copies& operator=(count_copies const&);
    };

    bool operator==(test::count_copies const&, test::count_copies const&) {
        return true;
    }
}

#if defined(BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP)
namespace boost {
#else
namespace test {
#endif
    std::size_t hash_value(test::count_copies const&) {
        return 0;
    }
}

namespace test {
    int count_copies::count;

    template <class T>
    void unnecessary_copy_test(T*)
    {
        count_copies::count = 0;
        T x;
        BOOST_DEDUCED_TYPENAME T::value_type a;
        BOOST_TEST(count_copies::count == 1);
        x.insert(a);
        BOOST_TEST(count_copies::count == 2);
    }
}

int main()
{
    test::unnecessary_copy_test((boost::unordered_set<test::count_copies>*) 0);
    test::unnecessary_copy_test((boost::unordered_multiset<test::count_copies>*) 0);
    test::unnecessary_copy_test((boost::unordered_map<int, test::count_copies>*) 0);
    test::unnecessary_copy_test((boost::unordered_multimap<int, test::count_copies>*) 0);

    return boost::report_errors();
}
