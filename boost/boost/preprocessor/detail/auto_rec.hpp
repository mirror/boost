#ifndef BOOST_PREPROCESSOR_DETAIL_AUTO_REC_HPP
#define BOOST_PREPROCESSOR_DETAIL_AUTO_REC_HPP

/* Copyright (C) 2002 Vesa Karvonen
 *
 * Permission to copy, use, modify, sell and distribute this software is
 * granted provided this copyright notice appears in all copies. This
 * software is provided "as is" without express or implied warranty, and
 * with no claim as to its suitability for any purpose.
 *
 * Based on an original idea by Paul Mensonides this header defines macros
 * for the definition of automatically recursive macros.
 *
 * See http://www.boost.org for most recent version.
 */

/* Identity macro for auto rec support. */
#define BOOST_PP_AUTO_REC_ID(X) X

/* Catenation macros for auto rec support. */
#define BOOST_PP_AUTO_REC_CAT0(X,Y) BOOST_PP_AUTO_REC_DELAY_CAT0(X,Y)
#define BOOST_PP_AUTO_REC_CAT1(X,Y) BOOST_PP_AUTO_REC_DELAY_CAT1(X,Y)
#define BOOST_PP_AUTO_REC_CAT2(X,Y) BOOST_PP_AUTO_REC_DELAY_CAT2(X,Y)
#define BOOST_PP_AUTO_REC_CAT3(X,Y) BOOST_PP_AUTO_REC_DELAY_CAT3(X,Y)
#define BOOST_PP_AUTO_REC_CAT4(X,Y) BOOST_PP_AUTO_REC_DELAY_CAT4(X,Y)
#define BOOST_PP_AUTO_REC_CAT5(X,Y) BOOST_PP_AUTO_REC_DELAY_CAT5(X,Y)
#define BOOST_PP_AUTO_REC_CAT6(X,Y) BOOST_PP_AUTO_REC_DELAY_CAT6(X,Y)
#define BOOST_PP_AUTO_REC_CAT7(X,Y) BOOST_PP_AUTO_REC_DELAY_CAT7(X,Y)
#define BOOST_PP_AUTO_REC_CAT8(X,Y) BOOST_PP_AUTO_REC_DELAY_CAT8(X,Y)
#define BOOST_PP_AUTO_REC_CAT9(X,Y) BOOST_PP_AUTO_REC_DELAY_CAT9(X,Y)

#define BOOST_PP_AUTO_REC_DELAY_CAT0(X,Y) BOOST_PP_AUTO_REC_DO_CAT0(X,Y)
#define BOOST_PP_AUTO_REC_DELAY_CAT1(X,Y) BOOST_PP_AUTO_REC_DO_CAT1(X,Y)
#define BOOST_PP_AUTO_REC_DELAY_CAT2(X,Y) BOOST_PP_AUTO_REC_DO_CAT2(X,Y)
#define BOOST_PP_AUTO_REC_DELAY_CAT3(X,Y) BOOST_PP_AUTO_REC_DO_CAT3(X,Y)
#define BOOST_PP_AUTO_REC_DELAY_CAT4(X,Y) BOOST_PP_AUTO_REC_DO_CAT4(X,Y)
#define BOOST_PP_AUTO_REC_DELAY_CAT5(X,Y) BOOST_PP_AUTO_REC_DO_CAT5(X,Y)
#define BOOST_PP_AUTO_REC_DELAY_CAT6(X,Y) BOOST_PP_AUTO_REC_DO_CAT6(X,Y)
#define BOOST_PP_AUTO_REC_DELAY_CAT7(X,Y) BOOST_PP_AUTO_REC_DO_CAT7(X,Y)
#define BOOST_PP_AUTO_REC_DELAY_CAT8(X,Y) BOOST_PP_AUTO_REC_DO_CAT8(X,Y)
#define BOOST_PP_AUTO_REC_DELAY_CAT9(X,Y) BOOST_PP_AUTO_REC_DO_CAT9(X,Y)

#define BOOST_PP_AUTO_REC_DO_CAT0(X,Y) X##Y
#define BOOST_PP_AUTO_REC_DO_CAT1(X,Y) X##Y
#define BOOST_PP_AUTO_REC_DO_CAT2(X,Y) X##Y
#define BOOST_PP_AUTO_REC_DO_CAT3(X,Y) X##Y
#define BOOST_PP_AUTO_REC_DO_CAT4(X,Y) X##Y
#define BOOST_PP_AUTO_REC_DO_CAT5(X,Y) X##Y
#define BOOST_PP_AUTO_REC_DO_CAT6(X,Y) X##Y
#define BOOST_PP_AUTO_REC_DO_CAT7(X,Y) X##Y
#define BOOST_PP_AUTO_REC_DO_CAT8(X,Y) X##Y
#define BOOST_PP_AUTO_REC_DO_CAT9(X,Y) X##Y
#endif
