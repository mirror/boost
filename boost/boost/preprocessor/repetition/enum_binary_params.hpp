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
# ifndef BOOST_PREPROCESSOR_REPETITION_ENUM_BINARY_PARAMS_HPP
# define BOOST_PREPROCESSOR_REPETITION_ENUM_BINARY_PARAMS_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/punctuation/comma_if.hpp>
# include <boost/preprocessor/repetition/repeat.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_ENUM_BINARY_PARAMS */
#
# if ~BOOST_PP_CONFIG_FLAGS & BOOST_PP_CONFIG_EDG
#    define BOOST_PP_ENUM_BINARY_PARAMS BOOST_PP_ENUM_BINARY_PARAMS_I
# else
#    define BOOST_PP_ENUM_BINARY_PARAMS(count, p1, p2) BOOST_PP_ENUM_BINARY_PARAMS_I(count, p1, p2)
# endif
#
# define BOOST_PP_ENUM_BINARY_PARAMS_I(count, p1, p2) BOOST_PP_REPEAT(count, BOOST_PP_ENUM_BINARY_PARAMS_M, (p1, p2))
#
# if ~BOOST_PP_CONFIG_FLAGS & BOOST_PP_CONFIG_EDG
#    define BOOST_PP_ENUM_BINARY_PARAMS_M(z, n, pp) BOOST_PP_COMMA_IF(n) BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(2, 0, pp), n) BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(2, 1, pp), n)
# else
#    define BOOST_PP_ENUM_BINARY_PARAMS_M(z, n, pp) BOOST_PP_ENUM_BINARY_PARAMS_M_A(n, BOOST_PP_TUPLE_REM_2 pp)
#    define BOOST_PP_ENUM_BINARY_PARAMS_M_A(n, im) BOOST_PP_ENUM_BINARY_PARAMS_M_B(n, im)
#    define BOOST_PP_ENUM_BINARY_PARAMS_M_B(n, p1, p2) BOOST_PP_COMMA_IF(n) p1 ## n p2 ## n
# endif
#
# /* BOOST_PP_ENUM_BINARY_PARAMS_Z */
#
# if ~BOOST_PP_CONFIG_FLAGS & BOOST_PP_CONFIG_EDG
#    define BOOST_PP_ENUM_BINARY_PARAMS_Z(z, count, p1, p2) BOOST_PP_REPEAT_ ## z(count, BOOST_PP_ENUM_BINARY_PARAMS_M, (p1, p2))
# else
#    define BOOST_PP_ENUM_BINARY_PARAMS_Z(z, count, p1, p2) BOOST_PP_ENUM_BINARY_PARAMS_Z_D(z, count, p1, p2)
#    define BOOST_PP_ENUM_BINARY_PARAMS_Z_D(z, count, p1, p2) BOOST_PP_REPEAT_ ## z(count, BOOST_PP_ENUM_BINARY_PARAMS_M, (p1, p2))
# endif
#
# endif
