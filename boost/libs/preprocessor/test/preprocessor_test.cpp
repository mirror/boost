// Copyright (C) 2001
// Housemarque Oy
// http://www.housemarque.com
//
// Permission to copy, use, modify, sell and distribute this software is
// granted provided this copyright notice appears in all copies. This
// software is provided "as is" without express or implied warranty, and
// with no claim as to its suitability for any purpose.

// See http://www.boost.org for most recent version.

#include <boost/preprocessor/empty.hpp>
#include <boost/preprocessor/if.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>

#include <libs/preprocessor/test/test.hpp>

// ***

struct Container
{
#define BOOST_PP_DEF(CV)\
  CV int& operator[](int i) CV;

  BOOST_PP_DEF(BOOST_PP_EMPTY())
  BOOST_PP_DEF(const)
  BOOST_PP_DEF(volatile)
  BOOST_PP_DEF(const volatile)

#undef BOOST_PP_DEF
};

// ***

TEST(BOOST_PP_IF(BOOST_PP_IF(1,1,1),true,false) &&
  BOOST_PP_IF(BOOST_PP_IF(0,0,0),false,true))

// ***

TEST(BOOST_PP_CAT(BOOST_PP_IF(1,tru,fals), e))

// ***

char stringize_test[4] = BOOST_PP_STRINGIZE(__LINE__);
