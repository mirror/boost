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
# ifndef BOOST_PREPROCESSOR_SET_FOR_EACH_HPP
# define BOOST_PREPROCESSOR_SET_FOR_EACH_HPP
#
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/repetition/for.hpp>
# include <boost/preprocessor/set/set.hpp>
# include <boost/preprocessor/set/size.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_SET_FOR_EACH */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SET_FOR_EACH(macro, data, set) BOOST_PP_FOR((macro, data, set (nil)), BOOST_PP_SET_FOR_EACH_P, BOOST_PP_SET_FOR_EACH_O, BOOST_PP_SET_FOR_EACH_M)
# else
#    define BOOST_PP_SET_FOR_EACH(macro, data, set) BOOST_PP_SET_FOR_EACH_D(macro, data, set)
#    define BOOST_PP_SET_FOR_EACH_D(macro, data, set) BOOST_PP_FOR((macro, data, set (nil)), BOOST_PP_SET_FOR_EACH_P, BOOST_PP_SET_FOR_EACH_O, BOOST_PP_SET_FOR_EACH_M)
# endif
#
# define BOOST_PP_SET_FOR_EACH_P(r, x) BOOST_PP_DEC(BOOST_PP_SET_SIZE(BOOST_PP_TUPLE_ELEM(3, 2, x)))
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_SET_FOR_EACH_O(r, x) BOOST_PP_SET_FOR_EACH_O_I x
# else
#    define BOOST_PP_SET_FOR_EACH_O(r, x) BOOST_PP_SET_FOR_EACH_O_I(BOOST_PP_TUPLE_ELEM(3, 0, x), BOOST_PP_TUPLE_ELEM(3, 1, x), BOOST_PP_TUPLE_ELEM(3, 2, x))
# endif
#
# define BOOST_PP_SET_FOR_EACH_O_I(macro, data, set) (macro, data, BOOST_PP_SET_TAIL(set))
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_SET_FOR_EACH_M(r, x) BOOST_PP_SET_FOR_EACH_M_IM(r, BOOST_PP_TUPLE_REM_3 x)
#    define BOOST_PP_SET_FOR_EACH_M_IM(r, im) BOOST_PP_SET_FOR_EACH_M_I(r, im)
# else
#    define BOOST_PP_SET_FOR_EACH_M(r, x) BOOST_PP_SET_FOR_EACH_M_I(r, BOOST_PP_TUPLE_ELEM(3, 0, x), BOOST_PP_TUPLE_ELEM(3, 1, x), BOOST_PP_TUPLE_ELEM(3, 2, x))
# endif
#
# define BOOST_PP_SET_FOR_EACH_M_I(r, macro, data, set) macro(r, data, BOOST_PP_SET_HEAD(set))
#
# /* BOOST_PP_SET_FOR_EACH_R */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SET_FOR_EACH_R(r, macro, data, set) BOOST_PP_FOR_ ## r((macro, data, set (nil)), BOOST_PP_SET_FOR_EACH_P, BOOST_PP_SET_FOR_EACH_O, BOOST_PP_SET_FOR_EACH_M)
# else
#    define BOOST_PP_SET_FOR_EACH_R(r, macro, data, set) BOOST_PP_SET_FOR_EACH_R_I(r, macro, data, set)
#    define BOOST_PP_SET_FOR_EACH_R_I(r, macro, data, set) BOOST_PP_FOR_ ## r((macro, data, set (nil)), BOOST_PP_SET_FOR_EACH_P, BOOST_PP_SET_FOR_EACH_O, BOOST_PP_SET_FOR_EACH_M)
# endif
#
# endif
