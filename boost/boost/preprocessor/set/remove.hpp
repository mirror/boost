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
# ifndef BOOST_PREPROCESSOR_SET_REMOVE_HPP
# define BOOST_PREPROCESSOR_SET_REMOVE_HPP
#
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/set/first_n.hpp>
# include <boost/preprocessor/set/rest_n.hpp>
#
# /* BOOST_PP_SET_REMOVE */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SET_REMOVE(set, i) BOOST_PP_SET_FIRST_N(i, set) BOOST_PP_SET_REST_N(BOOST_PP_INC(i), set)
# else
#    define BOOST_PP_SET_REMOVE(set, i) BOOST_PP_SET_REMOVE_I(set, i)
#    define BOOST_PP_SET_REMOVE_I(set, i) BOOST_PP_SET_FIRST_N(i, set) BOOST_PP_SET_REST_N(BOOST_PP_INC(i), set)
# endif
#
# endif
