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
# ifndef BOOST_PREPROCESSOR_DEBUG_ERROR_HPP
# define BOOST_PREPROCESSOR_DEBUG_ERROR_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_ERROR */
#
# if BOOST_PP_CONFIG_ERRORS
#    define BOOST_PP_ERROR(code) BOOST_PP_CAT(BOOST_PP_ERROR_, code)
# endif
#
# define BOOST_PP_ERROR_0x0000 BOOST_PP_ERROR(0x0000, BOOST_PP_INDEX_OUT_OF_BOUNDS)
# define BOOST_PP_ERROR_0x0001 BOOST_PP_ERROR(0x0001, BOOST_PP_WHILE_OVERFLOW)
# define BOOST_PP_ERROR_0x0002 BOOST_PP_ERROR(0x0002, BOOST_PP_FOR_OVERFLOW)
# define BOOST_PP_ERROR_0x0003 BOOST_PP_ERROR(0x0003, BOOST_PP_REPEAT_OVERFLOW)
# define BOOST_PP_ERROR_0x0004 BOOST_PP_ERROR(0x0004, BOOST_PP_FOLD_OVERFLOW)
#
# endif
