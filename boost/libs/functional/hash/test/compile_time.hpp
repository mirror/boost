
//  (C) Copyright Daniel James 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>
#include <boost/mpl/assert.hpp>

template <class T>
struct compile_time_tests
{
    BOOST_MPL_ASSERT((boost::is_base_and_derived<
        std::unary_function<T, std::size_t>, HASH_NAMESPACE::hash<T> >));
    BOOST_STATIC_CONSTANT(bool, success = true);
};

