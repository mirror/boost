#ifndef BOOST_PREPROCESSOR_LIST_HPP
#define BOOST_PREPROCESSOR_LIST_HPP

/* Copyright (C) 2001
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

/** <p>Includes all list headers.</p>

<p>A list is an arbitrary size collection of elements.</p>

<p>In the preprocessor library, the internal representation of lists
uses parts that are like macro parameter lists. Thus an element of a list
can be any sequence of tokens that constitutes a single macro parameter.</p>

<p>Lists are manipulated using both list ADT macros and higher-order macros. For an introduction to manipulation of lists in functional programming, see
<a href="../bibliography.htm#[Thompson]">[Thompson]</a>,
<a href="../bibliography.htm#[Abelson]">[Abelson]</a> or
<a href="../bibliography.htm#[Cousineau]">[Cousineau]</a>.</p>
*/

#include <boost/preprocessor/list/append.hpp>
#include <boost/preprocessor/list/at.hpp>
#include <boost/preprocessor/list/cat.hpp>
#include <boost/preprocessor/list/filter.hpp>
#include <boost/preprocessor/list/first_n.hpp>
#include <boost/preprocessor/list/for_each.hpp>
#include <boost/preprocessor/list/for_each_product.hpp>
#include <boost/preprocessor/list/size.hpp>
#include <boost/preprocessor/list/to_tuple.hpp>
#include <boost/preprocessor/list/transform.hpp>
#endif
