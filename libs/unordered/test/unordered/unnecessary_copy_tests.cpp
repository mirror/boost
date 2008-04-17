
// Copyright 2006-2008 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/unordered_set.hpp>
#include <boost/unordered_map.hpp>
#include "../helpers/test.hpp"

namespace unnecessary_copy_tests
{
    struct count_copies
    {
        static int count;
        count_copies() { ++count; }
        count_copies(count_copies const&) { ++count; }
    private:
       count_copies& operator=(count_copies const&);
    };

    bool operator==(count_copies const&, count_copies const&) {
        return true;
    }
}

#if defined(BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP)
namespace boost
#else
namespace unnecessary_copy_tests
#endif
{
    std::size_t hash_value(unnecessary_copy_tests::count_copies const&) {
        return 0;
    }
}

namespace unnecessary_copy_tests
{
    int count_copies::count;

    template <class T>
    void unnecessary_copy_test(T*)
    {
        count_copies::count = 0;
        T x;
        BOOST_DEDUCED_TYPENAME T::value_type a;
        BOOST_CHECK(count_copies::count == 1);
        if(count_copies::count != 1)
            std::cerr<<count_copies::count<<" copies.\n";

        x.insert(a);
        BOOST_CHECK(count_copies::count == 2);
        if(count_copies::count != 1)
            std::cerr<<count_copies::count<<" copies.\n";
    }

    boost::unordered_set<count_copies>* set;
    boost::unordered_multiset<count_copies>* multiset;
    boost::unordered_map<int, count_copies>* map;
    boost::unordered_multimap<int, count_copies>* multimap;

    UNORDERED_TEST(unnecessary_copy_test, ((set)(multiset)(map)(multimap)))
}

RUN_TESTS()
