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
# ifndef BOOST_PREPROCESSOR_SET_POP_FRONT_HPP
# define BOOST_PREPROCESSOR_SET_POP_FRONT_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/set/set.hpp>
#
# /* BOOST_PP_SET_POP_FRONT */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SET_POP_FRONT(set) BOOST_PP_SET_TAIL(set)
# else
#    define BOOST_PP_SET_POP_FRONT(set) BOOST_PP_SET_POP_FRONT_I(set)
#    define BOOST_PP_SET_POP_FRONT_I(set) BOOST_PP_SET_TAIL(set)
# endif
#
# endif
