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

/* This example shows how BOOST_PP_EMPTY can be used as an unused or
 * empty parameter.
 */

#include <boost/preprocessor/empty.hpp>

/* This could be a layer from a generative container library. */
template<class base>
struct subscript_layer : base
{
#define DEF(CV)\
  CV() typename base::value_type& operator[](typename base::index_type i) CV()\
  { return base::begin()[i]; }

  DEF(BOOST_PP_EMPTY)
  DEF(const BOOST_PP_EMPTY)
#undef DEF
};
