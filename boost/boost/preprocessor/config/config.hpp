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
# ifndef BOOST_PREPROCESSOR_CONFIG_CONFIG_HPP
# define BOOST_PREPROCESSOR_CONFIG_CONFIG_HPP
#
# /* BOOST_PP_CONFIG_FLAGS */
#
# define BOOST_PP_CONFIG_STRICT 0x0001
# define BOOST_PP_CONFIG_IDEAL 0x0002
#
# define BOOST_PP_CONFIG_MSVC 0x0004
# define BOOST_PP_CONFIG_MWCW 0x0008
# define BOOST_PP_CONFIG_BCC 0x0010
# define BOOST_PP_CONFIG_EDG 0x0020
#
# ifndef BOOST_PP_CONFIG_FLAGS
#    if defined(__EDG__)
#        define BOOST_PP_CONFIG_FLAGS (BOOST_PP_CONFIG_EDG | BOOST_PP_CONFIG_STRICT)
#    elif defined(_MSC_VER)
#        define BOOST_PP_CONFIG_FLAGS (BOOST_PP_CONFIG_MSVC)
#    elif defined(__MWERKS__)
#        define BOOST_PP_CONFIG_FLAGS (BOOST_PP_CONFIG_MWCW)
#    elif defined(__BORLANDC__)
#        define BOOST_PP_CONFIG_FLAGS (BOOST_PP_CONFIG_BCC)
#    else
#        define BOOST_PP_CONFIG_FLAGS (BOOST_PP_CONFIG_STRICT | BOOST_PP_CONFIG_IDEAL)
#    endif
# endif
#
# /* BOOST_PP_CONFIG_VARIADIC */
#
# if __STDC_VERSION__ >= 199901L && !defined(__cplusplus)
#    define BOOST_PP_CONFIG_VARIADIC_DEF 1
# else
#    define BOOST_PP_CONFIG_VARIADIC_DEF 0
# endif
#
# ifndef BOOST_PP_CONFIG_VARIADIC
#    define BOOST_PP_CONFIG_VARIADIC BOOST_PP_CONFIG_VARIADIC_DEF
# endif
#
# /* BOOST_PP_CONFIG_UNROLLED */
#
# define BOOST_PP_CONFIG_UNROLLED_DEF 0
#
# ifndef BOOST_PP_CONFIG_UNROLLED
#    define BOOST_PP_CONFIG_UNROLLED BOOST_PP_CONFIG_UNROLLED_DEF
# endif
#
# /* BOOST_PP_CONFIG_WARNINGS */
#
# ifndef NDEBUG
#    define BOOST_PP_CONFIG_WARNINGS_DEF 1
# else
#    define BOOST_PP_CONFIG_WARNINGS_DEF 0
# endif
#
# ifndef BOOST_PP_CONFIG_WARNINGS
#    define BOOST_PP_CONFIG_WARNINGS BOOST_PP_CONFIG_WARNINGS_DEF
# endif
#
# /* BOOST_PP_CONFIG_ERRORS */
#
# ifndef NDEBUG
#    define BOOST_PP_CONFIG_ERRORS_DEF 1
# else
#    define BOOST_PP_CONFIG_ERRORS_DEF 0
# endif
#
# ifndef BOOST_PP_CONFIG_ERRORS
#    define BOOST_PP_CONFIG_ERRORS BOOST_PP_CONFIG_ERRORS_DEF
# endif
#
# /* BOOST_PP_CONFIG_EXTENDED_LINE_INFO */
#
# define BOOST_PP_CONFIG_EXTENDED_LINE_INFO_DEF 0
#
# ifndef BOOST_PP_CONFIG_EXTENDED_LINE_INFO
#    define BOOST_PP_CONFIG_EXTENDED_LINE_INFO BOOST_PP_CONFIG_EXTENDED_LINE_INFO_DEF
# endif
#
# endif
