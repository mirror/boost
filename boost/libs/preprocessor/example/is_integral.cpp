// Copyright (C) 2002
// Housemarque Oy
// http://www.housemarque.com
//
// Permission to copy, use, modify, sell and distribute this software is
// granted provided this copyright notice appears in all copies. This
// software is provided "as is" without express or implied warranty, and
// with no claim as to its suitability for any purpose.

// See http://www.boost.org for most recent version.

#include <boost/preprocessor/list/for_each.hpp>
#include <boost/preprocessor/tuple/to_list.hpp>

// This is a list of integral types. Strictly speaking the following list
// does not include all integral types, because some compilers do not yet
// recognize all standard C++ integral types.
#define INTEGRAL_TYPES\
  BOOST_PP_TUPLE_TO_LIST\
  ( 9\
  , ( char, signed char, unsigned char,\
      short, unsigned short,\
      int, unsigned int,\
      long, unsigned long )\
  )

// This is a template for testing is a type is an integral type.
template<class T> struct is_integral {static const bool value = false;};

#define INTEGRAL_TYPE_SPECIALIZATION(R,_,T)\
  template<> struct is_integral<T> {static const bool value = true;};\
  template<> struct is_integral<const T> {static const bool value = true;};\
  template<> struct is_integral<volatile T> {static const bool value = true;};\
  template<> struct is_integral<const volatile T> {static const bool value = true;};

BOOST_PP_LIST_FOR_EACH(INTEGRAL_TYPE_SPECIALIZATION,_,INTEGRAL_TYPES)
#undef INTEGRAL_TYPE_SPECIALIZATION
#undef INTEGRAL_TYPES
