# ifndef BOOST_PREPROCESSOR_SLOT_HPP
# define BOOST_PREPROCESSOR_SLOT_HPP
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
# include <boost/preprocessor/detail/cat.hpp>
# include <boost/preprocessor/detail/line.hpp>
#
# define BOOST_PP_SLOT_LIMIT 5
#
# define BOOST_PP_ASSIGN_SLOT(i) BOOST_PP_DETAIL_CAT4(<boost/preprocessor/detail/slot/slot, i, ., hpp>)
# define BOOST_PP_SLOT(i) BOOST_PP_DETAIL_CAT2(BOOST_PP_SLOT_, i)
#
# endif
