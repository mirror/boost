# ifndef BOOST_PREPROCESSOR_DETAIL_LINE_HPP
# define BOOST_PREPROCESSOR_DETAIL_LINE_HPP
#
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
# include <boost/preprocessor/stringize.hpp>
#
# if !defined(__MWERKS__) || defined(BOOST_NO_COMPILER_CONFIG) || __MWERKS__ > 0x3002
#   define BOOST_PP_DETAIL_LINE(text) 1 BOOST_PP_STRINGIZE(text)
# else
#   define BOOST_PP_DETAIL_LINE(text) 1
# endif
#
# endif
