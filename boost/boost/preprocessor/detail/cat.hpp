#ifndef BOOST_PREPROCESSOR_DETAIL_CAT_HPP
#define BOOST_PREPROCESSOR_DETAIL_CAT_HPP

/* Copyright (C) 2002 Vesa Karvonen
*
* Permission to copy, use, modify, sell and distribute this software is
* granted provided this copyright notice appears in all copies. This
* software is provided "as is" without express or implied warranty, and
* with no claim as to its suitability for any purpose.
*
* See http://www.boost.org for most recent version.
*/

#define BOOST_PP_DETAIL_CAT2(A,B) BOOST_PP_DETAIL_CAT2_DELAY(A,B)
#define BOOST_PP_DETAIL_CAT2_DELAY(A, B) BOOST_PP_DETAIL_DO_CAT2(A, B)
#define BOOST_PP_DETAIL_DO_CAT2(A,B) A##B

#define BOOST_PP_DETAIL_CAT3(A,B,C) BOOST_PP_DETAIL_CAT3_DELAY(A,B,C)
#define BOOST_PP_DETAIL_CAT3_DELAY(A,B,C) BOOST_PP_DETAIL_DO_CAT3(A,B,C)
#define BOOST_PP_DETAIL_DO_CAT3(A,B,C) A##B##C

#define BOOST_PP_DETAIL_CAT4(A,B,C,D) BOOST_PP_DETAIL_CAT4_DELAY(A,B,C,D)
#define BOOST_PP_DETAIL_CAT4_DELAY(A,B,C,D) BOOST_PP_DETAIL_DO_CAT4(A,B,C,D)
#define BOOST_PP_DETAIL_DO_CAT4(A,B,C,D) A##B##C##D

#define BOOST_PP_DETAIL_CAT5(A,B,C,D,E) BOOST_PP_DETAIL_CAT5_DELAY(A,B,C,D,E)
#define BOOST_PP_DETAIL_CAT5_DELAY(A,B,C,D,E) BOOST_PP_DETAIL_DO_CAT5(A,B,C,D,E)
#define BOOST_PP_DETAIL_DO_CAT5(A,B,C,D,E) A##B##C##D##E

#endif
