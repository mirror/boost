
// Copyright 2005-2008 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_UNORDERED_TEST_HELPERS_STRONG_HEADER)
#define BOOST_UNORDERED_TEST_HELPERS_STRONG_HEADER

#include <boost/config.hpp>
#include <vector>
#include <iterator>
#include "./metafunctions.hpp"
#include "./equivalent.hpp"
#include "../objects/exception.hpp"

namespace test
{
    template <class X>
    class strong
    {
        typedef std::vector<BOOST_DEDUCED_TYPENAME non_const_value_type<X>::type> values_type;
        values_type values_;
    public:
        void store(X const& x) {
            DISABLE_EXCEPTIONS;
            values_.clear();
            values_.reserve(x.size());
            std::copy(x.cbegin(), x.cend(), std::back_inserter(values_));
        }

        void test(X const& x) const {
            if(!(x.size() == values_.size() &&
                        std::equal(x.cbegin(), x.cend(), values_.begin(), test::equivalent)))
                BOOST_ERROR("Strong exception safety failure.");
        }
    };
}

#endif
