// Copyright David Abrahams 2004. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef POINTEE_DWA200415_HPP
# define POINTEE_DWA200415_HPP

// dereferenceable_traits provides access to the value_type and
// reference of a Dereferenceable type.

# include <boost/detail/is_incrementable.hpp>
# include <boost/iterator/iterator_traits.hpp>
# include <boost/type_traits/remove_cv.hpp>
# include <boost/mpl/apply_if.hpp>

namespace boost { 

namespace detail
{
  template <class P>
  struct smart_ptr_value
  {
      typedef typename remove_cv<typename P::element_type>::type type;
  };
}

template <class P>
struct pointee
{
    typedef typename remove_cv<P>::type stripped;
    
    typedef typename mpl::apply_if<
        detail::is_incrementable<stripped>
      , iterator_value<stripped>
      , detail::smart_ptr_value<stripped>
    >::type type;
};
  
} // namespace boost

#endif // POINTEE_DWA200415_HPP
