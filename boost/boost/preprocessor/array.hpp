# ifndef BOOST_PREPROCESSOR_ARRAY_HPP
# define BOOST_PREPROCESSOR_ARRAY_HPP
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
# include <boost/preprocessor/tuple/elem.hpp>
#
# define BOOST_PP_ARRAY(size, data) (size, data)
#
# define BOOST_PP_ARRAY_SIZE(arr) BOOST_PP_ARRAY_SIZE_I arr
# define BOOST_PP_ARRAY_SIZE_I(size, data) size
#
# define BOOST_PP_ARRAY_DATA(arr) BOOST_PP_ARRAY_DATA_I arr
# define BOOST_PP_ARRAY_DATA_I(size, data) data
#
# define BOOST_PP_ARRAY_ELEM(i, arr) BOOST_PP_TUPLE_ELEM(BOOST_PP_ARRAY_SIZE_I arr, i, BOOST_PP_ARRAY_DATA_I arr)
#
# endif
