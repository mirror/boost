/*
 *
 * Copyright (c) 2002
 * Dr John Maddock
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Dr John Maddock makes no representations
 * about the suitability of this software for any purpose.
 * It is provided "as is" without express or implied warranty.
 *
 */

 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         regex_match.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Iterator traits for selecting an iterator type as
  *                an integral constant expression.
  */


#ifndef BOOST_REGEX_ITERATOR_CATEGORY_HPP
#define BOOST_REGEX_ITERATOR_CATEGORY_HPP

#include <iterator>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_pointer.hpp>

namespace boost{
namespace detail{

template <class I>
struct is_random_imp
{
private:
   typedef typename std::iterator_traits<I>::iterator_category cat;
public:
   BOOST_STATIC_CONSTANT(bool, value = (::boost::is_convertible<cat*, std::random_access_iterator_tag*>::value));
};

template <class I>
struct is_random_pointer_imp
{
   BOOST_STATIC_CONSTANT(bool, value = true);
};

template <bool is_pointer_type>
struct is_random_imp_selector
{
   template <class I>
   struct rebind
   {
      typedef is_random_imp<I> type;
   };
};

template <>
struct is_random_imp_selector<true>
{
   template <class I>
   struct rebind
   {
      typedef is_random_pointer_imp<I> type;
   };
};

}

template <class I>
struct is_random_access_iterator
{
private:
   typedef detail::is_random_imp_selector< ::boost::is_pointer<I>::value> selector;
   typedef typename selector::template rebind<I> bound_type;
   typedef typename bound_type::type answer;
public:
   BOOST_STATIC_CONSTANT(bool, value = answer::value);
};

}

#endif
