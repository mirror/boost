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
# if !defined(__MWERKS__) || defined(BOOST_NO_COMPILER_CONFIG) || __MWERKS__ > 0x3002 
#   define BOOST_PP_ARRAY_SIZE(arr) BOOST_PP_ARRAY_SIZE_I arr
# else
#   define BOOST_PP_ARRAY_SIZE(arr) BOOST_PP_ARRAY_SIZE_D(arr)
#   define BOOST_PP_ARRAY_SIZE_D(arr) BOOST_PP_ARRAY_SIZE_I ## arr
# endif
#
# define BOOST_PP_ARRAY_SIZE_I(size, data) size
#
# if !defined(__MWERKS__) || defined(BOOST_NO_COMPILER_CONFIG) || __MWERKS__ > 0x3002
#   define BOOST_PP_ARRAY_DATA(arr) BOOST_PP_ARRAY_DATA_I arr
# else
#   define BOOST_PP_ARRAY_DATA(arr) BOOST_PP_ARRAY_DATA_D(arr)
#   define BOOST_PP_ARRAY_DATA_D(arr) BOOST_PP_ARRAY_DATA_I ## arr
# endif
#
# define BOOST_PP_ARRAY_DATA_I(size, data) data
#
# if !defined(__MWERKS__) || defined(BOOST_NO_COMPILER_CONFIG) || __MWERKS__ > 0x3002
#   define BOOST_PP_ARRAY_ELEM(i, arr) BOOST_PP_TUPLE_ELEM(BOOST_PP_ARRAY_SIZE_I arr, i, BOOST_PP_ARRAY_DATA_I arr)
# else
#   define BOOST_PP_ARRAY_ELEM(i, arr) BOOST_PP_ARRAY_ELEM_D(i, arr)
#   define BOOST_PP_ARRAY_ELEM_D(i, arr) BOOST_PP_TUPLE_ELEM(BOOST_PP_ARRAY_SIZE(arr), i, BOOST_PP_ARRAY_DATA(arr))
# endif
#
# endif
