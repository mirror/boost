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
# ifndef BOOST_PREPROCESSOR_SLOT_HPP
# define BOOST_PREPROCESSOR_SLOT_HPP
#
# include <boost/preprocessor/detail/cat.hpp>
# include <boost/preprocessor/detail/line.hpp>
#
# define BOOST_PP_SLOT_LIMIT 5
# define BOOST_PP_SLOT_MAX 4294967295 /* 2^32 - 1 */
#
# define BOOST_PP_ASSIGN_SLOT(i) BOOST_PP_DETAIL_CAT2(BOOST_PP_ASSIGN_SLOT_, i)
# define BOOST_PP_ASSIGN_SLOT_1 <boost/preprocessor/detail/slot/slot1.hpp>
# define BOOST_PP_ASSIGN_SLOT_2 <boost/preprocessor/detail/slot/slot2.hpp>
# define BOOST_PP_ASSIGN_SLOT_3 <boost/preprocessor/detail/slot/slot3.hpp>
# define BOOST_PP_ASSIGN_SLOT_4 <boost/preprocessor/detail/slot/slot4.hpp>
# define BOOST_PP_ASSIGN_SLOT_5 <boost/preprocessor/detail/slot/slot5.hpp>
#
# define BOOST_PP_SLOT(i) BOOST_PP_DETAIL_CAT2(BOOST_PP_SLOT_, i)()
#
# ifndef BOOST_PP_SLOT_SIG
#   define BOOST_PP_SLOT_SIG 10
# endif
#
# if BOOST_PP_SLOT_SIG >= 10
#    define BOOST_PP_SLOT_10TH(x) (x) % 1000000000UL
# else
#    define BOOST_PP_SLOT_10TH(x) (x)
# endif
#
# if BOOST_PP_SLOT_SIG >= 9
#    define BOOST_PP_SLOT_9TH(x) BOOST_PP_SLOT_10TH(x) % 100000000UL
# else
#    define BOOST_PP_SLOT_9TH(x) (x)
# endif
#
# if BOOST_PP_SLOT_SIG >= 8
#    define BOOST_PP_SLOT_8TH(x) BOOST_PP_SLOT_9TH(x) % 10000000UL
# else
#    define BOOST_PP_SLOT_8TH(x) (x)
# endif
#
# if BOOST_PP_SLOT_SIG >= 7
#    define BOOST_PP_SLOT_7TH(x) BOOST_PP_SLOT_8TH(x) % 1000000UL
# else
#    define BOOST_PP_SLOT_7TH(x) (x)
# endif
#
# if BOOST_PP_SLOT_SIG >= 6
#    define BOOST_PP_SLOT_6TH(x) BOOST_PP_SLOT_7TH(x) % 100000UL
# else
#    define BOOST_PP_SLOT_6TH(x) (x)
# endif
#
# if BOOST_PP_SLOT_SIG >= 5
#    define BOOST_PP_SLOT_5TH(x) BOOST_PP_SLOT_6TH(x) % 10000UL
# else
#    define BOOST_PP_SLOT_5TH(x) (x)
# endif
#
# if BOOST_PP_SLOT_SIG >= 4
#    define BOOST_PP_SLOT_4TH(x) BOOST_PP_SLOT_5TH(x) % 1000UL
# else
#    define BOOST_PP_SLOT_4TH(x) (x)
# endif
#
# if BOOST_PP_SLOT_SIG >= 3
#    define BOOST_PP_SLOT_3RD(x) BOOST_PP_SLOT_4TH(x) % 100UL
# else
#    define BOOST_PP_SLOT_3RD(x) (x)
# endif
#
# if BOOST_PP_SLOT_SIG >= 2
#    define BOOST_PP_SLOT_2ND(x) BOOST_PP_SLOT_3RD(x) % 10UL
# else
#    define BOOST_PP_SLOT_2ND(x) (x)
# endif
#
# define BOOST_PP_SLOT_CC_2(a, b) BOOST_PP_DETAIL_CAT2(a, b)
# define BOOST_PP_SLOT_CC_3(a, b, c) BOOST_PP_DETAIL_CAT2(BOOST_PP_SLOT_CC_2(a, b), c)
# define BOOST_PP_SLOT_CC_4(a, b, c, d) BOOST_PP_DETAIL_CAT2(BOOST_PP_SLOT_CC_3(a, b, c), d)
# define BOOST_PP_SLOT_CC_5(a, b, c, d, e) BOOST_PP_DETAIL_CAT2(BOOST_PP_SLOT_CC_4(a, b, c, d), e)
# define BOOST_PP_SLOT_CC_6(a, b, c, d, e, f) BOOST_PP_DETAIL_CAT2(BOOST_PP_SLOT_CC_5(a, b, c, d, e), f)
# define BOOST_PP_SLOT_CC_7(a, b, c, d, e, f, g) BOOST_PP_DETAIL_CAT2(BOOST_PP_SLOT_CC_6(a, b, c, d, e, f), g)
# define BOOST_PP_SLOT_CC_8(a, b, c, d, e, f, g, h) BOOST_PP_DETAIL_CAT2(BOOST_PP_SLOT_CC_7(a, b, c, d, e, f, g), h)
# define BOOST_PP_SLOT_CC_9(a, b, c, d, e, f, g, h, i) BOOST_PP_DETAIL_CAT2(BOOST_PP_SLOT_CC_8(a, b, c, d, e, f, g, h), i)
# define BOOST_PP_SLOT_CC_10(a, b, c, d, e, f, g, h, i, j) BOOST_PP_DETAIL_CAT2(BOOST_PP_SLOT_CC_9(a, b, c, d, e, f, g, h, i), j)
#
# endif
