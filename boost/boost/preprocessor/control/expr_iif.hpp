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
# ifndef BOOST_PREPROCESSOR_CONTROL_EXPR_IIF_HPP
# define BOOST_PREPROCESSOR_CONTROL_EXPR_IIF_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_EXPR_IIF */
#
# if BOOST_PP_CONFIG_FLAGS & BOOST_PP_CONFIG_IDEAL
#    define BOOST_PP_EXPR_IIF(bit, expr) BOOST_PP_CAT(BOOST_PP_EXPR_IIF_, bit)(expr)
# else
#    if ~BOOST_PP_CONFIG_FLAGS & BOOST_PP_CONFIG_MWCW
#        define BOOST_PP_EXPR_IIF(bit, expr) BOOST_PP_EXPR_IIF_D(bit, expr)
#    else
#        define BOOST_PP_EXPR_IIF(bit, expr) BOOST_PP_EVIL_EXPR_IIF_D((bit, expr))
#        define BOOST_PP_EVIL_EXPR_IIF_D(par) BOOST_PP_EXPR_IIF_D ## par
#    endif
#    define BOOST_PP_EXPR_IIF_D(bit, expr) BOOST_PP_EXPR_IIF_ ## bit(expr)
# endif
#
# define BOOST_PP_EXPR_IIF_0(expr)
# define BOOST_PP_EXPR_IIF_1(expr) expr
#
# endif
