# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Permission to copy, use, modify, sell and distribute this software is
#  * granted provided this copyright notice appears in all copies. This
#  * software is provided "as is" without express or implied warranty, and
#  * with no claim as to its suitability for any purpose.
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_CONFIG_LIMITS_HPP
# define BOOST_PREPROCESSOR_CONFIG_LIMITS_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_LIMIT_MAG */
#
# define BOOST_PP_LIMIT_MAG 256
#
# /* BOOST_PP_LIMIT_TUPLE */
#
# define BOOST_PP_LIMIT_TUPLE 25
#
# /* BOOST_PP_LIMIT_DIM */
#
# define BOOST_PP_LIMIT_DIM 3
#
# /* BOOST_PP_LIMIT_REPEAT */
#
# if BOOST_PP_CONFIG_UNROLLED
#    define BOOST_PP_LIMIT_REPEAT 128
# else
#    define BOOST_PP_LIMIT_REPEAT 256
# endif
#
# /* BOOST_PP_LIMIT_WHILE */
#
# define BOOST_PP_LIMIT_WHILE 256
#
# /* BOOST_PP_LIMIT_FOR */
#
# define BOOST_PP_LIMIT_FOR 256
#
# /* BOOST_PP_LIMIT_ITERATION */
#
# define BOOST_PP_LIMIT_ITERATION 256
#
# /* BOOST_PP_LIMIT_ITERATION_DIM */
#
# define BOOST_PP_LIMIT_ITERATION_DIM 5
#
# /* BOOST_PP_LIMIT_SLOT_SIG */
#
# define BOOST_PP_LIMIT_SLOT_SIG 10
#
# /* BOOST_PP_LIMIT_SLOT_COUNT */
#
# define BOOST_PP_LIMIT_SLOT_COUNT 5
#
# /* BOOST_PP_INFINITY */
#
# define BOOST_PP_INFINITY (-1)
#
# /* BOOST_PP_LIMIT_BOOL */
#
# if ~BOOST_PP_CONFIG_FLAGS & BOOST_PP_CONFIG_EDG
#    define BOOST_PP_LIMIT_BOOL BOOST_PP_INFINITY
# else
#    define BOOST_PP_LIMIT_BOOL BOOST_PP_LIMIT_MAG
# endif
#
# endif
