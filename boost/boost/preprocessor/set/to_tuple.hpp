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
# ifndef BOOST_PREPROCESSOR_SET_TO_TUPLE_HPP
# define BOOST_PREPROCESSOR_SET_TO_TUPLE_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/set/enum.hpp>
#
# /* BOOST_PP_SET_TO_TUPLE */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SET_TO_TUPLE(set) (BOOST_PP_SET_ENUM(set))
# else
#    define BOOST_PP_SET_TO_TUPLE(set) BOOST_PP_SET_TO_TUPLE_I(set)
#    define BOOST_PP_SET_TO_TUPLE_I(set) (BOOST_PP_SET_ENUM(set))
# endif
#
# endif
