/* Copyright (C) 2002
 * Housemarque Oy
 * http://www.housemarque.com
 *
 * Permission to copy, use, modify, sell and distribute this software is
 * granted provided this copyright notice appears in all copies. This
 * software is provided "as is" without express or implied warranty, and
 * with no claim as to its suitability for any purpose.
 *
 * See http://www.boost.org for most recent version.
 */

/* This example demonstrates the usage of preprocessor lists for generating C++ code. */

#include <boost/preprocessor/list/for_each.hpp>
#include <boost/preprocessor/tuple/to_list.hpp>
#include <boost/preprocessor/empty.hpp>

/* List of integral types. (Strictly speaking, wchar_t should be on the list.) */
#define INTEGRAL_TYPES\
  BOOST_PP_TUPLE_TO_LIST(9,(char, signed char, unsigned char, short, unsigned short, int, unsigned, long, unsigned long))

/* Template for testing whether a type is an integral type. */
template<class T> struct is_integral {enum {value = false};};

/* Macro for defining a specialization of is_integral<> template.
 * NOTE: CV is invoked so that it is possible to pass empty cv-qualifiers.
 */
#define IS_INTEGRAL_SPECIALIZATION(_,CV,T)\
  template<> struct is_integral<CV() T> {enum {value = true};};

BOOST_PP_LIST_FOR_EACH(IS_INTEGRAL_SPECIALIZATION, BOOST_PP_EMPTY, INTEGRAL_TYPES)
BOOST_PP_LIST_FOR_EACH(IS_INTEGRAL_SPECIALIZATION, const BOOST_PP_EMPTY, INTEGRAL_TYPES)
BOOST_PP_LIST_FOR_EACH(IS_INTEGRAL_SPECIALIZATION, volatile BOOST_PP_EMPTY, INTEGRAL_TYPES)
BOOST_PP_LIST_FOR_EACH(IS_INTEGRAL_SPECIALIZATION, const volatile BOOST_PP_EMPTY, INTEGRAL_TYPES)
#undef IS_INTEGRAL_SPECIALIZATION
#undef INTEGRAL_TYPES
