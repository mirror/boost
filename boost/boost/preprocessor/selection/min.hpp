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
# ifndef BOOST_PREPROCESSOR_MIN_HPP
# define BOOST_PREPROCESSOR_MIN_HPP
#
# include <boost/preprocessor/comparison/less_equal.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/iif.hpp>
#
# /* BOOST_PP_MIN */
#
# if ~BOOST_PP_CONFIG_FLAGS & BOOST_PP_CONFIG_EDG
#    define BOOST_PP_MIN BOOST_PP_MIN_I
# else
#    define BOOST_PP_MIN(x, y) BOOST_PP_MIN_I(x, y)
# endif
#
# define BOOST_PP_MIN_I(x, y) BOOST_PP_IIF(BOOST_PP_LESS_EQUAL(y, x), y, x)
#
# /* BOOST_PP_MIN_D */
#
# if ~BOOST_PP_CONFIG_FLAGS & BOOST_PP_CONFIG_EDG
#    define BOOST_PP_MIN_D BOOST_PP_MIN_D_I
# else
#    define BOOST_PP_MIN_D(d, x, y) BOOST_PP_MIN_D_I(d, x, y)
# endif
#
# define BOOST_PP_MIN_D_I(d, x, y) BOOST_PP_IIF(BOOST_PP_LESS_EQUAL_D(d, y, x), y, x)
#
# endif
