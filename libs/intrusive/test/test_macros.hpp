/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2006-2007
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_TEST_TEST_MACROS_HPP
#define BOOST_INTRUSIVE_TEST_TEST_MACROS_HPP

#define TEST_INTRUSIVE_SEQUENCE( INTVALUES, ITERATOR )\
{  \
   const int init_values_size = sizeof(INTVALUES)/sizeof(INTVALUES[0]); \
   std::vector<int> expected; \
   expected.assign(&INTVALUES[0], &INTVALUES[0] + init_values_size); \
   BOOST_TEST (std::equal(expected.begin(), expected.end(), ITERATOR) ); \
}

#define TEST_INTRUSIVE_SEQUENCE_EXPECTED( EXPECTEDVECTOR, ITERATOR )\
{  \
   BOOST_TEST (std::equal(EXPECTEDVECTOR.begin(), EXPECTEDVECTOR.end(), ITERATOR) ); \
}

#endif
