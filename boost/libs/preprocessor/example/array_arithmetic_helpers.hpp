#ifndef BOOST_LIBS_PREPROCESSOR_EXAMPLE_ARRAY_ARITHMETIC_HELPERS_HPP
#define BOOST_LIBS_PREPROCESSOR_EXAMPLE_ARRAY_ARITHMETIC_HELPERS_HPP

/* Copyright (C) 2002
 * Housemarque Oy
 * http://www.housemarque.com
 *
 * Permission to copy, use, modify, sell and distribute this software is
 * granted provided this copyright notice appears in all copies. This
 * software is provided "as is" without express or implied warranty, and
 * with no claim as to its suitability for any purpose.
 *
 * See http://www.boost.org for most recent version.
 */

#include <boost/preprocessor/cat.hpp>

#define BOOST_PP_CAT3(A,B,C) BOOST_PP_CAT(BOOST_PP_CAT(A,B),C)
#define BOOST_PP_CAT4(A,B,C,D) BOOST_PP_CAT3(BOOST_PP_CAT(A,B),C,D)
#define BOOST_PP_CAT5(A,B,C,D,E) BOOST_PP_CAT4(BOOST_PP_CAT(A,B),C,D,E)
#define BOOST_PP_CAT6(A,B,C,D,E,F) BOOST_PP_CAT5(BOOST_PP_CAT(A,B),C,D,E,F)
#endif
