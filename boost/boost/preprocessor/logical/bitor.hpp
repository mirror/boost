# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.  Permission to copy, use,        *
#  *     modify, sell, and distribute this software is granted provided       *
#  *     this copyright notice appears in all copies.  This software is       *
#  *     provided "as is" without express or implied warranty, and with       *
#  *     no claim at to its suitability for any purpose.                      *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_LOGICAL_BITOR_HPP
# define BOOST_PREPROCESSOR_LOGICAL_BITOR_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_BITOR */
#
# if BOOST_PP_CONFIG_FLAGS & BOOST_PP_CONFIG_IDEAL
#    define BOOST_PP_BITOR(x, y) BOOST_PP_CAT(BOOST_PP_BITOR_, BOOST_PP_CAT(x, y))
# else
#    if ~BOOST_PP_CONFIG_FLAGS & BOOST_PP_CONFIG_MWCW
#        define BOOST_PP_BITOR(x, y) BOOST_PP_BITOR_D(x, y)
#    else
#        define BOOST_PP_BITOR(x, y) BOOST_PP_EVIL_BITOR_D((x, y))
#        define BOOST_PP_EVIL_BITOR_D(par) BOOST_PP_BITOR_D ## par
#    endif
#    define BOOST_PP_BITOR_D(x, y) BOOST_PP_BITOR_ ## x ## y
# endif
#
# define BOOST_PP_BITOR_00 0
# define BOOST_PP_BITOR_01 1
# define BOOST_PP_BITOR_10 1
# define BOOST_PP_BITOR_11 1
#
# endif
