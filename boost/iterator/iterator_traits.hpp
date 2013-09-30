// Copyright David Abrahams 2003.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef ITERATOR_TRAITS_DWA200347_HPP
# define ITERATOR_TRAITS_DWA200347_HPP

# include <boost/detail/iterator.hpp>
# include <boost/detail/workaround.hpp>

namespace boost { 

// Obsolete. Remove.
#define BOOST_ITERATOR_CATEGORY iterator_category


template <class Iterator>
struct iterator_value
{
    typedef typename boost::detail::iterator_traits<Iterator>::value_type type;
};
  
template <class Iterator>
struct iterator_reference
{
    typedef typename boost::detail::iterator_traits<Iterator>::reference type;
};
  
  
template <class Iterator>
struct iterator_pointer
{
    typedef typename boost::detail::iterator_traits<Iterator>::pointer type;
};
  
template <class Iterator>
struct iterator_difference
{
    typedef typename boost::detail::iterator_traits<Iterator>::difference_type type;
};

template <class Iterator>
struct iterator_category
{
    typedef typename boost::detail::iterator_traits<Iterator>::iterator_category type;
};

# if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
template <>
struct iterator_value<int>
{
    typedef void type;
};
  
template <>
struct iterator_reference<int>
{
    typedef void type;
};

template <>
struct iterator_pointer<int>
{
    typedef void type;
};
  
template <>
struct iterator_difference<int>
{
    typedef void type;
};
  
template <>
struct iterator_category<int>
{
    typedef void type;
};
# endif

} // namespace boost::iterator

#endif // ITERATOR_TRAITS_DWA200347_HPP
