#ifndef BOOST_PREPROCESSOR_DETAIL_EXPAND_HPP
#define BOOST_PREPROCESSOR_DETAIL_EXPAND_HPP

/* Copyright (C) 2002 Vesa Karvonen
 *
 * Permission to copy, use, modify, sell and distribute this software is
 * granted provided this copyright notice appears in all copies. This
 * software is provided "as is" without express or implied warranty, and
 * with no claim as to its suitability for any purpose.
 *
 * See http://www.boost.org for most recent version.
 */

#define BOOST_PP_DETAIL_EXPAND(X) BOOST_PP_DETAIL_EXPAND_DELAY(X)
#define BOOST_PP_DETAIL_EXPAND_DELAY(X) X
#endif
