# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Permission to copy, use, modify, sell and distribute this software is
#  * granted provided this copyright notice appears in all copies. This
#  * software is provided "as is" without express or implied warranty, and
#  * with no claim as to its suitability for any purpose.
#  *
#  * See http://www.boost.org for most recent version.
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# ifndef BOOST_PREPROCESSOR_REPETITION_REPEAT_FROM_TO_HPP
# define BOOST_PREPROCESSOR_REPETITION_REPEAT_FROM_TO_HPP
#
# include <boost/preprocessor/arithmetic/add.hpp>
# include <boost/preprocessor/arithmetic/sub.hpp>
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/detail/auto_rec.hpp>
# include <boost/preprocessor/repetition/repeat.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_REPEAT_FROM_TO */
#
# if 0
#    define BOOST_PP_REPEAT_FROM_TO(first, last, macro, data)
# endif
#
# define BOOST_PP_REPEAT_FROM_TO BOOST_PP_CAT(BOOST_PP_REPEAT_FROM_TO_, BOOST_PP_AUTO_REC(BOOST_PP_REPEAT_P, 4))
#
# if ~BOOST_PP_CONFIG_FLAGS & BOOST_PP_CONFIG_EDG
#    define BOOST_PP_REPEAT_FROM_TO_1(f, l, m, d) BOOST_PP_REPEAT_1(BOOST_PP_SUB(l, f), BOOST_PP_REPEAT_FROM_TO_M_1, (f, m, d))
#    define BOOST_PP_REPEAT_FROM_TO_2(f, l, m, d) BOOST_PP_REPEAT_2(BOOST_PP_SUB(l, f), BOOST_PP_REPEAT_FROM_TO_M_2, (f, m, d))
#    define BOOST_PP_REPEAT_FROM_TO_3(f, l, m, d) BOOST_PP_REPEAT_3(BOOST_PP_SUB(l, f), BOOST_PP_REPEAT_FROM_TO_M_3, (f, m, d))
# else
#    define BOOST_PP_REPEAT_FROM_TO_1(f, l, m, d) BOOST_PP_REPEAT_FROM_TO_1_D(f, l, m, d)
#    define BOOST_PP_REPEAT_FROM_TO_2(f, l, m, d) BOOST_PP_REPEAT_FROM_TO_2_D(f, l, m, d)
#    define BOOST_PP_REPEAT_FROM_TO_3(f, l, m, d) BOOST_PP_REPEAT_FROM_TO_3_D(f, l, m, d)
#    define BOOST_PP_REPEAT_FROM_TO_1_D(f, l, m, d) BOOST_PP_REPEAT_1(BOOST_PP_SUB(l, f), BOOST_PP_REPEAT_FROM_TO_M_1, (f, m, d))
#    define BOOST_PP_REPEAT_FROM_TO_2_D(f, l, m, d) BOOST_PP_REPEAT_2(BOOST_PP_SUB(l, f), BOOST_PP_REPEAT_FROM_TO_M_2, (f, m, d))
#    define BOOST_PP_REPEAT_FROM_TO_3_D(f, l, m, d) BOOST_PP_REPEAT_3(BOOST_PP_SUB(l, f), BOOST_PP_REPEAT_FROM_TO_M_3, (f, m, d))
# endif
#
# define BOOST_PP_REPEAT_FROM_TO_1ST BOOST_PP_REPEAT_FROM_TO_1
# define BOOST_PP_REPEAT_FROM_TO_2ND BOOST_PP_REPEAT_FROM_TO_2
# define BOOST_PP_REPEAT_FROM_TO_3RD BOOST_PP_REPEAT_FROM_TO_3
#
# define BOOST_PP_REPEAT_FROM_TO_4(f, l, m, d) BOOST_PP_ERROR(0x0003)
#
# if BOOST_PP_CONFIG_FLAGS & BOOST_PP_CONFIG_STRICT
#    define BOOST_PP_REPEAT_FROM_TO_M_1(z, n, fmd) BOOST_PP_REPEAT_FROM_TO_M_1_I(z, n, BOOST_PP_TUPLE_REM_3 fmd)
#    define BOOST_PP_REPEAT_FROM_TO_M_1_I(z, n, fmd_e) BOOST_PP_REPEAT_FROM_TO_M_1_D(z, n, fmd_e)
# else
#    define BOOST_PP_REPEAT_FROM_TO_M_1(z, n, fmd) BOOST_PP_REPEAT_FROM_TO_M_1_D(z, n, BOOST_PP_TUPLE_ELEM(3, 0, fmd), BOOST_PP_TUPLE_ELEM(3, 1, fmd), BOOST_PP_TUPLE_ELEM(3, 2, fmd))
# endif
#
# define BOOST_PP_REPEAT_FROM_TO_M_1_D(z, n, f, m, d) m(z, BOOST_PP_ADD(n, f), d)
#
# if BOOST_PP_CONFIG_FLAGS & BOOST_PP_CONFIG_STRICT
#    define BOOST_PP_REPEAT_FROM_TO_M_2(z, n, fmd) BOOST_PP_REPEAT_FROM_TO_M_2_I(z, n, BOOST_PP_TUPLE_REM_3 fmd)
#    define BOOST_PP_REPEAT_FROM_TO_M_2_I(z, n, fmd_e) BOOST_PP_REPEAT_FROM_TO_M_2_D(z, n, fmd_e)
# else
#    define BOOST_PP_REPEAT_FROM_TO_M_2(z, n, fmd) BOOST_PP_REPEAT_FROM_TO_M_2_D(z, n, BOOST_PP_TUPLE_ELEM(3, 0, fmd), BOOST_PP_TUPLE_ELEM(3, 1, fmd), BOOST_PP_TUPLE_ELEM(3, 2, fmd))
# endif
#
# define BOOST_PP_REPEAT_FROM_TO_M_2_D(z, n, f, m, d) m(z, BOOST_PP_ADD(n, f), d)
#
# if BOOST_PP_CONFIG_FLAGS & BOOST_PP_CONFIG_STRICT
#    define BOOST_PP_REPEAT_FROM_TO_M_3(z, n, fmd) BOOST_PP_REPEAT_FROM_TO_M_3_I(z, n, BOOST_PP_TUPLE_REM_3 fmd)
#    define BOOST_PP_REPEAT_FROM_TO_M_3_I(z, n, fmd_e) BOOST_PP_REPEAT_FROM_TO_M_3_D(z, n, fmd_e)
# else
#    define BOOST_PP_REPEAT_FROM_TO_M_3(z, n, fmd) BOOST_PP_REPEAT_FROM_TO_M_3_D(z, n, BOOST_PP_TUPLE_ELEM(3, 0, fmd), BOOST_PP_TUPLE_ELEM(3, 1, fmd), BOOST_PP_TUPLE_ELEM(3, 2, fmd))
# endif
#
# define BOOST_PP_REPEAT_FROM_TO_M_3_D(z, n, f, m, d) m(z, BOOST_PP_ADD(n, f), d)
#
# endif
