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
# ifndef BOOST_PREPROCESSOR_FACILITIES_EXPAND_HPP
# define BOOST_PREPROCESSOR_FACILITIES_EXPAND_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_EXPAND */
#
# if BOOST_PP_CONFIG_FLAGS & BOOST_PP_CONFIG_IDEAL
#    define BOOST_PP_EXPAND(x) x
# else
#    if ~BOOST_PP_CONFIG_FLAGS & BOOST_PP_CONFIG_MWCW
#        define BOOST_PP_EXPAND(x) BOOST_PP_EXPAND_D(x)
#    else
#        define BOOST_PP_EXPAND(x) BOOST_PP_EVIL_EXPAND_D((x))
#        define BOOST_PP_EVIL_EXPAND_D(par) BOOST_PP_EXPAND_D ## par
#    endif
#    define BOOST_PP_EXPAND_D(x) x
# endif
#
# endif
