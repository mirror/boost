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
# if !defined(BOOST_PP_VALUE)
#   error BOOST_PP_ERROR:  BOOST_PP_VALUE is not defined
# elif (BOOST_PP_VALUE) > BOOST_PP_SLOT_MAX
#   error BOOST_PP_ERROR:  slot value overflow
# endif
#
# undef BOOST_PP_SLOT_TEMP_1
# undef BOOST_PP_SLOT_TEMP_2
# undef BOOST_PP_SLOT_TEMP_3
# undef BOOST_PP_SLOT_TEMP_4
# undef BOOST_PP_SLOT_TEMP_5
# undef BOOST_PP_SLOT_TEMP_6
# undef BOOST_PP_SLOT_TEMP_7
# undef BOOST_PP_SLOT_TEMP_8
# undef BOOST_PP_SLOT_TEMP_9
# undef BOOST_PP_SLOT_TEMP_10
#
# /* 10th digit */
#
# if BOOST_PP_SLOT_SIG >= 10
#    if (BOOST_PP_VALUE) / 1000000000UL == 0
#        define BOOST_PP_SLOT_TEMP_10 0
#    elif (BOOST_PP_VALUE) / 1000000000UL == 1
#        define BOOST_PP_SLOT_TEMP_10 1
#    elif (BOOST_PP_VALUE) / 1000000000UL == 2
#        define BOOST_PP_SLOT_TEMP_10 2
#    elif (BOOST_PP_VALUE) / 1000000000UL == 3
#        define BOOST_PP_SLOT_TEMP_10 3
#    elif (BOOST_PP_VALUE) / 1000000000UL == 4
#        define BOOST_PP_SLOT_TEMP_10 4
#    elif (BOOST_PP_VALUE) / 1000000000UL == 5
#        define BOOST_PP_SLOT_TEMP_10 5
#    elif (BOOST_PP_VALUE) / 1000000000UL == 6
#        define BOOST_PP_SLOT_TEMP_10 6
#    elif (BOOST_PP_VALUE) / 1000000000UL == 7
#        define BOOST_PP_SLOT_TEMP_10 7
#    elif (BOOST_PP_VALUE) / 1000000000UL == 8
#        define BOOST_PP_SLOT_TEMP_10 8
#    elif (BOOST_PP_VALUE) / 1000000000UL == 9
#        define BOOST_PP_SLOT_TEMP_10 9
#    endif
# endif
#
# /* 9th digit */
#
# if BOOST_PP_SLOT_SIG >= 9
#    if BOOST_PP_SLOT_10TH(BOOST_PP_VALUE) / 100000000UL == 0
#        define BOOST_PP_SLOT_TEMP_9 0
#    elif BOOST_PP_SLOT_10TH(BOOST_PP_VALUE) / 100000000UL == 1
#        define BOOST_PP_SLOT_TEMP_9 1
#    elif BOOST_PP_SLOT_10TH(BOOST_PP_VALUE) / 100000000UL == 2
#        define BOOST_PP_SLOT_TEMP_9 2
#    elif BOOST_PP_SLOT_10TH(BOOST_PP_VALUE) / 100000000UL == 3
#        define BOOST_PP_SLOT_TEMP_9 3
#    elif BOOST_PP_SLOT_10TH(BOOST_PP_VALUE) / 100000000UL == 4
#        define BOOST_PP_SLOT_TEMP_9 4
#    elif BOOST_PP_SLOT_10TH(BOOST_PP_VALUE) / 100000000UL == 5
#        define BOOST_PP_SLOT_TEMP_9 5
#    elif BOOST_PP_SLOT_10TH(BOOST_PP_VALUE) / 100000000UL == 6
#        define BOOST_PP_SLOT_TEMP_9 6
#    elif BOOST_PP_SLOT_10TH(BOOST_PP_VALUE) / 100000000UL == 7
#        define BOOST_PP_SLOT_TEMP_9 7
#    elif BOOST_PP_SLOT_10TH(BOOST_PP_VALUE) / 100000000UL == 8
#        define BOOST_PP_SLOT_TEMP_9 8
#    elif BOOST_PP_SLOT_10TH(BOOST_PP_VALUE) / 100000000UL == 9
#        define BOOST_PP_SLOT_TEMP_9 9
#    endif
# endif
#
# /* 8th digit */
#
# if BOOST_PP_SLOT_SIG >= 8
#    if BOOST_PP_SLOT_9TH(BOOST_PP_VALUE) / 10000000UL == 0
#        define BOOST_PP_SLOT_TEMP_8 0
#    elif BOOST_PP_SLOT_9TH(BOOST_PP_VALUE) / 10000000UL == 1
#        define BOOST_PP_SLOT_TEMP_8 1
#    elif BOOST_PP_SLOT_9TH(BOOST_PP_VALUE) / 10000000UL == 2
#        define BOOST_PP_SLOT_TEMP_8 2
#    elif BOOST_PP_SLOT_9TH(BOOST_PP_VALUE) / 10000000UL == 3
#        define BOOST_PP_SLOT_TEMP_8 3
#    elif BOOST_PP_SLOT_9TH(BOOST_PP_VALUE) / 10000000UL == 4
#        define BOOST_PP_SLOT_TEMP_8 4
#    elif BOOST_PP_SLOT_9TH(BOOST_PP_VALUE) / 10000000UL == 5
#        define BOOST_PP_SLOT_TEMP_8 5
#    elif BOOST_PP_SLOT_9TH(BOOST_PP_VALUE) / 10000000UL == 6
#        define BOOST_PP_SLOT_TEMP_8 6
#    elif BOOST_PP_SLOT_9TH(BOOST_PP_VALUE) / 10000000UL == 7
#        define BOOST_PP_SLOT_TEMP_8 7
#    elif BOOST_PP_SLOT_9TH(BOOST_PP_VALUE) / 10000000UL == 8
#        define BOOST_PP_SLOT_TEMP_8 8
#    elif BOOST_PP_SLOT_9TH(BOOST_PP_VALUE) / 10000000UL == 9
#        define BOOST_PP_SLOT_TEMP_8 9
#    endif
# endif
#
# /* 7th digit */
#
# if BOOST_PP_SLOT_SIG >= 7
#    if BOOST_PP_SLOT_8TH(BOOST_PP_VALUE) / 1000000UL == 0
#        define BOOST_PP_SLOT_TEMP_7 0
#    elif BOOST_PP_SLOT_8TH(BOOST_PP_VALUE) / 1000000UL == 1
#        define BOOST_PP_SLOT_TEMP_7 1
#    elif BOOST_PP_SLOT_8TH(BOOST_PP_VALUE) / 1000000UL == 2
#        define BOOST_PP_SLOT_TEMP_7 2
#    elif BOOST_PP_SLOT_8TH(BOOST_PP_VALUE) / 1000000UL == 3
#        define BOOST_PP_SLOT_TEMP_7 3
#    elif BOOST_PP_SLOT_8TH(BOOST_PP_VALUE) / 1000000UL == 4
#        define BOOST_PP_SLOT_TEMP_7 4
#    elif BOOST_PP_SLOT_8TH(BOOST_PP_VALUE) / 1000000UL == 5
#        define BOOST_PP_SLOT_TEMP_7 5
#    elif BOOST_PP_SLOT_8TH(BOOST_PP_VALUE) / 1000000UL == 6
#        define BOOST_PP_SLOT_TEMP_7 6
#    elif BOOST_PP_SLOT_8TH(BOOST_PP_VALUE) / 1000000UL == 7
#        define BOOST_PP_SLOT_TEMP_7 7
#    elif BOOST_PP_SLOT_8TH(BOOST_PP_VALUE) / 1000000UL == 8
#        define BOOST_PP_SLOT_TEMP_7 8
#    elif BOOST_PP_SLOT_8TH(BOOST_PP_VALUE) / 1000000UL == 9
#        define BOOST_PP_SLOT_TEMP_7 9
#    endif
# endif
#
# /* 6th digit */
#
# if BOOST_PP_SLOT_SIG >= 6
#    if BOOST_PP_SLOT_7TH(BOOST_PP_VALUE) / 100000UL == 0
#        define BOOST_PP_SLOT_TEMP_6 0
#    elif BOOST_PP_SLOT_7TH(BOOST_PP_VALUE) / 100000UL == 1
#        define BOOST_PP_SLOT_TEMP_6 1
#    elif BOOST_PP_SLOT_7TH(BOOST_PP_VALUE) / 100000UL == 2
#        define BOOST_PP_SLOT_TEMP_6 2
#    elif BOOST_PP_SLOT_7TH(BOOST_PP_VALUE) / 100000UL == 3
#        define BOOST_PP_SLOT_TEMP_6 3
#    elif BOOST_PP_SLOT_7TH(BOOST_PP_VALUE) / 100000UL == 4
#        define BOOST_PP_SLOT_TEMP_6 4
#    elif BOOST_PP_SLOT_7TH(BOOST_PP_VALUE) / 100000UL == 5
#        define BOOST_PP_SLOT_TEMP_6 5
#    elif BOOST_PP_SLOT_7TH(BOOST_PP_VALUE) / 100000UL == 6
#        define BOOST_PP_SLOT_TEMP_6 6
#    elif BOOST_PP_SLOT_7TH(BOOST_PP_VALUE) / 100000UL == 7
#        define BOOST_PP_SLOT_TEMP_6 7
#    elif BOOST_PP_SLOT_7TH(BOOST_PP_VALUE) / 100000UL == 8
#        define BOOST_PP_SLOT_TEMP_6 8
#    elif BOOST_PP_SLOT_7TH(BOOST_PP_VALUE) / 100000UL == 9
#        define BOOST_PP_SLOT_TEMP_6 9
#    endif
# endif
#
# /* 5th digit */
#
# if BOOST_PP_SLOT_SIG >= 5
#    if BOOST_PP_SLOT_6TH(BOOST_PP_VALUE) / 10000UL == 0
#        define BOOST_PP_SLOT_TEMP_5 0
#    elif BOOST_PP_SLOT_6TH(BOOST_PP_VALUE) / 10000UL == 1
#        define BOOST_PP_SLOT_TEMP_5 1
#    elif BOOST_PP_SLOT_6TH(BOOST_PP_VALUE) / 10000UL == 2
#        define BOOST_PP_SLOT_TEMP_5 2
#    elif BOOST_PP_SLOT_6TH(BOOST_PP_VALUE) / 10000UL == 3
#        define BOOST_PP_SLOT_TEMP_5 3
#    elif BOOST_PP_SLOT_6TH(BOOST_PP_VALUE) / 10000UL == 4
#        define BOOST_PP_SLOT_TEMP_5 4
#    elif BOOST_PP_SLOT_6TH(BOOST_PP_VALUE) / 10000UL == 5
#        define BOOST_PP_SLOT_TEMP_5 5
#    elif BOOST_PP_SLOT_6TH(BOOST_PP_VALUE) / 10000UL == 6
#        define BOOST_PP_SLOT_TEMP_5 6
#    elif BOOST_PP_SLOT_6TH(BOOST_PP_VALUE) / 10000UL == 7
#        define BOOST_PP_SLOT_TEMP_5 7
#    elif BOOST_PP_SLOT_6TH(BOOST_PP_VALUE) / 10000UL == 8
#        define BOOST_PP_SLOT_TEMP_5 8
#    elif BOOST_PP_SLOT_6TH(BOOST_PP_VALUE) / 10000UL == 9
#        define BOOST_PP_SLOT_TEMP_5 9
#    endif
# endif
#
# /* 4th digit */
#
# if BOOST_PP_SLOT_SIG >= 4
#    if BOOST_PP_SLOT_5TH(BOOST_PP_VALUE) / 1000UL == 0
#        define BOOST_PP_SLOT_TEMP_4 0
#    elif BOOST_PP_SLOT_5TH(BOOST_PP_VALUE) / 1000UL == 1
#        define BOOST_PP_SLOT_TEMP_4 1
#    elif BOOST_PP_SLOT_5TH(BOOST_PP_VALUE) / 1000UL == 2
#        define BOOST_PP_SLOT_TEMP_4 2
#    elif BOOST_PP_SLOT_5TH(BOOST_PP_VALUE) / 1000UL == 3
#        define BOOST_PP_SLOT_TEMP_4 3
#    elif BOOST_PP_SLOT_5TH(BOOST_PP_VALUE) / 1000UL == 4
#        define BOOST_PP_SLOT_TEMP_4 4
#    elif BOOST_PP_SLOT_5TH(BOOST_PP_VALUE) / 1000UL == 5
#        define BOOST_PP_SLOT_TEMP_4 5
#    elif BOOST_PP_SLOT_5TH(BOOST_PP_VALUE) / 1000UL == 6
#        define BOOST_PP_SLOT_TEMP_4 6
#    elif BOOST_PP_SLOT_5TH(BOOST_PP_VALUE) / 1000UL == 7
#        define BOOST_PP_SLOT_TEMP_4 7
#    elif BOOST_PP_SLOT_5TH(BOOST_PP_VALUE) / 1000UL == 8
#        define BOOST_PP_SLOT_TEMP_4 8
#    elif BOOST_PP_SLOT_5TH(BOOST_PP_VALUE) / 1000UL == 9
#        define BOOST_PP_SLOT_TEMP_4 9
#    endif
# endif
#
# /* 3rd digit */
#
# if BOOST_PP_SLOT_SIG >= 3
#    if BOOST_PP_SLOT_4TH(BOOST_PP_VALUE) / 100UL == 0
#        define BOOST_PP_SLOT_TEMP_3 0
#    elif BOOST_PP_SLOT_4TH(BOOST_PP_VALUE) / 100UL == 1
#        define BOOST_PP_SLOT_TEMP_3 1
#    elif BOOST_PP_SLOT_4TH(BOOST_PP_VALUE) / 100UL == 2
#        define BOOST_PP_SLOT_TEMP_3 2
#    elif BOOST_PP_SLOT_4TH(BOOST_PP_VALUE) / 100UL == 3
#        define BOOST_PP_SLOT_TEMP_3 3
#    elif BOOST_PP_SLOT_4TH(BOOST_PP_VALUE) / 100UL == 4
#        define BOOST_PP_SLOT_TEMP_3 4
#    elif BOOST_PP_SLOT_4TH(BOOST_PP_VALUE) / 100UL == 5
#        define BOOST_PP_SLOT_TEMP_3 5
#    elif BOOST_PP_SLOT_4TH(BOOST_PP_VALUE) / 100UL == 6
#        define BOOST_PP_SLOT_TEMP_3 6
#    elif BOOST_PP_SLOT_4TH(BOOST_PP_VALUE) / 100UL == 7
#        define BOOST_PP_SLOT_TEMP_3 7
#    elif BOOST_PP_SLOT_4TH(BOOST_PP_VALUE) / 100UL == 8
#        define BOOST_PP_SLOT_TEMP_3 8
#    elif BOOST_PP_SLOT_4TH(BOOST_PP_VALUE) / 100UL == 9
#        define BOOST_PP_SLOT_TEMP_3 9
#    endif
# endif
#
# /* 2nd digit */
#
# if BOOST_PP_SLOT_SIG >= 2
#    if BOOST_PP_SLOT_3RD(BOOST_PP_VALUE) / 10UL == 0
#        define BOOST_PP_SLOT_TEMP_2 0
#    elif BOOST_PP_SLOT_3RD(BOOST_PP_VALUE) / 10UL == 1
#        define BOOST_PP_SLOT_TEMP_2 1
#    elif BOOST_PP_SLOT_3RD(BOOST_PP_VALUE) / 10UL == 2
#        define BOOST_PP_SLOT_TEMP_2 2
#    elif BOOST_PP_SLOT_3RD(BOOST_PP_VALUE) / 10UL == 3
#        define BOOST_PP_SLOT_TEMP_2 3
#    elif BOOST_PP_SLOT_3RD(BOOST_PP_VALUE) / 10UL == 4
#        define BOOST_PP_SLOT_TEMP_2 4
#    elif BOOST_PP_SLOT_3RD(BOOST_PP_VALUE) / 10UL == 5
#        define BOOST_PP_SLOT_TEMP_2 5
#    elif BOOST_PP_SLOT_3RD(BOOST_PP_VALUE) / 10UL == 6
#        define BOOST_PP_SLOT_TEMP_2 6
#    elif BOOST_PP_SLOT_3RD(BOOST_PP_VALUE) / 10UL == 7
#        define BOOST_PP_SLOT_TEMP_2 7
#    elif BOOST_PP_SLOT_3RD(BOOST_PP_VALUE) / 10UL == 8
#        define BOOST_PP_SLOT_TEMP_2 8
#    elif BOOST_PP_SLOT_3RD(BOOST_PP_VALUE) / 10UL == 9
#        define BOOST_PP_SLOT_TEMP_2 9
#    endif
# endif
#
# /* 1st digit */
#
# if BOOST_PP_SLOT_2ND(BOOST_PP_VALUE) == 0
#    define BOOST_PP_SLOT_TEMP_1 0
# elif BOOST_PP_SLOT_2ND(BOOST_PP_VALUE) == 1
#    define BOOST_PP_SLOT_TEMP_1 1
# elif BOOST_PP_SLOT_2ND(BOOST_PP_VALUE) == 2
#    define BOOST_PP_SLOT_TEMP_1 2
# elif BOOST_PP_SLOT_2ND(BOOST_PP_VALUE) == 3
#    define BOOST_PP_SLOT_TEMP_1 3
# elif BOOST_PP_SLOT_2ND(BOOST_PP_VALUE) == 4
#    define BOOST_PP_SLOT_TEMP_1 4
# elif BOOST_PP_SLOT_2ND(BOOST_PP_VALUE) == 5
#    define BOOST_PP_SLOT_TEMP_1 5
# elif BOOST_PP_SLOT_2ND(BOOST_PP_VALUE) == 6
#    define BOOST_PP_SLOT_TEMP_1 6
# elif BOOST_PP_SLOT_2ND(BOOST_PP_VALUE) == 7
#    define BOOST_PP_SLOT_TEMP_1 7
# elif BOOST_PP_SLOT_2ND(BOOST_PP_VALUE) == 8
#    define BOOST_PP_SLOT_TEMP_1 8
# elif BOOST_PP_SLOT_2ND(BOOST_PP_VALUE) == 9
#    define BOOST_PP_SLOT_TEMP_1 9
# endif
#
# undef BOOST_PP_VALUE
