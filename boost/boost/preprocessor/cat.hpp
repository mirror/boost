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
# ifndef BOOST_PREPROCESSOR_CAT_HPP
# define BOOST_PREPROCESSOR_CAT_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_CAT */
#
# if ~BOOST_PP_CONFIG_FLAGS & BOOST_PP_CONFIG_MWCW
#    define BOOST_PP_CAT(a, b) BOOST_PP_CAT_D(a, b)
# else
#    define BOOST_PP_CAT(a, b) BOOST_PP_EVIL_CAT_D((a, b))
#    define BOOST_PP_EVIL_CAT_D(par) BOOST_PP_CAT_D ## par
# endif
#
# define BOOST_PP_CAT_D(a, b) a ## b
#
# endif
