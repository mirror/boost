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
# ifndef BOOST_PREPROCESSOR_SET_SET_HPP
# define BOOST_PREPROCESSOR_SET_SET_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/set/elem.hpp>
#
# /* BOOST_PP_SET_HEAD */
#
# define BOOST_PP_SET_HEAD(set) BOOST_PP_SET_ELEM(0, set)
#
# /* BOOST_PP_SET_TAIL */
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_SET_TAIL(set) BOOST_PP_SET_TAIL_1((set))
#    define BOOST_PP_SET_TAIL_1(par) BOOST_PP_SET_TAIL_2 ## par
#    define BOOST_PP_SET_TAIL_2(set) BOOST_PP_SET_TAIL_I ## set
# elif BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_SET_TAIL(set) BOOST_PP_SET_TAIL_ID(BOOST_PP_SET_TAIL_I set)
#    define BOOST_PP_SET_TAIL_ID(id) id
# elif BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SET_TAIL(set) BOOST_PP_SET_TAIL_D(set)
#    define BOOST_PP_SET_TAIL_D(set) BOOST_PP_SET_TAIL_I set
# else
#    define BOOST_PP_SET_TAIL(set) BOOST_PP_SET_TAIL_I set
# endif
#
# define BOOST_PP_SET_TAIL_I(x)
#
# /* BOOST_PP_SET_NIL */
#
# define BOOST_PP_SET_NIL(x) (x)
#
# endif
