// (C) Copyright David Abrahams 2004.
// (C) Copyright Jonathan Turkanis 2005.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_IS_DEREFERENCEABLE_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_IS_DEREFERENCEABLE_HPP_INCLUDED

namespace boost { namespace iostreams { namespace detail { 

// is_dereferenceable<T> metafunction
//
// Requires: Given x of type T&, if the expression *x is well-formed
// it must have complete type; otherwise, it must neither be ambiguous
// nor violate access.

// This namespace ensures that ADL doesn't mess things up.
namespace is_dereferenceable_
{
  // a type returned from operator* when no increment is found in the
  // type's own namespace
  struct tag {};
  
  // any soaks up implicit conversions and makes the following
  // operator* less-preferred than any other such operator that
  // might be found via ADL.
  struct any { template <class T> any(T const&); };

  // This is a last-resort operator* for when none other is found
  tag operator*(any const&);

# if BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3202)) \
    || BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
#  define BOOST_comma(a,b) (a)
# else 
  // In case an operator++ is found that returns void, we'll use ++x,0
  tag operator,(tag,int);  
#  define BOOST_comma(a,b) (a,b)
# endif 
  
  // two check overloads help us identify which operator++ was picked
  char (& check(tag) )[2];
  
  template <class T>
  char check(T const&);
  
  template <class T>
  struct impl
  {
      static typename remove_cv<T>::type& x;

      BOOST_STATIC_CONSTANT(
          bool
        , value = sizeof(is_dereferenceable_::check(BOOST_comma(*x,0))) == 1
      );
  };
}

# undef BOOST_comma

template <class T>
struct is_dereferenceable
    : mpl::bool_< ::boost::detail::is_incrementable_::impl<T>::value >
    { };

} } } // End namespaces detail, iostreams, boost.

#endif // BOOST_IOSTREAMS_DETAIL_IS_DEREFERENCEABLE_HPP_INCLUDED
