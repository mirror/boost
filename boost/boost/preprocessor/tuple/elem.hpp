# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Permission to copy, use, modify, sell and distribute this software is
#  * granted provided this copyright notice appears in all copies. This
#  * software is provided "as is" without express or implied warranty, and
#  * with no claim as to its suitability for any purpose.
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_TUPLE_ELEM_HPP
# define BOOST_PREPROCESSOR_TUPLE_ELEM_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/debug/error.hpp>
#
# /* BOOST_PP_TUPLE_ELEM */
#
# if BOOST_PP_CONFIG_FLAGS & BOOST_PP_CONFIG_IDEAL || BOOST_PP_CONFIG_FLAGS & BOOST_PP_CONFIG_BCC
#    define BOOST_PP_TUPLE_ELEM(size, i, tuple) BOOST_PP_TUPLE_ELEM_D(size, i, tuple)
#    define BOOST_PP_TUPLE_ELEM_D(size, i, tuple) BOOST_PP_TUPLE_ELEM_D_II(BOOST_PP_TUPLE_ELEM_EX_ ## size tuple, i)
#    define BOOST_PP_TUPLE_ELEM_D_II(tuple, i) BOOST_PP_TUPLE_ELEM_ ## i tuple
# elif ~BOOST_PP_CONFIG_FLAGS & BOOST_PP_CONFIG_MWCW
#    define BOOST_PP_TUPLE_ELEM(size, index, tuple) BOOST_PP_TUPLE_ELEM_I(size, index, tuple)
#    define BOOST_PP_TUPLE_ELEM_I(size, i, tuple) BOOST_PP_TUPLE_ELEM_II(BOOST_PP_TUPLE_ELEM_EX_ ## size, i, tuple)
#    define BOOST_PP_TUPLE_ELEM_II(exp, i, tuple) BOOST_PP_TUPLE_ELEM_III(exp tuple, i)
#    define BOOST_PP_TUPLE_ELEM_III(ext, i) BOOST_PP_TUPLE_ELEM_IV(ext, i)
#    define BOOST_PP_TUPLE_ELEM_IV(ext, i) BOOST_PP_TUPLE_ELEM_V(BOOST_PP_TUPLE_ELEM_ ## i ext)
#    define BOOST_PP_TUPLE_ELEM_V(res) res
# else
#    define BOOST_PP_TUPLE_ELEM(size, index, tuple) BOOST_PP_TUPLE_ELEM_D((size, index, tuple))
#    define BOOST_PP_TUPLE_ELEM_D(par) BOOST_PP_TUPLE_ELEM_I ## par
#    define BOOST_PP_TUPLE_ELEM_I(s, i, t) BOOST_PP_TUPLE_ELEM_II((BOOST_PP_TUPLE_ELEM_EX_ ## s, i, t))
#    define BOOST_PP_TUPLE_ELEM_II(par) BOOST_PP_TUPLE_ELEM_III ## par
#    define BOOST_PP_TUPLE_ELEM_III(m, i, t) BOOST_PP_TUPLE_ELEM_IV((m ## t, i))
#    define BOOST_PP_TUPLE_ELEM_IV(par) BOOST_PP_TUPLE_ELEM_IV_D(par)
#    define BOOST_PP_TUPLE_ELEM_IV_D(par) BOOST_PP_TUPLE_ELEM_V ## par
#    define BOOST_PP_TUPLE_ELEM_V(x, i) BOOST_PP_TUPLE_ELEM_VI(BOOST_PP_TUPLE_ELEM_ ## i ## x)
#    define BOOST_PP_TUPLE_ELEM_VI(res) res
# endif
#
# define BOOST_PP_TUPLE_ELEM_EX_0() (BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000))
# define BOOST_PP_TUPLE_ELEM_EX_1(a) (a, BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000))
# define BOOST_PP_TUPLE_ELEM_EX_2(a, b) (a, b, BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000))
# define BOOST_PP_TUPLE_ELEM_EX_3(a, b, c) (a, b, c, BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000))
# define BOOST_PP_TUPLE_ELEM_EX_4(a, b, c, d) (a, b, c, d, BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000))
# define BOOST_PP_TUPLE_ELEM_EX_5(a, b, c, d, e) (a, b, c, d, e, BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000))
# define BOOST_PP_TUPLE_ELEM_EX_6(a, b, c, d, e, f) (a, b, c, d, e, f, BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000))
# define BOOST_PP_TUPLE_ELEM_EX_7(a, b, c, d, e, f, g) (a, b, c, d, e, f, g, BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000))
# define BOOST_PP_TUPLE_ELEM_EX_8(a, b, c, d, e, f, g, h) (a, b, c, d, e, f, g, h, BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000))
# define BOOST_PP_TUPLE_ELEM_EX_9(a, b, c, d, e, f, g, h, i) (a, b, c, d, e, f, g, h, i, BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000))
# define BOOST_PP_TUPLE_ELEM_EX_10(a, b, c, d, e, f, g, h, i, j) (a, b, c, d, e, f, g, h, i, j, BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000))
# define BOOST_PP_TUPLE_ELEM_EX_11(a, b, c, d, e, f, g, h, i, j, k) (a, b, c, d, e, f, g, h, i, j, k, BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000))
# define BOOST_PP_TUPLE_ELEM_EX_12(a, b, c, d, e, f, g, h, i, j, k, l) (a, b, c, d, e, f, g, h, i, j, k, l, BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000))
# define BOOST_PP_TUPLE_ELEM_EX_13(a, b, c, d, e, f, g, h, i, j, k, l, m) (a, b, c, d, e, f, g, h, i, j, k, l, m, BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000))
# define BOOST_PP_TUPLE_ELEM_EX_14(a, b, c, d, e, f, g, h, i, j, k, l, m, n) (a, b, c, d, e, f, g, h, i, j, k, l, m, n, BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000))
# define BOOST_PP_TUPLE_ELEM_EX_15(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o) (a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000))
# define BOOST_PP_TUPLE_ELEM_EX_16(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p) (a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000))
# define BOOST_PP_TUPLE_ELEM_EX_17(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q) (a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000))
# define BOOST_PP_TUPLE_ELEM_EX_18(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r) (a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000))
# define BOOST_PP_TUPLE_ELEM_EX_19(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s) (a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000))
# define BOOST_PP_TUPLE_ELEM_EX_20(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t) (a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000))
# define BOOST_PP_TUPLE_ELEM_EX_21(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u) (a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000))
# define BOOST_PP_TUPLE_ELEM_EX_22(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v) (a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000))
# define BOOST_PP_TUPLE_ELEM_EX_23(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w) (a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, BOOST_PP_ERROR(0x0000), BOOST_PP_ERROR(0x0000))
# define BOOST_PP_TUPLE_ELEM_EX_24(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x) (a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, BOOST_PP_ERROR(0x0000))
# define BOOST_PP_TUPLE_ELEM_EX_25(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y) (a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y)
#
# define BOOST_PP_TUPLE_ELEM_0(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y) a
# define BOOST_PP_TUPLE_ELEM_1(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y) b
# define BOOST_PP_TUPLE_ELEM_2(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y) c
# define BOOST_PP_TUPLE_ELEM_3(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y) d
# define BOOST_PP_TUPLE_ELEM_4(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y) e
# define BOOST_PP_TUPLE_ELEM_5(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y) f
# define BOOST_PP_TUPLE_ELEM_6(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y) g
# define BOOST_PP_TUPLE_ELEM_7(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y) h
# define BOOST_PP_TUPLE_ELEM_8(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y) i
# define BOOST_PP_TUPLE_ELEM_9(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y) j
# define BOOST_PP_TUPLE_ELEM_10(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y) k
# define BOOST_PP_TUPLE_ELEM_11(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y) l
# define BOOST_PP_TUPLE_ELEM_12(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y) m
# define BOOST_PP_TUPLE_ELEM_13(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y) n
# define BOOST_PP_TUPLE_ELEM_14(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y) o
# define BOOST_PP_TUPLE_ELEM_15(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y) p
# define BOOST_PP_TUPLE_ELEM_16(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y) q
# define BOOST_PP_TUPLE_ELEM_17(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y) r
# define BOOST_PP_TUPLE_ELEM_18(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y) s
# define BOOST_PP_TUPLE_ELEM_19(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y) t
# define BOOST_PP_TUPLE_ELEM_20(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y) u
# define BOOST_PP_TUPLE_ELEM_21(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y) v
# define BOOST_PP_TUPLE_ELEM_22(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y) w
# define BOOST_PP_TUPLE_ELEM_23(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y) x
# define BOOST_PP_TUPLE_ELEM_24(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y) y
#
# endif
