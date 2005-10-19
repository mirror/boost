//  (C) Copyright John Maddock 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TR1_TEST_RESULT_HPP
#define BOOST_TR1_TEST_RESULT_HPP

#include <boost/type_traits/is_same.hpp>
#include <boost/static_assert.hpp>

template <class T1, class T2>
void verify_return_type(T1, T2)
{
   BOOST_STATIC_ASSERT( (::boost::is_same<T1, T2>::value));
}


#endif

