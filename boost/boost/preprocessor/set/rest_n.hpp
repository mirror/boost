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
# ifndef BOOST_PREPROCESSOR_SET_REST_N_HPP
# define BOOST_PREPROCESSOR_SET_REST_N_HPP
#
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/facilities/empty.hpp>
# include <boost/preprocessor/set/detail/split.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_SET_REST_N */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SET_REST_N(n, set) BOOST_PP_TUPLE_ELEM(2, 1, BOOST_PP_SET_SPLIT(BOOST_PP_INC(n), (nil) set BOOST_PP_EMPTY))()
# else
#    define BOOST_PP_SET_REST_N(n, set) BOOST_PP_SET_REST_N_I(n, set)
#    define BOOST_PP_SET_REST_N_I(n, set) BOOST_PP_TUPLE_ELEM(2, 1, BOOST_PP_SET_SPLIT(BOOST_PP_INC(n), (nil) set BOOST_PP_EMPTY))()
# endif
#
# endif
