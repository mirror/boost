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
# ifndef BOOST_PREPROCESSOR_ARRAY_SIZE_HPP
# define BOOST_PREPROCESSOR_ARRAY_SIZE_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_ARRAY_SIZE */
#
# if ~BOOST_PP_CONFIG_FLAGS & BOOST_PP_CONFIG_EDG && ~BOOST_PP_CONFIG_FLAGS & BOOST_PP_CONFIG_MWCW
#    define BOOST_PP_ARRAY_SIZE BOOST_PP_ARRAY_SIZE_I
# elif ~BOOST_PP_CONFIG_FLAGS & BOOST_PP_CONFIG_MWCW
#    define BOOST_PP_ARRAY_SIZE(array) BOOST_PP_ARRAY_SIZE_I(array)
# else
#    define BOOST_PP_ARRAY_SIZE(array) BOOST_PP_EVIL_ARRAY_SIZE_D((array))
#    define BOOST_PP_EVIL_ARRAY_SIZE_D(par) BOOST_PP_ARRAY_SIZE_I ## par
# endif
#
# if BOOST_PP_CONFIG_FLAGS & BOOST_PP_CONFIG_STRICT || BOOST_PP_CONFIG_FLAGS & BOOST_PP_CONFIG_BCC
#    define BOOST_PP_ARRAY_SIZE_I(array) BOOST_PP_ARRAY_SIZE_X array
# elif BOOST_PP_CONFIG_FLAGS & BOOST_PP_CONFIG_MWCW
#    define BOOST_PP_ARRAY_SIZE_I(array) BOOST_PP_ARRAY_SIZE_X ## array
# elif BOOST_PP_CONFIG_FLAGS & BOOST_PP_CONFIG_MSVC
#    define BOOST_PP_ARRAY_SIZE_I(array) BOOST_PP_ARRAY_SIZE_D(BOOST_PP_ARRAY_SIZE_X array)
#    define BOOST_PP_ARRAY_SIZE_D(res) res
# endif
#
# define BOOST_PP_ARRAY_SIZE_X(s, d) s
#
# endif
