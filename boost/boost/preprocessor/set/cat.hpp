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
# ifndef BOOST_PREPROCESSOR_SET_CAT_HPP
# define BOOST_PREPROCESSOR_SET_CAT_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/set/fold_left.hpp>
# include <boost/preprocessor/set/set.hpp>
#
# /* BOOST_PP_SET_CAT */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SET_CAT(set) BOOST_PP_SET_FOLD_LEFT(BOOST_PP_SET_CAT_O, BOOST_PP_SET_HEAD(set), BOOST_PP_SET_TAIL(set))
# else
#    define BOOST_PP_SET_CAT(set) BOOST_PP_SET_CAT_I(set)
#    define BOOST_PP_SET_CAT_I(set) BOOST_PP_SET_FOLD_LEFT(BOOST_PP_SET_CAT_O, BOOST_PP_SET_HEAD(set), BOOST_PP_SET_TAIL(set))
# endif
#
# define BOOST_PP_SET_CAT_O(s, st, elem) BOOST_PP_SET_CAT_O_I(st, elem)
# define BOOST_PP_SET_CAT_O_I(a, b) a ## b
#
# /* BOOST_PP_SET_CAT_S */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SET_CAT_S(s, set) BOOST_PP_SET_FOLD_LEFT_ ## s(BOOST_PP_SET_CAT_O, BOOST_PP_SET_HEAD(set), BOOST_PP_SET_TAIL(set))
# else
#    define BOOST_PP_SET_CAT_S(s, set) BOOST_PP_SET_CAT_S_I(s, set)
#    define BOOST_PP_SET_CAT_S_I(s, set) BOOST_PP_SET_FOLD_LEFT_ ## s(BOOST_PP_SET_CAT_O, BOOST_PP_SET_HEAD(set), BOOST_PP_SET_TAIL(set))
# endif
#
# endif
