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
# ifndef BOOST_PREPROCESSOR_REPETITION_ENUM_SHIFTED_HPP
# define BOOST_PREPROCESSOR_REPETITION_ENUM_SHIFTED_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/detail/auto_rec.hpp>
# include <boost/preprocessor/punctuation/comma_if.hpp>
# include <boost/preprocessor/repetition/repeat.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_ENUM_SHIFTED */
#
# if 0
#    define BOOST_PP_ENUM_SHIFTED(count, macro, data)
# endif
#
# define BOOST_PP_ENUM_SHIFTED BOOST_PP_CAT(BOOST_PP_ENUM_SHIFTED_, BOOST_PP_AUTO_REC(BOOST_PP_REPEAT_P, 4))
#
# define BOOST_PP_ENUM_SHIFTED_4(c, m, d) BOOST_PP_ERROR(0x003)
#
# if ~BOOST_PP_CONFIG_FLAGS & BOOST_PP_CONFIG_EDG
#    define BOOST_PP_ENUM_SHIFTED_1(c, m, d) BOOST_PP_REPEAT_1(BOOST_PP_DEC(c), BOOST_PP_ENUM_SHIFTED_M_1, (m, d))
#    define BOOST_PP_ENUM_SHIFTED_2(c, m, d) BOOST_PP_REPEAT_2(BOOST_PP_DEC(c), BOOST_PP_ENUM_SHIFTED_M_2, (m, d))
#    define BOOST_PP_ENUM_SHIFTED_3(c, m, d) BOOST_PP_REPEAT_3(BOOST_PP_DEC(c), BOOST_PP_ENUM_SHIFTED_M_3, (m, d))
# else
#    define BOOST_PP_ENUM_SHIFTED_1(c, m, d) BOOST_PP_ENUM_SHIFTED_1_D(c, m, d)
#    define BOOST_PP_ENUM_SHIFTED_2(c, m, d) BOOST_PP_ENUM_SHIFTED_2_D(c, m, d)
#    define BOOST_PP_ENUM_SHIFTED_3(c, m, d) BOOST_PP_ENUM_SHIFTED_3_D(c, m, d)
#    define BOOST_PP_ENUM_SHIFTED_1_D(c, m, d) BOOST_PP_REPEAT_1(BOOST_PP_DEC(c), BOOST_PP_ENUM_SHIFTED_M_1, (m, d))
#    define BOOST_PP_ENUM_SHIFTED_2_D(c, m, d) BOOST_PP_REPEAT_2(BOOST_PP_DEC(c), BOOST_PP_ENUM_SHIFTED_M_2, (m, d))
#    define BOOST_PP_ENUM_SHIFTED_3_D(c, m, d) BOOST_PP_REPEAT_3(BOOST_PP_DEC(c), BOOST_PP_ENUM_SHIFTED_M_3, (m, d))
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS & BOOST_PP_CONFIG_MWCW && ~BOOST_PP_CONFIG_FLAGS & BOOST_PP_CONFIG_EDG
#    define BOOST_PP_ENUM_SHIFTED_M_1(z, n, md) BOOST_PP_COMMA_IF(n) BOOST_PP_TUPLE_ELEM(2, 0, md)(z, BOOST_PP_INC(n), BOOST_PP_TUPLE_ELEM(2, 1, md))
#    define BOOST_PP_ENUM_SHIFTED_M_2(z, n, md) BOOST_PP_COMMA_IF(n) BOOST_PP_TUPLE_ELEM(2, 0, md)(z, BOOST_PP_INC(n), BOOST_PP_TUPLE_ELEM(2, 1, md))
#    define BOOST_PP_ENUM_SHIFTED_M_3(z, n, md) BOOST_PP_COMMA_IF(n) BOOST_PP_TUPLE_ELEM(2, 0, md)(z, BOOST_PP_INC(n), BOOST_PP_TUPLE_ELEM(2, 1, md))
# elif BOOST_PP_CONFIG_FLAGS & BOOST_PP_CONFIG_EDG
#    define BOOST_PP_ENUM_SHIFTED_M_1(z, n, md) BOOST_PP_ENUM_SHIFTED_M_1_A(z, n, BOOST_PP_TUPLE_REM_2 md)
#    define BOOST_PP_ENUM_SHIFTED_M_1_A(z, n, md_e) BOOST_PP_ENUM_SHIFTED_M_1_B(z, n, md_e)
#    define BOOST_PP_ENUM_SHIFTED_M_1_B(z, n, m, d) BOOST_PP_COMMA_IF(n) m(z, BOOST_PP_INC(n), d)
#    define BOOST_PP_ENUM_SHIFTED_M_2(z, n, md) BOOST_PP_ENUM_SHIFTED_M_2_A(z, n, BOOST_PP_TUPLE_REM_2 md)
#    define BOOST_PP_ENUM_SHIFTED_M_2_A(z, n, md_e) BOOST_PP_ENUM_SHIFTED_M_2_B(z, n, md_e)
#    define BOOST_PP_ENUM_SHIFTED_M_2_B(z, n, m, d) BOOST_PP_COMMA_IF(n) m(z, BOOST_PP_INC(n), d)
#    define BOOST_PP_ENUM_SHIFTED_M_3(z, n, md) BOOST_PP_ENUM_SHIFTED_M_3_A(z, n, BOOST_PP_TUPLE_REM_2 md)
#    define BOOST_PP_ENUM_SHIFTED_M_3_A(z, n, md_e) BOOST_PP_ENUM_SHIFTED_M_3_B(z, n, md_e)
#    define BOOST_PP_ENUM_SHIFTED_M_3_B(z, n, m, d) BOOST_PP_COMMA_IF(n) m(z, BOOST_PP_INC(n), d)
# else
#    define BOOST_PP_ENUM_SHIFTED_M_1(z, n, md) BOOST_PP_ENUM_SHIFTED_M_1_D(z, n, BOOST_PP_TUPLE_ELEM(2, 0, md), BOOST_PP_TUPLE_ELEM(2, 1, md))
#    define BOOST_PP_ENUM_SHIFTED_M_1_D(z, n, m, d) BOOST_PP_COMMA_IF(n) m(z, BOOST_PP_INC(n), d)
#    define BOOST_PP_ENUM_SHIFTED_M_2(z, n, md) BOOST_PP_ENUM_SHIFTED_M_2_D(z, n, BOOST_PP_TUPLE_ELEM(2, 0, md), BOOST_PP_TUPLE_ELEM(2, 1, md))
#    define BOOST_PP_ENUM_SHIFTED_M_2_D(z, n, m, d) BOOST_PP_COMMA_IF(n) m(z, BOOST_PP_INC(n), d)
#    define BOOST_PP_ENUM_SHIFTED_M_3(z, n, md) BOOST_PP_ENUM_SHIFTED_M_3_D(z, n, BOOST_PP_TUPLE_ELEM(2, 0, md), BOOST_PP_TUPLE_ELEM(2, 1, md))
#    define BOOST_PP_ENUM_SHIFTED_M_3_D(z, n, m, d) BOOST_PP_COMMA_IF(n) m(z, BOOST_PP_INC(n), d)
# endif
#
# endif
