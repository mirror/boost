
//  (C) Copyright John Maddock 2005. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "test.hpp"
#include "check_type.hpp"
#ifdef TEST_STD
#  include <type_traits>
#else
#  include <boost/type_traits/remove_extent.hpp>
#endif

BOOST_DECL_TRANSFORM_TEST(remove_extent_test_1, ::boost::remove_extent, const, const)
BOOST_DECL_TRANSFORM_TEST(remove_extent_test_2, ::boost::remove_extent, volatile, volatile)
BOOST_DECL_TRANSFORM_TEST3(remove_extent_test_3, ::boost::remove_extent, [2])
BOOST_DECL_TRANSFORM_TEST0(remove_extent_test_4, ::boost::remove_extent)
BOOST_DECL_TRANSFORM_TEST(remove_extent_test_5, ::boost::remove_extent, const &, const&)
BOOST_DECL_TRANSFORM_TEST(remove_extent_test_6, ::boost::remove_extent, *, *)
BOOST_DECL_TRANSFORM_TEST(remove_extent_test_7, ::boost::remove_extent, *volatile, *volatile)
BOOST_DECL_TRANSFORM_TEST(remove_extent_test_8, ::boost::remove_extent, const [2], const)
BOOST_DECL_TRANSFORM_TEST(remove_extent_test_9, ::boost::remove_extent, const &, const&)
BOOST_DECL_TRANSFORM_TEST(remove_extent_test_10, ::boost::remove_extent, const*, const*)
BOOST_DECL_TRANSFORM_TEST(remove_extent_test_11, ::boost::remove_extent, volatile*, volatile*)
BOOST_DECL_TRANSFORM_TEST(remove_extent_test_12, ::boost::remove_extent, const[2][3], const[3])
BOOST_DECL_TRANSFORM_TEST(remove_extent_test_13, ::boost::remove_extent, (&)[2], (&)[2])
BOOST_DECL_TRANSFORM_TEST3(remove_extent_test_14, ::boost::remove_extent, [])
BOOST_DECL_TRANSFORM_TEST(remove_extent_test_15, ::boost::remove_extent, const [], const)
BOOST_DECL_TRANSFORM_TEST(remove_extent_test_16, ::boost::remove_extent, const[][3], const[3])

TT_TEST_BEGIN(remove_extent)

   remove_extent_test_1();
   remove_extent_test_2();
   remove_extent_test_3();
   remove_extent_test_4();
   remove_extent_test_5();
   remove_extent_test_6();
   remove_extent_test_7();
   remove_extent_test_8();
   remove_extent_test_9();
   remove_extent_test_10();
   remove_extent_test_11();
   remove_extent_test_12();
   remove_extent_test_13();
   remove_extent_test_14();
   remove_extent_test_15();
   remove_extent_test_16();

TT_TEST_END








