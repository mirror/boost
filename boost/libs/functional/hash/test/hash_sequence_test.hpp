
//  (C) Copyright Daniel James 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(CONTAINER_TYPE)
#error "CONTAINER_TYPE not defined"
#else

#include <boost/preprocessor/cat.hpp>
#include <boost/assign/list_inserter.hpp>

namespace BOOST_PP_CAT(CONTAINER_TYPE, _tests)
{
    template <class T>
    void integer_tests(T* = 0)
    {
        using namespace boost::assign;

        const int number_of_containers = 11;
        T containers[number_of_containers];

        for(int i = 0; i < 5; ++i) {
            for(int j = 0; j < i; ++j)
                boost::assign::push_back(containers[i])(0);
        }

        boost::assign::push_back(containers[5])(1);
        boost::assign::push_back(containers[6])(1)(1);
        boost::assign::push_back(containers[7])(-1);
        boost::assign::push_back(containers[8])(-1)(-1);
        boost::assign::push_back(containers[9])(1)(-1);
        boost::assign::push_back(containers[10])(-1)(1);

        boost::hash<T> hasher;

        for(int i2 = 0; i2 < number_of_containers; ++i2) {
            BOOST_CHECK_EQUAL(hasher(containers[i2]), hasher(containers[i2]));

            for(int j2 = i2 + 1; j2 < number_of_containers; ++j2) {
                BOOST_CHECK(
                        (containers[i2] == containers[j2]) ==
                        (hasher(containers[i2]) == hasher(containers[j2]))
                        );
            }
        }
    }

    BOOST_AUTO_UNIT_TEST(BOOST_PP_CAT(CONTAINER_TYPE, _hash_integer_tests))
    {
        integer_tests((CONTAINER_TYPE<char>*) 0);
        integer_tests((CONTAINER_TYPE<int>*) 0);
        integer_tests((CONTAINER_TYPE<unsigned long>*) 0);
        integer_tests((CONTAINER_TYPE<double>*) 0);
    }
}

#undef CONTAINER_TYPE
#endif
